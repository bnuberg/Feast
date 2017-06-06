#include "Enemy.h"
#include "EnemyAI.h"
#include "GameManager.h"
#include <OgreEntity.h>
#include "Player.h"
#include "BodyPart.h"

#include "EnemyPatternManager.h"
#include <OgreLogManager.h>
#include "Grid.h"


int enemyCount = 0;

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
	//Init();
	SetHealth(health);
	enemySpeed = speed;
	enemeyDamage = damage;
	enemyMaxDamage = damage;
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	GameManager& mgr = GameManager::GetSingleton();

	enemyID = ++mgr.mEnemyManager.totalEnemyID;

	startPosition = getStartPosition();

	enemyNumber = enemyCount++;

	int width = 21;
	int height = 21;
	int wo2 = width / 2;
	int ho2 = height / 2;

	Grid * blockageGrid = Grid::getInstance(width, height);

	if (!blockageGrid->initialized)
	{
		for (int i = -wo2; i <= wo2; i++)
		{
			for (int j = -ho2; j <= ho2; j++)
			{
				if (i % 3 == 0 && j % 3 != 0)
					blockageGrid->setBlockageAt(Ogre::Vector2(i, j));
			}
		}
	}

	startPosition = (0, 0, 20);
	
	// Create an enemy entity with the right mesh
	enemyEntity = mgr.mSceneMgr->createEntity("boletus.mesh");

	// Add the node to the scene
	enemy_node_ = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID), fakeStartPosition);
	enemy_node_->setPosition(fakeStartPosition);
	enemy_node_->resetOrientation();
	enemy_node_->setScale(scale, scale, scale);
	enemy_node_->attachObject(enemyEntity);

	epm = new EnemyPatternManager();
	epm->createTravelGrid();

	// right arm origin
	enemyHeight = 50;
	Ogre::Vector3 rightarmoffset = Ogre::Vector3(30, enemyHeight, 0);
	erightarmOrigin = mgr.mSceneMgr->getSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID))->createChildSceneNode("erightarmOrigin" + Ogre::StringConverter::toString(enemyID), fakeStartPosition + rightarmoffset);
	erightarmNode = mgr.mSceneMgr->getSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID))->createChildSceneNode("erightarmNode" + Ogre::StringConverter::toString(enemyID), fakeStartPosition + rightarmoffset);
	erightarmNode->setScale(0.2, 0.2, 0.2);
	enemyEquipment.EnemyEquipArm(erightarmNode);
	//SetEquipment();
	//Ogre::Entity* erightarmEntity = GameManager::getSingleton().mSceneMgr->createEntity("cube.mesh");

	//erightarmNode->attachObject(erightarmEntity);

	// rocket arm target
	Ogre::Vector3 rocketarmtargetoffset = Ogre::Vector3(0, 0, -500);
	rocketarmtargetNode = enemy_node_->createChildSceneNode(fakeStartPosition - rocketarmtargetoffset);

	// All nodes added, translate enemy to start position
	enemy_node_->translate(startPosition, Ogre::Node::TS_LOCAL);


	SetHealth(10);


	//Set aggroRange and attackRange of the enemy
	EnemyPatternManager enemyPatternManager;
	enemyPatternManager.BasicEnemy();

	timer_.reset();
	attackRange = enemyPatternManager.setAttackR();
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

	Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition();

	Ogre::Vector3 MoveDirection = Ogre::Vector3::ZERO;

	Ogre::Vector3 distanceVector = target - enemy_node_->getPosition();
	float distance = distanceVector.length();

	if (distance <= aggroRange)
	{
		epm->updateStartAndEndPositions(enemy_node_->getPosition(), target, enemyNumber);
		std::vector<Ogre::Vector3> route = epm->getRoute();
		
		if (route.size() > 0)
		{
			enemy_node_->lookAt(route[0], Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
		}
		else
		{
			enemy_node_->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
			Ogre::LogManager::getSingletonPtr()->logMessage("Route not found.");
		}

		if (distance > attackRange)
		{
			MoveDirection.z = enemySpeed;
		}
		else
		{
			MoveDirection.z = -enemySpeed;
		}
		enemy_node_->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	}
	else if (enemy_node_->getPosition() != startPosition)
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


