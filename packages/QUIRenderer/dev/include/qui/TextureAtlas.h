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
#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_TEXTUREATLAS_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_TEXTUREATLAS_H_
#include <glm/glm.hpp>
#include <qui/cpp11compat.h>
#include <string>
#include <vector>
namespace qui
{
class TextureAtlasModule;
class TextureAtlas
{
    public:
        explicit TextureAtlas(const std::string& fileName);
        bool loadModules();
        bool createMaterials(size_t shaderId);
    private:
        std::string fileName;
        std::string image;
        glm::vec2 size;
        std::vector<cpp0x::shared_ptr<TextureAtlasModule> > modules;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_TEXTUREATLAS_H_
