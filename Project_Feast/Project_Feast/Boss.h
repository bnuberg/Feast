#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	Boss();
	~Boss();
	void Init();
	void Update(const Ogre::FrameEvent& evt);
	void AddBodyObjectsStageOne();
	void AddBodyObjectsStageTwo();
	void DetachBodyParts() const;

private:
	int id = 0;

	typedef Ogre::Vector3 vector3;
	vector3 fakeStartPosition;
	vector3 healthBarPosition = vector3(0, 50, 0);
	vector3 startPosition;
	
	const float shoulderHeight = 55;

	const Ogre::Real characterScale = 4;

	Ogre::SceneNode* baseNode;

	Ogre::SceneNode* bodyNode;
	const char* bodyMeshName1 = "bossBody1.mesh";
	const char* bodyMeshName2 = "bossBody2.mesh";
	const vector3 bodySocketPosition = vector3(0, 25, 0);

	Ogre::SceneNode* leftArmNode;
	Ogre::SceneNode* rightArmNode;
	const char* leftFistMeshName1 = "bossFistL1.mesh";
	const char* leftFistMeshName2 = "bossFistL2.mesh";
	const char* rightFistMeshName1 = "bossFistR1.mesh";
	const char* rightFistMeshName2 = "bossFistR2.mesh";
	const vector3 leftArmSocketPosition = vector3(-7, 5, 0);
	const vector3 rightArmSocketPosition = vector3(7, 5, 0);

	int stage = 1;
};

