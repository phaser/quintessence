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

#include <qui/MaterialManager.h>
#include <qui/Material.h>
#include <qui/Hash.h>

#ifdef PLATFORM_ANDROID
#ifndef nullptr
#define nullptr 0
#endif
#endif

namespace qui
{
UniversalHashStore<cpp0x::shared_ptr<IMaterial> > MaterialManager::materials;

void MaterialManager::addMaterial(const char* materialName, cpp0x::shared_ptr<IMaterial> material)
{
    materials.store(Hash(materialName).value, cpp0x::shared_ptr<IMaterial>(material));
}

cpp0x::shared_ptr<IMaterial> MaterialManager::getMaterial(size_t materialId)
{
    if (!materials.exists(materialId))
    {
        return cpp0x::shared_ptr<IMaterial>();
    }
    return materials.get(materialId);
}
}  // namespace qui
