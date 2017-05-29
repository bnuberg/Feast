#pragma once
#include <OgreVector3.h>


class IAbilityMovement
{
public:
	
	virtual void SetTarget(Ogre::Vector3 abilityTarget) = 0;
	virtual void SetGlobalTarget(Ogre::Vector3 globalTarget) = 0;
	virtual Ogre::Vector3 GetTarget() = 0;
	virtual Ogre::Vector3 GetGlobalTarget() = 0;
	virtual bool Move(Ogre::SceneNode* node, const Ogre::FrameEvent& evt) = 0;
	virtual bool MoveGlobal(Ogre::SceneNode* node, const Ogre::FrameEvent& evt) = 0;
};

