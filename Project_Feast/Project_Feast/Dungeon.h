#pragma once
#include "Ogre.h"

class Dungeon
{
public:
	Dungeon(Ogre::SceneManager* sceneManager);
	~Dungeon();
	Ogre::Vector3 GetPlayerSpawnPoint() const;
	Ogre::Real GetFallRange() const;

private:
	void LoadScene(Ogre::SceneManager* sceneManager) const;
	const Ogre::String meshName = "arena.mesh";
	const Ogre::String boxMeshName = "arenaBox.mesh";
	const Ogre::String lavaMeshName = "arenaLava.mesh";

	Ogre::Vector3 playerSpawnPoint = Ogre::Vector3(0, 0, -500);
	const Ogre::Vector3 dungeonSpawnPoint = Ogre::Vector3(0, -320, 0);
	const Ogre::Vector3 dungeonScale = Ogre::Vector3(32, 32, 32);
	Ogre::Real fallRange = 200;
};