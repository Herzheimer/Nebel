#include "nebel.h"
#include "game.h"
#include "graphics.h"
#include "scheduler.h"
#include "importer.h"
#include <iostream>
#include "physics2d.h"
#include "scripting_system.h"
#include "script.h"
#include "Scripts.h"

namespace Nebel
{
    void run()
    {
        Game::Start();
        Game::ecs = new ECS();
        Game::platform->Create(1280, 720, "Hello World");
        Game::renderer->Init();
        Game::camera->update(1);
        Game::camera2d->update();
        PhysicsWorld2D pw2d = PhysicsWorld2D();
        ImpulseSolver2D impulse_solver = ImpulseSolver2D();
        pw2d.solvers.push_back(&impulse_solver);
        Game::physics = &pw2d;
        std::function<void(float)> phys_update = [](float delta_time){
            //Game::physics->step(delta_time);
            //Game::physics->ResolveCollisions(delta_time);
            //Game::scripting_system->physics_update(delta_time);
            Game::physics->ResolveCollisions(delta_time);
            Game::scripting_system->physics_update(delta_time);
            Game::physics->step(delta_time);
            Game::physics->Synchronize_Transforms();
        };
        SchedulerTask UpdateTask(phys_update, 60);
        Game::scheduler->addTask(UpdateTask);
        
        std::function<void(float)> sprites_update = [](float delta_time)
        {
            for (auto &&sprite : Game::resources->sprites)
            {
                sprite.second.update();
            }
        };
        SchedulerTask sprites_update_task = SchedulerTask(sprites_update, 2);
        Game::scheduler->addTask(sprites_update_task);
        Transform2D pt1;
        pt1.position = {0,0};
        pt1.rotation = 0;
        pt1.scale = {1,1};
        AABB2D ab1;
        ab1.max = {Game::resources->sprites[0].dimensions.x, Game::resources->sprites[0].dimensions.y};// Game::resources->sprites[0].dimensions; // or {10,10};
        ab1.min = {-Game::resources->sprites[0].dimensions.x, -Game::resources->sprites[0].dimensions.y};
        PhysicObject2D ph1 = PhysicObject2D();
        ph1.type = PhysicsObjType::DynamicPO;
        ph1.force = {0,0};
        ph1.linear_velocity = {0,0};
        ph1.mass = 2;
        ph1.restitution = 2;
        ph1.shape = &ab1;
        ph1.transform = pt1;
        pw2d.physic_objects.push_back(&ph1);

        Entity ent1 = Entity();
        ent1.id = 0;
        //pt1.scale = ab1.max;
        //Game::resources->sprites[0].dimensions = pt1.scale;
        pt1.scale = Game::resources->sprites[0].dimensions;
        ent1.transform2D = ph1.transform;
        Game::ecs->entities[ent1.id] = ent1;
        
        Game::ecs->components.physics_components[ent1.id] = {};
        Game::ecs->components.physics_components[ent1.id].entity = &Game::ecs->entities[ent1.id];
        Game::ecs->components.physics_components[ent1.id].object=&ph1;

        Entity ent2 = ent1;
        ent2.id = 1;
        Game::ecs->entities[ent2.id] = ent2;
        
        Transform2D pt2;
        pt2.position = {80,40};
        pt2.rotation = 0;
        pt2.scale = {40,40};
        ent2.transform2D=pt2;
        AABB2D ab2;
        ab2.max = { 40,  40};
        ab2.min = {-40, -40};
        PhysicObject2D ph2 = ph1;
        ph2.type = PhysicsObjType::DynamicPO;
        ph2.force = {0,0};
        ph2.linear_velocity = {0,0};
        ph2.mass = 8;
        ph2.restitution = 3;
        ph2.shape = &ab1;
        ph2.transform = pt2;
        pw2d.physic_objects.push_back(&ph2);
        Game::ecs->components.physics_components[ent2.id] = {};
        Game::ecs->components.physics_components[ent2.id].entity = &Game::ecs->entities[ent2.id];
        Game::ecs->components.physics_components[ent2.id].object=&ph2;

        //add_Script<TestScript>(&ent1);
        add_Script<PlayerScript>(&ent1);

        while (!Game::platform->ShouldClose())
        {
            Game::scheduler->Update();
            Game::scripting_system->update();
            Game::platform->UpdateInput();
            Game::platform->Update();
            Game::renderer->Update();
            Game::platform->LateUpdate();
            //if(Input::controller[0].isPressed(CONTROLLER_A))
            //{
            //    std::cout << "A is down" << std::endl;
            //}
            //std::cout << "ph1 pos: " << ph1.transform.position.x << ", " << ph1.transform.position.y << std::endl;
        }
        removeScript(&ent1);
        Game::physics = nullptr;
        Game::Over();
    }
} // namespace Nebel
