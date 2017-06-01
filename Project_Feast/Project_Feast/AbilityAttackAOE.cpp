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
	/*Ogre::LogManager::getSingletonPtr()->logMessage("Arm Damage: " + std::to_string(damage));*/
}

void AbilityAttackAOE::AttackEnemy(Ogre::Vector3 target, int damage)
{
	
	GameManager& mgr = GameManager::getSingleton();

	Ogre::SceneNode* playerNode = mgr.mSceneMgr->getSceneNode("PlayerNode");
	Ogre::Vector3 distanceVector = target - playerNode->getPosition();
	float distance = distanceVector.length();
	if (distance <= attackRadius)
	{
		mgr.player.DecreaseHealth(damage); 
	}
}