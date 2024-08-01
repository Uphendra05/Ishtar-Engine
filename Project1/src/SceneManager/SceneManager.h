#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "BaseScene.h"

class ApplicationRenderer;

class SceneManager
{
public:

	static SceneManager& GetInstance();

	void AddScene(const std::string& sceneName, BaseScene* scene);
	void RemoveScene(const std::string& sceneName);
	void OnChangeScene(const std::string& sceneName);

	void Update();
	void Render();
	void ShutDown();

	BaseScene* GetScene(const std::string& sceneName);
	BaseScene* GetCurrentScene();

	ApplicationRenderer* application = nullptr;

private:

	std::string currentSceneName = "";
	std::unordered_map<std::string, BaseScene*> listOfScenes;

};

