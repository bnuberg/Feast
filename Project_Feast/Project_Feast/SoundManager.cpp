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
void SoundManager::PlaySound(char* fileName, bool loop) const
{
	char result[100];
	strcpy(result, path);
	strcat(result, soundFolder);
	strcat(result, fileName);
	engine->play2D(result, loop);
}

/** Plays a sound from the /Resources/Sound/ folder when given the filename with passed sound effects.\n
*	@param fileName is the name
*	@param loop is if the sound should loop
*	@param effect the sound effect you want on the soundclip
*/
void SoundManager::PlaySoundWithEffect(char* fileName, bool loop, Effects effect) const
{
	char result[100];
	strcpy(result, path);
	strcat(result, soundFolder);
	strcat(result, fileName);
	ISound* sound = engine->play2D(result, loop, false, true, ESM_AUTO_DETECT, true);
	
	if (effect == 0) return;

	ISoundEffectControl* fx = sound->getSoundEffectControl();

	switch(effect)
	{
	case SoundManager::Distortion:
		fx->enableDistortionSoundEffect();
		break;
	case SoundManager::Chorus:
		fx->enableChorusSoundEffect();
		break;
	case SoundManager::Echo:
		fx->enableEchoSoundEffect();
		break;
	case SoundManager::Flanger:
		fx->enableFlangerSoundEffect();
		break;
	case SoundManager::Gargle:
		fx->enableGargleSoundEffect();
		break;
	default:
		break;
	}	
}

