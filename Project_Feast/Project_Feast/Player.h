#pragma once

#include <iostream>
#include <OgreFrameListener.h>
#include <OgreEntity.h>
#include <OgreTimer.h>
#include "Equipment.h"

class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update(const Ogre::FrameEvent& evt);

	float GetMeat();
	void SetMeat(float startingMeat);
	void IncreaseMeat(float incMeat);
	void DecreaseMeat(float spendMeat);

	void convertMeattoHealth();

	float GetHealth();
	void SetHealth(float startingHealth);
	void IncreaseHealth(float heal);
	void DecreaseHealth(float dmg);
	void IncreaseMaxHealth(float permaHeal);
	void DecreaseMaxHealth(float permaDmg);
	void SetAttack();
	void SetSpeed();
	void Pickup();
	void Discard();

	void ChangeRightArmMesh(Ogre::String meshName);

	Ogre::Vector3 playerPosition;
	Equipment equipment;
	Ogre::Real move = 200;
	int playerDamage;
	int playerAttackSpeed;
	int attack = 0;
private:
	void InitiateSmash();
	void GroundSmashAttack(const Ogre::FrameEvent& evt, Ogre::Vector3 localStrikeTarget, Ogre::Vector3 globalStrikeTarget);
	void Die();
	Ogre::SceneNode* rocketarmtargetNode;
	Ogre::SceneNode* rightarmNode;
	Ogre::SceneNode* rightarmOrigin;

	bool isSmashing = false;
	bool smashingDown = false;

	bool keyPressed = false;
	bool dodgeLeft = false;
	bool dodgeRight = false;
	bool ableToDodge = false;

	float health;
	float meat;
	float maxHealth;
	float dodgeMeatCost = 5;
	float rightarmSpeed = 500;

	Ogre::Timer timer_;							// Ogre timer class object
	Ogre::Timer dodge_timer_;
	unsigned long dodge_cooldown_;			// The duration it takes for an enemy to spawn
	unsigned long move_cooldown_;
};

