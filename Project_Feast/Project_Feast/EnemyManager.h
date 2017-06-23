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
#include "Tutorial.h"

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
	void DamageEnemiesInCircle(Ogre::Vector3 center, float killdistance, int damage);
	void DamageEnemies();
	int SetLevel();
	int RandomPercent();

	float IterateMeat(Ogre::Vector3 center, float pickupDistance);
	void BodypartToAdd();
	int totalEnemyID = 0;
	bool isWaveAlive = false;
	int waveCount = 0;
	float waveTimeSpent;

	int GetEnemyCount();
	Tutorial tutorial;

private:
	void EnemyManager::SpawnWave();
	Ogre::Vector3 enemySpawnPoints[5];
	std::list<Enemy> enemy_list_;				// List containing all enemies
	Ogre::Timer timer_;							// Ogre timer class object
	Ogre::Timer waveAliveTimer;
	unsigned long enemy_spawn_timer_;			// The duration it takes for an enemy to spawn
	std::vector<Meat> meatList;					// List containing all meat objects

	int waveDifficultyIncreaseChance = 60;
	int waveDifficultyDecreaseChance = 40;
};

