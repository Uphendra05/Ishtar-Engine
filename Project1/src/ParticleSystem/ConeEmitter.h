#pragma once
#include "BaseEmitterShape.h"

enum class EmmitFrom
{
	// Unity enums for spawning from base meaning from down sphere and volume meaning from volume between two sphere 
	BASE = 0,
	VOLUME = 1
};

class ConeEmitter : public BaseEmitterShape
{

public:

	ConeEmitter();

	glm::vec3 endPos = glm::vec3(0);

	EmmitFrom emitFrom = EmmitFrom::BASE;

	void SetEmitFrom(EmmitFrom emmitFrom);
	EmmitFrom GetEmifrom();

	// Inherited via BaseEmitterShape
	void DrawProperties() override;

	void SceneDraw() override;

	void UpdateParticle(glm::vec3& pos, glm::vec3& dir) override;

	void Render() override;

	//Unity Particle System Variables, default value 1, adjust radius for size of the two spheres
	//adjust angle for wider and shorter spawning 
	//adjust height for cone height
	float angle = 25.0f;
	float radius = 1.0f;
	bool isDebug = false;
	

private :

	float height = 1.0f;
	float topRadius = 0;


	const char* emitStrings[2] = { "Base", "Volume" };


	int currentEmitInt = 0;
	float GetRadius(float& heightValue);
	glm::vec3 GetDirection(glm::vec3& up, glm::vec3& xzPlane);
	glm::vec3 CircularRandVec3();
	glm::vec3 GetRandomDirInsideCone( glm::vec3& up);

	glm::vec4 bottomColor = glm::vec4(0, 1, 0, 1);
	glm::vec4 topColor = glm::vec4(0, 0, 1, 1);
};

