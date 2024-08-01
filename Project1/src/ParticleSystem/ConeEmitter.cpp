#include "ConeEmitter.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "../Random.h"
#include "../Utilities/Lerp.h"
#include "../ImGui/ImGuiUtils.h"

#include "../GraphicsRender.h"

ConeEmitter::ConeEmitter()
{


}

void ConeEmitter::SetEmitFrom(EmmitFrom emmitFrom)
{
	this->emitFrom = emmitFrom;
	currentEmitInt = (int)emmitFrom;
}

EmmitFrom ConeEmitter::GetEmifrom()
{
	return this->emitFrom;
}

void ConeEmitter::DrawProperties()
{
	DrawBoolImGui("IsDebug", isDebug);
	DrawFloatImGui("Angle", angle);
	DrawFloatImGui("Radius", radius);
	


	if (DrawDropDownImGui("EmitFrom", currentEmitInt, emitStrings, 2))
	{
		SetEmitFrom((EmmitFrom)currentEmitInt);
	}

	BaseEmitterShape::DrawProperties();
}

void ConeEmitter::SceneDraw()
{
}

void ConeEmitter::UpdateParticle(glm::vec3& pos, glm::vec3& dir)
{
	float randomHeight = 0;

	glm::vec3 eulerAnglesRadians = glm::radians(rotation);
	glm::quat quatRot = glm::quat(
		glm::eulerAngleYXZ(eulerAnglesRadians.y, eulerAnglesRadians.x, eulerAnglesRadians.z));
	glm::vec3 up = glm::normalize(glm::vec3(glm::mat4_cast(quatRot)[1]));

	endPos = position + up * height;

	if (emitFrom == EmmitFrom::BASE)
	{
		pos = position;
	}
	else
	{
		randomHeight = GetRandomFloatNumber(0, height);

		pos = Lerp(position, endPos, randomHeight);
	}

	float radius = GetRadius(randomHeight);

	glm::vec3 dirInCone = GetRandomDirInsideCone(up);
	dirInCone = glm::normalize(dirInCone);

	pos = pos + dirInCone * (GetRandomFloatNumber(0, radius));
	dir = GetDirection(up, dirInCone);

	if (isRandomDir)
	{
		//TODO randomize direction
	}

}

void ConeEmitter::Render()
{
	if (isDebug)
	{
		glm::vec3 center = position;
		glm::vec3 end = endPos;

		topRadius = GetRadius(height);

		GraphicsRender::GetInstance().DrawSphere(center, radius, bottomColor, true);
		GraphicsRender::GetInstance().DrawSphere(end, topRadius, topColor, true);
	}

	
}

float ConeEmitter::GetRadius(float& heightValue)
{
	return (radius + glm::tan(glm::radians(angle)) * heightValue);
}

glm::vec3 ConeEmitter::GetDirection(glm::vec3& up, glm::vec3& xzPlane)
{
	glm::vec3 normalizedUp = glm::normalize(up);
	glm::vec3 normalizedXZPlane = glm::normalize(xzPlane);

	glm::vec3 rotationAxis = glm::cross(normalizedUp, normalizedXZPlane);

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotationAxis);

	glm::vec3 direction = glm::vec3(rotationMatrix * glm::vec4(normalizedUp, 1.0f));

	return direction;
}

glm::vec3 ConeEmitter::CircularRandVec3()
{
	float a = GetRandomFloatNumber(0, glm::two_pi<float>());
	return glm::normalize(glm::vec3(glm::cos(a), 0.0f, glm::sin(a)));
}

glm::vec3 ConeEmitter::GetRandomDirInsideCone( glm::vec3& up)
{

	glm::vec3 dir = CircularRandVec3();

	return glm::normalize(glm::rotate(dir, glm::orientedAngle(glm::vec3(0, 0, 1), up, glm::vec3(1, 0, 0)), up));
	
}
