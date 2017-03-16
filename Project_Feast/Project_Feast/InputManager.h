#pragma once
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
class InputManager : public OIS::KeyListener, public OIS::MouseListener
{
public:
	InputManager();
	~InputManager();
	void InitInput();
protected:
	OIS::InputManager* mInputManager;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;
};

