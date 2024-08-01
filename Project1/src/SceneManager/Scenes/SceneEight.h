#pragma once
#include "../BaseScene.h"

class SceneEight : public BaseScene
{
public:
	SceneEight(const std::string& sceneName);
	~SceneEight();

	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;
	//AudioSystem* audio = new AudioSystem();

private:

};

