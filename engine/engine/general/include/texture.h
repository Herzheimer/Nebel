#pragma once

#include <cstdint>

namespace Nebel
{
    struct Texture
    {
        uint32_t id;
        int width, height, num_channels;
        unsigned char* data;
        void Texture2D();
        void use(uint32_t slot);
        void use();
    };
    
} // namespace Nebel
