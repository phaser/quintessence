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

#ifndef TESTGAME_DEV_INCLUDE_ANIM_AAAGREGATOR_H_
#define TESTGAME_DEV_INCLUDE_ANIM_AAAGREGATOR_H_
#include <anim/IAnimationAction.h>
#include <stdint.h>
#include <vector>
namespace anim
{
class AAAgregator : public IAnimationAction
{
    public:
        AAAgregator();
        ~AAAgregator();
        void update(uint64_t dt);
        bool isFinished();
        void addAnimationAction(IAnimationAction* action);
        void reset();
    private:
        std::vector<IAnimationAction*> actions;
        bool finished;
};
}  // namespace anim
#endif  // TESTGAME_DEV_INCLUDE_ANIM_AAAGREGATOR_H_
