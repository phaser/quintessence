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

#include <MathUtils.h>

namespace MathUtils
{
const float MY_PI = 3.141592653;

/** Converts a position relative to origin (0, 0) to the
 * angle made by the segment from the origin to the position
 * with the Ox axis.
 */
float getAngleFromPosition(const glm::vec2& pos)
{
    if (glm::abs(pos.x) <= 0.0000001f && glm::abs(pos.y) <= 0.0000001f)
    {
        return 0.f;
    }
    else if (glm::abs(pos.x) <= 0.0000001f && glm::abs(pos.y) >= 0.f)
    {
        return (pos.y >= 0.f ? 90.f : 270.f);
    }
    else if (glm::abs(pos.x) >= 0.f && glm::abs(pos.y) <= 0.0000001f)
    {
        return (pos.x >= 0.f ? 0.f : 180.f);
    }
    float OS = (pos.x * pos.y >= 0.f ? pos.y : pos.x);
    float sinx = glm::abs(OS) / glm::sqrt(pos.x*pos.x + pos.y*pos.y);
    float asinx = glm::asin(sinx);
    if (pos.x < 0.f && pos.y >= 0.f)
    {
        asinx += (MY_PI / 2.f);
    }
    else if (pos.x < 0.f && pos.y < 0.f)
    {
        asinx += MY_PI;
    }
    else if (pos.x >= 0.f && pos.y < 0.f)
    {
        asinx += (3.f*MY_PI) / 2.f;
    }

    return (asinx * 180) / MY_PI;
}

float getMinAngleDistance(float angle1, float angle2)
{
    float diff1 = angle2 - angle1;
    float diff2 = -360.f + angle2 - angle1;
    float adiff1 = glm::abs(diff1);
    float adiff2 = glm::abs(diff2);
    return (adiff1 < adiff2 ? diff1 : diff2);
}
}  // namespace MathUtils

