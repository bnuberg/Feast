#include "Equipment.h"


Equipment::Equipment()
{
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
		player.move = leg.randSpeed;
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

}
