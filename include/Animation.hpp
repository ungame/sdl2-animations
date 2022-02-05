#ifndef ANIMATION_H
#define ANIMATION_H

#include "Asset.hpp"
#include "AnimationBuilder.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <chrono>
#include <vector>

class Animation
{
    public:
        Animation(Asset* asset, AnimationProps* props, std::string name, int scale = 1);
        Animation(Asset* asset, AnimationBuilder* builder, std::string name, int scale = 1);
        void animate(SDL_Renderer* renderer, int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void reset(); 
        inline bool wasAnimated() { return _animated; }
        inline std::string getName() { return _name; }

    private:
        Asset* _asset;
        AnimationProps* _props;
        std::string _name;
        int _frame;
        int _scale;
        bool _started;
        std::chrono::time_point<std::chrono::system_clock> _start;
        std::vector<SDL_Rect> _frames;
        int _animated;

        void build();
        void next();
};

#endif