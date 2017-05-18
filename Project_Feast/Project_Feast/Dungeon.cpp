#include "Dungeon.h"

/** Constructor.\n
*/
Dungeon::Dungeon(){}

/** Deconstructor.\n
*/
Dungeon::~Dungeon(){}

/** Returns the player spawn point.\n
	@return Vector3 player spawn point
*/
Vector3 Dungeon::GetPlayerSpawnPoint()
{
	return playerSpawnPoint;
}

/** Returns the enemy spawn points.\n
	@return Vector3 array of the enemy spawn points
*/
Vector3 Dungeon::GetEnemySpawnPoints()
{
	return enemySpawnPoints;
}
