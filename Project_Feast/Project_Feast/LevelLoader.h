#pragma once

#include "MainMenuScene.h"
#include <SdkCameraMan.h>
#include "GameScene.h"

enum SceneEnum
{
	MainMenu, Level1
};

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();
	SceneEnum sceneEnum;
	void InitLevelLoader();
	void LoadScene();
	MainMenuScene MainMenuScene;
	GameScene gameScene;
	
	void InitMainMenuScene();
	void InitScene2();
	void UpdateScene();
	
	
};

