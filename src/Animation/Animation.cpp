#include "Animation.hpp"
#include "Asset.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <chrono>

Animation::Animation(Asset* asset, AnimationProps* props, std::string name, int scale)
{
    _asset = asset;
    _props = props;
    _name = name;
    _scale = scale;
    _frame = 0;
    _started = false;

    build();
}

void Animation::build()
{
    for(int i = 0; i < _props->frames; i++)
    {
        SDL_Rect frame;
        frame.x = _props->frameWidth * i;
        frame.y = _props->frameHeight * _props->row;
        frame.w = _props->frameWidth;
        frame.h = _props->frameHeight;
        _frames.push_back(frame);
    }
}

Animation::Animation(Asset* asset, AnimationProps* props, std::vector<SDL_Rect> frames, std::string name, int scale)
{
    _asset = asset;
    _props = props;
    _name = name;
    _scale = scale;
    _frame = 0;
    _started = false;
    _frames = frames;
}

void Animation::animate(SDL_Renderer* renderer, int x, int y, SDL_RendererFlip flip)
{

    if (!_started)
    {
        _start = std::chrono::system_clock::now();
        _started = true;
    }

    int width = _props->frameWidth;
    int height = _props->frameHeight;
    
    SDL_Rect frame = _frames[_frame];

    _asset->draw(renderer, frame, width, height, x, y, _scale, flip);

    next();
}

void Animation::next()
{
    std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - _start;

    if (elapsed.count() < _props->frameDuration)
    {
        return;
    }

    if (_frame == _props->frames - 1)
    {
        _frame = _props->repeat ? 0 : _frame;
        _animated++;
    } 
    else
    {
        _frame++;
    }

    _start = std::chrono::system_clock::now();
}

void Animation::reset()
{
    _started = false;
    _frame = 0;
    _animated = 0;
}