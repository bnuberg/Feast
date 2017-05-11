#include "BodyPart.h"
#include "GameManager.h"
#include "AbilityAttackAOE.h"


BodyPart::BodyPart()
{
	if (rand() % 2 == 0)
		type = 0;
	else
		type = 1;

	attackType = new AbilityAttackAOE::AbilityAttack();
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
	bodyPartNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	bodyPartNode->attachObject(bodyPartEntity);
	bodyPartNode->setScale(0.2, 0.2, 0.2);

	//Ogre::MaterialPtr bodyPartMat = bodyPartEntity->getSubEntity(0)->getMaterial();
	//bodyPartMat->getTechnique(0)->getPass(0)->setAmbient(0, 1, 0);
	//bodyPartMat->getTechnique(0)->getPass(0)->setDiffuse(0, 1, 0, 0);
	//bodyPartEntity->setMaterialName(bodyPartMat->getName());
}


void BodyPart::Stats()
{
}

void BodyPart::AbilityTarget(Ogre::Vector3 abilityTarget)
{
	moveType.SetTarget(abilityTarget);
}

Ogre::Vector3 BodyPart::GetAbilityTarget()
{
	return moveType.GetTarget();
}

bool BodyPart::AbilityUpdate(Ogre::SceneNode* node, const Ogre::FrameEvent& evt)
{
	return moveType.Move(node, evt);
}

void BodyPart::AbilityDamage(Ogre::Vector3 target)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("DO YOU GET HERE");
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(target.x));
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(target.y));
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(target.z));
	attackType = new AbilityAttackAOE::AbilityAttack();
	attackType->Attack(target);
}