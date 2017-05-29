#include "Equipment.h"


Equipment::Equipment()
{
	for (int i = 0; i < 100; i++){
		arm = generateArm.Generate();
	}
	
	
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
	
}

void Equipment::EquipLeg()
{
	if (hasALeg == false)
	{
		
		hasALeg = true;
	}
	
	// TODO set player leg
}

void Equipment::DiscardArm(int dmg, int as)
{
	if (hasAArm){
		damage -= dmg;
		attackSpeed -= as;
		hasAArm = false;
		once = false;
	}
}

void Equipment::DiscardLeg(int spd)
{
	if (hasALeg){
		speed -= spd;
		hasALeg = false;
		once2 = false;
	}
	// TODO discard bodyparts
}

void Equipment::setPlayerArmStats(int dmg, int as)
{
	
	if (once == false){
		damage += dmg;
		attackSpeed += as;
		once = true;
	}
}
void Equipment::setPlayerLegStats(int spd)
{
	if (once2 == false){
		speed += spd;
		once2 = true;
	}

}



