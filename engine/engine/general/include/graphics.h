#pragma once

#include "mesh.h"
#include "sprite.h"
#include "texture.h"
#include "transform.h"
#include "glm/glm.hpp"

namespace Nebel
{
    enum class BlendingMode
    {
        BlendOpaque,
        BlendCutOff,
    };
    void InitGraphics();
    void SetViewport(uint32_t width, uint32_t height);
    void SetBlendingMode(BlendingMode mode);
    void ClearColor(float color);
    void Draw(Mesh &mesh);
    void Draw(glm::mat4 &matrix, Sprite* sprite);
    void DrawRect(Transform2D &transform, glm::vec4 &color);
    void DrawRect(Transform2D &transform, glm::vec4 &color, glm::mat4 &proj);
    void DrawRect(glm::mat4 &matrix, glm::vec4 &color);
    void DrawImage(Transform2D &transform, glm::vec4 &color, Texture &image);
    void DrawImage(Transform2D &transform, glm::vec4 &color, Texture &image, glm::mat4 &proj);
    void DrawImage(glm::mat4 &matrix, glm::vec4 &color, Texture &image);
    void EndGraphics();
} // namespace Nebel
