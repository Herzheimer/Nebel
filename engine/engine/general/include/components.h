#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include "ecs.h"
#include "sprite.h"
#include "transform.h"
#include "rng.h"
#include "resources.h"

namespace Nebel
{
    enum class ComponentType
    {
        Sprite_Component,
        Transform2D_Component,
        Custom_Component,
    };
    struct SpriteComponent : IComponent
    {
        uint64_t id;
        Sprite* sprite;
    };
    struct Transform2DComponent : IComponent
    {
        uint64_t id;
        Transform2D* transform;
    };
    struct Components
    {
        std::map<uint64_t, SpriteComponent> sprites;
        std::map<uint64_t, Transform2DComponent> transform2d;
        std::map<uint16_t, ComponentContainer> custom_components;
    };
}
