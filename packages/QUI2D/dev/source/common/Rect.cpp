// Copyright (C) 2013 Cristian Bidea
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
#include <qui/Rect.h>
#include <qui/Hash.h>
#include <qui/ObjectData.h>
#include <qui/GLVertexBufferObject.h>
#include <qui/ShaderManager.h>
#include <qui/MaterialManager.h>
#include <qui/IMaterial.h>
#include <qui/RenderOptions.h>
#include <glm/gtc/type_ptr.hpp>
#include <qui/log.h>

namespace qui
{
namespace Q2D
{
Rect::Rect()
    : IObject()
{
}

Rect* Rect::getObject(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color)
{
    Rect *result = new Rect();
    if (!result)
    {
        LOG(LERROR) << "Could not allocate object of type qui::Q2D::Rect!";
        return NULL;
    }

    result->data = std::auto_ptr<ObjectData>(new ObjectData());
    if (!(result->data.get()))
    {
        LOG(LERROR) << "Could not allocate data<ObjectData>.";
        return NULL;
    }

    result->vObj = std::auto_ptr<GLVertexBufferObject>(
            new GLVertexBufferObject(qui::Hash(qui::Q2D::COLOR_SHADER).value, true));
    if (!result->vObj.get())
    {
        LOG(LERROR) << "Could not allocate vertexBufferObject!";
        return NULL;
    }

    const GLuint vsize = 28;
    const GLuint isize = 6;
    GLfloat vert[vsize] = {  // NOLINT
                        p1.x, p1.y, 0.f
                      , color[0], color[1], color[2], color[3]
                      , p2.x, p1.y, 0.f
                      , color[0], color[1], color[2], color[3]
                      , p2.x, p2.y, 0.f
                      , color[0], color[1], color[2], color[3]
                      , p1.x, p2.y, 0.f
                      , color[0], color[1], color[2], color[3]
                       };
    GLushort ind[isize] = {0, 1, 2, 2, 3, 0};  // NOLINT
    GLfloat *vertices = new GLfloat[vsize];
    if (!vertices)
    {
        LOG(LERROR) << "Allocation error!";
        return NULL;
    }
    GLushort *indices = new GLushort[isize];
    if (!indices)
    {
        delete [] vertices;
        LOG(LERROR) << "Allocation error!";
        return NULL;
    }
    memcpy(vertices, &vert, vsize*sizeof(GLfloat));
    memcpy(indices, &ind, isize*sizeof(GLushort));
    result->vObj->setVertices(vertices, vsize);
    result->vObj->setIndices(indices, isize);

    result->setMaterialId(qui::Hash(COLOR_SHADER).value);
    return result;
}

void Rect::paint()
{
    qui::ShaderManager sm;
    qui::MaterialManager mm;
    cpp0x::shared_ptr<qui::IMaterial> material = mm.getMaterial(data->material);
    material->before();
    GLuint programObject = sm.getShader(qui::Hash(qui::Q2D::COLOR_SHADER).value)->getProgramObject();
    int matrixLoc = GL->getUniformLocation(programObject, qui::SHADER_PROJECTION_MODEL_VIEW_MATRIX);
    GL->uniformMatrix4fv(matrixLoc, 1, false, glm::value_ptr(data->modelview));
    vObj->paint();
    material->after();
}

void Rect::setPosition(const glm::vec2& pos)
{
    data->setPosition(pos);
}

void Rect::setAnchorPoint(const glm::vec2& anchor)
{
    data->anchorPoint = anchor;
}

bool Rect::getHasUpdate() const
{
    return data->hasUpdate;
}

void Rect::setHasUpdate(bool update)
{
    data->hasUpdate = update;
}

bool Rect::isVisible() const
{
    return data->visible;
}

void Rect::setVisible(bool visible)
{
    data->visible = visible;
}

void Rect::update(uint64_t /*dt*/)
{
}

glm::vec2& Rect::getPosition()
{
    return data->position;
}

void Rect::setRotationAngle(float angle)
{
    data->setRotationAngle(angle);
}

float Rect::getRotationAngle() const
{
    return data->rotationAngle;
}

glm::vec2& Rect::getAnchorPoint()
{
    return data->anchorPoint;
}

void Rect::setMaterialId(size_t material)
{
    data->material = material;
}

size_t Rect::getMaterialId() const
{
    return data->material;
}

}  // namespace Q2D
}  // namespace qui
