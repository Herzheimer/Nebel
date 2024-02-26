#include"renderer.h"

#include "graphics.h"
#include "texture.h"
#include "importer.h"
#include "ui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "game.h"
#include "model.h"
#include "shader.h"
#include "loader.h"
#include <iostream>

namespace Nebel
{
    Texture tex1;
    Texture sprite_tex1;
    UiImage im;
    UiBox bo;
    Sprite sprite1;
    void Renderer::Init()
    {
        InitGraphics();
        import_texture(tex1, "../../../../assets/textures/checker.png");
        import_texture(sprite_tex1, "../../../../assets/textures/checker.png");
        Transform2D t2 = {
            {5.0f, 5.0f},
            0.0f,
            {8.0f, 8.0f}
        };
        im = UiImage();
        im.tex1 = tex1;
        bo = UiBox();
        Game::ui->nodes.push_back(UiNode());
        Game::ui->nodes[0].transform = t2;
        Game::ui->nodes[0].element = &im;// = &bo;
        Game::ui->nodes[0].type = UiType::UiImage;// = UiType::UiBox;

        SpriteAnimation spriteanim1 = {
            {4, 1},
            {0, 0},
            {4, 1},
            {0, 0},
            {50, 32},
            24.0f
        };
        sprite1.tex=&sprite_tex1;
        sprite1.row_column_count=glm::vec2(10, 1);
        sprite1.row_column_indices=glm::vec2(0, 0);
        sprite1.dimensions = {50, 32};
        sprite1.animations.push_back(spriteanim1);
        sprite1.currentanimation=0;
        
        Game::resources->sprites[0]=sprite1;
    }
    glm::mat4 modelmat = glm::mat4(1);
    glm::vec2 sprite1pos = glm::vec2(0);
    void Renderer::Update()
    {
        ClearColor(0.5f);
        SetBlendingMode(BlendingMode::BlendOpaque);
        Game::camera->update(0.03f);
        glm::mat4 vp = Game::camera->projection * Game::camera->view;
        glm::translate(modelmat, {3,0,0});
        glm::mat4 mvp = vp*modelmat;
        //model.draw();

        SetBlendingMode(BlendingMode::BlendCutOff);
        glm::mat4 matrix = glm::mat4(1);
        matrix = Game::camera2d->projection;
        matrix = glm::translate(matrix,{sprite1pos,0});//glm::vec3(transform.position, 0.0f));
        //matrix = glm::rotate(matrix, glm::radians(0), glm::vec3(0.f, 0.f, 1.f));
        matrix = glm::scale(matrix, {1,1,1}); // glm::vec3(transform.scale, 1.0f));
        for (auto &&sprite : Game::resources->sprites)
        {
            Draw(matrix, sprite.second);
        }
        
        //sprite1pos.x+=1;
        Game::ui->render();
    }
    void Renderer::Resize()
    {
        //GraphicsDevice::SetViewport(Game::platform->width, Game::platform->height);
        SetViewport(Game::platform->width, Game::platform->height);
        //gbuffer.exit();
    }
    Renderer::~Renderer()
    {
        EndGraphics();
    }
} // namespace Nebel
