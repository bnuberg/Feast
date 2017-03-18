
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include "EntityTest.h"
#include "MainCamera.h"

class Main
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
	EntityTest* test;
	MainCamera* mMainCamera;
};


