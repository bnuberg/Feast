#include "Player.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "LevelLoader.h"

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
	GameManager& mgr = GameManager::getSingleton();

	// Instantiate player variables
	Ogre::Vector3 startingPosition = Ogre::Vector3(0, 0, 0);
	SetMaxHealth(100);
	if (mgr.reset == false){
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
		returnPosition = entityNode->getPosition();
	}
	else if (mgr.reset)
	{

		hasDied = false;
		doomed = false;
		entityNode->setPosition(spawnPoint);
		
		
	}
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

	Ogre::Vector3 velocity = GetWalkInput(); //Get walking input of the user

	if (!isSmashing) //Lock movement when smashing
	{
		TryDodging(velocity);
		float currentX = ms.X.rel; //Get's mouse information
		static Ogre::Real rotate = .13; //Rotate constant
		entityNode->yaw(Ogre::Degree(-1 * currentX * rotate)); // Rotate Player Yaw
		entityNode->translate(velocity * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL); //Moves player with the velocity
	}

	TryEating(); //Check eating input and eat if possible
	Pickup();	 //Pickup logic

	if (ms.buttonDown(OIS::MB_Left)) InitiateAbility(); //Execute attack

	Smash(evt);

	PickupMeat();

	playerHealthbar.SetLength(health, maxHealth);
	CheckLavaDrop(evt);
	CheckHealth();
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

/** Checks if any body parts are close then checks the pickup button before attempting to pick the item up
*/
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

void Player::Win()
{
	if (!hasWon)
	{
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("WinScreen", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		material->getTechnique(0)->getPass(0)->createTextureUnitState("Win.png");
		material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
		material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
		material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

		Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
		rect->setCorners(-1.0f, 1.0f, 1.0f, -1.0f);
		rect->setMaterial("WinScreen");
		rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_MAX);
		rect->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));

		Ogre::AxisAlignedBox aabInf;
		aabInf.setInfinite();
		rect->setBoundingBox(aabInf);

		GameManager& mgr = GameManager::getSingleton();
		auto m_pSceneMgr = mgr.mSceneMgr;
		Ogre::SceneNode* node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("WinScreen");
		node->attachObject(rect);
	}
	hasWon = true;
}

/** Gets forward and sidewards movement. So the WASD
* @return Walking input as a vector3
*/
Ogre::Vector3 Player::GetWalkInput()
{
	auto keyboard = GameManager::getSingleton().mInputManager.mKeyboard;

	Ogre::Vector3 velocity = Ogre::Vector3::ZERO;
	if (keyboard->isKeyDown(OIS::KC_W)) velocity.z--;
	else if (keyboard->isKeyDown(OIS::KC_S)) velocity.z++;
	
	if (keyboard->isKeyDown(OIS::KC_A)) velocity.x--;
	else if (keyboard->isKeyDown(OIS::KC_D)) velocity.x++;

	return move * velocity;
}

/** Dodge logic
*/
void Player::TryDodging(Ogre::Vector3& velocity)
{
	ableToDodge = (GetMeat() >= dodgeMeatCost); //Checks if the player has enough meat

	if (timer_.getMilliseconds() >= dodge_cooldown_) keyPressed = false; //Sets the variable false after a set amount of time

	if (GameManager::getSingleton().mInputManager.mKeyboard->isKeyDown(OIS::KC_SPACE) && (!keyPressed) && (ableToDodge) && !velocity.isZeroLength())
	{
		timer_.reset();
		dodge_timer_.reset();
		DecreaseMeat(dodgeMeatCost);
		dodgeDirection = velocity.normalisedCopy();
		keyPressed = true;
	}

	if (dodge_timer_.getMilliseconds() <= move_cooldown_)
	{
		velocity += 1000 * dodgeDirection;
	}
}

/** Eating logic, checks eating button and if you have enough meat to eat
*/
void Player::TryEating()
{
	//Heals player when key is pressed and decreases meat
	if (GameManager::getSingleton().mInputManager.mKeyboard->isKeyDown(OIS::KC_F) && meat >= 10 && !meatToHealth)
	{
		meatToHealth = true;
		ConvertMeattoHealth();
		SoundManager::GetSingleton().PlaySound("Eat.wav");
	}
	else
	{
		meatToHealth = false;
	}
}

/** Tries to pickup meet and checks if the player is able to heal
*/
void Player::PickupMeat()
{
	float meat = GameManager::getSingleton().mEnemyManager.IterateMeat(entityNode->getPosition(), 50);
	IncreaseMeat(meat);
	ableToHeal = GetMeat() >= 10 && health != maxHealth;
}

/** Sees if the player is smashing and then uses the ability 
*/
void Player::Smash(const Ogre::FrameEvent& evt)
{
	// Ground smash attack
	if (!isSmashing) return;

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
