#include "MainCamera.h"

MainCamera::MainCamera()
{
}


MainCamera::~MainCamera()
{
}

void MainCamera::CameraInstance()
{
	GameManager& mgr = GameManager::getSingleton();

	mgr.mCamera = mgr.mSceneMgr->createCamera("MainCam");

	mgr.mCamera->lookAt(0, 200, 300);
	mgr.mCamera->setPosition(0, 0, 0);
	mgr.mCamera->setNearClipDistance(5);
}
