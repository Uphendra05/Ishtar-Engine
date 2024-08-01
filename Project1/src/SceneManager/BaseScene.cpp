#include "BaseScene.h"
#include "SceneManager.h"
#include "../ApplicationRenderer.h"

unsigned int BaseScene::sceneID = 0;

BaseScene::BaseScene()
{
	BaseScene::sceneID++;
}

BaseScene::BaseScene(std::string sceneName)
{
	BaseScene::sceneID++;

	this->sceneName = sceneName;

	SceneManager::GetInstance().AddScene(sceneName, this);
}

void BaseScene::ShutDown()
{
	InputManager::GetInstance().ClearObservers();
	GraphicsRender::GetInstance().CleanUpData();
	EntityManager::GetInstance().ClearEntitiesList();
	CameraManager::GetInstance().ClearCameras();

}
