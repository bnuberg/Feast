#include "BodyPart.h"
#include "GameManager.h"
#include "AbilityAttackAOE.h"


BodyPart::BodyPart()
{
}


BodyPart::~BodyPart()
{

}

void BodyPart::Spawn(Ogre::Vector3 position, Ogre::String bodypart)
{
	GameManager& mgr = GameManager::GetSingleton();

	//Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("Enemy")->getPosition();
	Ogre::Vector3 target = Ogre::Vector3(0, 0, 0);

	// Create a body part entity with the right mesh
	if (bodypart == "groundSmash")
	{
		type = 0;
	}
	else
	{
		type = 1;
	}
	bodyPartEntity = mgr.mSceneMgr->createEntity(mesh);

	// Add the node to the scene
	bodyPartNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	bodyPartNode->attachObject(bodyPartEntity);
	bodyPartNode->setScale(0.2, 0.2, 0.2);
	
}

void BodyPart::Drop(Ogre::Vector3 position)
{
	GameManager& mgr = GameManager::GetSingleton();

	Ogre::Entity *bodyPartEntity = mgr.mSceneMgr->createEntity(mesh);

	// Add the node to the scene
	bodyPartNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	bodyPartNode->attachObject(bodyPartEntity);
	bodyPartNode->setScale(0.2, 0.2, 0.2);

}

void BodyPart::AbilityTarget(Ogre::Vector3 abilityTarget)
{
	moveType->SetTarget(abilityTarget);
}

void BodyPart::AbilityGlobalTarget(Ogre::Vector3 target)
{
	globalTarget = target;
	moveType->SetGlobalTarget(target);
}

Ogre::Vector3 BodyPart::GetAbilityTarget()
{
	return moveType->GetTarget();
}

Ogre::Vector3 BodyPart::GetAbilityGlobalTarget()
{
	return moveType->GetGlobalTarget();
}

bool BodyPart::AbilityUpdate(Ogre::SceneNode* node, const Ogre::FrameEvent& evt)
{
	return moveType->Move(node, evt);
}

bool BodyPart::AbilityUpdate(Ogre::SceneNode* node, const Ogre::FrameEvent& evt, Ogre::String string)
{
	if (string == "global")
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Global attack");
		return moveType->MoveGlobal(node, evt);
	}
	else
		return moveType->Move(node, evt);
}

void BodyPart::AbilityDamage()
{
	if (equippedByEnemy)
	{
		attackType->AttackEnemy(globalTarget, randDamage);
	}
	else
	{
		attackType->Attack(globalTarget, randDamage);
	}
}