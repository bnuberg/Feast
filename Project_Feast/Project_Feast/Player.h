#pragma once

#include <iostream>
#include <OgreFrameListener.h>
#include <OgreEntity.h>
#include "Equipment.h"

class Player
{
public:
	Player();
	~Player();
	void Init(Ogre::Vector3 spawnPoint = Ogre::Vector3(0, 0, 0));
	void Update(const Ogre::FrameEvent& evt);

	// Meat functions
	float GetMeat();
	void SetMeat(float startingMeat);
	void IncreaseMeat(float incMeat);
	void DecreaseMeat(float spendMeat);
	void convertMeattoHealth();

	// Health functions
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

	bool exists = false;
private:
	void InitiateAbility();
	void GroundSmashAttack(const Ogre::FrameEvent& evt, Ogre::Vector3 localStrikeTarget, Ogre::Vector3 globalStrikeTarget);
	void Die();

	Ogre::SceneNode* rocketarmtargetNode;
	Ogre::SceneNode* rightarmNode;
	Ogre::SceneNode* rightarmOrigin;
	float playerShoulderHeight = 160;

	bool isSmashing = false;
	bool smashingDown = false;

	float health;
	float meat;
	float maxHealth;
	float rightarmSpeed = 500;
};