#include "AbilityAttackAOE.h"
#include "GameManager.h"


AbilityAttackAOE::AbilityAttackAOE()
{
}


AbilityAttackAOE::~AbilityAttackAOE()
{
}

void AbilityAttackAOE::Attack(Ogre::Vector3 target, int damage)
{
	GameManager& mgr = GameManager::getSingleton();

	mgr.mEnemyManager.DamageEnemiesInCircle(target, attackRadius, damage);
}

void AbilityAttackAOE::AttackEnemy(Ogre::Vector3 target, int damage)
{
	GameManager& mgr = GameManager::getSingleton();

	Ogre::SceneNode* playerNode = mgr.mSceneMgr->getSceneNode("PlayerNode");
	Ogre::Vector3 distanceVector = target - playerNode->getPosition();
	float distance = distanceVector.length();
	if (distance <= attackRadius)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("player gets damaged by: " + std::to_string(damage));
		//player.getDamaged(); 
	}
}