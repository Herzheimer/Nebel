#include "game.h"

namespace Nebel
{
    void Game::Start()
    {
        running = true;
        resources = new Resources();
        components = new Components();
        scheduler = new Scheduler();
        platform = new Platform();
        renderer = new Renderer();
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
        delete camera2d;
        delete camera;
        delete scheduler;
        delete components;
        delete resources;
        audio->DeInit();
        delete audio;
        delete ui;
        renderer->~Renderer();
        delete renderer;
        platform->~Platform();
        delete platform;
    }
}