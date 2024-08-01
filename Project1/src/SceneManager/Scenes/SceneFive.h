#pragma once
#include "../BaseScene.h"
#include "../../Audio/AudioSystem.h"
#include "../../Player/PlayerController.h"


class SceneFive : public BaseScene
{
public:
	SceneFive(const std::string& sceneName);
	// Inherited via BaseScene
	void Start() override;
	void Update() override;
	void Render() override;

	AudioSystem* audio = new AudioSystem();
	bool isPlaying = true;
	PlayerController* player;
};

