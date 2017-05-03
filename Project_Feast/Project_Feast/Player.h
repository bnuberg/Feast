#pragma once

#include <iostream>
#include <OgreFrameListener.h>

class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update(const Ogre::FrameEvent& evt);
	void SetHealth(float startingHealth);
	void IncreaseHealth(float heal);
	void DecreaseHealth(float dmg);
	void IncreaseMaxHealth(float permaHeal);
	void DecreaseMaxHealth(float permaDmg);

private:
	void InitiateSmash();
	void GroundSmashAttack(const Ogre::FrameEvent& evt, Ogre::Vector3 localStrikeTarget, Ogre::Vector3 globalStrikeTarget);
	void Die();

	Ogre::SceneNode* rocketarmtargetNode;
	Ogre::SceneNode* rightarmNode;
	Ogre::SceneNode* rightarmOrigin;

	bool isSmashing = false;
	bool smashingDown = false;

	float health;
	float maxHealth;
	float rightarmSpeed = 500;
};

