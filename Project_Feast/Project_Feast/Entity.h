#pragma once
#include <OgreSceneNode.h>

class Entity
{
public:
	/*Health functions*/
	float GetHealth() const;
	void SetHealth(float value);
	float GetMaxHealth() const;
	void SetMaxHealth(float value);
	void IncreaseHealth(float value);
	void DecreaseHealth(float value);
	void IncreaseMaxHealth(float value);
	void DecreaseMaxHealth(float value);
	void CheckHealth();
	virtual void Die();
	Ogre::SceneNode* entityNode;
protected:
	float health;
	float maxHealth;
	

	void CheckLavaDrop(const Ogre::FrameEvent& evt);
	bool doomed = false;
	Ogre::Real fallingSpeed = 0;
	const Ogre::Real dropRange = 1632;
	const Ogre::Real lavaHeight = -300;
	const Ogre::Real lavaDamage = 200;
};
