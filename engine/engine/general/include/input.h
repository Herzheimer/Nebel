#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include "controller.h"

namespace Nebel
{
    enum MouseButton
    {
        LMB,
        MMB,
        RMB,
    };
    enum Key
    {
        W,
        A,
        S,
        D,
        E,
        F,
        Q,
        Up,
        Down,
        Left,
        Right,
        Shift,
        LShift,
        RShift,
        Esc,
        Space,
    };
    struct Input
    {
        inline static bool has_mouse; // todo
        inline static glm::vec2 MousePosition; //in window pixel
        inline static glm::vec2 last_MousePosition; //in window pixel
        inline static glm::ivec2 MousePositionI; //in window pixel
        inline static glm::vec2 MouseDelta; // window -1 to 1
        inline static float MouseWheelDelta; // todo
        inline static std::map<MouseButton, bool> mouse_buttons_down;
        inline static std::map<MouseButton, bool> mouse_buttons_last_down;
        inline static std::map<Key, bool> keys_down;
        inline static std::map<Key, bool> keys_last_down;
        inline static bool has_controller = false;
        inline static std::vector<Controller> controller;
        static void Init();
        static void Terminate();
        static bool isMouseButtonUp(MouseButton mouseButton);
        static bool isMouseButtonDown(MouseButton mouseButton);
        static bool isMouseButtonPressed(MouseButton mouseButton);
        static bool isMouseButtonReleased(MouseButton mouseButton);
        static void ResetKeys();
        static bool isKeyUp(Key key);
        static bool isKeyDown(Key key);
        static bool isKeyPressed(Key key);
        static bool isKeyReleased(Key key);
    };
} // namespace Nebel