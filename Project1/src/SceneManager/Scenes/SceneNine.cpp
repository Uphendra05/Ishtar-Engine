#include "SceneNine.h"

#include "../../ApplicationRenderer.h"

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
    EmptyCheck* dummy = new EmptyCheck();
   

    // TODO Change this code to separate class
    /*Model* interiorMapBuilding = new Model("Models/DefaultQuad/DefaultQuad.fbx");
   
    interiorMapBuilding->meshes[0]->meshMaterial = new InteriorMappingMat();
    InteriorMappingMat* interiorMapMat = interiorMapBuilding->meshes[0]->meshMaterial->interiorMapMaterial();

    std::vector<std::string> faces
    {
       ("Textures/Interior/Wall_1.png"),
       ("Textures/Interior/Wall_1.png"),
       ("Textures/Interior/Ceiling_1.png"),
       ("Textures/Interior/Floor_1.png"),
       ("Textures/Interior/Wall_1.png"),
       ("Textures/Interior/Wall_1.png")
    };

    interiorMapMat->InteriorMapTexture->LoadTexture(faces);

   
    GraphicsRender::GetInstance().AddModelAndShader(interiorMapBuilding, application->interiorMapShader);*/
   
}

void SceneNine::Update()
{
}

void SceneNine::Render()
{
}
