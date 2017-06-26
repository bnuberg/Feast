#include "Healthbar.h"
#include <OgreSceneManager.h>
#include "GameManager.h"


Healthbar::Healthbar()
{
	
}


Healthbar::~Healthbar()
{
}

void Healthbar::Init(Ogre::SceneNode* sceneNode, Ogre::Vector3 position, Ogre::SceneManager* sceneManager, int enemyID)
{
	
	billBoardSet = sceneManager->createBillboardSet("billBoardSet" + Ogre::StringConverter::toString(enemyID));

	Ogre::MaterialPtr healthBarMaterial = Ogre::MaterialManager::getSingleton().create("Common", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Pass* healthBarPass = healthBarMaterial->getTechnique(0)->getPass(0);
	healthBarPass->setLightingEnabled(false);
	billBoardSet->setMaterial(healthBarMaterial);

	greenHP = billBoardSet->createBillboard(position += Ogre::Vector3(0, 0, 0.05));
	greenHP->setColour(Ogre::ColourValue::Green);
	billBoardSet->setDefaultDimensions(100, 10);
	
	sceneNode->attachObject(billBoardSet);
}

void Healthbar::SetLength(float currentHealth, float health)
{
	float fRatio = (float)currentHealth / (float)health;
	float fNewWidth =  100 * fRatio;
	float fNewTexWidth = 100 * fRatio;
	greenHP->setDimensions(fNewWidth, 10);
	greenHP->setTexcoordRect(0.0f, -10, 1* fNewTexWidth, -10);
}

void Healthbar::Destroy()
{
	billBoardSet->removeBillboard(greenHP);
	billBoardSet = NULL;
}
