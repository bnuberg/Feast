#include "EnemyManager.h"
#include "EnemyAI.h"
#include "BodyPartManager.h"
#include "GameManager.h"


EnemyManager::EnemyManager()
	:enemy_spawn_timer_(5000),
	bleedTick(1000)
{
	enemySpawnPoints[0] = Ogre::Vector3(0, 0, 300);
	enemySpawnPoints[1] = Ogre::Vector3(200, 0, 100);
	enemySpawnPoints[2] = Ogre::Vector3(-200, 0, 100);
	enemySpawnPoints[3] = Ogre::Vector3(100, 0, 200);
	enemySpawnPoints[4] = Ogre::Vector3(-100, 0, 200);
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	// Make sure the timer starts from 0
	tutorial.Init();
	timer_.reset();
	bleedTimer.reset();
	waveAliveTimer.reset();
}

void EnemyManager::Update(const Ogre::FrameEvent& evt)
{
	GameManager& mgr = GameManager::getSingleton();

	if (!tutorial.isFinished)
	{
		tutorial.Update();
	}
	else
	{
	// When the timer reaches the spawn timer, spawn an enemy wave and reset the timer
	if (enemy_list_.size() <= 0 && isWaveAlive)
	{
		isWaveAlive = false;
		Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(waveTimeSpent));
		timer_.reset();
	}

	if (isWaveAlive)
	{
		waveTimeSpent = waveAliveTimer.getMilliseconds() / 1000;
	}

	if (timer_.getMilliseconds() >= enemy_spawn_timer_ && !isWaveAlive)
	{
		SpawnWave();

		timer_.reset();
	}
	}

	std::list<Enemy>::iterator e = enemy_list_.begin();
	while (e != enemy_list_.end())
	{
		e->Update(evt);
		Ogre::LogManager::getSingletonPtr()->logMessage("enemyID" + Ogre::StringConverter::toString(e->enemyID));
		Ogre::LogManager::getSingletonPtr()->logMessage("enemy modifier" + Ogre::StringConverter::toString(e->enemyEquipment.modifier));


		// If the enemy is dead but not yet removed remove him.
		if (e->is_dead_ && !e->is_dead2_)
		{
			// Spawn meat
			Meat meat;
			meat.Spawn(e->enemy_node_->getPosition());
			meatList.push_back(meat);

			// Spawn bodypart
			mgr.mBodyPartManager.DropArm(e->enemy_node_->getPosition(), e->enemyEquipment.arm);

			// Remove all objects and take it out of the list
			e->enemy_node_->detachAllObjects();
			e->erightarmNode->detachAllObjects();
			e->is_dead2_ = true;
			enemy_list_.erase(e++);
		}
		else
		{
			++e;
		}
		//


	}

}

int EnemyManager::GetEnemyCount()
{
	return enemy_list_.size();
}

void EnemyManager::SpawnWave()
{
	waveCount++;

	for (int i = 0; i < numberOfEnemies; i++)
	{
		enemyLevels[i] = waveCount;
	}

	int i = 0;
	for each (Ogre::Vector3 position in enemySpawnPoints)
	{
		SpawnEnemy(position, enemyLevels[i++]);
	}

	waveAliveTimer.reset();
	isWaveAlive = true;
}

float EnemyManager::IterateMeat(Ogre::Vector3 center, float pickupDistance)
{
	// Create a reference to the game manager
	GameManager& mgr = GameManager::getSingleton();

	std::vector<Meat>::iterator b = meatList.begin();
	while (b != meatList.end())
	{
		Ogre::Vector3 distanceVector = center - b->bodyPartNode->getPosition();

		float distance = distanceVector.length();
		/*Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(b->isPickupAble));*/
		if (distance < pickupDistance)
		{
			b->bodyPartNode->detachAllObjects();
			b = meatList.erase(b);
			return 5;
			/*bodyPartsList.erase(b++);*/
		}
		else
		{
			++b;
		}
	}
	return 0;
}

// Spawns a new enemy and adds it to the manager
void EnemyManager::SpawnEnemy(Ogre::Vector3 position, int level)
{
	Enemy enemy;
	enemy.setStartPosition(position);
	enemy.Init(level);
	enemy_list_.push_back(enemy);
}

void EnemyManager::SpawnHeavyEnemy(Ogre::Vector3 position, int level)
{
	//				hp  spd dmg position scale
	Enemy e = Enemy(20, 25, 10, position, 3.0f);
	e.Init(level);
	enemy_list_.push_back(e);
}

void EnemyManager::SpawnLightEnemy(Ogre::Vector3 position, int level)
{
	position.y = 0;
	Enemy e = Enemy(5, 75, 1, position, 0.5f);
	e.Init(level);
	enemy_list_.push_back(e);
}

/**	This function damages all the enemies within a given distance around a given point.
	@param The center point around which the enemies are damaged.
	@param The distance from the point in which the enemies are damaged.
*/
void EnemyManager::DamageEnemiesInCircle(Ogre::Vector3 center, float killdistance, int damage, int modifier)
{
	/*GameManager& mgr = GameManager::getSingleton();*/

	// The iterator is used to go over all the enmies in the list
	for (std::list<Enemy>::iterator e = enemy_list_.begin(); e != enemy_list_.end(); ++e)
	{
		// If the enemy isn't dead damage it
		if (!e->is_dead_)
		{
			Ogre::Vector3 distanceVector = center - e->enemy_node_->getPosition();
			float distance = distanceVector.length();

			if (distance < killdistance)
			{
				e->GetDamaged(damage);

				if (!e->is_bleeding && modifier == 1)
				{
					e->StartBleeding(damage);
				}
				if (!e->is_slowed && modifier == 2)
				{
					e->StartSlow();

				}
				
			}

		}
	}
}

void EnemyManager::DamageEnemies()
{
	for each (Enemy e in enemy_list_)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(e.is_dead_));
		if (!e.is_dead_)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("DAMAGE");
			
			e.is_dead_ = true;
		}
	}
}