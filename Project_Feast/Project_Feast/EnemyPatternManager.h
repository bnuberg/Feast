#pragma once
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreTimer.h>
#include "GameManager.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include <vector>


class EnemyPatternManager
{
public:
	EnemyPatternManager();
	~EnemyPatternManager();
	void BasicEnemy();
	float setAggroR();
	float setAttackR();

	// Boolean is for whether or not it is blocked - only call this once. - At this point a series of operations is performed to generate route.
	// Route can be found by calling getRoute().
	// It returns the route between startPosition and endPosition
	void createTravelGrid(std::vector<Ogre::Vector3> positions, std::vector<bool> blockages);
	void updateStartAndEndPositions(Ogre::Vector3 enemyPosition, Ogre::Vector3 playerPosition, int enemyNumber);
	std::vector<Ogre::Vector3> getRoute();
private:
	float aggroRange;
	float attackRange;

	Ogre::Vector3 simplifyPosition3(Ogre::Vector3 position);
	Ogre::Vector2 simplifyPosition2(Ogre::Vector3 position);

	int calculateManhattanDistance(Ogre::Vector2 position);

	bool gridIsSet = false;

	// Uses the A* Method, as described here: https://www.raywenderlich.com/4946/introduction-to-a-pathfinding
	// and here: http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html
	void pathFind(int enemyNumber);

	std::vector<Ogre::Vector3> route;

	// Does not use the parent system.
	struct gridPosition
	{
		Ogre::Vector2 position;
		bool isBlocked;
		int movCostFromStart = 0; // G
		int movCostToEnd;         // H
		int sumCost;              // F
	};

	Ogre::Vector2 startPosition, endPosition;
	Ogre::Vector2 lastStartPosition, lastEndPosition;

	gridPosition currentPosition;

	// Adds valid adjacent positions to the open list
	void checkAdjacentPositions(gridPosition currentPosition, int enemyNumber);

	// Returns a grid position at a given location
	gridPosition getGridPositionAt(Ogre::Vector2 checkPosition);

	// Finds whether or not an item already exists in the closed list
	bool existsInClosedList(Ogre::Vector2 checkPosition);

	// Adds the next square (from the list of open positions) to the closed list
	void findNextSquare(int enemyNumber);

	// Only create grid once, when the game loads.
	// The main point of this is to assign the positions and isBlocked values.
	std::vector<gridPosition> grid;

	// Positions open for consideration
	std::vector<gridPosition> openList;
	// Positions chosen and won't be considered again.
	std::vector<gridPosition> closedList;

	// Do this last.
	void assignPathToEnemy(int enemyNumber);

	bool foundEndPos = false;

	gridPosition invalidPosition;

	
};
