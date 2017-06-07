#include "AbilityAttackAOE.h"
#include "GameManager.h"


AbilityAttackAOE::AbilityAttackAOE()
{
}

AbilityAttackAOE::~AbilityAttackAOE()
{
}

/**	The player attack which gets called by the bodypart when it hits the target
	@param The target where the attack needs to happen.
	@param The amount of damage that the attack needs to do.
	@param The modifier that is on the bodypart, this is then used to apply on enemies that are hit.
*/
void AbilityAttackAOE::Attack(Ogre::Vector3 target, int damage, int modifier)
{
	GameManager& mgr = GameManager::getSingleton();

	// Call the enemy manager to find all the enemies in the given circle
	mgr.mEnemyManager.DamageEnemiesInCircle(target, attackRadius, damage, modifier);
	AttackParticlesPlayer(target);
}

/**	The enemy attack which gets called by the bodypart when it hits the target
	@param The target where the attack needs to happen.
	@param The amount of damage that the attack needs to do.
	@param The enemyID used to create multiple particle effects, one for each enemy at max.
*/
void AbilityAttackAOE::AttackEnemy(Ogre::Vector3 target, int damage, int enemyID)
{
	GameManager& mgr = GameManager::getSingleton();

	Ogre::SceneNode* playerNode = mgr.mSceneMgr->getSceneNode("PlayerNode");

	// Calculate the distance between the attack target and the player location
	Ogre::Vector3 distanceVector = target - playerNode->_getDerivedPosition();
	float distance = distanceVector.length();
	AttackParticlesEnemy(target, enemyID);

	if (distance <= attackRadius)
	{
		mgr.player.DecreaseHealth(damage); 
	}
}

void AbilityAttackAOE::AttackParticlesPlayer(Ogre::Vector3 target)
{
	GameManager& mgr = GameManager::getSingleton();

	if (playerAttackParticle != NULL){
		mgr.mSceneMgr->destroyParticleSystem("playerAttack");
	}

	playerAttackParticle = mgr.mSceneMgr->createParticleSystem("playerAttack", "AttackWave");

	if (playerAttackNode != NULL)
	{
		mgr.mSceneMgr->destroySceneNode("playerAttackNode");
	}
	
	playerAttackNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("playerAttackNode", target);

	playerAttackNode->attachObject(playerAttackParticle);

}

void AbilityAttackAOE::AttackParticlesEnemy(Ogre::Vector3 target, int enemyID)
{
	GameManager& mgr = GameManager::getSingleton();

	if (enemyAttackParticle != NULL){
		mgr.mSceneMgr->destroyParticleSystem("enemyAttack" + Ogre::StringConverter::toString(enemyID));
	}

	enemyAttackParticle = mgr.mSceneMgr->createParticleSystem("enemyAttack" + Ogre::StringConverter::toString(enemyID), "AttackWave");

	if (enemyAttackNode != NULL)
	{
		mgr.mSceneMgr->destroySceneNode("enemyAttackNode" + Ogre::StringConverter::toString(enemyID));
	}

	enemyAttackNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("enemyAttackNode" + Ogre::StringConverter::toString(enemyID), target);

	enemyAttackNode->attachObject(enemyAttackParticle);
}
