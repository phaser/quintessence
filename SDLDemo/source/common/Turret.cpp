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

#include <Turret.h>
#include <qui/IObject.h>
#include <MathUtils.h>
#include <qui/log.h>
#include <anim/AnimatorsManager.h>
#include <anim/AAConstSpeedRotate.h>
#include <anim/AAFunctionExecutor.h>

using qui::Q2D::IObject;
uint16_t Turret::static_uid = 0;

Turret::Turret(qui::IRenderScene& scene, size_t objectId)  // NOLINT
    : scene(scene)
    , objectId(objectId)
    , target(-1.f, -1.f)
    , playerTurretAnimatorHash(0)
{
    uid = static_uid++;
}

void Turret::positionAndShoot(const glm::vec2& target)
{
    if (target.x < 0 && target.y < 0)
    {  // reset
    }
    this->target = target;
    IObject *object = scene.getObject(objectId);
    float angle = MathUtils::getAngleFromPosition(target - object->getPosition());
    float diff = MathUtils::getMinAngleDistance(object->getRotationAngle(), angle);
    LOG(INFO) << "Diff angle: " << diff;
    if (glm::abs(diff) <= 0.0000001f)
    {  // angle didn't changed
        return;
    }
    anim::AnimatorsManager am;
    am.unregisterAnimator(getPlayerTurretAnimatorHash());
    cpp0x::shared_ptr<anim::Animator> turretAnimator = cpp0x::shared_ptr<anim::Animator>(new anim::Animator());
    anim::AAConstSpeedRotate *rotation = new anim::AAConstSpeedRotate(scene, objectId);
    rotation->setRotationSpeed(0.5f * (diff / glm::abs(diff)));
    rotation->setDisplacement(diff);
    turretAnimator->addAnimationAction(rotation);
    am.registerAnimator(getPlayerTurretAnimatorHash(), turretAnimator);
}

size_t Turret::getPlayerTurretAnimatorHash()
{
    if (playerTurretAnimatorHash != 0)
    {
        return playerTurretAnimatorHash;
    }
    char* text = new char[32];
    memset(text, 0, 32);
    snprintf(text, 31, "PlayerTurretAnimator%d", uid);  // NOLINT
    playerTurretAnimatorHash = HASH(text);
    return playerTurretAnimatorHash;
}
