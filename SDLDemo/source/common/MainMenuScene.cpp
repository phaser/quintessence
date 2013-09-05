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

#include <MainMenuScene.h>
#include <qui/text/Font.h>
#include <qui/text/Label.h>
#include <qui/Hash.h>
#include <qui/log.h>

using qui::Q2D::IObject;

MainMenuScene::MainMenuScene(const qui::StandardGameEntry& game)
    : IRenderScene(game)
{
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::render()
{
    IRenderScene::render();
}

bool MainMenuScene::init()
{
    const char mainMenuTitle[] = "MainMenu";
    IObject *label = qui::text::Label::getObject(mainMenuTitle, HASH("MainFont"));
    label->setPosition(game.getWindow().getSize() / 2.f);
    addObject(HASH(mainMenuTitle), label);
    return true;
}

