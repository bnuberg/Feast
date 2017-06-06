#include "LevelLoader.h"
#include "GameManager.h"



LevelLoader::LevelLoader()
{
}


LevelLoader::~LevelLoader()
{

}

void LevelLoader::InitLevelLoader()
{
	sceneEnum = SceneEnum::Level1;
}

void LevelLoader::LoadScene()
{
	GameManager& mgr = GameManager::getSingleton();
	switch(sceneEnum){
	case MainMenu:
		{
			MainMenuScene.CreateScene(mgr.mSceneMgr, mgr.mWindow);
			break;
		}
	case Level1:
		{
			gameScene.CreateScene(mgr.mSceneMgr, mgr.mWindow);
			break;
		}
	
	}

	
}

void LevelLoader::InitMainMenuScene()
{
	sceneEnum = SceneEnum::MainMenu;
}

void LevelLoader::InitScene2()
{
	sceneEnum = SceneEnum::Level1;
}

void LevelLoader::UpdateScene()
{
	GameManager& mgr = GameManager::getSingleton();
	switch (sceneEnum)
	{
		case MainMenu:
		{
			break;
		}
		case Level1:
		{
			gameScene.Update();
			break;
		}

	}
}


