#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include "interfaces.h"
#include "components.h"
#include "rng.h"
#include "transform.h"

namespace Nebel
{
    struct Entity
    {
        Entity* parent = nullptr;
        uint64_t id;
        Transform transform; // and 2D??
        Transform2D transform2D;
        std::vector<uint16_t> component_types;
        void Serialize();
    };
    struct Scene
    {
        std::vector<uint64_t> entities;
        void Load();
        void UnLoad();
    };
    struct ECS
    {
        std::map<uint64_t, Entity> entities;
        Components components;
        //std::map<const char*, Scene> scenes;
        std::map<uint64_t, Scene> scenes;
        std::map<const char*, uint64_t> scene_ids;
    };
}