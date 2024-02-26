#include "controller.h"
#include <iostream>

namespace Nebel
{
    bool Controller::isUp(ControllerButton button)
    {
        return !buttons_down[button];
    }
    bool Controller::isDown(ControllerButton button)
    {
        return buttons_down[button];
    }
    bool Controller::isPressed(ControllerButton button)
    {
        return (buttons_down[button] && !buttons_last_down[button]);
    }
    bool Controller::isReleased(ControllerButton button)
    {
        return (!buttons_down[button] && buttons_last_down[button]);
    }
    void Controller::resetButtons()
    {
        switch (type)
        {
        case SWITCH_CONTROLLER:
            buttons_down[CONTROLLER_A] = false;
            buttons_down[CONTROLLER_B] = false;
            buttons_down[CONTROLLER_X] = false;
            buttons_down[CONTROLLER_Y] = false;
            buttons_down[CONTROLLER_L] = false;
            buttons_down[CONTROLLER_R] = false;
            buttons_down[CONTROLLER_ZL] = false;
            buttons_down[CONTROLLER_ZR] = false;
            buttons_down[CONTROLLER_MINUS] = false;
            buttons_down[CONTROLLER_PLUS] = false;
            buttons_down[CONTROLLER_LEFT_JOYSTICK] = false;
            buttons_down[CONTROLLER_RIGHT_JOYSTICK] = false;
            buttons_down[CONTROLLER_HOME] = false;
            buttons_down[CONTROLLER_CIRCLE_IN_SQUARE] = false;
            //buttons_down[CONTROLLER_TURBO] = false;
            buttons_last_down[CONTROLLER_A] = false;
            buttons_last_down[CONTROLLER_B] = false;
            buttons_last_down[CONTROLLER_X] = false;
            buttons_last_down[CONTROLLER_Y] = false;
            buttons_last_down[CONTROLLER_L] = false;
            buttons_last_down[CONTROLLER_R] = false;
            buttons_last_down[CONTROLLER_ZL] = false;
            buttons_last_down[CONTROLLER_ZR] = false;
            buttons_last_down[CONTROLLER_MINUS] = false;
            buttons_last_down[CONTROLLER_PLUS] = false;
            buttons_last_down[CONTROLLER_LEFT_JOYSTICK] = false;
            buttons_last_down[CONTROLLER_RIGHT_JOYSTICK] = false;
            buttons_last_down[CONTROLLER_HOME] = false;
            buttons_last_down[CONTROLLER_CIRCLE_IN_SQUARE] = false;
            //buttons_last_down[CONTROLLER_TURBO] = false;
            break;
        case XBOX_360_CONTROLLER:
            if (SDL_JoystickGetButton(gGameController, 0)) {
                std::cerr << "no idea what button 0 is. (switch: Y, xbox360: A)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 1)) {
                std::cerr << "no idea what button 1 is. (switch: B, xbox360: B)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 2)) {
                std::cerr << "no idea what button 2 is. (switch: A, xbox360: X)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 3)) {
                std::cerr << "no idea what button 3 is. (switch: X, xbox360: Y)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 4)) {
                std::cerr << "no idea what button 4 is(switch: L, xbox360: LB)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 5)) {
                std::cerr << "no idea what button 5 is(switch: R, xbox360: RB)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 6)) {
                std::cerr << "no idea what button 6 is(switch: ZL, xbox360: BACK)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 7)) {
                std::cerr << "no idea what button 7 is(switch: ZR, xbox360: START)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 8)) {
                std::cerr << "no idea what button 8 is(switch: -, xbox360: xbox-btn)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 9)) {
                std::cerr << "no idea what button 9 is(switch: +, xbox360: LeftJoyButton)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 10)) {
                std::cerr << "no idea what button 10 is(switch: LeftJoyButton, xbox360: RightJoyButton)" << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 11)) {
                std::cerr << "no idea what button 11 is(switch: RightJoyButton, xbox360: " << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 12)) {
                std::cerr << "no idea what button 12 is(switch: Home, xbox360: " << std::endl;
            }
            if (SDL_JoystickGetButton(gGameController, 13)) {
                std::cerr << "no idea what button 13 is(switch: SquaredCircle, xbox360: " << std::endl;
            }
            break;
        
        default:
            std::cerr << "buttons not set!" << std::endl;
            break;
        }
    }
} // namespace Nebel
