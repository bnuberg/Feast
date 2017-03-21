#include "Main.h"

#include <OgreRenderWindow.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include "GameManager.h"
#include <OgreWindowEventUtilities.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreCamera.h>



Main::Main()
:mRoot(0),
mWindow(0),
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

	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;

	mWindow = mRoot->initialise(true, "Main");

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// Calls the Singleton GameManager 
	new GameManager();
	GameManager& mgr = GameManager::getSingleton();
	

	mgr.mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	
	mMainCamera->CameraInstance();

	Ogre::Viewport* vp = mWindow->addViewport(mgr.mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	
	mgr.mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	//Create the scene

	Ogre::Entity* ogreHead = mgr.mSceneMgr->createEntity("Head", "ogrehead.mesh");
	
	Ogre::SceneNode* headNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);

	// Instantiate the player
	
	player.Init();

	mgr.mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	Ogre::Light* light = mgr.mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);
	
	mgr.mInputManager.InitInput(mWindow);
	

	mRoot->addFrameListener(this);
	mRoot->startRendering();
	
	return true;
}

bool Main::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mWindow->isClosed())
		return false;
	GameManager& mgr = GameManager::getSingleton();

	//Need to capture/update each device
	mgr.mInputManager.mKeyboard->capture();
	mgr.mInputManager.mMouse->capture();

	

	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;

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

