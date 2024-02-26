#include "shader.h"

#include <glad/glad.h>
#include <fstream>
#include <string>
#include <sstream>

//#include <iostream>
// TODO: cleanup

namespace Nebel
{
    void Shader::use()
    {
        glUseProgram(id);
    }
    void Shader::terminate()
    {
        glDeleteProgram(id);
    }
    void Shader::setBool(const char* &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(id, name), (int)value); 
    }
    void Shader::setFloat(const char* name, float value)
    { 
        glUniform1f(glGetUniformLocation(id, name), value); 
    }
    void Shader::setInt(const char* name, int value)
    { 
        glUniform1i(glGetUniformLocation(id, name), value); 
    }
    void Shader::setVec2(const char* name, glm::vec2 &value)
    {
        glUniform2fv(glGetUniformLocation(id, name), 1, &value[0]);
    }
    void Shader::setVec3(const char* name, glm::vec3 &value)
    { 
        glUniform3fv(glGetUniformLocation(id, name), 1, &value[0]);
    }
    void Shader::setVec4(const char* name, glm::vec4 &value)
    {
        glUniform4fv(glGetUniformLocation(id, name), 1, &value[0]);
    }
    void Shader::setMat4(const char* loc, glm::mat4 &var) {
        int modelLoc = glGetUniformLocation(id, loc);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(var));
    }
    void Shader::unload()
    { 
        glDeleteProgram(id); 
    }
    void load(Shader &shader, const char* vs_path, const char* fs_path)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            vShaderFile.open(vs_path);
            fShaderFile.open(fs_path);
            std::stringstream vShaderStream, fShaderStream;
            
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();		

            vShaderFile.close();
            fShaderFile.close();
            
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();			
        }
        catch (std::ifstream::failure& e)
        {
            //std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();

        uint32_t vs, fs;
        
        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vShaderCode, NULL);
        glCompileShader(vs);
        
        fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fShaderCode, NULL);
        glCompileShader(fs);
        
        shader.id = glCreateProgram();
        glAttachShader(shader.id, vs);
        glAttachShader(shader.id, fs);
        glLinkProgram(shader.id);
        
        glDeleteShader(vs);
        glDeleteShader(fs);
    }
    void load(Shader &shader, ShaderDesc desc)
    {
        std::vector<uint32_t> ids;
        for (size_t i = 0; i < desc.types.size(); i++)
        {
            ids.push_back(0);
            std::string code;
            std::ifstream shaderFile;
            
            shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            try 
            {
                shaderFile.open(desc.paths[i]);
                std::stringstream shaderStream;
                
                shaderStream << shaderFile.rdbuf();
                
                shaderFile.close();
                
                code = shaderStream.str();		
            }
            catch (std::ifstream::failure& e)
            {
                //std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            }
            const char* shaderCode = code.c_str();
            uint32_t shader_id;
            switch (desc.types[i])
            {
            case VertexShader:
                shader_id = glCreateShader(GL_VERTEX_SHADER);
                break;
            case GeometryShader:
                shader_id = glCreateShader(GL_GEOMETRY_SHADER);
                break;
            case FragmentShader:
                shader_id = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            case ComputeShader:
                shader_id = glCreateShader(GL_COMPUTE_SHADER);
                break;
            }
            glShaderSource(shader_id, 1, &shaderCode, NULL);
            glCompileShader(shader_id);
            ids[i] = shader_id;;
        }
        shader.id = glCreateProgram();
        for (size_t i = 0; i < ids.size(); i++)
        {
            glAttachShader(shader.id, ids[i]);
        }
        glLinkProgram(shader.id);
        for (size_t i = 0; i < ids.size(); i++)
        {
            glDeleteShader(ids[i]);
        }
    }
    void loadSrc(Shader &shader, const char* vs_path, const char* fs_path)
    {
        std::ifstream file;
        uint32_t vs, fs;
        
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vs_path, NULL);
        glCompileShader(vertexShader);
        
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fs_path, NULL);
        glCompileShader(fragmentShader);
        
        shader.id = glCreateProgram();
        glAttachShader(shader.id, vertexShader);
        glAttachShader(shader.id, fragmentShader);
        glLinkProgram(shader.id);
        
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}