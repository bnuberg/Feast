#pragma once
#include <OgreEntity.h>
#include <OgreMaterialManager.h>
#include <OgrePass.h>


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
	void ApplyRarity(int aDamageMax, int aDamageMin, int aSpeedMax, int aSpeedMin);
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

