#pragma once
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>
/** @brief Generic Healthbar class that handles the display of healtbars

Detailed description:
The Healtbar class enables generic implementation of healtbars. It has 3 main methods:
Init is used to create a billboardset and a billboard to display the healthbar at the right position and the right target.
SetLength is used to change the healthbar width to display health gains or decreases (when taking damage).
Destroy handles the destruction of the healthbar when the entity is dead and we don't want to display a healthbar.

Architectual information:
The class is set up as a generic class so both enemies and the player can use it. 
To generate a healthbar we need to run the Init() method which needs a scenenode, position, scenemanager and an ID
Position and ID are the most important factors here. Position handles where the healthbar should be created and ID
is used for specification so that multiple entities can have healthbars without getting conflicts when creating the Billboardset.

@author Brian Nuberg
@date June 2017
*/
class Healthbar
{
public:
	Healthbar();
	~Healthbar();
	void Init(Ogre::SceneNode* sceneNode, Ogre::Vector3 position, Ogre::SceneManager* sceneManager, int ID);
	void SetLength(float currentHealth, float health);
	void Destroy();
	Ogre::BillboardSet* billBoardSet;
	Ogre::Billboard* greenHP;
};

