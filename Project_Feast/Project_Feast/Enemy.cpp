#include "Enemy.h"
#include "GameManager.h"
#include <OgreEntity.h>
#include "Player.h"
#include "BodyPart.h"


Enemy::Enemy()
	:enemyHealth(0),
	enemySpeed(0),
	enemyMaxHealth(0),
	enemeyDamage(0),
	enemyMaxDamage(0)
{
	
}


Enemy::~Enemy()
{
	delete this;
}

void Enemy::Init()
{
	GameManager& mgr = GameManager::GetSingleton();
	startPosition = (0, 0, 0);

	// Create a player entity with the right mesh
	Ogre::Entity* enemyEntity = mgr.mSceneMgr->createEntity("ogrehead.mesh");

	// Add the node to the scene
	Ogre::SceneNode* enemyNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("Enemy", startPosition);
	enemyNode->attachObject(enemyEntity);

	SetHealth(10);

}

void Enemy::Update(const Ogre::FrameEvent& evt)
{
	 Move(evt);

	 GetDamaged(1);
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
		Die();
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

	Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition();

	Ogre::Vector3 distanceVector = target - mgr.mSceneMgr->getSceneNode("Enemy")->getPosition();;
	enemySpeed = 10;
	float distance = distanceVector.length();
	
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(distance));

	if (distance <= enemySpeed / 2500)
	{
		mgr.mSceneMgr->getSceneNode("Enemy")->setPosition(target);

	}
	else
	{

		distanceVector.normalise();

		mgr.mSceneMgr->getSceneNode("Enemy")->translate(
			(distanceVector * enemySpeed) * evt.timeSinceLastFrame,
			Ogre::Node::TS_LOCAL);
		
	}
}

void Enemy::Die()
{
	GameManager& mgr = GameManager::GetSingleton();
	
	BodyPart bodyPart;
	if (isDead){
		bodyPart.Spawn();
		isDead = false;

		/*mgr.mSceneMgr->getSceneNode("Enemy")->removeAndDestroyAllChildren();
		mgr.mSceneMgr->destroySceneNode(mgr.mSceneMgr->getSceneNode("Enemy"));*/
	}
	

}


