#include "Main.h"

#include <OgreRenderWindow.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include "GameManager.h"
#include <OgreWindowEventUtilities.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreMeshManager.h>
#include "SoundManager.h"

Main::Main()
:mRoot(0),
//mWindow(0),
mCameraMan(0),
mResourcesCfg(Ogre::StringUtil::BLANK),
mPluginsCfg(Ogre::StringUtil::BLANK)
{
	
}

Main::~Main()
{
	delete mRoot;
}

bool Main::go()
{
#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif
	char const* c = getenv("RESOURCE_HOME");
	
	mRoot = new Ogre::Root(mPluginsCfg);

	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);
	
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;

	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	//Adds a new resource folder declared by the enviroment variable RESOURCE_HOME 
	if (c == NULL)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Please execute the MEDIA_HOME.bat file in the /resources folder");
	}
	else
	{
		Ogre::String s(c);
		Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(s, "FileSystem", "General");
	}
	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;
	// Calls the Singleton GameManager 
	new GameManager();
	GameManager& mgr = GameManager::getSingleton();
	mgr.mWindow = mRoot->initialise(true, "Main");

	new SoundManager(); //Instantiates the SoundManager
	SoundManager::getSingleton().PlaySound("ActionMusic.wav", true); //Starts the music loop
	mgr.mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	
	// initialize the OverlaySystem (changed for 1.9)
	mOverlaySystem = new Ogre::OverlaySystem();
	mgr.mSceneMgr->addRenderQueueListener(mOverlaySystem);
	mgr.mInputManager.InitInput(mgr.mWindow);
	levelLoader.InitLevelLoader();
	levelLoader.LoadScene();
	
	mRoot->addFrameListener(this);
	mRoot->startRendering();
	return true;
}

bool Main::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	GameManager& mgr = GameManager::getSingleton();
	if (mgr.mWindow->isClosed())
		return false;

	//Need to capture/update each device
	mgr.mInputManager.mKeyboard->capture();
	mgr.mInputManager.mMouse->capture();	
	mgr.mEnemyManager.Update(evt);
	mgr.ui.mTrayMgr->frameRenderingQueued(evt);

	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;
	if (!processUnbufferedInput(evt))
		return false;
	levelLoader.UpdateScene();
	/*mCameraMan->frameRenderingQueued(evt);*/
	return true;
}

bool Main::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
	GameManager& mgr = GameManager::getSingleton();

	if (mgr.player.exists)
	{
		mgr.player.Update(evt);
	}

	return true;
}

//Main 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		Main app;

		try {
			app.go();
		}
		catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif

