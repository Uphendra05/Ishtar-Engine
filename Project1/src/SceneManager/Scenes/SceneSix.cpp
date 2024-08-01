#include "SceneSix.h"
#include "../../ApplicationRenderer.h"
#include"../../AI/Enemy.h"

SceneSix::SceneSix(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{

}

void SceneSix::Start()
{

    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));


    PlayerController* player = new PlayerController(application);

    PhysXObject* plane = new PhysXObject();
    plane->LoadModel("Models/Terrain/Terrain.fbx");
    plane->transform.SetPosition(glm::vec3(0,-4.f,0));
    plane->transform.SetScale(glm::vec3(2,1,2));
    plane->transform.SetRotation(glm::vec3(-90,0,0));
    plane->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);
    GraphicsRender::GetInstance().AddModelAndShader(plane, application->defaultShader);


    
    Enemy* enemyOne = new Enemy(player);

    enemyOne->name = "Enemy 1";

    enemyOne->AddRoamingPoints(-20, 1, 1);
    enemyOne->AddRoamingPoints(-20, 1, -9.50f);

}

void SceneSix::Update()
{
}

void SceneSix::Render()
{
}
