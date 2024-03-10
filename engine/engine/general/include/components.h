#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include "sprite.h"
#include "transform.h"
#include "rng.h"
#include "resources.h"
#include "physics2d.h"

namespace Nebel
{
    struct Entity;
    enum class ComponentType
    {
        Sprite_Component,
        Transform2D_Component,
        Custom_Component,
    };
    struct IComponent
    {
        //const char* struct_name;
        //uint16_t type_id;
        Entity* entity;
        virtual void Serialize(){};
    };
    struct RectComponent : IComponent
    {
        glm::vec4 color = {0.2, 0.2, 0.2, 1.0};
    };
    struct ModelComponent : IComponent
    {
        uint64_t res_id;
        Model* model;
    };
    struct StaticModelComponent : IComponent
    {
        uint64_t res_id;
        StaticModel* model;
    };
    struct SpriteComponent : IComponent
    {
        uint64_t id;
        Sprite* sprite;
    };
    struct Transform2DComponent : IComponent
    {
        uint64_t id;
        Transform2D* transform;
    };
    struct PhysicsComponent2D : IComponent
    {
        PhysicObject2D* object;
    };
    struct ComponentContainer
    {
        std::map<uint64_t, IComponent*> components;
        uint16_t component_type;
    };
    struct Components
    {
        std::map<uint64_t, StaticModelComponent> static_models;
        std::map<uint64_t, ModelComponent> models;
        std::map<uint64_t, SpriteComponent> sprites;
        std::map<uint64_t, RectComponent> rects;
        std::map<uint64_t, Transform2DComponent> transform2d;
        std::map<uint64_t, PhysicsComponent2D> physics_components;
        std::map<uint16_t, ComponentContainer> custom_components;
        std::map<uint16_t, const char*> id_string_mapping;
        //uint16_t Register(const char* name)
        //{
        //    uint16_t counter = id_string_mapping.size();
        //    id_string_mapping[counter] = name;
        //    return counter;
        //}
    };
    // TODO
    //#define RegisterComponent(X) uint16_t X##_id = Game::ecs->components.Register(#X)
}
