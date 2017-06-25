#pragma once
#include "MainCamera.h"
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include "IScene.h"



class MainMenuScene : IScene, OgreBites::SdkTrayListener
{
public:
	MainMenuScene();
	~MainMenuScene();
	void CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow) override;
	void Update();

	MainCamera* mainCamera;
	OgreBites::SdkTrayManager* mTrayMgrMenu;
	OgreBites::InputContext mInputContext;
	OgreBites::Label* gameName;
	OgreBites::Label* startLabel;
};

