#pragma once
#include "MainCamera.h"
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include "IScene.h"



class MainMenuScene: IScene
{
public:
	MainMenuScene();
	~MainMenuScene();
	MainCamera* mainCamera;
	
	void CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow) override;
	void Update();
};

