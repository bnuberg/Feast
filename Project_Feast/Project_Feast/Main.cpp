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
mWindow(0),
mCameraMan(0),
mTrayMgr(0),
mDetailsPanel(0),
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
	
	/*Ogre::String resourcePath = getenv("RESOURCE_HOME");*/
	//Ogre::LogManager::getSingletonPtr()->logMessage("resourcepath =" + (resourcePath));
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
			//well shit
		}
		else
		{
			Ogre::String s(c);
			Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(s, "FileSystem", "General");
		}


	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;

	mWindow = mRoot->initialise(true, "Main");

	// Calls the Singleton GameManager 
	new GameManager();
	GameManager& mgr = GameManager::getSingleton();
	
	new SoundManager();
	SoundManager::getSingleton().PlaySound("ActionMusic.wav", true);

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

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

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

	// Create a player entity with the right mesh
	Ogre::Entity* playerEntity = GameManager::getSingleton().mSceneMgr->createEntity("Hammermesh", "RightArm_Hammer.mesh");

	// Add the node to the scene
	Ogre::Vector3 startingPosition = Ogre::Vector3(1000, -200, 50);
	Ogre::SceneNode* playerNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("hammerarm", startingPosition);
	playerNode->attachObject(playerEntity);

	// Instantiate the player
	player.Init();

	// Initialize the enemy manager
	mgr.mEnemyManager.Init();

	// Create an ambient light
	mgr.mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
	Ogre::Light* light = mgr.mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);


	// Bind the cameraman to the player
	mCameraMan->setTarget(mgr.mSceneMgr->getSceneNode("PlayerHeadNode"));
	//mCameraMan->setYawPitchDist(Ogre::Radian(0), Ogre::Radian(1.0472), Ogre::Real(500));
	
	// Initialize the input manager
	mgr.mInputManager.InitInput(mWindow);
	
	menu.Init();


	/*mInputContext.mKeyboard = mgr.mInputManager.mKeyboard;
	mInputContext.mMouse = mgr.mInputManager.mMouse;

	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mInputContext, this);
	mTrayMgr->showFrameStats(OgreBites::TL_TOPLEFT);
	mTrayMgr->hideCursor();

	Ogre::StringVector items;
	items.push_back("Health");
	items.push_back("Meat");


	mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT, "DetailsPanel", 200, items);
	mDetailsPanel->setParamValue(0, "Health");
	mDetailsPanel->setParamValue(1, "Meat");

	mLabel = mTrayMgr->createLabel(OgreBites::TL_CENTER, "Text", "Press 'E' to interact", 200);*/

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
		//mTrayMgr->frameRenderingQueued(evt);

		//if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_E))
		//{
		//	mLabel->hide();
		//	mTrayMgr->clearTray(OgreBites::TL_CENTER);
		//}

		//if (mgr.mBodyPartManager.show_label_ == true)
		//{
		//	mTrayMgr->moveWidgetToTray("Text", OgreBites::TL_CENTER);
		//	mLabel->show();
		//}
		//else if (mgr.mBodyPartManager.show_label_ == false)
		//{
		//	mLabel->hide();
		//	mTrayMgr->clearTray(OgreBites::TL_CENTER);
		//}

		//if (!mTrayMgr->isDialogVisible())
		//{
		//	mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
		//	if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
		//	{
		//		mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(player.GetHealth()));
		//		mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(player.GetMeat()));
		//	}
		//}
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_M))
	{
		menu.ShowControls();
	}

	mgr.mEnemyManager.Update(evt);

	if (menu.QuitApplication()){
		return false;
	}

	if (!processUnbufferedInput(evt))
		return false;

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

