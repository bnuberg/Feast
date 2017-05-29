#pragma once
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>


class InputManager : public Ogre::WindowEventListener
{
public:
	InputManager();
	~InputManager();
	void InitInput(Ogre::RenderWindow* mWindow);
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;
	OIS::KeyListener* mKeyListner;
protected:
	OIS::InputManager* mInputManager;
	

	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);
	
};

