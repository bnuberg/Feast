#include "Dungeon.h"
#include "GameManager.h"
#include "EnemyManager.h";

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
	dungeonNode->setScale(dungeonScale);

	sceneManager->setAmbientLight(Ogre::ColourValue(.8, .8, .8));
	Ogre::Light* light = sceneManager->createLight("SecondaryLight");
	light->setPosition(20, 5000, 50);

	mgr.mSceneMgr->getSceneNode("dungeon")->translate(dungeonSpawnPoint, Ogre::Node::TS_LOCAL);

	mgr.mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
}
