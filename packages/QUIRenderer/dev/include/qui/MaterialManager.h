// Copyright (C) 2013 Cristian Bidea
// This file is part of QUIRenderer.
//
//    QUIRenderer is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIRenderer is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIRenderer.  If not, see <http://www.gnu.org/licenses/>.

#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_MATERIALMANAGER_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_MATERIALMANAGER_H_

#include <qui/UniversalHashStore.h>
#include <qui/cpp11compat.h>

namespace qui
{
class IMaterial;
class Material;
class MaterialManager
{
 public:
     MaterialManager()
     {
     }

     void addMaterial(const char* materialName, cpp0x::shared_ptr<IMaterial> material);
     cpp0x::shared_ptr<IMaterial> getMaterial(size_t materialId);
 private:
    static UniversalHashStore<cpp0x::shared_ptr<IMaterial> > materials;

    MaterialManager(const MaterialManager&)  // no copy
    {
    }
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_MATERIALMANAGER_H_
