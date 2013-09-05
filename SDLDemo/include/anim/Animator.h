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

#ifndef TESTGAME_DEV_INCLUDE_ANIM_ANIMATOR_H_
#define TESTGAME_DEV_INCLUDE_ANIM_ANIMATOR_H_
#include <anim/IAnimationAction.h>
#include <stdint.h>
#include <vector>
#include <memory>
namespace anim
{
class Animator : public IAnimationAction
{
    public:
        Animator();
        ~Animator();
        void update(uint64_t dt);
        void addAnimationAction(IAnimationAction* action);
        inline void setLooped(bool looped);
        inline bool isLooped() const;
        bool isFinished();
        void reset();
    private:
        std::vector<IAnimationAction*> actions;
        uint16_t currentAction;
        bool looped;
        bool finished;
};

void Animator::setLooped(bool looped)
{
    this->looped = looped;
}

bool Animator::isLooped() const
{
    return this->looped;
}
}  // namespace anim
#endif  // TESTGAME_DEV_INCLUDE_ANIM_ANIMATOR_H_
