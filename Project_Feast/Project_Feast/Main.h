
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include "Player.h"
#include "MainCamera.h"
#include "InputManager.h"
#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include "Menu.h"

class Main : public Ogre::FrameListener, Ogre::WindowEventListener, OgreBites::SdkTrayListener
{
public:
	Main();
	virtual ~Main();

	bool go();

protected:
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Player player;
	MainCamera* mMainCamera;
	OgreBites::SdkCameraMan* mCameraMan;      // basic camera controller
	Menu menu;
	Ogre::OverlaySystem *mOverlaySystem;
		// OgreBites
		OgreBites::InputContext mInputContext;
		OgreBites::SdkTrayManager* mTrayMgr;
		OgreBites::ParamsPanel* mDetailsPanel;    // sample details panel
		OgreBites::Label* mLabel;    // sample details panel
	
	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
	bool processUnbufferedInput(const Ogre::FrameEvent& fe);
	
};


