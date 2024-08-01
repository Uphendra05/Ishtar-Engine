#pragma once
#include "../BaseScene.h"
class SceneSix: public BaseScene
{
public:
	SceneSix(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
};

