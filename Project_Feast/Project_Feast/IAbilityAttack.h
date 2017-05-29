#pragma once
#include <OgreEntity.h>

class IAbilityAttack
{
public:
	virtual void Attack(Ogre::Vector3 target, int damage) = 0;
	virtual void AttackEnemy(Ogre::Vector3 target, int damage) = 0;
};
