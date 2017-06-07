#pragma once
#include "IAbilityAttack.h"
class AbilityAttackAOE :
	public IAbilityAttack
{
public:
	AbilityAttackAOE();
	~AbilityAttackAOE();

	void Attack(Ogre::Vector3 target, int damage, int modifier) override;
	void AttackEnemy(Ogre::Vector3 target, int damage, int enemyID) override;
	void AttackParticlesPlayer(Ogre::Vector3 target);
	void AttackParticlesEnemy(Ogre::Vector3 target, int enemyID);
private:
	float attackRadius = 200;
	Ogre::SceneNode* playerAttackNode;
	Ogre::ParticleSystem* playerAttackParticle;
	Ogre::SceneNode* enemyAttackNode;
	Ogre::ParticleSystem* enemyAttackParticle;




};

