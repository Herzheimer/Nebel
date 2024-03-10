#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Nebel
{
    struct Transform2D;
    struct Transform
    {
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;
        //glm::vec3 rotation_euler;
        void setTransform2D(Transform2D transform2d);
        Transform2D getTransform2D();
        void setPosition2D(glm::vec2 pos){position.x=pos.x; position.y = pos.y;}
        void setRotation2D(float angle){rotation.w = angle;} // TODO
        void setScale2D(glm::vec2 scale2D){scale.x=scale2D.x; scale.y = scale2D.y;}
        glm::vec2 getPosition2D(){return glm::vec2(position.x, position.y);}
        float getRotation2D(){return rotation.w;} // TODO
        glm::vec2 getScale2D(){return glm::vec2(scale.x, scale.y);}
    };
    struct Transform2D : Transform
    {
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    };
} // namespace Nebel
