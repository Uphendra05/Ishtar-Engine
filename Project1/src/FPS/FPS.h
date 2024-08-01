#pragma once
#include "../EntityManager/EntityManager.h"
class FPS : public  Entity
{
public :

	FPS();
	// Inherited via Entity
	void Start() override {};
	void Update(float deltaTime) override {};
	void OnDestroy() override {};
	void Render() override {};

    void DrawProperties() override;
    void SceneDraw() override;
private:

	double currentFPS = 0;

};

