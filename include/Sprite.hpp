#ifndef SPRITE_H
#define SPRITE_H

#include "Asset.hpp"
#include "Animation.hpp"
#include <string>
#include <map>

#include <SDL2/SDL.h>

#define WALK_FORCE 4.0f

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
        SDL_RendererFlip _flip;
        bool _startedWalk;
        bool _isWalking;
};

#endif