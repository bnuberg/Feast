#include "GameScene.h"
#include <OgreLight.h>
#include "GameManager.h"
#include <SdkCameraMan.h>

#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include "SoundManager.h"
#include "Dungeon.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

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
	Dungeon* dungeon = new Dungeon(sceneManager);

	// Create a player entity with the right mesh
	Ogre::Entity* playerEntity = GameManager::getSingleton().mSceneMgr->createEntity("Hammermesh", "RightArm_Hammer.mesh");

	// Add the node to the scene
	Ogre::Vector3 startingPosition = Ogre::Vector3(1000, -200, 50);
	Ogre::SceneNode* playerNode = sceneManager->getRootSceneNode()->createChildSceneNode("hammerarm", startingPosition);
	playerNode->attachObject(playerEntity);

	// Instantiate the player
	mgr.player.Init(dungeon->GetPlayerSpawnPoint());

	// Initialize the enemy manager
	mgr.mEnemyManager.Init();

	// Create an ambient light
	sceneManager->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
	Ogre::Light* light = sceneManager->createLight("MainLight");
	light->setPosition(20, 80, 50);

	// Bind the cameraman to the player
	mgr.cameraMan->setTarget(sceneManager->getSceneNode("PlayerHeadNode"));
	//mCameraMan->setYawPitchDist(Ogre::Radian(0), Ogre::Radian(1.0472), Ogre::Real(500));

	mgr.ui.Init();
}

void GameScene::Update()
{
	GameManager& mgr = GameManager::getSingleton();

	mgr.ui.ShowHud(mgr.player);
	
	//Ogre::Real dist = (mgr.mCamera->getPosition() - mCameraMan->getTarget()->_getDerivedPosition()).length();
	//mCameraMan->setYawPitchDist(mgr.mCamera->getOrientation().getYaw(), Ogre::Radian(1.0472), dist);
	mgr.cameraMan->setYawPitchDist(Ogre::Radian(0), Ogre::Radian(0.349066), Ogre::Real(380));
}

