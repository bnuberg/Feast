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

/** Plays a sound from the /Resources/Sound/ folder when given the filename.\n
*	@param fileName is the name
*	@param loop is if the sound should loop
*/
void SoundManager::PlaySound(char* fileName, bool loop)
{
	char result[100];
	strcpy(result, path);
	strcat(result, soundFolder);
	strcat(result, fileName);
	engine->play2D(result, loop);
}

/*
Before you begin, add IrrKlang.dll to
	ogre/build/sdk/bin/debug

Then add this to Main.cpp
	new SoundManager();

Add these lines to the place where you want to play the sound
	SoundManager& sound = SoundManager::GetSingleton();
	sound.PlaySound("SpellCasting.wav");

	or

	SoundManager::GetSingleton().PlaySound("SpellCasting.wav");
*/