#pragma once

#include <OgreSceneManager.h>
#include "OgreEntity.h"
#include "IAbilityMovement.h"

class AbilityMovement : public IAbilityMovement
{
public:
	AbilityMovement();
	~AbilityMovement();

	void SetTarget(Ogre::Vector3 abilityTarget) override;
	void SetGlobalTarget(Ogre::Vector3 globalTarget) override;
	Ogre::Vector3 GetTarget() override;
	Ogre::Vector3 GetGlobalTarget() override;
	bool Move(Ogre::SceneNode* node, const Ogre::FrameEvent& evt, bool equipped) override;
	bool MoveGlobal(Ogre::SceneNode* node, const Ogre::FrameEvent& evt) override;
private:
	Ogre::Vector3 target;
	Ogre::Vector3 globalTarget;
};

