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
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include <qui/log.h>
#include <qui/Timer.h>


namespace qui
{
StandardGameEntry::StandardGameEntry()
    : window(cpp0x::shared_ptr<GLWindow> (new GLWindow("Default", 640, 480)))
{
}

GLWindow& StandardGameEntry::getWindow() const
{
    return *window.get();
}

void StandardGameEntry::setWindow(GLWindow win)
{
    *this->window = win;
}
}  // namespace qui

/* The entry point of the application */
#ifdef PLATFORM_OSX
int main(int argc, char* argv[])
#else
int SDL_main(int argc, char* argv[])
#endif
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        LOG(FATAL) << "SDL_Init failed. " << SDL_GetError();
    }
    
    SDL_Window *win = nullptr;
    win = SDL_CreateWindow(qui::game->getWindow().getWindowName().c_str()
                         , SDL_WINDOWPOS_CENTERED
                         , SDL_WINDOWPOS_CENTERED
                         , qui::game->getWindow().getSize().x
                         , qui::game->getWindow().getSize().y
                         , SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        LOG(FATAL) << "Window initialization failed. " << SDL_GetError();
    }
    
    SDL_Renderer *ren = nullptr;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        LOG(FATAL) << SDL_GetError();
    }
    
    qui::game->init();
    qui::Timer timer;
    bool quit = false;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            LOG(INFO) << "Event type: " << e.type;
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                LOG(INFO) << "Mouse button down";
            }
        }
        qui::game->update(timer.getDeltaTime());
        SDL_RenderClear(ren);
        qui::game->paint();
        SDL_RenderPresent(ren);
        SDL_Delay(10);
    }
    
    qui::game->cleanup();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}