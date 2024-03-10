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
    Texture tex1;
    Texture sprite_tex1;
    UiImage im;
    UiBox bo;
    Sprite sprite1;
    void Renderer2D::Init()
    {
        std::cout << "2D" << std::endl;
        InitGraphics();
        import_texture(tex1, "../../../../assets/textures/checker.png");
        import_texture(sprite_tex1, "../../../../assets/textures/checker.png");
        
        Transform2D t2 = Transform2D();
        t2.position = {5.0f, 5.0f};
        t2.rotation = 0.0f;
        t2.scale    = {8.0f, 8.0f};

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
    void Renderer2D::Update()
    {
        glm::vec3 rotation_axis = glm::vec3(0.0f, 0.0f, 1.0f);
        vp = Game::camera2d->projection * Game::camera2d->view; 

        ClearColor(0.5f);
        SetBlendingMode(BlendingMode::BlendOpaque);
        for (auto &&rect : Game::ecs->components.rects)
        {
            Transform2D transform = rect.second.entity->transform2D;
            mvp = vp;
            mvp = glm::translate(mvp,{transform.position.x, transform.position.y,0});
            mvp = glm::rotate(mvp, glm::radians(0.0f), rotation_axis);
            mvp = glm::scale(mvp, glm::vec3(transform.scale, 0));

            DrawRect(mvp, rect.second.color);
        }

        SetBlendingMode(BlendingMode::BlendCutOff);

        for (auto &&sprite : Game::ecs->components.sprites)
        {
            mvp = vp;
            Transform2D et1r = Game::ecs->entities[0].transform2D;
            mvp = glm::translate(mvp,{et1r.position.x, et1r.position.y,0});
            mvp = glm::rotate(mvp, glm::radians(0.0f), rotation_axis);
            mvp = glm::scale(mvp, {1,1,1});
            Draw(mvp, sprite.second.sprite);
        }
        
        Game::ui->render();
    }
    void Renderer2D::Resize()
    {
        //GraphicsDevice::SetViewport(Game::platform->width, Game::platform->height);
        SetViewport(Game::platform->width, Game::platform->height);
        //gbuffer.exit();
    }
    void Renderer2D::End()
    {
        EndGraphics();
    }
} // namespace Nebel
