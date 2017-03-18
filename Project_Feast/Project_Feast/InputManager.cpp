#include "InputManager.h"
#include <OgreLogManager.h>


InputManager::InputManager()
	: mInputManager(0),
	  mMouse(0),
	  mKeyboard(0)
{
}


InputManager::~InputManager()
{
}

void InputManager::InitInput()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);
}
