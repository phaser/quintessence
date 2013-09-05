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
#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_IMATERIAL_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_IMATERIAL_H_
#include <qui/cpp11compat.h>
#include <glm/glm.hpp>
namespace qui
{
class GLShader;
class GLTexture;
class IMaterial
{
    public:
        virtual ~IMaterial()
        {
        }
        virtual void before() =0;
        virtual void after() =0;
        virtual cpp0x::shared_ptr<GLShader> getShader() const =0;
        virtual cpp0x::shared_ptr<GLTexture> getTexture() const =0;
        virtual glm::vec2 getTexturePos() const =0;
        virtual glm::vec2 getTextureSize() const =0;
        virtual glm::vec2 getUVTopLeft() const =0;
        virtual glm::vec2 getUVBottomRight() const =0;
        virtual bool isRotated() const =0;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_IMATERIAL_H_
