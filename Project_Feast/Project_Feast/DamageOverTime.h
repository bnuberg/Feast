#pragma once 

#include "AbilityModifier.h" 


class DamageOverTime : public AbilityModifier
{
public:

	DamageOverTime();
	~DamageOverTime();

	void AddDamageOverTime();

	void UseModifier(Enemy enemy) override;
	void UseEModifier(Player player) override;
};