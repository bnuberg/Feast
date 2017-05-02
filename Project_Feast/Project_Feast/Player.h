#pragma once

#include <iostream>
#include <OgreFrameListener.h>
#include <OgreEntity.h>

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
	void Pickup();
	Ogre::Vector3 playerPosition;

private:
	void Die();

	float health;
	float maxHealth;
};

