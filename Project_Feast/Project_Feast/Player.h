#pragma once

#include <OgreEntity.h>
#include <OgreTimer.h>
#include "Equipment.h"
#include "Healthbar.h"
#include "Entity.h"

/** Inherits from Entity for basic functions like health 
*/
class Player : public Entity
{
public:
	Player();
	~Player();
	void Init(Ogre::Vector3 spawnPoint = Ogre::Vector3(0, 0, 0));
	void Update(const Ogre::FrameEvent& evt);

	// Meat functions
	float GetMeat() const;
	void SetMeat(float startingMeat);
	void IncreaseMeat(float incMeat);
	void DecreaseMeat(float spendMeat);
	void ConvertMeattoHealth();

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
	void Die() override;

	bool smashingDown = false;
	bool hasDied = false;
	bool ableToHeal;

	bool keyPressed = false;
	bool dodgeLeft = false;
	bool dodgeRight = false;
	bool ableToDodge = false;
	bool CanPickUp = true;

	float meat;
	float dodgeMeatCost = 5;
	float rightarmSpeed = 500;

	const float shouderHeight = 55;

	const Ogre::Real characterScale = 4;

	Ogre::SceneNode* torsoNode;
	const char* torsoMeshName = "torso.mesh";
	const Ogre::Vector3 torsoSocketPosition = Ogre::Vector3(0, 25, 0);

	Ogre::SceneNode* headNode;
	const char* headMeshName = "head.mesh";
	const Ogre::Vector3 headSocketPosition = Ogre::Vector3(0, 10, 0);

	Ogre::SceneNode* leftArmNode;
	Ogre::SceneNode* rightArmNode;
	const char* armMeshName = "hand.mesh";
	const Ogre::Vector3 leftArmSocketPosition = Ogre::Vector3(-7, 5, 0);
	const Ogre::Vector3 rightArmSocketPosition = Ogre::Vector3(7, 5, 0);

	Ogre::SceneNode* rocketArmTargetNode;
	Ogre::SceneNode* rightArmOrigin;

	Ogre::SceneNode* leftFootNode;
	Ogre::SceneNode* rightFootNode;
	const char* footMeshName = "foot.mesh";
	const Ogre::Vector3 leftFootSocketPosition = Ogre::Vector3(-3, -3, 0);
	const Ogre::Vector3 rightFootSocketPosition = Ogre::Vector3(3, -3, 0);

	Ogre::ParticleSystem* ModifierParticle;

	Ogre::Vector3 cameraPosition = Ogre::Vector3(0, 300, 0);

	bool meatToHealth = false;

	Ogre::Timer timer_;							// Ogre timer class object
	Ogre::Timer dodge_timer_;
	unsigned long dodge_cooldown_;			// The duration it takes for an enemy to spawn
	unsigned long move_cooldown_;
};
