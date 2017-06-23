#include "Player.h"
#include "GameManager.h"
#include "SoundManager.h"

Player::Player()
:dodge_cooldown_(800),
move_cooldown_(200)
{
}

Player::~Player(){}

/**	This function instantiates the nodes and the entities attached for the player
as well as setting the base values for the player hp and such.
*/
void Player::Init(Ogre::Vector3 spawnPoint)
{
	// Create a reference to the game manager
	GameManager& mgr = GameManager::getSingleton();

	// Instantiate player variables
	Ogre::Vector3 startingPosition = Ogre::Vector3(0, 0, 0);
	SetMaxHealth(100);

	// Add the node to the scene
	entityNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", startingPosition);

	//Creates player parts with nodes and attach meshes
	Ogre::SceneNode* torsoNode = entityNode->createChildSceneNode("TorsoNode", torsoSocketPosition);
	Ogre::Entity* torsoEntity = GameManager::getSingleton().mSceneMgr->createEntity(torsoMeshName);
	torsoNode->attachObject(torsoEntity);
	torsoNode->setScale(characterScale, characterScale, -characterScale);

	headNode = torsoNode->createChildSceneNode("HeadNode", headSocketPosition);
	Ogre::Entity* headEntity = GameManager::getSingleton().mSceneMgr->createEntity(headMeshName);
	headNode->attachObject(headEntity);

	playerHealthBarNode = mgr.mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("playerHealthBarNode", startingPosition + Ogre::Vector3(0, 100, 0));
	playerHealthbar.Init(playerHealthBarNode, startingPosition + Ogre::Vector3(0, 70, 0), mgr.mSceneMgr, 999);

	leftArmNode = torsoNode->createChildSceneNode("LeftArmNode", leftArmSocketPosition);
	Ogre::Entity* leftArmEntity = GameManager::getSingleton().mSceneMgr->createEntity(armMeshName);
	leftArmNode->attachObject(leftArmEntity);

	rightArmOrigin = entityNode->createChildSceneNode("RightArmOrigin", Ogre::Vector3(28, 45, 0));
	rightArmNode = entityNode->createChildSceneNode("RightArmNode", Ogre::Vector3(28, 45, 0));
	rightArmOrigin->setScale(characterScale, characterScale, characterScale);
	rightArmNode->setScale(characterScale, characterScale, characterScale);
	Ogre::Entity* rightArmEntity = GameManager::getSingleton().mSceneMgr->createEntity(armMeshName);
	rightArmNode->attachObject(rightArmEntity);

	leftFootNode = torsoNode->createChildSceneNode("LeftFootNode", leftFootSocketPosition);
	Ogre::Entity* leftFootEntity = GameManager::getSingleton().mSceneMgr->createEntity(footMeshName);
	leftFootNode->attachObject(leftFootEntity);

	rightFootNode = torsoNode->createChildSceneNode("RightFootNode", rightFootSocketPosition);
	Ogre::Entity* rightFootEntity = GameManager::getSingleton().mSceneMgr->createEntity(footMeshName);
	rightFootNode->attachObject(rightFootEntity);

	Ogre::SceneNode* cameraNode = entityNode->createChildSceneNode("CameraNode", cameraPosition);

	// rocket arm target
	Ogre::Vector3 rocketArmTargetOffset = Ogre::Vector3(0, 0, -400);
	rocketArmTargetNode = entityNode->createChildSceneNode("RocketArmTargetNode", rocketArmTargetOffset);

	entityNode->translate(spawnPoint, Ogre::Node::TS_LOCAL);
	equipment.arm.randDamage = 2;
	exists = true;
	timer_.reset();
	dodge_timer_.reset();
}

/**	The update from the player, everything here about input, controls, movement
@param evt is the frameEvent passed to be framerate independent.
*/
void Player::Update(const Ogre::FrameEvent& evt)
{
	GameManager& mgr = GameManager::getSingleton();
	OIS::MouseState ms = mgr.mInputManager.mMouse->getMouseState();

	if (!isSmashing)
	{
		// Get and set mouse information at the start of the update
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

		//Removes meat and executes dodge method when player has enough meat
		if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_A))
		{
			if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_SPACE) && (!keyPressed) && (ableToDodge))
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

		//Dodges to the left side
		if (dodgeLeft)
		{
			if (dodge_timer_.getMilliseconds() <= move_cooldown_)
			{
				dirVec.x -= move * 5;
				dodgeRight = false;
			}
		}

		//Removes meat and executes dodge method when player has enough meat
		if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_D))
		{
			if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_SPACE) && (!keyPressed) && (ableToDodge))
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

		//Dodges to the right side
		if (dodgeRight)
		{
			if (dodge_timer_.getMilliseconds() <= move_cooldown_)
			{
				dirVec.x += move * 5;
				dodgeLeft = false;
			}
		}


		// Rotate Player Yaw
		entityNode->yaw(Ogre::Degree(-1 * currentX * rotate));
		entityNode->translate(dirVec * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	}

	//Heals player when key is pressed and decreases meat
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_F) && meat >= 10 && !meatToHealth)
	{
		meatToHealth = true;
		ConvertMeattoHealth();
		SoundManager::GetSingleton().PlaySound("Eat.wav");
	}
	else
	{
		meatToHealth = false;
	}


	Pickup();
	Discard();

	// Execute attack
	if (ms.buttonDown(OIS::MB_Left))
	{
		InitiateAbility();
	}

	// Ground smash attack
	if (isSmashing)
	{
		if (smashingDown)
		{
			if (equipment.arm.AbilityUpdate(rightArmNode, evt))
			{
				equipment.arm.AbilityDamage();
				smashingDown = false;
				equipment.arm.AbilityTarget(rightArmOrigin->getPosition());
			}
		}
		else
		{
			if (equipment.arm.AbilityUpdate(rightArmNode, evt))
			{
				isSmashing = false;
			}
		}
	}

	float meat = mgr.mEnemyManager.IterateMeat(entityNode->getPosition(), 50);
	IncreaseMeat(meat);
	if (GetMeat() >= 10 && health != maxHealth){
		ableToHeal = true;
	}
	else
	{
		ableToHeal = false;
	}
	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_F) && ableToHeal == true){
	}

	playerHealthbar.SetLength(health, maxHealth);
	CheckLavaDrop(evt);
	CheckHealth();


	/*mgr.mSceneMgr->getSceneNode("TorsoNode")->yaw(0.05 * Ogre::Degree(sin(totalTime)));
	mgr.mSceneMgr->getSceneNode("HeadNode")->yaw(0.2 * Ogre::Degree(sin(totalTime)));*/
}

/** Changes the mesh attached to the right arm, it first detaches all objects on the rightArm and then spawns a new one.
@param meshName name of the mesh to load.
*/
void Player::ChangeRightArmMesh(Ogre::String meshName)
{
	rightArmNode->detachAllObjects();
	Ogre::Entity* rightarmEntity = GameManager::getSingleton().mSceneMgr->createEntity(meshName);
	rightArmNode->attachObject(rightarmEntity);

	common = Ogre::MaterialManager::getSingleton().create("Common", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	commonPass = common->getTechnique(0)->getPass(0);
	commonPass->setAmbient(equipment.arm.r, equipment.arm.g, equipment.arm.b);
	commonPass->setDiffuse(equipment.arm.r, equipment.arm.g, equipment.arm.b, 1);
	commonPass->setEmissive(equipment.arm.r, equipment.arm.g, equipment.arm.b);
	rightarmEntity->setMaterial(common);
}

void Player::ChangeArmModifier(int modifier)
{
	GameManager& mgr = GameManager::getSingleton();

	switch (modifier)
	{
	case 0:
		break;
	case 1:
		if (ModifierParticle != NULL){
			ModifierParticle->clear();
		}
		mgr.mSceneMgr->destroyParticleSystem("playerBleed");
		ModifierParticle = mgr.mSceneMgr->createParticleSystem("playerBleed", "BleedParticle");
		rightArmNode->attachObject(ModifierParticle);


		break;
	case 2:
		if (ModifierParticle != NULL){
			ModifierParticle->clear();
		}
		mgr.mSceneMgr->destroyParticleSystem("playerSlow");
		ModifierParticle = mgr.mSceneMgr->createParticleSystem("playerSlow", "SlowParticle");
		rightArmNode->attachObject(ModifierParticle);

		break;
	default:
		break;
	}


}

void Player::InitiateAbility()
{
	equipment.arm.equippedByEnemy = false;
	if (!isSmashing)
	{
		//equipment.arm.type = 1;
		if (equipment.arm.type == 0)
		{
			equipment.arm.AbilityTarget(rightArmOrigin->getPosition() - Ogre::Vector3(0, shouderHeight, 0));
			equipment.arm.AbilityGlobalTarget(rightArmOrigin->_getDerivedPosition() - Ogre::Vector3(0, shouderHeight, 0));
		}
		else if (equipment.arm.type == 1)
		{
			equipment.arm.AbilityTarget(rocketArmTargetNode->getPosition());
			equipment.arm.AbilityGlobalTarget(rocketArmTargetNode->_getDerivedPosition());
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
	if (!hasDied)
	{
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("DeathScreen", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		material->getTechnique(0)->getPass(0)->createTextureUnitState("Death.png");
		material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
		material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
		material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

		Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
		rect->setCorners(-1.0f, 1.0f, 1.0f, -1.0f);
		rect->setMaterial("DeathScreen");
		rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_MAX);
		rect->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));

		Ogre::AxisAlignedBox aabInf;
		aabInf.setInfinite();
		rect->setBoundingBox(aabInf);

		GameManager& mgr = GameManager::getSingleton();
		auto m_pSceneMgr = mgr.mSceneMgr;
		Ogre::SceneNode* node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("DeathScreen");
		node->attachObject(rect);
	}
	hasDied = true;
}

float Player::GetMeat() const
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

void Player::ConvertMeattoHealth()
{
	DecreaseMeat(10);
	IncreaseHealth(10);
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

	playerPosition = entityNode->getPosition();
	mgr.mBodyPartManager.IterateBodyParts(playerPosition, 200);

	if (mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_E) && CanPickUp)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("fullmetal");
		BodyPart bodypart = mgr.mBodyPartManager.ClosestBodyPart(playerPosition);
		CanPickUp = false;

		if (bodypart.tag == "Arm")
		{
			equipment.EquipArm();
			equipment.setPlayerArmStats(bodypart.randDamage, bodypart.randAttackSpeed, bodypart.randModifier);
			equipment.arm.r = bodypart.r;
			equipment.arm.g = bodypart.g;
			equipment.arm.b = bodypart.b;
			Ogre::LogManager::getSingletonPtr()->logMessage("player attackspeed" + std::to_string(bodypart.randAttackSpeed));
			bodypart.pickedUp = true;
			if (bodypart.type == 1)
			{
				ChangeRightArmMesh(bodypart.mesh);
				ChangeArmModifier(bodypart.randModifier);
				equipment.arm.type = 1;
			}
			else if (bodypart.type == 0)
			{
				ChangeRightArmMesh(bodypart.mesh);
				ChangeArmModifier(bodypart.randModifier);
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
	else if (!mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_E))
	{
		CanPickUp = true;
	}
}

void Player::Discard()
{
}