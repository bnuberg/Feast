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

	mgr.mCamera->lookAt(0, -100, 300);
	mgr.mCamera->setPosition(0, -200, -600);
	mgr.mCamera->setNearClipDistance(5);
}
