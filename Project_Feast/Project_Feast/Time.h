#include <OgreFrameListener.h>

class Time
{
public:
	static float deltaTime;
	static float unscaledDeltaTime;
	static float timeScale;
	void Update(const Ogre::FrameEvent& evt);
};