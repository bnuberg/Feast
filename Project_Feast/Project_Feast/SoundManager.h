#pragma once
#include <OgreSingleton.h>
#include <irrKlang.h>

#pragma comment(lib, "irrKlang.lib")

using namespace std;
using namespace irrklang;

class SoundManager : public Ogre::Singleton<SoundManager>
{
public:
	SoundManager();
	~SoundManager();
	static SoundManager& GetSingleton(void);
	static SoundManager* GetSingletonPtr(void);
	void PlaySound(char* fileName, bool loop = false) const;
	enum Effects {None, Distortion, Chorus, Echo, Flanger, Gargle };
	void PlaySoundWithEffect(char* fileName, bool loop = false, Effects = Effects::None) const;

private:
	irrklang::ISoundEngine* engine; 
	const char* path = getenv("RESOURCE_HOME");
	const char* soundFolder = "/Sound/";
};