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
	sceneEnum = SceneEnum::MainMenu;
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
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_RETURN) && sceneEnum == MainMenu)
	{
		MainMenuScene.startLabel = 0;
		delete MainMenuScene.mTrayMgrMenu;
		MainMenuScene.mTrayMgrMenu = 0;
		sceneEnum = Level1;
		LoadScene();

	}
	if (sceneEnum == MainMenu)
	{
		MainMenuScene.Update();
	}
	else if (sceneEnum == Level1)
	{
		/*Ogre::LogManager::getSingletonPtr()->logMessage("Update this");*/
		gameScene.Update();
	}
	
}


