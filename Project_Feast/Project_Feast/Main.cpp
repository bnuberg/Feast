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



Main::Main()
:mRoot(0),
mWindow(0),
mCameraMan(0),
mOverlaySystem(0),
mDetailsPanel(0),
mTrayMgr(0),
mMouse(0),
mKeyboard(0),
mInputManager(0),
mResourcesCfg(Ogre::StringUtil::BLANK),
mPluginsCfg(Ogre::StringUtil::BLANK)
{
	
}

Main::~Main()
{
	if (mTrayMgr) delete mTrayMgr;
	if (mOverlaySystem) delete mOverlaySystem;

	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
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

	// initialize the OverlaySystem (changed for 1.9)
	mOverlaySystem = new Ogre::OverlaySystem();
	mgr.mSceneMgr->addRenderQueueListener(mOverlaySystem);
	
	mMainCamera->CameraInstance();

	mCameraMan = new OgreBites::SdkCameraMan(mgr.mCamera);   // create a default camera controller
	mCameraMan->setStyle(OgreBites::CameraStyle::CS_ORBIT);

	Ogre::Viewport* vp = mWindow->addViewport(mgr.mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	
	mgr.mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	//---Create the scene---
	

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -2);

	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = mgr.mSceneMgr->createEntity("ground");
	mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setMaterialName("Examples/Rockwall");
	groundEntity->setCastShadows(false);

	// Instantiate the player
	player.Init();

	// Initialize the enemy manager
	enemyManager.Init();
	// Create an ambient light


	mgr.mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
	Ogre::Light* light = mgr.mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);


	// Bind the cameraman to the player
	mCameraMan->setTarget(mgr.mSceneMgr->getSceneNode("PlayerHeadNode"));
	//mCameraMan->setYawPitchDist(Ogre::Radian(0), Ogre::Radian(1.0472), Ogre::Real(500));
	
	// Initialize the input manager
	mgr.mInputManager.InitInput(mWindow);

	//-------------------------------------------------------------------------------------
	//create FrameListener
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mInputContext.mKeyboard = mKeyboard;
	mInputContext.mMouse = mMouse;
	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mInputContext, this);
	mTrayMgr->hideCursor();

	// create a params panel for displaying sample details
	Ogre::StringVector items;
	items.push_back("Test");

	mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT, "DetailsPanel", 200, items);

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

	enemyManager.Update(evt);

	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;

	if (!processUnbufferedInput(evt))
		return false;

	mTrayMgr->frameRenderingQueued(evt);

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	if (!mTrayMgr->isDialogVisible())
	{
		mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
		if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
		{
			mDetailsPanel->setParamValue(0, "Test");
		}
	}

	//Ogre::Real dist = (mgr.mCamera->getPosition() - mCameraMan->getTarget()->_getDerivedPosition()).length();
	//mCameraMan->setYawPitchDist(mgr.mCamera->getOrientation().getYaw(), Ogre::Radian(1.0472), dist);
	mCameraMan->setYawPitchDist(Ogre::Radian(0), Ogre::Radian(0.349066), Ogre::Real(380));
	mCameraMan->frameRenderingQueued(evt);

	return true;
}

bool Main::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
	player.Update(evt);

	return true;
}

bool Main::keyPressed(const OIS::KeyEvent &arg)
{
	if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up
	mCameraMan->injectKeyDown(arg);
	return true;
}

bool Main::keyReleased(const OIS::KeyEvent &arg)
{
	mCameraMan->injectKeyUp(arg);
	return true;
}

bool Main::mouseMoved(const OIS::MouseEvent &arg)
{
	if (mTrayMgr->injectMouseMove(arg)) return true;
	mCameraMan->injectMouseMove(arg);
	return true;
}

bool Main::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if (mTrayMgr->injectMouseDown(arg, id)) return true;
	mCameraMan->injectMouseDown(arg, id);
	return true;
}

bool Main::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if (mTrayMgr->injectMouseUp(arg, id)) return true;
	mCameraMan->injectMouseUp(arg, id);
	return true;
}

//Adjust mouse clipping area
void Main::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void Main::windowClosed(Ogre::RenderWindow* rw)
{
	//Only close for window that created OIS (the main window in these demos)
	if (rw == mWindow)
	{
		if (mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
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

