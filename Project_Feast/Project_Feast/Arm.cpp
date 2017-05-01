#include "Arm.h"
#include "GameManager.h"


Arm::Arm()
{
	mesh = "sphere.mesh";
}


Arm::~Arm()
{
}

void Arm::Stats()
{
	randDamage = rand() % (damageMax - damageMin + 1) + damageMin;
	randAttackSpeed = rand() % (attackSpeedMax - attackSpeedMin + 1) + attackSpeedMin;
}

void Arm::Ability()
{

}

