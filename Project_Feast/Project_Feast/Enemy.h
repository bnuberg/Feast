#pragma once
#include <OISPrereqs.h>
#include <OgreVector3.h>
#include <OgreFrameListener.h>
#include <OgreEntity.h>
#include "EnemyEquipment.h"
#include <OgreTimer.h>

class EnemyPatternManager;

class Enemy
{
public:
	Enemy();
	Enemy(float health, float speed, float damage, Ogre::Vector3 sPosition, float scale = 1.0f);
	~Enemy();

	EnemyPatternManager* epm;

	int enemyNumber;

	void Init();
	void Update(const Ogre::FrameEvent& evt);
	void GetDamaged(float damage);
	Ogre::Vector3 DistanceToPlayer();
	void SetEquipmentMesh(Ogre::String meshName);
	void SetAttack();
	void SetEquipment();
	void setStartPosition(Ogre::Vector3 position);

	Ogre::Vector3 startPosition;
	bool is_dead_ = false;
	bool is_dead2_ = false;
	Ogre::Entity* enemyEntity;
	Ogre::SceneNode* enemy_node_;
	EnemyEquipment enemyEquipment;
	Ogre::SceneNode* erightarmNode;

	bool operator == (const Enemy& e) const { return e.is_dead2_; }
	bool operator != (const Enemy& e) const { return !operator==(e); }
protected: 
	int enemyID;

private:
	Ogre::Timer timer_;

	Ogre::Vector3 getStartPosition();

	float getScale();
	void setScale(float scale);

	float enemyHeight;
	float enemyHealth;
	float enemySpeed;
	float enemyMaxHealth;
	float enemeyDamage;
	float enemyMaxDamage;
	float aggroRange;
	float attackRange;
	float scale;

	std::vector<Ogre::Vector3> positions;
	std::vector<bool> blockages;

	bool isAttacking = false;
	bool attackDown = false;

	Ogre::Vector3 fakeStartPosition;
	Ogre::SceneNode* rocketarmtargetNode;
	
	void SetHealth(float startingHealth);
	void DoDamage(float damage);
	void DropBodyPart();
	void Move(const Ogre::FrameEvent& evt);
	void Die();
	void InitiateAbility();
	void InitiateSmash();
	void GroundSmashAttack(const Ogre::FrameEvent& evt, Ogre::Vector3 localStrikeTarget, Ogre::Vector3 globalStrikeTarget);

	Ogre::SceneNode* erocketarmtargetNode;
	Ogre::SceneNode* erightarmOrigin;
};