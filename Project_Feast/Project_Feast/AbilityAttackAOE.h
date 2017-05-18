#pragma once
#include "IAbilityAttack.h"
class AbilityAttackAOE :
	public IAbilityAttack
{
public:
	AbilityAttackAOE();
	~AbilityAttackAOE();

	void Attack(Ogre::Vector3 target) override;
private:
	float attackRadius = 200;
};

