#include "Rarity.h"
#include <cstdlib>
#include <OgreResourceGroupManager.h>
#include <OgreMaterialManager.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>


Rarity::Rarity()
{
	
}


Rarity::~Rarity()
{
}

void Rarity::RarityPicker()
{
	rarityTypes = static_cast<RarityTypes>(rand() % 5);
	switch (rarityTypes){
	case Common:
		{
			ApplyRarity(3, 1, 2, 1);	
		}
	case Uncommon:
		{
			ApplyRarity(5, 3, 4, 2);
		}
	case Rare:
		{
			ApplyRarity(7, 5, 6, 4);
		}
	case Epic:
		{
			ApplyRarity(9, 7, 8, 6);
		}
	case Legendary:
		{
			ApplyRarity(15, 9, 12, 8);
		}
	}
}

void Rarity::ApplyRarity(int aDamageMax, int aDamageMin, int aSpeedMax, int aSpeedMin)
{
	aDamage = rand() % (aDamageMax - aDamageMin + 1) + aDamageMin;
	aSpeed = rand() % (aSpeedMax - aSpeedMin + 1) + aSpeedMin;
}

int Rarity::GetDamageValue()
{
	return aDamage;
}

int Rarity::GetSpeedValue()
{
	return aSpeed;
}


Ogre::Entity* Rarity::SetRarityMaterial(Ogre::Entity* entity)
{
	

	return entity;
}
