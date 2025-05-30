#pragma once
#include "EntityManager/Entity.h"
class FogSystem : public Entity
{
public:
	FogSystem();

	// Inherited via Entity
	void Start() override {};

	void Update(float deltaTime) override {};

	void OnDestroy() override {};

	void Render() override {};

	 void DrawProperties() override;
	 void SceneDraw() override;

	 float fogDensity = 0.4f;
	 float fogStart = 8.0f;
	 float fogEnd = 40.0f;
	 glm::vec3 fogColor = { 0.49f,0.49f,0.49f };
	 bool fogActive = false;

};

