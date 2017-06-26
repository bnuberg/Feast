#include "Tutorial.h"
#include "GameManager.h"


Tutorial::Tutorial()
{
}


Tutorial::~Tutorial()
{
}

void Tutorial::Init()
{
	tutorialPart++;
	GameManager& mgr = GameManager::getSingleton();
	if (mgr.reset)
	{
		tutorialPart = 0;
		tutorialPart++;
	}
}

void Tutorial::Update()
{
	GameManager& mgr = GameManager::getSingleton();
	auto ms = mgr.mInputManager.mMouse->getMouseState();
	
	if (ms.buttonDown(OIS::MB_Left) && tutorialPart == 1)
	{
		tutorialPart = 2;
	}

	if (tutorialPart > 1 && mgr.player.GetMeat() <= 5)
	{
		mgr.player.IncreaseMeat(10);
	}

	if ((mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_A) || mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_D)) && tutorialPart == 2)
	{
		if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_SPACE))
		{
			tutorialPart = 3;
			mgr.player.DecreaseHealth(9);
		}
	}

	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_F) && tutorialPart == 3)
	{
		mgr.mEnemyManager.SpawnEnemy(Ogre::Vector3(0, 0, -500), 1);
		tutorialPart = 4;
	}

	if (mgr.mEnemyManager.GetEnemyCount() <= 0 && tutorialPart == 4)
	{
		tutorialPart = 5;
		finishedTimer.reset();
	}

	if (tutorialPart == 5 && finishedTimer.getMilliseconds() >= countdown)
	{
		isFinished = true;	
	}
}