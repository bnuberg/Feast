#include "GameScene.h"
#include "GameManager.h"
#include <SdkCameraMan.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include "SoundManager.h"
#include "Dungeon.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

void GameScene::CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow)
{
	GameManager& mgr = GameManager::getSingleton();
	//---Create the scene---
	
	if (mgr.reset == false){
		dungeon = new Dungeon(sceneManager);
	}
	// Instantiate the player
	mgr.player.Init(dungeon->GetPlayerSpawnPoint());

	// Initialize the enemy manager
	mgr.mEnemyManager.Init();

	// Bind the cameraman to the player

	if (mgr.reset == false){
		mgr.cameraMan->setTarget(sceneManager->getSceneNode("CameraNode"));
		auto cameraNode = sceneManager->getSceneNode("CameraNode");
		cameraNode->translate(0, 20, 60);
		cameraNode->lookAt(Ogre::Vector3(0, -5, -40), Ogre::Node::TS_LOCAL);
		mgr.ui.Init();
	}
}

void GameScene::Update()
{
	GameManager& mgr = GameManager::getSingleton();
	/*Ogre::LogManager::getSingletonPtr()->logMessage("Update this");*/
	mgr.ui.ShowHud(mgr.player);
	mgr.cameraMan->setYawPitchDist(Ogre::Radian(0), Ogre::Radian(0.1), Ogre::Real(680));
	
}

