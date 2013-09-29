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
#include <Enemy.h>
#include <IRenderScene.h>
#include <Turret.h>
#include <qui/Sprite.h>
#include <qui/log.h>
#include <qui/Hash.h>
#include <qui/cpp11compat.h>

using qui::Q2D::Sprite;
uint16_t Enemy::static_uid = 0;

Enemy::Enemy(qui::IRenderScene* renderScene)
    : renderScene(renderScene)
{
    uid = static_uid++;
}

bool Enemy::init()
{
    char* text = new char[32];
    memset(text, 0, 32);
    snprintf(text, 31, "EnemyBoat%d", uid);  // NOLINT
    boatSpriteHash = HASH(text);
    memset(text, 0, 32);
    snprintf(text, 31, "EnemyTurret%d", uid);  // NOLINT
    turretSpriteHash = HASH(text);

    Sprite *sprite = new qui::Q2D::Sprite(HASH("enemy_boat"));
    if (!sprite->init())
    {
        LOG(LERROR) << "Could not load enemy sprite!";
        return false;
    }
    sprite->setPosition(glm::vec2(100.f, 100.f));
    renderScene->addObject(getBoatSpriteHash(), sprite);

    sprite = new qui::Q2D::Sprite(HASH("enemy_turet_lvl1"));
    if (!sprite->init())
    {
        LOG(LERROR) << "Could not load enemy turret sprite!";
        return false;
    }
    sprite->setPosition(glm::vec2(130.f, 100.f));
    renderScene->addObject(getTurretSpriteHash(), sprite);
    turret = std::auto_ptr<Turret>(new Turret(*renderScene, getTurretSpriteHash()));
    return true;
}

void Enemy::update(uint64_t dt)
{
}

size_t Enemy::getBoatSpriteHash() const
{
    return boatSpriteHash;
}

size_t Enemy::getTurretSpriteHash() const
{
    return turretSpriteHash;
}
