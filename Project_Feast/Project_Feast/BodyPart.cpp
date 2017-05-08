#include "BodyPart.h"
#include "GameManager.h"


BodyPart::BodyPart()
{
	if (rand() % 2 == 0)
		type = 0;
	else
		type = 1;

}


BodyPart::~BodyPart()
{

}

void BodyPart::Spawn(Ogre::Vector3 position)
{
	GameManager& mgr = GameManager::GetSingleton();

	//Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("Enemy")->getPosition();
	Ogre::Vector3 target = Ogre::Vector3(0, 0, 0);

	// Create a body part entity with the right mesh
	Ogre::Entity *bodypartentity = mgr.mSceneMgr->createEntity(mesh);

	// Add the node to the scene
	bodyPartNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	bodyPartNode->attachObject(bodypartentity);
	bodyPartNode->setScale(0.2, 0.2, 0.2);

	
}


void BodyPart::Stats()
{
}
