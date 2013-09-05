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

#include <anim/AAConstSpeedMove.h>
#include <IRenderScene.h>
#include <qui/log.h>

namespace anim
{
AAConstSpeedMove::AAConstSpeedMove(qui::IRenderScene& scene, unsigned int objectHash)  // NOLINT
    : finished(false)
    , scene(scene)
    , objectHash(objectHash)
    , speed(glm::vec2(0.f, 0.f))
    , displacement(glm::vec2(0.f, 0.f))
    , delta(glm::vec2(0.f, 0.f))
{
}

AAConstSpeedMove::~AAConstSpeedMove()
{
}

void AAConstSpeedMove::update(uint64_t /* dt */)
{
    if (glm::abs(delta.x) >= glm::abs(displacement.x)
     && delta.y >= displacement.y)
    {
        finished = true;
        return;
    }
    delta += speed;
    qui::Q2D::IObject* object = scene.getObject(objectHash);
    if (object == NULL)
    {
        LOG(LERROR) << "There is no object with " << objectHash;
        return;
    }
    object->setPosition(object->getPosition() + speed);
}

bool AAConstSpeedMove::isFinished()
{
    return finished;
}

void AAConstSpeedMove::setSpeed(const glm::vec2& speed)
{
    this->speed = speed;
}

void AAConstSpeedMove::setDisplacement(const glm::vec2& displacement)
{
    this->displacement = displacement;
}

void AAConstSpeedMove::reset()
{
    qui::Q2D::IObject* object = scene.getObject(objectHash);
    if (object == NULL)
    {
        LOG(LERROR) << "There is no object with " << objectHash;
        return;
    }
    object->setPosition(object->getPosition() - delta);
    delta = glm::vec2(0.f, 0.f);
    finished = false;
}
}  // namespace anim
