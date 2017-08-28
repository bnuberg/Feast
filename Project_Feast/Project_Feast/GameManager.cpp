#include "GameManager.h"

template<> GameManager* Ogre::Singleton<GameManager>::msSingleton = nullptr;

/** The GameManager is the class that gives you access to basic objects which you will need most of the time
*/
GameManager::GameManager()
	:mSceneMgr(0),
	mCamera(0),
	mWindow(0)
{
	
}

GameManager::~GameManager()
{
	
}

GameManager* GameManager::GetSingletonPtr()
{
	return msSingleton;
}

/** Returns the GameManager singleton, this gives you access to the Input, EnemyManager, UI, Player and more important objects
 * @return GameManager singleton
*/
GameManager& GameManager::GetSingleton()
{
	assert(msSingleton); 
	return *msSingleton;
}
