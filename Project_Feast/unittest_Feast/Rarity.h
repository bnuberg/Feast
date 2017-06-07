#pragma once
class Rarity
{
public:
	Rarity();
	~Rarity();

	void ApplyRarity(int aDamageMax, int aDamageMin, int aSpeedMax, int aSpeedMin);
	int GetDamageValue();
	int GetSpeedValue();
	int Random(int min, int max);

private:
	int aSpeed;
	int aDamage;
};

