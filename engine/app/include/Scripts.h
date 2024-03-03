#pragma once

#include "Game.h"

namespace Nebel
{
    struct PlayerScript : Script
    {
        float speed = 2000;
        PhysicObject2D* physics_thing;
        glm::vec2 move_vec = {0, 0};
        void onCreate() override
        {
            physics_thing = Game::ecs->components.physics_components[entity->id].object;
        }
        void update() override
        {
            move_vec = {0, 0};
            if(Input::isKeyDown(Key::W))
            {
                move_vec.y += 1;
            }
            if(Input::isKeyDown(Key::S))
            {
                move_vec.y -= 1;
            }
            if(Input::isKeyDown(Key::D))
            {
                move_vec.x += 1;
            }
            if(Input::isKeyDown(Key::A))
            {
                move_vec.x -= 1;
            }
            glm::normalize(move_vec);
            move_vec *= speed;
        }
        void physics_update(float delta_time) override
        {
            glm::vec2 apl = {0, 0};
            physics_thing->addForce(apl);
            
            physics_thing->move(move_vec*delta_time);
            Game::camera2d->position = physics_thing->transform.position;
            //Game::camera2d->update_view();
        }
        void onDestroy() override
        {
            physics_thing = nullptr;
        }
    };
} // namespace Nebel
