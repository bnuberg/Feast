#pragma once 
#include "Enemy.h"
#include "Player.h"

class AbilityModifier
{

public:

	AbilityModifier();
	~AbilityModifier();

	int modifierType;

	void AddModifier();

	virtual void UseModifier(Enemy enemy);
	virtual void UseEModifier(Player player);

};