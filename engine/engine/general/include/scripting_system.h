#pragma once

#include "ecs.h"
#include <map>

namespace Nebel
{
    struct Script
    {
        Entity* entity = nullptr;
        virtual void onCreate() = 0;
        virtual void update() = 0;
        virtual void physics_update(float delta_time) = 0;
        virtual void onDestroy() = 0;
        //template<typename T>
        //IComponent* Get();
    };
    struct ScriptContainer
    {
        //Entity* entity = nullptr;
        uint64_t entity_id = -1;
        Script* script = nullptr;
        void onCreate();
        void update();
        void physics_update(float delta_time);
        void onDestroy();
        ~ScriptContainer()
        {
            if (script != nullptr)
            {
                delete script;
            }
        }
    };
    struct ScriptingSystem
    {
        std::map<uint64_t, ScriptContainer> scripts;
        //std::map<uint64_t, std::function> registry;
        void update();
        void physics_update(float delta_time);
    };
} // namespace Nebel
