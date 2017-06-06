#include "AbilityAttackAOE.h"
#include "GameManager.h"


AbilityAttackAOE::AbilityAttackAOE()
{

}


AbilityAttackAOE::~AbilityAttackAOE()
{
}

void AbilityAttackAOE::Attack(Ogre::Vector3 target, int damage, int modifier)
{
	GameManager& mgr = GameManager::getSingleton();


	mgr.mEnemyManager.DamageEnemiesInCircle(target, attackRadius, damage, modifier);
	AttackParticlesPlayer(target);
	/*Ogre::LogManager::getSingletonPtr()->logMessage("Arm Damage: " + std::to_string(damage));*/
}

void AbilityAttackAOE::AttackEnemy(Ogre::Vector3 target, int damage, int enemyID)
{
	GameManager& mgr = GameManager::getSingleton();

	Ogre::LogManager::getSingletonPtr()->logMessage("AbilityAttackAOE.cpp target");
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(target.x));
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(target.y));
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(target.z));

	Ogre::SceneNode* playerNode = mgr.mSceneMgr->getSceneNode("PlayerNode");

	Ogre::LogManager::getSingletonPtr()->logMessage("AbilityAttackAOE.cpp player");
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(playerNode->_getDerivedPosition().x));
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(playerNode->_getDerivedPosition().y));
	Ogre::LogManager::getSingletonPtr()->logMessage(std::to_string(playerNode->_getDerivedPosition().z));

	Ogre::Vector3 distanceVector = target - playerNode->_getDerivedPosition();
	float distance = distanceVector.length();
	Ogre::LogManager::getSingletonPtr()->logMessage("distance target to player" + std::to_string(distance));
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
