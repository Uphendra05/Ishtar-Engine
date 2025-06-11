#pragma once
#include <glm/glm.hpp>

struct Lights
{
    glm::vec3 position;
    float pad1 = 0.0f;
    glm::vec3 direction;
    float pad2 = 0.0f;
    int lightType;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
    glm::vec4 color;
    float radius;
    float pad3 = 0.0f, pad4 = 0.0f, pad5 = 0.0f;


};

struct LightBlock
{
    Lights lights[1];
};