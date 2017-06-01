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

void EnemyEquipment::EnemyEquipArm(Ogre::SceneNode* enemyNode)
{
	GameManager& mgr = GameManager::GetSingleton();

	AssignRandomBodypart();

	//TODO: tell enemy which arm they have
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

void EnemyEquipment::AssignRandomBodypart() 
{
	/*Placeholder for procedual generation
	Randomly makes number and assigns number to bodypart
	*/
	arm = generateBodyPart.Generate();
	attackspeed = arm.randAttackSpeed;
	damage = arm.randDamage;

	/*Ogre::LogManager::getSingletonPtr()->logMessage("enemy attackspeed" +std::to_string(arm.randAttackSpeed));
	if (arm.type == 0)
	{
		arm.mesh = "cube.mesh";
		attackspeed = arm.randAttackSpeed;
		damage = arm.randDamage;
		enemyBodypart = "groundSmash";
	}

	else
	{
		arm.mesh = "sphere.mesh";
		attackspeed = arm.randAttackSpeed;
		damage = arm.randDamage;
		enemyBodypart = "rangedAttack";
	}
*/




	/*Ogre::String bodypartName;

	float bodypartToSpawn = Ogre::Math::RangeRandom(0, 2);

	if (bodypartToSpawn < 1)// set bodypart to groundstomp
	{
		//bodypartName = "sphere.mesh";
		arm.mesh = "cube.mesh";
		enemyBodypart = "groundSmash";
	}

	else//set bodypart to rangeattack
	{
		//bodypartName = "cube.mesh";
		arm.mesh = "sphere.mesh";
		enemyBodypart = "rangedAttack";
	}*/

}

