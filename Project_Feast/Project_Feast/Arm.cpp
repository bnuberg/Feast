#include "Arm.h"
#include "GameManager.h"


Arm::Arm()
{
	mesh_ = "sphere.mesh";
	tag_ = "Arm";
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

