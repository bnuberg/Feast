#pragma once

#include <OgreSceneManager.h>
#include "OgreEntity.h"
#include "IAbilityMovement.h"

class AbilityMovementRange : public IAbilityMovement
{
public:
	AbilityMovementRange();
	~AbilityMovementRange();

	Ogre::Node* SetNode(Ogre::SceneNode* node, bool equippedByEnemy) override;
	void Return(Ogre::SceneNode* node) override;
	bool Move(const Ogre::FrameEvent& evt) override;
private:
	Ogre::SceneNode* node;
	Ogre::Vector3 target;
	Ogre::Vector3 globalTarget;
};

