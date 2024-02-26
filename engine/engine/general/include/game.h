#pragma once

#include <map>
#include <memory>
#include "camera.h"
#include "components.h"
#include "ecs.h"
#include "platform.h"
#include "renderer.h"
#include "scheduler.h"
#include "sprite.h"
#include "ui.h"
#include "audio.h"
#include "resources.h"

namespace Nebel
{
    struct Game
    {
        inline static bool running;
        //inline static float delta_time;
        inline static AudioEngine* audio;
        inline static Camera* camera;
        inline static Camera2D* camera2d;
        inline static Components* components;
        inline static Platform* platform;
        inline static Renderer* renderer;
        inline static Resources* resources;
        inline static Scheduler* scheduler;
        inline static UiSystem* ui;
        inline static std::map<uint64_t, Entity> entities;
        inline static std::map<const char*, Scene> scenes;

        static void Load(const char* path);
        static void Start();
        static void Over();
    };
}