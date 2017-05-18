#pragma once
#include "OgreEntity.h"
#include "OgreSubEntity.h"

class BodyPart
{
public:
	BodyPart();
	~BodyPart();

	void Spawn(Ogre::Vector3 position, Ogre::String bodypart);
	void Drop(Ogre::Vector3 position);

	virtual void Stats();
	Ogre::SceneNode* bodyPartNode;
	Ogre::String mesh;
	bool isPickupAble = false;
	bool pickedUp = false;
	Ogre::String tag;
	int randDamage;
	int randAttackSpeed;
	int randSpeed;
	int type;

private: 
	int bodyPartHPMax;
	int bodyPartHPMin;
};

