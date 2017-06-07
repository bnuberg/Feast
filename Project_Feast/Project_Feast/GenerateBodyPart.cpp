#include "GenerateBodyPart.h"
#include "AbilityAttackAOE.h"
#include "GameManager.h"

GenerateBodyPart::GenerateBodyPart()
{

}

GenerateBodyPart::~GenerateBodyPart()
{

}

void GenerateBodyPart::SetRarity()
{
	rarity.RarityPicker(level);
	
	arm.randDamage = rarity.GetDamageValue();
	arm.randSpeed = rarity.GetSpeedValue();
	arm.r = rarity.R();
	arm.g = rarity.G();
	arm.b = rarity.B();
}

void GenerateBodyPart::SetAttackTemplate()
{
	attackTypeEnum = static_cast<AttackTypeEnum>(rand() % TotalAttackTypes);
	switch (attackTypeEnum)
	{
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
				arm.mesh = "handGroundPound.mesh";
			}
			else
			{
				arm.type = 1;
				arm.mesh = "handRocket.mesh";
			}
		}
	}
}

void GenerateBodyPart::SetModifier()
{
	arm.randModifier = matth.random(1, 5);
}

void GenerateBodyPart::Combine()
{
	SetRarity();
	SetModifier();
	SetAttackTemplate();
	SetMovementTemplates();
}

Arm GenerateBodyPart::Generate(int lvl)
{
	level = lvl;
	Combine();
	return arm;
}
