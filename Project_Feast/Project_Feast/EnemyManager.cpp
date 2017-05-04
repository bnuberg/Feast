#include "EnemyManager.h"
#include "BodyPartManager.h"
#include "GameManager.h"


EnemyManager::EnemyManager()
	:enemy_spawn_timer_(5000)
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	// Make sure the timer starts from 0
	timer_.reset();
}

void EnemyManager::Update(const Ogre::FrameEvent& evt)
{
	// When the timer reaches the spawn timer, spawn an enemy and reset the timer
	if (timer_.getMilliseconds() >= enemy_spawn_timer_)
	{
		SpawnEnemy();
		timer_.reset();
	}

	for (std::list<Enemy>::iterator e = enemy_list_.begin(); e != enemy_list_.end(); ++e)
	{
		e->Update(evt);
	}
}

// Spawns a new enemy and adds it to the manager
void EnemyManager::SpawnEnemy()
{
	Enemy enemy;
	enemy.Init();

	enemy_list_.push_back(enemy);
}

/**	This function damages all the enemies within a given distance around a given point.
	@param The center point around which the enemies are damaged.
	@param The distance from the point in which the enemies are damaged.
*/
void EnemyManager::DamageEnemiesInCircle(Ogre::Vector3 center, float killdistance)
{
	GameManager& mgr = GameManager::getSingleton();

	// The iterator is used to go over all the enmies in the list
	std::list<Enemy>::iterator e = enemy_list_.begin();
	while (e != enemy_list_.end())
	{
		// If the enemy isn't dead damage it
		if (!e->is_dead_)
		{
			Ogre::Vector3 distanceVector = center - e->enemy_node_->getPosition();
			float distance = distanceVector.length();

			if (distance < killdistance)
			{
				e->GetDamaged(10);
			}

		}

		// If the enemy is dead but not yet removed remove him.
		if (e->is_dead_ && !e->is_dead2_)
		{
			mgr.mBodyPartManager.Spawn(e->enemy_node_->getPosition());
			// Spawn bodypart

			// Remove all objects and take it out of the list
			e->enemy_node_->detachAllObjects();
			e->is_dead2_ = true;
			enemy_list_.erase(e++);
			// Spawn meat
			Meat meat;
			meat.Spawn(e->enemyNode->getPosition());

			meatList.push_back(meat);

			// TODO: fix remove enemys
		}
		else
		{
			++e;
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