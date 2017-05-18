#include "Player.h"
#include "GameManager.h"
#include "SoundManager.h"


Player::Player()
{
}


Player::~Player()
{
}

/**	This function instantiates the nodes and the entities attached for the player
	as well as setting the base values for the player hp and such.
*/
void Player::Init()
{
	// Create a reference to the game manager
	GameManager& mgr = GameManager::getSingleton();
	GameManager* pMgr = GameManager::getSingletonPtr();

	// Instantiate player variables
	Ogre::Vector3 startingPosition = Ogre::Vector3(0, 0, 0);
	SetHealth(10);

	// Create a player entity with the right mesh
	Ogre::Entity* playerEntity = GameManager::getSingleton().mSceneMgr->createEntity("Body", "Body.mesh");

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

	Pickup();

	// Execute attack
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_SPACE))
	{
		InitiateSmash();
	}
	Discard();
	// Ground smash attack
	if (isSmashing)
	{
		Ogre::Vector3 target = Ogre::Vector3(0, 0, 0);
		Ogre::Vector3 globaltarget = Ogre::Vector3(0, 0, 0);

		// TODO: decide which attack is cast based on attached bodypart
		

		switch (attack)
		{
		case 0: // is ground smash at player position approximately
			target = rightarmOrigin->getPosition();
			target -= Ogre::Vector3(0, 160, 0);
			globaltarget = rightarmOrigin->_getDerivedPosition();
			globaltarget -= Ogre::Vector3(0, 160, 0);
			break;
		case 1: // is ground smash far in front of the player position
			target = rocketarmtargetNode->getPosition();
			globaltarget = rocketarmtargetNode->_getDerivedPosition();
			break;
		default:
			break;
		}

		GroundSmashAttack(evt, target, globaltarget);
	}

	float meat = mgr.mEnemyManager.IterateMeat(mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition(), 50);
	IncreaseMeat(meat);
	if (GetMeat() >= 10)
		convertMeattoHealth();
}

void Player::ChangeRightArmMesh(Ogre::String meshName)
{
	rightarmNode->detachAllObjects();
	Ogre::Entity* rightarmEntity = GameManager::getSingleton().mSceneMgr->createEntity(meshName);
	rightarmNode->attachObject(rightarmEntity);
}

void Player::InitiateSmash()
{
	if (!isSmashing)
	{
		isSmashing = true;
		smashingDown = true;
		SoundManager::GetSingleton().PlaySound("SpellCasting.wav");

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
	DecreaseMeat(10);
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

void Player::SetAttack()
{
	playerDamage = equipment.damage;
	playerAttackSpeed = equipment.attackSpeed;
	
}

void Player::SetSpeed()
{
	
	move = equipment.speed;
}

void Player::Pickup()
{
	GameManager& mgr = GameManager::getSingleton();

	playerPosition = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition();
	mgr.mBodyPartManager.IterateBodyParts(playerPosition, 200);

	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_E))
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("fullmetal");
		BodyPart bodypart = mgr.mBodyPartManager.ClosestBodyPart(playerPosition);

		Ogre::LogManager::getSingletonPtr()->logMessage(bodypart.tag);
		//Ogre::LogManager::getSingletonPtr()->logMessage(bodypart.mesh);
		if (bodypart.tag == "Arm")
		{
			equipment.EquipArm();
			equipment.setPlayerArmStats(bodypart.randDamage, bodypart.randAttackSpeed);
			Ogre::LogManager::getSingletonPtr()->logMessage("player attackspeed" + std::to_string(bodypart.randAttackSpeed));
			bodypart.pickedUp = true;
			if (bodypart.type == 1)
			{
				ChangeRightArmMesh("sphere.mesh");
			}
			else if (bodypart.type == 0)
			{
				ChangeRightArmMesh("cube.mesh");
			}
			attack = bodypart.type;
			
			SetAttack();
			
		}
		else if (bodypart.tag == "Leg")
		{
			equipment.EquipLeg();
			
			equipment.setPlayerLegStats(bodypart.randSpeed);
			bodypart.pickedUp = true;
			SetSpeed();
		}
		// TODO equip bodypart
	}
	
}

void Player::Discard()
{
	GameManager& mgr = GameManager::getSingleton();
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_F))
	{
		equipment.DiscardArm(5, 2);
		attack = 0;
		ChangeRightArmMesh("cube.mesh");
	}
	else if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_T))
	{
		equipment.DiscardLeg(50);
	}

}
