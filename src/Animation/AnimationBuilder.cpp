#include "AnimationBuilder.hpp"

#include <SDL2/SDL.h>
#include <vector>

AnimationBuilder::AnimationBuilder(int width, int height, double duration, bool repeat)
{
    _props = new AnimationProps;
    _props->frameWidth = width;
    _props->frameHeight = height;
    _props->frameDuration = duration;
    _props->repeat = repeat;
    _props->row = -1; // unused
}

void AnimationBuilder::add(int row, int column)
{
    SDL_Rect frame;
    frame.x = _props->frameWidth * column;
    frame.y = _props->frameHeight * row;
    frame.w = _props->frameWidth;
    frame.h = _props->frameHeight;
    _frames.push_back(frame);
    _props->frames = _frames.size();
}
