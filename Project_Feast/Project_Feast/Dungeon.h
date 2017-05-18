#pragma once
#include "Ogre.h"

using namespace Ogre;

class Dungeon
{
public:
	Dungeon(Ogre::SceneManager* sceneManager);
	~Dungeon();
	Vector3 GetPlayerSpawnPoint();
	Vector3 GetEnemySpawnPoints();
	void PushOut();

private:
	void LoadScene(SceneManager* sceneManager);
	const String meshName = "pPlane1.mesh";
	const Vector3 playerSpawnPoint;
	Vector3 enemySpawnPoints;
	//Mesh map;
};