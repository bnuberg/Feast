#include "GameScene.h"
#include <OgreLight.h>
#include "GameManager.h"
#include <SdkCameraMan.h>

#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include "SoundManager.h"
#include "Dungeon.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

void GameScene::CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow)
{
	GameManager& mgr = GameManager::getSingleton();
	mainCamera->CameraInstance();

	mgr.cameraMan = new OgreBites::SdkCameraMan(mgr.mCamera);   // create a default camera controller
	mgr.cameraMan->setStyle(OgreBites::CameraStyle::CS_ORBIT);

	Ogre::Viewport* vp = mWindow->addViewport(mgr.mCamera);
	
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	mgr.mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//---Create the scene---
	materialLoader.LoadMaterials();
	Dungeon* dungeon = new Dungeon(sceneManager);

	// Instantiate the player
	mgr.player.Init(dungeon->GetPlayerSpawnPoint());

	// Initialize the enemy manager
	mgr.mEnemyManager.Init();

	// Bind the cameraman to the player
	mgr.cameraMan->setTarget(sceneManager->getSceneNode("CameraNode"));

	mgr.ui.Init();
}

void GameScene::Update()
{
	GameManager& mgr = GameManager::getSingleton();

	mgr.ui.ShowHud(mgr.player);
	mgr.cameraMan->setYawPitchDist(Ogre::Radian(0), Ogre::Radian(0.2), Ogre::Real(680));
}

