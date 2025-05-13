#pragma once
#include "../EntityManager/Entity.h"


class EmptyCheck : public Entity
{

public:
	EmptyCheck();
	~EmptyCheck();

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;
	void Render() override;

	void DrawProperties() override;
	void SceneDraw() override;
};

