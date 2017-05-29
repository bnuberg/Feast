#include "AbilityModifier.h" 
#include "GameManager.h" 


AbilityModifier::AbilityModifier()
{
	switch (rand() % 3)
	{
	case 0:
		modifierType = 0;
		break;
	case 1:
		modifierType = 1;
		break;
	case 2:
		modifierType = 2;
		break;
	default:
		break;
	}
}

AbilityModifier::~AbilityModifier()
{

}

void AbilityModifier::AddModifier()
{

}

void AbilityModifier::UseModifier(Enemy enemy)
{
}

void AbilityModifier::UseEModifier(Player player)
{

}