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

#ifndef TESTGAME_DEV_INCLUDE_IRENDERSCENE_H_
#define TESTGAME_DEV_INCLUDE_IRENDERSCENE_H_
#include <qui/IObject.h>
#include <qui/StandardGameEntry.h>
#include <qui/Hash.h>
#include <map>
#include <vector>
namespace qui
{
class IRenderScene
{
    public:
        explicit IRenderScene(const qui::StandardGameEntry& game)
            : game(game)
        {
        }
        virtual ~IRenderScene()
        {
        }
        virtual void render()
        {
            for (std::vector<Q2D::IObject*>::iterator it = renderObjects.begin()
               ; it != renderObjects.end()
               ; it++)
            {
                (*it)->paint();
            }
        }
        virtual bool init() =0;
        void addObject(unsigned int hash, Q2D::IObject* renderObject)
        {
            renderObjects.push_back(renderObject);
            objects.insert(std::make_pair(hash, renderObject));
        }
        Q2D::IObject* getObject(unsigned int hash)
        {
            std::map<unsigned int, Q2D::IObject*>::iterator it = objects.find(hash);
            if (it == objects.end())
            {
                return NULL;
            }
            return it->second;
        }
    protected:
        std::vector<Q2D::IObject*> renderObjects;
        std::map<unsigned int, Q2D::IObject*> objects;
        const qui::StandardGameEntry& game;
};
}  // namespace qui
#endif  // TESTGAME_DEV_INCLUDE_IRENDERSCENE_H_
