#include "SceneTen.h"

#include "../../ApplicationRenderer.h"


SceneTen::SceneTen(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneTen::Start()
{

   

   

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
