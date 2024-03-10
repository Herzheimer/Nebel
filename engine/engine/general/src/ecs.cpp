#include "ecs.h"
#include "game.h"

namespace Nebel
{
    void Scene::Load()
    {
        Entity ent = Entity();
        ent.id = RNG();
        entities.push_back(ent.id);
        Game::ecs->entities[ent.id] = ent;
    }
    void Scene::UnLoad()
    {
        //
    }
} // namespace Nebel
