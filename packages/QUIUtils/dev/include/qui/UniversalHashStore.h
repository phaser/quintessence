// Copyright (C) 2013 Cristian Bidea
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

#ifndef PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_UNIVERSALHASHSTORE_H_
#define PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_UNIVERSALHASHSTORE_H_
#include <qui/cpp11compat.h>
#include <qui/Hash.h>

namespace qui
{
template <class MyObject>
class UniversalHashStore
{
 public:
     UniversalHashStore()
     {
     }

     virtual ~UniversalHashStore()
     {
     }

     inline void store(size_t id, MyObject obj)
     {
         objectsStore[id] = obj;
     }

     inline MyObject get(size_t id) const
     {
#ifdef PLATFORM_WIN32
         MyObject result = objectsStore.at(id);
#else
         MyObject result = objectsStore.find(id)->second;
#endif
         return result;
     }

     inline bool exists(size_t id) const
     {
         return (objectsStore.find(id) != objectsStore.end());
     }

     void remove(size_t id)
     {
        if (objectsStore.find(id) != objectsStore.end())
        {
            objectsStore.erase(objectsStore.find(id));
        }
     }

     cpp0x::unordered_map<size_t, MyObject>& getMap()
     {
         return objectsStore;
     }
 private:
     cpp0x::unordered_map<size_t, MyObject> objectsStore;
     UniversalHashStore(const UniversalHashStore&)  // no copy
     {
     }
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_UNIVERSALHASHSTORE_H_
