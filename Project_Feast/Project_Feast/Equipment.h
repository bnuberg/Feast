#pragma once
#include "Player.h"

enum
{
	LeftArm, RightArm, LeftLeg, RightLeg
};
class Equipment
{
public:
	Equipment();
	~Equipment();

	void Equip();
	void Discard();
	Player player;
	// TODO add equipment slots

	// TODO equip bodyparts 

	// TODO return slots to player
};

