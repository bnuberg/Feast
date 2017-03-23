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
	// Make sure the timer starts from 0
	timer.reset();
}

void EnemyManager::Update(const Ogre::FrameEvent& evt)
{
	GameManager& mgr = GameManager::getSingleton();

	// When the timer reaches the spawn timer, spawn an enemy and reset the timer
	if (timer.getMilliseconds() >= enemySpawnTimer)
	{
		SpawnEnemy();
		timer.reset();
	}

	/*for each (Enemy e in enemyList)
	{*/
		//if (e.isDead)
		//	break;

		//e.Update(evt);

		//e.isDead = true;

		//if (e.isDead)
		//{
		//	// TODO: spawn bodypart

		//	// TODO: remove enemys
		//	//e.enemyNode->detachAllObjects();
		//	/*enemyList.remove(e);*/
		//}
	/*}*/
}

// Spawns a new enemy and adds it to the manager
void EnemyManager::SpawnEnemy()
{
	Enemy enemy;
	enemy.Init();

	enemyList.push_back(enemy);
}

