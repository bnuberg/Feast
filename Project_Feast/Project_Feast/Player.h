#pragma once

#include <iostream>
#include <OgreFrameListener.h>
#include <OgreEntity.h>
#include <OgreTimer.h>
#include "Equipment.h"
#include "Healthbar.h"

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

	// Helalth functions
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
	void ChangeArmModifier(int modifier);

	Ogre::Vector3 playerPosition;
	Equipment equipment;
	Ogre::Real move = 300;
	int playerDamage;
	int playerAttackSpeed;
	int attack = 0;

	bool isSmashing = false;
	bool exists = false;
	Ogre::Pass* commonPass;
	Ogre::MaterialPtr common;
	Healthbar playerHealthbar;
private:
	void InitiateAbility();
	void GroundSmashAttack(const Ogre::FrameEvent& evt, Ogre::Vector3 localStrikeTarget, Ogre::Vector3 globalStrikeTarget);
	void Die();

	Ogre::SceneNode* playerHealthBarNode;
	Ogre::SceneNode* rocketarmtargetNode;
	Ogre::SceneNode* rightarmNode;
	Ogre::SceneNode* rightarmOrigin;
	Ogre::ParticleSystem* ModifierParticle;
	float playerShoulderHeight = 160;

	bool smashingDown = false;
	bool ableToHeal;

	bool keyPressed = false;
	bool dodgeLeft = false;
	bool dodgeRight = false;
	bool ableToDodge = false;
	bool CanPickUp = true;

	float health;
	float meat;
	float maxHealth;
	float dodgeMeatCost = 5;
	float rightarmSpeed = 500;

	bool meatToHealth = false;

	Ogre::Timer timer_;							// Ogre timer class object
	Ogre::Timer dodge_timer_;
	unsigned long dodge_cooldown_;			// The duration it takes for an enemy to spawn
	unsigned long move_cooldown_;
};
