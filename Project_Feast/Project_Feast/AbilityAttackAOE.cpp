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

	Ogre::Vector3 distanceVector = target - playerNode->_getDerivedPosition();
	float distance = distanceVector.length();
	Ogre::LogManager::getSingletonPtr()->logMessage("distance target to player" + std::to_string(distance));
	if (distance <= attackRadius)
	{
		mgr.player.DecreaseHealth(damage); 
	}
}