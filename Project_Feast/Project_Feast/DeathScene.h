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
	Ogre::Rectangle2D* rect;
	bool doOnce = false;
	bool doOnce2 = false;
	Ogre::SceneNode* node;
	/*OgreBites::SdkTrayManager* mTrayMgrDeath;
	OgreBites::InputContext mInputContext;
	OgreBites::Label* resetLabel;*/
};

