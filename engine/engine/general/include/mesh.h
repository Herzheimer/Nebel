#pragma once

#include <cstdint>
#include <vector>
#include "Vertex.h"

namespace Nebel
{
    struct VertexAttribute
    {
        const char* name;
        uint16_t offset;
        uint16_t stride;
        uint16_t num_components;
        bool isNormalized = false;
    };
    struct VertexStructure
    {
        std::vector<VertexAttribute> attributes;
        uint32_t byte_size; //sum of bytes of each attribute
        bool is_instanced = false;
    };
    struct Mesh
    {
        uint32_t VBO, VAO, EBO;
        uint32_t materialID = -1;
        uint32_t index_count = 0;
        void create(void* vertices, void* indices, uint32_t vertex_size, uint32_t index_size);
        void draw();
        void destroy();
    };
    struct StaticMesh
    {
        uint32_t VBO, VAO, EBO;
        uint32_t materialID = -1;
        uint32_t index_count = 0;
        std::vector<StaticVertex> vertices;
        std::vector<uint32_t> indices;
        void create();
        void draw();
        void destroy();
    };
    struct AnimatedMesh
    {
        uint32_t VBO, VAO, EBO;
        uint32_t materialID = -1;
        uint32_t index_count = 0;
        std::vector<AnimatedVertex> vertices;
        std::vector<uint32_t> indices;
        void create();
        void draw();
        void destroy();
    };
} // namespace Nebel

/*
    Position
    Normal
    binormal
    bitangent
    Tex0
    Tex1
    VertexColor
*/