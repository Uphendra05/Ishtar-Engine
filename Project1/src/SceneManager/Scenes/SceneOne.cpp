#include "SceneOne.h"
#include "../../ApplicationRenderer.h"
#include "../../Player/PlayerController.h"
#include "../../PostProcessing bounds/CubeVolume.h"
SceneOne::SceneOne(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
	
}

void SceneOne::Start()
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
    player->transform.SetPosition(glm::vec3(0, 0, 0));

    PhysXObject* plane = new PhysXObject();
    plane->LoadModel("Models/Terrain/Terrain.fbx");
    plane->transform.SetPosition(glm::vec3(0, -4.f, 0));
    plane->transform.SetScale(glm::vec3(2, 1, 2));
    plane->transform.SetRotation(glm::vec3(-90, 0, 0));
    plane->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);
    GraphicsRender::GetInstance().AddModelAndShader(plane, application->defaultShader);


  


  //  CubeVolume* cube = new CubeVolume();
  //  cube->transform.SetPosition(glm::vec3(0, -1, 5));
  //  cube->transform.SetScale(glm::vec3(0.5f));
  //  cube->Intialize(application->gameScenecamera);
  //  cube->AddCubeEffects(eEffectType::CHROMATIC);
  //  cube->AddCubeEffects(eEffectType::PIXELIZATION);

  //  CubeVolume* cube2 = new CubeVolume();
  //  cube2->transform.SetPosition(glm::vec3(0, -1, 7));
  //  cube2->transform.SetScale(glm::vec3(0.5f));
  //  cube2->Intialize(application->gameScenecamera);
  //  cube2->AddCubeEffects(eEffectType::PIXELIZATION);

 
    //PhysXObject* cathedral = new PhysXObject();
  
    /*cathedral->LoadModel("Models/Cathedral/Cath.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(cathedral, application->defaultShader);
    cathedral->name = "Cathedral";
    cathedral->transform.SetPosition(glm::vec3(-61.7, 21.00, 83.40));
    cathedral->transform.SetRotation(glm::vec3(0, 0, 0));
    cathedral->transform.SetScale(glm::vec3(0.01, 0.01, 0.01));
    cathedral->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);*/

    //Model* tree = new Model("Models/Tree/NewTree.fbx");
    //GraphicsRender::GetInstance().AddModelAndShader(tree, application->defaultShader);

}

void SceneOne::Update()
{
}

void SceneOne::Render()
{
}
