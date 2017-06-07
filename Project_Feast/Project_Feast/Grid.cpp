#include "Grid.h"

static Grid * gridInstance;

Grid* Grid::getInstance(int width, int height)
{
	if (gridInstance == nullptr)
	{
		if (gridInstance == nullptr)
		{
			gridInstance = new Grid(width, height);
		}
	}
	return gridInstance;
}

Grid* Grid::getInstance()
{
	return gridInstance;
}

void Grid::setBlockageAt(Ogre::Vector2 pos)
{
	if (!isValidPosition(pos))
		return;
	initialized = true;
	blockages[getIndexFromPosition(pos)] = true;
}

bool Grid::isBlocked(Ogre::Vector2 pos)
{
	if (!isValidPosition(pos))
		return false;
	return blockages[getIndexFromPosition(pos)];
}

bool Grid::isValidPosition(Ogre::Vector2 pos)
{
	int x = pos.x + xOffset;
	int z = pos.y + zOffset;
	if (x > gridWidth || x < 0 || z > gridHeight || z < 0)
		return false;
	return true;
}

int Grid::getWidth()
{
	return gridWidth;
}

int Grid::getHeight()
{
	return gridHeight;
}

int Grid::getIndexFromPosition(Ogre::Vector2 pos)
{
	int x = pos.x + xOffset;
	int z = pos.y + zOffset;
	return (z * gridWidth + x);
}

Ogre::Vector2 Grid::getPositionFromIndex(int index)
{
	int x = (index % gridWidth) - xOffset;
	int z = (index / gridWidth) - zOffset;
	return Ogre::Vector2(x, z);
}

Grid::Grid(int width, int height)
{
	initialized = false;

	xOffset = width / 2;
	zOffset = height / 2;

	blockages = new bool[width * height];

	gridWidth = width;
	gridHeight = height;
	for (int i = 0; i < gridWidth * gridHeight; i++)
	{
		// Initialize all positions to false.
		blockages[i] = false;
	}

}

Grid::~Grid()
{
	delete [] blockages;
}
