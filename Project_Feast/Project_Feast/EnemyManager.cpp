#include "EnemyManager.h"
#include "BodyPartManager.h"
#include "GameManager.h"


EnemyManager::EnemyManager()
	:enemy_spawn_timer_(5000),
	bleedTick(1000)
{
	enemySpawnPoints[0] = Ogre::Vector3(0, 0, 1500);
	enemySpawnPoints[1] = Ogre::Vector3(1500, 0, 0);
	enemySpawnPoints[2] = Ogre::Vector3(-1500, 0, 0);
	enemySpawnPoints[3] = Ogre::Vector3(300, 0, -1200);
	enemySpawnPoints[4] = Ogre::Vector3(-300, 0, -1200);
	//BodyPartManager bodyPartManager;
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
	GameManager& mgr = GameManager::getSingleton();
	if (mgr.reset)
	{
		resetEnemies = true;
		waveCount = 0;
	}
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
			mgr.mBodyPartManager.despawnTimer.reset();
			mgr.mBodyPartManager.despawnActive = true;
			Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(waveTimeSpent));
			timer_.reset();
		}
		if (mgr.mBodyPartManager.despawnActive)
		{
			mgr.mBodyPartManager.DespawnBodyparts();
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
		if (waveCount >= 5)
		{
			mgr.player.Win();
		}
	}

	e = enemy_list_.begin();
	while (e != enemy_list_.end())
	{
		e->Update(evt);
		Ogre::LogManager::getSingletonPtr()->logMessage("enemyID" + Ogre::StringConverter::toString(e->enemyID));
		Ogre::LogManager::getSingletonPtr()->logMessage("enemy modifier" + Ogre::StringConverter::toString(e->enemyEquipment.modifier));
		if (resetEnemies)
		{
		
			e->GetDamaged(1000);
			
		}
		// If the enemy is dead but not yet removed remove him.
		if (e->is_dead_ && !e->is_dead2_)
		{
			// Spawn meat
			SpawnMeat(e->enemyNode->getPosition());

			// Spawn bodypart
			mgr.mBodyPartManager.DropArm(e->enemyNode->getPosition(), e->enemyEquipment.arm);

			// Remove all objects and take it out of the list
			e->Die();
			enemy_list_.erase(e++);
		}
		else
		{
			++e;
		}
	}
	if (e == enemy_list_.end())
	{
		resetEnemies = false;
	}

}

void EnemyManager::SpawnMeat(Ogre::Vector3 position)
{
	Meat meat;
	meat.Spawn(position);
	meatList.push_back(meat);
}

int EnemyManager::GetEnemyCount()
{
	return enemy_list_.size();
}

/**	Spawns the wave of enemies, resets the timer and updates the wavecount
*/
void EnemyManager::SpawnWave()
{
	waveCount++;
	int enemyCount = waveCount + 1;
	
	if (enemyCount > numberOfEnemies) enemyCount = numberOfEnemies;

	for (int i = 0; i < enemyCount; i++)
	{
		SpawnEnemy(enemySpawnPoints[i], SetLevel());
	}

	waveAliveTimer.reset();
	isWaveAlive = true;
}

/**	Sets the enemy level based on the time it took to complete the wave
*/
int EnemyManager::SetLevel()
{
	if (waveCount == 1) return waveCount;

	int level = waveCount; 

	// if the wave was completed in less than a minute give a chance to increase the difficulty
	if (waveAliveTimer.getMilliseconds() <= 60000)
	{
		if (RandomPercent() <= waveDifficultyIncreaseChance)
		{
			level++;
		}
	}
	// if it took long than 2 minutes give a chance to make it easier
	else if (waveAliveTimer.getMilliseconds() >= 120000)
	{
		if (RandomPercent() <= waveDifficultyDecreaseChance)
		{
			level--;
		}
	}

	return level;
}

int EnemyManager::RandomPercent()
{
	//Returns a random number between 1 and 100.
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 100);
	return dist(mt);
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
		if (distance < pickupDistance)
		{
			b->bodyPartNode->detachAllObjects();
			b = meatList.erase(b);
			return 10;
		}
		++b;
	}
	return 0;
}

// Spawns a new enemy and adds it to the manager
void EnemyManager::SpawnEnemy(Ogre::Vector3 position, int level)
{
	Enemy enemy;
	enemy.SetStartPosition(position);
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
void EnemyManager::DamageEnemiesInCircle(Ogre::Vector3 center, float killDistance, int damage, int modifier)
{
	/*GameManager& mgr = GameManager::getSingleton();*/

	// The iterator is used to go over all the enmies in the list
	for (std::list<Enemy>::iterator e = enemy_list_.begin(); e != enemy_list_.end(); ++e)
	{
		// If the enemy isn't dead damage it
		if (!e->is_dead_)
		{
			Ogre::Vector3 distanceVector = center - e->enemyNode->getPosition();
			float distance = distanceVector.length();

			if (distance < killDistance)
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