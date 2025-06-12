#include "SceneTen.h"

#include "../../RenderingPipeline/BaseRenderingPipeline.h"


SceneTen::SceneTen(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneTen::Start()
{

 
    
   
    



    Model* floor = new Model("Models/DefaultCube/DefaultCube.fbx", true);
    floor->name = "floor";
   
    Texture* cubediffuse = new Texture("Models/DefaultCube/Default_Diffuse.png");
    Texture* cubespecular = new Texture("Models/DefaultCube/Default_Specular.jpg");
    floor->meshes[0]->meshMaterial = new MaterialGBuffer();

    floor->meshes[0]->meshMaterial->gBufferMat()->diffuseTexture = cubediffuse;
    floor->meshes[0]->meshMaterial->gBufferMat()->specularTexture = cubespecular;

    floor->transform.position = glm::vec3(0, 0, 0);
    floor->transform.SetScale(glm::vec3(100, 0.25, 100));

    GraphicsRender::GetInstance().AddGbufferModels(floor, application->gBufferShader);
 
    float rotation = 0;

    // === Car ===
    Model* tempCar = new Model("Models/Car/Car.fbx");
    Texture* tempDiffuse = new Texture("Models/Car/Diffuse.png");
    Texture* tempSpecular = new Texture("Models/Car/Specular.png");
    

   



    float spacing = 10.0f;

    for (int x = 0; x < 30; ++x)
    {
        for (int z = 0; z < 30; ++z)
        {
            glm::vec3 carPosition = glm::vec3(x * spacing, 0.0f, z * spacing);
            float rotationY = rotation;

            Model* car = new Model(*tempCar);
            car->name = "Car_" + std::to_string(x) + "_" + std::to_string(z);

            Texture* diffuse = new Texture(*tempDiffuse);
            Texture* specular = new Texture(*tempSpecular);
            car->meshes[0]->meshMaterial = new MaterialGBuffer();
            car->meshes[0]->meshMaterial->gBufferMat()->diffuseTexture = diffuse;
            car->meshes[0]->meshMaterial->gBufferMat()->specularTexture = specular;

            car->transform.position = carPosition;
            car->transform.SetRotation(glm::vec3(-90, rotationY, 0)); // Rotate around Y
            GraphicsRender::GetInstance().AddGbufferModels(car, application->gBufferShader);

            Light* pointLight = new Light();
            pointLight->SetLightType(LightType::POINT_LIGHT);
            pointLight->InitializeDeferredLights();
            pointLight->SetColor(glm::vec4(1, 1, 1, 1));
            pointLight->SetAttenuation(1.0f, 0.09f, 0.032f);
            pointLight->transform.position = carPosition + glm::vec3(0, 4.0f, 0);

            Light* spotLight = new Light();
            spotLight->SetLightType(LightType::SPOT_LIGHT);
            spotLight->InitializeDeferredLights();
            spotLight->SetColor(glm::vec4(1, 1, 1, 1));
            spotLight->SetAttenuation(1.0f, 0.09f, 0.032f);
            spotLight->SetInnerAndOuterCutoffAngle(0, 45.0f);

            spotLight->transform.position = carPosition + glm::vec3(0, 1.5f, 0);
            spotLight->transform.SetRotation(glm::vec3(0,180,0));
            spotLight->lightRadius = 1.0f;
        }
    }

    

   

}

void SceneTen::Update()
{
}

void SceneTen::Render()
{
}
