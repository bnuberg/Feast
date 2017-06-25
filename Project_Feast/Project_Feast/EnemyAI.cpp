#include "EnemyAI.h"
#include "Enemy.h"
#include "GameManager.h"
#include <OgreEntity.h>
#include "Player.h"
#include "BodyPart.h"
#include "EnemyPatternManager.h"
#include <OgreLogManager.h>

/*
We have chosen to split up the enemy class into enemy and enemyAI because the code related to movement and AI kept growing and growing and this way the code is easier to oversee.
This class contains all of the code related to the enemy movement such as dodging according to what weapons the player and enemy are using
It also contains the different states of the enemy and how they need to move in those states
*/

EnemyAI::EnemyAI()
	:aggroRange(400),
	attackRange(100),
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
	setEnemySpeed();
	timer_.reset();
}

void EnemyAI::Update(const Ogre::FrameEvent& evt)
{
	
}
// Methode to find the distance to the player from an enemy and return it as a vector.
Ogre::Vector3 EnemyAI::DistanceToPlayer(Ogre::SceneNode* enemyNode)
{
	GameManager& mgr = GameManager::GetSingleton();
	Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition();
	Ogre::Vector3 distanceVector = target - enemyNode->getPosition();
	return distanceVector;
}
//Methode to get the position of the target and return it as vector.
Ogre::Vector3 EnemyAI::EnemyTarget()
{
	GameManager& mgr = GameManager::GetSingleton();
	Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition();
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
	inAttackState = false;
	if (isAttacking)
	{
		return;
	}
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
	inAttackState = true;

	if (isAttacking)
	{
		return;
	}
	MoveDirection.z = -enemySpeed;

	enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
}
//Idle state so the enemy will walk back to spawn when it's too far from the player.
void EnemyAI::IdleState(const Ogre::FrameEvent& evt, Ogre::Vector3 MoveDirection, Ogre::SceneNode* enemyNode)
{
	inAttackState = false;
	Ogre::Vector3 startDistanceVector = startPosition - enemyNode->getPosition();
	float startDistance = startDistanceVector.length();

	if (isAttacking)
	{
		return;
	}
	enemyNode->lookAt(startPosition, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);

	MoveDirection.z = enemySpeed;

	enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	if (startDistance <= enemySpeed / 2500)
	{
		enemyNode->setPosition(startPosition);
	}
}

/** DodgeCheck checks if the player is attacking and executes a dodge for a set percentage of the attacks if true.
*	@param evt contains information about the frame event
*	@param enemyNode contains information about the node the enemy is attached to
*/

void EnemyAI::enemyDodgeCheck(const Ogre::FrameEvent& evt, Ogre::SceneNode* enemyNode){
	//This method checks if the player is attacking
	//It also checks what type off arm the player and enemy is using and dodges accordingly for a set percentage.
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

/** Dodge function moves the enemy away from the player quickly
*	@param evt contains information about the frame event
*	@param enemyNode contains information about the node the enemy is attached to
*/

void EnemyAI::enemyDodge(const Ogre::FrameEvent& evt, Ogre::SceneNode* enemyNode){
	Ogre::Vector3 MoveDirection = Ogre::Vector3::ZERO;
	if (isAttacking)
	{
		return;
	}
	//This method executes the dodge for a set amount 
		if (dodgeTimer.getMilliseconds() < dodgeTime)
		{
			MoveDirection.z = -enemySpeed * 8;
			enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
		}
		else
		{
			enemyAllowedToDodge = false;
		}
}

/** Random number generator
*	@return a random number between 1 and 100
*/

int EnemyAI::DodgeChance()
{
	//Returns a random number between 1 and 100. This is used for the dodge percentage
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
		aggroRange = 1500;
	}
	else
	{
		aggroRange = 1750;
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

float EnemyAI::setEnemySpeed()
{
	if (enemyArmType == 0)
	{
		enemySpeed*=2;
	}
	return enemySpeed;
}

/** This method checks what type of arm the player and enemy are using and dodges accordingly
*	@param enemyNode contains information about the node the enemy is attached to and is used for the position
*/

bool EnemyAI::DodgeCondition(Ogre::SceneNode* enemyNode)
{
	//This method checks what arm the player and enemy are using and in what range they both are and the enemy dodges accordingly 
	GameManager& mgr = GameManager::GetSingleton();
	int playerArmType = mgr.player.equipment.arm.type;

	//Enemy dodges when both are melee and the distance between both is less then 250
	if (enemyArmType == 0 && playerArmType == 0)
	{
		if (DistanceToPlayer(enemyNode).length() > 0 && DistanceToPlayer(enemyNode).length() < 250){
			return true;

		}
		else
			return false;
	}

	//Enemy dodges when enemy is melee and player is range and the enemy is in the ranged attack radius
	if (enemyArmType == 0 && playerArmType == 1)
	{
		if (DistanceToPlayer(enemyNode).length() > 450 && DistanceToPlayer(enemyNode).length() < 550){
			return true;

		}
		else
			return false;
	}

	//Enemy dodges when player is melee and enemy is ranged and the player is close range 
	if (enemyArmType == 1 && playerArmType == 0)
	{
		if (DistanceToPlayer(enemyNode).length() > 0 && DistanceToPlayer(enemyNode).length() < 250){
			return true;

		}
		else
			return false;

	}

	//Enemy dodges when both are ranged and the enemy is in range of the player's attack
	if (enemyArmType == 1 && playerArmType == 1)
	{
		if (DistanceToPlayer(enemyNode).length() > 450 && DistanceToPlayer(enemyNode).length() < 550){
			return true;

		}
		else
			return false;

	}

}

bool EnemyAI::AllowedToAttack()
{
	if (inAttackState)
	{
		return true;

	}
	else
	{
		return false;
	}

}