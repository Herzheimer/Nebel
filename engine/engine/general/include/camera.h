#pragma once

#include <glm/glm.hpp>
#include "input.h"

namespace Nebel
{
    struct Camera
    {
        glm::mat4 projection;
        glm::mat4 view;
        float fov = 45.0f;
        float near = 0.1f;
        float far = 100000.0f;
        float yaw=0;
        float pitch=0;
        glm::vec3 position = glm::vec3(0.0f, 0.0f,  0.0f);
        glm::vec3 front    = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up       = glm::vec3(0.0f, 1.0f,  0.0f);
        void update(float sensitivity);
    };
    struct Camera2D
    {
        glm::mat4 projection;
        float near = -1000.1f;
        float far = 1000.0f;
        float rotation = 0;
        glm::vec2 position = glm::vec2(0.0f, 0.0f);
        void update();
    };
} // namespace Nebel
