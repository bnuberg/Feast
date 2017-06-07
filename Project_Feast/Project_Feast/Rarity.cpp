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
			ApplyRarityValues(level + 1 + commonRange, level + 1 - commonRange, 2, 1);
			ChangePass(0.2, 0.2, 0.2);
			break;
		}
	case Uncommon:
		{
			ApplyRarityValues(level * 2 + 2 + uncommonRange, level * 2 + 2 - uncommonRange, 4, 2);
			ChangePass(1, 1, 1);
			break;
		}
	case Rare:
		{
			ApplyRarityValues(level * 3 + 3 + rareRange, level * 3 + 3 - rareRange, 6, 4);
			ChangePass(0, 0.2, 1);
			break;
		}
	case Epic:
		{
			ApplyRarityValues(level * 4 + 4 + epicRange, level * 4 + 4 - epicRange, 8, 6);
			ChangePass(0.3, 0, 0.8);
			break;
		}
	case Legendary:
		{
			ApplyRarityValues(level * 6 + 6 + legendaryRange, level * 6 + 6 - legendaryRange, 12, 8);
			ChangePass(0.8, 0.4, 0);
			break;
		}
	}
}
/**	This function Applies the damage based on rarity
@param The maximum damage possible for a specific rarity
@param The minimum damage possible for a specific rarity
@param The maximum attack speed possible for a specific rarity
@param The minimum attack speed possible for a specific rarity
*/
void Rarity::ApplyRarityValues(int aDamageMax, int aDamageMin, int aSpeedMax, int aSpeedMin)
{
	aDamage = Random(aDamageMin, aDamageMax);
	aSpeed = Random (aSpeedMin, aSpeedMax);
}
/**	This function uses a random device (mt19937 theory) for better random generation than rand() within a certain range and the returns the value
@param The maximum random range
@param The minimum random range
*/
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

