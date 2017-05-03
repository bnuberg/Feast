#include "Player.h"
#include "GameManager.h"



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
	Ogre::Entity* playerEntity = GameManager::getSingleton().mSceneMgr->createEntity("Body", "ninja.mesh");

	// Add the node to the scene
	Ogre::SceneNode* playerNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", startingPosition);
	playerNode->attachObject(playerEntity);

	Ogre::Vector3 headOffset = Ogre::Vector3(0, 220, 0);
	Ogre::SceneNode* playerHeadNode = mgr.mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("PlayerHeadNode", startingPosition + headOffset);
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

	Pickup();
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

void Player::Pickup()
{
	GameManager& mgr = GameManager::getSingleton();

	playerPosition = mgr.mSceneMgr->getSceneNode("PlayerNode")->getPosition();
	mgr.mBodyPartManager.IterateBodyParts(playerPosition, 20);

	if (mgr.mBodyPartManager.isPickupAble == true && mgr.mInputManager.mKeyboard->isKeyDown(OIS::KC_LCONTROL))
	{
		
		// TODO equip bodypart
	}
	
}
