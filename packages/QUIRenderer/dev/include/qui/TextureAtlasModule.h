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
#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_TEXTUREATLASMODULE_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_TEXTUREATLASMODULE_H_
#include <glm/glm.hpp>
#include <string>
namespace qui
{
struct TextureAtlasModule
{
    public:
        std::string name;
        unsigned int textureId;
        glm::vec2 pos;
        glm::vec2 size;
    /*
        glm::vec2 oPos;
        glm::vec2 oSize;
     */
        bool rotated;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_TEXTUREATLASMODULE_H_
