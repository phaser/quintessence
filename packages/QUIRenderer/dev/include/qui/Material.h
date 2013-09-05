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
#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_MATERIAL_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_MATERIAL_H_
#include <glm/glm.hpp>
#include <qui/IMaterial.h>
#include <qui/cpp11compat.h>

namespace qui
{
class GLShader;
class GLTexture;
class TextureAtlasModule;

class Material : public IMaterial
{
 public:
     Material()
         : color(1.f)
     {
     }
     void before();
     void after();
     inline void setShader(cpp0x::shared_ptr<GLShader> shader);
     inline void setTexture(cpp0x::shared_ptr<GLTexture> texture);
     inline void setTextureAtlasModule(cpp0x::shared_ptr<TextureAtlasModule> module);
     inline void setColor(glm::vec4 color);
     glm::vec2 getTexturePos() const;
     glm::vec2 getTextureSize() const;
     glm::vec2 getUVTopLeft() const;
     glm::vec2 getUVTopRight() const;
     glm::vec2 getUVBottomLeft() const;
     glm::vec2 getUVBottomRight() const;
     bool isRotated() const;
     cpp0x::shared_ptr<GLShader> getShader() const;
     cpp0x::shared_ptr<GLTexture> getTexture() const;
     cpp0x::shared_ptr<TextureAtlasModule> getAtlasModule() const;
 private:
     cpp0x::shared_ptr<GLShader> shader;
     cpp0x::shared_ptr<GLTexture> texture;
     cpp0x::shared_ptr<TextureAtlasModule> atlasModule;
     glm::vec4 color;
};

void Material::setShader(cpp0x::shared_ptr<GLShader> shader)
{
    this->shader = shader;
}

void Material::setTexture(cpp0x::shared_ptr<GLTexture> texture)
{
    this->texture = texture;
}

void Material::setColor(glm::vec4 color)
{
    this->color = color;
}

void Material::setTextureAtlasModule(cpp0x::shared_ptr<TextureAtlasModule> module)
{
    this->atlasModule = module;
}
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_MATERIAL_H_
