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
	void Init(Ogre::Vector3 spawnPoint = Ogre::Vector3(0, 0, 0));
	void CheckHealth();
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
	Ogre::Real move = 200;
	int playerDamage;
	int playerAttackSpeed;
	int attack = 0;

	bool isSmashing = false;
	bool exists = false;
	Ogre::Pass* commonPass;
	Ogre::MaterialPtr common;
private:
	void InitiateAbility();
	void GroundSmashAttack(const Ogre::FrameEvent& evt, Ogre::Vector3 localStrikeTarget, Ogre::Vector3 globalStrikeTarget);
	void Die();

	Ogre::SceneNode* rocketarmtargetNode;
	Ogre::SceneNode* rightarmNode;
	Ogre::SceneNode* rightarmOrigin;
	Ogre::ParticleSystem* ModifierParticle;

	bool smashingDown = false;
	bool hasDied = false;
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

	const float playerShoulderHeight = 55;

	const Ogre::Real characterScale = 4;

	const char* torsoMeshName = "torso.mesh";
	const Ogre::Vector3 torsoSocketPosition = Ogre::Vector3(0, 25, 0);

	const char* headMeshName = "head.mesh";
	const Ogre::Vector3 headSocketPosition = Ogre::Vector3(0, 10, 0);

	const char* armMeshName = "hand.mesh";
	const Ogre::Vector3 leftArmSocketPosition = Ogre::Vector3(-7, 5, 0);
	const Ogre::Vector3 rightArmSocketPosition = Ogre::Vector3(7, 5, 0);

	const char* footMeshName = "foot.mesh";
	const Ogre::Vector3 leftFootSocketPosition = Ogre::Vector3(-3, -3, 0);
	const Ogre::Vector3 rightFootSocketPosition = Ogre::Vector3(3, -3, 0);

	void CheckLavaDrop(const Ogre::FrameEvent& evt);
	bool doomed = false;
	Ogre::Real fallingSpeed = 0;
	Ogre::Real dropRange = 1632;
	Ogre::Real lavaHeight = -300;
	Ogre::Real lavaDamage = 200;

	Ogre::Real totalTime = 0;

	Ogre::Vector3 cameraPosition = Ogre::Vector3(0, 100, 0);

	bool meatToHealth = false;

	Ogre::Timer timer_;							// Ogre timer class object
	Ogre::Timer dodge_timer_;
	unsigned long dodge_cooldown_;			// The duration it takes for an enemy to spawn
	unsigned long move_cooldown_;
};