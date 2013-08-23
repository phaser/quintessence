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
#include <stdint.h>

namespace qui
{
Timer::Timer()
{
    st.wHour = 0;
    st.wMinute = 0;
    st.wSecond = 0;
    st.wMilliseconds = 0;
}

uint32_t Timer::getDeltaTime()
{
    SYSTEMTIME st2;
    ::GetSystemTime(&st2);
    uint64_t result = 0;
    if (!(st.wHour == 0
     && st.wMinute == 0
     && st.wSecond == 0
     && st.wMilliseconds == 0))
    {
        result = (st2.wMilliseconds - st.wMilliseconds)
               + (st2.wSecond - st.wSecond) * 1000
               + (st2.wMinute - st.wMinute) * 60000
               + (st2.wHour - st.wHour) * 3600000;
    }
    st = st2;
    return result;
}
}  // namespace qui
