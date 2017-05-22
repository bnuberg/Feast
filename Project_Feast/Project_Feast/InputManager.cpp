#include "InputManager.h"
#include <OgreLogManager.h>
#include <OgreRenderWindow.h>


InputManager::InputManager()
	: mMouse(0),
	  mKeyboard(0),
	  mInputManager(0)
{
}


InputManager::~InputManager()
{
	/*Ogre::WindowEventUtilities::removeWindowEventListener(mgr.mWindow, this);
	windowClosed(mgr.mWindow);*/
}

void InputManager::InitInput(Ogre::RenderWindow* mWindow)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);
	Ogre::LogManager::getSingletonPtr()->logMessage("*** We are here ***");

	try
	{
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, false));
	}
	catch (std::exception &e)
	{
		// Fail quietly. Seems not to work if there is no mouse or track-pad plugged in.
		std::cerr << e.what();
	}

	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
	
	
}

void InputManager::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void InputManager::windowClosed(Ogre::RenderWindow* rw)
{
	
	
		if (mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	
}
