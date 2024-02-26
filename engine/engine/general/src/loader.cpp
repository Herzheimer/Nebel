#include "loader.h"

#include <iostream>
#include <fstream>
#include <vector>

namespace Nebel
{    
    void loadModel(AnimatedModel &model, const char* path)
    {
        uint32_t file_format_version = -1;
        uint32_t data_version = -1;
        uint32_t model_type = -1;
    }
    void loadModel(StaticModel &model, const char* path)
    {
        uint32_t file_format_version = -1;
        uint32_t data_version = -1;
        uint32_t model_type = -1;
        uint32_t mesh_count = -1;

        std::ifstream file(path, std::ios::binary | std::ios::in); // | ios::ate);
        int size = file.tellg();
        file.seekg(0, std::ios::beg);
        //std::vector<char> buffer;
        //buffer.resize(size);
        //file.read(buffer.data(), size);
        file.read(reinterpret_cast<char*>(&file_format_version), sizeof(file_format_version));
        std::cout << "file format version: " << file_format_version << std::endl;
        file.read(reinterpret_cast<char*>(&data_version), sizeof(data_version));
        std::cout << "data version: " << data_version << std::endl;
        file.read(reinterpret_cast<char*>(&model_type), sizeof(model_type));
        std::cout << "model type: " << model_type << std::endl;
        file.read(reinterpret_cast<char*>(&mesh_count), sizeof(mesh_count));
        std::cout << "number of meshes: " << mesh_count << std::endl;

        for (size_t i = 0; i < mesh_count; i++)
        {
            StaticMesh mesh;
            mesh.materialID = i;
            uint32_t index_count = 0;
            file.read(reinterpret_cast<char*>(&index_count), sizeof(index_count));
            for (size_t j = 0; j < index_count; j++)
            {
                uint32_t val = -1;
                file.read(reinterpret_cast<char*>(&val), sizeof(val));
                std::cout << "Index " << j << ": " << val << std::endl;
                mesh.indices.push_back(val);
            }
            uint32_t vertex_count = 0;
            file.read(reinterpret_cast<char*>(&vertex_count), sizeof(vertex_count));
            for (size_t j = 0; j < vertex_count; j++)
            {
                StaticVertex vertex;
                file.read(reinterpret_cast<char*>(&vertex.position.x), sizeof(float));
                file.read(reinterpret_cast<char*>(&vertex.position.y), sizeof(float));
                file.read(reinterpret_cast<char*>(&vertex.position.z), sizeof(float));
                std::cout << "Position " << j << ": " << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << std::endl;
                file.read(reinterpret_cast<char*>(&vertex.normal.x), sizeof(float));
                file.read(reinterpret_cast<char*>(&vertex.normal.y), sizeof(float));
                file.read(reinterpret_cast<char*>(&vertex.normal.z), sizeof(float));
                std::cout << "Normal " << j << ": " << vertex.normal.x << ", " << vertex.normal.y << ", " << vertex.normal.z << std::endl; 
                file.read(reinterpret_cast<char*>(&vertex.texcoord.x), sizeof(float));
                file.read(reinterpret_cast<char*>(&vertex.texcoord.y), sizeof(float));
                std::cout << "TexCoords " << j << ": " << vertex.texcoord.x << ", " << vertex.texcoord.y << std::endl;
                mesh.vertices.push_back(vertex);
            }
            model.meshes.push_back(mesh);
        }
        
        file.close();
    }
} // namespace Nebel
