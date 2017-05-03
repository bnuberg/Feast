#pragma once
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreTimer.h>
#include "GameManager.h"
#include "EnemyManager.h"
#include "Enemy.h"

class EnemyPatternManager
{
public:
	EnemyPatternManager();
	~EnemyPatternManager();
	void BasicEnemy();
	float setAggroR();
	float setAttackR();

private:
	float aggroRange;
	float attackRange;





};