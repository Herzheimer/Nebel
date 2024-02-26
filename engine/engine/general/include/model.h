#pragma once

#include "mesh.h"
#include "SkeletalAnimation.h"
#include <vector>

namespace Nebel
{
    struct Model
    {
        std::vector<Mesh> meshes;
        void draw()
        {
            for(int i = 0; i < meshes.size(); i++)
            {
                meshes[i].draw();
            }
        }
        void destroy()
        {
            for(int i = 0; i < meshes.size(); i++)
            {
                meshes[i].destroy();
            }
        }
    };
    struct StaticModel
    {
        std::vector<StaticMesh> meshes;
        void create()
        {
            for (size_t i = 0; i < meshes.size(); i++)
            {
                meshes[i].create();
            }
        }
        void draw()
        {
            for(int i = 0; i < meshes.size(); i++)
            {
                meshes[i].draw();
            }
        }
        void destroy()
        {
            for(int i = 0; i < meshes.size(); i++)
            {
                meshes[i].destroy();
            }
        }
    };
    struct AnimatedModel
    {
        std::vector<AnimatedMesh> meshes;
        Joint root_joint;
        uint32_t joint_count;
        SkeletalAnimator animator;
        
        void create()
        {
            for(int i = 0; i < meshes.size(); i++)
            {
                meshes[i].create();
            }
        }
        void draw()
        {
            for(int i = 0; i < meshes.size(); i++)
            {
                meshes[i].draw();
            }
        }
        void destroy()
        {
            for(int i = 0; i < meshes.size(); i++)
            {
                meshes[i].destroy();
            }
        }
    };
} // namespace Nebel
