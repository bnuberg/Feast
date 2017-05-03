#include "Equipment.h"


Equipment::Equipment()
{
	setPlayerStats();
}


Equipment::~Equipment()
{
}

void Equipment::EquipArm()
{
	if (hasAArm == false)
	{
		
		hasAArm = true;
		// TODO set player arm
	}
	else if (hasAArm)
	{
		// TODO discard arm if player wants to
	}
}

void Equipment::EquipLeg()
{
	if (hasALeg == false)
	{
		
		hasALeg = true;
	}
	else if (hasALeg)
	{
		// TODO discard legs if the player wants to
	}
	// TODO set player leg
}

void Equipment::Discard()
{
	// TODO discard bodyparts
}

void Equipment::setPlayerStats()
{
	damage = arm.randDamage;
	attackSpeed = arm.randAttackSpeed;
	speed = leg.randSpeed;
}



