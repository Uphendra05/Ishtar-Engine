#pragma once
#include "random"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


static float RandomBetweenTwoFloats(float A, float B)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(A, B);
    return dis(gen);
}


static glm::vec3 RandomBetweemTwoVec3(glm::vec3 A, glm::vec3 B)
{
    float x = RandomBetweenTwoFloats(A.x, B.x);
    float y = RandomBetweenTwoFloats(A.y, B.y);
    float z = RandomBetweenTwoFloats(A.z, B.z);
    return glm::vec3(x, y, z);
}

static glm::vec4 RandomBetweenTwoVec4(glm::vec4 A, glm::vec4 B)
{
    float x = RandomBetweenTwoFloats(A.x, B.x);
    float y = RandomBetweenTwoFloats(A.y, B.y);
    float z = RandomBetweenTwoFloats(A.z, B.z);
    float w = RandomBetweenTwoFloats(A.w, B.w);
    return glm::vec4(x, y, z, w);
}