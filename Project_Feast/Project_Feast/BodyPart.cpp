#include "BodyPart.h"
#include "GameManager.h"


BodyPart::BodyPart()
{

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
	Ogre::Entity *bodyPartEntity = mgr.mSceneMgr->createEntity(mesh_);

	// Add the node to the scene
	body_part_node_ = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	body_part_node_->attachObject(bodyPartEntity);
	body_part_node_->setScale(0.2, 0.2, 0.2);

}


