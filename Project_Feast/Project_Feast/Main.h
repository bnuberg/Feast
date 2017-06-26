#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include "Player.h"
#include "MainCamera.h"
#include "InputManager.h"
#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include "UI.h"
#include "LevelLoader.h"

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
	/*Ogre::RenderWindow* mWindow;*/
	Player player;
	UI ui;
	/*MainCamera* mMainCamera;*/
	OgreBites::SdkCameraMan* mCameraMan;      // basic camera controller
	LevelLoader levelLoader;
	Ogre::OverlaySystem *mOverlaySystem;
	
		// OgreBites
		
		
	
	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
	bool processUnbufferedInput(const Ogre::FrameEvent& fe);
	
};


