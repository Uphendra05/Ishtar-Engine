#include "SceneNine.h"

#include "../../RenderingPipeline/BaseRenderingPipeline.h"

#include "../../PostProcessing bounds/CubeVolume.h"
#include "../../InteriorMapping/InteriorMapping.h"
#include "../../InteriorMapping/EmptyCheck.h"

SceneNine::SceneNine(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{
}

void SceneNine::Start()
{

   

    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));

    InteriorMapping* window = new InteriorMapping(application);

    Model* window2 = new Model("Models/DefaultQuad/DefaultQuad.fbx");
    window2->name = "Window 2";
    Texture* diffuse = new Texture("Textures/Interior/blending_transparent_window.png");
    Texture* alpha = new Texture("Textures/Interior/WindowAlphaMask.png");
    window2->meshes[0]->meshMaterial->material()->diffuseTexture = diffuse;
    window2->meshes[0]->meshMaterial->material()->alphaTexture = alpha;
    window2->meshes[0]->meshMaterial->material()->useMaskTexture = true;

    GraphicsRender::GetInstance().AddModelAndShader(window2, application->alphaBlendShader);
    
   
   
}

void SceneNine::Update()
{
}

void SceneNine::Render()
{
}
