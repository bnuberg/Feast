#pragma once
#include <OISPrereqs.h>
#include <OgreVector3.h>
#include <OgreFrameListener.h>
#include <OgreEntity.h>
#include "EnemyEquipment.h"

class Enemy
{
public:
	Enemy();
	Enemy(float health, float speed, float damage, Ogre::Vector3 sPosition, float scale = 1.0f);
	~Enemy();
	void Init();
	void Update(const Ogre::FrameEvent& evt);
	void GetDamaged(float damage);
	void SetEquipmentMesh(Ogre::String meshName);
	void SetAttack();
	void SetEquipment();

	bool is_dead_ = false;
	bool is_dead2_ = false;
	Ogre::Entity* enemyEntity;
	Ogre::SceneNode* enemy_node_;
	EnemyEquipment enemyEquipment;
	Ogre::SceneNode* erightarmNode;

	bool operator == (const Enemy& e) const { return e.is_dead2_; }
	bool operator != (const Enemy& e) const { return !operator==(e); }

	void setStartPosition(Ogre::Vector3 position);

	int enemyID;

private:
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

	bool isAttacking = false;
	bool attackDown = false;

	Ogre::Vector3 fakeStartPosition;
	Ogre::Vector3 startPosition;
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

