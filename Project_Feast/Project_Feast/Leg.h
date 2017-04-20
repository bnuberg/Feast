#pragma once
#include "BodyPart.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"

class Leg : public BodyPart
{
public:
	Leg();
	~Leg();

	void Spawn(Ogre::Vector3 position);
};

