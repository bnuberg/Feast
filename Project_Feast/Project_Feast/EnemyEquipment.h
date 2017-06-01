#pragma once

#include "Arm.h"
#include "GenerateBodyPart.h"

class EnemyEquipment
{

public:
	EnemyEquipment();
	~EnemyEquipment();

	void EnemyEquipArm(Ogre::SceneNode* enemyNode, int enemyID);
	void SetEnemyArmStats(int dmg, int as);
	void AssignRandomBodypart(int enemyID);

	int damage;
	int attackspeed;
	int modifier;
	bool once = false;
	Ogre::String enemyBodypart;

	Arm arm;
	Ogre::SceneNode* erightarmNode;
	Ogre::Entity* eArmEntity;
	GenerateBodyPart generateBodyPart;
	Ogre::ParticleSystem* ModifierParticle;

};
