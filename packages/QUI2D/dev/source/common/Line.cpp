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
#include <qui/Line.h>
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
Line::Line()
    : IObject()
{
}

Line* Line::getObject(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color, float thick)
{
    Line *result = new Line();
    if (!result)
    {
        LOG(LERROR) << "Could not allocate object of type qui::Q2D::Line!";
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
    GLfloat x1 = p1.x;
    GLfloat y1 = p1.y;
    GLfloat x2 = p2.x;
    GLfloat y2 = p2.y;
    GLfloat t = thick / 2;
    GLfloat d = glm::sqrt(glm::pow<GLfloat>((x2 - x1), 2)
                                 + glm::pow<GLfloat>((y2 - y1), 2));
    GLfloat dx = glm::abs<GLfloat>(x2 - x1);
    GLfloat dy = glm::abs<GLfloat>(y2 - y1);

    GLfloat xn =  (dy * t) / d;
    GLfloat yn = -(dx * t) / d;
    const GLuint vsize = 42;
    const GLuint isize = 12;
    GLfloat vert[vsize] =  {  // NOLINT
                             x1, y1, 0.f
                           , color[0], color[1], color[2], color[3]
                           , x1 + xn, y1 + yn, 0.f
                           , color[0], color[1], color[2], 0.f
                           , x2 + xn, y2 + yn, 0.f
                           , color[0], color[1], color[2], 0.f
                           , x2, y2, 0.f
                           , color[0], color[1], color[2], color[3]
                           , x2 - xn, y2 - yn, 0.f
                           , color[0], color[1], color[2], 0.f
                           , x1 - xn, y1 - yn, 0.f
                           , color[0], color[1], color[2], 0.f
                        };
    GLushort ind[isize] = {2, 3, 0, 1, 2, 0, 3, 4, 5, 5, 0, 3};  // NOLINT
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

void Line::paint()
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

void Line::setPosition(const glm::vec2& pos)
{
    data->setPosition(pos);
}

void Line::setAnchorPoint(const glm::vec2& anchor)
{
    data->anchorPoint = anchor;
}

bool Line::getHasUpdate() const
{
    return data->hasUpdate;
}

void Line::setHasUpdate(bool update)
{
    data->hasUpdate = update;
}

bool Line::isVisible() const
{
    return data->visible;
}

void Line::setVisible(bool visible)
{
    data->visible = visible;
}

void Line::update(uint64_t /*dt*/)
{
}

glm::vec2& Line::getPosition()
{
    return data->position;
}

void Line::setRotationAngle(float angle)
{
    data->setRotationAngle(angle);
}

float Line::getRotationAngle() const
{
    return data->rotationAngle;
}

glm::vec2& Line::getAnchorPoint()
{
    return data->anchorPoint;
}

void Line::setMaterialId(size_t material)
{
    data->material = material;
}

size_t Line::getMaterialId() const
{
    return data->material;
}

}  // namespace Q2D
}  // namespace qui
