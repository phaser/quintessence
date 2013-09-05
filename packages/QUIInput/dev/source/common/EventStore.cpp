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
#include "EventStore.h"  // NOLINT
#include <qui/TouchInputEvent.h>
#include <qui/ITouchInput.h>
#include <assert.h>
#include <list>

namespace qui
{
namespace input
{
EventStore::EventStore()
{
}

void EventStore::addTouchEvent(TouchInputEvent *event)
{
    assert(event != NULL);
    touchEvents.push_back(event);
}

void EventStore::registerTouchInputListener(ITouchInput *listener)
{
    listeners.push_back(listener);
}

void EventStore::unregisterTouchInputListener(ITouchInput *listener)
{
    listeners.remove(listener);
}

void EventStore::fireUpdateListeners()
{
    std::list<TouchInputEvent*> began;
    std::list<TouchInputEvent*> move;
    std::list<TouchInputEvent*> end;
    std::list<TouchInputEvent*> cancel;
    while (!touchEvents.empty())
    {
        std::list<TouchInputEvent*>::iterator it = touchEvents.begin();
        if ((*it)->getType() == qui::input::TouchInputEvent::DOWN)
        {
            began.push_back(*it);
        }
        else if ((*it)->getType() == qui::input::TouchInputEvent::MOVE)
        {
            move.push_back(*it);
        }
        else if ((*it)->getType() == qui::input::TouchInputEvent::UP)
        {
            end.push_back(*it);
        }
        else
        {
            cancel.push_back(*it);
        }
        touchEvents.erase(it);
    }

    for (std::list<ITouchInput*>::iterator it = listeners.begin()
       ; it != listeners.end()
       ; it++)
    {
        if ((*it)->canReceiveUpdates())
        {
            if (!began.empty()) (*it)->onTouchesBegan(began);
            if (!move.empty()) (*it)->onTouchesMoved(move);
            if (!end.empty()) (*it)->onTouchesEnd(end);
            if (!cancel.empty()) (*it)->onTouchesCanceled(cancel);
        }
    }

    while (!began.empty())
    {
        std::list<TouchInputEvent*>::iterator it = began.begin();
        delete (*it);
        began.erase(it);
    }

    while (!move.empty())
    {
        std::list<TouchInputEvent*>::iterator it = move.begin();
        delete (*it);
        move.erase(it);
    }

    while (!end.empty())
    {
        std::list<TouchInputEvent*>::iterator it = end.begin();
        delete (*it);
        end.erase(it);
    }

    while (!cancel.empty())
    {
        std::list<TouchInputEvent*>::iterator it = cancel.begin();
        delete (*it);
        cancel.erase(it);
    }
}
}  // namespace input
}  // namespace qui
