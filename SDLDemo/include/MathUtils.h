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

#ifndef TESTGAME_DEV_INCLUDE_MATHUTILS_H_
#define TESTGAME_DEV_INCLUDE_MATHUTILS_H_
#include <glm/glm.hpp>
namespace MathUtils
{
float getAngleFromPosition(const glm::vec2& pos);
float getMinAngleDistance(float angle1, float angle2);
}  // namespace MathUtils
#endif  // TESTGAME_DEV_INCLUDE_MATHUTILS_H_
