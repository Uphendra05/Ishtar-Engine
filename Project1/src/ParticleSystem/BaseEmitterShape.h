#pragma once
#include "../Object.h"


class BaseEmitterShape : public Object
{
public:

	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(0);

	virtual void DrawProperties();
	virtual void SceneDraw() = 0;
	virtual void UpdateParticle(glm::vec3& pos, glm::vec3& dir) = 0;
	virtual void Render() = 0;

	

	
	bool isRandomDir;

};