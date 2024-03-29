#pragma once

namespace Nebel
{
    struct Networking
    {
        //
    };
    struct PhysicsWorld
    {
        virtual void step(float delta_time) = 0;
        virtual void ResolveCollisions(float delta_time) = 0;
        virtual void Synchronize_Transforms() = 0;
    };
    struct Renderer
    {
        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Resize() = 0;
        virtual void End() = 0;
        //void Init();
        //void Update();
        //void Resize();
        //~Renderer();
    };
    //struct SceneSystem
    //{
    //    //
    //};
} // namespace Nebel   
