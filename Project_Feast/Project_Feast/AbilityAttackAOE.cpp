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
	SpawnAttackParticles(target);
	/*Ogre::LogManager::getSingletonPtr()->logMessage("Arm Damage: " + std::to_string(damage));*/
}

void AbilityAttackAOE::AttackEnemy(Ogre::Vector3 target, int damage)
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
	if (distance <= attackRadius)
	{
		mgr.player.DecreaseHealth(damage); 
	}
}

void AbilityAttackAOE::SpawnAttackParticles(Ogre::Vector3 target)
{
	GameManager& mgr = GameManager::getSingleton();

	int i = 0;

	if (attackParticle != NULL){
		mgr.mSceneMgr->destroyParticleSystem("playerAttack");
	}

	attackParticle = mgr.mSceneMgr->createParticleSystem("playerAttack", "AttackWave");

	if (playerAttackNode != NULL)
	{
		mgr.mSceneMgr->destroySceneNode("PlayerAttackNode");
	}
	
	playerAttackNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerAttackNode", target);


	i++;

	playerAttackNode->attachObject(attackParticle);

}
