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

Ogre::Vector3 AbilityMovement::GetTarget()
{
	return target;
}

bool AbilityMovement::Move(Ogre::SceneNode* node, const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 distanceVector = target - node->getPosition();
	float distance = distanceVector.length();
	float movementSpeed = 500;

	if (distance <= movementSpeed / 1500)
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