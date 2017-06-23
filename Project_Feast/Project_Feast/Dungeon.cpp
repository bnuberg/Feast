#include "Dungeon.h"
#include "GameManager.h"
#include "EnemyManager.h"

/** Constructor.\n
*/
Dungeon::Dungeon(Ogre::SceneManager* sceneManager)
{
	LoadScene(sceneManager);
}

/** Deconstructor.\n
*/
Dungeon::~Dungeon(){}

/** Returns the player spawn point.\n
	@return Vector3 player spawn point
*/
Ogre::Vector3 Dungeon::GetPlayerSpawnPoint() const
{
	return playerSpawnPoint;
}

/** Returns the radius from what point on entities fall.\n
	@return Real length from center
*/
Ogre::Real Dungeon::GetFallRange() const
{ 
	return fallRange; 
}

/** Load Dungeon.mesh, lava mesh, wall mesh, skybox and lights.\n
*/
void Dungeon::LoadScene(Ogre::SceneManager* sceneManager) const
{
	GameManager& mgr = GameManager::getSingleton();
	Ogre::Vector3 startingPosition = Ogre::Vector3(0, 0, 0);

	/*Platform + base lava*/
	Ogre::Entity* dungeonEntity = mgr.mSceneMgr->createEntity("Dungeonmesh", meshName);
	Ogre::SceneNode* dungeonNode = sceneManager->getRootSceneNode()->createChildSceneNode("dungeon", startingPosition);
	dungeonNode->attachObject(dungeonEntity);
	dungeonNode->setScale(dungeonScale);
	dungeonNode->translate(dungeonSpawnPoint, Ogre::Node::TS_LOCAL);

	/*Blocky wall*/
	Ogre::Entity* dungeonBoxEntity = mgr.mSceneMgr->createEntity("DungeonBoxmesh", boxMeshName);
	Ogre::SceneNode* dungeonBoxNode = sceneManager->getRootSceneNode()->createChildSceneNode("dungeonBox", startingPosition);
	dungeonBoxNode->attachObject(dungeonBoxEntity);
	dungeonBoxNode->setScale(4 * dungeonScale);
	dungeonBoxNode->translate(dungeonSpawnPoint, Ogre::Node::TS_LOCAL);

	/*Lava*/
	Ogre::Entity* dungeonLavaEntity = mgr.mSceneMgr->createEntity("DungeonLavamesh", lavaMeshName);
	Ogre::SceneNode* dungeonLavaNode = sceneManager->getRootSceneNode()->createChildSceneNode("dungeonLava", startingPosition);
	dungeonLavaNode->attachObject(dungeonLavaEntity);
	dungeonLavaNode->setScale(8 * dungeonScale);
	dungeonLavaNode->translate(1.5 * dungeonSpawnPoint, Ogre::Node::TS_LOCAL);

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
	light3->setDirection(-1, -1, -0.5);

	/*Skybox*/
	mgr.mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");
}
