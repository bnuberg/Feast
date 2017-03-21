
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include "Player.h"
#include "MainCamera.h"
#include "InputManager.h"
#include "Enemy.h"

#include <SdkCameraMan.h>


class Main: public Ogre::FrameListener, Ogre::WindowEventListener
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
	Enemy enemy;
	OgreBites::SdkCameraMan* mCameraMan;      // basic camera controller
	
	
	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
	bool processUnbufferedInput(const Ogre::FrameEvent& fe);
	
};


