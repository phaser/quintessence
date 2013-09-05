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
#include <qui/InputInterface.h>
#include <qui/TouchInputEvent.h>
#include <qui/ITouchInput.h>
#include "./EventStore.h"

namespace qui
{
namespace input
{
    std::auto_ptr<EventStore> InputInterface::eventStore(new EventStore());

InputInterface::InputInterface()
{
}

void InputInterface::addTouchEvent(TouchInputEvent *event)
{
    eventStore->addTouchEvent(event);
}

void InputInterface::registerTouchInputListener(ITouchInput *listener)
{
    eventStore->registerTouchInputListener(listener);
}

void InputInterface::unregisterTouchInputListener(ITouchInput *listener)
{
    eventStore->unregisterTouchInputListener(listener);
}

void InputInterface::fireUpdateListeners()
{
    eventStore->fireUpdateListeners();
}
}  // namespace input
}  // namespace qui
