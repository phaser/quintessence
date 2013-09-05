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

#include <GameHUDScene.h>
#include <qui/text/Font.h>
#include <qui/text/Label.h>
#include <qui/Hash.h>
#include <qui/log.h>

using qui::Q2D::IObject;
const char SCORE_CONST[] = "Label::Score";

GameHUDScene::GameHUDScene(const qui::StandardGameEntry& game)
    : IRenderScene(game)
{
}

GameHUDScene::~GameHUDScene()
{
}

void GameHUDScene::render()
{
    IRenderScene::render();
}

bool GameHUDScene::init()
{
    IObject *label = qui::text::Label::getObject("Score", HASH("MainFont"));
    label->setAnchorPoint(glm::vec2(0.f, 0.f));
    label->setPosition(glm::vec2(0.f, 0.f));
    addObject(HASH(SCORE_CONST), label);
    return true;
}

