#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

enum MouseButton { NONE, LEFT, RIGHT };

class Input
{
    public:
        static Input* Instance() { return _input = (_input != nullptr) ? _input : new Input(); }
        bool Listen();
        bool IsKeyDown(SDL_Scancode key);
        bool IsMouseButtonDown(MouseButton button);

    private:
        Input();
        static Input* _input;
        const Uint8* _keyboard;
        Uint8 _mouse;
};

#endif