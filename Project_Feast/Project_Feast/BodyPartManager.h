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
	
	void Spawn(Ogre::Vector3 position); // Body part spawn method
	void IterateBodyParts(Ogre::Vector3 distance, float pickupDistance); // Method for iterating through the body parts
	std::vector<BodyPart> body_parts_list_;		// List containing all bodypart objects
	BodyPart ClosestBodyPart(Ogre::Vector3 center); // Body part instance
private:
	

	void SpawnArm(Ogre::Vector3 position); // Spawn method for arms
	void SpawnLeg(Ogre::Vector3 position); // Spawn method for legs
	

};

