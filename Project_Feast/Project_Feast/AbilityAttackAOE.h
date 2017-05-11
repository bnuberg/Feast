#pragma once
#include "AbilityAttack.h"
class AbilityAttackAOE :
	public AbilityAttack
{
public:
	AbilityAttackAOE();
	~AbilityAttackAOE();

	void Attack(Ogre::Vector3 target) override;
private:
	float attackRadius = 200;
};

