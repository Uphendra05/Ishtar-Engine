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

  

    Model* Gun = new Model("Models/Gun/Gun.obj");
    Gun->name = "Gun";
    Gun->transform.SetPosition(glm::vec3(-6.39, 0, 4.02));
    Gun->transform.SetScale(glm::vec3(2));
    Gun->castShadow = true;

    GraphicsRender::GetInstance().AddModelAndShader(Gun, application->defaultShader);

    


}

void SceneEleven::Update()
{
}

void SceneEleven::Render()
{
}
