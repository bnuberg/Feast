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
	void RarityPicker();
	void ApplyRarity(int aDamageMax, int aDamageMin, int aSpeedMax, int aSpeedMin);
	RarityTypes rarityTypes;
	int GetDamageValue();
	int GetSpeedValue();
	Ogre::Entity* SetRarityMaterial(Ogre::Entity* entity);
	void LoadMaterials();
	void ChangePass(float r, float g, float b);
	float R();
	float G();
	float B();
	/*Ogre::Pass* commonPass;
	Ogre::MaterialPtr common;*/
private:
	int aSpeed;
	int aDamage;
	float rValue, gValue, bValue;
};

