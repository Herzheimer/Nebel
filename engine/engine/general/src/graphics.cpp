#include "graphics.h"
#include "shader.h"
#include "glad/glad.h"

namespace Nebel
{
    Shader RectShader;
    Shader ImageShader;
    Shader SpriteShader;
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    void SetViewport(uint32_t width, uint32_t height)
    {
        glViewport(0,0, width, height);
    }
    void ClearColor(float color)
    {
        glClearColor(color, color, color, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void SetBlendingMode(BlendingMode mode)
    {
        switch (mode)
        {
        case BlendingMode::BlendOpaque:
            glDisable(GL_BLEND);  
            break;
        case BlendingMode::BlendCutOff:
            glEnable(GL_BLEND);
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
            break;
        default:
            break;
        }
    }
    void InitGraphics()
    {
        load(RectShader, "../../../../assets/shader/rect.vert", "../../../../assets/shader/rect.frag");
        load(ImageShader, "../../../../assets/shader/image.vert", "../../../../assets/shader/image.frag");
        load(SpriteShader, "../../../../assets/shader/sprite.vert", "../../../../assets/shader/sprite.frag");
    }
    void Draw(Mesh &mesh)
    {
        //
    }
    void Draw(glm::mat4 &matrix, Sprite &sprite)
    {
        float vertices[] = {
            -sprite.dimensions.x, -sprite.dimensions.y, 0.0f, // left  
             sprite.dimensions.x, -sprite.dimensions.y, 0.0f, // right 
             sprite.dimensions.x,  sprite.dimensions.y, 0.0f, // top
            -sprite.dimensions.x,  sprite.dimensions.y, 0.0f, // top-left
            -sprite.dimensions.x, -sprite.dimensions.y, 0.0f, // bottom-left
             sprite.dimensions.x,  sprite.dimensions.y, 0.0f, // top-right
            0.0f, 0.0f,                                                                                // left  
            1.0f, 0.0f,                                                                                // right 
            1.0f, 1.0f,                                                                                // top
            0.0f, 1.0f,                                                                                // top-left
            0.0f, 0.0f,                                                                                // bottom-left
            1.0f, 1.0f                                                                                 // top-right
        };
        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)(18*sizeof(float)));
        glEnableVertexAttribArray(1);

        SpriteShader.use();
        SpriteShader.setMat4("mvp", matrix);
        SpriteShader.setVec2("row_column_indices", sprite.row_column_indices);
        SpriteShader.setVec2("row_column_count", sprite.row_column_count);
        sprite.tex->use(0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 

        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void DrawRect(Transform2D &transform, glm::vec4 &color)
    {
        float vertices[] = {
            -transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // left  
             transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // right 
             transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f,  // top
            -transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f,  // top-left
            -transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f,  // bottom-left
             transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f   // top-right
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        RectShader.use();
        RectShader.setVec4("Color", color);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 

        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        //
    }
    void DrawImage(Transform2D &transform, glm::vec4 &color, Texture &image) // TODO
    {
        float vertices[] = {
            -transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // left  
             transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // right 
             transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f, // top
            -transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f, // top-left
            -transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // bottom-left
             transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f, // top-right
            0.0f, 0.0f,                                                                                // left  
            1.0f, 0.0f,                                                                                // right 
            1.0f, 1.0f,                                                                                // top
            0.0f, 1.0f,                                                                                // top-left
            0.0f, 0.0f,                                                                                // bottom-left
            1.0f, 1.0f                                                                                 // top-right
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)(18*sizeof(float)));
        glEnableVertexAttribArray(1);

        image.use(0);
        ImageShader.use();
        ImageShader.setVec4("Color", color);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 

        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void DrawRect(Transform2D &transform, glm::vec4 &color, glm::mat4 &proj)
    {
        float vertices[] = {
            -transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // left  
             transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // right 
             transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f,  // top
            -transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f,  // top-left
            -transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f,  // bottom-left
             transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f   // top-right
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        RectShader.use();
        RectShader.setVec4("Color", color);
        RectShader.setMat4("mvp", proj);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 

        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void DrawImage(Transform2D &transform, glm::vec4 &color, Texture &image, glm::mat4 &proj)
    {
        float vertices[] = {
            -transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // left  
             transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // right 
             transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f, // top
            -transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f, // top-left
            -transform.scale.x+transform.position.x, -transform.scale.y+(-transform.position.y), 0.0f, // bottom-left
             transform.scale.x+transform.position.x,  transform.scale.y+(-transform.position.y), 0.0f, // top-right
            0.0f, 0.0f,                                                                                // left  
            1.0f, 0.0f,                                                                                // right 
            1.0f, 1.0f,                                                                                // top
            0.0f, 1.0f,                                                                                // top-left
            0.0f, 0.0f,                                                                                // bottom-left
            1.0f, 1.0f                                                                                 // top-right
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)(18*sizeof(float)));
        glEnableVertexAttribArray(1);

        image.use(0);
        ImageShader.use();
        ImageShader.setVec4("Color", color);
        ImageShader.setMat4("mvp", proj);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 

        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void DrawRect(glm::mat4 &matrix, glm::vec4 &color)
    {
        float vertices[] = {
            -1, -1, 0.0f, // left  
             1, -1, 0.0f, // right 
             1,  1, 0.0f,  // top
            -1,  1, 0.0f,  // top-left
            -1, -1, 0.0f,  // bottom-left
             1,  1, 0.0f   // top-right
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        RectShader.use();
        RectShader.setVec4("Color", color);
        RectShader.setMat4("mvp", matrix);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 

        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void DrawImage(glm::mat4 &matrix, glm::vec4 &color, Texture &image)
    {
        float vertices[] = {
            -1.0f, -1.0f, 0.0f, // left  
             1.0f, -1.0f, 0.0f, // right 
             1.0f,  1.0f, 0.0f, // top
            -1.0f,  1.0f, 0.0f, // top-left
            -1.0f, -1.0f, 0.0f, // bottom-left
             1.0f,  1.0f, 0.0f, // top-right
            0.0f, 0.0f,                                                                                // left  
            1.0f, 0.0f,                                                                                // right 
            1.0f, 1.0f,                                                                                // top
            0.0f, 1.0f,                                                                                // top-left
            0.0f, 0.0f,                                                                                // bottom-left
            1.0f, 1.0f                                                                                 // top-right
        };

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)(18*sizeof(float)));
        glEnableVertexAttribArray(1);

        image.use(0);
        ImageShader.use();
        ImageShader.setVec4("Color", color);
        ImageShader.setMat4("mvp", matrix);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 

        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void EndGraphics()
    {
        //
    }
} // namespace Nebel
