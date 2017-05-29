#pragma once
#include <OgreEntity.h>

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
	
private:
	int aSpeed;
	int aDamage;
	int r;
	int g;
	int b;
	
};

