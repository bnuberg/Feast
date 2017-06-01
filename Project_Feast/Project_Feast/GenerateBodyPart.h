#pragma once
#include "BodyPart.h"
#include "Arm.h"
#include "Rarity.h"
#include "AbilityModifier.h"
#include "Matth.h"
enum AttackTypeEnum
{
	GroundSmash,
	TotalAttackTypes
};
enum MovementTypeEnum
{
	TravelToPoint,
	TotalMovementTypes
};
class GenerateBodyPart
{
public:
	GenerateBodyPart();
	~GenerateBodyPart();
	void SetRarity();
	void SetAttackTemplate();
	void SetMovementTemplates();
	void SetModifier();
	void Combine();
	Arm Generate();
	AttackTypeEnum attackTypeEnum;
	MovementTypeEnum movementTypeEnum;
	Arm arm;
	AbilityModifier abilityModifier;
	int type;
	Rarity rarity;
	
private:
	Matth matth;

};

