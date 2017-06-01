#pragma once
#include <OgreTimer.h>
#include "GameManager.h"

class Grid
{
public:
	static Grid* getInstance(int width, int height);
	static Grid* getInstance();
	void setBlockageAt(Ogre::Vector2 pos);
	bool isBlocked(Ogre::Vector2 pos);
	bool isValidPosition(Ogre::Vector2 pos);
	bool initialized;
	int getWidth();
	int getHeight();
	int getIndexFromPosition(Ogre::Vector2 pos);
	Ogre::Vector2 getPositionFromIndex(int index);
private:
//	static Grid* gridInstance;

	int xOffset, zOffset;

	bool * blockages = nullptr;

	Grid(int width, int height);
	~Grid();

	int gridWidth, gridHeight;
};

