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

#ifndef TESTGAME_DEV_INCLUDE_LOADINGSCREEN_H_
#define TESTGAME_DEV_INCLUDE_LOADINGSCREEN_H_
#include <IGameScreen.h>
#include <IRenderScene.h>
#include <memory>

class LoadingScreen : public IGameScreen
{
    public:
        explicit LoadingScreen(const qui::StandardGameEntry& game);
        ~LoadingScreen();
        bool init();
        void update(uint64_t dt);
        void paint();
    private:
        std::auto_ptr<qui::IRenderScene> scene;
};
#endif  // TESTGAME_DEV_INCLUDE_LOADINGSCREEN_H_
