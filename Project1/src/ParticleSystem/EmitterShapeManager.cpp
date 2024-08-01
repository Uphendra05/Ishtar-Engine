#include "EmitterShapeManager.h"
#include "ConeEmitter.h"
#include "BoxEmitter.h"
#include "SphereEmitter.h"




EmitterShapeManager::EmitterShapeManager()
{
	AddEmitterShape(EmitterShape::CONE, new ConeEmitter());
	AddEmitterShape(EmitterShape::BOX, new BoxEmitter());
	AddEmitterShape(EmitterShape::SPHERE, new SphereEmitter());
	SetEmitterShape(EmitterShape::BOX);
}

EmitterShapeManager::~EmitterShapeManager()
{


}

void EmitterShapeManager::SetEmitterShape(EmitterShape shape)
{
	this->m_EmitterShape = shape;
	m_CurrentEmitterShape = (int)m_EmitterShape;
}



void EmitterShapeManager::AddEmitterShape(EmitterShape shapeType, BaseEmitterShape* shape)
{
	m_ListOfShapes[shapeType] = shape;
}

void EmitterShapeManager::RemoveEmitterShape(EmitterShape shapeType)
{
	m_ListOfShapes.erase(shapeType);
}

void EmitterShapeManager::Render()
{
	GetEmitterShape()->Render();
}

void EmitterShapeManager::UpdateParticle(glm::vec3& pos, glm::vec3& dir)
{
	GetEmitterShape()->UpdateParticle(pos, dir);
}



void EmitterShapeManager::DrawProperties()
{
	if (DrawDropDownImGui("Shape", m_CurrentEmitterShape, shapes, 3))
	{
		SetEmitterShape((EmitterShape)m_CurrentEmitterShape);
	}
	
	m_ListOfShapes[m_EmitterShape]->DrawProperties();

}

void EmitterShapeManager::SceneDraw()
{
}

BoxEmitter* EmitterShapeManager::asBoxEmitter()
{
	
	return (BoxEmitter*)GetEmitterShape();
	

}

ConeEmitter* EmitterShapeManager::asConeEmitter()
{
	return (ConeEmitter*)GetEmitterShape();
}

SphereEmitter* EmitterShapeManager::asSphereEmitter()
{
	return (SphereEmitter*)GetEmitterShape();
}

BaseEmitterShape* EmitterShapeManager::GetEmitterShape()
{
	return m_ListOfShapes[m_EmitterShape];
}