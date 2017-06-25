#include "EnemyEquipment.h"
#include <OgreLogManager.h>
#include <OgreEntity.h>
#include "GameManager.h"
#include "BodyPart.h"



EnemyEquipment::EnemyEquipment()
{
	
}

EnemyEquipment::~EnemyEquipment()
{

}

void EnemyEquipment::EnemyEquipArm(Ogre::SceneNode* enemyNode, int enemyID, int level)
{
	GameManager& mgr = GameManager::GetSingleton();

	AssignRandomBodypart(enemyID, level);

	//TODO: tell enemy which arm they have
	if (ModifierParticle != NULL)
	{
		enemyNode->attachObject(ModifierParticle);
	}

	eArmEntity = mgr.mSceneMgr->createEntity(arm.mesh);
	enemyNode->attachObject(eArmEntity);
	common = Ogre::MaterialManager::getSingleton().create("Common", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	commonPass = common->getTechnique(0)->getPass(0);
	commonPass->setAmbient(arm.r, arm.g, arm.b);
	commonPass->setDiffuse(arm.r, arm.g, arm.b, 1);
	commonPass->setEmissive(arm.r, arm.g, arm.b);
	eArmEntity->setMaterial(common);
}

void EnemyEquipment::SetEnemyArmStats(int dmg, int as)
{
	//TODO: change attack stats of enemy to the arms dmg
}

void EnemyEquipment::AssignRandomBodypart(int enemyID, int level) 
{
	GameManager& mgr = GameManager::GetSingleton();
	/*Placeholder for procedual generation
	Randomly makes number and assigns number to bodypart
	*/
	arm = generateBodyPart.Generate(level);
	attackspeed = arm.randAttackSpeed;
	damage = arm.randDamage;
	modifier = arm.randModifier;

	switch (modifier)
	{
	case 0:
		break;
	case 1:
		ModifierParticle = mgr.mSceneMgr->createParticleSystem("bleed" + Ogre::StringConverter::toString(enemyID) + "1", "BleedParticle");
		break;
	case 2:
		ModifierParticle = mgr.mSceneMgr->createParticleSystem("slow" + Ogre::StringConverter::toString(enemyID) + "1", "SlowParticle");
		break;
	case 3:
		break;
	default:
		break;
	}

}

