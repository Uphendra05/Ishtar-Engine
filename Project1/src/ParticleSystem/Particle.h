#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Particle
{
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(0);
	glm::vec3 velocity = glm::vec3(0);
	float currentLifetime = 0;
	float lifeTime = 2;

	void SetLifeTime(float lifeTime);

};