#include "Player.h"
#include "GameManager.h"
#include "SoundManager.h"

Player::Player()
:dodge_cooldown_(800),
move_cooldown_(200)
{
}

Player::~Player()
{
}

/**	This function instantiates the nodes and the entities attached for the player
as well as setting the base values for the player hp and such.
*/
void Player::Init(Ogre::Vector3 spawnPoint)
{
	// Create a reference to the game manager
	GameManager& mgr = GameManager::getSingleton();

	// Instantiate player variables
	Ogre::Vector3 startingPosition = Ogre::Vector3(0, 0, 0);
	SetHealth(10);

	// Add the node to the scene
	Ogre::SceneNode* playerNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", startingPosition);

	//Creates player parts with nodes and attach meshes
	Ogre::SceneNode* torsoNode = playerNode->createChildSceneNode("TorsoNode", torsoSocketPosition);
	Ogre::Entity* torsoEntity = GameManager::getSingleton().mSceneMgr->createEntity(torsoMeshName);
	torsoNode->attachObject(torsoEntity);
	torsoNode->setScale(characterScale, characterScale, -characterScale);

	Ogre::SceneNode* headNode = torsoNode->createChildSceneNode("HeadNode", headSocketPosition);	//Used for camera
	Ogre::Entity* headEntity = GameManager::getSingleton().mSceneMgr->createEntity(headMeshName);
	headNode->attachObject(headEntity);

	Ogre::SceneNode* leftArmNode = torsoNode->createChildSceneNode("LeftArmNode", leftArmSocketPosition);
	Ogre::Entity* leftArmEntity = GameManager::getSingleton().mSceneMgr->createEntity(armMeshName);
	leftArmNode->attachObject(leftArmEntity);

	Ogre::SceneNode* rightArmNode = torsoNode->createChildSceneNode("RightArmNode", rightArmSocketPosition);
	Ogre::Entity* rightArmEntity = GameManager::getSingleton().mSceneMgr->createEntity(armMeshName);
	rightArmNode->attachObject(rightArmEntity);

	Ogre::SceneNode* leftFootNode = torsoNode->createChildSceneNode("LeftFootNode", leftFootSocketPosition);
	Ogre::Entity* leftFootEntity = GameManager::getSingleton().mSceneMgr->createEntity(footMeshName);
	leftFootNode->attachObject(leftFootEntity);

	Ogre::SceneNode* rightFootNode = torsoNode->createChildSceneNode("RightFootNode", rightFootSocketPosition);
	Ogre::Entity* rightFootEntity = GameManager::getSingleton().mSceneMgr->createEntity(footMeshName);
	rightFootNode->attachObject(rightFootEntity);

	Ogre::SceneNode* cameraNode = playerNode->createChildSceneNode("CameraNode", cameraPosition);

	// right arm origin
	Ogre::Vector3 rightarmoffset = Ogre::Vector3(30, playerShoulderHeight, 0);
	rightarmOrigin = mgr.mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("rightarmOrigin", rightarmoffset);
	rightarmNode = mgr.mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("rightarmNode", rightarmoffset);
	rightarmNode->setScale(0.2, 0.2, 0.2);
	Ogre::Entity* rightarmEntity = GameManager::getSingleton().mSceneMgr->createEntity("cube.mesh");
	rightarmNode->attachObject(rightarmEntity);

	// rocket arm target
	Ogre::Vector3 rocketarmtargetoffset = Ogre::Vector3(0, 0, 500);
	rocketarmtargetNode = mgr.mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("rocketarmtargetNode", -rocketarmtargetoffset);

	mgr.mSceneMgr->getSceneNode("PlayerNode")->translate(spawnPoint, Ogre::Node::TS_LOCAL);

	exists = true;
	timer_.reset();
	dodge_timer_.reset();
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

	// Null check 
	if (GetMeat() >= dodgeMeatCost)
		ableToDodge = true;
	else
		ableToDodge = false;

	//Sets the variable false after a set amount of time
	if (timer_.getMilliseconds() >= dodge_cooldown_)
	{
		keyPressed = false;
	}

	//Checks if player has enough meat, executes dodge method and decreases meat
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_A))
	{
		if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_LSHIFT) && (!keyPressed) && (ableToDodge))
		{
			timer_.reset();
			dodge_timer_.reset();
			dodgeLeft = true;
			DecreaseMeat(dodgeMeatCost);
			keyPressed = true;
		}

		else
			dirVec.x -= move;
	}

	if (dodgeLeft)
	{
		if (dodge_timer_.getMilliseconds() <= move_cooldown_)
		{
			dirVec.x -= move * 5;
			dodgeRight = false;
		}
	}

	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_D))
	{
		if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_LSHIFT) && (!keyPressed) && (ableToDodge))
		{
			timer_.reset();
			dodge_timer_.reset();
			dodgeRight = true;
			DecreaseMeat(dodgeMeatCost);
			keyPressed = true;
		}

		else
			dirVec.x += move;
	}

	if (dodgeRight)
	{
		if (dodge_timer_.getMilliseconds() <= move_cooldown_)
		{
			dirVec.x += move * 5;
			dodgeLeft = false;
		}
	}

	// Rotate Player Yaw
	mgr.mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(-1 * currentX * rotate));
	mgr.mSceneMgr->getSceneNode("PlayerNode")->translate(dirVec * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	Pickup();
	Discard();

	// Execute attack
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_SPACE))
	{
		InitiateAbility();
	}

	// Ground smash attack
	if (isSmashing)
	{
		if (smashingDown)
		{
			if (equipment.arm.AbilityUpdate(rightarmNode, evt))
			{
				equipment.arm.AbilityDamage();
				smashingDown = false;
				equipment.arm.AbilityTarget(rightarmOrigin->getPosition());
			}
		}
		else
		{
			if (equipment.arm.AbilityUpdate(rightarmNode, evt))
			{
				isSmashing = false;
			}
		}
	}

	float meat = mgr.mEnemyManager.IterateMeat(mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition(), 50);
	IncreaseMeat(meat);

	//Check if player needs to fall
	Ogre::Vector3 playerPosition = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition();
	Ogre::Real dropRange = 1632;
	Ogre::Real lavaHeight = -320;
	if (!doomed && playerPosition.squaredLength() > dropRange * dropRange)
	{
		doomed = true;
	}
	if (doomed)
	{ 
		playerPosition = (playerPosition.squaredLength() > dropRange * dropRange) ? playerPosition : playerPosition.normalisedCopy() * dropRange;
		mgr.mSceneMgr->getSceneNode("PlayerNode")->setPosition(playerPosition);
		if (playerPosition.y > lavaHeight){ mgr.mSceneMgr->getSceneNode("PlayerNode")->translate(Ogre::Vector3(0, -++fallingSpeed * 9.81f, 0) * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL); }
		else 
		{ 
			DecreaseHealth(50.0f * evt.timeSinceLastFrame); 
		}
	}
}

void Player::ChangeRightArmMesh(Ogre::String meshName)
{
	rightarmNode->detachAllObjects();
	Ogre::Entity* rightarmEntity = GameManager::getSingleton().mSceneMgr->createEntity(meshName);
	rightarmNode->attachObject(rightarmEntity);
}

void Player::InitiateAbility()
{
	equipment.arm.equippedByEnemy = false;
	if (!isSmashing)
	{
		//equipment.arm.type = 1;
		if (equipment.arm.type == 0)
		{
			equipment.arm.AbilityTarget(rightarmOrigin->getPosition() - Ogre::Vector3(0, playerShoulderHeight, 0));
			equipment.arm.AbilityGlobalTarget(rightarmOrigin->_getDerivedPosition() - Ogre::Vector3(0, playerShoulderHeight, 0));
		}
		else if (equipment.arm.type == 1)
		{
			equipment.arm.AbilityTarget(rocketarmtargetNode->getPosition());
			equipment.arm.AbilityGlobalTarget(rocketarmtargetNode->_getDerivedPosition());
		}

		isSmashing = true;
		smashingDown = true;
		SoundManager::GetSingleton().PlaySound("SpellCasting.wav");
	}
	else
	{
		// TODO: attack in progress
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
	if ((meat - spendMeat) < 0)
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

		if (bodypart.tag == "Arm")
		{
			equipment.EquipArm();
			equipment.setPlayerArmStats(bodypart.randDamage, bodypart.randAttackSpeed);
			Ogre::LogManager::getSingletonPtr()->logMessage("player attackspeed" + std::to_string(bodypart.randAttackSpeed));
			bodypart.pickedUp = true;
			if (bodypart.type == 1)
			{
				ChangeRightArmMesh(bodypart.mesh);
				equipment.arm.type = 1;
			}
			else if (bodypart.type == 0)
			{
				ChangeRightArmMesh(bodypart.mesh);
				equipment.arm.type = 0;

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