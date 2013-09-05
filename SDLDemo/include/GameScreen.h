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

#ifndef TESTGAME_DEV_INCLUDE_GAMESCREEN_H_
#define TESTGAME_DEV_INCLUDE_GAMESCREEN_H_
#include <IGameScreen.h>
#include <IRenderScene.h>
#include <qui/ITouchInput.h>
#include <anim/Animator.h>
#include <memory>
#include <list>

using qui::input::TouchInputEvent;
class Turret;
class Enemy;
class GameScreen : public IGameScreen, public qui::input::ITouchInput
{
    public:
        explicit GameScreen(const qui::StandardGameEntry& game);
        ~GameScreen();
        bool init();
        void update(uint64_t dt);
        void paint();

        /* Touch input functions */
        void onTouchesBegan(std::list<TouchInputEvent*> touches);
        void onTouchesMoved(std::list<TouchInputEvent*> touches);
        void onTouchesEnd(std::list<TouchInputEvent*> touches);
        void onTouchesCanceled(std::list<TouchInputEvent*> touches);
        bool canReceiveUpdates();
        /* Touch input functions */
    private:
        std::auto_ptr<qui::IRenderScene> hudScene;
        std::auto_ptr<qui::IRenderScene> gameScene;
        std::auto_ptr<Turret> playerTurret;
        bool receiveUpdates;
        std::auto_ptr<Enemy> enemy;
        void createWaterAnimator();
};
#endif  // TESTGAME_DEV_INCLUDE_GAMESCREEN_H_
