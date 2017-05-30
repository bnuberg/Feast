#include "GenerateBodyPart.h"
#include "AbilityAttackAOE.h"
#include "AbilityMovementMelee.h"
#include "AbilityMovementRange.h"


GenerateBodyPart::GenerateBodyPart()
{

}


GenerateBodyPart::~GenerateBodyPart()
{

}

void GenerateBodyPart::RandomStats()
{
	arm.randDamage = rand() % (damageMax - damageMin + 1) + damageMin;
	arm.randAttackSpeed = rand() % (attackSpeedMax - attackSpeedMin + 1) + attackSpeedMin;
}

void GenerateBodyPart::PickAttackTemplate()
{
	attackTypeEnum = static_cast<AttackTypeEnum>(rand() % TotalAttackTypes);
	switch (attackTypeEnum){
	case GroundSmash:
		{
			arm.attackType = new AbilityAttackAOE;
			
		}
	}
	
}

void GenerateBodyPart::PickMovementTemplates()
{
	movementTypeEnum = static_cast<MovementTypeEnum>(rand() % TotalMovementTypes);

	switch(movementTypeEnum){
	case TravelToPoint:
		{
			if (rand() % 2 == 0)
			{
				arm.moveType = new AbilityMovementMelee;
				arm.type = 0;
				arm.mesh = "cube.mesh";
				/*Ogre::LogManager::getSingletonPtr()->logMessage("Pepe");*/
			}
			else
			{
				arm.moveType = new AbilityMovementRange;
				arm.type = 1;
				arm.mesh = "sphere.mesh";
			}
			/*Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(arm.type));*/
		}
	}
}

void GenerateBodyPart::Combine()
{
	RandomStats();
	PickAttackTemplate();
	PickMovementTemplates();
	
}

Arm GenerateBodyPart::Generate()
{
	
	Combine();
	return arm;
}
