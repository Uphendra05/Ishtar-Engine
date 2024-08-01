#pragma once
#include "EmitterProperty.h"
#include "BaseEmitterShape.h"
#include <unordered_map>

enum class EmitterShape
{
	BOX = 0,
	CONE = 1,
	SPHERE = 2

};

class ConeEmitter;
class BoxEmitter;
class SphereEmitter;

class EmitterShapeManager : public EmitterProperty
{
public:

	EmitterShapeManager();
	~EmitterShapeManager();

	void SetEmitterShape(EmitterShape shape);
	void AddEmitterShape(EmitterShape shapeType, BaseEmitterShape* shape);
	void RemoveEmitterShape(EmitterShape shapeType);
	void Render();
	void UpdateParticle(glm::vec3& pos, glm::vec3& dir);


	// Inherited via EmitterProperty
	void DrawProperties() override;
	void SceneDraw() override;

	BoxEmitter* asBoxEmitter();
	ConeEmitter* asConeEmitter();
	SphereEmitter* asSphereEmitter();
	BaseEmitterShape* GetEmitterShape();

private :

	const char* shapes[3] = { "BOX", "CONE","SPHERE" };
	std::unordered_map< EmitterShape, BaseEmitterShape*> m_ListOfShapes;

	int m_CurrentEmitterShape = 0;
	EmitterShape m_EmitterShape = EmitterShape::CONE;

};

