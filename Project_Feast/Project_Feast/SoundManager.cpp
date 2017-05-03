#include "SoundManager.h"

template<> SoundManager* Ogre::Singleton<SoundManager>::msSingleton = 0;

SoundManager::SoundManager()
{
	engine = irrklang::createIrrKlangDevice();
}

SoundManager::~SoundManager()
{
	engine->drop();
}

SoundManager* SoundManager::GetSingletonPtr(void)
{ 
	return msSingleton; 
}

SoundManager& SoundManager::GetSingleton(void)
{
	assert(msSingleton); 
	return (*msSingleton); 
}

void SoundManager::PlaySound(char* fileName, bool loop)
{
	char result[100];
	strcpy(result, path);
	strcat(result, fileName);
	engine->play2D(result, loop);
}

/*
Before you begin, add IrrKlang.dll to
	ogre/build/sdk/bin/debug

Change const char* path in SoundManager.h to your path of the sound folder

Then add this to Main.cpp
	new SoundManager();

Add these lines to the place where you want to play the sound
	SoundManager& sound = SoundManager::GetSingleton();
	sound.PlaySound();

*/