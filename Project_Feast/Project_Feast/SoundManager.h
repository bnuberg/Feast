#pragma once
#include <OgreSingleton.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
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
	void PlaySound(char* fileName, bool loop = false);

private:
	irrklang::ISoundEngine* engine; 
	const char* path = getenv("RESOURCE_HOME");
	const char* soundFolder = "/Sound/";
};


