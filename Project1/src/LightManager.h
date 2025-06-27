#pragma once

#include "Light.h"
#include "LightUBO.h"
#include "UniformBuffer.h"

class LightManager 
{
public:

    static LightManager& GetInstance();
    ~LightManager();

    void SetUniforms(GLuint shaderID);
    void SetUBOs();
    void AddLight(Light* light);
    void RemoveLight(Light* light);
    void AddShader(Shader* shader);
    void RemoveShader(Shader* shader);

    void AddDeferredLight(Light* light);
    void RemoveDeferredLight(Light* light);
    void AddDeferredShader(Shader* shader);
    void RemoveDeferredShader(Shader* shader);

    glm::mat4 LightProjection();
    glm::mat4 LightView();
    glm::mat4 LightSpaceMatrix();

    // This is called every frame
    void UpdateUniformValues(GLuint shaderID);
    void UpdateUniformValuesToShader(Shader* shader);
    void  RenderLights();
    void  RenderLightPassShaderLights();
    void UpdateLightPassUBO();
    static const unsigned int MAX_LIGHT = 11;
    static const unsigned int MAXDEFERRED_LIGHT = 200;
    
    const std::vector<Light*>& GetLightList();
    const std::vector<Light*>& GetDeferredLightList();
    UniformBuffer* LightUBO;

    
private:
    std::vector<Light*> lightList;

    std::vector<Light*> deferredLights;

    std::vector<Shader*> listOfShaders;

    std::vector<Shader*> deferredLightShader;

    LightBlock block;


};



