#pragma once
#include "../BaseScene.h"
class SceneOne : public BaseScene
{
public:
	SceneOne(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
};

