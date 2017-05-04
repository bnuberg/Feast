#include "EnemyPatternManager.h"

EnemyPatternManager::EnemyPatternManager()
	:aggroRange(0),
	 attackRange(0)
{	
	
}	

EnemyPatternManager::~EnemyPatternManager()
{

}

void EnemyPatternManager::BasicEnemy()
{
	//Override enemy movement
	//Variable aggro range on enemy type
	aggroRange = 500;
	attackRange = 100;
	//Enemy moves towards player when player is in aggro range
	//Enemy moves sideways when player is in attack range
	//Enemy moves away if the player gets too close
	//Enemy loses interest in player if the player moves out of aggro range for a certain amount of time
}

float EnemyPatternManager::setAggroR()
{

	return aggroRange;
}

float EnemyPatternManager::setAttackR()
{

	return attackRange;
}


