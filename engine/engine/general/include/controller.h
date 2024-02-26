#pragma once

#include <SDL.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>

namespace Nebel
{
    enum ControllerType
    {
        UNDEFINED_CONTROLLER,
        UNKNOWN_CONTROLLER,
        SWITCH_CONTROLLER,
        //SWITCH_DUO_JOYCON,
        //SWITCH_LEFT_JOYCON,
        //SWITCH_RIGHT_JOYCON,
        XBOX_360_CONTROLLER,
        XBOX_ONE_CONTROLLER,
        PS3_CONTROLLER,
        PS4_CONTROLLER,
        PS5_CONTROLLER,
    };
    enum ControllerButton
    {
        CONTROLLER_A,
        CONTROLLER_B,
        CONTROLLER_X,
        CONTROLLER_Y,
        CONTROLLER_Square,
        CONTROLLER_Circle,
        CONTROLLER_Triangle,
        CONTROLLER_Cross,
        CONTROLLER_START,
        CONTROLLER_BACK,
        CONTROLLER_MINUS,
        CONTROLLER_PLUS,
        CONTROLLER_XBOX,
        CONTROLLER_RB,
        CONTROLLER_LB,
        CONTROLLER_R,
        CONTROLLER_L,
        CONTROLLER_ZR,
        CONTROLLER_ZL,
        CONTROLLER_RIGHT_JOYSTICK,
        CONTROLLER_LEFT_JOYSTICK,
        CONTROLLER_HOME,
        CONTROLLER_CIRCLE_IN_SQUARE,
        // CONTROLLER_TURBO // WO?
        // CONTROLLER_LT, // WO?
        // CONTROLLER_RT, // WO?
    };
    struct Controller
    {
        SDL_Joystick* gGameController = NULL;
        ControllerType type = UNDEFINED_CONTROLLER;
        std::map<ControllerButton, bool> buttons_down;
        std::map<ControllerButton, bool> buttons_last_down;
        glm::vec2 left_thumb = glm::vec2(0, 0);
        glm::vec2 right_thumb = glm::vec2(0, 0);
        bool isUp(ControllerButton button);
        bool isDown(ControllerButton button);
        bool isPressed(ControllerButton button);
        bool isReleased(ControllerButton button);
        void resetButtons();
    };
} // namespace Nebel
