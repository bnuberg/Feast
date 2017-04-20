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
	float health;

private:
	void Die();

	
	float maxHealth;
};

