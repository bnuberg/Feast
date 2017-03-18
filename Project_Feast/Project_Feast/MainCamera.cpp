#include "MainCamera.h"

MainCamera::MainCamera()
	
{
}


MainCamera::~MainCamera()
{
}

void MainCamera::CameraInstance()
{
	/*new GameManager();*/
	GameManager& mgr = GameManager::getSingleton();
	GameManager* pMgr = GameManager::getSingletonPtr();

	mgr.mCamera = mgr.mSceneMgr->createCamera("MainCam");

	mgr.mCamera->setPosition(0, 0, 80);
	mgr.mCamera->lookAt(0, 0, -300);
	mgr.mCamera->setNearClipDistance(5);
}
