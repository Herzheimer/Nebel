#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include "rng.h"
#include "transform.h"

namespace Nebel
{
    enum class ResourceType
    {
        SpriteResource,
        CustomResource,
    };
    struct Resources
    {
        std::map<uint64_t, Sprite> sprites;
        std::map<uint16_t, ComponentContainer> custom_components;
    };
} // namespace Nebel
