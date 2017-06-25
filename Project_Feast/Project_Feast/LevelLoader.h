#pragma once

#include "MainMenuScene.h"
#include <SdkCameraMan.h>
#include "GameScene.h"
#include "DeathScene.h"

enum SceneEnum
{
	MainMenu, Level1, DeathScreen
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
	DeathScene deathScene;
	
	void InitMainMenuScene();
	void InitScene2();
	void UpdateScene();
	
	
};

