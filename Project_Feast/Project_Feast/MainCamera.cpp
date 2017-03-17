#include "MainCamera.h"

MainCamera::MainCamera()
	: Camera("MainCam", mSceneMgr), mCamera(0)
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

	mCamera = mgr.mSceneMgr->createCamera("MainCam");

	mCamera->setPosition(0, 0, 80);
	mCamera->lookAt(0, 0, -300);
	mCamera->setNearClipDistance(5);
}
