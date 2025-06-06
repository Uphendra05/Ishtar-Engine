#pragma once

#include "Light.h"

class LightManager 
{
public:

    static LightManager& GetInstance();
   

    void SetUniforms(GLuint shaderID);
    void AddLight(Light* light);
    void RemoveLight(Light* light);
    void AddShader(Shader* shader);
    void RemoveShader(Shader* shader);

    void AddDeferredLight(Light* light);
    void RemoveDeferredLight(Light* light);
    void AddDeferredShader(Shader* shader);
    void RemoveDeferredShader(Shader* shader);

    // This is called every frame
    void UpdateUniformValues(GLuint shaderID);
    void UpdateUniformValuesToShader(Shader* shader);
    void  RenderLights();
    void  RenderLightPassShaderLights();
    static const unsigned int MAX_LIGHT = 11;
    static const unsigned int MAXDEFERRED_LIGHT = 32;
    
    const std::vector<Light*>& GetLightList();
    const std::vector<Light*>& GetDeferredLightList();
private:
    std::vector<Light*> lightList;

    std::vector<Light*> deferredLights;

    std::vector<Shader*> listOfShaders;

    std::vector<Shader*> deferredLightShader;
};



