#ifndef ANIMATION_BUILDER_H
#define ANIMATION_BUILDER_H

#include "Asset.hpp"
#include <SDL2/SDL.h>
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

class AnimationBuilder
{
    public:
        AnimationBuilder(int width, int height, double duration, bool repeat);
        void add(int row, int column);
        inline std::vector<SDL_Rect> getFrames() { return _frames; };
        inline AnimationProps* getProps() { return _props; }

    private:
        std::vector<SDL_Rect> _frames;
        AnimationProps* _props;
};

#endif