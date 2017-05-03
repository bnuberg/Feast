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
	
	// TODO Change spawn rate of bodyparts to 10-20%
	if (rand() % 2 == 0)
		SpawnArm(position);
	else
		SpawnLeg(position);
}

BodyPart BodyPartManager::ClosestBodyPart(Ogre::Vector3 center)
{
	BodyPart closestbodypart;
	float closest = 999999;
	for (std::vector<BodyPart>::iterator b = bodyPartsList.begin(); b != bodyPartsList.end(); ++b)
	{
		if (b->isPickupAble == true)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(b->isPickupAble));
			Ogre::Vector3 distanceVector = center - b->bodyPartNode->getPosition();
			/*Ogre::LogManager::getSingletonPtr()->logMessage(b->tag);*/
			float distance = distanceVector.length();
			
			if (distance < closest)
			{
				closestbodypart = *b;
				/*Ogre::LogManager::getSingletonPtr()->logMessage(closestbodypart.tag);*/
				closest = distance;
			}
		}
	}
	return closestbodypart;
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
	
	for (std::vector<BodyPart>::iterator b = bodyPartsList.begin(); b != bodyPartsList.end(); ++b)
	{
		/*Ogre::LogManager::getSingletonPtr()->logMessage(b->tag);*/
		Ogre::Vector3 distanceVector = center - b->bodyPartNode->getPosition();
		
		float distance = distanceVector.length();
		/*Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(b->isPickupAble));*/
		if (distance < pickupDistance)
		{
			b->isPickupAble = true;
			
		}
		else
		{
			b->isPickupAble = false;
		}
		// TODO closest bodypart
		if (b->pickedUp == true)
		{
			// TODO delete bodypart
		}
		
	}
}
