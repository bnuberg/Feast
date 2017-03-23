#include "Enemy.h"
#include "GameManager.h"
#include <OgreEntity.h>
#include "Player.h"
#include "BodyPart.h"


Enemy::Enemy()
	:enemyHealth(10),
	enemySpeed(50),
	enemyMaxHealth(0),
	enemeyDamage(0),
	enemyMaxDamage(0),
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
	startPosition = (0, 0, 0);

	// Create an enemy entity with the right mesh
	enemyEntity = mgr.mSceneMgr->createEntity("ogrehead.mesh");

	// Add the node to the scene
	enemyNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode(startPosition);
	enemyNode->attachObject(enemyEntity);

	SetHealth(10);
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

	Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition();

	Ogre::Vector3 distanceVector = target - enemyNode->getPosition();
	float distance = distanceVector.length();
	
	//Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(distance));

	if (distance <= enemySpeed / 2500)
	{
		enemyNode->setPosition(target);
	}
	else
	{
		distanceVector.normalise();

		enemyNode->translate(distanceVector * enemySpeed * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
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


