#pragma once
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreRenderWindow.h>
class InputManager : public OIS::KeyListener, public OIS::MouseListener
{
public:
	InputManager();
	~InputManager();
	void InitInput(Ogre::RenderWindow* mWindow, OIS::InputManager* mInputManager);
protected:
	/*OIS::InputManager* mInputManager;*/
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;
};

