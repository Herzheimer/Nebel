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
        for (size_t iNode = 0; iNode < tinygltf_model.nodes.size(); iNode++)
        {
            tinygltf::Node tiny_node = tinygltf_model.nodes[iNode];
            tinygltf::Mesh tinymesh= tinygltf_model.meshes[tiny_node.mesh];
            tinygltf::Skin tinyskin = tinygltf_model.skins[tiny_node.skin];
            
            Nebel::Mesh mesh();

            for (size_t iPrimitive = 0; iPrimitive < tinymesh.primitives.size(); iPrimitive++)
            {
                tinygltf::Primitive tiny_primitive = tinymesh.primitives[0]; // Todo
                tiny_primitive.indices;
                tiny_primitive.attributes;
                tiny_primitive.material;
            }
        }
        
    }
} // namespace Nebel
