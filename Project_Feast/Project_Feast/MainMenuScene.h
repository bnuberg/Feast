#pragma once
#include "MainCamera.h"
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include "IScene.h"

namespace OgreBites {
	class SdkCameraMan;
}

class MainMenuScene: IScene
{
public:
	MainMenuScene();
	~MainMenuScene();
	
	
	void CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow) override;
};

