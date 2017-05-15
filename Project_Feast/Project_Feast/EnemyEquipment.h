#pragma once

#include "Arm.h"

class EnemyEquipment
{

public:
	EnemyEquipment();
	~EnemyEquipment();

	void EnemyEquipArm();
	void SetEnemyArmStats(int dmg, int as);
	Ogre::String AssignRandomBodypart();

	int damage;
	int attackspeed;
	bool once = false;

	Arm arm;

};