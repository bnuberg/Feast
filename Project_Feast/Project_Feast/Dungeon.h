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
	const String meshName = "pPlane1.mesh";
	Vector3 playerSpawnPoint = Vector3(0, 0, -500);
	//Mesh map;
};