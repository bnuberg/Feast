#pragma once
#include "IScene.h"
#include "MainCamera.h"

class GameScene:IScene
{
public:
	GameScene();
	~GameScene();
	MainCamera* mainCamera;
	void CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow) override;
	void Update();
};

