#include "Enemy.h"
#include "EnemyAI.h"
#include "GameManager.h"
#include <OgreEntity.h>
#include "BodyPart.h"
#include "EnemyPatternManager.h"
#include <OgreLogManager.h>
#include "Grid.h"
#include "SoundManager.h"

int enemyCount = 0;

Enemy::Enemy()
	:enemySpeed(50),
	enemyBaseSpeed(50),
	enemyDamage(0),
	enemyMaxDamage(0),
	aggroRange(0),
	attackRange(0),
	attackTimer(2000),
	is_dead_(false),
	is_dead2_(false),
	scale(1),
	bleedTick(0),
	maxBleedTick(5),
	bleed_Timer_Max(1000),
	slow_Timer_Max(5000)
{
	health = 10;
	maxHealth = 0;
}

Enemy::Enemy(float health, float speed, float damage, Ogre::Vector3 sPosition, float scale)
{
	SetStartPosition(sPosition);
	SetScale(scale);
	SetMaxHealth(health);
	enemyBaseSpeed = speed;
	SetSpeed(speed);
	enemyDamage = damage;
	enemyMaxDamage = damage;
}


Enemy::~Enemy()
{
}

void Enemy::Init(int lvl)
{
	
	GameManager& mgr = GameManager::GetSingleton();

	enemyID = ++mgr.mEnemyManager.totalEnemyID;

	startPosition = GetStartPosition();

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

	level = lvl;
	
	// Add the node to the scene
	enemyNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID), fakeStartPosition);

	//Creates enemy parts with nodes and attach meshes
	torsoNode = enemyNode->createChildSceneNode("EnemyTorsoNode" + Ogre::StringConverter::toString(enemyID), torsoSocketPosition);
	Ogre::Entity* torsoEntity = GameManager::getSingleton().mSceneMgr->createEntity(torsoMeshName);
	torsoNode->attachObject(torsoEntity);
	torsoNode->setScale(scale * characterScale, scale * characterScale, scale * characterScale);

	headNode = torsoNode->createChildSceneNode("EnemyHeadNode" + Ogre::StringConverter::toString(enemyID), headSocketPosition);
	Ogre::Entity* headEntity = GameManager::getSingleton().mSceneMgr->createEntity(headMeshName);
	headNode->attachObject(headEntity);

	leftArmNode = torsoNode->createChildSceneNode("EnemyLeftArmNode" + Ogre::StringConverter::toString(enemyID), leftArmSocketPosition);
	Ogre::Entity* leftArmEntity = GameManager::getSingleton().mSceneMgr->createEntity(armMeshName);
	leftArmNode->attachObject(leftArmEntity);

	rightArmNode = torsoNode->createChildSceneNode("EnemyRightArmNode" + Ogre::StringConverter::toString(enemyID), rightArmSocketPosition);
	Ogre::Entity* rightArmEntity = GameManager::getSingleton().mSceneMgr->createEntity(armMeshName);
	rightArmNode->attachObject(rightArmEntity);

	leftFootNode = torsoNode->createChildSceneNode("EnemyLeftFootNode" + Ogre::StringConverter::toString(enemyID), leftFootSocketPosition);
	Ogre::Entity* leftFootEntity = GameManager::getSingleton().mSceneMgr->createEntity(footMeshName);
	leftFootNode->attachObject(leftFootEntity);

	rightFootNode = torsoNode->createChildSceneNode("EnemyRightFootNode" + Ogre::StringConverter::toString(enemyID), rightFootSocketPosition);
	Ogre::Entity* rightFootEntity = GameManager::getSingleton().mSceneMgr->createEntity(footMeshName);
	rightFootNode->attachObject(rightFootEntity);

	epm = new EnemyPatternManager();
	epm->createTravelGrid();

	healthBarNode = mgr.mSceneMgr->getSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID))->createChildSceneNode("healthBarNode" + Ogre::StringConverter::toString(enemyID), healthBarPosition);
	healthbar.Init(healthBarNode, healthBarPosition, mgr.mSceneMgr, enemyID);

	// right arm origin
	Ogre::Vector3 rightarmoffset = Ogre::Vector3(30, shoulderHeight, 0);
	erightarmOrigin = mgr.mSceneMgr->getSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID))->createChildSceneNode("erightarmOrigin" + Ogre::StringConverter::toString(enemyID), fakeStartPosition + rightarmoffset);
	erightarmNode = mgr.mSceneMgr->getSceneNode("EnemyNode" + Ogre::StringConverter::toString(enemyID))->createChildSceneNode("erightarmNode" + Ogre::StringConverter::toString(enemyID), fakeStartPosition + rightarmoffset);
	erightarmNode->setScale(5, 5, 5);
	enemyEquipment.EnemyEquipArm(erightarmNode, enemyID, level);
	enemyAI.SetArm(enemyEquipment.arm);
	// rocket arm target
	Ogre::Vector3 rocketarmtargetoffset = Ogre::Vector3(0, 0, -500);
	rocketarmtargetNode = enemyNode->createChildSceneNode(fakeStartPosition - rocketarmtargetoffset);

	// All nodes added, translate enemy to start position
	enemyNode->translate(startPosition, Ogre::Node::TS_LOCAL);


	SetMaxHealth(10);


	//Set aggroRange and attackRange of the enemy
	EnemyPatternManager enemyPatternManager;
	enemyPatternManager.BasicEnemy();

	timer_.reset();
	attackRange = enemyPatternManager.setAttackR();
	aggroRange = enemyPatternManager.setAggroR();
	attackRange = enemyPatternManager.setAttackR();
	SetStats();
	timer_.reset();
	attackDelay.reset();
	enemyAI.Init();
}

void Enemy::Update(const Ogre::FrameEvent& evt)
{
	Move(evt);
	
	enemyAI.StateSelecter(evt, enemyNode);
	enemyAI.enemyDodgeCheck(evt, enemyNode);
	
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
				attackDelay.reset();
			}
		}
	}
	if (enemyAI.AllowedToAttack())
	{
		if (attackDelay.getMilliseconds() > attackTimer)
		{
			InitiateAbility();
		}
	}

	enemyAI.isAttacking = isAttacking;
	enemyAI.StateSelecter(evt, enemyNode); 
	enemyAI.enemyDodgeCheck(evt, enemyNode);
	 
	Debuff();
}

void Enemy::InitiateAbility()
{
	enemyEquipment.arm.equippedByEnemy = true;
	enemyEquipment.arm.enemyID = enemyID;
	if (!isAttacking)
	{
		//equipment.arm.type = 1;
		
		if (enemyEquipment.arm.type == 0)
		{
			enemyEquipment.arm.AbilityTarget(erightarmOrigin->getPosition() - Ogre::Vector3(0, shoulderHeight, 0));
			enemyEquipment.arm.AbilityGlobalTarget(erightarmOrigin->_getDerivedPosition() - Ogre::Vector3(0, shoulderHeight, 0));
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

/**	Set the health and speed based on the level
*/
void Enemy::SetStats()
{
	SetMaxHealth(10 * level);
	enemySpeed = 40 + 5 * level;
	SetHealth(10 * level);
	enemyAI.enemySpeed = 50 + 5 * level;
}

void Enemy::Debuff()
{
	if (is_bleeding)
	{
		BleedEnemy();
	}

	if (is_slowed)
	{
		SlowEnemy();
	}

}

void Enemy::StartBleeding(int damage)
{
	GameManager& mgr = GameManager::GetSingleton();
	is_bleeding = true;
	bleedTimer.reset();
	bleedDamage = (damage / 2) / maxBleedTick;
	
	if (bleedParticle == NULL){
		bleedParticle = mgr.mSceneMgr->createParticleSystem("bleeded" + Ogre::StringConverter::toString(enemyID), "BleedParticle");
	}
	enemyNode->attachObject(bleedParticle);

}

void Enemy::RemoveBleeding()
{
	is_bleeding = false;
	enemyNode->detachObject("bleeded" + Ogre::StringConverter::toString(enemyID));
}

void Enemy::BleedEnemy()
{
	if (bleedTimer.getMilliseconds() >= bleed_Timer_Max)
	{
		GetDamaged(bleedDamage);

		bleedTimer.reset();
		bleedTick++;
	}

	if (bleedTick >= maxBleedTick)
	{
		RemoveBleeding();
	}
}

void Enemy::StartSlow()
{

	GameManager& mgr = GameManager::GetSingleton();
	is_slowed = true;
	slowTimer.reset();
	SetSpeed(enemyBaseSpeed / 2);

	if (slowParticle == NULL){
		slowParticle = mgr.mSceneMgr->createParticleSystem("slowed" + Ogre::StringConverter::toString(enemyID), "SlowParticle");
	}
	enemyNode->attachObject(slowParticle);
}

void Enemy::RemoveSlow()
{
	is_slowed = false;
	enemyNode->detachObject("slowed" + Ogre::StringConverter::toString(enemyID));
	SetSpeed(enemyBaseSpeed);



}

void Enemy::SlowEnemy()
{

	if (slowTimer.getMilliseconds() >= slow_Timer_Max)
	{
		RemoveSlow();
	}

}

void Enemy::Knockback()
{

}

void Enemy::SetSpeed(float speed)
{
	enemySpeed = speed;
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
	enemyDamage = enemyMaxDamage;
}

void Enemy::GetDamaged(float damage)
{
	health -= damage;
	healthbar.SetLength(health, maxHealth);

	SoundManager::GetSingleton().PlaySound("EnemyHit.wav");

	if (health <= 0)
	{
		is_dead_ = true;
		healthbar.Destroy();
	}
}

Ogre::Vector3 Enemy::GetStartPosition() const
{
	return startPosition;
}

void Enemy::SetStartPosition(Ogre::Vector3 position)
{
	startPosition = position;
}

float Enemy::GetScale() const
{
	return scale;
}

void Enemy::SetScale(float scale)
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

	Ogre::Vector3 distanceVector = target - enemyNode->getPosition();
	float distance = distanceVector.length();

	if (distance <= aggroRange)
	{
		epm->updateStartAndEndPositions(enemyNode->getPosition(), target, enemyNumber);
		std::vector<Ogre::Vector3> route = epm->getRoute();
		
		if (route.size() > 0)
		{
			enemyNode->lookAt(route[0], Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
		}
		else
		{
			enemyNode->lookAt(target, Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_Z);
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
		enemyNode->translate(MoveDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	}
	else if (enemyNode->getPosition() != startPosition)
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
	}
}

void Enemy::Die()
{
	DetachBodyParts();
	is_dead2_ = true;
	/*GameManager& mgr = GameManager::GetSingleton();
	
	BodyPart bodyPart;
	if (isDead){
		bodyPart.Spawn();
		isDead = false;*/

		/*mgr.mSceneMgr->getSceneNode("Enemy")->removeAndDestroyAllChildren();
		mgr.mSceneMgr->destroySceneNode(mgr.mSceneMgr->getSceneNode("Enemy"));*/
	/*}*/
}

/**
 * \brief Detaches all the body parts so that the body parts are removed from the scene
 */
void Enemy::DetachBodyParts() const
{
	enemyNode->detachAllObjects();
	erightarmNode->detachAllObjects();
	healthBarNode->detachAllObjects();
	torsoNode->detachAllObjects();
	headNode->detachAllObjects();
	leftArmNode->detachAllObjects();
	rightArmNode->detachAllObjects();
	leftFootNode->detachAllObjects();
	rightFootNode->detachAllObjects();	
}
