#pragma once
#include "BaseEmitterShape.h"

class BoxEmitter : public BaseEmitterShape
{

public:
	BoxEmitter();
	glm::vec3 particleDir = glm::vec3(0, 1, 0);


	// Inherited via BaseEmitterShape
	void DrawProperties() override;

	void SceneDraw() override;
	void UpdateParticle(glm::vec3& pos, glm::vec3& dir) override;
	void Render() override;
	bool isDebug = false;


	glm::vec3 FindPointInsideBox(glm::vec3 minCorner, glm::vec3 maxCorner);
	glm::vec3 CalculateDirWithRotation(glm::vec3 rotation);

private:

	glm::vec4 boxColor = glm::vec4(0, 1, 0, 1);
};

