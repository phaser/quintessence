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
#ifndef PACKAGES_QUI_QUIINPUT_DEV_SOURCE_COMMON_EVENTSTORE_H_
#define PACKAGES_QUI_QUIINPUT_DEV_SOURCE_COMMON_EVENTSTORE_H_
#include <list>
#include <memory>
namespace qui
{
namespace input
{
class TouchInputEvent;
class ITouchInput;

class EventStore
{
 public:
     EventStore();
     ~EventStore()
     {
     }
     void addTouchEvent(TouchInputEvent *event);
     void registerTouchInputListener(ITouchInput *listener);
     void unregisterTouchInputListener(ITouchInput *listener);
     void fireUpdateListeners();
 private:
     std::list<TouchInputEvent*> touchEvents;
     std::list<ITouchInput*> listeners;
};
}  // namespace input
}  // namespace qui
#endif  // PACKAGES_QUI_QUIINPUT_DEV_SOURCE_COMMON_EVENTSTORE_H_
