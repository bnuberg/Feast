/*
	The enemymanager was chosen to be used because there are many enemies in the game at the same time.
	All these enemies have to be continuously updated, they are stored in a list because the amount of enemies is not fixed.
	The enemymanager also handles generic methods such as finding and damaging enemies in a circle and spawning the enemies.
*/

#pragma once
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreTimer.h>
#include "Enemy.h"
#include "Meat.h"

/** Creates and tracks all the enemy instances and bodypart instances
*/
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void EnemyManager::Init();
	void EnemyManager::Update(const Ogre::FrameEvent& evt);
	void SpawnEnemy(Ogre::Vector3 position);
	void SpawnHeavyEnemy(Ogre::Vector3 position);
	void SpawnLightEnemy(Ogre::Vector3 position);
	void DamageEnemiesInCircle(Ogre::Vector3 center, float killdistance);
	void DamageEnemies();
	float IterateMeat(Ogre::Vector3 center, float pickupDistance);

private:
	std::list<Enemy> enemy_list_;		// List containing all enemies
	Ogre::Timer timer_;							// Ogre timer class object
	unsigned long enemy_spawn_timer_;			// The duration it takes for an enemy to spawn
	std::vector<Meat> meatList;					// List containing all meat objects
};

