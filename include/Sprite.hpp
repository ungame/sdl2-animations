#ifndef SPRITE_H
#define SPRITE_H

#include "Asset.hpp"
#include "Animation.hpp"
#include "Time.hpp"
#include <string>
#include <map>
#include <chrono>

#include <SDL2/SDL.h>

#define WALK_FORCE 4.0f
#define GRAVITY 1.0f
#define INITIAL_VELOCITY 10.0f
#define JUMP_TIME 0.5f

class Sprite
{
    public:
        Sprite(Asset* asset, int x, int y);
        void update();
        void draw(SDL_Renderer* renderer);

    private:
        std::map<std::string, Animation*> _animations;
        std::string _currentAnimation;
        float _x;
        float _y;
        int _width;
        int _height;
        SDL_RendererFlip _flip;
        bool _isWalking;
        int _ground;
        bool _isGround;
        float _velocity;
        Time* _startedJump;
        Time* _startedFall;
};

#endif