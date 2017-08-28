#pragma once
#include <OgreVector3.h>
#include <OgreFrameListener.h>
#include <OgreTimer.h>
#include <OgreEntity.h>
#include "EnemyEquipment.h"
#include "Healthbar.h"
#include "EnemyAI.h"
#include "Entity.h"

class EnemyPatternManager;

/** Inherits from Entity for basic functions like health
*/
class Enemy : public Entity
{
public:
	Enemy();
	Enemy(float health, float speed, float damage, Ogre::Vector3 sPosition, float scale = 1.0f);
	~Enemy();

	EnemyPatternManager* epm;

	int enemyNumber;

	void Init(int level);
	void Update(const Ogre::FrameEvent& evt);
	void GetDamaged(float damage);
	Ogre::Vector3 DistanceToPlayer();
	void SetEquipmentMesh(Ogre::String meshName);
	void SetAttack();
	void SetEquipment();
	void SetStartPosition(Ogre::Vector3 position);
	void StartBleeding(int damage);
	void RemoveBleeding();
	void BleedEnemy();
	void StartSlow();
	void RemoveSlow();
	void SlowEnemy();
	void Knockback();
	void Die();

	bool is_dead_ = false;
	bool is_dead2_ = false;
	bool is_bleeding = false;
	bool is_slowed = false;
	Ogre::Entity* enemyEntity;
	Ogre::SceneNode* enemyNode;
	EnemyEquipment enemyEquipment;
	Ogre::SceneNode* erightarmNode;
	Ogre::SceneNode* healthBarNode;

	bool operator == (const Enemy& e) const { return e.is_dead2_; }
	bool operator != (const Enemy& e) const { return !operator==(e); }

	int enemyID;
	Healthbar healthbar;
	int bleedTick;
	int maxBleedTick;
	float scale;

private:
	Ogre::Timer timer_;
	Ogre::Timer attackDelay;
	EnemyAI enemyAI;
	
	Ogre::Vector3 GetStartPosition() const;

	Ogre::ParticleSystem* bleedParticle;
	Ogre::ParticleSystem* slowParticle;
	Ogre::ParticleSystem* knockbackParticle;
	Ogre::Timer bleedTimer;
	unsigned long bleed_Timer_Max;
	float bleedDamage;
	Ogre::Timer slowTimer;
	unsigned long slow_Timer_Max;
	unsigned long attackTimer;

	float GetScale() const;
	void SetScale(float scale);

	float enemySpeed;
	float enemyBaseSpeed;
	float enemyDamage;
	float enemyMaxDamage;
	float aggroRange;
	float attackRange;

	std::vector<Ogre::Vector3> positions;
	std::vector<bool> blockages;

	int level;
	bool isAttacking = false;
	bool attackDown = false;

	Ogre::Vector3 fakeStartPosition;
	Ogre::Vector3 healthBarPosition = Ogre::Vector3(0, 50, 0);
	Ogre::Vector3 startPosition;
	Ogre::SceneNode* rocketarmtargetNode;
	
	void SetStats();
	void SetSpeed(float speed);
	void DoDamage(float damage);
	void Move(const Ogre::FrameEvent& evt);
	
	void DetachBodyParts() const;
	void InitiateAbility();
	void InitiateSmash();
	void GroundSmashAttack(const Ogre::FrameEvent& evt, Ogre::Vector3 localStrikeTarget, Ogre::Vector3 globalStrikeTarget);
	void Debuff();

	const float shoulderHeight = 55;

	const Ogre::Real characterScale = 4;

	void AddBodyObjects();

	Ogre::SceneNode* torsoNode;
	const char* torsoMeshName = "enemyTorso.mesh";
	const Ogre::Vector3 torsoSocketPosition = Ogre::Vector3(0, 25, 0);

	Ogre::SceneNode* headNode;
	const char* headMeshName = "enemyHead.mesh";
	const Ogre::Vector3 headSocketPosition = Ogre::Vector3(0, 10, 0);

	Ogre::SceneNode* leftArmNode;
	Ogre::SceneNode* rightArmNode;
	const char* armMeshName = "enemyHand.mesh";
	const Ogre::Vector3 leftArmSocketPosition = Ogre::Vector3(-7, 5, 0);
	const Ogre::Vector3 rightArmSocketPosition = Ogre::Vector3(7, 5, 0);

	Ogre::SceneNode* leftFootNode;
	Ogre::SceneNode* rightFootNode;
	const char* footMeshName = "enemyFoot.mesh";
	const Ogre::Vector3 leftFootSocketPosition = Ogre::Vector3(-3, -3, 0);
	const Ogre::Vector3 rightFootSocketPosition = Ogre::Vector3(3, -3, 0);

	Ogre::SceneNode* erocketarmtargetNode;
	Ogre::SceneNode* erightarmOrigin;
	
};