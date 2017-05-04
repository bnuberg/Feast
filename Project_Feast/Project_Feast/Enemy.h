#pragma once
#include <OISPrereqs.h>
#include <OgreVector3.h>
#include <OgreFrameListener.h>

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init();
	void Update(const Ogre::FrameEvent& evt);
	void GetDamaged(float damage);

	bool is_dead_ = false;
	bool is_dead2_ = false;
	Ogre::Entity* enemyEntity;
	Ogre::SceneNode* enemy_node_;

	bool operator == (const Enemy& e) const { return e.is_dead2_; }
	bool operator != (const Enemy& e) const { return !operator==(e); }

protected: 
	float enemyHealth;
	float enemySpeed;
	float enemyMaxHealth;
	float enemeyDamage;
	float enemyMaxDamage;
	float aggroRange;
	float attackRange;

	Ogre::Vector3 startPosition;
	

	void SetHealth(float startingHealth);
	void DoDamage(float damage);
	void DropBodyPart();
	void Move(const Ogre::FrameEvent& evt);
	void Die();
};

