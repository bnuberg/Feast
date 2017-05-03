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
	Ogre::Vector3 startingPosition = Ogre::Vector3(0, 0, 0);
	SetHealth(10);

	// Create a player entity with the right mesh
	Ogre::Entity* playerEntity = GameManager::getSingleton().mSceneMgr->createEntity("Body", "Player.mesh");

	// Add the node to the scene
	Ogre::SceneNode* playerNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", startingPosition);
	playerNode->attachObject(playerEntity);

	// player head, used to position the camera
	Ogre::Vector3 headOffset = Ogre::Vector3(0, 220, 0);
	Ogre::SceneNode* playerHeadNode = mgr.mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("PlayerHeadNode", startingPosition + headOffset);

	// right arm origin
	Ogre::Vector3 rightarmoffset = Ogre::Vector3(30, 160, 0);
	rightarmOrigin = mgr.mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("rightarmOrigin", startingPosition + rightarmoffset);
	rightarmNode = mgr.mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("rightarmNode", startingPosition + rightarmoffset);
	rightarmNode->setScale(0.2, 0.2, 0.2);
	Ogre::Entity* rightarmEntity = GameManager::getSingleton().mSceneMgr->createEntity("cube.mesh");
	rightarmNode->attachObject(rightarmEntity);

	// rocket arm target
	Ogre::Vector3 rocketarmtargetoffset = Ogre::Vector3(0, 0, 500);
	rocketarmtargetNode = mgr.mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("rocketarmtargetNode", startingPosition - rocketarmtargetoffset);
}

void Player::Update(const Ogre::FrameEvent& evt)
{
	GameManager& mgr = GameManager::getSingleton();

	// Get and set mouse information at the start of the update
	OIS::MouseState ms = mgr.mInputManager.mMouse->getMouseState();
	float currentX = ms.X.rel;

	static Ogre::Real rotate = .13;
	static Ogre::Real move = 250;

	//Move ninja
	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	// Forwards and backwards
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_W))
		dirVec.z -= move;
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_S))
		dirVec.z += move;

	// Up and Down
	//if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_U))
	//	dirVec.y += move;
	//if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_O))
	//	dirVec.y -= move;

	// Left and Right
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_A))
		dirVec.x -= move;
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_D))
		dirVec.x += move;

	// Rotate Player Yaw
	mgr.mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(-1 * currentX * rotate));

	mgr.mSceneMgr->getSceneNode("PlayerNode")->translate(dirVec * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	// Execute attack
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_SPACE))
	{
		InitiateSmash();
	}

	// Ground smash attack
	if (isSmashing)
	{
		Ogre::Vector3 target = Ogre::Vector3(0, 0, 0);
		Ogre::Vector3 globalTarget = Ogre::Vector3(0, 0, 0);

		// TODO: decide which attack is cast based on attached bodypart
		int attack = 0;

		switch (attack)
		{
		case 0: // is ground smash at player position approximately
			target = rightarmOrigin->getPosition();
			target -= Ogre::Vector3(0, 160, 0);
			globalTarget = rightarmOrigin->_getDerivedPosition();
			globalTarget -= Ogre::Vector3(0, 160, 0);
			break;
		case 1: // is ground smash far in front of the player position
			target = rocketarmtargetNode->getPosition();
			globalTarget = rocketarmtargetNode->_getDerivedPosition();
			break;
		default:
			break;
		}

		GroundSmashAttack(evt, target, globalTarget);
	}
}

void Player::InitiateSmash()
{
	if (!isSmashing)
	{
		isSmashing = true;
		smashingDown = true;
	}
	else
	{
		// TODO: attack in progress
	}
}

void Player::GroundSmashAttack(const Ogre::FrameEvent& evt, Ogre::Vector3 localStrikeTarget, Ogre::Vector3 globalStrikeTarget)
{
	GameManager& mgr = GameManager::getSingleton();

	Ogre::Vector3 target = Ogre::Vector3(0, 0, 0);

	if (smashingDown)
	{
		target = localStrikeTarget;
	}
	else
	{
		target = rightarmOrigin->getPosition();
	}

	Ogre::Vector3 distanceVector = target - rightarmNode->getPosition();
	float distance = distanceVector.length();

	if (distance <= rightarmSpeed / 1500)
	{
		if (smashingDown)
		{
			rightarmNode->setPosition(target);
			float smashradius = 200;
			mgr.mEnemyManager.DamageEnemiesInCircle(globalStrikeTarget, smashradius);

			smashingDown = false;
		}
		else
		{
			rightarmNode->setPosition(target);
			isSmashing = false;
		}
	}
	else
	{
		distanceVector.normalise();

		rightarmNode->translate(distanceVector * rightarmSpeed * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	}
}

void Player::Die()
{
	// TODO: restart application/scene
}

float Player::GetHealth()
{
	return health;
}

float Player::GetMeat()
{
	return meat;
}

void Player::SetMeat(float startingMeat = 0) 
{
	meat = startingMeat;
}

void Player::IncreaseMeat(float incMeat)
{
	meat += incMeat;
}

void Player::DecreaseMeat(float spendMeat)
{
	if ((meat -= spendMeat) < 0)
	{
		meat = 0;
	}
	else
	{
		meat -= spendMeat;
	}
}

void Player::convertMeattoHealth()
{
	DecreaseMeat(50);
	IncreaseHealth(10);
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
		health = 0;
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
