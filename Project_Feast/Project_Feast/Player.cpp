#include "Player.h"
#include "GameManager.h"
#include <OgreEntity.h>


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	// Create a reference to the game manager
	GameManager& mgr = GameManager::getSingleton();
	GameManager* pMgr = GameManager::getSingletonPtr();

	// Instantiate player variables
	Ogre::Vector3 startingPosition = Ogre::Vector3(84, 48, 0);
	SetHealth(10);

	// Create a player entity with the right mesh
	Ogre::Entity* playerEntity = mgr.mSceneMgr->createEntity("Body", "ninja.mesh");

	// Add the node to the scene
	Ogre::SceneNode* playerNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", startingPosition);
	playerNode->attachObject(playerEntity);
}

void Player::Die()
{
	// TODO: restart application/scene
}

void Player::SetHealth(float startingHealth)
{
	maxHealth = startingHealth;
	health = maxHealth;
}

void Player::IncreaseHealth(float heal)
{
	health += heal;
	if (health > maxHealth)
	{
		health = maxHealth;
	}
}

void Player::DecreaseHealth(float dmg)
{
	health -= dmg;
	if (health <= 0)
	{
		Die();
	}
}

void Player::IncreaseMaxHealth(float permaHeal)
{
	maxHealth += permaHeal;
	IncreaseHealth(permaHeal);
}

void Player::DecreaseMaxHealth(float permaDmg)
{
	maxHealth -= permaDmg;
	DecreaseHealth(permaDmg);
}