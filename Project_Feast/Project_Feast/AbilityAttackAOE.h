#pragma once
#include "IAbilityAttack.h"

/*	The ability attack AOE class implements the ability attack interface.
	This class is a template for the AOE ability. 
	When a body part is made the body part can dynamically have any of the attacking templates.
	The attack AOE performs an area of effect attack at the given target and damages everything in a circle around that.
*/
class AbilityAttackAOE :
	public IAbilityAttack
{
public:
	AbilityAttackAOE();
	~AbilityAttackAOE();

	void Attack(Ogre::Vector3 target, int damage, int modifier) override;		// Player attack implementation
	void AttackEnemy(Ogre::Vector3 target, int damage, int enemyID) override;	// Enemy attack implementation
	void AttackParticlesPlayer(Ogre::Vector3 target);							// Creates the player particle
	void AttackParticlesEnemy(Ogre::Vector3 target, int enemyID);				// Creates the enemy particle
private:
	float attackRadius = 200;					// The radius of the aera of effect
	Ogre::SceneNode* playerAttackNode;			// Player node to which the particle effect is connected
	Ogre::ParticleSystem* playerAttackParticle;	// The corresponding particle effect
	Ogre::SceneNode* enemyAttackNode;			// Enemy node to which the particle effect is connected
	Ogre::ParticleSystem* enemyAttackParticle;	// The corresponding particle effect
};

