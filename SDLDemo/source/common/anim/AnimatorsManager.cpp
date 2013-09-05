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

#include <anim/AnimatorsManager.h>

namespace anim
{
qui::UniversalHashStore<cpp0x::shared_ptr<Animator> > AnimatorsManager::animators;

void AnimatorsManager::update(uint64_t dt)
{
    for (cpp0x::unordered_map<size_t, cpp0x::shared_ptr<Animator> >::iterator it = animators.getMap().begin()
       ; it != animators.getMap().end()
       ; it++)
    {
        it->second->update(dt);
        if (it->second->isFinished())
        {
            animators.remove(it->first);
        }
    }
}

void AnimatorsManager::registerAnimator(unsigned int hash, cpp0x::shared_ptr<Animator> animator)
{
    animators.store(hash, animator);
}

void AnimatorsManager::unregisterAnimator(unsigned int hash)
{
    animators.remove(hash);
}

cpp0x::shared_ptr<Animator> AnimatorsManager::getAnimator(unsigned int hash)
{
    if (animators.exists(hash))
    {
        return animators.get(hash);
    }
    cpp0x::shared_ptr<Animator>(reinterpret_cast<Animator*>(NULL));
}
}  // namespace anim
