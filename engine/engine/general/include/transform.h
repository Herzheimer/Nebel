#pragma once

#include <glm/glm.hpp>

namespace Nebel
{
    struct Transform2D
    {
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    };
    struct Transform
    {
        glm::vec3 position;
        //glm::quat rotation;
        glm::vec3 scale;
        //glm::vec3 rotation_euler;
    };
} // namespace Nebel
