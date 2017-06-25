#include "UI.h"
#include "GameManager.h"

/*
This class contains all the UI related code. It has the framestats inside, 
the different popup messages for picking object up and the tutorial messages, 
it also shows values like your health, meat, arm damage, current wave, and the wave timer.
We have chosen to use the basic ogre UI inside this project, because this was one of the most feasible options.
A lot of UI plugins are depricated and making a UI yourself takes a lot of time.
We decided to refactor the main class and put UI into a seperate class becuase the main needs to be clean and UI has a lot of code for a few elements.
*/

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
	//mTrayMgr->showFrameStats(OgreBites::TL_TOPLEFT);
	mTrayMgr->hideCursor();

	Ogre::StringVector items;
	items.push_back("Health");
	items.push_back("Meat");
	items.push_back("Wave");
	items.push_back("Wave timer");

	mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT, "DetailsPanel", 200, items);
	mDetailsPanel->setParamValue(0, "Health");
	mDetailsPanel->setParamValue(1, "Meat");
	mDetailsPanel->setParamValue(2, "Wave");
	mDetailsPanel->setParamValue(3, "WaveTime");

	mLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "Text", "Press 'E' to interact", 200);
	mLabel->hide();

	mTutorialLabel1 = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mTutorialLabel1", "Press LMB to attack", 250);
	mTutorialLabel2 = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mTutorialLabel2", "Use space + any direction to dash", 350);
	mTutorialLabel3 = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mTutorialLabel3", "You've been damaged, use 'f' to heal", 350);
	mTutorialLabel4 = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mTutorialLabel4", "An enemy has spawned, attack him", 330);
	mTutorialLabel5 = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mTutorialLabel5", "The first wave will spawn in a few seconds, get ready!", 500);
	
}

void UI::ShowHud(Player player)
{
	GameManager& mgr = GameManager::getSingleton();

	if (!mgr.mEnemyManager.tutorial.isFinished)
	{
		mTutorialLabel1->hide();
		mTutorialLabel2->hide();
		mTutorialLabel3->hide();
		mTutorialLabel4->hide();
		mTutorialLabel5->hide();
		mTrayMgr->clearTray(OgreBites::TL_CENTER);

		switch (mgr.mEnemyManager.tutorial.tutorialPart)
		{
		case 1 :
			mTrayMgr->moveWidgetToTray("mTutorialLabel1", OgreBites::TL_CENTER);
			mTutorialLabel1->show();
			break;
		case 2 :
			mTrayMgr->moveWidgetToTray("mTutorialLabel2", OgreBites::TL_CENTER);
			mTutorialLabel2->show();
			break;
		case 3 :
			mTrayMgr->moveWidgetToTray("mTutorialLabel3", OgreBites::TL_CENTER);
			mTutorialLabel3->show();
			break;
		case 4 :
			mTrayMgr->moveWidgetToTray("mTutorialLabel4", OgreBites::TL_CENTER);
			mTutorialLabel4->show();
			break;
		case 5 :
			mTrayMgr->moveWidgetToTray("mTutorialLabel5", OgreBites::TL_CENTER);
			mTutorialLabel5->show();
			break;
		default:
			break;
		}
	}
	else
	{
		mTutorialLabel5->hide();

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
	}

	if (!mTrayMgr->isDialogVisible())
	{
		/*camera->frameRenderingQueued(evt); */  // if dialog isn't up, then update the camera
		if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
		{
			mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(player.GetHealth()));
			mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(player.GetMeat()));
			mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mgr.mEnemyManager.waveCount));
			mDetailsPanel->setParamValue(3, (Ogre::StringConverter::toString(mgr.mEnemyManager.waveTimeSpent) + "s"));
		}
	}
}
