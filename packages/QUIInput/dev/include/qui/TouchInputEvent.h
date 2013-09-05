// Copyright (C) 2013 Cristian Bidea
// This file is part of QUIInput.
//
//    QUIInput is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIInput is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIInput.  If not, see <http://www.gnu.org/licenses/>.
#ifndef PACKAGES_QUI_QUIINPUT_DEV_INCLUDE_QUI_TOUCHINPUTEVENT_H_
#define PACKAGES_QUI_QUIINPUT_DEV_INCLUDE_QUI_TOUCHINPUTEVENT_H_

#include <stdint.h>

namespace qui
{
namespace input
{
class TouchInputEvent
{
 public:
    enum TouchInputEventType
    {
        DOWN = 0
      , MOVE
      , UP
      , CANCELED
    };
    TouchInputEvent(TouchInputEventType type
             , uint32_t pointerId
          , int32_t x
          , int32_t y)
       : type(type)
       , pointerId(pointerId)
       , x(x)
       , y(y)
    {
    }

    inline TouchInputEventType getType() const;
    inline void setType(TouchInputEventType type);
    inline uint32_t getPointerId() const;
    inline void setPointerId(uint32_t pointerId);
    inline int32_t getX() const;
    inline void setX(int32_t x);
    inline int32_t getY() const;
    inline void setY(int32_t y);

 private:
    TouchInputEventType type;
    uint32_t pointerId;
    int32_t x;
    int32_t y;
};

TouchInputEvent::TouchInputEventType TouchInputEvent::getType() const
{
    return type;
}

void TouchInputEvent::setType(TouchInputEventType type)
{
    this->type = type;
}

uint32_t TouchInputEvent::getPointerId() const
{
    return pointerId;
}

void TouchInputEvent::setPointerId(uint32_t pointerId)
{
    this->pointerId = pointerId;
}

int32_t TouchInputEvent::getX() const
{
    return x;
}

void TouchInputEvent::setX(int32_t x)
{
    this->x = x;
}

int32_t TouchInputEvent::getY() const
{
    return y;
}

void TouchInputEvent::setY(int32_t y)
{
    this->y = y;
}
}  // namespace input
}  // namespace qui
#endif  // PACKAGES_QUI_QUIINPUT_DEV_INCLUDE_QUI_TOUCHINPUTEVENT_H_
