#pragma once
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>

class Healthbar
{
public:
	Healthbar();
	~Healthbar();
	void Init(Ogre::SceneNode* sceneNode, Ogre::Vector3 position, Ogre::SceneManager* sceneManager, int enemyID);
	void SetLength(float currentHealth, float health);
	void Destroy();
	Ogre::BillboardSet* billBoardSet;
	Ogre::Billboard* redHP;
	Ogre::Billboard* greenHP;
	Ogre::ColourValue* color;
	Ogre::ColourValue* greenColor;

};

