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
	is_dead_(false),
	is_dead2_(false),
	scale(1)
{
}

Enemy::Enemy(float health, float speed, float damage, Ogre::Vector3 sPosition, float scale)
{
	setStartPosition(sPosition);
	setScale(scale);
	SetHealth(health);
	enemySpeed = speed;
	enemeyDamage = damage;
	enemyMaxDamage = damage;
}


Enemy::~Enemy()
{
}

void Enemy::Init(int lvl)
{
	GameManager& mgr = GameManager::GetSingleton();

	enemyID = ++mgr.mEnemyManager.totalEnemyID;
	level = lvl;

	// Create an enemy entity with the right mesh
	enemyEntity = mgr.mSceneMgr->createEntity("boletus.mesh");

	// Add the node to the scene
	enemy_node_ = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID), fakeStartPosition);
	enemy_node_->setPosition(fakeStartPosition);
	enemy_node_->resetOrientation();
	enemy_node_->setScale(scale, scale, scale);
	enemy_node_->attachObject(enemyEntity);

	// right arm origin
	enemyHeight = 50;
	Ogre::Vector3 rightarmoffset = Ogre::Vector3(30, enemyHeight, 0);
	erightarmOrigin = mgr.mSceneMgr->getSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID))->createChildSceneNode("erightarmOrigin" + Ogre::StringConverter::toString(enemyID), fakeStartPosition + rightarmoffset);
	erightarmNode = mgr.mSceneMgr->getSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID))->createChildSceneNode("erightarmNode" + Ogre::StringConverter::toString(enemyID), fakeStartPosition + rightarmoffset);
	erightarmNode->setScale(0.2, 0.2, 0.2);
	enemyEquipment.EnemyEquipArm(erightarmNode, level);

	// rocket arm target
	Ogre::Vector3 rocketarmtargetoffset = Ogre::Vector3(0, 0, -500);
	rocketarmtargetNode = enemy_node_->createChildSceneNode(fakeStartPosition - rocketarmtargetoffset);

	// All nodes added, translate enemy to start position
	enemy_node_->translate(startPosition, Ogre::Node::TS_LOCAL);

	SetStats();

	//Set aggroRange and attackRange of the enemy
	EnemyPatternManager enemyPatternManager;
	enemyPatternManager.BasicEnemy();

	aggroRange = enemyPatternManager.setAggroR();
	attackRange = enemyPatternManager.setAttackR();

}

void Enemy::Update(const Ogre::FrameEvent& evt)
{
	 Move(evt);

	 if (isAttacking)
	 {
		 if (attackDown)
		 {
			 if (enemyEquipment.arm.AbilityUpdate(erightarmNode, evt))
			 {
				 enemyEquipment.arm.AbilityDamage();
				 attackDown = false;
				 enemyEquipment.arm.AbilityTarget(erightarmOrigin->getPosition());
			 }
		 }
		 else
		 {
			 if (enemyEquipment.arm.AbilityUpdate(erightarmNode, evt))
			 {
				 isAttacking = false;
			 }
		 }
	 }

	 InitiateAbility();
}

void Enemy::InitiateAbility()
{
	enemyEquipment.arm.equippedByEnemy = true;
	if (!isAttacking)
	{
		//equipment.arm.type = 1;
		
		if (enemyEquipment.arm.type == 0)
		{
			enemyEquipment.arm.AbilityTarget(erightarmOrigin->getPosition() - Ogre::Vector3(0, enemyHeight, 0));
			enemyEquipment.arm.AbilityGlobalTarget(erightarmOrigin->_getDerivedPosition() - Ogre::Vector3(0, enemyHeight, 0));
		}
		else if (enemyEquipment.arm.type == 1)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("Enemy.cpp global target");
			Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(rocketarmtargetNode->_getDerivedPosition().x));
			Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(rocketarmtargetNode->_getDerivedPosition().y));
			Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(rocketarmtargetNode->_getDerivedPosition().z));
			enemyEquipment.arm.AbilityTarget(rocketarmtargetNode->getPosition());
			enemyEquipment.arm.AbilityGlobalTarget(rocketarmtargetNode->_getDerivedPosition());
		}

		isAttacking = true;
		attackDown = true;
	}
	else
	{
		// TODO: attack in progress
	}
}

void Enemy::SetStats()
{
	SetHealth(5 * level);
	enemySpeed = 40 + 5 * level;
}

void Enemy::SetHealth(float startingHealth)
{
	enemyMaxHealth = startingHealth;
	enemyHealth = enemyMaxHealth;
}

void Enemy::SetEquipmentMesh(Ogre::String meshName)
{
	//TODO: change mesh of arm to arm which the enemy will spawn with
	erightarmNode->detachAllObjects();
	Ogre::Entity* erightarmEntity = GameManager::getSingleton().mSceneMgr->createEntity(meshName);
	erightarmNode->attachObject(erightarmEntity);
}

void Enemy::SetEquipment()
{
	/*Ogre::String bodypartName;

	EnemyEquipment enemyequipment;
	bodypartName = enemyequipment.AssignRandomBodypart();
	Ogre::LogManager::getSingletonPtr()->logMessage("bodypartname:" + bodypartName);
	SetEquipmentMesh(bodypartName);*/


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
		is_dead_ = true;
	}
}

Ogre::Vector3 Enemy::getStartPosition()
{
	return startPosition;
}

void Enemy::setStartPosition(Ogre::Vector3 position)
{
	startPosition = position;
}

float Enemy::getScale()
{
	return scale;
}

void Enemy::setScale(float scale)
{
	this->scale = scale;
}

void Enemy::DropBodyPart()
{
	if (is_dead_)
	{
		// TODO drop body-part logic
	}
}

void Enemy::Move(const Ogre::FrameEvent& evt)
{
	GameManager& mgr = GameManager::GetSingleton();


	//Ogre::Vector3 offset = (0, -20, 0);

	Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition() /*+ Ogre::Vector3(0, 20, 0)*/;

	//target = Ogre::Vector3(target.x, 20, target.z);
	Ogre::Vector3 MoveDirection = Ogre::Vector3::ZERO;

	Ogre::Vector3 distanceVector = target - enemy_node_->getPosition();
	float distance = distanceVector.length();
	//Ogre::LogManager::getSingletonPtr()->logMessage("distanceVector pre move =" + Ogre::StringConverter::toString(distanceVector));
	//Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(distance));

	if (distance <= aggroRange)
	{

		/*if (distance <= enemySpeed / 2500)
		{
			enemyNode->setPosition(target);
		}*/

		enemy_node_->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);

		if (distance > attackRange)
		{
			MoveDirection.z = enemySpeed;
			//Ogre::LogManager::getSingletonPtr()->logMessage("distanceVector =" + Ogre::StringConverter::toString(distanceVector));
			distanceVector.normalise();
			//Ogre::LogManager::getSingletonPtr()->logMessage("normalised distanceVector =" + Ogre::StringConverter::toString(distanceVector));

			enemy_node_->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
		/*	Ogre::LogManager::getSingletonPtr()->logMessage("distance =" + Ogre::StringConverter::toString(distance));
			Ogre::LogManager::getSingletonPtr()->logMessage("attackrange =" + Ogre::StringConverter::toString(attackRange));*/

			
			//enemyNode->translate(distanceVector * enemySpeed * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
		}

		//Dodge when player attacks, implement when the player doesn't attack in a circle

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
			/*Ogre::LogManager::getSingletonPtr()->logMessage("stopDistance =" + Ogre::StringConverter::toString(distance));*/

			MoveDirection.z = -enemySpeed;

			enemy_node_->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

		}
	}
	else if (distance > aggroRange && enemy_node_->getPosition() != startPosition)
	{
		Ogre::Vector3 startDistanceVector = startPosition - enemy_node_->getPosition();
		float startDistance = startDistanceVector.length();


		enemy_node_->lookAt(startPosition, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);

		MoveDirection.z = enemySpeed;

		enemy_node_->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);


		if (startDistance <= enemySpeed / 2500)
		{
			enemy_node_->setPosition(startPosition);
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


