#include "DeathScene.h"
#include "LevelLoader.h"


DeathScene::DeathScene()
{
}


DeathScene::~DeathScene()
{
}

void DeathScene::CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow)
{
	GameManager& mgr = GameManager::getSingleton();
	
	mTrayMgrDeath = new OgreBites::SdkTrayManager("DeathScreen", mgr.mWindow, mgr.ui.mInputContext, this);
	mTrayMgrDeath->setListener(this);
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MainMenu", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->getTechnique(0)->getPass(0)->createTextureUnitState("Death.png");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	mTrayMgrDeath->showBackdrop("DeathScreen");
	resetLabel = mTrayMgrDeath->createLabel(OgreBites::TL_CENTER, "Start", "Press Enter to Restart", 200);
}

void DeathScene::Update()
{
}
