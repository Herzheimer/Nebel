#include"renderer.h"
#include "graphics.h"
#include "texture.h"
#include "importer.h"
#include "ui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "game.h"
#include "model.h"
#include "shader.h"
#include <iostream>
#include "glad/glad.h"
#include "loader.h"

namespace Nebel
{
    void Renderer3D::Init()
    {
        InitGraphics();
    }
    void Renderer3D::Update()
    {
        ClearColor(0.5f);
        Game::camera->update(0.03f);
        glm::mat4 vp = Game::camera->projection * Game::camera->view;
        //glm::translate(modelmat, {3,0,0});
        //glm::mat4 mvp = vp*modelmat;
    }
    void Renderer3D::Resize()
    {
        //GraphicsDevice::SetViewport(Game::platform->width, Game::platform->height);
        SetViewport(Game::platform->width, Game::platform->height);
        //gbuffer.exit();
    }
    Renderer3D::~Renderer3D()
    {
        EndGraphics();
    }
} // namespace Nebel
