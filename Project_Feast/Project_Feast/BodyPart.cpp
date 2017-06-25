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
	bodyPartNode->setScale(5, 5, 5);
	
}

void BodyPart::Drop(Ogre::Vector3 position)
{
	GameManager& mgr = GameManager::GetSingleton();

	Ogre::Entity *bodyPartEntity = mgr.mSceneMgr->createEntity(mesh);

	// Add the node to the scene
	bodyPartNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	bodyPartNode->attachObject(bodyPartEntity);
	bodyPartNode->setScale(5, 5, 5);
	
	common = Ogre::MaterialManager::getSingleton().create("Common", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	commonPass = common->getTechnique(0)->getPass(0);
	commonPass->setAmbient(r, g, b);
	commonPass->setDiffuse(r, g, b, 1);
	commonPass->setEmissive(r, g, b);
	bodyPartEntity->setMaterial(common);

	Ogre::LogManager::getSingletonPtr()->logMessage("Damage: " + std::to_string(randDamage));

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
	return moveType->Move(node, evt, equippedByEnemy);
}

bool BodyPart::AbilityUpdate(Ogre::SceneNode* node, const Ogre::FrameEvent& evt, Ogre::String string)
{
	if (string == "global")
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Global attack");
		return moveType->MoveGlobal(node, evt);
	}
	else
		return moveType->Move(node, evt, equippedByEnemy);
}

void BodyPart::AbilityDamage()
{
	if (equippedByEnemy)
	{
		attackType->AttackEnemy(globalTarget, randDamage, enemyID);

	}
	else
	{
		attackType->Attack(globalTarget, randDamage);
		Ogre::LogManager::getSingletonPtr()->logMessage("AAAAAAA: " + std::to_string(randDamage));
	}
}