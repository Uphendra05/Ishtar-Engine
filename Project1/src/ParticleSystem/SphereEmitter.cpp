#include "SphereEmitter.h"
#include "../Random.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "../GraphicsRender.h"

SphereEmitter::SphereEmitter()
{
}

void SphereEmitter::DrawProperties()
{
	DrawBoolImGui("IsDebug", isDebug);

	DrawFloatImGui("Radius", radius);
	DrawDragFloatImGui("Radius Thickness", radiusThickness, 0.01f, 0, 1);
	BaseEmitterShape::DrawProperties();
}

void SphereEmitter::SceneDraw()
{
}

void SphereEmitter::UpdateParticle(glm::vec3& pos, glm::vec3& dir)
{
	dir = GetRandomPointInSphere(minDir, maxDir);
	dir = glm::normalize(dir);

	float randomLength = GetRandomFloatNumber(radius - (radius * radiusThickness), radius);

	pos = position + dir * randomLength;

	if (isRandomDir)
	{
		dir = GetRandomPointInSphere(minDir, maxDir);
	}
}

void SphereEmitter::Render()
{
	if (isDebug)
	{
		glm::vec3 center = position;

		if (radiusThickness == 0)
		{
			GraphicsRender::GetInstance().DrawSphere(center, radius - (radius * radiusThickness), radiusThicknessCol, true);
			return;
		}
		else
		{
			GraphicsRender::GetInstance().DrawSphere(center, radius, sphereRadiusCol, true);
			GraphicsRender::GetInstance().DrawSphere(center, radius - (radius * radiusThickness), radiusThicknessCol, true);
		}

	}
	
}

glm::vec3 SphereEmitter::GetRandomPointInSphere(glm::vec3 minDir, glm::vec3 maxDir)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	// Generate random angles	
	float theta = glm::mix(minDir.x, maxDir.x, dist(gen)) * glm::pi<float>();  // [minDir.x, maxDir.x] mapped to [0, π]
	float phi = glm::mix(minDir.y, maxDir.y, dist(gen)) * glm::pi<float>();    // [minDir.y, maxDir.y] mapped to [0, π]

	// Convert spherical coordinates to Cartesian coordinates
	float x = radius * std::sin(phi) * std::cos(theta);
	float y = radius * std::sin(phi) * std::sin(theta);
	float z = radius * std::cos(phi);

	// Return the random point inside the sphere
	return glm::vec3(x, y, z);
}
