#pragma once 

#include "AbilityModifier.h" 


class DamageOverTime : public AbilityModifier
{
public:

	DamageOverTime();
	~DamageOverTime();

	void AddDamageOverTime();
};