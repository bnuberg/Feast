#include "EnemyManager.h"
#include "EnemyAI.h"
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
		// 10 is probably too far away.
		//SpawnEnemy(Ogre::Vector3(4, 0, 4));
		//SpawnHeavyEnemy(Ogre::Vector3(400, 0, 700));
		//SpawnLightEnemy(Ogre::Vector3(100, 0, 300));
		timer_.reset();
	}

	for (std::list<Enemy>::iterator e = enemy_list_.begin(); e != enemy_list_.end(); ++e)
	{
		e->Update(evt);
	}
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
void EnemyManager::SpawnEnemy(Ogre::Vector3 position)
{
	Enemy enemy;
	enemy.setStartPosition(position);
	enemy.Init();
	enemy_list_.push_back(enemy);
}

void EnemyManager::SpawnHeavyEnemy(Ogre::Vector3 position)
{
	//				hp  spd dmg position scale
	Enemy e = Enemy(20, 25, 10, position, 3.0f);
	e.Init();
	enemy_list_.push_back(e);
}

void EnemyManager::SpawnLightEnemy(Ogre::Vector3 position)
{
	Enemy e = Enemy(5, 75, 1, position, 0.5f);
	e.Init();
	enemy_list_.push_back(e);
}

/**	This function damages all the enemies within a given distance around a given point.
	@param The center point around which the enemies are damaged.
	@param The distance from the point in which the enemies are damaged.
*/
void EnemyManager::DamageEnemiesInCircle(Ogre::Vector3 center, float killdistance, int damage)
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
				e->GetDamaged(damage);
			}

		}

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