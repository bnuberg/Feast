#pragma once
#include "BodyPart.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"

class Arm: public BodyPart
{
public:
	Arm();
	~Arm();

	void Spawn(Ogre::Vector3 position);
};

