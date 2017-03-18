
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include "Player.h"

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
	Player* player;
};


