#pragma once
#include "Ogre.h"

using namespace Ogre;

class Dungeon
{
public:
	Dungeon();
	~Dungeon();
	Vector3 GetPlayerSpawnPoint();
	Vector3 GetEnemySpawnPoints();
	void PushOut();

private:
	const String meshName;
	const Vector3 playerSpawnPoint;
	Vector3 enemySpawnPoints;
	//Mesh map;
};