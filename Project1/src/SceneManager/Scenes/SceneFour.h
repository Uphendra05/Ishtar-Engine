#pragma once
#include "../BaseScene.h"
#include "../../Player/PlayerController.h"
class SceneFour : public BaseScene
{
public:
	SceneFour(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
private:
};



