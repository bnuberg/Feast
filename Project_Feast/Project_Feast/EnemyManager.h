#pragma once
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreTimer.h>
#include "Enemy.h"
#include "BodyPart.h"
#include "GameManager.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void EnemyManager::Init();
	void EnemyManager::Update(const Ogre::FrameEvent& evt);
	void SpawnEnemy();

private:
	std::list<Enemy> enemyList;
	Ogre::Timer timer;
	unsigned long enemySpawnTimer;
};

