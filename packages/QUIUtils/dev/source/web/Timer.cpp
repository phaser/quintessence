// Copyright (C) 2012 Cristian Bidea
// This file is part of QUIUtils.
//
//    QUIUtils is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIUtils is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIUtils.  If not, see <http://www.gnu.org/licenses/>.

#include <qui/Timer.h>
#include <time.h>
#include <stdint.h>

namespace qui
{
Timer::Timer()
{
    tp.tv_sec = 0;
    tp.tv_nsec = 0;
}

uint32_t Timer::getDeltaTime()
{
    struct timespec tp2;
    clock_gettime(CLOCK_REALTIME, &tp2);
    uint64_t result = 0;
    if (!(tp.tv_sec == 0
       && tp.tv_nsec == 0))
    {
        result += (tp2.tv_nsec - tp.tv_nsec)
                + (tp2.tv_sec - tp.tv_sec) * 1000;
    }
    tp = tp2;
    return result;
}
}  // namespace qui
