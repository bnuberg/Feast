#include "EntityTest.h"
#include "GameManager.h"
#include <OgreEntity.h>


EntityTest::EntityTest()
{
}


EntityTest::~EntityTest()
{
}

void EntityTest::DoStuff()
{
	GameManager& mgr = GameManager::getSingleton();
	GameManager* pMgr = GameManager::getSingletonPtr();

	Ogre::Entity* test = mgr.mSceneMgr->createEntity("Body", "ninja.mesh");
	Ogre::SceneNode* testNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode();
	testNode->attachObject(test);
}
