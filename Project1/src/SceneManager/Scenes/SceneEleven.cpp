#include "SceneEleven.h"
#include "../../RenderingPipeline/BaseRenderingPipeline.h"

SceneEleven::SceneEleven(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneEleven::Start()
{

    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);
    directionLight->castShadow = false;

    directionLight->transform.SetRotation(glm::vec3(-40, 0, 0));

    Model* Cube = new Model("Models/DefaultCube/DefaultCube.fbx");
    Cube->name = "Cube";
    Cube->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(1, 0, 0, 0))  ;
    Cube->castShadow = true;

    GraphicsRender::GetInstance().AddModelAndShader(Cube, application->defaultShader);

    Model* Cube1 = new Model("Models/DefaultCube/DefaultCube.fbx");
    Cube1->name = "Cube1";
    Cube1->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(0, 1, 0, 0));
    Cube1->transform.SetPosition(glm::vec3(-6.39, 0, 4.02));
    Cube1->castShadow = true;

    GraphicsRender::GetInstance().AddModelAndShader(Cube1, application->defaultShader);

    Model* Cube2 = new Model("Models/DefaultCube/DefaultCube.fbx");
    Cube2->name = "Cube2";
    Cube2->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(0, 0, 1, 0));
    Cube2->transform.SetPosition(glm::vec3(5.83, 0, 4.53));
    Cube2->castShadow = true;

    GraphicsRender::GetInstance().AddModelAndShader(Cube2, application->defaultShader);

    Model* Floor = new Model("Models/DefaultQuad/DefaultQuad.fbx");
    Floor->name = "Floor";
    Floor->transform.SetPosition(glm::vec3(0, -1.72, 0));
    Floor->transform.SetRotation(glm::vec3(-90, 0, 0));
    Floor->transform.SetScale(glm::vec3(50));
    Floor->castShadow = true;
    GraphicsRender::GetInstance().AddModelAndShader(Floor, application->defaultShader);


}

void SceneEleven::Update()
{
}

void SceneEleven::Render()
{
}
