#pragma once
#include <OgreEntity.h>

class IAbilityAttack
{
public:
	virtual void Attack(Ogre::Vector3 target) = 0;
};

