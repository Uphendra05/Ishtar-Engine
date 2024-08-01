#pragma once
#include "Softbody/SoftBody.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	static PhysicsEngine& GetInstance();

	void AddSoftBody(SoftBodyObjs* softBody);
	void RemoveSoftBody(SoftBodyObjs* softBody);

	void PhysicsEngineUpdate(float deltatime);
	void UpdateVerlet(float deltatime);
	void UpdateMeshVertices();

private:
	float timer = 0;
	float fixedTimeStep = 0.01f;
	std::vector<SoftBodyObjs*> softbodyObjects;

};

