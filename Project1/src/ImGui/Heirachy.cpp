#include "Heirachy.h"
#include "../EntityManager/EntityManager.h"
#include "../LightManager.h"
#include "../CameraManager.h"
#include "EditorLayout.h"

Heirachy::Heirachy()
{
    entityManager = &EntityManager::GetInstance();
    lightManager = &LightManager::GetInstance();
}

void Heirachy::OnRender(float windowWidth, float windowHeight)
{
    if (EditorLayout::GetInstance().IsMaximizePressed()) return;

    
    if (!isPanelOpen)
    {
        return;
    }

    if  (!ImGui::Begin("Hierarchy",&isPanelOpen) || !isEnable)
    {
        ImGui::End();
        return;
    }
    ShowAllCameras();
    ShowAllEntities();
    ShowLights();
    ImGui::End();

    

}

void Heirachy::ShowAllEntities()
{
    if (!ImGui::CollapsingHeader("Entities", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }

    std::unordered_map<std::string, Entity*>::iterator it;

    for (it = entityManager->listOfEntities.begin(); it != entityManager->listOfEntities.end(); ++it)
    {
        it->second->SceneDraw();
    }
}

void Heirachy::ShowLights()
{
    if (!ImGui::CollapsingHeader("Lights", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }
    std::vector<Light*> lights = lightManager->GetLightList();

    for (Light* light : lights)
    {
        light->SceneDraw();
    }

}

void Heirachy::ShowAllCameras()
{

    if (!ImGui::CollapsingHeader("Cameras", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }

    std::vector<Camera*> cameras = CameraManager::GetInstance().GetCameras();

    CameraManager::GetInstance().sceneViewCamera->SceneDraw();

    for (Camera* camera : cameras)
    {
        camera->SceneDraw();
    }
  
}
