#pragma once
#include "BodyPart.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"

class Leg : public BodyPart
{
public:
	Leg();
	~Leg();

	int speedMin = 200;
	int speedMax = 300;
	int randSpeed;

	virtual void Stats() override;
	virtual void Ability();
	
};

