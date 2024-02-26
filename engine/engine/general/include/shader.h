#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace Nebel
{
    enum ShaderType
    {
        VertexShader,
        GeometryShader,
        FragmentShader,
        ComputeShader,
    };
    struct ShaderDesc
    {
        std::vector<ShaderType> types;
        //std::vector<const char*> srcs;
        std::vector<const char*> paths;
    };
    class Shader
    {
        private:
        public:
        uint32_t id;
        void use();
        void terminate();
        void setBool(const char* &name, bool value) const;
        void setFloat(const char* name, float value);
        void setInt(const char* name, int value);
        void setVec2(const char* name, glm::vec2 &value);
        void setVec3(const char* name, glm::vec3 &value);
        void setVec4(const char* name, glm::vec4 &value);
        void setMat4(const char* name, glm::mat4 &var);
        //void setRGB(const char* name, RGB &color);
        //void setRGBA(const char* name, RGBA &color);
        void unload();
    };

    // TODO: cleanup
    void load(Shader &shader, const char* vs_path, const char* fs_path);
    void load(Shader &shader, ShaderDesc desc);
    void loadSrc(Shader &shader, const char* vs_path, const char* fs_path);
}