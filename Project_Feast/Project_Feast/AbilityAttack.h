#pragma once
#include <OgreEntity.h>

class AbilityAttack
{
public:
	AbilityAttack();
	~AbilityAttack();

	void virtual Attack(Ogre::Vector3 target);
};

