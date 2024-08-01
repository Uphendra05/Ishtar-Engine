#pragma once
#include "../EmitterProperty.h"
#include "../Particle.h"
#include "../../Utilities/Lerp.h"
#include <iostream>

class RotationOverLifetime : public EmitterProperty
{
public:

	bool isEnabled = false;
	glm::vec3 endRotation = glm::vec3(0, 0, 0);
	glm::vec3 startRotation = glm::vec3(0,0,0);

	glm::vec3 AngularVelocity(Particle& particle);

	// Inherited via EmitterProperty
	void DrawProperties() override;

	void SceneDraw() override;

};

