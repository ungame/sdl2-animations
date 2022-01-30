#include "Asset.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

Asset::Asset(SDL_Renderer* renderer, std::string filepath)
{
    SDL_Surface* surface = IMG_Load(filepath.c_str());

    if (surface == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl img load %s failed: %s", filepath.c_str(), IMG_GetError());
        return;
    }

    _texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (_texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create texture from surface failed: %s", SDL_GetError());
        return;
    }

    _width = surface->w;
    _height = surface->h;

    SDL_FreeSurface(surface);
}

void Asset::draw(SDL_Renderer* renderer, int width, int height, int x, int y, int row, int frame, int scale, SDL_RendererFlip flip)
{
    SDL_Rect src;
    src.x = width * frame;
    src.y = height * row;
    src.w = width;
    src.h = height;

    draw(renderer, src, width, height, x, y, scale, flip);
}

void Asset::draw(SDL_Renderer* renderer, SDL_Rect src, int width, int height, int x, int y, int scale, SDL_RendererFlip flip)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = width * scale;
    dst.h = height * scale;

    int angle = 0;
    SDL_Point* point = nullptr;

    SDL_RenderCopyEx(renderer, _texture, &src, &dst, angle, point, flip);
}

void Asset::destroy()
{
    if(_texture != nullptr) 
        SDL_DestroyTexture(_texture);
}