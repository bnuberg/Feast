#pragma once
#include <OISPrereqs.h>
#include <OgreVector3.h>
#include <OgreFrameListener.h>
#include <OgreTimer.h>
#include <OgreEntity.h>
#include "EnemyEquipment.h"
#include <OgreTimer.h>
#include "EnemyAI.h"

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
	void Init(int level);
	void Update(const Ogre::FrameEvent& evt);
	void GetDamaged(float damage);
	Ogre::Vector3 DistanceToPlayer();
	void SetEquipmentMesh(Ogre::String meshName);
	void SetAttack();
	void SetEquipment();
	void setStartPosition(Ogre::Vector3 position);
	void StartBleeding(int damage);
	void RemoveBleeding();
	void BleedEnemy();
	void StartSlow();
	void RemoveSlow();
	void SlowEnemy();
	void Knockback();

	bool is_dead_ = false;
	bool is_dead2_ = false;
	bool is_bleeding = false;
	bool is_slowed = false;
	Ogre::Entity* enemyEntity;
	Ogre::SceneNode* enemy_node_;
	EnemyEquipment enemyEquipment;
	Ogre::SceneNode* erightarmNode;

	bool operator == (const Enemy& e) const { return e.is_dead2_; }
	bool operator != (const Enemy& e) const { return !operator==(e); }
protected: 

	void setStartPosition(Ogre::Vector3 position);

	int enemyID;
	int bleedTick;
	int maxBleedTick;

private:
	Ogre::Timer timer_;

	Ogre::Timer timer_;
	EnemyAI enemyAI;
	
	Ogre::Vector3 getStartPosition();

	Ogre::ParticleSystem* bleedParticle;
	Ogre::ParticleSystem* slowParticle;
	Ogre::ParticleSystem* knockbackParticle;
	Ogre::Timer bleedTimer;
	unsigned long bleed_Timer_Max;
	float bleedDamage;
	Ogre::Timer slowTimer;
	unsigned long slow_Timer_Max;

	float getScale();
	void setScale(float scale);

	float enemyHeight;
	float enemyHealth;
	float enemySpeed;
	float enemyBaseSpeed;
	float enemyMaxHealth;
	float enemeyDamage;
	float enemyMaxDamage;
	float aggroRange;
	float attackRange;
	float scale;

	std::vector<Ogre::Vector3> positions;
	std::vector<bool> blockages;

	int level;
	bool isAttacking = false;
	bool attackDown = false;

	Ogre::Vector3 fakeStartPosition;
	Ogre::SceneNode* rocketarmtargetNode;
	
	void SetStats();
	void SetHealth(float startingHealth);
	void SetSpeed(float speed);
	void DoDamage(float damage);
	void DropBodyPart();
	void Move(const Ogre::FrameEvent& evt);
	void Die();
	void InitiateAbility();
	void InitiateSmash();
	void GroundSmashAttack(const Ogre::FrameEvent& evt, Ogre::Vector3 localStrikeTarget, Ogre::Vector3 globalStrikeTarget);
	void Debuff();

	Ogre::SceneNode* erocketarmtargetNode;
	Ogre::SceneNode* erightarmOrigin;
};