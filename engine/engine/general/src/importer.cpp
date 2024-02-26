#include "importer.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"
#include "glm/glm.hpp"
#include <iostream>

namespace Nebel
{
    struct MeshHelper
    {
        std::vector<char> positions;
        std::vector<char> normals;
        std::vector<char> tex0;
        std::vector<char> tex1;
        std::vector<char> vertex_color;
        std::vector<Nebel::VertexAttribute> attributes;
        std::vector<char> vertex_data;

        uint32_t index_count = 0;
        std::vector<uint32_t> indices;
    };
    static size_t ComponentTypeByteSize(int type) {
        switch (type) {
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
            case TINYGLTF_COMPONENT_TYPE_BYTE:
            return sizeof(char);
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
            case TINYGLTF_COMPONENT_TYPE_SHORT:
            return sizeof(short);
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
            case TINYGLTF_COMPONENT_TYPE_INT:
            return sizeof(int);
            case TINYGLTF_COMPONENT_TYPE_FLOAT:
            return sizeof(float);
            case TINYGLTF_COMPONENT_TYPE_DOUBLE:
            return sizeof(double);
            default:
            return 0;
        }
    }
    static std::string GetFilePathExtension(const std::string &FileName) {
        if (FileName.find_last_of(".") != std::string::npos)
        {
            return FileName.substr(FileName.find_last_of(".") + 1);
        }
        return "";
    }
    void import_texture(Texture &texture, const char* path)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        //texture.data = new unsigned char[width*height*nrChannels];
        //for (size_t i = 0; i < width*height*nrChannels; i++)
        //{
        //    texture.data[i] = data[i];
        //}
        texture.data = data;
        texture.width = width;
        texture.height = height;
        texture.num_channels = nrChannels;
        texture.Texture2D();
        if(data){
            std::cout << "texture data found: " << data[6] <<std::endl;
        }else{
            std::cout << "texture data: none" << std::endl;
        }
        stbi_image_free(data);
    }
    void import_gltf(Model &model, const char* path)
    {
        tinygltf::Model tinygltf_model;
        tinygltf::TinyGLTF loader;
        std::string err;
        std::string warn;
        
        std::string ext = GetFilePathExtension(path);
        bool ret;
        if(ext.compare("gltf") == 0){
            ret = loader.LoadASCIIFromFile(&tinygltf_model, &err, &warn, path);
        }else{
            ret = loader.LoadBinaryFromFile(&tinygltf_model, &err, &warn, path); // for binary glTF(.glb)
        }
        if(!warn.empty()) {
            std::cout << "Warn: " << warn.c_str() << std::endl;
        }
        if (!err.empty()) {
            std::cout << "Err: " << err.c_str() << std::endl;
        }
        if (!ret) {
            std::cout << "Failed to parse glTF" << std::endl;
            return;
        }
        for (size_t meshes_i = 0; meshes_i < tinygltf_model.meshes.size(); meshes_i++)
        {
            tinygltf::Mesh tiny_mesh = tinygltf_model.meshes[meshes_i];
            Nebel::Mesh mesh;
            MeshHelper meshHelper;
            for (size_t prim_i = 0; prim_i < tiny_mesh.primitives.size(); prim_i++)
            {
                tinygltf::Primitive primitive = tiny_mesh.primitives[prim_i];
                tinygltf::Accessor tiny_index_accessor = tinygltf_model.accessors[primitive.indices];
                tinygltf::BufferView tiny_index_bufferview = tinygltf_model.bufferViews[tiny_index_accessor.bufferView];
                tinygltf::Buffer tiny_index_buffer = tinygltf_model.buffers[tiny_index_bufferview.buffer];
                if(tiny_index_accessor.componentType==TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
                {
                    const uint8_t* indices_data = reinterpret_cast<const uint8_t*>(&tiny_index_buffer.data[tiny_index_bufferview.byteOffset + tiny_index_accessor.byteOffset]);
                    for (size_t ib_i = 0; ib_i < tiny_index_accessor.count; ib_i++)
                    {
                        meshHelper.indices.push_back(indices_data[ib_i]);
                    }
                } else if(tiny_index_accessor.componentType==TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
                {
                    const uint16_t* indices_data = reinterpret_cast<const uint16_t*>(&tiny_index_buffer.data[tiny_index_bufferview.byteOffset + tiny_index_accessor.byteOffset]);
                    for (size_t ib_i = 0; ib_i < tiny_index_accessor.count; ib_i++)
                    {
                        //uint32_t uint32_v = indices_data[ib_i]; // TODO?????
                        meshHelper.indices.push_back(indices_data[ib_i]); //uint32_v);
                    }
                } else if(tiny_index_accessor.componentType==TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
                {
                    const uint32_t* indices_data = reinterpret_cast<const uint32_t*>(&tiny_index_buffer.data[tiny_index_bufferview.byteOffset + tiny_index_accessor.byteOffset]);
                    for (size_t ib_i = 0; ib_i < tiny_index_accessor.count; ib_i++)
                    {
                        meshHelper.indices.push_back(indices_data[ib_i]);
                    }
                }else{
                    std::cout << "indices of unhandled type" << std::endl;
                }
                mesh.materialID = primitive.material;
                for (auto acc_indes : primitive.attributes)
                {
                    tinygltf::Accessor accessor = tinygltf_model.accessors[acc_indes.second];
                    tinygltf::BufferView bufferview = tinygltf_model.bufferViews[accessor.bufferView];
                    tinygltf::Buffer buffer = tinygltf_model.buffers[bufferview.buffer];
                    VertexAttribute attribute;
                    if(acc_indes.first == "POSITION")
                    {
                        attribute.name = "Position";
                        attribute.offset = 0;
                        attribute.stride = sizeof(glm::vec3);
                        attribute.num_components = 3;
                        attribute.isNormalized = false;
                        const char* buf = new char[accessor.count]();
                        buf = reinterpret_cast<const char*>(&buffer.data[bufferview.byteOffset + accessor.byteOffset]);
                        for (size_t push_i = 0; push_i < accessor.count; push_i++)
                        {
                            meshHelper.positions.push_back(buf[push_i]);
                        }
                        meshHelper.attributes.push_back(attribute);
                        //std::cout << bufferview.byteStride << std::endl;
                        //std::cout << accessor.ByteStride(bufferview) << std::endl;
                        //std::cout << accessor.type << std::endl;
                        //std::cout << accessor.count << std::endl;
                    }
                    if(acc_indes.first == "Normal")
                    {
                        attribute.name = "Normal";
                        attribute.offset = 0;
                        attribute.stride = sizeof(glm::vec3);
                        attribute.num_components = 3;
                        attribute.isNormalized = false;
                    }
                    if(acc_indes.first == "TEXCOORD_0")
                    {
                        attribute.name = "Tex0";
                        attribute.offset = 0;
                        attribute.stride = sizeof(glm::vec2);
                        attribute.num_components = 2;
                        attribute.isNormalized = false;
                    }
                }
            }
            mesh.create(meshHelper.positions.data(), meshHelper.indices.data(), 24, 36);
            model.meshes.push_back(mesh);
        }
    }
} // namespace Nebel
