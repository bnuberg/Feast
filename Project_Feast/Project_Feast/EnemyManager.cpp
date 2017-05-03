#include "EnemyManager.h"
#include "BodyPartManager.h"
#include "GameManager.h"


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
	// When the timer reaches the spawn timer, spawn an enemy and reset the timer
	if (timer.getMilliseconds() >= enemySpawnTimer)
	{
		SpawnEnemy();
		timer.reset();
	}

	for (std::list<Enemy>::iterator e = enemyList.begin(); e != enemyList.end(); ++e)
	{
		e->Update(evt);
	}
}

// Spawns a new enemy and adds it to the manager
void EnemyManager::SpawnEnemy()
{
	Enemy enemy;
	enemy.Init();

	enemyList.push_back(enemy);
}

void EnemyManager::DamageEnemiesInCircle(Ogre::Vector3 center, float damageDistance)
{
	GameManager& mgr = GameManager::getSingleton();

	std::list<Enemy>::iterator e = enemyList.begin();
	while (e != enemyList.end())
	{
		if (!e->isDead)
		{
			Ogre::Vector3 distanceVector = center - e->enemyNode->getPosition();
			float distance = distanceVector.length();

			if (distance < damageDistance)
			{
				e->GetDamaged(10);
			}

		}

		if (e->isDead && !e->isDead2)
		{
			mgr.mBodyPartManager.Spawn(e->enemyNode->getPosition());

			e->enemyNode->detachAllObjects();
			e->isDead2 = true;
			enemyList.erase(e++);
		}
		else
		{
			++e;
		}
	}
}

void EnemyManager::DamageEnemies()
{
	for each (Enemy e in enemyList)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(e.isDead));
		if (!e.isDead)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("DAMAGE");
			
			e.isDead = true;
		}
	}
}