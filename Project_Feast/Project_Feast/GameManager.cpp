#include "GameManager.h"

template<> GameManager* Ogre::Singleton<GameManager>::msSingleton = 0;

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

GameManager& GameManager::GetSingleton()
{
	assert(msSingleton); 
	return *msSingleton;
}
