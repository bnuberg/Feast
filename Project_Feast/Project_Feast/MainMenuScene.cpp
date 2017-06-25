#include "MainMenuScene.h"
#include <OgreLight.h>
#include <SdkCameraMan.h>
#include "LevelLoader.h"


MainMenuScene::MainMenuScene()
{
}


MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow)
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

	mInputContext.mKeyboard = mgr.mInputManager.mKeyboard;
	mInputContext.mMouse = mgr.mInputManager.mMouse;

	mTrayMgrMenu = new OgreBites::SdkTrayManager("MainMenu", mgr.mWindow, mInputContext, this);
	mTrayMgrMenu->hideCursor();
	mTrayMgrMenu->setListener(this);
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MainMenu", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->getTechnique(0)->getPass(0)->createTextureUnitState("Krossroads.png");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	mTrayMgrMenu->showBackdrop("MainMenu");
	gameName = mTrayMgrMenu->createLabel(OgreBites::TL_TOP, "Feast", "Feast", 100);
	startLabel = mTrayMgrMenu->createLabel(OgreBites::TL_CENTER, "Start", "Press Enter to start", 200);

}

void MainMenuScene::Update()
{
	
}



