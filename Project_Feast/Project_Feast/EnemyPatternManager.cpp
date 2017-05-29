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
unsigned long EnemyPatternManager::setAttackT()
{
	return attackTimer;
}

void EnemyPatternManager::attackPattern()
{
	//if (Ogre::Entity* ENEMYARM == GameManager::getSingleton().mSceneMgr->createEntity(MESHNAME)){
		//aggroRange = 400;
		//attackRange = 100;
		//attackTimer = 5000;
	//}
	//if (Ogre::Entity* ENEMYARM == GameManager::getSingleton().mSceneMgr->createEntity(MESHNAME)){
	//	aggroRange = 600;
	//	attackRange = 250;
	//	attackTimer = 10000;
	//}
	//if (Ogre::Entity* ENEMYARM == GameManager::getSingleton().mSceneMgr->createEntity(MESHNAME)){
	//	aggroRange = 500;
	//	attackRange = 100;
	//	attackTimer = 70000;
	//}


	
}


