#include "Healthbar.h"
#include <OgreSceneManager.h>
#include "GameManager.h"


Healthbar::Healthbar()
{
	
}


Healthbar::~Healthbar()
{
}
/**	This function initialises healthbar creation for a generic entity
@param The scenenode used
@param The position the healthbar gets created at
@param The scenemanager used (which scene it is applied to)
@param A unique identifier for the billboardset/healthbar
*/
void Healthbar::Init(Ogre::SceneNode* sceneNode, Ogre::Vector3 position, Ogre::SceneManager* sceneManager, int ID)
{
	
	billBoardSet = sceneManager->createBillboardSet("billBoardSet" + Ogre::StringConverter::toString(ID));

	Ogre::MaterialPtr healthBarMaterial = Ogre::MaterialManager::getSingleton().create("Common", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Pass* healthBarPass = healthBarMaterial->getTechnique(0)->getPass(0);
	healthBarPass->setLightingEnabled(false);
	billBoardSet->setMaterial(healthBarMaterial);

	greenHP = billBoardSet->createBillboard(position += Ogre::Vector3(0, 0, 0.05));
	greenHP->setColour(Ogre::ColourValue::Green);
	billBoardSet->setDefaultDimensions(100, 10);
	
	sceneNode->attachObject(billBoardSet);
}
/**	This function changes the length of the healthbar depending on how much health the entity has
@param The current health of the entity
@param The max health of the entity

*/
void Healthbar::SetLength(float currentHealth, float health)
{
	float fRatio = (float)currentHealth / (float)health;
	float fNewWidth =  100 * fRatio;
	float fNewTexWidth = 100 * fRatio;
	greenHP->setDimensions(fNewWidth, 10);
	greenHP->setTexcoordRect(0.0f, -10, 1* fNewTexWidth, -10);
}
/**	This function destroys the healthbar
*/
void Healthbar::Destroy()
{
	billBoardSet->removeBillboard(greenHP);
	billBoardSet = NULL;
}
