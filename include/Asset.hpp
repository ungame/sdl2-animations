#ifndef ASSET_H
#define ASSET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Asset
{
    public:
        Asset(SDL_Renderer* renderer, std::string filepath);
        void draw(SDL_Renderer* renderer, int width, int height, int x, int y, int row, int frame, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void draw(SDL_Renderer* renderer, SDL_Rect src, int width, int height, int x, int y, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void destroy();
        inline int getWidth() { return _width; }
        inline int getHeight() { return _height; }

    private:
        SDL_Texture* _texture;
        int _width;
        int _height;
};

#endif