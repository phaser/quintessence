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

#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_TEXTUREMANAGER_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_TEXTUREMANAGER_H_

#include <qui/UniversalHashStore.h>
#include <qui/cpp11compat.h>

namespace qui
{
class GLTexture;
class TextureManager
{
 public:
     TextureManager()
     {
     }

     cpp0x::shared_ptr<GLTexture> getTexture(size_t id) const;
     bool loadTexture(const char* textureFile, const char* name = NULL);
 private:
    static UniversalHashStore<cpp0x::shared_ptr<GLTexture> > textures;

    TextureManager(const TextureManager&)  // no copy
    {
    }
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_TEXTUREMANAGER_H_
