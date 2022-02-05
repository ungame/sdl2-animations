#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"
#include "Input.hpp"
#include "Asset.hpp"
#include "Sprite.hpp"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl init everything failed: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    int imgInitted = IMG_Init(imgFlags);

    if ((imgInitted&imgFlags) != imgFlags)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl img init failed: %s", IMG_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Animations", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create window failed: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create renderer failed: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Asset* asset = new Asset(renderer, "assets/Sprites/PrototypeHero.png");
    Sprite* hero = new Sprite(asset, WINDOW_WIDTH / 2, WINDOW_HEIGHT - 10);

    while(Input::Instance()->Listen())
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        hero->update();
        hero->draw(renderer);

        SDL_RenderPresent(renderer);
    }

    delete hero;
    
    asset->destroy();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}