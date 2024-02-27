#pragma once

#include <glm/glm.hpp>

namespace Nebel
{
    struct Transform
    {
        //glm::vec3 position;
        //glm::quat rotation;
        //glm::vec3 scale;
        //glm::vec3 rotation_euler;
    };
    struct Transform2D : Transform
    {
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    };
    struct Transform3D : Transform
    {
        glm::vec3 position;
        //glm::quat rotation;
        glm::vec3 scale;
        //glm::vec3 rotation_euler;
    };
} // namespace Nebel
