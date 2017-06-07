#include "BodyPartManager.h"
#include "GameManager.h"
#include <random>


BodyPartManager::BodyPartManager()
{
}


BodyPartManager::~BodyPartManager()
{
}
// TODO UPDATE FUNCTION
void BodyPartManager::Spawn(Ogre::Vector3 position, Ogre::String bodypart)
{

	int i = Random();
	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(i));
	if ( i > 8)
	{
		/*if (rand() % 2 == 0)*/
			SpawnArm(position, bodypart);
		/*else
			SpawnLeg(position);*/
	}
	// TODO Change spawn rate of bodyparts to 10-20%
	
}

int BodyPartManager::Random()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 25);
	
	return dist(mt);
}
/**	This function checks for the closest bodypart around a certain point
@param The center point/position around which is checked which body parts are close
*/
BodyPart BodyPartManager::ClosestBodyPart(Ogre::Vector3 center)
{
	BodyPart closestbodypart;
	for (std::vector<BodyPart>::iterator b = bodyPartsList.begin(); b != bodyPartsList.end(); ++b)
	{
		if (b->isPickupAble == true)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(b->isPickupAble));
			Ogre::Vector3 distanceVector = center - b->bodyPartNode->getPosition();
			/*Ogre::LogManager::getSingletonPtr()->logMessage(b->tag);*/
			float distance = distanceVector.length();
			
			if (distance < distanceThreshold)
			{
				b->pickedUp = true;
				return *b;
			}
		}
	}
	return closestbodypart;
}

void BodyPartManager::SpawnArm(Ogre::Vector3 position, Ogre::String bodypart)
{
	Arm arm;
	arm.Spawn(position, bodypart);
	bodyPartsList.push_back(arm);
}
/**	This function handles the actual body parts drops and chance to drop any body part
@param The position at which the body part is dropped
@param The arm object that is dropped
*/
void BodyPartManager::DropArm(Ogre::Vector3 position, Arm arm)
{
	int i = Random();
	if (i > dropChance)
	{
		arm.Drop(position);
		bodyPartsList.push_back(arm);
	}
}

void BodyPartManager::SpawnLeg(Ogre::Vector3 position)
{
	Leg leg;
	leg.Spawn(position, "");
	bodyPartsList.push_back(leg);
}

void BodyPartManager::IterateBodyParts(Ogre::Vector3 center, float pickupDistance)
{
	// Create a reference to the game manager
	GameManager& mgr = GameManager::getSingleton();
	
	std::vector<BodyPart>::iterator b = bodyPartsList.begin();
	while(b != bodyPartsList.end())
	{
		Ogre::Vector3 distanceVector = center - b->bodyPartNode->getPosition();
		
		float distance = distanceVector.length();
		/*Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(b->isPickupAble));*/
		if (distance < pickupDistance)
		{
			b->isPickupAble = true;
			show_label_ = true;
		}
		else
		{
			b->isPickupAble = false;
			show_label_ = false;
		}
		// TODO closest bodypart
		if (b->pickedUp == true)
		{
			b->bodyPartNode->detachAllObjects();
			b = bodyPartsList.erase(b);
			/*bodyPartsList.erase(b++);*/
		}
		else
		{
			++b;
		}
	}
}
