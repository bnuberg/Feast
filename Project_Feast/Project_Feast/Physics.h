#pragma once
#include "btBulletDynamicsCommon.h"
#include <string>
#include <map>
#include <vector>

class Physics
{
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape *> collisionShapes;
	std::map<std::string, btRigidBody *> physicsAccessors;

public:
	Physics();
	~Physics();

	void InitPhysics();
};

