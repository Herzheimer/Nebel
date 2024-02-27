#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include "rng.h"
#include "transform.h"

namespace Nebel
{
    struct Entity;
    struct GlueObj
    {
        uint16_t component_type;
        uint64_t id;
    };
    struct IComponent
    {
        Entity* entity;
        virtual void Serialize();
    };
    struct ComponentContainer
    {
        std::map<uint64_t, IComponent*> components;
        uint16_t component_type;
    };
    struct Entity
    {
        Entity* parent = nullptr;
        uint64_t id;
        Transform* transform; // and 2D??
        std::vector<uint16_t> component_types;
        void Serialize();
    };
    struct Scene
    {
        std::vector<uint64_t> entities;
        void Load();
        void UnLoad();
    };
}