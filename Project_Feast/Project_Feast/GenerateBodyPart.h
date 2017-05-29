#pragma once
#include "BodyPart.h"
#include "Arm.h"
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
	void RandomStats();
	void PickAttackTemplate();
	void PickMovementTemplates();
	void GenerateModifier();
	void Combine();
	
	Arm Generate();
	AttackTypeEnum attackTypeEnum;
	MovementTypeEnum movementTypeEnum;
	Arm arm;

	int attackSpeedMax = 5;
	int attackSpeedMin = 1;
	int damageMax = 10;
	int damageMin = 1;
	int type;
	
};

