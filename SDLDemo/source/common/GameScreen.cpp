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

#include <GameScreen.h>
#include <qui/InputInterface.h>
#include <qui/TouchInputEvent.h>
#include <anim/AAAgregator.h>
#include <anim/AAConstSpeedMove.h>
#include <GameHUDScene.h>
#include <GameScene.h>
#include <Turret.h>
#include <anim/AnimatorsManager.h>
#include <Enemy.h>
#include <list>

using qui::input::InputInterface;
using qui::input::TouchInputEvent;

GameScreen::GameScreen(const qui::StandardGameEntry& game)
    : IGameScreen(game)
    , hudScene(new GameHUDScene(game))
    , gameScene(new GameScene(game))
    , playerTurret(new Turret(*gameScene.get(), HASH("TurretPlayer")))
    , receiveUpdates(true)
{
}

GameScreen::~GameScreen()
{
    InputInterface ii;
    anim::AnimatorsManager am;
    ii.unregisterTouchInputListener(this);
    am.unregisterAnimator(HASH("WaterAnimator"));
}

bool GameScreen::init()
{
    InputInterface ii;
    ii.registerTouchInputListener(this);
    bool result = hudScene->init();
    result = (result && gameScene->init());
    createWaterAnimator();
    enemy = std::auto_ptr<Enemy>(new Enemy(gameScene.get()));
    result = (result && enemy->init());
    return result;
}

void GameScreen::update(uint64_t dt)
{
    enemy->update(dt);
}

void GameScreen::paint()
{
    gameScene->render();
    hudScene->render();
}

/* Touch input functions */
void GameScreen::onTouchesBegan(std::list<TouchInputEvent*> touches)
{
    for (std::list<TouchInputEvent*>::iterator it = touches.begin()
       ; it != touches.end()
       ; it++)
    {
        TouchInputEvent *event = *it;
        playerTurret->positionAndShoot(glm::vec2(event->getX(), event->getY()));
    }
}

void GameScreen::onTouchesMoved(std::list<TouchInputEvent*> touches)
{
    for (std::list<TouchInputEvent*>::iterator it = touches.begin()
       ; it != touches.end()
       ; it++)
    {
        TouchInputEvent *event = *it;
        playerTurret->positionAndShoot(glm::vec2(event->getX(), event->getY()));
    }
}

void GameScreen::onTouchesEnd(std::list<TouchInputEvent*> touches)
{
    for (std::list<TouchInputEvent*>::iterator it = touches.begin()
       ; it != touches.end()
       ; it++)
    {
        TouchInputEvent *event = *it;
        playerTurret->positionAndShoot(glm::vec2(event->getX(), event->getY()));
    }
}

void GameScreen::onTouchesCanceled(std::list<TouchInputEvent*> touches)
{
}

bool GameScreen::canReceiveUpdates()
{
    return receiveUpdates;
}
/* Touch input functions */

void GameScreen::createWaterAnimator()
{
    /* water animation */
    cpp0x::shared_ptr<anim::Animator> waterAnimator = cpp0x::shared_ptr<anim::Animator>(new anim::Animator());
    anim::AAAgregator *tiles = new anim::AAAgregator();
    anim::AAConstSpeedMove *waterTileMover1 = new anim::AAConstSpeedMove(*gameScene.get(), HASH("WaterTile1"));
    anim::AAConstSpeedMove *waterTileMover2 = new anim::AAConstSpeedMove(*gameScene.get(), HASH("WaterTile2"));
    tiles->addAnimationAction(waterTileMover1);
    tiles->addAnimationAction(waterTileMover2);
    waterAnimator->addAnimationAction(tiles);
    glm::vec2 speed(-3.0f, 0.f);
    glm::vec2 displacement(-1024.f, 0.f);
    waterTileMover1->setSpeed(speed);
    waterTileMover2->setSpeed(speed);
    waterTileMover1->setDisplacement(displacement);
    waterTileMover2->setDisplacement(displacement);
    waterAnimator->setLooped(true);

    anim::AnimatorsManager am;
    am.registerAnimator(HASH("WaterAnimator"), waterAnimator);
}
