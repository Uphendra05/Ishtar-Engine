#pragma once

#include "../BaseScene.h"
class SceneNine : public BaseScene
{

public:
	SceneNine(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
private:
	

};

