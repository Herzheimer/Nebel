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
        vp = Game::camera->projection * Game::camera->view;
        glm::mat4 mvp = vp;
        for (auto &&model : Game::ecs->components.static_models)
        {
            mvp = vp;
            Transform trans = Game::ecs->entities[model.first].transform;
            mvp = glm::translate(mvp, trans.position);
            //mvp = glm::rotate(mvp, trans.rotation);
            mvp = glm::scale(mvp, trans.scale);
            model.second.model->draw();
        }
        for (auto &&model : Game::ecs->components.models)
        {
            mvp = vp;
            Transform trans = Game::ecs->entities[model.first].transform;
            mvp = glm::translate(mvp, trans.position);
            //mvp = glm::rotate(mvp, trans.rotation);
            mvp = glm::scale(mvp, trans.scale);
            model.second.model->draw();
        }
        //for (auto &&sprite : Game::ecs->components.sprites)
        //{
        //    mvp = vp;
        //    Transform trans = Game::ecs->entities[sprite.first].transform;
        //    mvp = glm::translate(mvp, trans.position);
        //    //mvp = glm::rotate(mvp, trans.rotation);
        //    mvp = glm::scale(mvp, trans.scale);
        //    Draw(mvp, sprite.second.sprite);
        //}
        Game::ui->render();
    }
    void Renderer3D::Resize()
    {
        SetViewport(Game::platform->width, Game::platform->height);
        //gbuffer.exit();
    }
    void Renderer3D::End()
    {
        EndGraphics();
    }
} // namespace Nebel
