#pragma once
#include "BodyPart.h"
#include "Arm.h"
#include "Rarity.h"


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
	Arm Generate(int level);
	AttackTypeEnum attackTypeEnum;
	MovementTypeEnum movementTypeEnum;
	Arm arm;
	int type;
	Rarity rarity;
private:
	int level = 0;
};

