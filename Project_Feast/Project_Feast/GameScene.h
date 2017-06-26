#pragma once
#include "IScene.h"
#include "MainCamera.h"
#include "MaterialLoader.h"
#include "Dungeon.h"

class GameScene:IScene
{
public:
	GameScene();
	~GameScene();
	MainCamera* mainCamera;
	MaterialLoader materialLoader;
	Dungeon* dungeon;
	void CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow) override;
	void Update();
	
};

