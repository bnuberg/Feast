#pragma once
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "AbilityMovement.h"
#include "AbilityAttack.h"

class BodyPart
{
public:
	BodyPart();
	~BodyPart();

	void Spawn(Ogre::Vector3 position);

	virtual void Stats();

	void AbilityTarget(Ogre::Vector3 abilityTarget);
	Ogre::Vector3 GetAbilityTarget();
	bool AbilityUpdate(Ogre::SceneNode* node, const Ogre::FrameEvent& evt);
	void AbilityDamage(Ogre::Vector3 target);

	Ogre::SceneNode* bodyPartNode;
	Ogre::String mesh;
	bool isPickupAble = false;
	bool pickedUp = false;
	Ogre::String tag;
	int randDamage;
	int randAttackSpeed;
	int randSpeed;
	int type;

protected:
	AbilityMovement moveType;
	AbilityAttack *attackType;

private: 
	int bodyPartHPMax;
	int bodyPartHPMin;
};

