#pragma once
#include "IAbilityAttack.h"
class AbilityAttackAOE :
	public IAbilityAttack
{
public:
	AbilityAttackAOE();
	~AbilityAttackAOE();

	void Attack(Ogre::Vector3 target, int damage, int modifier) override;
	void AttackEnemy(Ogre::Vector3 target, int damage) override;
private:
	float attackRadius = 200;
};

