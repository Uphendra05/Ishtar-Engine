#include "SizeOverLifetime.h"
#include "../../Math.h"

glm::vec3 SizeOverLifetime::ScaleParticle(Particle& particle)
{
	float lerpValue = MathUtils::Math::Remap(particle.currentLifetime, 0, particle.lifeTime, 1, 0);

	return Lerp(startScale, endScale, lerpValue);
	
}

void SizeOverLifetime::DrawProperties()
{
	float width = 150;
	DrawBoolImGui("IsEnabled", this->isEnabled);

	if (isEnabled)
	{
		DrawTransformVector3ImGui("Start Scale", startScale, 0, width);
		DrawTransformVector3ImGui("End Scale", endScale, 0, width);
	}
}

void SizeOverLifetime::SceneDraw()
{
}
