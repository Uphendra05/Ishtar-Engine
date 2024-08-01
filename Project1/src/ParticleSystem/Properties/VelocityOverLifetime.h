#pragma once
#include "../EmitterProperty.h"
class VelocityOverLifetime : public EmitterProperty
{
public:

	bool isEnabled = false;
	float particleSpeed = 10;
	// Inherited via EmitterProperty
	void DrawProperties() override;
	void SceneDraw() override;
};

