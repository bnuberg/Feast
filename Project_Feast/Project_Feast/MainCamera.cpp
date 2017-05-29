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

	mgr.mCamera->setPosition(0, 0, 600);
	mgr.mCamera->lookAt(0, -100, -300);
	mgr.mCamera->setNearClipDistance(5);
}
