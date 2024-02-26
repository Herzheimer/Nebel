#pragma once

namespace Nebel
{
    struct Renderer
    {
        void Init();
        void Update();
        void Resize();
        ~Renderer();
    };
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
