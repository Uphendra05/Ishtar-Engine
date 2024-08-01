#include "SceneThree.h"
#include "../../ApplicationRenderer.h"

SceneThree::SceneThree(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{

}

void SceneThree::Start()
{
    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));


   /* Model* LODTest = new Model("Models/LOD_test/LOD_test.fbx");
    LODTest->name = "LOD Mesh";
    LODTest->useLOD = true;
    LODTest->AddLODGroup({ 0 }, 2);
    LODTest->AddLODGroup({ 1 }, 6);
    LODTest->AddLODGroup({ 2 }, 9);
    GraphicsRender::GetInstance().AddModelAndShader(LODTest, application->defaultShader);*/

    Model* Tree = new Model("Models/Tree/TreeTwo.fbx");
    Tree->transform.SetScale(glm::vec3(0.01f));
    Tree->name = "LOD Mesh";
    Tree->useLOD = true;
    Tree->AddLODGroup({ 0 }, 15);
    Tree->AddLODGroup({ 1 }, 28);
    Tree->AddLODGroup({ 2 }, 32);
    GraphicsRender::GetInstance().AddModelAndShader(Tree, application->defaultShader);

    Model* defaultCube = new Model("Models/DefaultCube/DefaultCube.fbx");
    defaultCube->name = "Cube";
    defaultCube->transform.SetPosition(glm::vec3(3.5f, 0, 0));
    GraphicsRender::GetInstance().AddModelAndShader(defaultCube, application->defaultShader);

}

void SceneThree::Update()
{
}

void SceneThree::Render()
{
}
