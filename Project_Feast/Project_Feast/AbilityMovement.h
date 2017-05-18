#pragma once

#include <OgreSceneManager.h>
#include "OgreEntity.h"

class AbilityMovement
{
public:
	AbilityMovement();
	~AbilityMovement();

	void SetTarget(Ogre::Vector3 abilityTarget);
	void SetGlobalTarget(Ogre::Vector3 globalTarget);
	Ogre::Vector3 GetTarget();
	Ogre::Vector3 GetGlobalTarget();
	bool Move(Ogre::SceneNode* node, const Ogre::FrameEvent& evt);
	bool MoveGlobal(Ogre::SceneNode* node, const Ogre::FrameEvent& evt);
private:
	Ogre::Vector3 target;
	Ogre::Vector3 globalTarget;
};

