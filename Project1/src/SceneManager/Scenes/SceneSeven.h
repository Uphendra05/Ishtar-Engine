
#pragma once
#include "../BaseScene.h"

class SceneSeven : public BaseScene
{
public:
	SceneSeven(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
};


