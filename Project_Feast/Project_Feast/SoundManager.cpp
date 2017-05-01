#include "SoundManager.h"
#include <irrKlang.h>

template<> SoundManager* Ogre::Singleton<SoundManager>::msSingleton = 0;

SoundManager::SoundManager()
{
	engine = irrklang::createIrrKlangDevice();
}

SoundManager::~SoundManager()
{
	engine->drop();
}

SoundManager* SoundManager::GetSingletonPtr(void){ return msSingleton; }
SoundManager& SoundManager::GetSingleton(void){ assert(msSingleton); return (*msSingleton); }

void SoundManager::PlaySound(bool loop = false)
{
	engine->play2D("Random3.wav", loop);
}