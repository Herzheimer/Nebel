#include "scripting_system.h"
#include "script.h"
#include "game.h"
#include <iostream>

namespace Nebel
{
    void ScriptContainer::onCreate()
    {
        script->onCreate();
    }
    void ScriptContainer::update()
    {
        script->update();
    }
    void ScriptContainer::physics_update(float delta_time)
    {
        script->physics_update(delta_time);
    }
    void ScriptContainer::onDestroy()
    {
        script->onDestroy();
    }
    void ScriptingSystem::update()
    {
        for (size_t i = 0; i < scripts.size(); i++)
        {
            scripts[i].update();
        }
    }
    void ScriptingSystem::physics_update(float delta_time)
    {
        for (size_t i = 0; i < scripts.size(); i++)
        {
            scripts[i].physics_update(delta_time);
        }
    }
    template<typename T>
    T getScript(Entity* entity)
    {
        return (T) Game::scripting_system->scripts[entity->id];
    }
    void removeScript(Entity* entity)
    {
        Game::scripting_system->scripts[entity->id].onDestroy();
        // TODO
        delete Game::scripting_system->scripts[entity->id].script;
        Game::scripting_system->scripts[entity->id].script->entity;//TODO: remove script on the entity's end
        Game::scripting_system->scripts[entity->id].script->entity = nullptr;
        Game::scripting_system->scripts[entity->id].script = nullptr;
        Game::scripting_system->scripts[entity->id]; // TODO
        Game::scripting_system->scripts.erase(entity->id);
    }
    void TestScript::onCreate()
    {
        std::cout << "TestScript created" << std::endl;
        sound.path = "../../../../assets/audio/test.wav";
        Game::audio->play(sound);
    }
    void TestScript::update()
    {
        //std::cout << "TestScript updated" << std::endl;
    }
    void TestScript::physics_update(float delta_time)
    {
        //std::cout << "TestScript updated" << std::endl;
    }
    void TestScript::onDestroy()
    {
        std::cout << "TestScript destroyed" << std::endl;
    }
} // namespace Nebel
