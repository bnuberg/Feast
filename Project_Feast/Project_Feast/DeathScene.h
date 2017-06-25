#pragma once
#include "IScene.h"
#include <InputContext.h>
#include <SdkTrays.h>

class DeathScene : IScene, OgreBites::SdkTrayListener
{
public:
	DeathScene();
	~DeathScene();
	void CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow) override;
	void Update();
	OgreBites::SdkTrayManager* mTrayMgrDeath;
	OgreBites::InputContext mInputContext;
	OgreBites::Label* resetLabel;
};

