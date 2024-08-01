#pragma once
#include "../EmitterProperty.h"
#include "../Particle.h"
#include "../../Utilities/Lerp.h"

class SizeOverLifetime : public EmitterProperty
{
public:


	bool isEnabled = false;
	glm::vec3 startScale = glm::vec3(0.1);
	glm::vec3 endScale = glm::vec3(1);

	glm::vec3 ScaleParticle(Particle& particle);
	// Inherited via EmitterProperty
	void DrawProperties() override;
	void SceneDraw() override;
};

