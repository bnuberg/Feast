#pragma once

#include <OgreSceneManager.h>
#include "OgreEntity.h"

class AbilityMovement
{
public:
	AbilityMovement();
	~AbilityMovement();

	void SetTarget(Ogre::Vector3 abilityTarget);
	Ogre::Vector3 GetTarget();
	bool Move(Ogre::SceneNode* node, const Ogre::FrameEvent& evt);
private:
	Ogre::Vector3 target;
};

