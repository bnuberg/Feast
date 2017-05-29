#include "GenerateBodyPart.h"
#include "AbilityAttackAOE.h"



GenerateBodyPart::GenerateBodyPart()
{

}


GenerateBodyPart::~GenerateBodyPart()
{

}

void GenerateBodyPart::SetRarity()
{
	rarity.RarityPicker();
	arm.randDamage = rarity.GetDamageValue();
	arm.randSpeed = rarity.GetSpeedValue();
}

void GenerateBodyPart::SetAttackTemplate()
{
	attackTypeEnum = static_cast<AttackTypeEnum>(rand() % TotalAttackTypes);
	switch (attackTypeEnum){
	case GroundSmash:
		{
			arm.attackType = new AbilityAttackAOE;
			
		}
	}
	
}

void GenerateBodyPart::SetMovementTemplates()
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

void GenerateBodyPart::SetModifier()
{
}

void GenerateBodyPart::Combine()
{
	SetRarity();
	SetAttackTemplate();
	SetMovementTemplates();
	
}

Arm GenerateBodyPart::Generate()
{
	
	Combine();
	return arm;
}
