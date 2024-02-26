#pragma once

#include "transform.h"
#include <vector>
#include <string>
#include "glm/gtc/matrix_inverse.hpp"

namespace Nebel
{
    struct Joint
    {
        uint32_t id;
        std::string name;
        std::vector<Joint> children;
        glm::mat4 animatedTransform = glm::mat4(1);

        //const glm::mat4 localBindTransform;
        glm::mat4 localBindTransform;
        glm::mat4 inverseBindTransform = glm::mat4(1);
        void calcInverseBindTransform(glm::mat4 parentBindTransform)
        {
            glm::mat4 bindTransform = parentBindTransform * localBindTransform;
            inverseBindTransform = glm::inverse(bindTransform);
            for (size_t i = 0; i < children.size(); i++)
            {
                children[i].calcInverseBindTransform(bindTransform);
            }
        }
    };
    struct KeyFrame
    {
        std::vector<Transform> transforms;
        float timestamp;
    };
    struct SkeletalAnimation
    {
        std::vector<KeyFrame> frames;
    };
    struct SkeletalAnimator
    {
        SkeletalAnimation* currentAnimation;
        float animationTime;
    };
} // namespace Nebel
