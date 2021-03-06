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
#ifndef PACKAGES_QUI_QUIGAMEENTRY_DEV_INCLUDE_QUI_STANDARDGAMEENTRY_H_
#define PACKAGES_QUI_QUIGAMEENTRY_DEV_INCLUDE_QUI_STANDARDGAMEENTRY_H_

#include <qui/GLWindow.h>
#include <qui/cpp11compat.h>
#include <stdint.h>

extern "C"
{
    void gameInit();
    void gameUpdate(uint64_t dt);
    void gamePaint();
    void gameExit();
    void gameSetWindowSize(uint16_t w, uint16_t h);
}

namespace qui
{
enum SystemEvent
{
    PAUSE = 0
  , RESUME
  , WINDOW_RESIZED
};

class StandardGameEntry
{
 public:
    StandardGameEntry();
    virtual ~StandardGameEntry()
    {
    };
    /**
    * Init function. Here you should init your stuff.
    */
    virtual void init() =0;

    /**
     * Update function.
     */
    virtual void update(uint64_t dt) =0;

    /**
     * Paint function.
     */
    virtual void paint() =0;

    /**
     * You should clean your shit up, before exiting the application.
     */
    virtual void cleanup() =0;

    /**
     * System events
     */
    virtual void onSystemEvent(SystemEvent event) =0;
    GLWindow& getWindow() const;
    void setWindow(GLWindow win);
 private:
    cpp0x::shared_ptr<GLWindow> window;
};

extern std::auto_ptr<StandardGameEntry> game;
}  // namespace qui

#endif  // PACKAGES_QUI_QUIGAMEENTRY_DEV_INCLUDE_QUI_STANDARDGAMEENTRY_H_
