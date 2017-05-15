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

	Ogre::LogManager::getSingletonPtr()->logMessage("ATTACK ATTACK");
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(target.x));
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(target.y));
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(target.z));

	// TODO: Create classes that hold the different attack types
	mgr.mEnemyManager.DamageEnemiesInCircle(target, attackRadius);
}