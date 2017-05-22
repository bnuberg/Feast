#include "Dungeon.h"
#include "GameManager.h"
#include "EnemyManager.h";

/** Constructor.\n
*/
Dungeon::Dungeon(SceneManager* sceneManager)
{
	enemySpawnPoints[0] = Vector3(100, 0, 100);
	enemySpawnPoints[1] = Vector3(200, 0, 300);
	enemySpawnPoints[2] = Vector3(1000, 0, -1000);

	LoadScene(sceneManager);
	SpawnEnemies();
}

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

/** Load Dungeon.mesh.\n
*/
void Dungeon::LoadScene(SceneManager* sceneManager)
{
	GameManager& mgr = GameManager::getSingleton();
	Entity* dungeonEntity = mgr.mSceneMgr->createEntity("Dungeonmesh", meshName);

	Vector3 startingPosition = Vector3(0, 0, 0);
	SceneNode* dungeonNode = sceneManager->getRootSceneNode()->createChildSceneNode("dungeon", startingPosition);
	dungeonNode->attachObject(dungeonEntity);
	dungeonNode->setScale(Vector3(4, 4, 4));

	mgr.mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
}

/** Spawning the enemies
*/
void Dungeon::SpawnEnemies()
{
	GameManager& mgr = GameManager::getSingleton();

	for each (Vector3 spawnPoint in enemySpawnPoints)
	{
		mgr.mEnemyManager.SpawnHeavyEnemy(spawnPoint);
	}
}
