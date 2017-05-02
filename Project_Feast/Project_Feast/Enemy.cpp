#include "Enemy.h"
#include "GameManager.h"
#include <OgreEntity.h>
#include "Player.h"
#include "BodyPart.h"
#include "EnemyPatternManager.h"
#include <OgreLogManager.h>


Enemy::Enemy()
	:enemyHealth(10),
	enemySpeed(50),
	enemyMaxHealth(0),
	enemeyDamage(0),
	enemyMaxDamage(0),
	aggroRange(0),
	attackRange(0),
	isDead(false),
	isDead2(false)
{
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	GameManager& mgr = GameManager::GetSingleton();
	startPosition = (0, 0, 20);

	// Create an enemy entity with the right mesh
	enemyEntity = mgr.mSceneMgr->createEntity("OgreEnemy.mesh");

	// Add the node to the scene
	enemyNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(startPosition);
	enemyNode->attachObject(enemyEntity);

	SetHealth(10);


	//Set aggroRange and attackRange of the enemy
	EnemyPatternManager enemyPatternManager;
	enemyPatternManager.BasicEnemy();

	aggroRange = enemyPatternManager.setAggroR();
	attackRange = enemyPatternManager.setAttackR();

}

void Enemy::Update(const Ogre::FrameEvent& evt)
{
	 Move(evt);

	 //GetDamaged(1);
}

void Enemy::SetHealth(float startingHealth)
{
	enemyMaxHealth = startingHealth;
	enemyHealth = enemyMaxHealth;
}

void Enemy::DoDamage(float damage)
{
	enemyMaxDamage = damage;
	enemeyDamage = enemyMaxDamage;
}

void Enemy::GetDamaged(float damage)
{
	enemyHealth -= damage;

	if (enemyHealth <= 0)
	{
		isDead = true;
	}
}

void Enemy::DropBodyPart()
{
	if (isDead)
	{
		// TODO drop bodypart logic
	}
}

void Enemy::Move(const Ogre::FrameEvent& evt)
{
	GameManager& mgr = GameManager::GetSingleton();


	//Ogre::Vector3 offset = (0, -20, 0);

	Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition() + Ogre::Vector3(0, 20, 0);

	//target = Ogre::Vector3(target.x, 20, target.z);
	Ogre::Vector3 MoveDirection = Ogre::Vector3::ZERO;

	Ogre::Vector3 distanceVector = target - enemyNode->getPosition();
	float distance = distanceVector.length();
	//Ogre::LogManager::getSingletonPtr()->logMessage("distanceVector pre move =" + Ogre::StringConverter::toString(distanceVector));
	//Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(distance));

	if (distance <= aggroRange){

		/*if (distance <= enemySpeed / 2500)
		{
			enemyNode->setPosition(target);
		}*/

		enemyNode->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);

		if (distance > attackRange)
		{
			MoveDirection.z = enemySpeed;
			//Ogre::LogManager::getSingletonPtr()->logMessage("distanceVector =" + Ogre::StringConverter::toString(distanceVector));
			distanceVector.normalise();
			//Ogre::LogManager::getSingletonPtr()->logMessage("normalised distanceVector =" + Ogre::StringConverter::toString(distanceVector));

			enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
			Ogre::LogManager::getSingletonPtr()->logMessage("distance =" + Ogre::StringConverter::toString(distance));
			Ogre::LogManager::getSingletonPtr()->logMessage("attackrange =" + Ogre::StringConverter::toString(attackRange));

			
			//enemyNode->translate(distanceVector * enemySpeed * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
		}

		//Dodge when player attacks, implement when the player doesnt attack in a circle

		/*else if(attackRange - distance <= enemySpeed)
		{
			float dodgeOutcome = Ogre::Math::RangeRandom(0, 3);

			Ogre::LogManager::getSingletonPtr()->logMessage("dodgeOutcome =" + Ogre::StringConverter::toString(dodgeOutcome));


			if (dodgeOutcome <= 1)
			{
				//enemyNode->translate((enemyNode->getPosition() + (100,0,0)) * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
				Ogre::LogManager::getSingletonPtr()->logMessage("beforeDodge" + Ogre::StringConverter::toString(enemyNode->getPosition()));
				enemyNode->setPosition(enemyNode->getPosition() + Ogre::Vector3(50,0,0));
				Ogre::LogManager::getSingletonPtr()->logMessage("afterDodge" + Ogre::StringConverter::toString(enemyNode->getPosition()));

			}
		}*/

		else
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("stopDistance =" + Ogre::StringConverter::toString(distance));

			MoveDirection.z = -enemySpeed;

			enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

		}
	}
	else if(distance > aggroRange && enemyNode->getPosition() != startPosition)
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
}

void Enemy::Die()
{
	/*GameManager& mgr = GameManager::GetSingleton();
	
	BodyPart bodyPart;
	if (isDead){
		bodyPart.Spawn();
		isDead = false;*/

		/*mgr.mSceneMgr->getSceneNode("Enemy")->removeAndDestroyAllChildren();
		mgr.mSceneMgr->destroySceneNode(mgr.mSceneMgr->getSceneNode("Enemy"));*/
	/*}*/
}


