#include "AbilityMovementRange.h"


AbilityMovementRange::AbilityMovementRange()
{
}


AbilityMovementRange::~AbilityMovementRange()
{
}

bool AbilityMovementRange::Move(const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 distanceVector = target - node->getPosition();
	float distance = distanceVector.length();
	float movementSpeed = 500;

	if (distance <= movementSpeed / 200)
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

Ogre::Node* AbilityMovementRange::SetNode(Ogre::SceneNode* n, bool equippedByEnemy)
{
	node = n;
	float direction = 1;
	if (equippedByEnemy)
	{
		direction = -1;
	}
	Ogre::Node* targetNode = n->createChildSceneNode(n->getPosition() - Ogre::Vector3(0, n->getPosition().y, direction * 500));
	target = targetNode->getPosition();

	// Return the target position to the bodypart so it canu se it for the attack
	return targetNode;
}

void AbilityMovementRange::Return(Ogre::SceneNode* n)
{
	target = n->getPosition();
}