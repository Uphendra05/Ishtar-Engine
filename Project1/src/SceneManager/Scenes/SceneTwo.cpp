#include "SceneTwo.h"
#include "../../ApplicationRenderer.h"
#include "../../Player/PlayerController.h"
#include "../../PostProcessing bounds/CubeVolume.h"
SceneTwo::SceneTwo(const std::string& sceneName) : BaseScene::BaseScene(sceneName)
{

}

void SceneTwo::Start()
{
    Light* directionLight = new Light();
    directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
    directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
    directionLight->SetAttenuation(1, 1, 0.01f);
    directionLight->SetInnerAndOuterCutoffAngle(11, 12);

    directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
    directionLight->transform.SetPosition(glm::vec3(0, 0, 5));


    MeshInstance* instanceMesh = new MeshInstance();
    instanceMesh->LoadModel("Models/DefaultCube/DefaultCube.fbx");
    instanceMesh->name = "InstancedCube";
    TransformData data;
    data.position = glm::vec3(0, 5, 1);
    data.rotation = glm::vec3(0);
    data.scale = glm::vec3(0.5f);

    const float radius = 10;

    float startAngle = 45.0f; // Starting angle of the arc
    float endAngle = 360.0f;  // Ending angle of the arc


 /*   glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));*/



    glm::vec3 center(0); // Center point
    float objectSpacing = 20; // Spacing between objects along the circle

    for (float i = 0; i < 360; i += objectSpacing)
    {
        float angleRadians = glm::radians(i);
        float x = center.x + glm::sin(angleRadians) * radius;
        float z = center.z + glm::cos(angleRadians) * radius;

        // Instantiate object at calculated position
        instanceMesh->AddTransformData(glm::vec3(x, center.y, z));


    }

    GraphicsRender::GetInstance().AddModelAndShader(instanceMesh, application->defaultInstanceShader);

    Model* modelSphere = new Model();
    modelSphere->LoadModel("Models/DefaultSphere/DefaultSphere.fbx");
    modelSphere->name = "Sphere";
    GraphicsRender::GetInstance().AddModelAndShader(modelSphere, application->defaultShader);


}

void SceneTwo::Update()
{
}

void SceneTwo::Render()
{
}
