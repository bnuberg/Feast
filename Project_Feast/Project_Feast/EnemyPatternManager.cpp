#include "EnemyPatternManager.h"

EnemyPatternManager::EnemyPatternManager()
	:aggroRange(0),
	 attackRange(0)
{	
	
}	

EnemyPatternManager::~EnemyPatternManager()
{

}

void EnemyPatternManager::BasicEnemy()
{
	//Override enemy movement
	//Variable aggro range on enemy type
	aggroRange = 500;
	attackRange = 100;
	//Enemy moves towards player when player is in aggro range
	//Enemy moves sideways when player is in attack range
	//Enemy moves away if the player gets too close
	//Enemy loses interest in player if the player moves out of aggro range for a certain amount of time
}

float EnemyPatternManager::setAggroR()
{
	return aggroRange;
}

float EnemyPatternManager::setAttackR()
{
	return attackRange;
}

void EnemyPatternManager::createTravelGrid(std::vector<Ogre::Vector3> positions, std::vector<bool> blockages, Ogre::Vector3 startPosition, Ogre::Vector3 endPosition)
{
	EnemyPatternManager::startPosition = simplifyPosition2(startPosition);
	EnemyPatternManager::endPosition = simplifyPosition2(endPosition);
	int i = 0;
	for (auto position : positions)
	{
		gridPosition thisPosition;
		thisPosition.position = simplifyPosition2(position);
		thisPosition.isBlocked = blockages[i];
		grid.push_back(thisPosition);
		i++;
	}
	pathFind();
}

// If only this was asynchronous. Call this when you want to find a path but the environment remains the same as before.
void EnemyPatternManager::updateStartAndEndPositions(Ogre::Vector3 enemyPosition, Ogre::Vector3 playerPosition)
{
	openList.empty();
	closedList.empty();
	startPosition = simplifyPosition2(enemyPosition);
	endPosition = simplifyPosition2(playerPosition);
	pathFind();
}

std::vector<Ogre::Vector3> EnemyPatternManager::getRoute()
{
	return route;
}

/** Rounds a Vector3 to the nearest hundred.
*	@param position The original position to be rounded.
*	@return value A Vector3 equal to the original position rounded to the
*	nearest hundred.
*/
Ogre::Vector3 EnemyPatternManager::simplifyPosition3(Ogre::Vector3 position)
{
	// Convert cm to m
	Ogre::Vector3 newPos = position / 100;
	newPos.x = Matth::round(newPos.x);
	newPos.y = 0.0;
	newPos.z = Matth::round(newPos.z);
	return newPos;
}

/** Rounds a Vector3 to the nearest hundred.
*	@param position The original position to be rounded.
*	@return value A Vector2 equal to the original position rounded to the
*	nearest hundred. The Y component isn't considered.
*/
Ogre::Vector2 EnemyPatternManager::simplifyPosition2(Ogre::Vector3 position)
{
	Ogre::Vector3 newPos = position / 100;
	newPos.x = Matth::round(newPos.x);
	newPos.z = Matth::round(newPos.z);
	return Ogre::Vector2(newPos.x, newPos.z);
}

/** Finds the distance between a given position and the end position.\n
*	Doesn't use diagonals.
*	@param position A Vector2 of where the currently considered square is.
*	@return The integer value of simplified distance between 2 points.
*/
int EnemyPatternManager::calculateManhattanDistance(Ogre::Vector2 position)
{
	return Matth::absi(position.x - endPosition.x) + Matth::absi(position.y - endPosition.y);
}

// Do not call this method often!
void EnemyPatternManager::pathFind()
{
	foundEndPos = false;
	Ogre::Vector2 ePos = EnemyPatternManager::endPosition;
	Ogre::Vector2 sPos = EnemyPatternManager::startPosition;

	currentPosition.position = startPosition;
	while (!foundEndPos)
	{
		checkAdjacentPositions(currentPosition);
		findNextSquare();
	}
	assignPathToEnemy();
	// Make sure the current route is empty
	//route.clear();
	//route[0] = ePos;
}

void EnemyPatternManager::checkAdjacentPositions(gridPosition current)
{
	// Create Positions
	gridPosition above;
	above.position.x = current.position.x;
	above.position.y = current.position.y - 1;

	gridPosition left;
	left.position.x = current.position.x - 1;
	left.position.y = current.position.y;

	gridPosition below;
	below.position.x = current.position.x;
	below.position.y = current.position.y + 1;

	gridPosition right;
	right.position.x = current.position.x + 1;
	right.position.y = current.position.y;

	// See if position exists in the grid and is not blocked
	// NB: When ordering the contents of if statements, be sure to put whichever is most likely to fail first at the start, to improve performance.
	if (!getGridPositionAt(above.position).isBlocked && !existsInClosedList(above.position) && getGridPositionAt(above.position).position.x != -1)
	{
		// Add that position to the open list
		above.movCostFromStart++;
		openList.push_back(getGridPositionAt(above.position));
	}
	if (!getGridPositionAt(left.position).isBlocked && !existsInClosedList(left.position) && getGridPositionAt(left.position).position.x != -1)
	{
		left.movCostFromStart++;
		openList.push_back(getGridPositionAt(left.position));
	}
	if (!getGridPositionAt(below.position).isBlocked && !existsInClosedList(below.position) && getGridPositionAt(below.position).position.x != -1)
	{
		below.movCostFromStart++;
		openList.push_back(getGridPositionAt(below.position));
	}
	if (!getGridPositionAt(right.position).isBlocked && !existsInClosedList(right.position) && getGridPositionAt(right.position).position.x != -1)
	{
		right.movCostFromStart++;
		openList.push_back(getGridPositionAt(right.position));
	}
}

EnemyPatternManager::gridPosition EnemyPatternManager::getGridPositionAt(Ogre::Vector2 checkPosition)
{
	// There must be a better way of doing this.
	for (gridPosition gp : grid)
	{
		if (gp.position.x == checkPosition.x && gp.position.y == checkPosition.y)
		{
			return gp;
		}
	}
	gridPosition invalidPosition;
	invalidPosition.position.x = -1;
	return invalidPosition;
}

bool EnemyPatternManager::existsInClosedList(Ogre::Vector2 checkPosition)
{
	for (gridPosition gp : closedList)
	{
		if (gp.position == checkPosition)
		{
			return true;
		}
	}
	return false;
}

void EnemyPatternManager::findNextSquare()
{
	// Find which has the smallest total cost
	// If there's a tie, find whichever has -individually- the lowest H score, then highest G score

	gridPosition bestGP;
	// Initialize best GP to worst so it can be replaced by the actual best.
	bestGP.sumCost = 1000;
	bestGP.movCostFromStart = 0;
	bestGP.movCostToEnd = 500;

	for (gridPosition gp : openList)
	{
		gp.movCostToEnd = calculateManhattanDistance(gp.position);
		gp.sumCost = gp.movCostFromStart + gp.movCostToEnd;
		if (gp.sumCost < bestGP.sumCost)
		{
			bestGP = gp;
		}
		else if (gp.sumCost == bestGP.sumCost)
		{
			if (gp.movCostToEnd < bestGP.movCostToEnd)
			{
				bestGP.movCostToEnd = gp.movCostToEnd;
			}
			else if (gp.movCostFromStart > bestGP.movCostFromStart)
			{
				bestGP.movCostFromStart = gp.movCostFromStart;
			}
			else if (gp.movCostToEnd == bestGP.movCostToEnd && gp.movCostFromStart == bestGP.movCostFromStart)
			{
				// All positions that reach this point are equally valid
				// So just assign the current one
				bestGP = gp;
			}
		}
	}
	if (bestGP.position == endPosition)
	{
		foundEndPos = true;
	}
	currentPosition = bestGP;
	closedList.push_back(bestGP);
}

void EnemyPatternManager::assignPathToEnemy()
{
	int i = 0;
	for (gridPosition gp : closedList)
	{
		route[i] = Ogre::Vector3(gp.position.x, 0.0, gp.position.y) * 100; // Don't forget to scale back to cm
		i++;
	}
	// Then get the enemy to follow that path...
}
