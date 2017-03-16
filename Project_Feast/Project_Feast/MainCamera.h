#pragma once
#include <OgreCamera.h>
#include "GameManager.h"


class MainCamera: public Ogre::Camera
{
public:
	MainCamera();
	~MainCamera();

	void CameraInstance();
	

protected:
	Ogre::Camera* mCamera;
};

