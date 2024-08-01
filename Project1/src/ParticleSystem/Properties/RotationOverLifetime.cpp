#include "RotationOverLifetime.h"
#include "../../Math.h"

glm::vec3 RotationOverLifetime::AngularVelocity(Particle& particle)
{
	float lerpValue = MathUtils::Math::Remap(particle.currentLifetime, 0, particle.lifeTime, 1, 0);
	return Lerp(startRotation, endRotation, lerpValue);
	
}

void RotationOverLifetime::DrawProperties()
{
	float width = 150;
	DrawBoolImGui("IsEnabled", this->isEnabled);

	if (isEnabled)
	{
		DrawTransformVector3ImGui("Start Rotation", startRotation, 0, width);
		DrawTransformVector3ImGui("End Rotation", endRotation, 0, width);
	}
}

void RotationOverLifetime::SceneDraw()
{
}
