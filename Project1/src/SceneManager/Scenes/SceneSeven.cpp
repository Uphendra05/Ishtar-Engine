#include "SceneSeven.h"
#include "../../ApplicationRenderer.h"

SceneSeven::SceneSeven(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneSeven::Start()
{
    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));

  
    const float spacing = 5.0f;
    for (size_t i = 0; i < 10; i++)
    {
        Model* Cube = new Model("Models/DefaultCube/DefaultCube.fbx");

        Cube->name = "Cube " + std::to_string(i);

        Cube->transform.SetPosition(glm::vec3(i * spacing, 0, 0));

       
        GraphicsRender::GetInstance().AddModelAndShader(Cube, application->defaultShader);
    }

    PhysXObject* CubePhy = new PhysXObject();

    CubePhy->LoadModel("Models/DefaultCube/DefaultCube.fbx");
    CubePhy->name = "Cube Phys";
    CubePhy->occulsionState = eOcculsionState::DYNAMIC;
    CubePhy->transform.SetPosition(glm::vec3(0, 5, 0));
    GraphicsRender::GetInstance().AddModelAndShader(CubePhy, application->defaultShader);
    CubePhy->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);

    OcculsionManager::GetInstance().InitializeOcculusion();



}

void SceneSeven::Update()
{
}

void SceneSeven::Render()
{
}
