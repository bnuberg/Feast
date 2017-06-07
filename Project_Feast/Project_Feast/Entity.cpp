#include "Entity.h"
#include "GameManager.h"

/**	Returns the current health value of this entity
@return Current health value
*/
float Entity::GetHealth() const
{
	return health;
}

/**	Sets the players current health
@parameter value the value you want the health to be
*/
void Entity::SetHealth(float value)
{
	health = (value < maxHealth) ? value : maxHealth;
}

/**	Returns the current max health value of this entity
@return Current max health value
*/
float Entity::GetMaxHealth() const
{
	return maxHealth;
}

/**  Sets the max health of the player
@parameter value The value you want the max health to be
*/
void Entity::SetMaxHealth(float value)
{
	maxHealth = value;
	health = maxHealth;
}

/**	Increases this entities health but clamps to maxHealth
@parameter value The amount you want the health to increase
*/
void Entity::IncreaseHealth(float value)
{
	health += value;
	if (health > maxHealth)
	{
		health = maxHealth;
	}
}

/**	Decreases this entities health but clamps to maxHealth
@parameter value The amount you want the health to decrease
*/
void Entity::DecreaseHealth(float value)
{
	health -= value;
	CheckHealth();
}

/**	Increases this entities max health and heals with the same amount
@parameter value The amount you want the max health to increase
*/
void Entity::IncreaseMaxHealth(float value)
{
	maxHealth += value;
	IncreaseHealth(value);
}

/**	Decreases this entities max health and Damages with the same amount
@parameter value The amount you want the max health to decrease
*/
void Entity::DecreaseMaxHealth(float value)
{
	maxHealth -= value;
	DecreaseHealth(value);
}

/** Checks the health and if he should die
*/
void Entity::CheckHealth()
{
	if (GetHealth() <= 0.0f)
	{
		SetHealth(0.0f);
		Die();
	}
}

/** Function that is called when this entity dies
*/
void Entity::Die()
{

}

/** Entity logic of falling in lava and getting hurt.\n
@param evt is the frameEvent passed to be framerate independent.
*/
void Entity::CheckLavaDrop(const Ogre::FrameEvent& evt)
{
	GameManager& mgr = GameManager::getSingleton();
	Ogre::Vector3 position = entityNode->getPosition();
	if (!doomed && position.squaredLength() > dropRange * dropRange)
	{
		doomed = true;
	}
	if (doomed)
	{
		position = (position.squaredLength() > dropRange * dropRange) ? position : position.normalisedCopy() * dropRange;
		entityNode->setPosition(position);
		if (position.y > lavaHeight){ entityNode->translate(Ogre::Vector3(0, -++fallingSpeed * 9.81f, 0) * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL); }
		else
		{
			DecreaseHealth(lavaDamage * evt.timeSinceLastFrame);
		}
	}
}