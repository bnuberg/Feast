#include "GameManager.h"

template<> GameManager* Ogre::Singleton<GameManager>::msSingleton = 0;

GameManager::GameManager()
	:mSceneMgr(0),
	mInputManager(0),
	mCamera(0)
	
{
	
}

GameManager::~GameManager()
{
	
}

GameManager* GameManager::GetSingletonPtr(void)
{
	return msSingleton;
}
GameManager& GameManager::GetSingleton(void)
{
	assert(msSingleton); return (*msSingleton);
}
