#include "Boss.h"
#include "GameManager.h"

/**
 This class contains all the boss related code. We inherit from enemy because we need the same basic moveset and health functions as the enemy.
*/
Boss::Boss()
{
	SetMaxHealth(30);
}

Boss::~Boss()
{
}

void Boss::Init()
{
	GameManager& mgr = GameManager::GetSingleton();
	baseNode = mgr.mSceneMgr->getRootSceneNode()->createChildSceneNode("BossNode", fakeStartPosition);

	AddBodyObjectsStageOne();

	baseNode->translate(startPosition, Ogre::Node::TS_LOCAL);
}

void Boss::Update(const Ogre::FrameEvent& evt)
{
	if (stage == 1 && health < maxHealth / 2)
	{
		DetachBodyParts();
		AddBodyObjectsStageTwo();
		stage++;
	}
}

/**
* \brief Attaches all the body parts of the first stage so that the body parts are shown from the scene
*/
void Boss::AddBodyObjectsStageOne()
{
	GameManager& mgr = GameManager::GetSingleton();
	bodyNode = enemyNode->createChildSceneNode("BossBodyNode" + Ogre::StringConverter::toString(++id), bodySocketPosition);
	Ogre::Entity* bodyEntity = mgr.mSceneMgr->createEntity(bodyMeshName1);
	bodyNode->attachObject(bodyEntity);
	bodyNode->setScale(scale * characterScale, scale * characterScale, scale * characterScale);

	leftArmNode = bodyNode->createChildSceneNode("EnemyLeftArmNode" + Ogre::StringConverter::toString(id), leftArmSocketPosition);
	Ogre::Entity* leftArmEntity = mgr.mSceneMgr->createEntity(leftFistMeshName1);
	leftArmNode->attachObject(leftArmEntity);

	rightArmNode = bodyNode->createChildSceneNode("EnemyRightArmNode" + Ogre::StringConverter::toString(id), rightArmSocketPosition);
	Ogre::Entity* rightArmEntity = mgr.mSceneMgr->createEntity(rightFistMeshName1);
	rightArmNode->attachObject(rightArmEntity);
}


/**
 * \brief Attaches the body parts of the second stage
 */
void Boss::AddBodyObjectsStageTwo()
{
	GameManager& mgr = GameManager::GetSingleton();
	bodyNode = enemyNode->createChildSceneNode("BossBodyNode" + Ogre::StringConverter::toString(++id), bodySocketPosition);
	Ogre::Entity* bodyEntity = mgr.mSceneMgr->createEntity(bodyMeshName2);
	bodyNode->attachObject(bodyEntity);
	bodyNode->setScale(scale * characterScale, scale * characterScale, scale * characterScale);

	leftArmNode = bodyNode->createChildSceneNode("EnemyLeftArmNode" + Ogre::StringConverter::toString(id), leftArmSocketPosition);
	Ogre::Entity* leftArmEntity = mgr.mSceneMgr->createEntity(leftFistMeshName2);
	leftArmNode->attachObject(leftArmEntity);

	rightArmNode = bodyNode->createChildSceneNode("EnemyRightArmNode" + Ogre::StringConverter::toString(id), rightArmSocketPosition);
	Ogre::Entity* rightArmEntity = mgr.mSceneMgr->createEntity(rightFistMeshName2);
	rightArmNode->attachObject(rightArmEntity);
}

/**
* \brief Detaches all the body parts so that the body parts are removed from the scene
*/
void Boss::DetachBodyParts() const
{
	baseNode->detachAllObjects();
	healthBarNode->detachAllObjects();

	bodyNode->detachAllObjects();
	leftArmNode->detachAllObjects();
	rightArmNode->detachAllObjects();
}