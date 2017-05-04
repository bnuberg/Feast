#pragma once

#include "Leg.h"
#include "Arm.h"

enum
{
	LeftArm, RightArm, Legs
};
class Equipment
{
public:
	Equipment();
	~Equipment();

	void EquipArm();
	void EquipLeg();
	void Discard();
	void setPlayerStats();
	int damage;
	int attackSpeed;
	int speed;
	bool hasAArm = false;
	bool hasALeg = false;
	
	Leg leg;
	Arm arm;
	// TODO add equipment slots

	// TODO equip bodyparts 

	// TODO return slots to player
};

