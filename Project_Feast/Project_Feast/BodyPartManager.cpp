#include "BodyPartManager.h"


BodyPartManager::BodyPartManager()
{
}


BodyPartManager::~BodyPartManager()
{
}

void BodyPartManager::Spawn(Ogre::Vector3 position)
{
	if (rand() % 2 == 0)
		SpawnArm(position);
	else
		SpawnLeg(position);
}

void BodyPartManager::SpawnArm(Ogre::Vector3 position)
{
	Arm arm;
	arm.Spawn(position);
	bodyPartsList.push_back(arm);
}

void BodyPartManager::SpawnLeg(Ogre::Vector3 position)
{
	Leg leg;
	leg.Spawn(position);
	bodyPartsList.push_back(leg);
}
