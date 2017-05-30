#pragma once

#include <OgreSceneManager.h>
#include "OgreEntity.h"
#include "IAbilityMovement.h"

class AbilityMovementMelee : public IAbilityMovement
{
public:
	AbilityMovementMelee();
	~AbilityMovementMelee();

	Ogre::Node* SetNode(Ogre::SceneNode* node, bool equippedByEnemy) override;
	void Return(Ogre::SceneNode* node) override;
	bool Move(const Ogre::FrameEvent& evt) override;
private:
	Ogre::SceneNode* node;
	Ogre::Vector3 target;
	Ogre::Vector3 globalTarget;
};

