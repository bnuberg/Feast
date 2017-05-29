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
	is_dead2_(false)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	GameManager& mgr = GameManager::GetSingleton();
	startPosition = (0, 0, 0);
	
	// Create an enemy entity with the right mesh
	enemyEntity = mgr.mSceneMgr->createEntity("boletus.mesh");

	// Add the node to the scene
	enemy_node_ = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(startPosition);
	enemy_node_->attachObject(enemyEntity);

	SetHealth(10);
	timer_.reset();
}

void Enemy::Update(const Ogre::FrameEvent& evt)
{
	EnemyAI enemyAI;
	enemyAI.StateSelecter(evt, enemy_node_);
	enemyAI.enemyDodge(evt, enemy_node_);
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
		is_dead_ = true;
	}
}

void Enemy::DropBodyPart()
{
	if (is_dead_)
	{
		// TODO drop bodypart logic
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


