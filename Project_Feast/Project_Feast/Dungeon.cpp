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

	// Create an ambient light
	sceneManager->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
	Ogre::Light* light = sceneManager->createLight("MainLight");
	light->setPosition(20, 80, 50);

	//Create second ambient light
	sceneManager->setAmbientLight(Ogre::ColourValue(.8, .8, .8));
	Ogre::Light* light2 = sceneManager->createLight("SecondaryLight");
	light2->setPosition(20, 5000, 50);

	Ogre::Light* light3 = sceneManager->createLight("TertiaryLight");
	light3->setType(Ogre::Light::LT_DIRECTIONAL);
	light3->setPosition(5000, 5000, 5000);
	light3->setDirection(-1, -1, -1);

	mgr.mSceneMgr->getSceneNode("dungeon")->translate(dungeonSpawnPoint, Ogre::Node::TS_LOCAL);

	mgr.mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
}
