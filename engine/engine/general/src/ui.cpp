#include "ui.h"
#include "graphics.h"
#include "game.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Nebel
{
    void UiNode::render()
    {
        UiBox* box;
        UiImage* image;
        glm::vec4 color = glm::vec4(0.8, 0.8, 0.9, 1.0);
        recalculate();
        switch (type)
        {
        case UiType::UiBox:
            box = (UiBox*) element;
            DrawRect(matrix, color);
            //delete box;
            break;
        case UiType::UiImage:
            image = (UiImage*) element;
            DrawImage(matrix, color, image->tex1);
            //delete image;
            break;
        default:
            break;
        }
    }
    void UiNode::recalculate()
    {
        float halfwidth = Game::platform->width/2;
        float halfheight = Game::platform->height/2;
        glm::vec3 pos = {0,0,0};
        glm::vec3 scale = {transform.scale, 1};
        switch (scale_unit_x)
        {
        case UiUnitType::UiPercent:
            scale.x = Game::platform->width/200.0*scale.x;
            break;
        case UiUnitType::UiEm:
            scale.x = 800.0*scale.x/Game::platform->vertical_dpi;
            break;
        case UiUnitType::UiPixel:
        default:
            break;
        }
        switch (scale_unit_y)
        {
        case UiUnitType::UiPercent:
            scale.y = Game::platform->height/200.0*scale.y;
            break;
        case UiUnitType::UiEm:
            scale.y = 800.0*scale.y/Game::platform->horizontal_dpi;
            break;
        case UiUnitType::UiPixel:
        default:
            break;
        }

        // TODO: take Origin shift into account when using translation of the transform
        if(position_unit_x == UiUnitType::UiCenter){pos.x+=0;}
        else if(position_unit_x == UiUnitType::UiPercent){pos.x+=Game::platform->width/100.0*transform.position.x;}
        else if(position_unit_x == UiUnitType::UiEm){pos.x+=transform.position.x/Game::platform->horizontal_dpi*1600;}
        else if(position_unit_x == UiUnitType::UiPixel){pos.x+=transform.position.x;}
        if(position_unit_y == UiUnitType::UiCenter){pos.y+=0;}
        else if(position_unit_y == UiUnitType::UiPercent){pos.y+=Game::platform->height/100*transform.position.y;}
        else if(position_unit_y == UiUnitType::UiEm){pos.y+=transform.position.y/Game::platform->vertical_dpi*1600;}
        else if(position_unit_y == UiUnitType::UiPixel){pos.y+=transform.position.y;}

        switch (origin_type)
        {
        case UiOriginType::UiOriginTopLeft:
            pos.x += -halfwidth +(scale.x);
            pos.y += -halfheight+(scale.y);
            break;
        case UiOriginType::UiOriginTopRight:
            pos.x  =  halfwidth -(scale.x) - pos.x;
            pos.y += -halfheight+(scale.y);
            break;
        case UiOriginType::UiOriginBottomLeft:
            pos.x += -halfwidth +(scale.x);
            pos.y  =  halfheight-(scale.y) - pos.y;
            break;
        case UiOriginType::UiOriginBottomRight:
            pos.x = (halfwidth - scale.x) - pos.x;
            pos.y = (halfheight- scale.y) - pos.y;
            break;
        case UiOriginType::UiOriginCenter:
            //pos += {0,0,0};
            break;
        }
        matrix = Game::camera2d->projection;
        matrix = glm::translate(matrix,pos);//glm::vec3(transform.position, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(transform.rotation), glm::vec3(0.f, 0.f, 1.f));
        matrix = glm::scale(matrix, scale); // glm::vec3(transform.scale, 1.0f));
        if (parent!=nullptr)
        {
            parent->recalculate();
            matrix = parent->matrix * matrix;
        }
    }
    void UiSystem::render()
    {
        float halfwidth = Game::platform->width / 2;
        float halfheight = Game::platform->height / 2;
        glm::mat4 proj = glm::ortho(-halfwidth, halfwidth, halfheight, -halfheight, -1000.0f, 1000.0f);
        for (size_t i = 0; i < nodes.size(); i++)
        {
            nodes[i].render();
        }
    }
} // namespace Nebel
