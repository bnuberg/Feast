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
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Enemy Manager update call ***");

	if (timer.getMilliseconds() > enemySpawnTimer)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("*** Spawn Enemy ***");

		SpawnEnemy();
		timer.reset();
	}

	for each (Enemy e in enemyList)
	{
		e.Update(evt);
	}
}

void EnemyManager::SpawnEnemy()
{
	Enemy enemy;
	enemy.Init();

	Ogre::LogManager::getSingletonPtr()->logMessage("*** Enemy initialized ***");

	enemyList.push_back(enemy);
}

