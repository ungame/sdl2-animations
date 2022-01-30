#include "Sprite.hpp"

#include "Asset.hpp"
#include "Animation.hpp"
#include "AnimationBuilder.hpp"
#include "Input.hpp"

#include <string>
#include <map>
#include <SDL2/SDL.h>

Sprite::Sprite(Asset* asset, int x, int y)
{
    int frameWidth = asset->getWidth() / 8;
    int frameHeight = asset->getHeight() / 3;

    AnimationProps* idleProps = new AnimationProps;
    idleProps->row = 0;
    idleProps->frames = 6;
    idleProps->frameWidth = frameWidth;
    idleProps->frameHeight = frameHeight;
    idleProps->frameDuration = 0.1;
    idleProps->repeat = true;

    int scale = 2;
    Animation* idle = new Animation(asset, idleProps, "idle", scale);
    _animations[idle->getName()] = idle;
    _currentAnimation = idle->getName();

    AnimationBuilder* startWalkBuilder = new AnimationBuilder(frameWidth, frameHeight, 0.05, true);
    startWalkBuilder->add(0, 6);
    startWalkBuilder->add(0, 7);
    Animation* startWalk = new Animation(asset, startWalkBuilder->getProps(), startWalkBuilder->getFrames(), "start_walk", scale);
    _animations[startWalk->getName()] = startWalk;

    AnimationBuilder* walkBuilder = new AnimationBuilder(frameWidth, frameHeight, 0.1, true);
    walkBuilder->add(1, 0);
    walkBuilder->add(1, 1);
    walkBuilder->add(1, 2);
    walkBuilder->add(1, 3);
    walkBuilder->add(1, 4);
    walkBuilder->add(1, 5);
    walkBuilder->add(1, 6);
    walkBuilder->add(1, 7);

    Animation* walk = new Animation(asset, walkBuilder->getProps(), walkBuilder->getFrames(), "walk", scale);
    _animations[walk->getName()] = walk;

    AnimationProps* stopWalkProps = new AnimationProps;
    stopWalkProps->row = 2;
    stopWalkProps->frames = 3;
    stopWalkProps->frameWidth = frameWidth;
    stopWalkProps->frameHeight = frameHeight;
    stopWalkProps->frameDuration = 0.05;
    stopWalkProps->repeat = true;
    Animation* stopWalk = new Animation(asset, stopWalkProps, "stop_walk", scale);
    _animations[stopWalk->getName()] = stopWalk;

    _x = x - idleProps->frameWidth * scale / 2;
    _y = y - idleProps->frameHeight * scale;
    _flip = SDL_FLIP_NONE;

    _isWalking = false;
}

void Sprite::update()
{
    if(Input::Instance()->IsMouseButtonDown(MouseButton::LEFT))
    {
        SDL_Log("Mouse button left");
    }
    
    if(Input::Instance()->IsMouseButtonDown(MouseButton::RIGHT))
    {
        SDL_Log("Mouse button right");
    }

    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_UP))
    {
        SDL_Log("Keyboard button up");
    }

    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
    {
        SDL_Log("Keyboard button down");
    }

    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_SPACE))
    {
        SDL_Log("Keyboard button space");
    } 

    _isWalking = false;

    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
    {
        _isWalking = true;
        _flip = SDL_FLIP_HORIZONTAL;
        _x -= 1 * WALK_FORCE;
    } 

    if(Input::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
    {
        _isWalking = true;
        _flip = SDL_FLIP_NONE;
        _x += 1 * WALK_FORCE;
    }

    if (_isWalking)
    {        
        if(_currentAnimation == "idle")
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "start_walk";
        }

        if(_currentAnimation == "start_walk" && _animations[_currentAnimation]->wasAnimated() == 1)
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "walk";
        }

    } 
    else 
    {
        if (_currentAnimation == "start_walk" || _currentAnimation == "walk")
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "stop_walk";
        }


        if(_currentAnimation == "stop_walk" && _animations[_currentAnimation]->wasAnimated() == 1)
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "idle";
        } 
    }
}

void Sprite::draw(SDL_Renderer* renderer)
{    
    _animations[_currentAnimation]->animate(renderer, _x, _y, _flip);
}