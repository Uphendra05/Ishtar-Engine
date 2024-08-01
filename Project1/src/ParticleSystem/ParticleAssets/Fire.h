#pragma once
#include "../ParticleSystem.h"

class Fire : public ParticleSystem
{
public:
	Fire(float radius, glm::vec3 position);
	float radius = 0;
	glm::vec3 position = { 0,0,0 };
};

