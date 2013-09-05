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

#include <MainMenuScreen.h>
#include <MainMenuScene.h>
#include <qui/InputInterface.h>
#include <qui/TouchInputEvent.h>
#include <qui/Hash.h>
#include <list>

using qui::input::InputInterface;
using qui::input::TouchInputEvent;

MainMenuScreen::MainMenuScreen(const qui::StandardGameEntry& game)
    : IGameScreen(game)
    , scene(new MainMenuScene(game))
    , receiveUpdates(true)
{
}

MainMenuScreen::~MainMenuScreen()
{
    InputInterface ii;
    ii.unregisterTouchInputListener(this);
}

bool MainMenuScreen::init()
{
    InputInterface ii;
    ii.registerTouchInputListener(this);
    return scene->init();
}

void MainMenuScreen::update(uint64_t /* dt */)
{
}

void MainMenuScreen::paint()
{
    scene->render();
}

void MainMenuScreen::onTouchesBegan(std::list<TouchInputEvent*> /* touches */)
{
    nextScene = HASH("Scene::Game");
}

void MainMenuScreen::onTouchesMoved(std::list<TouchInputEvent*> /* touches */)
{
}

void MainMenuScreen::onTouchesEnd(std::list<TouchInputEvent*> /* touches */)
{
}

void MainMenuScreen::onTouchesCanceled(std::list<TouchInputEvent*> /* touches */)
{
}

bool MainMenuScreen::canReceiveUpdates()
{
    return receiveUpdates;
}

