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
#ifndef PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_OBJECTDATA_H_
#define PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_OBJECTDATA_H_
#include <glm/glm.hpp>
namespace qui
{
namespace Q2D
{
const char DEFAULT_MATERIAL[] = "qui::Q2D::DefaultMaterial";
struct ObjectData
{
    glm::mat4 modelview;
    /** @brief Position of the object */
    glm::vec2 position;
    /** @brief The rotation angle of this object */
    float rotationAngle;
    /** @brief Defines wheater the Object::Update(unsigned long dt) function will be called. */
    bool hasUpdate;
    /** @brief Defines if this object is visible or not*/
    bool visible;
    /** @brief The anchor point around which the rotation and scalling happen. */
    glm::vec2 anchorPoint;
    /** @brief ID of the material being used by this object */
    size_t material;
    ObjectData();
    void updateModelViewMatrix();
    void setRotationAngle(float angle);
    void setPosition(const glm::vec2& pos);
};
}  // namespace Q2D
}  // namespace qui
#endif  // PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_OBJECTDATA_H_
