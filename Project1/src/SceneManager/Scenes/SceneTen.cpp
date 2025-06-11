#include "SceneTen.h"

#include "../../RenderingPipeline/BaseRenderingPipeline.h"


SceneTen::SceneTen(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneTen::Start()
{

 
    

        Light* deferredLight2 = new Light();
        deferredLight2->SetLightType(LightType::POINT_LIGHT);
        deferredLight2->InitializeDeferredLights();
        deferredLight2->SetColor(glm::vec4(1,0,0,1));
        deferredLight2->SetAttenuation(0.09f, 0.02f, 0.02f);
        deferredLight2->transform.position = glm::vec3(0, 10, 10);

    

   


 

    Model* Car = new Model("Models/Car/Car.obj");
    Car->name = "Car";
    Texture* diffuse = new Texture("Models/Car/WhiplashColor.png");
    Texture* specular = new Texture("Models/Car/WhiplashRoughness.png");
    Car->meshes[0]->meshMaterial =  new MaterialGBuffer();

    Car->meshes[0]->meshMaterial->gBufferMat()->diffuseTexture = diffuse;
    Car->meshes[0]->meshMaterial->gBufferMat()->specularTexture = specular;
    Car->transform.position = glm::vec3(0, 0, -10);
    GraphicsRender::GetInstance().AddGbufferModels(Car, application->gBufferShader);

   

        Model* Car2 = new Model(*Car);
        Car2->name = "Car " ;
        Texture* diffuse2 = new Texture(*diffuse);
        Texture* specular2 = new Texture(*specular);
        Car2->meshes[0]->meshMaterial = new MaterialGBuffer();

        Car2->meshes[0]->meshMaterial->gBufferMat()->diffuseTexture = diffuse2;
        Car2->meshes[0]->meshMaterial->gBufferMat()->specularTexture = specular2;
        Car2->transform.position = glm::vec3(0, 0, 10 );
        GraphicsRender::GetInstance().AddGbufferModels(Car2, application->gBufferShader);
  

   

}

void SceneTen::Update()
{
}

void SceneTen::Render()
{
}
