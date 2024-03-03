#pragma once

#include "game.h"
#include "scripting_system.h"

namespace Nebel
{
    struct TestScript : Script
    {
        Sound sound;

        void onCreate() override;
        void update() override;
        void physics_update(float delta_time) override;
        void onDestroy() override;
    };
    template<typename T>
    void add_Script(Entity* entity)
    {
        Game::scripting_system->scripts[entity->id] = ScriptContainer();
        Game::scripting_system->scripts[entity->id].script = new T();
        Game::scripting_system->scripts[entity->id].script->entity = entity;
        Game::scripting_system->scripts[entity->id].entity_id = entity->id;
        Game::scripting_system->scripts[entity->id].onCreate();
    }
    //#define REGISTER_SCRIPT(T) uint64_t T = RNG(); script_registy[T] = [](){ScriptContainer sc; sc.script=new T() return sc;};
    void removeScript(Entity* entity);
} // namespace Nebel
