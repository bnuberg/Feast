#pragma once
#include "Ogre.h"

using namespace Ogre;

class Dungeon
{
public:
	Dungeon(Ogre::SceneManager* sceneManager);
	~Dungeon();
	Vector3 GetPlayerSpawnPoint() const;
	Real GetFallRange();

private:
	void LoadScene(SceneManager* sceneManager);
	const String meshName = "arena.mesh";
	const String boxMeshName = "arenaBox.mesh";
	const String lavaMeshName = "arenaLava.mesh";

	Vector3 playerSpawnPoint = Vector3(0, 0, -500);
	const Vector3 dungeonSpawnPoint = Vector3(0, -320, 0);
	const Vector3 dungeonScale = Vector3(32, 32, 32);
	Real fallRange = 200;
};