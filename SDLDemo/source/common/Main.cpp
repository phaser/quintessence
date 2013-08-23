#include "SDL2/SDL.h"
#include <iostream>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = nullptr;
    win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    
    SDL_Renderer *ren = nullptr;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    return 0;
}