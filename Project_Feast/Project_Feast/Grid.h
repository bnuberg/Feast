#pragma once
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreTimer.h>
#include "GameManager.h"
#include "EnemyManager.h"
#include "Enemy.h"

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
private:
//	static Grid* gridInstance;

	int xOffset, zOffset;

	bool * blockages = NULL;

	Grid(int width, int height);
	~Grid();

	int gridWidth, gridHeight;
};

