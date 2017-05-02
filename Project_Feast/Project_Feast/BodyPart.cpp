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
	Ogre::Entity *bodyPartEntity = mgr.mSceneMgr->createEntity(mesh);

	// Add the node to the scene
	Ogre::SceneNode* bodyPartNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	bodyPartNode->attachObject(bodyPartEntity);
	bodyPartNode->setScale(0.2, 0.2, 0.2);

	Ogre::MaterialPtr bodyPartMat = bodyPartEntity->getSubEntity(0)->getMaterial();
	bodyPartMat->getTechnique(0)->getPass(0)->setAmbient(0, 1, 0);
	bodyPartMat->getTechnique(0)->getPass(0)->setDiffuse(0, 1, 0, 0);
	bodyPartEntity->setMaterialName(bodyPartMat->getName());
}


void BodyPart::Stats()
{
}
