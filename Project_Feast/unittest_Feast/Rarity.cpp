#include "stdafx.h"
#include "Rarity.h"
#include <random>


Rarity::Rarity()
{
}


Rarity::~Rarity()
{
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