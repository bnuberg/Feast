#include "GenerateBodyPart.h"
#include "AbilityAttackAOE.h"
#include "GameManager.h"
#include <OgreLogManager.h>


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
	//arm.randModifier = rand() % 3;
	arm.randModifier = matth.random(1, 3);

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
			
			arm.moveType = new AbilityMovement;
			if (rand() % 2 == 0)
			{
				arm.type = 0;
				arm.mesh = "cube.mesh";
				/*Ogre::LogManager::getSingletonPtr()->logMessage("Pepe");*/
			}
			else
			{
				arm.type = 1;
				arm.mesh = "sphere.mesh";
			}
			/*Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(arm.type));*/
		}
	}
}

void GenerateBodyPart::GenerateModifier()
{
	//ToDO: add different modifiers on spawn
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
