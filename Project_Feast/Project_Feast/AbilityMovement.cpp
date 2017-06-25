#include "AbilityMovement.h"


AbilityMovement::AbilityMovement()
{
}


AbilityMovement::~AbilityMovement()
{
}

void AbilityMovement::SetTarget(Ogre::Vector3 abilityTarget)
{
	target = abilityTarget;
}

void AbilityMovement::SetGlobalTarget(Ogre::Vector3 target)
{
	globalTarget = target;
}

Ogre::Vector3 AbilityMovement::GetTarget()
{
	return target;
}

Ogre::Vector3 AbilityMovement::GetGlobalTarget()
{
	return globalTarget;
}

bool AbilityMovement::Move(Ogre::SceneNode* node, const Ogre::FrameEvent& evt, bool equipped)
{
	Ogre::Vector3 distanceVector = target - node->getPosition();
	float distance = distanceVector.length();
	
	float movementSpeed = 800;

	if (equipped)
	{
		movementSpeed = 500;
	}

	if (distance <= movementSpeed / 50)
	{
		node->setPosition(target);
		return true;
	}
	else
	{
		distanceVector.normalise();

		node->translate(distanceVector * movementSpeed * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

		return false;
	}

	return false;
}

bool AbilityMovement::MoveGlobal(Ogre::SceneNode* node, const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 distanceVector = globalTarget - node->_getDerivedPosition();
	float distance = distanceVector.length();
	float movementSpeed = 500;

	if (distance <= movementSpeed / 1500)
	{
		node->setPosition(globalTarget);
		return true;
	}
	else
	{
		distanceVector.normalise();

		node->translate(distanceVector * movementSpeed * evt.timeSinceLastFrame, Ogre::Node::TS_WORLD);

		return false;
	}

	return false;
}