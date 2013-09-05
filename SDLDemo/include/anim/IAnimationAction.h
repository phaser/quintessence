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

#ifndef TESTGAME_DEV_INCLUDE_ANIM_IANIMATIONACTION_H_
#define TESTGAME_DEV_INCLUDE_ANIM_IANIMATIONACTION_H_
#include <stdint.h>
namespace anim
{
class IAnimationAction
{
    public:
        IAnimationAction()
        {
        }
        virtual ~IAnimationAction()
        {
        }
        virtual bool isFinished() =0;
        virtual void reset() =0;
        virtual void update(uint64_t dt) =0;
};
}  // namespace anim
#endif  // TESTGAME_DEV_INCLUDE_ANIM_IANIMATIONACTION_H_
