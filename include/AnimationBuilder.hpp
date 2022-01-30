#ifndef ANIMATION_BUILDER_H
#define ANIMATION_BUILDER_H

#include "Asset.hpp"
#include "Animation.hpp"
#include <SDL2/SDL.h>
#include <vector>

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