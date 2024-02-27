#include "nebel.h"
#include "game.h"
#include "graphics.h"
#include "scheduler.h"
#include "importer.h"
#include <iostream>

namespace Nebel
{
    void run()
    {
        Game::Start();
        //Game::physics = new PhysicsWorld2D();
        Game::platform->Create(1280, 720, "Hello World");
        Game::renderer->Init();
        //std::function<void()> somefunc = [](){std::cout << "surprise" << std::endl;};
        //SchedulerTask UpdateTask(somefunc, 50);
        //Game::scheduler->addTask(UpdateTask);
        Game::camera->update(1);
        Game::camera2d->update();
        Sound sound;
        sound.path = "../../../../assets/audio/test.wav";
        Game::audio->play(sound);
        
        std::function<void()> sprites_update = []()
        {
            for (auto &&sprite : Game::resources->sprites)
            {
                sprite.second.update();
            }
        };
        SchedulerTask sprites_update_task = SchedulerTask(sprites_update, 2);
        Game::scheduler->addTask(sprites_update_task);
        while (!Game::platform->ShouldClose())
        {
            Game::scheduler->Update();
            Game::platform->UpdateInput();
            Game::platform->Update();
            Game::renderer->Update();
            Game::platform->LateUpdate();
            //if(Input::controller[0].isPressed(CONTROLLER_A))
            //{
            //    std::cout << "A is down" << std::endl;
            //}
        }
        Game::Over();
    }
} // namespace Nebel
