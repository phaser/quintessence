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
#include <qui/text/Label.h>
#include <qui/text/Font.h>
#include <qui/text/FontManager.h>
#include <qui/ObjectData.h>
#include <qui/GLVertexBufferObject.h>
#include <qui/TextureManager.h>
#include <qui/MaterialManager.h>
#include <qui/ShaderManager.h>
#include <qui/Material.h>
#include <qui/GLTexture.h>
#include <qui/GLShader.h>
#include <glm/gtc/type_ptr.hpp>
#include <qui/log.h>
#include <string>
#include "./Glyph.h"

namespace qui
{
namespace text
{
Label* Label::getObject(const std::string& text
                      , size_t fontId)
{
    FontManager fm;
    cpp0x::shared_ptr<Font> font = fm.getFont(fontId);
    Label* label = new Label(text, font);
    label->init();
    return label;
}

Label::~Label()
{
}

bool Label::init()
{
    qui::MaterialManager mm;
    cpp0x::shared_ptr<qui::IMaterial> fontMaterial = mm.getMaterial(HASH(font->getMaterial()));
    GLfloat texWidth = fontMaterial->getTexture()->getWidth();
    GLfloat texHeight = fontMaterial->getTexture()->getHeight();
    mm.addMaterial(font->getFontName(), fontMaterial);
    setMaterialId(qui::Hash(font->getFontName()).value);
    if (!vobj.get())
    {
        vobj = std::auto_ptr<GLVertexBufferObject>(new GLVertexBufferObject(getMaterialId()));
    }
    xoffset = 0;
    size_t sz = text.size();
    GLfloat* vertices = new GLfloat[20 * sz];
    GLushort* indices = new GLushort[6 * sz];
    memset(vertices, 0, sizeof(GLfloat) * 20 * sz);
    memset(indices, 0, sizeof(GLushort) * 6 * sz);
    cpp0x::shared_ptr<Glyph> glyph;
    size.x = 0;
    size.y = 0;
    for (size_t i = 0; i < sz; i++)
    {
        glyph = font->getGlyphForChar(text.at(i));
        size_t vIdxOffs = 20 * i;
        size_t iIdxOffs = 6 * i;
        size_t nvIdxOffs = 4 * i;
        size.y = glm::max(glyph->offset.y + glyph->size.y, size.y);  // NOLINT
        vertices[vIdxOffs +  0] = glyph->offset.x + xoffset;
        vertices[vIdxOffs +  1] = glyph->offset.y;
        vertices[vIdxOffs +  3] = glyph->position.x / texWidth;
        vertices[vIdxOffs +  4] = glyph->position.y / texHeight;
        vertices[vIdxOffs +  5] = xoffset + glyph->size.x;
        vertices[vIdxOffs +  6] = glyph->offset.y;
        vertices[vIdxOffs +  8] = (glyph->position.x + glyph->size.x) / texWidth;
        vertices[vIdxOffs +  9] = vertices[vIdxOffs +  4];
        vertices[vIdxOffs + 10] = vertices[vIdxOffs +  5];
        vertices[vIdxOffs + 11] = glyph->offset.y + glyph->size.y;
        vertices[vIdxOffs + 13] = vertices[vIdxOffs +  8];
        vertices[vIdxOffs + 14] = (glyph->position.y + glyph->size.y) / texHeight;
        vertices[vIdxOffs + 15] = glyph->offset.x + xoffset;
        vertices[vIdxOffs + 16] = glyph->offset.y + glyph->size.y;
        vertices[vIdxOffs + 18] = vertices[vIdxOffs +  3];
        vertices[vIdxOffs + 19] = vertices[vIdxOffs + 14];

        indices[iIdxOffs + 0] = nvIdxOffs + 0;
        indices[iIdxOffs + 1] = nvIdxOffs + 1;
        indices[iIdxOffs + 2] = nvIdxOffs + 2;
        indices[iIdxOffs + 3] = nvIdxOffs + 0;
        indices[iIdxOffs + 4] = nvIdxOffs + 2;
        indices[iIdxOffs + 5] = nvIdxOffs + 3;
        xoffset += glyph->xadvance;
    }
    size.x = xoffset - glyph->xadvance;
    size.x += glyph->size.x;
    vobj->setVertices(vertices, 20 * sz);
    vobj->setIndices(indices, 6 * sz);
    realign(glm::vec2(0.f, 0.f));
    return true;
}

Label::Label(const std::string& text
           , cpp0x::shared_ptr<Font> font)
    : IObject()
    , data(new Q2D::ObjectData())
    , text(text)
    , font(font)
    , xoffset(0)
    , matrixLoc(0)
{
}

/* IObject functions */

void Label::paint()
{
    if (vobj.get() == NULL)
    {
        return;
    }

    qui::MaterialManager mm;
    cpp0x::shared_ptr<qui::IMaterial> material = mm.getMaterial(data->material);
    material->before();
    glUniformMatrix4fv(matrixLoc, 1, false, glm::value_ptr(data->modelview));
    vobj->paint();
    material->after();
}

void Label::setPosition(const glm::vec2& pos)
{
    data->setPosition(pos);
}

bool Label::getHasUpdate() const
{
    return data->hasUpdate;
}

void Label::setHasUpdate(bool update)
{
    data->hasUpdate = update;
}

bool Label::isVisible() const
{
    return data->visible;
}

void Label::setVisible(bool visible)
{
    data->visible = visible;
}

glm::vec2& Label::getPosition()
{
    return data->position;
}

void Label::setRotationAngle(float angle)
{
    data->setRotationAngle(angle);
}

float Label::getRotationAngle() const
{
    return data->rotationAngle;
}

void Label::setAnchorPoint(const glm::vec2& anchor)
{
    glm::vec2 oldAnchor = data->anchorPoint;
    data->anchorPoint = anchor;
    realign(oldAnchor);
}

glm::vec2& Label::getAnchorPoint()
{
    return data->anchorPoint;
}

void Label::update(uint64_t /*dt*/)
{
}

inline void Label::setMaterialId(size_t material)
{
    data->material = material;
    qui::MaterialManager mm;
    cpp0x::shared_ptr<qui::IMaterial> mat = mm.getMaterial(data->material);
    if (mat.get() == NULL)
    {
        LOG(LERROR) << "Coudn't find material " << data->material << ".";
        return;
    }
    matrixLoc = glGetUniformLocation(mat->getShader()->getProgramObject()
                                   , qui::SHADER_PROJECTION_MODEL_VIEW_MATRIX);
}

inline size_t Label::getMaterialId() const
{
    return data->material;
}
/* END IObject Functions */


void Label::realign(glm::vec2 oldAnchor)
{
    GLfloat* vertices = vobj->getVertices();
    if (vertices == NULL)
    {
        return;
    }
    size_t sz = text.size();

    /* Adjusting consindering the anchor point */
    for (size_t i = 0; i < sz; i++)
    {
        size_t vIdxOffs = 20 * i;
        vertices[vIdxOffs +  0] = vertices[vIdxOffs +  0]
                                    + (size.x * oldAnchor.x)
                                    - (size.x * getAnchorPoint().x);
        vertices[vIdxOffs +  1] = vertices[vIdxOffs +  1]
                                    + (size.y * oldAnchor.y)
                                    - (size.y * getAnchorPoint().y);
        vertices[vIdxOffs +  5] = vertices[vIdxOffs +  5]
                                    + (size.x * oldAnchor.x)
                                    - (size.x * getAnchorPoint().x);
        vertices[vIdxOffs +  6] = vertices[vIdxOffs +  6]
                                    + (size.y * oldAnchor.y)
                                    - (size.y * getAnchorPoint().y);
        vertices[vIdxOffs + 10] = vertices[vIdxOffs +  5];
        vertices[vIdxOffs + 11] = vertices[vIdxOffs + 11]
                                    + (size.y * oldAnchor.y)
                                    - (size.y * getAnchorPoint().y);
        vertices[vIdxOffs + 15] = vertices[vIdxOffs + 15]
                                    + (size.x * oldAnchor.x)
                                    - (size.x * getAnchorPoint().x);
        vertices[vIdxOffs + 16] = vertices[vIdxOffs + 16]
                                    + (size.y * oldAnchor.y)
                                    - (size.y * getAnchorPoint().y);
    }
}
}  // namespace text
}  // namespace qui
