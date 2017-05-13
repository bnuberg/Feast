#pragma once

#include <SdkTrays.h>

class Menu : OgreBites::SdkTrayListener
{
public:
	Menu();
	~Menu();
	void Init();
	bool QuitApplication();
	void StartApplication();
	void ShowControls();

protected:
	Ogre::OverlaySystem *mOverlaySystem;
	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager* mTrayMgr;
	OgreBites::Button* mButton;
};

