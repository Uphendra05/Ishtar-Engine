#pragma once
#ifndef MODEL_H
#define MODEL_H



#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "BaseMaterial.h"
#include "UnLitMaterial.h"
#include "EntityManager/Entity.h"


struct LODElement
{

    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<unsigned int> meshesIndex;
    float distance = 0;
};

struct LODGroup
{
    std::vector<LODElement> meshElements;
};

enum class eOcculsionState
{
    STATIC = 0,
    DYNAMIC = 1,
    NO_OCCULSION = 3, 

};

class Model : public Entity
{
public:


    std::vector<Texture*> textures_loaded;
    std::vector<std::shared_ptr<Mesh>> meshes;

    std::string directory;
    std::string modelPath;
    std::string id; //if needed 

    Texture* alphaMask;
    Shader* modelShader = nullptr;

    eOcculsionState occulsionState = eOcculsionState::STATIC;
    int offset;
    float size;

    bool gammaCorrection;
    bool isWireFrame;
    bool isVisible = true;
    bool useLOD = false;
    bool isLoadTexture;
    bool isOccluded = false;

    Model();
    Model(const Model& copyModel, bool isDebugModel = false);
    Model(std::string const& path, bool isLoadTexture = true, bool isDebugModel = false);
    ~Model();
    void LoadModel(const Model& copyModel, bool isDebugModel = false);
    virtual void LoadModel(std::string const& path, bool isLoadTexture = true, bool isDebugModel = false);
    void Draw(Shader& shader);
    virtual void Draw(Shader* shader);
    void DrawSolidColor(const glm::vec4& color, bool isWireframe = false);
    
    virtual void DrawProperties();
    virtual void SceneDraw();

    virtual void Start() override;
    virtual void Update(float deltaTime) override;
    virtual void Render();
    virtual void OnDestroy();

    void AddLODGroup(const std::vector<unsigned int>& meshIndices, float distance);
    virtual std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
protected:

    Texture* LoadDefaultTexture(aiTextureType type, std::string typeName);
    Texture* LoadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);

    std::string TextureType(aiTextureType type);

    LODElement* GetLODbyDistance(float distance);

    void ProcessNode(aiNode* node, const aiScene* scene);
    void SetModelName();

    LODGroup mLODGroup;

    const std::string alphaTextureDefaultPath = "Textures/DefaultTextures/Default_Opacity.png";

private:

    float mdDefaultCulledDistance = 20;
    float mCameraDistance;

};




#endif