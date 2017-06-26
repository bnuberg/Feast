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
	
	if (doOnce == false){
		GameManager& mgr = GameManager::getSingleton();
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("DeathScreen", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		material->getTechnique(0)->getPass(0)->createTextureUnitState("Death.png");
		material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
		material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
		material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

		rect = new Ogre::Rectangle2D(true);
		rect->setCorners(-1.0f, 1.0f, 1.0f, -1.0f);
		rect->setMaterial("DeathScreen");
		rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_MAX);
		rect->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));

		Ogre::AxisAlignedBox aabInf;
		aabInf.setInfinite();
		rect->setBoundingBox(aabInf);
		if (doOnce2 == false){
			auto m_pSceneMgr = mgr.mSceneMgr;
			node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("DeathScreenNode");
			doOnce2 = true;
		}
		node->attachObject(rect);
		mgr.reset = true;

	}
	doOnce = true;
	/*mTrayMgrDeath = new OgreBites::SdkTrayManager("DeathScreen", mgr.mWindow, mgr.ui.mInputContext, this);
	mTrayMgrDeath->setListener(this);
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MainMenu", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	material->getTechnique(0)->getPass(0)->createTextureUnitState("Death.png");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	mTrayMgrDeath->showBackdrop("DeathScreen");
	resetLabel = mTrayMgrDeath->createLabel(OgreBites::TL_CENTER, "Start", "Press Enter to Restart", 200);*/
}

void DeathScene::Update()
{

}
