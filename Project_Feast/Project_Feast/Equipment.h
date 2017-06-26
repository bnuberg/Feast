#pragma once

#include "Leg.h"
#include "Arm.h"
#include "GenerateBodyPart.h"

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
	void DiscardArm(int dmg, int as);
	void DiscardLeg(int spd);
	void setPlayerArmStats(int dmg, int as, int mod);
	void setPlayerLegStats(int spd);
	int damage;
	int attackSpeed;
	Ogre::Real speed = 100;
	bool hasAArm = false;
	bool hasALeg = false;
	bool once = false;
	bool once2 = false;
	GenerateBodyPart generateArm;
	Leg leg;
	Arm arm;
	// TODO add equipment slots

	// TODO equip bodyparts 

	// TODO return slots to player
};

