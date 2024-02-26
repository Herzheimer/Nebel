#include "sprite.h"
#include "graphics.h"
#include "game.h"

namespace Nebel
{
    void SpriteAnimation::update()
    {
        current_indices.x+=1;
        if (current_indices.x >= end_indices.x)
        {
            current_indices.x = start_indices.x;
            current_indices.y+=1;
            if (current_indices.y >= end_indices.y)
            {
                current_indices.y = start_indices.y;
            }
        }
    }
    void Sprite::update()
    {
        if (animations.size()>0)
        {
            animations[currentanimation].update();
            row_column_indices = animations[currentanimation].current_indices;
            row_column_count = animations[currentanimation].row_column_count;
        }
    }
} // namespace Nebel
