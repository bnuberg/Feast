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
		//enemySpawnTimer = 100000;
	}

	for (std::list<Enemy>::iterator e = enemyList.begin(); e != enemyList.end(); ++e)
	//for each (Enemy e in enemyList)
	{
		if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_SPACE))
		{
			if (!e->isDead)
			{
				Ogre::Vector3 target = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition();

				Ogre::Vector3 distanceVector = target - e->enemyNode->getPosition();
				float distance = distanceVector.length();

				if (distance < 200)
				{
					e->GetDamaged(10);
				}
			}
		}

		if (e->isDead && !e->isDead2)
		{
			// Spawn bodypart
			BodyPart bodypart;
			bodypart.Spawn(e->enemyNode->getPosition());

			bodyPartsList.push_back(bodypart);

			// Spawn meat
			Meat meat;
			meat.Spawn(e->enemyNode->getPosition());

			meatList.push_back(meat);

			// TODO: fix remove enemys
			e->enemyNode->detachAllObjects();
			e->isDead2 = true;
			//enemyList.remove(*e);
		}
		else
		{
			e->Update(evt);
		}
	}
}

// Spawns a new enemy and adds it to the manager
void EnemyManager::SpawnEnemy()
{
	Enemy enemy;
	enemy.Init();

	enemyList.push_back(enemy);
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