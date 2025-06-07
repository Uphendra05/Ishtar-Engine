#include "SceneTen.h"

#include "../../RenderingPipeline/BaseRenderingPipeline.h"


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
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));


   /* Light* deferredLight = new Light();
    deferredLight->SetLightType(LightType::POINT_LIGHT);
    deferredLight->InitializeDeferredLights();
    deferredLight->SetAttenuation(0.09f, 0.02f, 0.02f);
    deferredLight->transform.position = glm::vec3(0, 0, -9);*/

    Light* deferredLight2 = new Light();
    deferredLight2->SetLightType(LightType::SPOT_LIGHT);
    deferredLight2->InitializeDeferredLights();
    deferredLight2->SetAttenuation(0.09f, 0.02f, 0.02f);
    deferredLight2->transform.position = glm::vec3(0, 0, -1);



    Model* window3 = new Model("Models/Backpack/Backpack.obj");
    window3->name = "Backpack";
    Texture* diffuse2 = new Texture("Models/Backpack/1001_albedo.jpg");
    Texture* specular2 = new Texture("Models/Backpack/1001_roughness.jpg");
    window3->meshes[0]->meshMaterial->material()->diffuseTexture = diffuse2;
    window3->meshes[0]->meshMaterial->material()->specularTexture = specular2;
    GraphicsRender::GetInstance().AddModelAndShader(window3, application->defaultShader);
   

    Model* Car = new Model("Models/Car/Car.obj");
    Car->name = "Car";
    Texture* diffuse = new Texture("Models/Car/WhiplashColor.png");
    Texture* specular = new Texture("Models/Car/WhiplashRoughness.png");
    Car->meshes[0]->meshMaterial =  new MaterialGBuffer();

    Car->meshes[0]->meshMaterial->gBufferMat()->diffuseTexture = diffuse;
    Car->meshes[0]->meshMaterial->gBufferMat()->specularTexture = specular;
    Car->transform.position = glm::vec3(0, 0, -10);
    GraphicsRender::GetInstance().AddGbufferModels(Car, application->gBufferShader);


 

    for (size_t i = 0; i < 50; i++)
    {
        Model* Car2 = new Model(*Car);
        Car2->name = "Car " + i;
        Texture* diffuse2 = new Texture(*diffuse);
        Texture* specular2 = new Texture(*specular);
        Car2->meshes[0]->meshMaterial = new MaterialGBuffer();

        Car2->meshes[0]->meshMaterial->gBufferMat()->diffuseTexture = diffuse2;
        Car2->meshes[0]->meshMaterial->gBufferMat()->specularTexture = specular2;
        Car2->transform.position = glm::vec3(0, 0, -10);
        GraphicsRender::GetInstance().AddGbufferModels(Car2, application->gBufferShader);
    }

   

}

void SceneTen::Update()
{
}

void SceneTen::Render()
{
}
