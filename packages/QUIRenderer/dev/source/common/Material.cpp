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
#include <qui/Material.h>
#include <qui/ShaderManager.h>
#include <qui/TextureManager.h>
#include <qui/RenderOptions.h>
#include <qui/TextureAtlasModule.h>
#include <qui/GLTexture.h>
#include <qui/GLShader.h>

namespace qui
{
void Material::before()
{
    getShader()->useProgram();
    if (getTexture().get())
    {
        if (getTexture()->getFormat() == GL_RGBA)
        {
            GL->enable(GL_BLEND);
            GL->blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        getTexture()->enable(*(this->shader.get()));
    }
}

void Material::after()
{
}

cpp0x::shared_ptr<GLShader> Material::getShader() const
{
    return this->shader;
}

cpp0x::shared_ptr<GLTexture> Material::getTexture() const
{
    return this->texture;
}

cpp0x::shared_ptr<TextureAtlasModule> Material::getAtlasModule() const
{
    return this->atlasModule;
}

glm::vec2 Material::getTexturePos() const
{
    if (getAtlasModule().get())
    {
        glm::vec2 result = getAtlasModule()->pos;
        return result;
    }
    return glm::vec2(0.f, 0.f);
}

glm::vec2 Material::getTextureSize() const
{
    if (getAtlasModule().get())
    {
        glm::vec2 sz = getAtlasModule()->size;
        if (getAtlasModule()->rotated)
        {
            float p = sz.x;
            sz.x = sz.y;
            sz.y = p;
        }
        return sz;
    }
    else if (getTexture().get())
    {
        return glm::vec2(getTexture()->getWidth(), getTexture()->getHeight());
    }
    return glm::vec2(0.f, 0.f);
}

glm::vec2 Material::getUVTopLeft() const
{
    if (getAtlasModule().get())
    {
        glm::vec2 uvtopl = getAtlasModule()->pos;
        uvtopl /= glm::vec2(getTexture()->getWidth(), getTexture()->getHeight());
        return uvtopl;
    }
    return glm::vec2(0.f, 0.f);
}

glm::vec2 Material::getUVBottomRight() const
{
    if (getAtlasModule().get())
    {
        glm::vec2 uvbr = (getAtlasModule()->pos + getAtlasModule()->size);
        uvbr /= glm::vec2(getTexture()->getWidth(), getTexture()->getHeight());
        return uvbr;
    }
    return glm::vec2(1.f, 1.f);
}

bool Material::isRotated() const
{
    if (getAtlasModule().get())
    {
        return getAtlasModule()->rotated;
    }
    return false;
}
}  // namespace qui
