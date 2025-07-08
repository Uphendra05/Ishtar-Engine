#include "SceneEleven.h"
#include "../../RenderingPipeline/BaseRenderingPipeline.h"

SceneEleven::SceneEleven(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneEleven::Start()
{

    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);
    directionLight->castShadow = false;

    directionLight->transform.SetRotation(glm::vec3(-40, 0, 0));


    Light* pointLight = new Light();
    pointLight->Initialize(LightType::POINT_LIGHT, 1);
    pointLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    pointLight->SetColor(glm::vec4(1, 1, 1, 1));
    pointLight->SetAttenuation(1.0f, 0.09f, 0.032f);
    pointLight->castShadow = false;
    pointLight->transform.SetPosition(glm::vec3(1.37, 0.35, 0.50));

  

    Model* Gun = new Model("Models/Gun/Gun.obj");
    Gun->name = "Gun";
    Gun->transform.SetPosition(glm::vec3(-6.39, 0, 4.02));
    Gun->transform.SetScale(glm::vec3(2));
    Gun->castShadow = true;
    GraphicsRender::GetInstance().AddModelAndShader(Gun, application->defaultShader);

    Model* Wall = new Model("Models/Wall/Wall.obj");
    Wall->name = "Wall";
    Wall->transform.SetScale(glm::vec3(2));
    Wall->meshes[0]->meshMaterial->material()->shininess = 96;
    Wall->castShadow = true;
    GraphicsRender::GetInstance().AddModelAndShader(Wall, application->defaultShader);

    Model* House = new Model("Models/House/House.obj");
    House->name = "House";
    House->transform.SetPosition(glm::vec3(10,0,0));
    House->transform.SetScale(glm::vec3(2));
    House->meshes[0]->meshMaterial->material()->shininess = 96;
    House->castShadow = true;
    GraphicsRender::GetInstance().AddModelAndShader(House, application->defaultShader);
    

    


}

void SceneEleven::Update()
{
}

void SceneEleven::Render()
{
}
