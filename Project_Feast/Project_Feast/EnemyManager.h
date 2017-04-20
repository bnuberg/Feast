#pragma once
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreTimer.h>
#include "Enemy.h"
#include "BodyPart.h"
#include "Meat.h"
#include "GameManager.h"

// Creates and tracks all the enemy instances and bodypart instances
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void EnemyManager::Init();
	void EnemyManager::Update(const Ogre::FrameEvent& evt);
	void SpawnEnemy();
	void DamageEnemies();

private:
	std::list<Enemy> enemyList;				// List containing all enemies
	std::list<BodyPart> bodyPartsList;		// List containing all bodypart objects
	std::list<Meat> meatList;				// List containing all meat objects
	Ogre::Timer timer;						// Ogre timer class object
	unsigned long enemySpawnTimer;			// The duration it takes for an enemy to spawn
};

