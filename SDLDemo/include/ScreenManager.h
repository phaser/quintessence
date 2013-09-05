// Copyright (C) 2013 Cristian Bidea
// This file is part of TestGame.
//
//    TestGame is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    TestGame is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with TestGame.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TESTGAME_DEV_INCLUDE_SCREENMANAGER_H_
#define TESTGAME_DEV_INCLUDE_SCREENMANAGER_H_
#include <qui/Hash.h>
#include <IGameScreen.h>
#include <qui/StandardGameEntry.h>
#include <stdint.h>
class ScreenManager
{
    public:
        explicit ScreenManager(const qui::StandardGameEntry& game);
        ~ScreenManager();
        void update(uint64_t dt);
        void paint();
    private:
        enum ScreenManagerState
        {
            LOAD_LOADING_SCREEN = 0
          , LOAD_NEXT_SCENE
          , SCENE_PLAY
        };

        const qui::StandardGameEntry& game;
        ScreenManagerState state;
        IGameScreen *currentScreen;
        IGameScreen *loadingScreen;
        unsigned int nextScene;
        ScreenManagerState getState() const;
        void setState(ScreenManagerState state);
};
#endif  // TESTGAME_DEV_INCLUDE_SCREENMANAGER_H_
