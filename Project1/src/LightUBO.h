#pragma once
#include <glm/glm.hpp>

struct Lights
{
    glm::vec3 position;
    float pad1;

    glm::vec3 direction;
    float pad2;

    int lightType;
    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
    float radius;
    float pad3;

    glm::vec4 color;


};

struct LightBlock
{
    Lights lights[200];
};