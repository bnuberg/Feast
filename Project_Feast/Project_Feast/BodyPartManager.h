#pragma once
#include "OgreEntity.h"
#include "BodyPart.h"
#include "Arm.h"
#include "Leg.h"

class BodyPartManager
{
public:
	BodyPartManager();
	~BodyPartManager();

	void Spawn(Ogre::Vector3 position);

private:
	std::list<BodyPart> bodyPartsList;		// List containing all bodypart objects

	void SpawnArm(Ogre::Vector3 position);
	void SpawnLeg(Ogre::Vector3 position);
};

