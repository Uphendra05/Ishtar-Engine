#pragma once
#pragma once
#include "../BaseScene.h"
class SceneTwo : public BaseScene
{
public:
	SceneTwo(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
};
