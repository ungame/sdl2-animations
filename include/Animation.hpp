#ifndef ANIMATION_H
#define ANIMATION_H

#include "Asset.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <chrono>
#include <vector>

struct AnimationProps
{
    int row;
    int frames;
    int frameWidth;
    int frameHeight;
    // frameDuration is the time in seconds, 
    // ex: 1 = one second per frame 
    // ex: 0.1 = 100ms per frame
    double frameDuration; 
    bool repeat;
};

class Animation
{
    public:
        Animation(Asset* asset, AnimationProps* props, std::string name, int scale = 1);
        Animation(Asset* asset, AnimationProps* props, std::vector<SDL_Rect> frames, std::string name, int scale = 1);
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