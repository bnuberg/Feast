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
	void IterateBodyParts(Ogre::Vector3 distance, float pickupDistance);
	std::vector<BodyPart> bodyPartsList;		// List containing all bodypart objects
	BodyPart ClosestBodyPart(Ogre::Vector3 center);
private:
	

	void SpawnArm(Ogre::Vector3 position);
	void SpawnLeg(Ogre::Vector3 position);
	

};

