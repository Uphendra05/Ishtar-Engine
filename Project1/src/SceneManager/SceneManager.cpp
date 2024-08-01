#include "SceneManager.h"
#include "../ApplicationRenderer.h"
SceneManager& SceneManager::GetInstance()
{
    
    static SceneManager instance;

    return instance;
}

void SceneManager::AddScene(const std::string& sceneName, BaseScene* scene)
{
    listOfScenes[sceneName] = scene;

    scene->sceneName = sceneName;
    scene->application = application;

    currentSceneName = sceneName;


}

void SceneManager::RemoveScene(const std::string& sceneName)
{
    listOfScenes.erase(sceneName);
}

void SceneManager::OnChangeScene(const std::string& sceneName)
{
   
    if (sceneName == "") return;

    //GetCurrentScene()->ShutDown();

    currentSceneName = sceneName;

    GetCurrentScene()->Start();


}



void SceneManager::Update()
{
    if (currentSceneName == "") return;

    GetCurrentScene()->Update();
}

void SceneManager::Render()
{
    if (currentSceneName == "") return;

    GetCurrentScene()->Render();

}

void SceneManager::ShutDown()
{
    if (currentSceneName == "") return;

    GetCurrentScene()->ShutDown();

}


BaseScene* SceneManager::GetScene(const std::string& sceneName)
{
    return listOfScenes[sceneName];
}

BaseScene* SceneManager::GetCurrentScene()
{
    return listOfScenes[currentSceneName];
}
