#include "VelocityOverLifetime.h"

void VelocityOverLifetime::DrawProperties()
{
	DrawBoolImGui("IsEnabled", this->isEnabled);

	if (isEnabled)
	{
		DrawFloatImGui("Particle Speed", particleSpeed);
	}

}

void VelocityOverLifetime::SceneDraw()
{

}
