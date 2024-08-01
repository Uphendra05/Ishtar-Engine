#include "SceneFive.h"
#include "../../ApplicationRenderer.h"
#include "../../PostProcessing bounds/CubeVolume.h"
#include"../../AI/Enemy.h"
#include "../../Grass/GrassMesh.h"
#include "../../ParticleSystem/ParticleAssets/FireFly.h"
#include "../../Physics/Softbody/SoftBody.h"
#include "../../Threading/SoftBodyThread.h"


SoftBodyThread* sbThread = sbInfo;


SceneFive::SceneFive(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
	
}

void SceneFive::Start()
{
    StartThreadForSoftBody(0.01f);

    std::string diffuseTexturePath = "Models/Graveyard/Fences/atlas-universal-albedo-a.png";
    Texture* diffuseTexture = new Texture(diffuseTexturePath);

    std::string diffuseFoilage = "Models/Graveyard/Fences/foliage-a.png";
    Texture* diffFoilage = new Texture(diffuseFoilage);

    std::string diffuseTerPath2x = "Models/Terrain/2k_diffuse_2x.png";
    Texture* diffTerrain2x = new Texture(diffuseTerPath2x);

    std::string diffuseTerPath4x = "Models/Terrain/2k_diffuse_4x_.png";
    Texture* diffTerrain4x = new Texture(diffuseTerPath4x);

    std::string diffuseTexStatuePath = "Models/Graveyard/angelStatue.png";
    Texture* diffuseTexStatue = new Texture(diffuseTexStatuePath);

#pragma region Lights

    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.01, 0.01, 0.06,1));
    directionLight->SetColor(glm::vec4(0.01, 0.01, 0.06, 1));
    directionLight->SetAttenuation(0.1, 0.1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);
    directionLight->transform.SetRotation(glm::vec3(0, 90.00, 90.00));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));
    directionLight->isVisible = false;
    

    Light* pointLight = new Light();
    pointLight->Initialize(LightType::POINT_LIGHT, 1);
    pointLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    pointLight->SetColor(glm::vec4(0.81, 0.51, 0.24,1.0));
    pointLight->SetIntensity(1);
    pointLight->SetAttenuation(0.1, 0.1, 0.01f);
    pointLight->transform.SetRotation(glm::vec3(0));
    pointLight->transform.SetPosition(glm::vec3(-76.42, 4.16, 86.84));
    pointLight->isVisible = false;

    Light* pointLight2 = new Light();
    pointLight2->Initialize(LightType::POINT_LIGHT, 1);
    pointLight2->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    pointLight2->SetColor(glm::vec4(0.81, 0.51, 0.24, 1.0));
    pointLight2->SetIntensity(1);
    pointLight2->SetAttenuation(0.1, 0.1, 0.01f);
    pointLight2->transform.SetRotation(glm::vec3(0));
    pointLight2->transform.SetPosition(glm::vec3(-76.42, 6.85, 76.63));
    pointLight2->isVisible = false;

    Light* pointLight3 = new Light();
    pointLight3->Initialize(LightType::POINT_LIGHT, 1);
    pointLight3->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    pointLight3->SetColor(glm::vec4(0.81, 0.51, 0.24, 1.0));
    pointLight3->SetIntensity(1);
    pointLight3->SetAttenuation(0.1, 0.1, 0.01f);
    pointLight3->transform.SetRotation(glm::vec3(0));
    pointLight3->transform.SetPosition(glm::vec3(-53.22, 8.27, 78.41));
    pointLight3->isVisible = false;

    Light* pointLight4 = new Light();
    pointLight4->Initialize(LightType::POINT_LIGHT, 1);
    pointLight4->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    pointLight4->SetColor(glm::vec4(0.81, 0.51, 0.24, 1.0));
    pointLight4->SetIntensity(1);
    pointLight4->SetAttenuation(0.1, 0.1, 0.01f);
    pointLight4->transform.SetRotation(glm::vec3(0));
    pointLight4->transform.SetPosition(glm::vec3(-37.86, 5.37, 54.31));
    pointLight4->isVisible = false;

    Light* pointLight5 = new Light();
    pointLight5->Initialize(LightType::POINT_LIGHT, 1);
    pointLight5->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    pointLight5->SetColor(glm::vec4(0.81, 0.51, 0.24, 1.0));
    pointLight5->SetIntensity(1);
    pointLight5->SetAttenuation(0.1,0.1, 0.01f);
    pointLight5->transform.SetRotation(glm::vec3(0));
    pointLight5->transform.SetPosition(glm::vec3(-23.69, 3.73, 67.31));
    pointLight5->isVisible = false;

    Light* moonLight = new Light();
    moonLight->Initialize(LightType::POINT_LIGHT, 1);
    moonLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    moonLight->SetColor(glm::vec4(5));
    moonLight->SetIntensity(100);
    moonLight->SetAttenuation(0.1, 0.1, 0.01f);
    moonLight->transform.SetRotation(glm::vec3(0));
    moonLight->transform.SetPosition(glm::vec3(10.11, 93.11, -116.19));
    moonLight->name = "Moon Light";
    moonLight->isVisible = false;

    

#pragma endregion


 



    player = new PlayerController(application);
    player->transform.SetPosition(glm::vec3(-75.64, 3.27, 105.30));

   

    PhysXObject* terrain = new PhysXObject();
    terrain->occulsionState = eOcculsionState::NO_OCCULSION;
    terrain->LoadModel("Models/Terrain/Terrain2.fbx");
    terrain->meshes[0]->meshMaterial->material()->diffuseTexture = diffTerrain4x;
    GraphicsRender::GetInstance().AddModelAndShader(terrain, application->defaultShader);
    terrain->name = "Terrain";
    terrain->transform.SetPosition(glm::vec3(0, -2, 0));
    terrain->transform.SetRotation(glm::vec3(0, 0, 0));
    terrain->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


   
#pragma region Wall and Gate

    PhysXObject* gate = new PhysXObject();
    gate->LoadModel("Models/Graveyard/Fences/Gate.fbx");
    gate->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(gate, application->defaultShader);
    gate->name = "Gate";
    gate->transform.SetPosition(glm::vec3(-76.10, 4.00, 106.90));
    gate->transform.SetRotation(glm::vec3(0, 50, 0));
    gate->transform.SetScale(glm::vec3(0.015));
    gate->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);



    PhysXObject* wall = new PhysXObject();
    wall->LoadModel("Models/Graveyard/Fences/WallBig.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(wall, application->defaultShader);
    wall->name = "Wall";
    wall->transform.SetPosition(glm::vec3(-82.10, 4.00, 107.50));
    wall->transform.SetRotation(glm::vec3(0, 1.50, 0));
    wall->transform.SetScale(glm::vec3(0.015));
    wall->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);



    PhysXObject* wallCopy = new PhysXObject();
    wallCopy->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy, application->defaultShader);
    wallCopy->name = "Wall 1";
    wallCopy->transform.SetPosition(glm::vec3(-70.00, 4.00, 106.10));
    wallCopy->transform.SetRotation(glm::vec3(0, 6.20, 0));
    wallCopy->transform.SetScale(glm::vec3(0.015));
    wallCopy->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* corner = new PhysXObject();
    corner->LoadModel("Models/Graveyard/Fences/CornerBig.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(corner, application->defaultShader);
    corner->name = "Corner";
    corner->transform.SetPosition(glm::vec3(-86.40, 3.95, 106.80));
    corner->transform.SetRotation(glm::vec3(0, 280.90, 0));
    corner->transform.SetScale(glm::vec3(0.015, 0.015, -0.01));
    corner->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* wallCopy2 = new PhysXObject();
    wallCopy2->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy2, application->defaultShader);
    wallCopy2->name = "Wall 2";
    wallCopy2->transform.SetPosition(glm::vec3(-88.50, 4.00, 101.20));
    wallCopy2->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy2->transform.SetScale(glm::vec3(0.015));
    wallCopy2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);


    PhysXObject* corner2 = new PhysXObject();
    corner2->LoadModel("Models/Graveyard/Fences/CornerSmall.fbx");
    corner2->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(corner2, application->defaultShader);
    corner2->name = "Corner";
    corner2->transform.SetPosition(glm::vec3(-67.60, 2.95, 105.90));
    corner2->transform.SetRotation(glm::vec3(0, 363.10, 0));
    corner2->transform.SetScale(glm::vec3(0.015, 0.015, -0.015));
    corner2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* wallCopy3 = new PhysXObject();
    wallCopy3->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy3, application->defaultShader);
    wallCopy3->name = "Wall 3";
    wallCopy3->transform.SetPosition(glm::vec3(-89.70, 4.00, 96.90));
    wallCopy3->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy3->transform.SetScale(glm::vec3(0.015));
    wallCopy3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy4 = new PhysXObject();
    wallCopy4->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy4, application->defaultShader);
    wallCopy4->name = "Wall 4";
    wallCopy4->transform.SetPosition(glm::vec3(-90.80, 4.00, 92.50));
    wallCopy4->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy4->transform.SetScale(glm::vec3(0.015));
    wallCopy4->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy5 = new PhysXObject();
    wallCopy5->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy5, application->defaultShader);
    wallCopy5->name = "Wall 5";
    wallCopy5->transform.SetPosition(glm::vec3(-92.00, 4.00, 88.20));
    wallCopy5->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy5->transform.SetScale(glm::vec3(0.015));
    wallCopy5->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy6 = new PhysXObject();
    wallCopy6->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy6, application->defaultShader);
    wallCopy6->name = "Wall 6";
    wallCopy6->transform.SetPosition(glm::vec3(-93.20, 4.10, 83.90));
    wallCopy6->transform.SetRotation(glm::vec3(0, -74.80, 0));
    wallCopy6->transform.SetScale(glm::vec3(0.015));
    wallCopy6->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy7 = new PhysXObject();
    wallCopy7->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy7, application->defaultShader);
    wallCopy7->name = "Wall 7";
    wallCopy7->transform.SetPosition(glm::vec3(-94.40, 5.70, 79.80));
    wallCopy7->transform.SetRotation(glm::vec3(0, 107.40, 0));
    wallCopy7->transform.SetScale(glm::vec3(0.015));
    wallCopy7->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy8 = new PhysXObject();
    wallCopy8->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy8, application->defaultShader);
    wallCopy8->name = "Wall 8";
    wallCopy8->transform.SetPosition(glm::vec3(-95.70, 6.60, 75.70));
    wallCopy8->transform.SetRotation(glm::vec3(0, 107.40, 0));
    wallCopy8->transform.SetScale(glm::vec3(0.015));
    wallCopy8->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy10 = new PhysXObject();
    wallCopy10->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy10, application->defaultShader);
    wallCopy10->name = "Wall 10";
    wallCopy10->transform.SetPosition(glm::vec3(-66.20, 4.00, 102.30));
    wallCopy10->transform.SetRotation(glm::vec3(0, 87.80, 0));
    wallCopy10->transform.SetScale(glm::vec3(0.015));
    wallCopy10->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy11 = new PhysXObject();
    wallCopy11->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy11, application->defaultShader);
    wallCopy11->name = "Wall 11";
    wallCopy11->transform.SetPosition(glm::vec3(-66.00, 4.00, 97.70));
    wallCopy11->transform.SetRotation(glm::vec3(0, 87.80, 0));
    wallCopy11->transform.SetScale(glm::vec3(0.015));
    wallCopy11->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy12 = new PhysXObject();
    wallCopy12->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy12, application->defaultShader);
    wallCopy12->name = "Wall 12";
    wallCopy12->transform.SetPosition(glm::vec3(-65.80, 4.00, 93.10));
    wallCopy12->transform.SetRotation(glm::vec3(0, 87.80, 0));
    wallCopy12->transform.SetScale(glm::vec3(0.015));
    wallCopy12->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy13 = new PhysXObject();
    wallCopy13->LoadModel("Models/Graveyard/Fences/Wall.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy13, application->defaultShader);
    wallCopy13->name = "Wall 13";
    wallCopy13->transform.SetPosition(glm::vec3(-37.94, 6.40, 86.14));
    wallCopy13->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy13->transform.SetScale(glm::vec3(0.015));
    wallCopy13->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    PhysXObject* wallCopy14 = new PhysXObject();
    wallCopy14->LoadModel(*wallCopy13);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy14, application->defaultShader);
    wallCopy14->name = "Wall 14";
    wallCopy14->transform.SetPosition(glm::vec3(-34.92, 5.38, 86.14));
    wallCopy14->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy14->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy14->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* wallCopy15 = new PhysXObject();
    wallCopy15->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy15, application->defaultShader);
    wallCopy15->name = "Wall 15";
    wallCopy15->transform.SetPosition(glm::vec3(-30.03, 5.52, 86.14));
    wallCopy15->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy15->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy15->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);


    PhysXObject* wallCopy16 = new PhysXObject();
    wallCopy16->LoadModel(*wallCopy13);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy16, application->defaultShader);
    wallCopy16->name = "Wall 16";
    wallCopy16->transform.SetPosition(glm::vec3(-27.69, 4.46, 86.14));
    wallCopy16->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy16->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy16->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* corner3 = new PhysXObject();
    corner3->LoadModel(*corner2);
    GraphicsRender::GetInstance().AddModelAndShader(corner3, application->defaultShader);
    corner3->name = "Corner 3";
    corner3->transform.SetPosition(glm::vec3(-24.97, 4.27, 86.15));
    corner3->transform.SetRotation(glm::vec3(0, 0, 0));
    corner3->transform.SetScale(glm::vec3(0.015, 0.015, -0.015));
    corner3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* corner4 = new PhysXObject();
    corner4->LoadModel(*corner2);
    GraphicsRender::GetInstance().AddModelAndShader(corner4, application->defaultShader);
    corner4->name = "Corner 4";
    corner4->transform.SetPosition(glm::vec3(-23.55, 3.94, 84.94));
    corner4->transform.SetRotation(glm::vec3(0, 80.10, 0));
    corner4->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    corner4->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* corner5 = new PhysXObject();
    corner5->LoadModel(*corner2);
    GraphicsRender::GetInstance().AddModelAndShader(corner5, application->defaultShader);
    corner5->name = "Corner 5";
    corner5->transform.SetPosition(glm::vec3(-21.77, 3.57, 83.75));
    corner5->transform.SetRotation(glm::vec3(0, 10.10, 0));
    corner5->transform.SetScale(glm::vec3(0.015, 0.015, -0.015));
    corner5->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    PhysXObject* corner6 = new PhysXObject();
    corner6->LoadModel(*corner2);
    GraphicsRender::GetInstance().AddModelAndShader(corner6, application->defaultShader);
    corner6->name = "Corner 6";
    corner6->transform.SetPosition(glm::vec3(-16.07, 2.84, 81.92));
    corner6->transform.SetRotation(glm::vec3(0, 0, 0));
    corner6->transform.SetScale(glm::vec3(0.015, 0.015, -0.015));
    corner6->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* wallCopy17 = new PhysXObject();
    wallCopy17->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy17, application->defaultShader);
    wallCopy17->name = "Wall 17";
    wallCopy17->transform.SetPosition(glm::vec3(-18.62, 4.23, 81.94));
    wallCopy17->transform.SetRotation(glm::vec3(0, 0, 0));
    wallCopy17->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy17->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy18 = new PhysXObject();
    wallCopy18->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy18, application->defaultShader);
    wallCopy18->name = "Wall 18";
    wallCopy18->transform.SetPosition(glm::vec3(-53.53, 7.74, 48.31));
    wallCopy18->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy18->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy18->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy19 = new PhysXObject();
    wallCopy19->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy19, application->defaultShader);
    wallCopy19->name = "Wall 19";
    wallCopy19->transform.SetPosition(glm::vec3(-49.18, 6.54, 48.31));
    wallCopy19->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy19->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy19->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy20 = new PhysXObject();
    wallCopy20->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy20, application->defaultShader);
    wallCopy20->name = "Wall 20";
    wallCopy20->transform.SetPosition(glm::vec3(-44.68, 6.23, 48.31));
    wallCopy20->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy20->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy20->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy21 = new PhysXObject();
    wallCopy21->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy21, application->defaultShader);
    wallCopy21->name = "Wall 21";
    wallCopy21->transform.SetPosition(glm::vec3(-40.19, 6.22, 48.31));
    wallCopy21->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy21->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy21->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy22 = new PhysXObject();
    wallCopy22->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy22, application->defaultShader);
    wallCopy22->name = "Wall 22";
    wallCopy22->transform.SetPosition(glm::vec3(-35.64, 6.23, 48.31));
    wallCopy22->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy22->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy22->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* wallCopy23 = new PhysXObject();
    wallCopy23->LoadModel(*wall);
    GraphicsRender::GetInstance().AddModelAndShader(wallCopy23, application->defaultShader);
    wallCopy23->name = "Wall 23";
    wallCopy23->transform.SetPosition(glm::vec3(-31.11, 6.19, 48.31));
    wallCopy23->transform.SetRotation(glm::vec3(0, 180.00, 0));
    wallCopy23->transform.SetScale(glm::vec3(0.015, 0.015, 0.015));
    wallCopy23->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* FenceBig = new PhysXObject();
    FenceBig->LoadModel("Models/Graveyard/Fences/FenceBig.fbx");
    FenceBig->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(FenceBig, application->defaultShader);
    FenceBig->name = "Fence Big";
    FenceBig->transform.SetPosition(glm::vec3(-65.16, 7.12, 83.13));
    FenceBig->transform.SetRotation(glm::vec3(-90.00, 0, 0));
    FenceBig->transform.SetScale(glm::vec3(1, 1, 1.1));
    FenceBig->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

#pragma endregion


   

   
#pragma region House

    std::string RoofPath = "Models/Graveyard/Fences/Roof_01.png";
    std::string bodyPath = "Models/Graveyard/Fences/PolygonDarkFantasy_Texture_04_A.png";
    Texture* roof = new Texture(RoofPath);
    Texture* body = new Texture(bodyPath);
    //try to bring in the Cathedral
    PhysXObject* BigHouse = new PhysXObject();
    BigHouse->LoadModel("Models/Graveyard/Fences/BigHouse.fbx");
    BigHouse->meshes[0]->meshMaterial->material()->diffuseTexture = body;
    BigHouse->meshes[1]->meshMaterial->material()->diffuseTexture = roof;
    GraphicsRender::GetInstance().AddModelAndShader(BigHouse, application->defaultShader);
    BigHouse->name = "Big House";
    BigHouse->transform.SetPosition(glm::vec3(-47.18, 7.35, 80.54));
    BigHouse->transform.SetRotation(glm::vec3(0, -125.10, 0));
    BigHouse->transform.SetScale(glm::vec3(0.02, 0.014, 0.02));
    BigHouse->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    PhysXObject* BigHouse2 = new PhysXObject();
    BigHouse2->LoadModel(*BigHouse);
    GraphicsRender::GetInstance().AddModelAndShader(BigHouse2, application->defaultShader);
    BigHouse2->name = "Big House 2";
    BigHouse2->transform.SetPosition(glm::vec3(-32.74, 4.16, 55.15));
    BigHouse2->transform.SetRotation(glm::vec3(0, -46.60, 0));
    BigHouse2->transform.SetScale(glm::vec3(0.01));
    BigHouse2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* BigHouse3 = new PhysXObject();
    BigHouse3->LoadModel(*BigHouse);
    GraphicsRender::GetInstance().AddModelAndShader(BigHouse3, application->defaultShader);
    BigHouse3->name = "Big House";
    BigHouse3->transform.SetPosition(glm::vec3(-88.12, 3.32, 88.25));
    BigHouse3->transform.SetRotation(glm::vec3(0, 85.20, 0));
    BigHouse3->transform.SetScale(glm::vec3(0.01));
    BigHouse3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

#pragma endregion



#pragma region Trees


    PhysXObject* Tree = new PhysXObject();
    Tree->LoadModel("Models/Tree/TreeTwo.fbx");
    Tree->name = "Tree";
    Tree->useLOD = true;
    Tree->AddLODGroup({ 0 }, 10);
    Tree->AddLODGroup({ 1 }, 23);
    Tree->AddLODGroup({ 2 }, 27);
    Tree->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    Tree->meshes[1]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    Tree->meshes[2]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(Tree, application->defaultShader);
    Tree->transform.SetPosition(glm::vec3(-68.67, 3.16, 99.81));
    Tree->transform.SetRotation(glm::vec3(0, -26.20, 0));
    Tree->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    Tree->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* Tree2 = new PhysXObject();
    Tree2->LoadModel(*Tree);
    Tree2->useLOD = true;
    Tree2->AddLODGroup({ 0 }, 15);
    Tree2->AddLODGroup({ 1 }, 28);
    Tree2->AddLODGroup({ 2 }, 32);
    GraphicsRender::GetInstance().AddModelAndShader(Tree2, application->defaultShader);
    Tree2->name = "Tree2";
    Tree2->transform.SetPosition(glm::vec3(-42.05, 7.28, 85.52));
    Tree2->transform.SetRotation(glm::vec3(0, 31.00, 0));
    Tree2->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    Tree2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* Tree3 = new PhysXObject();
    Tree3->LoadModel(*Tree);
    Tree3->useLOD = true;
    Tree3->AddLODGroup({ 0 }, 15);
    Tree3->AddLODGroup({ 1 }, 28);
    Tree3->AddLODGroup({ 2 }, 32);
    GraphicsRender::GetInstance().AddModelAndShader(Tree3, application->defaultShader);
    Tree3->name = "Tree3";
    Tree3->transform.SetPosition(glm::vec3(-92.69, 4.98, 71.95));
    Tree3->transform.SetRotation(glm::vec3(7.40, 40.10, 0));
    Tree3->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    Tree3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* Tree4 = new PhysXObject();
    Tree4->LoadModel(*Tree);
    Tree4->useLOD = true;
    Tree4->AddLODGroup({ 0 }, 15);
    Tree4->AddLODGroup({ 1 }, 28);
    Tree4->AddLODGroup({ 2 }, 32);
    GraphicsRender::GetInstance().AddModelAndShader(Tree4, application->defaultShader);
    Tree4->name = "Tree4";
    Tree4->transform.SetPosition(glm::vec3(-61.58, 8.83, 50.88));
    Tree4->transform.SetRotation(glm::vec3(0, 40.10, 0));
    Tree4->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    Tree4->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* Tree5 = new PhysXObject();
    Tree5->LoadModel(*Tree);
    Tree5->useLOD = true;
    Tree5->AddLODGroup({ 0 }, 15);
    Tree5->AddLODGroup({ 1 }, 28);
    Tree5->AddLODGroup({ 2 }, 32);
    GraphicsRender::GetInstance().AddModelAndShader(Tree5, application->defaultShader);
    Tree5->name = "Tree5";
    Tree5->transform.SetPosition(glm::vec3(-77.65, 3.48, 84.19));
    Tree5->transform.SetRotation(glm::vec3(0, 157.70, 0));
    Tree5->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    Tree5->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);



    PhysXObject* TreeOne = new PhysXObject();
    TreeOne->LoadModel("Models/Tree/NewTree.fbx");
    TreeOne->useLOD = true;
    TreeOne->AddLODGroup({ 0 }, 15);
    TreeOne->AddLODGroup({ 1 }, 28);
    TreeOne->AddLODGroup({ 2 }, 32);
    TreeOne->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    TreeOne->meshes[1]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    TreeOne->meshes[2]->meshMaterial->material()->diffuseTexture = diffuseTexture;

    GraphicsRender::GetInstance().AddModelAndShader(TreeOne, application->defaultShader);
    TreeOne->name = "TreeOne";
    TreeOne->transform.SetPosition(glm::vec3(-64.96, 7.06, 85.66));
    TreeOne->transform.SetRotation(glm::vec3(0, -26.20, 0));
    TreeOne->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    TreeOne->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* TreeOne1 = new PhysXObject();
    TreeOne1->LoadModel(*TreeOne);
    TreeOne1->useLOD = true;
    TreeOne1->AddLODGroup({ 0 }, 15);
    TreeOne1->AddLODGroup({ 1 }, 28);
    TreeOne1->AddLODGroup({ 2 }, 32);
    GraphicsRender::GetInstance().AddModelAndShader(TreeOne1, application->defaultShader);
    TreeOne1->name = "TreeOne1";
    TreeOne1->transform.SetPosition(glm::vec3(-47.46, 7.47, 88.37));
    TreeOne1->transform.SetRotation(glm::vec3(0, -26.20, 0));
    TreeOne1->transform.SetScale(glm::vec3(0.013, 0.013, 0.013));
    TreeOne1->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    MeshInstance* instanceMesh = new MeshInstance();
    instanceMesh->LoadModel("Models/Graveyard/TreeThree.fbx");
    instanceMesh->name = "InstancedTree";
    //instanceMesh->isVisible = false;
    instanceMesh->meshes[0]->meshMaterial->material()->specular = 0;
    instanceMesh->meshes[1]->meshMaterial->material()->specular = 0;
    instanceMesh->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(0.3, 0.2, 0.1, 1));
    instanceMesh->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(0, 0.4, 0, 1));
    instanceMesh->AddTransformData(glm::vec3(-98.32, 1.77, 101.94), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-95.13, 0.77, 97.47), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-95.13, 1.77, 102.73), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-95.13, 0.77, 108.11), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-90.26, 1.77, 108.11), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-98.09, 0.77, 93.41), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-104.33, 3.07, 93.41), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-104.33, 1.07, 93.41), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-104.33, 3.07, 88.94), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-94.99, 1.97, 91.27), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-98.82, 0.97, 87.12), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-102.19, 3.53, 83.21), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-97.01, 2.53, 83.21), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-82.33, 1.97, 110.49), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-80.46, 0.97, 113.56), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-77.43, 1.97, 111.13), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-72.91, 0.97, 117.52), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-71.19, 1.97, 113.00), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-68.77, 0.97, 115.72), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-68.77, 1.97, 118.15), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-65.35, 0.97, 118.15), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-62.96, 1.97, 111.69), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-60.33, 0.62, 115.69), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-57.02, 0.98, 114.39), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-57.02, 0.62, 110.60), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-60.06, 0.96, 106.27), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-63.35, 1.77, 106.27), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-59.32, 0.78, 101.12), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-59.32, 2.34, 97.52), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-56.83, 2.34, 97.52), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-54.54, 1.68, 101.18), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-51.53, 0.89, 105.44), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-49.94, -0.29, 110.66), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-47.51, 1.0, 101.94), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-47.51, 1.0, 98.24), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-43.97, 0.0, 98.24), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-42.61, 1.0, 101.94), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-40.17, 1.0, 105.70), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-44.07, -0.49, 111.41), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-40.22, 0.20, 111.41), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-36.27, -0.66, 111.41), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-36.27, 0.14, 106.71), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-36.27, 0.14, 106.71), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-36.27, 1.19, 101.03), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-32.86, 0.84, 101.03), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-32.86, 1.06, 96.13), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-28.64, 2.06, 94.78), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-28.64, 2.21, 91.45), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-24.46, 1.94, 94.31), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-24.46, 1.34, 89.01), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-20.30, 1.08, 93.72), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-18.33, 1.50, 97.07), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-22.73, 0.97, 102.54), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-22.73, 0.97, 107.50), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-19.36, 0.51, 85.86), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-15.40, 2.08, 89.22), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-10.40, 1.08, 84.37), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-8.91, 0.74, 89.37), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-8.55, 0.74, 95.91), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-13.24, -1.25, 103.30), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-90.19, 0.48, 114.52), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-94.50, -0.79, 114.52), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-90.45, -1.45, 116.00), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-85.05, 0.10, 117.00), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-78.48, 0.62, 116.36), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-30.68, -1.65, 107.57), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-27.22, -0.70, 100.86), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-97.82, 4.89, 77.90), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-99.44, 5.26, 75.23), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-102.34, 5.26, 77.13), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-101.09, 5.85, 71.98), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-98.47, 4.85, 67.49), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-106.05, 4.39, 71.40), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-107.24, 3.25, 75.06), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-108.29, 3.77, 79.92), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-111.27, 2.93, 76.27), glm::vec3(0, 90, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-104.65, 4.25, 65.32), glm::vec3(0, 180, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-109.55, 4.25, 62.79), glm::vec3(0, 270, 0), glm::vec3(0.015));
    instanceMesh->AddTransformData(glm::vec3(-111.77, 5.25, 66.75), glm::vec3(0, 90, 0), glm::vec3(0.015));



    GraphicsRender::GetInstance().AddModelAndShader(instanceMesh, application->defaultInstanceShader);


    PhysXObject* TreeNew = new PhysXObject();
    TreeNew->LoadModel("Models/Graveyard/TreeNew.fbx");
    TreeNew->meshes[0]->meshMaterial->material()->diffuseTexture = body;
    GraphicsRender::GetInstance().AddModelAndShader(TreeNew, application->defaultShader);
    TreeNew->name = "TreeNew";
    TreeNew->transform.SetPosition(glm::vec3(-45.50, 7.27, 67.61));
    TreeNew->transform.SetRotation(glm::vec3(0, -76.80, 0));
    TreeNew->transform.SetScale(glm::vec3(0.013));
    TreeNew->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


#pragma endregion


   

  


   /* Model* dummy = new Model();
    dummy->LoadModel("Models/Graveyard/TreeThree.fbx");
    dummy->name = "dummy";
    dummy->transform.SetPosition(glm::vec3(-32.86, 2.06, 96.13));
    dummy->transform.SetRotation(glm::vec3(0));
    dummy->transform.SetScale(glm::vec3(0.015));
    GraphicsRender::GetInstance().AddModelAndShader(dummy, application->defaultShader);*/

#pragma region Rocks

    PhysXObject* Rocks = new PhysXObject();
    Rocks->LoadModel("Models/Graveyard/Fences/Rocks.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(Rocks, application->defaultShader);
    Rocks->name = "Rocks";
    Rocks->transform.SetPosition(glm::vec3(-70.00, 3.10, 88.80));
    Rocks->transform.SetRotation(glm::vec3(-30.70, -26.30, -7.70));
    Rocks->transform.SetScale(glm::vec3(0.007));
    Rocks->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* Rocks2 = new PhysXObject();
    Rocks2->LoadModel("Models/Graveyard/Fences/RocksTwo.fbx");
    Rocks2->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(Rocks2, application->defaultShader);
    Rocks2->name = "Rocks";
    Rocks2->transform.SetPosition(glm::vec3(-84.00, 5.70, 53.90));
    Rocks2->transform.SetRotation(glm::vec3(-90.00, 0, 0));
    Rocks2->transform.SetScale(glm::vec3(1.50));
    Rocks2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    PhysXObject* RocksAlone = new PhysXObject();
    RocksAlone->LoadModel("Models/Graveyard/RocksOne.fbx");
    RocksAlone->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(RocksAlone, application->defaultShader);
    RocksAlone->name = "Rocks Alone";
    RocksAlone->transform.SetPosition(glm::vec3(-26.44, 2.91, 51.96));
    RocksAlone->transform.SetRotation(glm::vec3(0, 102.90, 0));
    RocksAlone->transform.SetScale(glm::vec3(0.01, 0.01, 0.01));
    RocksAlone->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* RocksAlone1 = new PhysXObject();
    RocksAlone1->LoadModel(*RocksAlone);
    GraphicsRender::GetInstance().AddModelAndShader(RocksAlone1, application->defaultShader);
    RocksAlone1->name = "Rocks Alone 1";
    RocksAlone1->transform.SetPosition(glm::vec3(-23.35, 1.15, 60.93));
    RocksAlone1->transform.SetRotation(glm::vec3(0, -63.20, 0));
    RocksAlone1->transform.SetScale(glm::vec3(0.01, 0.01, 0.01));
    RocksAlone1->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* RocksAlone2 = new PhysXObject();
    RocksAlone2->LoadModel(*RocksAlone);
    GraphicsRender::GetInstance().AddModelAndShader(RocksAlone2, application->defaultShader);
    RocksAlone2->name = "Rocks Alone 2";
    RocksAlone2->transform.SetPosition(glm::vec3(-18.62, 0.74, 68.53));
    RocksAlone2->transform.SetRotation(glm::vec3(0, 111.20, 0));
    RocksAlone2->transform.SetScale(glm::vec3(0.01, 0.01, 0.01));
    RocksAlone2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* RocksAlone3 = new PhysXObject();
    RocksAlone3->LoadModel(*RocksAlone);
    GraphicsRender::GetInstance().AddModelAndShader(RocksAlone3, application->defaultShader);
    RocksAlone3->name = "Rocks Alone 3";
    RocksAlone3->transform.SetPosition(glm::vec3(-15.61, 5.45, 76.95));
    RocksAlone3->transform.SetRotation(glm::vec3(0, -130.40, 180.00));
    RocksAlone3->transform.SetScale(glm::vec3(0.01, 0.01, 0.01));
    RocksAlone3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

#pragma endregion

   

    PhysXObject* TombOne = new PhysXObject();
    TombOne->LoadModel("Models/Graveyard/TombOne.fbx");
    TombOne->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(TombOne, application->defaultShader);
    TombOne->name = "TombOne";
    TombOne->transform.SetPosition(glm::vec3(-35.00, 7.37, 81.68));
    TombOne->transform.SetRotation(glm::vec3(0, -90.00, 0));
    TombOne->transform.SetScale(glm::vec3(0.02, 0.02, 0.02));
    TombOne->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* TombTwo = new PhysXObject();
    TombTwo->LoadModel("Models/Graveyard/TombTwo.fbx");
    TombTwo->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(TombTwo, application->defaultShader);
    TombTwo->name = "TombTwo";
    TombTwo->transform.SetPosition(glm::vec3(-31.34, 5.97, 82.71));
    TombTwo->transform.SetRotation(glm::vec3(0, -90.00, 0));
    TombTwo->transform.SetScale(glm::vec3(0.01));
    TombTwo->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* TombThree = new PhysXObject();
    TombThree->LoadModel("Models/Graveyard/TombThree.fbx");
    TombThree->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(TombThree, application->defaultShader);
    TombThree->name = "TombThree";
    TombThree->transform.SetPosition(glm::vec3(-31.95, 5.22, 80.58));
    TombThree->transform.SetRotation(glm::vec3(-90.00, -90.00, 0));
    TombThree->transform.SetScale(glm::vec3(0.031));
    TombThree->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* TombFour = new PhysXObject();
    TombFour->LoadModel("Models/Graveyard/TombFour.fbx");
    TombFour->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(TombFour, application->defaultShader);
    TombFour->name = "TombFour";
    TombFour->transform.SetPosition(glm::vec3(-35.03, 6.40, 77.92));
    TombFour->transform.SetRotation(glm::vec3(0, -90.00, 0));
    TombFour->transform.SetScale(glm::vec3(0.02));
    TombFour->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* TombOne2 = new PhysXObject();
    TombOne2->LoadModel(*TombOne);
    GraphicsRender::GetInstance().AddModelAndShader(TombOne2, application->defaultShader);
    TombOne2->name = "TombOne2";
    TombOne2->transform.SetPosition(glm::vec3(-30.90, 4.53, 77.38));
    TombOne2->transform.SetRotation(glm::vec3(0, -90.00, 0));
    TombOne2->transform.SetScale(glm::vec3(0.02, 0.02, 0.02));
    TombOne2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* TombOne3 = new PhysXObject();
    TombOne3->LoadModel(*TombOne);
    GraphicsRender::GetInstance().AddModelAndShader(TombOne3, application->defaultShader);
    TombOne3->name = "TombOne3";
    TombOne3->transform.SetPosition(glm::vec3(-30.90, 4.53, 77.38));
    TombOne3->transform.SetRotation(glm::vec3(0, -90.00, 0));
    TombOne3->transform.SetScale(glm::vec3(0.02, 0.02, 0.02));
    TombOne3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* TombFour2 = new PhysXObject();
    TombFour2->LoadModel(*TombFour);
    GraphicsRender::GetInstance().AddModelAndShader(TombFour2, application->defaultShader);
    TombFour2->name = "TombFour2";
    TombFour2->transform.SetPosition(glm::vec3(-26.55, 4.61, 81.41));
    TombFour2->transform.SetRotation(glm::vec3(0, -90.00, 0));
    TombFour2->transform.SetScale(glm::vec3(0.02));
    TombFour2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* TombTwo2 = new PhysXObject();
    TombTwo2->LoadModel(*TombTwo);
    GraphicsRender::GetInstance().AddModelAndShader(TombTwo2, application->defaultShader);
    TombTwo2->name = "TombTwo2";
    TombTwo2->transform.SetPosition(glm::vec3(-24.94, 3.60, 78.00));
    TombTwo2->transform.SetRotation(glm::vec3(0, -90.00, 0));
    TombTwo2->transform.SetScale(glm::vec3(0.01));
    TombTwo2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* LightPole = new PhysXObject();
    LightPole->LoadModel("Models/Graveyard/LightPole.fbx");
    LightPole->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10,10,0,1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole, application->defaultShader);
    LightPole->name = "LightPole";
    LightPole->transform.SetPosition(glm::vec3(-84.96, 2.94, 94.92));
    LightPole->transform.SetRotation(glm::vec3(0, 90.00, 0));
    LightPole->transform.SetScale(glm::vec3(0.012));
    LightPole->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* LightPole2 = new PhysXObject();
    LightPole2->LoadModel(*LightPole);
    LightPole2->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole2->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole2, application->defaultShader);
    LightPole2->name = "LightPole2";
    LightPole2->transform.SetPosition(glm::vec3(-90.61, 3.76, 81.70));
    LightPole2->transform.SetRotation(glm::vec3(0, 65.00, 0));
    LightPole2->transform.SetScale(glm::vec3(0.012));
    LightPole2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* LightPole3 = new PhysXObject();
    LightPole3->LoadModel(*LightPole);
    LightPole3->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole3->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole3, application->defaultShader);
    LightPole3->name = "LightPole3";
    LightPole3->transform.SetPosition(glm::vec3(-88.30, 6.10, 64.93));
    LightPole3->transform.SetRotation(glm::vec3(0, 44.40, 0));
    LightPole3->transform.SetScale(glm::vec3(0.012));
    LightPole3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    PhysXObject* LightPole4 = new PhysXObject();
    LightPole4->LoadModel(*LightPole);
    LightPole4->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole4->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole4, application->defaultShader);
    LightPole4->name = "LightPole4";
    LightPole4->transform.SetPosition(glm::vec3(-76.07, 6.44, 58.10));
    LightPole4->transform.SetRotation(glm::vec3(0, 13.60, 0));
    LightPole4->transform.SetScale(glm::vec3(0.012));
    LightPole4->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* LightPole5 = new PhysXObject();
    LightPole5->LoadModel(*LightPole);
    LightPole5->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole5->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole5, application->defaultShader);
    LightPole5->name = "LightPole5";
    LightPole5->transform.SetPosition(glm::vec3(-51.82, 7.11, 61.23));
    LightPole5->transform.SetRotation(glm::vec3(0, -144.70, 0));
    LightPole5->transform.SetScale(glm::vec3(0.012));
    LightPole5->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* LightPole6 = new PhysXObject();
    LightPole6->LoadModel(*LightPole);
    LightPole6->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole6->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole6, application->defaultShader);
    LightPole6->name = "LightPole6";
    LightPole6->transform.SetPosition(glm::vec3(-43.02, 4.92, 51.53));
    LightPole6->transform.SetRotation(glm::vec3(0, -14.80, 0));
    LightPole6->transform.SetScale(glm::vec3(0.012));
    LightPole6->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* LightPole7 = new PhysXObject();
    LightPole7->LoadModel(*LightPole);
    LightPole7->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole7->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole7, application->defaultShader);
    LightPole7->name = "LightPole7";
    LightPole7->transform.SetPosition(glm::vec3(-26.97, 3.59, 59.99));
    LightPole7->transform.SetRotation(glm::vec3(0, -76.30, 0));
    LightPole7->transform.SetScale(glm::vec3(0.012));
    LightPole7->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* LightPole8 = new PhysXObject();
    LightPole8->LoadModel(*LightPole);
    LightPole8->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole8->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole8, application->defaultShader);
    LightPole8->name = "LightPole8";
    LightPole8->transform.SetPosition(glm::vec3(-21.21, 2.98, 74.60));
    LightPole8->transform.SetRotation(glm::vec3(0, -70.00, 0));
    LightPole8->transform.SetScale(glm::vec3(0.012));
    LightPole8->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* LightPole9 = new PhysXObject();
    LightPole9->LoadModel(*LightPole);
    LightPole9->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole9->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole9, application->defaultShader);
    LightPole9->name = "LightPole9";
    LightPole9->transform.SetPosition(glm::vec3(-58.94, 7.38, 81.62));
    LightPole9->transform.SetRotation(glm::vec3(0, -152.40, 0));
    LightPole9->transform.SetScale(glm::vec3(0.012));
    LightPole9->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysXObject* LightPole10 = new PhysXObject();
    LightPole10->LoadModel(*LightPole);
    LightPole10->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    LightPole10->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    GraphicsRender::GetInstance().AddModelAndShader(LightPole10, application->defaultShader);
    LightPole10->name = "LightPole10";
    LightPole10->transform.SetPosition(glm::vec3(-70.74, 6.37, 79.11));
    LightPole10->transform.SetRotation(glm::vec3(0, -183.90, 0));
    LightPole10->transform.SetScale(glm::vec3(0.012));
    LightPole10->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

    PhysicsMaterial coffinPhy;
    coffinPhy.staticFriction = 100;
    coffinPhy.dynamicFriction = 100;

    PhysXObject* Coffin = new PhysXObject();
    Coffin->LoadModel("Models/Graveyard/Coffin.fbx");
    Coffin->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    Coffin->occulsionState = eOcculsionState::DYNAMIC;
    GraphicsRender::GetInstance().AddModelAndShader(Coffin, application->defaultShader);
    Coffin->name = "Coffin";
    Coffin->transform.SetPosition(glm::vec3(-55.12, 7.76, 64.84));
    Coffin->transform.SetRotation(glm::vec3(0, -54.99, 0));
    Coffin->transform.SetScale(glm::vec3(0.012));
    Coffin->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Coffin2 = new PhysXObject();
    Coffin2->LoadModel(*Coffin);
    Coffin2->occulsionState = eOcculsionState::DYNAMIC;
    GraphicsRender::GetInstance().AddModelAndShader(Coffin2, application->defaultShader);
    Coffin2->name = "Coffin2";
    Coffin2->transform.SetPosition(glm::vec3(-48.47, 6.68, 68.96));
    Coffin2->transform.SetRotation(glm::vec3(0, -90.00, 0));
    Coffin2->transform.SetScale(glm::vec3(0.012));
    Coffin2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Coffin3 = new PhysXObject();
    Coffin3->LoadModel(*Coffin);
    Coffin3->occulsionState = eOcculsionState::DYNAMIC;
    GraphicsRender::GetInstance().AddModelAndShader(Coffin3, application->defaultShader);
    Coffin3->name = "Coffin3";
    Coffin3->transform.SetPosition(glm::vec3(-54.40, 7.76, 65.86));
    Coffin3->transform.SetRotation(glm::vec3(0, -54.99, 0));
    Coffin3->transform.SetScale(glm::vec3(0.012));
    Coffin3->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Coffin4 = new PhysXObject();
    Coffin4->LoadModel(*Coffin);
    Coffin4->occulsionState = eOcculsionState::DYNAMIC;
    GraphicsRender::GetInstance().AddModelAndShader(Coffin4, application->defaultShader);
    Coffin4->name = "Coffin4";
    Coffin4->transform.SetPosition(glm::vec3(-53.67, 7.76, 66.90));
    Coffin4->transform.SetRotation(glm::vec3(0, -54.99, 0));
    Coffin4->transform.SetScale(glm::vec3(0.012));
    Coffin4->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);
    Coffin4->collider->AsBoxCollider()->SetPhysicsMaterial(coffinPhy);

    PhysXObject* Coffin5 = new PhysXObject();
    Coffin5->LoadModel(*Coffin);
    Coffin5->occulsionState = eOcculsionState::DYNAMIC;
    GraphicsRender::GetInstance().AddModelAndShader(Coffin5, application->defaultShader);
    Coffin5->name = "Coffin5";
    Coffin5->transform.SetPosition(glm::vec3(-52.99, 7.76, 67.88));
    Coffin5->transform.SetRotation(glm::vec3(0, -54.99, 0));
    Coffin5->transform.SetScale(glm::vec3(0.012));
    Coffin5->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);   
    Coffin5->collider->AsBoxCollider()->SetPhysicsMaterial(coffinPhy);



    PhysXObject* Gibbet = new PhysXObject();
    Gibbet->LoadModel("Models/Graveyard/Gibbet.fbx");
    Gibbet->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(Gibbet, application->defaultShader);
    Gibbet->name = "Gibbet";
    Gibbet->transform.SetPosition(glm::vec3(-66.52, 9.56, 53.89));
    Gibbet->transform.SetRotation(glm::vec3(0, -31.60, 0));
    Gibbet->transform.SetScale(glm::vec3(0.01));
    Gibbet->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Gibbet2 = new PhysXObject();
    Gibbet2->LoadModel(*Gibbet);
    Gibbet2->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(Gibbet2, application->defaultShader);
    Gibbet2->name = "Gibbet2";
    Gibbet2->transform.SetPosition(glm::vec3(-17.72, 4.60, 80.56));
    Gibbet2->transform.SetRotation(glm::vec3(0, 6.10, 0));
    Gibbet2->transform.SetScale(glm::vec3(0.01));
    Gibbet2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Guillotine = new PhysXObject();
    Guillotine->LoadModel("Models/Graveyard/Guillotine.fbx");
    Guillotine->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    GraphicsRender::GetInstance().AddModelAndShader(Guillotine, application->defaultShader);
    Guillotine->name = "Guillotine";
    Guillotine->transform.SetPosition(glm::vec3(-42.45, 6.61, 73.41));
    Guillotine->transform.SetRotation(glm::vec3(0, -130.90, 0));
    Guillotine->transform.SetScale(glm::vec3(0.012));
    Guillotine->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Brazier = new PhysXObject();
    Brazier->LoadModel("Models/Graveyard/Brazier.fbx");
    Brazier->meshes[0]->meshMaterial->material()->diffuseTexture = body;
    GraphicsRender::GetInstance().AddModelAndShader(Brazier, application->defaultShader);
    Brazier->name = "Brazier";
    Brazier->transform.SetPosition(glm::vec3(-76.42, 3.16, 86.84));
    Brazier->transform.SetRotation(glm::vec3(0, -90.00, 0));
    Brazier->transform.SetScale(glm::vec3(0.013));
    Brazier->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Brazier2 = new PhysXObject();
    Brazier2->LoadModel(*Brazier);
    Brazier2->meshes[0]->meshMaterial->material()->diffuseTexture = body;
    GraphicsRender::GetInstance().AddModelAndShader(Brazier2, application->defaultShader);
    Brazier2->name = "Brazier1";
    Brazier2->transform.SetPosition(glm::vec3(-76.42, 5.88, 76.65));
    Brazier2->transform.SetRotation(glm::vec3(0, -90.00, 0));
    Brazier2->transform.SetScale(glm::vec3(0.013));
    Brazier2->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Brazier3 = new PhysXObject();
    Brazier3->LoadModel(*Brazier);
    Brazier3->meshes[0]->meshMaterial->material()->diffuseTexture = body;
    GraphicsRender::GetInstance().AddModelAndShader(Brazier3, application->defaultShader);
    Brazier3->name = "Brazier3";
    Brazier3->transform.SetPosition(glm::vec3(-53.16, 7.31, 78.43));
    Brazier3->transform.SetRotation(glm::vec3(0, 0, 0));
    Brazier3->transform.SetScale(glm::vec3(0.013));
    Brazier3->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Brazier4 = new PhysXObject();
    Brazier4->LoadModel(*Brazier);
    Brazier4->meshes[0]->meshMaterial->material()->diffuseTexture = body;
    GraphicsRender::GetInstance().AddModelAndShader(Brazier4, application->defaultShader);
    Brazier4->name = "Brazier4";
    Brazier4->transform.SetPosition(glm::vec3(-23.66, 2.75, 67.31));
    Brazier4->transform.SetRotation(glm::vec3(0, 0, 0));
    Brazier4->transform.SetScale(glm::vec3(0.013));
    Brazier4->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

    PhysXObject* Brazier5 = new PhysXObject();
    Brazier5->LoadModel(*Brazier);
    Brazier5->meshes[0]->meshMaterial->material()->diffuseTexture = body;
    GraphicsRender::GetInstance().AddModelAndShader(Brazier5, application->defaultShader);
    Brazier5->name = "Brazier5";
    Brazier5->transform.SetPosition(glm::vec3(-37.87, 4.33, 54.30));
    Brazier5->transform.SetRotation(glm::vec3(0, 0, 0));
    Brazier5->transform.SetScale(glm::vec3(0.013));
    Brazier5->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);



    GrassMesh* grassMeshInstance = new GrassMesh();
    grassMeshInstance->AddTransformData(glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(0.015f));
    grassMeshInstance->name = "InstanceGrass";
    grassMeshInstance->meshes[0]->meshMaterial->material()->specular = 0;
    grassMeshInstance->AddTransformData(glm::vec3(-71.29, 3.12, 100.90), glm::vec3(0, 25, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-71.76, 3.12, 100.26), glm::vec3(0, 60, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-71.76, 3.12, 101.13), glm::vec3(0, 15, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-71.76, 2.8, 98.50), glm::vec3(0, 25, 0),   glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-72.10, 2.8, 98.02), glm::vec3(0, 60, 0),   glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-71.64, 2.8, 97.69), glm::vec3(0, 15, 0),   glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-83.72, 2.93, 96.51), glm::vec3(0, 25, 0),  glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-83.72, 2.93, 95.83), glm::vec3(0, 60, 0),  glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-85.07, 3.21, 90.20), glm::vec3(0, 15, 0),  glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-85.22, 3.12, 89.68), glm::vec3(0, 15, 0),  glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-84.94, 3.12, 89.91), glm::vec3(0, 15, 0),  glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-77.85, 3.21, 85.94), glm::vec3(0, 15, 0),  glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-77.32, 3.21, 86.02), glm::vec3(0, 15, 0),  glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-77.79, 3.21, 86.40), glm::vec3(0, 15, 0),  glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-83.76, 2.65, 102.05), glm::vec3(0, 15, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-83.76, 2.65, 101.58), glm::vec3(0, 15, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-83.25, 2.65, 101.94), glm::vec3(0, 15, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-80.88, 2.91, 103.54), glm::vec3(0, 15, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-81.37, 2.91, 102.80), glm::vec3(0, -36.60, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-85.75, 3.71, 85.64), glm::vec3(0, -36.60, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-86.03, 3.71, 85.37), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-91.04, 3.54, 82.60), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-90.36, 3.54, 81.96), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-77.46, 5.60, 76.60), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-87.71, 5.67, 65.60), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-88.87, 5.67, 65.60), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-75.98, 6.09, 58.92), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-76.95, 6.09, 58.21), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-70.94, 6.09, 78.42), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-70.94, 6.09, 78.42), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-59.58, 7.27, 80.89), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-50.61, 7.27, 74.06), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-54.20, 7.27, 78.88), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-54.20, 7.27, 81.72), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-54.20, 7.27, 82.43), glm::vec3(0, -68.60, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-54.15, 7.27, 83.13), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-48.02, 7.02, 67.09), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-46.08, 7.02, 69.30), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-45.13, 7.02, 69.50), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-45.82, 6.65, 65.65), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-43.39, 4.65, 52.26), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-37.61, 4.14, 55.83), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-33.93, 3.87, 58.40), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-28.29, 3.57, 59.90), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-27.24, 3.48, 60.75), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-25.53, 2.95, 70.72), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-24.55, 2.95, 73.00), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-21.62, 2.83, 73.85), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-17.67, 2.62, 78.85), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-17.67, 2.62, 79.83), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-29.84, 4.45, 79.06), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-29.84, 3.80, 76.79), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-26.58, 3.40, 76.79), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-34.69, 5.13, 76.86), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-36.32, 6.64, 81.29), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-22.33, 3.46, 83.29), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-26.36, 4.40, 83.29), glm::vec3(0, 0, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-39.47, 4.20, 62.33), glm::vec3(0, -49.80, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-41.47, 4.20, 61.57), glm::vec3(0, -49.80, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-64.55, 6.73, 85.96), glm::vec3(0, -49.80, 0), glm::vec3(0.012));
    grassMeshInstance->AddTransformData(glm::vec3(-64.30, 6.64, 86.42), glm::vec3(0, -49.80, 0), glm::vec3(0.012));
        
    GraphicsRender::GetInstance().AddModelAndShader(grassMeshInstance, application->grassInstanceShader);

   /* Model* dummy = new Model();
    dummy->LoadModel("Models/Graveyard/Fences/Grass.fbx");
    dummy->name = "dummy";
    dummy->transform.SetPosition(glm::vec3(-71.76, 3.12, 101.13));
    dummy->transform.SetRotation(glm::vec3(0));
    dummy->transform.SetScale(glm::vec3(0.015));
    GraphicsRender::GetInstance().AddModelAndShader(dummy, application->defaultShader);*/

    PhysXObject* Scythe = new PhysXObject();
    Scythe->LoadModel("Models/Graveyard/Scythe.fbx");
    Scythe->meshes[0]->meshMaterial->material()->diffuseTexture = body;
    Scythe->occulsionState = eOcculsionState::DYNAMIC;
    GraphicsRender::GetInstance().AddModelAndShader(Scythe, application->defaultShader);
    Scythe->name = "Scythe";
    Scythe->transform.SetPosition(glm::vec3(-49.43, 8.41, 74.47));
    Scythe->transform.SetRotation(glm::vec3(0, -202.40, -15.50));
    Scythe->transform.SetScale(glm::vec3(0.013));
    Scythe->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);
    PhysicsMaterial scythePhyMat;
    scythePhyMat.staticFriction = 10;
    scythePhyMat.dynamicFriction = 10;
    Scythe->collider->AsBoxCollider()->SetPhysicsMaterial(scythePhyMat);


    MeshInstance* PumpkinInstance = new MeshInstance();
    PumpkinInstance->LoadModel("Models/Graveyard/Pumpkin.fbx");
    PumpkinInstance->name = "PumpkinInstance";
    PumpkinInstance->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    PumpkinInstance->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));

    PumpkinInstance->AddTransformData(glm::vec3(-72.67, 2.77, 95.57), glm::vec3(0, -75, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-72.57, 2.77, 96.73), glm::vec3(0, -50, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-73.04, 2.77, 96.17), glm::vec3(0, -31.50, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-74.97, 3.21, 87.43), glm::vec3(0, -27.40, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-74.30, 3.21, 87.77), glm::vec3(0, -51.90, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-77.84, 6.13, 80.32), glm::vec3(0, 0, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-69.89, 7.23, 56.58), glm::vec3(0, -40.50, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-69.25, 7.23, 57.13), glm::vec3(0, -68.40, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-60.52, 7.28, 81.15), glm::vec3(0, -115.70, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-85.70, 6.32, 63.22), glm::vec3(0, 0, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-85.70, 6.32, 63.22), glm::vec3(0, 0, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-88.99, 11.04, 57.34), glm::vec3(0, 0, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-35.02, 7.08, 78.02), glm::vec3(0, -161.80, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-35.02, 7.08, 78.02), glm::vec3(0, -161.80, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-20.86, 2.83, 81.10), glm::vec3(0, -161.80, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-30.37, 3.63, 59.23), glm::vec3(0, -52.40, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-52.50, 7.00, 61.03), glm::vec3(0, -95.60, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-43.91, 4.83, 52.10), glm::vec3(0, -45.40, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-45.31, 14.43, 69.47), glm::vec3(0, -93.60, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-92.47, 4.79, 74.34), glm::vec3(0, 42.20, 0), glm::vec3(0.015));
    PumpkinInstance->AddTransformData(glm::vec3(-91.36, 4.58, 74.34), glm::vec3(0, 19.00, 0), glm::vec3(0.015));
    GraphicsRender::GetInstance().AddModelAndShader(PumpkinInstance, application->defaultInstanceShader);


   /* Model* dummy = new Model();
    dummy->LoadModel("Models/Graveyard/Pumpkin.fbx");
    dummy->name = "dummy";
    dummy->transform.SetPosition(glm::vec3(-98.32, 1.77, 101.94));
    dummy->transform.SetRotation(glm::vec3(0));
    dummy->transform.SetScale(glm::vec3(0.015));
    GraphicsRender::GetInstance().AddModelAndShader(dummy, application->defaultShader);*/

    PhysXObject* Angel = new PhysXObject();
    Angel->LoadModel("Models/Graveyard/Angle.fbx");
    Angel->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexStatue;
    GraphicsRender::GetInstance().AddModelAndShader(Angel, application->defaultShader);
    Angel->name = "Angel";
    Angel->transform.SetPosition(glm::vec3(-82.64, 4.90, 103.80));
    Angel->transform.SetRotation(glm::vec3(0, 30.00,0));
    Angel->transform.SetScale(glm::vec3(0.009));
    Angel->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);
    PhysicsMaterial AngelPhyMat;
    AngelPhyMat.staticFriction = 100;
    AngelPhyMat.dynamicFriction = 100;
    Angel->collider->AsBoxCollider()->SetPhysicsMaterial(AngelPhyMat);

    Fire* fire = new Fire(0.1f, { -76.43, 3.60, 86.83 });
    Fire* fire2 = new Fire(0.1f, { -76.40, 6.25, 76.60 });
    Fire* fire3 = new Fire(0.1f, { -53.18, 7.70, 78.43 });
    Fire* fire4 = new Fire(0.1f, { -37.88, 4.70, 54.33 });
    Fire* fire5 = new Fire(0.1f, { -23.68, 3.10, 67.33 });


    FireFly* fireFly = new FireFly(1.20, glm::vec3(-66.40, 9.80, 53.30));
    FireFly* fireFly2 = new FireFly(1.20, glm::vec3(-49.20, 7.40, 68.70));
    FireFly* fireFly3 = new FireFly(1.20, glm::vec3(-66.70, 7.50, 64.90));


    Model* FoilageStone = new Model();
    FoilageStone->LoadModel("Models/Graveyard/FoilageStones.fbx");
    FoilageStone->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    FoilageStone->name = "FoilageStone";
    FoilageStone->transform.SetPosition(glm::vec3(-85.97, 3.90, 77.38));
    FoilageStone->transform.SetRotation(glm::vec3(-3.40, 154.20, 3.70));
    FoilageStone->transform.SetScale(glm::vec3(0.03, 0.01, 0.01));
    GraphicsRender::GetInstance().AddModelAndShader(FoilageStone, application->defaultShader);

    Model* FoilageStone2 = new Model();
    FoilageStone2->LoadModel(*FoilageStone);
    FoilageStone2->name = "FoilageStone2";
    FoilageStone2->transform.SetPosition(glm::vec3(-75.09, 2.92, 101.73));
    FoilageStone2->transform.SetRotation(glm::vec3(0));
    FoilageStone2->transform.SetScale(glm::vec3(0.03, 0.007, 0.007));
    GraphicsRender::GetInstance().AddModelAndShader(FoilageStone2, application->defaultShader);

    Model* FoilageStone3 = new Model();
    FoilageStone3->LoadModel(*FoilageStone);
    FoilageStone3->name = "FoilageStone3";
    FoilageStone3->transform.SetPosition(glm::vec3(-56.35, 7.13, 75.21));
    FoilageStone3->transform.SetRotation(glm::vec3(0, 70.30,0));
    FoilageStone3->transform.SetScale(glm::vec3(0.03, 0.007, 0.007));
    GraphicsRender::GetInstance().AddModelAndShader(FoilageStone3, application->defaultShader);

    Model* FoilageStone4 = new Model();
    FoilageStone4->LoadModel(*FoilageStone);
    FoilageStone4->name = "FoilageStone4";
    FoilageStone4->transform.SetPosition(glm::vec3(-50.30, 5.58, 57.22));
    FoilageStone4->transform.SetRotation(glm::vec3(-19.60, -106.20, 0));
    FoilageStone4->transform.SetScale(glm::vec3(0.03, 0.007, 0.007));
    GraphicsRender::GetInstance().AddModelAndShader(FoilageStone4, application->defaultShader);

    Model* FoilageStone5 = new Model();
    FoilageStone5->LoadModel(*FoilageStone);
    FoilageStone5->name = "FoilageStone5";
    FoilageStone5->transform.SetPosition(glm::vec3(-26.52, 2.97, 72.97));
    FoilageStone5->transform.SetRotation(glm::vec3(0, 14.90, -6.50));
    FoilageStone5->transform.SetScale(glm::vec3(0.03, 0.007, 0.007));
    GraphicsRender::GetInstance().AddModelAndShader(FoilageStone5, application->defaultShader);
    

    CubeVolume* cubeVolume = new CubeVolume();
    cubeVolume->transform.SetPosition(glm::vec3(-48.05, 8.22, 79.81));
    cubeVolume->transform.SetRotation(glm::vec3(0, -32.40, 0));
    cubeVolume->transform.SetScale(glm::vec3(2.00));
    cubeVolume->Intialize(application->gameScenecamera);
    cubeVolume->AddCubeEffects(eEffectType::NIGHTVISION);
    cubeVolume->isVisible = false;

    PhysXObject* PumpkinPhy = new PhysXObject();
    PumpkinPhy->LoadModel("Models/Graveyard/Pumpkin.fbx");
    PumpkinPhy->meshes[0]->meshMaterial->material()->diffuseTexture = diffuseTexture;
    PumpkinPhy->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
    PumpkinPhy->occulsionState = eOcculsionState::DYNAMIC;
    GraphicsRender::GetInstance().AddModelAndShader(PumpkinPhy, application->defaultShader);
    PumpkinPhy->name = "Pumpkin";
    PumpkinPhy->transform.SetPosition(glm::vec3(-52.29, 9.20, 73.25));
    PumpkinPhy->transform.SetRotation(glm::vec3(0, -202.40, -15.50));
    PumpkinPhy->transform.SetScale(glm::vec3(0.013));
    PumpkinPhy->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::SPHERE);
    PhysicsMaterial pumpkinMat;
    pumpkinMat.staticFriction = 10;
    pumpkinMat.dynamicFriction = 10;
    PumpkinPhy->collider->AsBoxCollider()->SetPhysicsMaterial(pumpkinMat);

    Enemy* enemyOne = new Enemy(player);

    enemyOne->name = "Enemy 1";
    enemyOne->transform.SetPosition(glm::vec3(-34.87, 4.07, 58.27));
    enemyOne->AddRoamingPoints(-34.87, 4.07, 58.27);
    enemyOne->AddRoamingPoints(-29.51, 4.07, 78.80);


    Model* moon = new Model();
   moon->LoadModel("Models/DefaultSphere/DefaultSphere.fbx");
   moon->name = "Moon";
   moon->transform.SetPosition(glm::vec3(10.11, 93.11, -116.19));
   moon->transform.SetRotation(glm::vec3(0, 14.90, -6.50));
   moon->transform.SetScale(glm::vec3(10));
   moon->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(100, 100, 100, 1));
   GraphicsRender::GetInstance().AddModelAndShader(moon, application->defaultShader);



#pragma region Flag


   std::string textureFile = "Models/Plane/Flag1.png";
   Texture* diffuse = new Texture(textureFile);

   std::string textureFile2 = "Models/Plane/Flag.png";
   Texture* diffuse2 = new Texture(textureFile2);

   std::string alphaText = "Models/Plane/BW1.png";
   Texture* modelAlpha = new Texture(alphaText);

   SoftBodyObjs* FlagCloth = new SoftBodyObjs();
   FlagCloth->LoadModel("Models/Plane/Flag.ply");
   FlagCloth->name = "MY PLANE";
   FlagCloth->meshes[0]->meshMaterial->material()->diffuseTexture = diffuse2;
   FlagCloth->meshes[0]->meshMaterial->material()->specular = 0;
   //softBodyTest1->meshes[0]->meshMaterial->material()->alphaTexture = modelAlpha;
   FlagCloth->meshes[0]->meshMaterial->material()->useMaskTexture = true;
   FlagCloth->transform.SetPosition(glm::vec3(-64.39, 9.85, 86.32));
   FlagCloth->transform.SetRotation(glm::vec3(0, 30.60, 180.00));
   FlagCloth->transform.SetScale(glm::vec3(6.00, 4.00, 3.00));
   GraphicsRender::GetInstance().AddModelAndShader(FlagCloth, application->defaultShader);
   FlagCloth->InitializeSoftBody();
   FlagCloth->AddLockSphere(2400, 0.1);
   FlagCloth->AddLockSphere(0, 0.01f);
   FlagCloth->acceleration = { .2, -0.3, 1 };

   Model* flagPole = new Model("Models/Plane/Pole.fbx");
   flagPole->name = "Pole";
   flagPole->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(1, .75, 0, 1));
   flagPole->meshes[1]->meshMaterial->material()->SetBaseColor(glm::vec4(1, .75, 0, 1));
   flagPole->meshes[2]->meshMaterial->material()->SetBaseColor(glm::vec4(1, .75, 0, 1));
   flagPole->meshes[3]->meshMaterial->material()->SetBaseColor(glm::vec4(1, .75, 0, 1));
   flagPole->meshes[4]->meshMaterial->material()->SetBaseColor(glm::vec4(1, .75, 0, 1));
   flagPole->meshes[5]->meshMaterial->material()->SetBaseColor(glm::vec4(1, .75, 0, 1));
   flagPole->meshes[6]->meshMaterial->material()->SetBaseColor(glm::vec4(1, .75, 0, 1));
   flagPole->transform.SetPosition(glm::vec3(-64.41, 6.69, 86.30));
   flagPole->transform.SetScale(glm::vec3(0.21));

   GraphicsRender::GetInstance().AddModelAndShader(flagPole, application->defaultShader);


#pragma endregion

  

   PhysXObject* Sword = new PhysXObject();
   Sword->LoadModel("Models/Sword/Sword.obj");  
   GraphicsRender::GetInstance().AddModelAndShader(Sword, application->defaultShader);
   Sword->name = "Sword";
   Sword->transform.SetPosition(glm::vec3(-66.65, 7.53, 64.83));
   Sword->transform.SetRotation(glm::vec3(-63.90, 69.70, 111.30));
   Sword->transform.SetScale(glm::vec3(0.13));
   Sword->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

   std::string baseColorPath = "Models/GOW/chaos_sword.png";
   Texture* bladesDiffuse = new Texture(baseColorPath);


   PhysXObject* Blades = new PhysXObject();
   Blades->LoadModel("Models/GOW/Blades.fbx");
   Blades->meshes[0]->meshMaterial->material()->diffuseTexture = bladesDiffuse;
   Blades->occulsionState = eOcculsionState::DYNAMIC;
   GraphicsRender::GetInstance().AddModelAndShader(Blades, application->defaultShader);
   Blades->name = "Blades";
   Blades->transform.SetPosition(glm::vec3(-60.08, 9.53, 68.82));
   Blades->transform.SetRotation(glm::vec3(0, 0, 90.00));
   Blades->transform.SetScale(glm::vec3(2.30));
   Blades->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);

   PhysXObject* Blades2 = new PhysXObject();
   Blades2->LoadModel(*Blades);
   Blades2->occulsionState = eOcculsionState::DYNAMIC;

   GraphicsRender::GetInstance().AddModelAndShader(Blades2, application->defaultShader);
   Blades2->name = "Blades2";
   Blades2->transform.SetPosition(glm::vec3(-60.61, 9.53, 70.88));
   Blades2->transform.SetRotation(glm::vec3(180.00, 0, 90.00));
   Blades2->transform.SetScale(glm::vec3(2.30));
   Blades2->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);

   std::string baseColorPath_ = "Models/Borne/02___Default_Base_Color.png";
   Texture* BorneDiffuse = new Texture(baseColorPath_);

   PhysXObject* Borne = new PhysXObject();
   Borne->LoadModel("Models/Borne/Borne.fbx");
   Borne->meshes[0]->meshMaterial->material()->diffuseTexture = BorneDiffuse;
   Borne->occulsionState = eOcculsionState::DYNAMIC;

   GraphicsRender::GetInstance().AddModelAndShader(Borne, application->defaultShader);
   Borne->name = "Borne";
   Borne->transform.SetPosition(glm::vec3(-59.09, 9.53, 73.16));
   Borne->transform.SetRotation(glm::vec3(0, 90.00, 0));
   Borne->transform.SetScale(glm::vec3(0.01));
   Borne->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);

   std::string mimicPath = "Models/Mimic/Mimic_4K_BaseColor.png";
   Texture* mimicdiffuse = new Texture(mimicPath);

   PhysXObject* Mimic = new PhysXObject();
   Mimic->LoadModel("Models/Mimic/Mimic.fbx");
   Mimic->meshes[0]->meshMaterial->material()->diffuseTexture = mimicdiffuse;
   Mimic->occulsionState = eOcculsionState::DYNAMIC;
   GraphicsRender::GetInstance().AddModelAndShader(Mimic, application->defaultShader);
   Mimic->name = "Mimic";
   Mimic->transform.SetPosition(glm::vec3(-45.76, 7.15, 78.76));
   Mimic->transform.SetRotation(glm::vec3(-90.00, -36.60, 0));
   Mimic->transform.SetScale(glm::vec3(2.00));
   Mimic->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

   
   std::string statuePath = "Models/Statue/gaurdianColor.png";
   Texture* statueDiffuse = new Texture(statuePath);

   PhysXObject* Statue = new PhysXObject();
   Statue->LoadModel("Models/Statue/Statue.fbx");
   Statue->meshes[0]->meshMaterial->material()->diffuseTexture = statueDiffuse;

   GraphicsRender::GetInstance().AddModelAndShader(Statue, application->defaultShader);
   Statue->name = "Statue";
   Statue->transform.SetPosition(glm::vec3(-44.70, 7.33, 82.35));
   Statue->transform.SetRotation(glm::vec3(0, -126.00, 0));
   Statue->transform.SetScale(glm::vec3(0.01));
   Statue->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

   Model* Death = new Model();
   Death->LoadModel("Models/Death/Death.fbx");
   Death->name = "Death";
   Death->transform.SetPosition(glm::vec3(-50.19, 11.77, 78.40));
   Death->transform.SetRotation(glm::vec3(-90.00, -125.60, 0.00));
   Death->transform.SetScale(glm::vec3(0.08));
   Death->meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(10, 10, 0, 1));
   GraphicsRender::GetInstance().AddModelAndShader(Death, application->defaultShader);

   PhysXObject* wallFinal = new PhysXObject();
   wallFinal->LoadModel("Models/DefaultCube/DefaultCube.fbx");
   GraphicsRender::GetInstance().AddModelAndShader(wallFinal, application->defaultShader);
   wallFinal->isVisible = false;
   wallFinal->name = "wallFinal";
   wallFinal->transform.SetPosition(glm::vec3(-75.83, 3.84, 106.88));
   wallFinal->transform.SetRotation(glm::vec3(0, 8.40, 0));
   wallFinal->transform.SetScale(glm::vec3(1.80, 1.60, 0.30));
   wallFinal->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);
  


   
    OcculsionManager::GetInstance().InitializeOcculusion();
}

//TreeThree

void SceneFive::Update()
{
    sbThread->bRun = application->isPlayMode ? true : false;

    if (application->isPlayMode)
    {
        if (isPlaying)
        {
            audio->PlayBGAudio();
            isPlaying = false;
        }

    }
   

}

void SceneFive::Render()
{
}
