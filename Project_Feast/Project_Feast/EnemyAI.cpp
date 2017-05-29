#include "EnemyAI.h"
#include "Enemy.h"
#include "GameManager.h"
#include <OgreEntity.h>
#include "Player.h"
#include "BodyPart.h"
#include "EnemyPatternManager.h"
#include <OgreLogManager.h>


EnemyAI::EnemyAI()
	:aggroRange(400),
	attackRange(100),
	attackTimer(0),
	dodgeTime(200),
	enemySpeed(50),
	startPosition(0, 0, 0)
{
}

EnemyAI::~EnemyAI()
{
}
void EnemyAI::Init()
{	
	timer_.reset();
}

void EnemyAI::Update(const Ogre::FrameEvent& evt)
{
	
}
// Methode to find the distance to the player from an enemy and return it as a vector.
Ogre::Vector3 EnemyAI::DistanceToPlayer(Ogre::SceneNode* enemyNode)
{
	GameManager& mgr = GameManager::GetSingleton();
	Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition() /*+ Ogre::Vector3(0, 20, 0)*/;
	Ogre::Vector3 distanceVector = target - enemyNode->getPosition();
	return distanceVector;
}
//Methode to get the position of the target and return it as vector.
Ogre::Vector3 EnemyAI::EnemyTarget()
{
	GameManager& mgr = GameManager::GetSingleton();
	Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition() /* + Ogre::Vector3(0, 20, 0)*/;
	return target;
}
//State selecter for the enemy behaviour
void EnemyAI::StateSelecter(const Ogre::FrameEvent& evt, Ogre::SceneNode* enemyNode)
{
	GameManager& mgr = GameManager::GetSingleton();
	Ogre::Vector3 MoveDirection (0, 0, 0);

	
	// When the distance to the player is less than the aggro range it will aggro
	if (DistanceToPlayer(enemyNode).length() <= aggroRange)
	{
		AggroState(evt, MoveDirection, enemyNode);
	}
	// When the player is outside the aggro range and the enemy isn't at the start position it will go to idle state
	else if (DistanceToPlayer(enemyNode).length() > aggroRange && enemyNode->getPosition() != startPosition)
	{
		IdleState(evt, MoveDirection, enemyNode);
	}
}
//Aggro state so the enemy walks to the player when it is in range
void EnemyAI::AggroState(const Ogre::FrameEvent& evt, Ogre::Vector3 MoveDirection, Ogre::SceneNode* enemyNode)
{
	enemyNode->lookAt(EnemyTarget(), Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);

	if (DistanceToPlayer(enemyNode).length()> attackRange)
	{
		MoveDirection.z = enemySpeed;
		DistanceToPlayer(enemyNode).normalise();
		enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	}
	else
	{
		AttackState(evt, MoveDirection, enemyNode);
	}
}
// Attack state so that the enemy stays withing a radius of the player and doesnt come closer
void EnemyAI::AttackState(const Ogre::FrameEvent& evt, Ogre::Vector3 MoveDirection, Ogre::SceneNode* enemyNode)
{
	if (timer_.getMilliseconds() >= attackTimer)
	{
		//attack 

		timer_.reset();
	}
	MoveDirection.z = -enemySpeed;
	enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
}
//Idle state so the enemy will walk back to spawn when it's too far from the player.
void EnemyAI::IdleState(const Ogre::FrameEvent& evt, Ogre::Vector3 MoveDirection, Ogre::SceneNode* enemyNode)
{
	Ogre::Vector3 startDistanceVector = startPosition - enemyNode->getPosition();
	float startDistance = startDistanceVector.length();


	enemyNode->lookAt(startPosition, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);

	MoveDirection.z = enemySpeed;

	enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	if (startDistance <= enemySpeed / 2500)
	{
		enemyNode->setPosition(startPosition);
	}
	else
	{
	}
}

void EnemyAI::enemyDodge(const Ogre::FrameEvent& evt, Ogre::SceneNode* enemyNode){
	Ogre::Vector3 MoveDirection = Ogre::Vector3::ZERO;
	GameManager& mgr = GameManager::GetSingleton();
	if (DistanceToPlayer(enemyNode).length() > attackRange){
		if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_SPACE)){
			enemyAllowedToDodge = true;
			dodgeTimer.reset();
		}
		if (enemyAllowedToDodge == true)
		{

			float dodgeChance = Ogre::Math::RangeRandom(0, 9);
			if (dodgeChance > 8)
			{

			if (dodgeTimer.getMilliseconds() <= dodgeTime)
			{
				MoveDirection.z = -enemySpeed * 5;  
				enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

			}
			else if (dodgeTimer.getMilliseconds() >= dodgeTime)
			{
				enemyAllowedToDodge = false;
				dodgeTimer.reset();
			}
			}
		}
	}
}