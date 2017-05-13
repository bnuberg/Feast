#include "Menu.h"
#include "GameManager.h"

Menu::Menu()
{
	
}

void Menu::Init()
{
	GameManager& mgr = GameManager::GetSingleton();

	mInputContext.mKeyboard = mgr.mInputManager.mKeyboard;
	mInputContext.mMouse = mgr.mInputManager.mMouse;

	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mgr.mWindow, mInputContext, this);
	mButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Play", "Play", 200);
	mButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Controls", "Controls", 200);
	mButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "Quit", "Quit", 200);
}

bool Menu::QuitApplication()
{
	GameManager& mgr = GameManager::GetSingleton();
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return true;
}

void Menu::StartApplication()
{

}

void Menu::ShowControls()
{
	GameManager& mgr = GameManager::GetSingleton();
	mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
}


Menu::~Menu()
{
}
