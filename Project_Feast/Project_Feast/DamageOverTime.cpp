#include "DamageOverTime.h" 
#include <OgreLogManager.h>


DamageOverTime::DamageOverTime()
{
}

DamageOverTime::~DamageOverTime()
{

}

void DamageOverTime::AddDamageOverTime()
{

}

void DamageOverTime::UseModifier(Enemy enemy)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("Player Dot");
	enemy.GetDamaged(100);
	

}

void DamageOverTime::UseEModifier(Player player)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("Enemy Dot");

}