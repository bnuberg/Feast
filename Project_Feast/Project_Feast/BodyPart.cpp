#include "BodyPart.h"
#include "GameManager.h"
#include "AbilityAttackAOE.h"


BodyPart::BodyPart()
{
	if (rand() % 2 == 0)
		type = 0;
	else
		type = 1;

	//attackType = new AbilityAttackAOE();
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

void BodyPart::AbilityGlobalTarget(Ogre::Vector3 target)
{
	globalTarget = target;
	moveType.SetGlobalTarget(target);
}

Ogre::Vector3 BodyPart::GetAbilityTarget()
{
	return moveType.GetTarget();
}

Ogre::Vector3 BodyPart::GetAbilityGlobalTarget()
{
	return moveType.GetGlobalTarget();
}

bool BodyPart::AbilityUpdate(Ogre::SceneNode* node, const Ogre::FrameEvent& evt)
{
	return moveType.Move(node, evt);
}

bool BodyPart::AbilityUpdate(Ogre::SceneNode* node, const Ogre::FrameEvent& evt, Ogre::String string)
{
	if (string == "global")
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Global attack");
		return moveType.MoveGlobal(node, evt);
	}
	else
		return moveType.Move(node, evt);
}

void BodyPart::AbilityDamage()
{
	attackType = new AbilityAttackAOE;
	attackType->Attack(globalTarget);
}