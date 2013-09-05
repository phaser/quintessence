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

#include <anim/Animator.h>
#include <anim/IAnimationAction.h>
#include <vector>

namespace anim
{
Animator::Animator()
    : currentAction(0)
    , looped(false)
    , finished(false)
{
}

Animator::~Animator()
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

void Animator::update(uint64_t dt)
{
    if (currentAction >= actions.size())
    {
        finished = true;
        return;
    }
    IAnimationAction *action = actions.at(currentAction);
    action->update(dt);
    if (action->isFinished())
    {
        currentAction++;
        if (currentAction >= actions.size() && isLooped())
        {
            currentAction = 0;
            reset();
        }
    }
}

void Animator::addAnimationAction(IAnimationAction* action)
{
    actions.push_back(action);
}

bool Animator::isFinished()
{
    return finished;
}

void Animator::reset()
{
    this->finished = false;
    for (std::vector<IAnimationAction*>::iterator it = actions.begin()
       ; it != actions.end()
       ; it++)
    {
        (*it)->reset();
    }
}
}  // namespace anim
