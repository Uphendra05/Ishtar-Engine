#pragma once
#pragma once
#include "../BaseScene.h"
class SceneThree : public BaseScene
{
public:
	SceneThree(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
};
