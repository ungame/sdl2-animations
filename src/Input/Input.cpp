#include "Input.hpp"

#include <SDL2/SDL.h>

Input* Input::_input = nullptr;

Input::Input()
{
    _keyboard = SDL_GetKeyboardState(nullptr);
    _mouse = MouseButton::NONE;
}

bool Input::Listen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return false;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
            _keyboard = SDL_GetKeyboardState(nullptr);
            break;

        case SDL_MOUSEBUTTONDOWN:
            _mouse = event.button.button;
            break;
        
        case SDL_MOUSEBUTTONUP:
            _mouse = 0;
            break;

        default:
            break;
        }
    }

    return true;

}
bool Input::IsKeyDown(SDL_Scancode key)
{
    return _keyboard[key] == 1;
}

bool Input::IsMouseButtonDown(MouseButton button)
{
    if (button == MouseButton::LEFT)
        return _mouse == SDL_BUTTON_LEFT;
   
    return _mouse == SDL_BUTTON_RIGHT;
}