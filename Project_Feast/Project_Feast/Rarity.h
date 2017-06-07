#pragma once
#include <OgreEntity.h>
#include <OgreMaterialManager.h>
#include <OgrePass.h>
/** @brief The Rarity class handles assigning a raritytype to body parts.
 

Detailed description:
*It generates a Rarity then based on the rarity it will assign specific damage
*and attack speed values, it will also assign the right material corresponding the rarity. 
*This information is then passed on to the generator class that generates body parts.

Architectual information:
Rarity contains an enumeration so we can easily check and assign rarity types when generating body parts.
It then uses a state machine to check for each rarity case and applies the corresponding values.
Rarity is an element in the chain of the body part generation.


@author Brian Nuberg
@date June 2017
*/

enum RarityTypes
{
	Common, Uncommon, Rare, Epic, Legendary
};
class Rarity
{
public:
	Rarity();
	~Rarity();
	void RarityPicker(int level);
	void ApplyRarityValues(int aDamageMax, int aDamageMin, int aSpeedMax, int aSpeedMin);
	RarityTypes rarityTypes;
	int GetDamageValue();
	int GetSpeedValue();
	Ogre::Entity* SetRarityMaterial(Ogre::Entity* entity);
	void LoadMaterials();
	void ChangePass(float r, float g, float b);
	int Random(int min, int max);
	float R();
	float G();
	float B();
	/*Ogre::Pass* commonPass;
	Ogre::MaterialPtr common;*/
private:
	int aSpeed;
	int aDamage;
	float rValue, gValue, bValue;

	int commonRange = 1;
	int uncommonRange = 2;
	int rareRange = 3;
	int epicRange = 4;
	int legendaryRange = 6;
};

