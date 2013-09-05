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

#include <anim/AAAgregator.h>
#include <vector>

#ifdef PLATFORM_LINUX
#define NULL nullptr
#endif
namespace anim
{
AAAgregator::AAAgregator()
    : finished(false)
{
}

AAAgregator::~AAAgregator()
{
    for (std::vector<IAnimationAction*>::iterator it = actions.begin()
       ; it != actions.end()
       ; it++)
    {
        IAnimationAction *action = (*it);
        delete action;
        action = NULL;
    }
    actions.clear();
}

void AAAgregator::update(uint64_t dt)
{
    finished = true;
    for (std::vector<IAnimationAction*>::iterator it = actions.begin()
       ; it != actions.end()
       ; it++)
    {
        (*it)->update(dt);
        finished = finished && (*it)->isFinished();
    }
}

bool AAAgregator::isFinished()
{
    return finished;
}

void AAAgregator::addAnimationAction(IAnimationAction* action)
{
    actions.push_back(action);
}

void AAAgregator::reset()
{
    finished = false;
    for (std::vector<IAnimationAction*>::iterator it = actions.begin()
       ; it != actions.end()
       ; it++)
    {
        (*it)->reset();
    }
}
}  // namespace anim
