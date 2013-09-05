// Copyright (C) 2012 Cristian Bidea
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
#include <qui/ObjectData.h>
#include <qui/Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <qui/Hash.h>

namespace qui
{
namespace Q2D
{
ObjectData::ObjectData()
    : position(glm::vec2(0.f, 0.f))
    , rotationAngle(0.f)
    , hasUpdate(false)
    , visible(true)
    , anchorPoint(glm::vec2(0.5f, 0.5f))
    , material(Hash(qui::Q2D::DEFAULT_MATERIAL).value)
{
    updateModelViewMatrix();
}
/** @brief Setter for ObjectData::rotationAngle */
void ObjectData::setRotationAngle(float angle)
{
    this->rotationAngle = angle;
    this->updateModelViewMatrix();
}

/** 
 *
 */
void ObjectData::setPosition(const glm::vec2& pos)
{
    position = pos;
    this->updateModelViewMatrix();
}

/** @brief Updates the model view matrix everytime position, rotation or scale
 *         are changed.
 *  @return void
 */
void ObjectData::updateModelViewMatrix()
{
    modelview = glm::mat4(1.f);
    modelview = glm::rotate(modelview
                          , this->rotationAngle
                          , glm::vec3(0.f, 0.f, 1.f));
    modelview = glm::translate(glm::mat4(1.f)
                             , glm::vec3(position.x, position.y, 0.f))
                * modelview;
    modelview = *(Camera::getActiveCamera()->getProjectionMatrix()) * modelview;
}
}  // namespace Q2D
}  // namespace qui
