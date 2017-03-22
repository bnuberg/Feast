#include "EnemyManager.h"


EnemyManager::EnemyManager()
	:enemySpawnTimer(5000)
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	timer.reset();
}

void EnemyManager::Update(const Ogre::FrameEvent& evt)
{
	if (timer.getMilliseconds() > enemySpawnTimer)
	{
		SpawnEnemy();
		timer.reset();
		enemySpawnTimer = 100000;
	}
}

void EnemyManager::SpawnEnemy()
{
	Enemy enemy;
	enemy.Init();

	enemyList.push_back(enemy);
}

