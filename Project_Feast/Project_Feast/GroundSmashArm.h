#pragma once
#include "Arm.h"

class GroundSmashArm: public Arm
{
public:
	GroundSmashArm();
	~GroundSmashArm();

	virtual void Ability() override;
};

