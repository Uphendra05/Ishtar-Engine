#include "InteriorMapping.h"
#include "../InteriorMappingMat.h"
#include "../GraphicsRender.h"
InteriorMapping::InteriorMapping()
{
   
   
   

}

InteriorMapping::InteriorMapping(BaseRenderingPipeline* applicaiton)
{
    this->application = applicaiton;

    LoadModel("Models/DefaultQuad/DefaultQuad.fbx");
    name = "Window";
    meshes[0]->meshMaterial = new InteriorMappingMat();
   
    InteriorMappingMat* interiorMapMat = meshes[0]->meshMaterial->interiorMapMaterial();
   
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

    GraphicsRender::GetInstance().AddModelAndShader(this, applicaiton->solidColorShader);



   

}

InteriorMapping::~InteriorMapping()
{

}



void InteriorMapping::Init()
{
   
}

void InteriorMapping::Draw(Shader* shader)
{
    if (useDefaultShader)
    {
        
        Model::Draw(shader);
    }
    else
    {
        shader = application->interiorMapShader;
       


        shader->Bind();
        shader->setFloat("NUM_ROOMS_X", noOfRoomsX);
        shader->setFloat("NUM_ROOMS_Y", noOfRoomY);
        
        Model::Draw(shader);
    }
    
   
}

void InteriorMapping::DrawProperties()
{
   
    Model::DrawProperties();

    if (!ImGui::TreeNodeEx("Material Properties", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }

    DrawDragFloatImGui("No Of Rooms X", noOfRoomsX, 0.1f, 0, 100);
    DrawDragFloatImGui("No Of Rooms Y", noOfRoomY, 0.1f, 0, 100);
    DrawBoolImGui("Use Default Shader", useDefaultShader, 100);


    ImGui::TreePop();


}

void InteriorMapping::SceneDraw()
{
    Model::SceneDraw();
}

void InteriorMapping::Update(float deltaTime)
{
}
