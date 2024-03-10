#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include "model.h"
#include "rng.h"
#include "transform.h"

namespace Nebel
{
    enum class ResourceType
    {
        SpriteResource,
        ModelResource,
        StaticModelResource,
        TextureResource,
        CustomResource,
    };
    struct Resources
    {
        std::map<uint64_t, Sprite> sprites;
        std::map<uint64_t, Model> models;
        std::map<uint64_t, StaticModel> static_models;
        std::map<uint64_t, Texture> textures; // TODO
        //std::map<uint16_t, ComponentContainer> custom_components;
    };
} // namespace Nebel
