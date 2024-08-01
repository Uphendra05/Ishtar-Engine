#pragma once

#include "BaseEmitterShape.h"
class SphereEmitter : public BaseEmitterShape
{

public:
	SphereEmitter();



	// Inherited via BaseEmitterShape
	void DrawProperties() override ;
	void SceneDraw() override;
	void UpdateParticle(glm::vec3& pos, glm::vec3& dir) override;
	void Render() override;
	bool isDebug = false;

	// Unity Particle System Variables, default value 1, adjust radius for size and thickness for spawning volume

	float radius = 1;
	float radiusThickness = 1;

private :



	glm::vec3 minDir = glm::vec3(-1);
	glm::vec3 maxDir = glm::vec3(1);

	glm::vec4 sphereRadiusCol = glm::vec4(0, 1, 0, 1);
	glm::vec4 radiusThicknessCol = glm::vec4(0, 0, 0, 1);

	glm::vec3 GetRandomPointInSphere(glm::vec3 minDir, glm::vec3 maxDir);
};

