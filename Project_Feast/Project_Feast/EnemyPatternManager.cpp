#include "EnemyPatternManager.h"
#include "Matth.h"
#include "Grid.h"

EnemyPatternManager::EnemyPatternManager()
	:aggroRange(0),
	 attackRange(0)
{	
	invalidPosition.position.x = -600;
	invalidPosition.position.y = -600;

	lastEndPosition = invalidPosition.position;
	lastStartPosition = invalidPosition.position;
}	

EnemyPatternManager::~EnemyPatternManager()
{

}

void EnemyPatternManager::BasicEnemy()
{
	//Override enemy movement
	//Variable aggro range on enemy type
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
unsigned long EnemyPatternManager::setAttackT()
{
	return attackTimer;
}

void EnemyPatternManager::attackPattern()
{
	//if (Ogre::Entity* ENEMYARM == GameManager::getSingleton().mSceneMgr->createEntity(MESHNAME)){
		//aggroRange = 400;
		//attackRange = 100;
		//attackTimer = 5000;
	//}
	//if (Ogre::Entity* ENEMYARM == GameManager::getSingleton().mSceneMgr->createEntity(MESHNAME)){
	//	aggroRange = 600;
	//	attackRange = 250;
	//	attackTimer = 10000;
	//}
	//if (Ogre::Entity* ENEMYARM == GameManager::getSingleton().mSceneMgr->createEntity(MESHNAME)){
	//	aggroRange = 500;
	//	attackRange = 100;
	//	attackTimer = 70000;
	//}


	
}

void EnemyPatternManager::createTravelGrid()
{
	Grid * blockagesGrid = Grid::getInstance();
	if (blockagesGrid == nullptr)
		return;

	grid = new gridPosition[blockagesGrid->getWidth() * blockagesGrid->getHeight()];
}

// If only this was asynchronous. Call this when you want to find a path but the environment remains the same as before.
void EnemyPatternManager::updateStartAndEndPositions(Ogre::Vector3 enemyPosition, Ogre::Vector3 playerPosition, int enemyNumber)
{
	startPosition = simplifyPosition2(enemyPosition);
	endPosition = simplifyPosition2(playerPosition);
	pathFind(enemyNumber);
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
void EnemyPatternManager::pathFind(int enemyNumber)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("Starting path find.");
	foundEndPos = false;

	currentPosition.position = startPosition;
	int safetyCounter = 0;
	Ogre::Vector2 lastPosition;

	// If the player moves
	if (endPosition != lastEndPosition)
	{
		if (!openList.empty())
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("Clearing open list.");
			openList.clear();
		}
		if (!closedList.empty())
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("Clearing closed list.");
			closedList.clear();
		}
		if(!route.empty())
			route.clear();
		Ogre::LogManager::getSingletonPtr()->logMessage("end position is not the last end position.");
		while (!foundEndPos && safetyCounter < 100)
		{
			//Ogre::LogManager::getSingletonPtr()->logMessage("About to check current position.");
			checkAdjacentPositions(currentPosition);
			//Ogre::LogManager::getSingletonPtr()->logMessage("About to check next position.");
			lastPosition = currentPosition.position;
			findNextSquare(enemyNumber);
			if (currentPosition.position == lastPosition)
				break;
			//Ogre::LogManager::getSingletonPtr()->logMessage("About to create route.");
			safetyCounter++;
		}
		if (foundEndPos)
			assignPathToEnemy(enemyNumber);
	}
	// If the enemy moves
	else if (startPosition != lastStartPosition && route.size() > 1)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("start position is not the last start position.");
		route.erase(route.begin());
	}
	// else keep going to first point in route

	lastEndPosition = endPosition;
	lastStartPosition = startPosition;
	
	//Ogre::LogManager::getSingletonPtr()->logMessage("Route created.");
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

	addIfValidToOpenList(above);
	addIfValidToOpenList(left);
	addIfValidToOpenList(below);
	addIfValidToOpenList(right);
}

void EnemyPatternManager::addIfValidToOpenList(gridPosition &gPosition)
{
	Grid * blockagesGrid = Grid::getInstance();
	if (blockagesGrid == nullptr)
		return;

	if (!blockagesGrid->isBlocked(gPosition.position) && !existsInClosedList(gPosition.position))
	{
		// Add that position to the open list
		gPosition.movCostFromStart++;
		gridPosition gp = getGridPositionAt(gPosition.position);
		// Assign position to grid position
		gp.position = gPosition.position;
		openList.push_back(gp);
	}
}

EnemyPatternManager::gridPosition EnemyPatternManager::getGridPositionAt(Ogre::Vector2 checkPosition)
{
	Grid * blockagesGrid = Grid::getInstance();
	if (blockagesGrid == nullptr)
		return invalidPosition;

	return grid[blockagesGrid->getIndexFromPosition(checkPosition)];
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

void EnemyPatternManager::findNextSquare(int enemyNumber)
{
	// Find which has the smallest total cost
	// If there's a tie, find whichever has -individually- the lowest H score, then highest G score

	if (openList.empty())
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Open list is empty.");
		return;
	}
		

	gridPosition bestGP;
	// Initialize best GP to worst so it can be replaced by the actual best.
	bestGP.sumCost = -1;
	bestGP.movCostFromStart = 0;
	bestGP.movCostToEnd = 500;

	int i = 0;
	int bestIndex = -1;

	for (gridPosition gp : openList)
	{
		gp.movCostToEnd = calculateManhattanDistance(gp.position);
		gp.sumCost = gp.movCostFromStart + gp.movCostToEnd;
		if (gp.sumCost < bestGP.sumCost || bestGP.sumCost == -1)
		{
			bestGP = gp;
			bestIndex = i;
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
				bestIndex = i;
			}
		}
		i++;
	}
	if (bestGP.position == endPosition)
	{
		char message[2000];
		sprintf_s(message, "Found end position. Enemy number: %d", enemyNumber);
		Ogre::LogManager::getSingletonPtr()->logMessage(message);
		foundEndPos = true;
	}
	else
	{
		char message[2000];
		sprintf_s(message, "Changed position. Enemy number: %d. Position: %f, %f", enemyNumber, bestGP.position.x, bestGP.position.y);
		Ogre::LogManager::getSingletonPtr()->logMessage(message);
	}
	currentPosition = bestGP;
	if(bestIndex != -1)
		openList.erase(openList.begin() + bestIndex);
	closedList.push_back(bestGP);
}

void EnemyPatternManager::assignPathToEnemy(int enemyNumber)
{
	for (gridPosition gp : closedList)
	{
		route.push_back(Ogre::Vector3(gp.position.x, 0.0, gp.position.y) * 100); // Don't forget to scale back to cm
	}
	if (route.size() > 0)
	{
		char message[2000];
		sprintf_s(message, "Path found! Enemy number: %d. Position: %f, %f", enemyNumber, route[0].x, route[0].z);
		Ogre::LogManager::getSingletonPtr()->logMessage(message);
	}
	
	// Then get the enemy to follow that path...
}
