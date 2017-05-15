#include "AbilityAttackAOE.h"
#include "GameManager.h"


AbilityAttackAOE::AbilityAttackAOE()
{
}


AbilityAttackAOE::~AbilityAttackAOE()
{
}

void AbilityAttackAOE::Attack(Ogre::Vector3 target)
{
	GameManager& mgr = GameManager::getSingleton();

	// TODO: Create classes that hold the different attack types
	mgr.mEnemyManager.DamageEnemiesInCircle(target, attackRadius);
}