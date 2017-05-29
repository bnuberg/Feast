#include "Enemy.h"
#include "EnemyAI.h"
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
	enemyEquipment.EnemyEquipArm(erightarmNode);
	//SetEquipment();
	//Ogre::Entity* erightarmEntity = GameManager::getSingleton().mSceneMgr->createEntity("cube.mesh");

	//erightarmNode->attachObject(erightarmEntity);

	// rocket arm target
	Ogre::Vector3 rocketarmtargetoffset = Ogre::Vector3(0, 0, -500);
	rocketarmtargetNode = erightarmNode->createChildSceneNode(fakeStartPosition - rocketarmtargetoffset);

	// All nodes added, translate enemy to start position
	enemy_node_->translate(startPosition, Ogre::Node::TS_LOCAL);


	SetHealth(10);
	timer_.reset();


}

void Enemy::Update(const Ogre::FrameEvent& evt)
{
	EnemyAI enemyAI;
	enemyAI.StateSelecter(evt, enemy_node_);
	enemyAI.enemyDodge(evt, enemy_node_);
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

	{
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


