#pragma once
#include <OgreEntity.h>

/*	The ability attack interface is used by the ability templates.
	All the body parts which are used by both the player and the enemies have an attack ability.
	By creating an interface that all the templates need to follow we ensure that all body parts 
	can have all templates and that both the players and the enemies can both use all of the abilities.
	The templates need to work for both the player and the enemies because once an enemy dies,
	he can drop his bodypart and the same object can then be used by the player.
*/
class IAbilityAttack
{
public:
	virtual void Attack(Ogre::Vector3 target, int damage, int modifier) = 0; // Attack used by player
	virtual void AttackEnemy(Ogre::Vector3 target, int damage, int enemyID) = 0; // Attack used by enemy
};
