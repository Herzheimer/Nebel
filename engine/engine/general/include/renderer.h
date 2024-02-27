#pragma once

#include "interfaces.h"

namespace Nebel
{
    struct Renderer2D : Renderer
    {
        void Init();
        void Update();
        void Resize();
        ~Renderer2D();
    };
    struct Renderer3D : Renderer
    {
        void Init();
        void Update();
        void Resize();
        ~Renderer3D();
    };
    
} // namespace Nebel
