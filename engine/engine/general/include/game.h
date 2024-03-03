#pragma once

#include <map>
#include <memory>
#include "camera.h"
#include "components.h"
#include "ecs.h"
#include "interfaces.h"
#include "platform.h"
#include "renderer.h"
#include "scheduler.h"
//#include "script.h"
#include "sprite.h"
#include "ui.h"
#include "audio.h"
#include "resources.h"
#include "scripting_system.h"

namespace Nebel
{
    struct Game
    {
        inline static bool running = false;
        inline static AudioEngine* audio;
        inline static Camera* camera; // TODO: Where to put the camera
        inline static Camera2D* camera2d;
        inline static Networking* networking = nullptr;
        inline static Platform* platform;
        inline static PhysicsWorld* physics = nullptr;
        inline static Renderer* renderer;
        inline static Resources* resources;
        inline static Scheduler* scheduler;
        inline static ScriptingSystem* scripting_system;
        inline static ECS* ecs = nullptr;
        inline static UiSystem* ui;

        static void Load(const char* path);
        static void Start();
        static void Over();
    };
}