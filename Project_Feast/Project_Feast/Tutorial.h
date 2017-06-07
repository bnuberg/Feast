#pragma once

#include <OgreTimer.h>

class Tutorial
{
public:
	Tutorial();
	~Tutorial();

	void Init();
	void Update();

	int tutorialPart = 0;

	Ogre::Timer finishedTimer;
	unsigned long countdown = 5000;

	bool isFinished = false;
};

