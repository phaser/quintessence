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
#include <anim/AAConstSpeedRotate.h>
#include <qui/log.h>

namespace anim
{
AAConstSpeedRotate::AAConstSpeedRotate(qui::IRenderScene& scene, unsigned int objectHash)  // NOLINT
    : finished(false)
    , scene(scene)
    , objectHash(objectHash)
    , rotationSpeed(0.f)
    , displacement(0.f)
    , delta(0.f)
{
}

AAConstSpeedRotate::~AAConstSpeedRotate()
{
}

void AAConstSpeedRotate::update(uint64_t /* dt */)
{
    if (glm::abs(delta) >= glm::abs(displacement))
    {
        finished = true;
        return;
    }
    delta += rotationSpeed;
    qui::Q2D::IObject* object = scene.getObject(objectHash);
    if (object == NULL)
    {
        LOG(LERROR) << "There is no object with " << objectHash;
        return;
    }
    object->setRotationAngle(object->getRotationAngle() + rotationSpeed);
}

bool AAConstSpeedRotate::isFinished()
{
    return finished;
}

void AAConstSpeedRotate::reset()
{
    delta = 0.f;
    finished = false;
}
}  // namespace anim
