#pragma once
#include "Ogre.h"

using namespace Ogre;

class Dungeon
{
public:
	Dungeon(Ogre::SceneManager* sceneManager);
	~Dungeon();
	Vector3 GetPlayerSpawnPoint();
	void PushOut();

private:
	void LoadScene(SceneManager* sceneManager);
	void SpawnEnemies();
	const String meshName = "pPlane1.mesh";
	Vector3 playerSpawnPoint = Vector3(1000, 0, 1000);
	Vector3 enemySpawnPoints[5];
	//Mesh map;
};