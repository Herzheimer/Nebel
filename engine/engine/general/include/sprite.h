#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "texture.h"

namespace Nebel
{
    struct SpriteAnimation
    {
        glm::vec2 row_column_count;
        glm::vec2 start_indices;
        glm::vec2 end_indices;
        glm::vec2 current_indices;
        glm::vec2 dimensions;
        float fps = 24.0f;
        void update();
    };
    struct Sprite
    {
        uint32_t texture_id;
        Texture* tex;
        glm::vec2 dimensions;
        glm::vec2 row_column_indices;
        glm::vec2 row_column_count;
        size_t currentanimation = -1;
        std::vector<SpriteAnimation> animations;
        void update();
    };
    
} // namespace Nebel
