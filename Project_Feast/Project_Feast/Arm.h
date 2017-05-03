#pragma once
#include "BodyPart.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"

class Arm: public BodyPart
{
public:
	Arm();
	~Arm();

	int attackSpeedMax = 5;
	int attackSpeedMin = 1;
	int damageMax = 20;
	int damageMin = 1;
	int randDamage;
	int randAttackSpeed;

	virtual void Stats() override;
    virtual void Ability();
};

