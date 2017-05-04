
#pragma once
#include <OgreSingleton.h>
#include "InputManager.h"
#include "EnemyManager.h"
#include "BodyPartManager.h"
#include <OgreSceneManager.h>
#include <OgreCamera.h>


class GameManager: public Ogre::Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();
	static GameManager& GetSingleton(void);
	static GameManager* GetSingletonPtr(void);
	InputManager mInputManager;
	EnemyManager mEnemyManager;
	BodyPartManager mBodyPartManager;

	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::RenderWindow* mWindow;
	
};


