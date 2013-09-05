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

#include <GameScene.h>
#include <qui/Sprite.h>
#include <qui/log.h>

using qui::Q2D::IObject;
const char SCORE_CONST[] = "Label::Score";

GameScene::GameScene(const qui::StandardGameEntry& game)
    : IRenderScene(game)
{
}

GameScene::~GameScene()
{
}

void GameScene::render()
{
    IRenderScene::render();
}

bool GameScene::init()
{
    qui::Q2D::Sprite *sprite = new qui::Q2D::Sprite(HASH("Game::WaterTile"));
    if (!sprite->init())
    {
        LOG(LERROR) << "Could not load sprite 1!";
        return false;
    }
    sprite->setPosition(game.getWindow().getSize() / 2.f);
    addObject(HASH("WaterTile1"), sprite);
    sprite = new qui::Q2D::Sprite(HASH("Game::WaterTile"));
    if (!sprite->init())
    {
        LOG(LERROR) << "Could not load sprite 2!";
        return false;
    }
    sprite->setPosition(game.getWindow().getSize() / 2.f + glm::vec2(1024.f, 0.f));
    addObject(HASH("WaterTile2"), sprite);
    sprite = new qui::Q2D::Sprite(HASH("boat_lvl1"));
    if (!sprite->init())
    {
        LOG(LERROR) << "Could not load boat!";
        return false;
    }
    sprite->setPosition(game.getWindow().getSize() / 2.f);
    addObject(HASH("BoatPlayer"), sprite);
    sprite = new qui::Q2D::Sprite(HASH("boat_lvl1_turet"));
    if (!sprite->init())
    {
        LOG(LERROR) << "Could not load turret!";
        return false;
    }
    sprite->setAnchorPoint(glm::vec2(0.23f, 0.5f));
    sprite->setPosition(game.getWindow().getSize() / 2.f + glm::vec2(40.f, 0.f));
    addObject(HASH("TurretPlayer"), sprite);
    return true;
}

