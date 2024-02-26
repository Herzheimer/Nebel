#include"renderer.h"
#include "graphics.h"
#include "texture.h"
#include "importer.h"
#include "ui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "game.h"
#include "shader.h"
#include "loader.h"
#include <iostream>

namespace Nebel
{
    void Renderer2D::Init()
    {
        InitGraphics();
        std::cout << "2D" << std::endl;
    }
    void Renderer2D::Update()
    {
        ClearColor(0.5f);
        Game::ui->render();
    }
    void Renderer2D::Resize()
    {
        //GraphicsDevice::SetViewport(Game::platform->width, Game::platform->height);
        SetViewport(Game::platform->width, Game::platform->height);
        //gbuffer.exit();
    }
    Renderer2D::~Renderer2D()
    {
        EndGraphics();
    }
} // namespace Nebel
