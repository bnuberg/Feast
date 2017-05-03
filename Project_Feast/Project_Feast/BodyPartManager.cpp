#include "BodyPartManager.h"
#include "GameManager.h"


BodyPartManager::BodyPartManager()
{
}


BodyPartManager::~BodyPartManager()
{
}
// TODO UPDATE FUNCTION
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

void BodyPartManager::IterateBodyParts(Ogre::Vector3 center, float pickupDistance)
{
	// Create a reference to the game manager
	GameManager& mgr = GameManager::getSingleton();
	
	for (std::list<BodyPart>::iterator b = bodyPartsList.begin(); b != bodyPartsList.end(); ++b)
	{

		Ogre::Vector3 distanceVector = center - b->bodyPartNode->getPosition();
		float distance = distanceVector.length();

		if (distance < pickupDistance)
		{
			isPickupAble = true;
		}
		// TODO closest bodypart
		
	}
}
