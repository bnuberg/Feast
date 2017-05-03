#pragma once
#include "OgreEntity.h"
#include "OgreSubEntity.h"
/**
 *Body part is the parent class for all the body parts
 *It has basic logic that every body part needs to have
 *This means there is no need for rewriting the same functions every body part needs in every single body part class
 *@param Spawn function handles spawning 
 *@param mesh_ is a variable so any mesh string can be passed along
 *@param is_pick_up_able_ checks if the body part can be picked up
 *@param picked_up_ checks if the body part has been picked up
 *@param tag_ checks what tag the body part has this is a string 
 */
class BodyPart
{
public:
	BodyPart();
	~BodyPart();

	void Spawn(Ogre::Vector3 position);

	virtual void Stats();
	Ogre::SceneNode* body_part_node_;
	Ogre::String mesh_;
	bool is_pick_up_able_ = false;
	bool picked_up_ = false;
	Ogre::String tag_;

private: 
	// HP variables needed for random generation of health stat for body parts
	int body_part_hp_max_;
	int body_part_hp_min_;
};

