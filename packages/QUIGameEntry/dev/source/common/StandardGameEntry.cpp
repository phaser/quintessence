// Copyright (C) 2012 Cristian Bidea
// This file is part of QUIGameEntry.
//
//    QUIGameEntry is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIGameEntry is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIGameEntry.  If not, see <http://www.gnu.org/licenses/>.
#include <qui/StandardGameEntry.h>
#include <SDL2/SDL.h>
#include <iostream>

namespace qui
{
StandardGameEntry::StandardGameEntry()
{
}
}  // namespace qui

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
    
    while (1)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
            {
                break;
            }

            qui::game->update(0);
            qui::game->paint();
        }
    }
    return 0;
}
