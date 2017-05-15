#pragma once

#include "Arm.h"

class EnemyEquipment
{

public:
	EnemyEquipment();
	~EnemyEquipment();

	void EnemyEquipArm(Ogre::SceneNode* enemyNode);
	void SetEnemyArmStats(int dmg, int as);
	void AssignRandomBodypart();

	int damage;
	int attackspeed;
	bool once = false;
	Ogre::String enemyBodypart;

	Arm arm;
	Ogre::SceneNode* erightarmNode;
	Ogre::Entity* eArmEntity;


};