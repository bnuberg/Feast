#include "Rarity.h"
#include <OgreTechnique.h>
#include <OgreResourceGroupManager.h>

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
			ChangePass(0.2, 0.2, 0.2);
			break;
		}
	case Uncommon:
		{
			ApplyRarity(5, 3, 4, 2);
			ChangePass(1, 1, 1);
			break;
		}
	case Rare:
		{
			ApplyRarity(7, 5, 6, 4);
			ChangePass(0, 0.2, 1);
			break;
		}
	case Epic:
		{
			ApplyRarity(9, 7, 8, 6);
			ChangePass(0.3, 0, 0.8);
			break;
		}
	case Legendary:
		{
			ApplyRarity(15, 9, 12, 8);
			ChangePass(0.8, 0.4, 0);
			break;
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

void Rarity::LoadMaterials()
{
	/*common = Ogre::MaterialManager::getSingleton().create("Common", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	commonPass = common->getTechnique(0)->getPass(0);*/
	/*commonPass->setAmbient(1, 0, 0);
	commonPass->setDiffuse(1, 0, 1, 1);
	commonPass->setEmissive(0.5, 0.5, 0.5);*/
}

void Rarity::ChangePass(float r, float g, float b)
{
	rValue = r;
	gValue = g;
	bValue = b;
}

float Rarity::R()
{
	return rValue;
}

float Rarity::G()
{
	return gValue;
}

float Rarity::B()
{
	return bValue;
}

