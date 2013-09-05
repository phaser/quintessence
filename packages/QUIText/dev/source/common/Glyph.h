// Copyright (C) 2013 Cristian Bidea
// This file is part of QUIText.
//
//    QUIText is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIText is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIText.  If not, see <http://www.gnu.org/licenses/>.
#ifndef PACKAGES_QUI_QUITEXT_DEV_SOURCE_COMMON_GLYPH_H_
#define PACKAGES_QUI_QUITEXT_DEV_SOURCE_COMMON_GLYPH_H_

#include <stdint.h>
#include <glm/glm.hpp>

struct Glyph
{
    Glyph()
        : charId(0)
        , position(glm::vec2(0.f, 0.f))
        , size(glm::vec2(0.f, 0.f))
        , offset(glm::vec2(0.f, 0.f))
        , xadvance(0)
    {
    }
    int32_t charId;
    glm::vec2 position;
    glm::vec2 size;
    glm::vec2 offset;
    int8_t xadvance;
};
#endif  // PACKAGES_QUI_QUITEXT_DEV_SOURCE_COMMON_GLYPH_H_
