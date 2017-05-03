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
/**
 * This function checks for the closest body part to the player that can be picked up
 * @param The center point around which body parts distance is checked
 * @param The distance between the center point and the different body parts
 * @param The closest body part to the player is saved in a body part instance
 */
BodyPart BodyPartManager::ClosestBodyPart(Ogre::Vector3 center)
{
	// Instance of body part
	BodyPart closestbodypart;
	// pick a really high float value for the first iteration
	float closest = 999999;
	// Iteration through the body parts list
	for (std::vector<BodyPart>::iterator b = body_parts_list_.begin(); b != body_parts_list_.end(); ++b)
	{
		if (b->is_pick_up_able_ == true)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(b->is_pick_up_able_));
			Ogre::Vector3 distancevector = center - b->body_part_node_->getPosition();
			
			float distance = distancevector.length();
			// Check if the distance is lower than the closest distance 
			if (distance < closest)
			{
				// Pointer to element of the list in the interator is bound to body part instance 
				closestbodypart = *b;
				// Changes the closest distance to match the closest object
				closest = distance;
			}
		}
	}
	return closestbodypart;
}

// This method spawns the arm body parts and adds them to the list
void BodyPartManager::SpawnArm(Ogre::Vector3 position)
{
	Arm arm;
	arm.Spawn(position);
	body_parts_list_.push_back(arm);
}
// This method spawns the leg body parts and adds them to the list
void BodyPartManager::SpawnLeg(Ogre::Vector3 position)
{
	Leg leg;
	leg.Spawn(position);
	body_parts_list_.push_back(leg);
}

void BodyPartManager::IterateBodyParts(Ogre::Vector3 center, float pickupdistance)
{
	// Create a reference to the game manager
	GameManager& mgr = GameManager::getSingleton();
	
	// Iterator to go through the bodypartlist filled with different parts
	for (std::vector<BodyPart>::iterator b = body_parts_list_.begin(); b != body_parts_list_.end(); ++b)
	{
		/*Ogre::LogManager::getSingletonPtr()->logMessage(b->tag);*/

		// Check the Vector3 distancevector between a point and the body parts in the list
		Ogre::Vector3 distancevector = center - b->body_part_node_->getPosition();
		
		// Pass it onto a float value
		float distance = distancevector.length();
		
		// Here we check if the distance is smaller than the pickup distance so the player can only pick up body parts that are close
		if (distance < pickupdistance)
		{
			// sets the bodypart to be able to be picked up
			b->is_pick_up_able_ = true;
			
		}
		else
		{
			// when going out of range change this back to false
			b->is_pick_up_able_ = false;
		}
		
		if (b->picked_up_ == true)
		{
			// TODO delete bodypart
		}
		
	}
}
