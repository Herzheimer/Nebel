#pragma once

#include "glm/glm.hpp"

//#define MAX_BONE_INFLUENCE 4

namespace Nebel
{
    struct StaticVertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;
        //glm::vec3 Tangent;
        //glm::vec3 Bitangent;
    };
    struct AnimatedVertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;
        //glm::vec3 Tangent;
        //glm::vec3 Bitangent;
        glm::ivec3 boneIDs;
        glm::vec3 weights;
        //int m_BoneIDs[MAX_BONE_INFLUENCE];
        //float m_Weights[MAX_BONE_INFLUENCE];
    };
    
} // namespace Nebel
