#include "InputManager.h"
#include <OgreLogManager.h>
#include <OgreRenderWindow.h>


InputManager::InputManager()
	: mMouse(0),
	  mKeyboard(0)
{
}


InputManager::~InputManager()
{
}

void InputManager::InitInput(Ogre::RenderWindow* mWindow, OIS::InputManager* mInputManager)
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

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, false));
	
	
}
