#pragma once
#include "BodyPart.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"

class Leg : public BodyPart
{
public:
	Leg();
	~Leg();

	int speedMin = 150;
	int speedMax = 250;
	

	virtual void Stats() override;
	virtual void Ability();
	
};

