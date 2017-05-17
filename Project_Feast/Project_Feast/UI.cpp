#include "UI.h"
#include "GameManager.h"


UI::UI()
{
}


UI::~UI()
{
}

void UI::Init()
{
	Ogre::Root& root = Ogre::Root::getSingleton();
	GameManager& mgr = GameManager::getSingleton();
	mInputContext.mKeyboard = mgr.mInputManager.mKeyboard;
	mInputContext.mMouse = mgr.mInputManager.mMouse;

	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mgr.mWindow, mInputContext, this);
	mTrayMgr->showFrameStats(OgreBites::TL_TOPLEFT);
	mTrayMgr->hideCursor();

	Ogre::StringVector items;
	items.push_back("Health");
	items.push_back("Meat");

	mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT, "DetailsPanel", 200, items);
	mDetailsPanel->setParamValue(0, "Health");
	mDetailsPanel->setParamValue(1, "Meat");

	mLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "Text", "Press 'E' to interact", 200);
	
}

void UI::ShowHud(Player player)
{
	GameManager& mgr = GameManager::getSingleton();
	
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_E))
	{
		mLabel->hide();
		mTrayMgr->clearTray(OgreBites::TL_CENTER);
	}

	if (mgr.mBodyPartManager.show_label_ == true)
	{
		mTrayMgr->moveWidgetToTray("Text", OgreBites::TL_CENTER);
		mLabel->show();
	}
	else if (mgr.mBodyPartManager.show_label_ == false)
	{
		mLabel->hide();
		mTrayMgr->clearTray(OgreBites::TL_CENTER);
	}

	if (!mTrayMgr->isDialogVisible())
	{
		/*camera->frameRenderingQueued(evt); */  // if dialog isn't up, then update the camera
		if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
		{
			mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(player.GetHealth()));
			mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(player.GetMeat()));
			
		}
	}
}



