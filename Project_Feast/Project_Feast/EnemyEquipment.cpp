#include "EnemyEquipment.h"
#include <OgreLogManager.h>

EnemyEquipment::EnemyEquipment()
{

}

EnemyEquipment::~EnemyEquipment()
{

}

void EnemyEquipment::EnemyEquipArm()
{
	//TODO: tell enemy which arm they have
}

void EnemyEquipment::SetEnemyArmStats(int dmg, int as)
{
	//TODO: change attack stats of enemy to the arms dmg
}

Ogre::String EnemyEquipment::AssignRandomBodypart() 
{
	/*Placeholder for procedual generation
	Randomly makes number and assigns number to bodypart
	*/
	Ogre::String bodypartName;

	float bodypartToSpawn = Ogre::Math::RangeRandom(0, 2);

	Ogre::LogManager::getSingletonPtr()->logMessage("randomNumber" + std::to_string(bodypartToSpawn));

	if (bodypartToSpawn < 1)// set bodypart to groundstomp
	{
		bodypartName = "sphere.mesh";
	}

	else//set bodypart to rangeattack
	{
		bodypartName = "cube.mesh";
	}

	return bodypartName;
}

