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
	const String meshName = "arena.mesh";
	Vector3 playerSpawnPoint = Vector3(0, 0, 0);
	Vector3 enemySpawnPoints[5];
	const Vector3 dungeonSpawnPoint = Vector3(0, -320, 0);
	const Vector3 dungeonScale = Vector3(32, 32, 32);
	//Mesh map;
};