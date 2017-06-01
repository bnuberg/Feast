#include "Dungeon.h"
#include "GameManager.h"
#include "EnemyManager.h"

/** Constructor.\n
*/
Dungeon::Dungeon(SceneManager* sceneManager)
{
	LoadScene(sceneManager);
}

/** Deconstructor.\n
*/
Dungeon::~Dungeon(){}

/** Returns the player spawn point.\n
	@return Vector3 player spawn point
*/
Vector3 Dungeon::GetPlayerSpawnPoint() const
{
	return playerSpawnPoint;
}

/** Returns the radius from what point on entities fall.\n
	@return Real length from center
*/
Real Dungeon::GetFallRange()
{ 
	return fallRange; 
}

/** Load Dungeon.mesh, lava mesh, wall mesh, skybox and lights.\n
*/
void Dungeon::LoadScene(SceneManager* sceneManager)
{
	
	GameManager& mgr = GameManager::getSingleton();
	Vector3 startingPosition = Vector3(0, 0, 0);

	/*Platform + base lava*/
	Entity* dungeonEntity = mgr.mSceneMgr->createEntity("Dungeonmesh", meshName);
	SceneNode* dungeonNode = sceneManager->getRootSceneNode()->createChildSceneNode("dungeon", startingPosition);
	dungeonNode->attachObject(dungeonEntity);
	dungeonNode->setScale(dungeonScale);
	dungeonNode->translate(dungeonSpawnPoint, Node::TS_LOCAL);

	/*Blocky wall*/
	Entity* dungeonBoxEntity = mgr.mSceneMgr->createEntity("DungeonBoxmesh", boxMeshName);
	SceneNode* dungeonBoxNode = sceneManager->getRootSceneNode()->createChildSceneNode("dungeonBox", startingPosition);
	dungeonBoxNode->attachObject(dungeonBoxEntity);
	dungeonBoxNode->setScale(4 * dungeonScale);
	dungeonBoxNode->translate(dungeonSpawnPoint, Node::TS_LOCAL);

	/*Lava*/
	Entity* dungeonLavaEntity = mgr.mSceneMgr->createEntity("DungeonLavamesh", lavaMeshName);
	SceneNode* dungeonLavaNode = sceneManager->getRootSceneNode()->createChildSceneNode("dungeonLava", startingPosition);
	dungeonLavaNode->attachObject(dungeonLavaEntity);
	dungeonLavaNode->setScale(8 * dungeonScale);
	dungeonLavaNode->translate(1.5 * dungeonSpawnPoint, Node::TS_LOCAL);

	// Create an ambient light
	sceneManager->setAmbientLight(ColourValue(.5, .5, .5));
	Light* light = sceneManager->createLight("MainLight");
	light->setPosition(20, 80, 50);

	//Create second ambient light
	sceneManager->setAmbientLight(ColourValue(.8, .8, .8));
	Light* light2 = sceneManager->createLight("SecondaryLight");
	light2->setPosition(20, 5000, 50);

	Light* light3 = sceneManager->createLight("TertiaryLight");
	light3->setType(Light::LT_DIRECTIONAL);
	light3->setPosition(5000, 5000, 5000);
	light3->setDirection(-1, -1, -0.5);

	/*Skybox*/
	mgr.mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
}
