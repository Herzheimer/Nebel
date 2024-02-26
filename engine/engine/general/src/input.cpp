#include "input.h"

namespace Nebel
{
    void Input::Init()
    {
        has_mouse = false;
        MousePosition = {0,0};
        last_MousePosition = {0,0};
        MousePositionI = {0,0};
        MouseDelta = {0,0};
        MouseWheelDelta = 0;
        ResetKeys();
    }
    void Input::Terminate()
    {
        //
    }
    bool Input::isMouseButtonUp(MouseButton mouseButton)
    {
        return !mouse_buttons_down[mouseButton];
    }
    bool Input::isMouseButtonDown(MouseButton mouseButton)
    {
        return mouse_buttons_down[mouseButton];
    }
    bool Input::isMouseButtonPressed(MouseButton mouseButton)
    {
        return (mouse_buttons_down[mouseButton] && !mouse_buttons_last_down[mouseButton]);
    }
    bool Input::isMouseButtonReleased(MouseButton mouseButton)
    {
        return (!mouse_buttons_down[mouseButton] && mouse_buttons_last_down[mouseButton]);
    }
    void Input::ResetKeys()
    {
        Input::keys_down[W] = false;
        Input::keys_down[A] = false;
        Input::keys_down[S] = false;
        Input::keys_down[D] = false;
        Input::keys_down[E] = false;
        Input::keys_down[F] = false;
        Input::keys_down[Q] = false;
        Input::keys_down[Left] = false;
        Input::keys_down[Right] = false;
        Input::keys_down[Up] = false;
        Input::keys_down[Down] = false;
        Input::keys_down[LShift] = false;
        Input::keys_down[Esc] = false;
        Input::keys_down[Space] = false;
        Input::keys_last_down[W] = false;
        Input::keys_last_down[A] = false;
        Input::keys_last_down[S] = false;
        Input::keys_last_down[D] = false;
        Input::keys_last_down[E] = false;
        Input::keys_last_down[F] = false;
        Input::keys_last_down[Q] = false;
        Input::keys_last_down[Left] = false;
        Input::keys_last_down[Right] = false;
        Input::keys_last_down[Up] = false;
        Input::keys_last_down[Down] = false;
        Input::keys_last_down[LShift] = false;
        Input::keys_last_down[Esc] = false;
        Input::keys_last_down[Space] = false;
    }
    bool Input::isKeyUp(Key key)
    {
        return !keys_down[key];
    }
    bool Input::isKeyDown(Key key)
    {
        return keys_down[key];
    }
    bool Input::isKeyPressed(Key key)
    {
        return (keys_down[key] && !keys_last_down[key]);
    }
    bool Input::isKeyReleased(Key key)
    {
        return (!keys_down[key] && keys_last_down[key]);
    }
} // namespace Nebel
