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
#ifdef PLATFORM_OSX
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_mouse.h>
#elif defined(PLATFORM_WEB)
#include <SDL/SDL.h>
#else 
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mouse.h>
#endif

#include <qui/InputInterface.h>
#include <qui/TouchInputEvent.h>
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

/* C Interface for dynamic game loading */
void gameInit()
{
    qui::game->init();
}

void gameUpdate(uint64_t dt)
{
    qui::game->update(dt);
}

void gamePaint()
{
    qui::game->paint();
}

void gameExit()
{
    qui::game->cleanup();
}

void gameSetWindowSize(uint16_t w, uint16_t h)
{
    qui::game->getWindow().setSize(glm::vec2(w, h));
    qui::game->onSystemEvent(qui::WINDOW_RESIZED);
}
/* End C Interface */

#ifndef PLATFORM_QT5
/* The entry point of the application */
#ifdef PLATFORM_OSX
int main(int /* argc */, char** /* argv */)
#elif defined(PLATFORM_WEB)
extern "C" int main(int, char**)
#else
int SDL_main(int argc, char* argv[])
#endif
#ifndef PLATFORM_WEB
{
    using qui::input::InputInterface;
    using qui::input::TouchInputEvent;
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
            else if (e.type == SDL_MOUSEBUTTONDOWN
                  || e.type == SDL_MOUSEBUTTONUP)
            {
                int x(0);
                int y(0);
                Uint32 state = SDL_GetMouseState(&x, &y);
                InputInterface ii;
                if (state == SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    LOG(INFO) << "Mouse button down";
                    ii.addTouchEvent(new TouchInputEvent(TouchInputEvent::DOWN, 0, x, y));
                }
                else
                {
                    LOG(INFO) << "Mouse button up";
                    ii.addTouchEvent(new TouchInputEvent(TouchInputEvent::UP, 0, x, y));
                }
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                int x(0);
                int y(0);
                Uint32 state = SDL_GetMouseState(&x, &y);
                if (state == SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    InputInterface ii;
                    ii.addTouchEvent(new TouchInputEvent(TouchInputEvent::MOVE, 0, x, y));
                }
            }
        }
        InputInterface ii;
        ii.fireUpdateListeners();
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
#else
{
    using qui::input::InputInterface;
    using qui::input::TouchInputEvent;
    LOG(INFO) << "App start.";

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(qui::game->getWindow().getSize().x
                                         , qui::game->getWindow().getSize().y
                                         , 32
                                         , SDL_OPENGL);

    qui::game->init();
    qui::Timer timer;
    bool quit = false;
    while (!quit)
    {
        qui::game->update(timer.getDeltaTime());
        qui::game->paint();
        SDL_Flip(screen); 
    }
/*
 if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 256; j++) {
      // alpha component is actually ignored, since this is to the screen
      *((Uint32*)screen->pixels + i * 256 + j) = SDL_MapRGBA(screen->format, i, j, 255-i, (i+j) % 255);
    }
  }
  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
*/
  qui::game->cleanup();
  SDL_Quit();
  return 0;
}
#endif  // PLATFORM_WEB
#endif  // PLATFORM_QT5
