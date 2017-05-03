#pragma once
#include "Player.h"
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
	bool hasAArm = false;
	bool hasALeg = false;
	Player player;
	Leg leg;
	Arm arm;
	// TODO add equipment slots

	// TODO equip bodyparts 

	// TODO return slots to player
};

