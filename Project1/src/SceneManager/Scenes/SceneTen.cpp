#include "SceneTen.h"

#include "../../ApplicationRenderer.h"


SceneTen::SceneTen(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneTen::Start()
{

   
    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(3, 3, 5));
   

    Model* window2 = new Model("Models/Backpack/Backpack.obj");
    window2->name = "Backpack";
    Texture* diffuse = new Texture("Models/Backpack/1001_albedo.jpg");
    Texture* specular = new Texture("Models/Backpack/1001_roughness.jpg");
    window2->meshes[0]->meshMaterial =  new MaterialGBuffer();

    window2->meshes[0]->meshMaterial->gBufferMat()->diffuseTexture = diffuse;
    window2->meshes[0]->meshMaterial->gBufferMat()->specularTexture = specular;
   

   GraphicsRender::GetInstance().AddModelAndShader(window2, application->gBufferShader);

}

void SceneTen::Update()
{
}

void SceneTen::Render()
{
}
