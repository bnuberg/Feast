#pragma once
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "AbilityMovement.h"
#include "IAbilityAttack.h"

class BodyPart
{
public:
	BodyPart();
	~BodyPart();

	void Spawn(Ogre::Vector3 position, Ogre::String bodypart);
	void Drop(Ogre::Vector3 position);

	void AbilityTarget(Ogre::Vector3 abilityTarget);
	void AbilityGlobalTarget(Ogre::Vector3 globalTarget);
	Ogre::Vector3 GetAbilityTarget();
	Ogre::Vector3 GetAbilityGlobalTarget();
	bool AbilityUpdate(Ogre::SceneNode* node, const Ogre::FrameEvent& evt);
	bool AbilityUpdate(Ogre::SceneNode* node, const Ogre::FrameEvent& evt, Ogre::String string);
	void AbilityDamage();

	Ogre::SceneNode* bodyPartNode;
	Ogre::String mesh;
	bool isPickupAble = false;
	bool pickedUp = false;
	Ogre::String tag;
	int randDamage;
	int randAttackSpeed;
	int randSpeed;
	int type;
	bool equippedByEnemy;
	IAbilityMovement *moveType;
	IAbilityAttack *attackType;

protected:

	Ogre::Vector3 globalTarget;

private: 
	int bodyPartHPMax;
	int bodyPartHPMin;
};

