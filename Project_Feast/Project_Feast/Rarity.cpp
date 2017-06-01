#include "Rarity.h"
#include <OgreTechnique.h>
#include <OgreResourceGroupManager.h>
#include <random>

Rarity::Rarity()
{

}


Rarity::~Rarity()
{
}

void Rarity::RarityPicker(int level)
{
	int randomRarity = Random(1, 100);
	if (randomRarity > 95)
	{
		rarityTypes = Legendary;
	}
	else if (randomRarity > 85)
	{
		rarityTypes = Epic;
	}
	else if (randomRarity > 65)
	{
		rarityTypes = Rare;
	}
	else if (randomRarity > 40)
	{
		rarityTypes = Uncommon;
	}
	else
	{
		rarityTypes = Common;
	}

	switch (rarityTypes){
	case Common:
		{
			ApplyRarity(level + 1 + commonRange, level + 1 - commonRange, 2, 1);
			ChangePass(0.2, 0.2, 0.2);
			break;
		}
	case Uncommon:
		{
			ApplyRarity(level * 2 + 2 + uncommonRange, level * 2 + 2 - uncommonRange, 4, 2);
			ChangePass(1, 1, 1);
			break;
		}
	case Rare:
		{
			ApplyRarity(level * 3 + 3 + rareRange, level * 3 + 3 - rareRange, 6, 4);
			ChangePass(0, 0.2, 1);
			break;
		}
	case Epic:
		{
			ApplyRarity(level * 4 + 4 + epicRange, level * 4 + 4 - epicRange, 8, 6);
			ChangePass(0.3, 0, 0.8);
			break;
		}
	case Legendary:
		{
			ApplyRarity(level * 6 + 6 + legendaryRange, level * 6 + 6 - legendaryRange, 12, 8);
			ChangePass(0.8, 0.4, 0);
			break;
		}
	}
}

void Rarity::ApplyRarity(int aDamageMax, int aDamageMin, int aSpeedMax, int aSpeedMin)
{
	aDamage = Random(aDamageMin, aDamageMax);
	aSpeed = rand() % (aSpeedMax - aSpeedMin + 1) + aSpeedMin;
}

int Rarity::Random(int min, int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(mt);
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

