#include "BodyPart.h"
#include "GameManager.h"
#include "OgreEntity.h"


BodyPart::BodyPart()
{

}


BodyPart::~BodyPart()
{

}

void BodyPart::Spawn()
{
	GameManager& mgr = GameManager::GetSingleton();

	//Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("Enemy")->getPosition();
	Ogre::Vector3 target = Ogre::Vector3(0, 0, 0);

	// Create a body part entity with the right mesh
	Ogre::Entity* bodyPartEntity = mgr.mSceneMgr->createEntity("ninja.mesh");

	// Add the node to the scene
	Ogre::SceneNode* bodyPartNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("BodyPart", target);
	bodyPartNode->attachObject(bodyPartEntity);
}
