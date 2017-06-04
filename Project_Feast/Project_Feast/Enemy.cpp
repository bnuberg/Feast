#include "Enemy.h"
#include "EnemyAI.h"
#include "GameManager.h"
#include <OgreEntity.h>
#include "Player.h"
#include "BodyPart.h"
#include "EnemyPatternManager.h"
#include <OgreLogManager.h>
#include <OgreParticleSystem.h>


Enemy::Enemy()
	:enemyHealth(10),
	enemySpeed(50),
	enemyBaseSpeed(50),
	enemyMaxHealth(0),
	enemeyDamage(0),
	enemyMaxDamage(0),
	is_dead_(false),
	is_dead2_(false),
	scale(1),
	bleedTick(0),
	maxBleedTick(5),
	bleed_Timer_Max(1000),
	slow_Timer_Max(5000)
{
}

Enemy::Enemy(float health, float speed, float damage, Ogre::Vector3 sPosition, float scale)
{
	setStartPosition(sPosition);
	setScale(scale);
	SetHealth(health);
	enemyBaseSpeed = speed;
	SetSpeed(speed);
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
	enemyEquipment.EnemyEquipArm(erightarmNode, enemyID, level);
	enemyAI.SetArm(enemyEquipment.arm);
	// rocket arm target
	Ogre::Vector3 rocketarmtargetoffset = Ogre::Vector3(0, 0, -500);
	rocketarmtargetNode = enemy_node_->createChildSceneNode(fakeStartPosition - rocketarmtargetoffset);

	// All nodes added, translate enemy to start position
	enemy_node_->translate(startPosition, Ogre::Node::TS_LOCAL);

	SetStats();
	timer_.reset();
	enemyAI.Init();
}

void Enemy::Update(const Ogre::FrameEvent& evt)
{
	
	enemyAI.StateSelecter(evt, enemy_node_);
	enemyAI.enemyDodgeCheck(evt, enemy_node_);
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
	 if (enemyAI.AllowedToAttack())
	 {
		 InitiateAbility();
	 }
	 Debuff();

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
	SetHealth(10 * level);
	enemySpeed = 40 + 5 * level;
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
	enemy_node_->attachObject(bleedParticle);

}

void Enemy::RemoveBleeding()
{
	is_bleeding = false;
	enemy_node_->detachObject("bleeded" + Ogre::StringConverter::toString(enemyID));
}

void Enemy::BleedEnemy()
{
	if (bleedTimer.getMilliseconds() >= bleed_Timer_Max)
	{
		GetDamaged(bleedDamage);
		//Ogre::LogManager::getSingletonPtr()->logMessage("after bleed health" + Ogre::StringConverter::toString(enemyHealth));

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
	enemy_node_->attachObject(slowParticle);
}

void Enemy::RemoveSlow()
{
	is_slowed = false;
	enemy_node_->detachObject("slowed" + Ogre::StringConverter::toString(enemyID));
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

void Enemy::SetHealth(float startingHealth)
{
	enemyMaxHealth = startingHealth;
	enemyHealth = enemyMaxHealth;
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


