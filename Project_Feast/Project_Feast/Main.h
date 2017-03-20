
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include "Player.h"
#include "MainCamera.h"
#include "InputManager.h"


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
	InputManager mInputManager;
	OIS::InputManager* mInput;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;
	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	
};


