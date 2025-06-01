#pragma once


#include "../BaseScene.h"
class SceneTen : public BaseScene
{

public:
	SceneTen(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
private:


};