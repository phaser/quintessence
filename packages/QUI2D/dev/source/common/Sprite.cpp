// Copyright (c) 2012 Cristian Bidea
/** 
 * This file is part of QUI2D.
 *
 *    QUI2D is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published
 *    by the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    QUI2D is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with QUI2D.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <qui/Sprite.h>
#include <qui/GLVertexBufferObject.h>
#include <qui/GLTexture.h>
#include <qui/GLShader.h>
#include <qui/ObjectData.h>
#include <glm/gtc/type_ptr.hpp>
#include <qui/MaterialManager.h>
#include <qui/Material.h>
#include <qui/log.h>

namespace qui
{
namespace Q2D
{
/* ========================================================================*
 *  Public functions implementation
 * ========================================================================*/
Sprite::Sprite(size_t materialId)
    : IObject()
    , data(new ObjectData())
{
    if (materialId != 0xFFFFFFFF)
    {
        setMaterialId(materialId);
    }
    else
    {
        setMaterialId(qui::Hash(TEXTURED_SHADER).value);
    }
}

Sprite::~Sprite()
{
}

bool Sprite::init()
{
    qui::MaterialManager mm;
    cpp0x::shared_ptr<qui::IMaterial> material = mm.getMaterial(data->material);
    if (material.get() == NULL)
    {
        LOG(LERROR) << "Coudn't find material " << data->material << ".";
        return false;
    }
    vobj = std::auto_ptr<GLVertexBufferObject>(new qui::GLVertexBufferObject(data->material));
    vobj->setVertices(this->getVertices(), 20);
    vobj->setIndices(this->getIndices(), 6);
    vobj->prepareForPaint();
    return true;
}

void Sprite::paint()
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

void Sprite::setPosition(const glm::vec2& pos)
{
    data->setPosition(pos);
}

bool Sprite::getHasUpdate() const
{
    return data->hasUpdate;
}

void Sprite::setHasUpdate(bool update)
{
    data->hasUpdate = update;
}

bool Sprite::isVisible() const
{
    return data->visible;
}

void Sprite::setVisible(bool visible)
{
    data->visible = visible;
}

glm::vec2& Sprite::getPosition()
{
    return data->position;
}

void Sprite::setRotationAngle(float angle)
{
    data->setRotationAngle(angle);
}

float Sprite::getRotationAngle() const
{
    return data->rotationAngle;
}

glm::vec2& Sprite::getAnchorPoint()
{
    return data->anchorPoint;
}

void Sprite::update(uint64_t /*dt*/)
{
}

inline void Sprite::setMaterialId(size_t material)
{
    data->material = material;
    qui::MaterialManager mm;
    cpp0x::shared_ptr<qui::IMaterial> mat = mm.getMaterial(data->material);
    if (mat.get() == NULL)
    {
        LOG(LERROR) << "Coudn't found material " << data->material << ".";
        return;
    }
    matrixLoc = glGetUniformLocation(mat->getShader()->getProgramObject()
                                   , qui::SHADER_PROJECTION_MODEL_VIEW_MATRIX);
    init();
}

inline size_t Sprite::getMaterialId() const
{
    return data->material;
}

/* ========================================================================*
 *  Private functions implementation
 * ========================================================================*/
GLfloat* Sprite::getVertices()
{
    qui::MaterialManager mm;
    cpp0x::shared_ptr<qui::IMaterial> material = mm.getMaterial(data->material);
    if (material.get() == NULL)
    {
        LOG(LERROR) << "Material " << data->material << " not loaded.";
        return NULL;
    }

    GLfloat *vertices = new GLfloat[20];

    vertices[0]  = vertices[1]  = vertices[2]  = 0.0f;
    vertices[3]  = 0.0f; vertices[4] = 0.0f;  // NOLINT
    vertices[5]  = vertices[6]  = vertices[7]  = 0.0f;
    vertices[8]  = 1.0f; vertices[9] = 0.0f;  // NOLINT
    vertices[10] = vertices[11] = vertices[12] = 0.0f;
    vertices[13] = 1.0f; vertices[14] = 1.0f;  // NOLINT
    vertices[15] = vertices[16] = vertices[17] = 0.0f;
    vertices[18] = 0.0f; vertices[19] = 1.0f;  // NOLINT

    float width = material->getTextureSize().x;
    float height = material->getTextureSize().y;
    float ancw = this->getAnchorPoint().x * width;
    float anch = this->getAnchorPoint().y * height;
    vertices[0] = 0.f - ancw;
    vertices[1] = 0.f - anch;
    vertices[5] = width - ancw;
    vertices[6] = 0.f - anch;
    vertices[10] = width - ancw;
    vertices[11] = height - anch;
    vertices[15] = 0.f - ancw;
    vertices[16] = height - anch;

    // UV mapping
    if (!material->isRotated())
    {
        vertices[3]  = material->getUVTopLeft().x;
        vertices[4]  = material->getUVTopLeft().y;
        vertices[8]  = material->getUVBottomRight().x;
        vertices[9]  = vertices[4];
        vertices[13] = vertices[8];
        vertices[14] = material->getUVBottomRight().y;
        vertices[18] = vertices[3];
        vertices[19] = vertices[14];
    }
    else
    {
        vertices[3]  = material->getUVBottomRight().x;
        vertices[4]  = material->getUVTopLeft().y;
        vertices[8]  = material->getUVBottomRight().x;
        vertices[9]  = material->getUVBottomRight().y;
        vertices[13] = material->getUVTopLeft().x;
        vertices[14] = material->getUVBottomRight().y;
        vertices[18] = material->getUVTopLeft().x;
        vertices[19] = material->getUVTopLeft().y;
    }
    return vertices;
}

GLushort* Sprite::getIndices()
{
    GLushort *indices = new GLushort[6];
    indices[0] = 0; indices[1] = 1; indices[2] = 2;  // NOLINT
    indices[3] = 0; indices[4] = 2; indices[5] = 3;  // NOLINT
    return indices;
}

void Sprite::setAnchorPoint(const glm::vec2& anchor)
{
    data->anchorPoint = anchor;
    vobj->setVertices(this->getVertices(), 20);
}
}  // namespace Q2D
}  // namespace qui
