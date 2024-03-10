#pragma once

#include "interfaces.h"
#include "glm/glm.hpp"

namespace Nebel
{
    struct Renderer2D : Renderer
    {
        glm::mat4 vp = glm::mat4(1);
        glm::mat4 mvp = glm::mat4(1);
        void Init() override;
        void Update() override;
        void Resize() override;
        void End() override;
    };
    struct Renderer3D : Renderer
    {
        glm::mat4 vp = glm::mat4(1);
        glm::mat4 mvp = glm::mat4(1);
        void Init() override;
        void Update() override;
        void Resize() override;
        void End() override;
    };
    
} // namespace Nebel
