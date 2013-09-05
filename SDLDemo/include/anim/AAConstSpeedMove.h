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

#ifndef TESTGAME_DEV_INCLUDE_ANIM_AACONSTSPEEDMOVE_H_
#define TESTGAME_DEV_INCLUDE_ANIM_AACONSTSPEEDMOVE_H_
#include <anim/IAnimationAction.h>
#include <IRenderScene.h>
#include <stdint.h>
#include <glm/glm.hpp>
#include <vector>

namespace anim
{
class AAConstSpeedMove : public IAnimationAction
{
    public:
        AAConstSpeedMove(qui::IRenderScene& scene, unsigned int objectHash);  // NOLINT
        ~AAConstSpeedMove();
        void update(uint64_t dt);
        bool isFinished();
        void setSpeed(const glm::vec2& speed);
        void setDisplacement(const glm::vec2& displacement);
        void reset();
    private:
        bool finished;
        qui::IRenderScene& scene;
        unsigned int objectHash;
        glm::vec2 speed;
        glm::vec2 displacement;
        glm::vec2 delta;
};
}  // namespace anim
#endif  // TESTGAME_DEV_INCLUDE_ANIM_AACONSTSPEEDMOVE_H_
