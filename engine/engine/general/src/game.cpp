#include "game.h"

namespace Nebel
{
    void Game::Start()
    {
        running = true;
        resources = new Resources();
        scheduler = new Scheduler();
        scripting_system = new ScriptingSystem();
        platform = new Platform();
        renderer = new Renderer2D();// = new Renderer3D();
        ui = new UiSystem();
        audio = new AudioEngine();
        camera = new Camera();
        camera2d = new Camera2D();
        audio->Init();
    }
    void Game::Over()
    {
        if (networking != nullptr)
        {
            delete networking;
        }
        if (physics != nullptr)
        {
            delete physics;
        }
        if (ecs != nullptr)
        {
            delete ecs;
        }
        delete camera2d;
        delete camera;
        delete scheduler;
        if (scripting_system != nullptr)
        {
            delete scripting_system;
        }
        delete resources;
        audio->DeInit();
        delete audio;
        delete ui;
        if(renderer != nullptr)
        {
            renderer->End();
            delete renderer;
        }
        platform->~Platform();
        delete platform;
    }
}