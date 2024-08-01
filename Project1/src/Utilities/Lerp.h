#pragma once
#include <glm/glm.hpp>

static glm::vec3 Lerp(const glm::vec3& start, const glm::vec3& end, float t)
{
    t = glm::clamp(t, 0.0f, 1.0f);

    return start + t * (end - start);
}