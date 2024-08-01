#include "SceneFour.h"
#include "../../ApplicationRenderer.h"
#include "../../Grass/GrassMesh.h"
#include "../../ParticleSystem/ParticleAssets/FireFly.h"
SceneFour::SceneFour(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneFour::Start()
{
    std::string diffuseTexturePath = "Models/Graveyard/Fences/atlas-universal-albedo-a.png";
    Texture* diffuseTexture = new Texture(diffuseTexturePath);

    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));

    std::string diffuseTerPath4x = "Models/Terrain/2k_diffuse_4x_.png";
    Texture* diffTerrain4x = new Texture(diffuseTerPath4x);

    PhysXObject* terrain = new PhysXObject();
    terrain->occulsionState = eOcculsionState::NO_OCCULSION;
    terrain->LoadModel("Models/Terrain/Terrain2.fbx");
    terrain->meshes[0]->meshMaterial->material()->diffuseTexture = diffTerrain4x;
    GraphicsRender::GetInstance().AddModelAndShader(terrain, application->defaultShader);
    terrain->name = "Terrain";
    terrain->transform.SetPosition(glm::vec3(0, -2, 0));
    terrain->transform.SetRotation(glm::vec3(0, 0, 0));
    terrain->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);


    PlayerController* player = new PlayerController(application);
    player->transform.SetPosition(glm::vec3(-75.64, 3.27, 105.30));

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


    Model* Plane = new Model();
    Plane->LoadModel("Models/DefaultQuad/DefaultQuad.fbx");
    Plane->transform.SetRotation(glm::vec3(90, 0, 0));
    Plane->transform.SetScale(glm::vec3(10));
    GraphicsRender::GetInstance().AddModelAndShader(Plane, application->defaultShader);

    Model* Plane2 = new Model();
    Plane2->LoadModel("Models/DefaultQuad/DefaultQuad.fbx");
    Plane->transform.SetPosition(glm::vec3(0, 10, 0));
    Plane2->transform.SetRotation(glm::vec3(90, 0, 0));
    Plane2->transform.SetScale(glm::vec3(10));
    GraphicsRender::GetInstance().AddModelAndShader(Plane2, application->defaultShader);

   FireFly* fireFly = new FireFly(0.2, { 0, 0 ,0 });
   Fire* fire = new Fire(0.2, { 0, 0 ,0 });
}

void SceneFour::Update()
{
}

void SceneFour::Render()
{
}
