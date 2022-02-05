#include "Asset.hpp"
#include "AnimationBuilder.hpp"
#include "Animation.hpp"
#include "Input.hpp"
#include "Sprite.hpp"
#include "Time.hpp"

#include <string>
#include <map>
#include <math.h>
#include <iostream>

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
    Animation* startWalk = new Animation(asset, startWalkBuilder, "start_walk", scale);
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

    Animation* walk = new Animation(asset, walkBuilder, "walk", scale);
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

    AnimationBuilder* jumpBuilder = new AnimationBuilder(frameWidth, frameHeight, 0.1, false);
    jumpBuilder->add(2, 3);
    jumpBuilder->add(2, 4);
    jumpBuilder->add(2, 5);
    Animation* jump = new Animation(asset, jumpBuilder, "jump", scale);
    _animations[jump->getName()] = jump;

    AnimationBuilder* startFallBuilder = new AnimationBuilder(frameWidth, frameHeight, 0.2, false);
    startFallBuilder->add(2, 6);
    Animation* startFall = new Animation(asset, startFallBuilder, "start_fall", scale);
    _animations[startFall->getName()] = startFall;

    AnimationBuilder* fallBuilder = new AnimationBuilder(frameWidth, frameHeight, 1, true);
    fallBuilder->add(2, 7);
    Animation* fall = new Animation(asset, fallBuilder, "fall", scale);
    _animations[fall->getName()] = fall;

    _width = idleProps->frameWidth * scale / 2;
    _height = idleProps->frameHeight * scale;
    _x = x - _width;
    _y = y - _height;
    _flip = SDL_FLIP_NONE;

    _ground = y;
    _isWalking = false;
    _isGround = true;
    _velocity = INITIAL_VELOCITY;
    _startedJump = nullptr;
    _startedFall = nullptr;

    SDL_Log("Ground=%d, Height=%d, Y=%f", _ground, _height, _y);
}

void Sprite::update()
{
    _isWalking = false;

    bool jump = Input::Instance()->IsKeyDown(SDL_SCANCODE_SPACE) || Input::Instance()->IsKeyDown(SDL_SCANCODE_W);

    if(jump && _isGround)
    {
        _startedJump = new Time();
        SDL_Log("Started jump: %s", _startedJump->toString().c_str());
        _animations[_currentAnimation]->reset();
        _currentAnimation = "jump";
        _isGround = false;
    }

    if (!_isGround)
    {
        
        if (_currentAnimation == "jump")
        {
            _y -= _velocity;
            _velocity -= (GRAVITY / 4);
        }

        if (_currentAnimation == "fall")
        {
              _y -= _velocity;
            _velocity -= (GRAVITY / 2);
        }
    }

    bool walkLeft = Input::Instance()->IsKeyDown(SDL_SCANCODE_LEFT) || Input::Instance()->IsKeyDown(SDL_SCANCODE_A);
    
    if(walkLeft && _isGround)
    {
        _isWalking = true;
        _flip = SDL_FLIP_HORIZONTAL;
        _x -= 1 * WALK_FORCE;
    } 
    else if(walkLeft)
    {
        _flip = SDL_FLIP_HORIZONTAL;
        _x -= abs(_velocity);
    }

    bool walkRight = Input::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT) || Input::Instance()->IsKeyDown(SDL_SCANCODE_D);
    
    if(walkRight && _isGround)
    {
        _isWalking = true;
        _flip = SDL_FLIP_NONE;
        _x += 1 * WALK_FORCE;
    }
    else if(walkRight)
    {
        _flip = SDL_FLIP_NONE;
        _x += abs(_velocity);
    }

    if (_isWalking)
    {        
        if(_currentAnimation == "idle")
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "start_walk";
        }

        if(_currentAnimation == "start_walk" && _animations[_currentAnimation]->wasAnimated() >= 1)
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "walk";
        }

    } 
    else 
    {
        bool canStopWalk = _currentAnimation == "start_walk" || _currentAnimation == "walk";

        if (_isGround && canStopWalk)
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "stop_walk";
        }


        bool stoppedWalk = _currentAnimation == "stop_walk" && _animations[_currentAnimation]->wasAnimated() == 1;

        if(_isGround && stoppedWalk)
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "idle";
        }
    }

    if (_currentAnimation == "jump")
        SDL_Log("Jump elapsed %lfs. X=%lf, Y=%lf", Time::since(_startedJump), _x, _y);
    else if (_currentAnimation == "start_fall")
        SDL_Log("Start fall elapsed %lfs. X=%lf, Y=%lf", Time::since(_startedFall), _x, _y);
    else if (_currentAnimation != "idle")
        SDL_Log("%s. X=%lf, Y=%lf", _currentAnimation.c_str(), _x, _y);


    if (_currentAnimation == "jump" && Time::since(_startedJump) >= JUMP_TIME)
    {
        _animations[_currentAnimation]->reset();
        _currentAnimation = "start_fall";
        _startedJump = nullptr;
        _startedFall = new Time();
    }



    if (_currentAnimation == "start_fall" && Time::since(_startedFall) >= 0.1)
    {
        _animations[_currentAnimation]->reset();
        _currentAnimation = "fall";
        _startedFall = nullptr;
    }

    if (_y + _height >= _ground)
    {
        _y = _ground - _height;
        _isGround = true;

        if (_currentAnimation == "jump" || _currentAnimation == "start_fall" || _currentAnimation == "fall")
        {
            _animations[_currentAnimation]->reset();
            _currentAnimation = "idle";
             _velocity = INITIAL_VELOCITY;
        }
    }        
}

void Sprite::draw(SDL_Renderer* renderer)
{    
    _animations[_currentAnimation]->animate(renderer, _x, _y, _flip);
}