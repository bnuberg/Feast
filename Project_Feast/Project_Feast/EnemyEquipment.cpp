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

void EnemyEquipment::EnemyEquipArm(Ogre::SceneNode* enemyNode, int enemyID)
{
	GameManager& mgr = GameManager::GetSingleton();

	AssignRandomBodypart(enemyID);

	//TODO: tell enemy which arm they have
	if (ModifierParticle != NULL)
	{
		enemyNode->attachObject(ModifierParticle);
	}

	eArmEntity = mgr.mSceneMgr->createEntity(arm.mesh);
	enemyNode->attachObject(eArmEntity);
}

void EnemyEquipment::SetEnemyArmStats(int dmg, int as)
{
	//TODO: change attack stats of enemy to the arms dmg
}

void EnemyEquipment::AssignRandomBodypart(int enemyID) 
{
	GameManager& mgr = GameManager::GetSingleton();
	/*Placeholder for procedual generation
	Randomly makes number and assigns number to bodypart
	*/
	arm = generateBodyPart.Generate();
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
	default:
		break;
	}

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

