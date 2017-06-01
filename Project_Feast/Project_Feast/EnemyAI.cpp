#include "EnemyAI.h"
#include "Enemy.h"
#include "GameManager.h"
#include <OgreEntity.h>
#include "Player.h"
#include "BodyPart.h"
#include "EnemyPatternManager.h"
#include <OgreLogManager.h>
#include <random>


EnemyAI::EnemyAI()
	:aggroRange(400),
	attackRange(100),
	attackTimer(0),
	dodgeTime(350),
	enemySpeed(50),
	startPosition(0, 0, 0)
{
}

EnemyAI::~EnemyAI()
{
}
void EnemyAI::Init()
{	
	setAggroR();
	setAttackR();
	timer_.reset();
	dodgeTimer.reset();
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

void EnemyAI::enemyDodgeCheck(const Ogre::FrameEvent& evt, Ogre::SceneNode* enemyNode){

	GameManager& mgr = GameManager::GetSingleton();

	if (mgr.player.isSmashing && !hasDodged)
	{
		if (DodgeChance() > 100 - chancePrecentage)
		{
			if (DodgeCondition(enemyNode))
			{
				dodgeTimer.reset();
				enemyAllowedToDodge = true;
			}
		}

		hasDodged = true;
	}

	if (!mgr.player.isSmashing)
	{
		hasDodged = false;
	}

	if (enemyAllowedToDodge)
	{
			enemyDodge(evt, enemyNode);	
	}

}

void EnemyAI::enemyDodge(const Ogre::FrameEvent& evt, Ogre::SceneNode* enemyNode){
	Ogre::Vector3 MoveDirection = Ogre::Vector3::ZERO;

		if (dodgeTimer.getMilliseconds() < dodgeTime)
		{
			MoveDirection.z = -enemySpeed * 15;
			enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
		}
		else
		{
			enemyAllowedToDodge = false;
		}
}

int EnemyAI::DodgeChance()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 100);
	return dist(mt);
}

void EnemyAI::SetArm(Arm arm)
{
	enemyArmType = arm.type;
}


float EnemyAI::setAggroR()
{
	if (enemyArmType == 0)
	{
		aggroRange = 1000;
	}
	else
	{
		aggroRange = 1250;
	}
	return aggroRange;
}

float EnemyAI::setAttackR()
{
	if (enemyArmType == 0)
	{
		attackRange = 125;
	}
	else
	{
		attackRange = 500;
	}
	return attackRange;
}

unsigned long EnemyAI::setAttackT()
{
	if (enemyArmType == 0)
	{

	}
	else
	{

	}
	return attackTimer;
}

bool EnemyAI::DodgeCondition(Ogre::SceneNode* enemyNode)
{
	GameManager& mgr = GameManager::GetSingleton();
	int playerArmType = mgr.player.equipment.arm.type;

	if (enemyArmType == 0 && playerArmType == 0)
	{
		if (DistanceToPlayer(enemyNode).length() > 0 && DistanceToPlayer(enemyNode).length() < 250){
			return true;

		}
		else
			return false;
	}

	if (enemyArmType == 0 && playerArmType == 1)
	{
		if (DistanceToPlayer(enemyNode).length() > 450 && DistanceToPlayer(enemyNode).length() < 550){
			return true;

		}
		else
			return false;
	}

	if (enemyArmType == 1 && playerArmType == 0)
	{
		if (DistanceToPlayer(enemyNode).length() > 0 && DistanceToPlayer(enemyNode).length() < 250){
			return true;

		}
		else
			return false;

	}

	if (enemyArmType == 1 && playerArmType == 1)
	{
		if (DistanceToPlayer(enemyNode).length() > 450 && DistanceToPlayer(enemyNode).length() < 550){
			return true;

		}
		else
			return false;

	}

}