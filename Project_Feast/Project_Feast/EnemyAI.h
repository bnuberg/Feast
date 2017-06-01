#pragma once
#include <OISPrereqs.h>
#include <OgreVector3.h>
#include <OgreFrameListener.h>
#include <OgreTimer.h>

class EnemyAI
{
public:
	EnemyAI();
	~EnemyAI();
	void Init();
	void Update(const Ogre::FrameEvent& evt);
	void StateSelecter(const Ogre::FrameEvent& evt);
	Ogre::Vector3 DistanceToPlayer(Ogre::SceneNode* enemyNode);
	Ogre::Vector3 startPosition;
	void StateSelecter(const Ogre::FrameEvent& evt, Ogre::SceneNode* enemyNode);
	void enemyDodge(const Ogre::FrameEvent& evt, Ogre::SceneNode* enemyNode);
	void enemyDodgeCheck(const Ogre::FrameEvent& evt, Ogre::SceneNode* enemyNode);
	int DodgeChance();	

private:
	Ogre::Timer timer_;
	Ogre::Timer dodgeTimer;

protected:
	float enemySpeed;
	float aggroRange;
	float attackRange;
	unsigned long attackTimer;
	float dodgeChance;
	unsigned long dodgeTime;
	bool enemyAllowedToDodge = false;

	Ogre::Vector3 EnemyTarget();

	void IdleState(const Ogre::FrameEvent& evt, Ogre::Vector3 MoveDirection, Ogre::SceneNode* enemyNode);
	void AggroState(const Ogre::FrameEvent& evt, Ogre::Vector3 MoveDirection, Ogre::SceneNode* enemyNode);
	void AttackState(const Ogre::FrameEvent& evt, Ogre::Vector3 MoveDirection, Ogre::SceneNode* enemyNode);

	bool hasDodged;
	int chancePrecentage = 20;
};