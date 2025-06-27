#pragma once
#include "../BaseScene.h"
class SceneEleven : public BaseScene
{ 
public:
	SceneEleven(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
};

