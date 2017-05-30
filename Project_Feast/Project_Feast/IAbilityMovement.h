#pragma once
#include <OgreVector3.h>


class IAbilityMovement
{
public:
	virtual Ogre::Node* SetNode(Ogre::SceneNode* node, bool equippedByEnemy) = 0;
	virtual void Return(Ogre::SceneNode* node) = 0;
	virtual bool Move(const Ogre::FrameEvent& evt) = 0;
};

