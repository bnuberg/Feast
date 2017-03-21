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
protected: 
	float enemyHealth;
	float enemySpeed;
	float enemyMaxHealth;
	float enemeyDamage;
	float enemyMaxDamage;
	bool isDead = true;

	Ogre::Vector3 startPosition;

	void SetHealth(float startingHealth);
	void DoDamage(float damage);
	void GetDamaged(float damage);
	void DropBodyPart();
	void Move(const Ogre::FrameEvent& evt);
	void Die();
	
	
};

