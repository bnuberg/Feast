#include "Leg.h"
#include "GameManager.h"


Leg::Leg()
{
	mesh_ = "cube.mesh";
	tag_ = "Leg";
}


Leg::~Leg()
{
}

void Leg::Stats()
{
	randSpeed = rand() % (speedMax - speedMin + 1) + speedMin;
}

void Leg::Ability()
{

}


