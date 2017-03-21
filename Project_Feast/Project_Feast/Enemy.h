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
	bool isDead;

	Ogre::Vector3 startPosition;
	Ogre::Vector3 targetPosition;


	void SetHealth(float startingHealth);
	void DoDamage(float damage);
	void GetDamaged(float damage);
	void DropBodyPart();
	void Move(Ogre::Vector3 target, const Ogre::FrameEvent& evt);
	void Die();
	
	
};

