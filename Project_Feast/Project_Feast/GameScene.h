#pragma once
#include "IScene.h"
#include "MainCamera.h"
#include "MaterialLoader.h"

class GameScene:IScene
{
public:
	GameScene();
	~GameScene();
	MainCamera* mainCamera;
	MaterialLoader materialLoader;
	void CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow) override;
	void Update();
};

