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
#ifndef PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_IOBJECT_H_
#define PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_IOBJECT_H_

#include <glm/glm.hpp>
#include <stdint.h>
/** namespace qui
  * @brief qui is the namespace for the entire project
  */
namespace qui
{
/** namespace Q2D
  * @brief Q2D is the namespace for the 2D engine.
  */
namespace Q2D
{
const char TEXTURED_SHADER[] = "qui::Q2D::textured";
const char COLOR_SHADER[] = "qui::Q2D::color";
/** class Object
 * @brief Object is the root class for every object that can be added to a scene.
 */
class IObject
{
 public:
    virtual ~IObject()
    {
    }
    virtual bool getHasUpdate() const = 0;
    virtual void setHasUpdate(bool update) = 0;
    virtual bool isVisible() const = 0;
    virtual void setVisible(bool visible) = 0;
    virtual void update(uint64_t dt) = 0;
    virtual void paint() = 0;
    virtual void setPosition(const glm::vec2& pos) = 0;
    virtual glm::vec2& getPosition() = 0;
    virtual void setRotationAngle(float angle) = 0;
    virtual float getRotationAngle() const = 0;
    virtual void setAnchorPoint(const glm::vec2& anchor) = 0;
    virtual glm::vec2& getAnchorPoint() = 0;
    virtual void setMaterialId(size_t material) =0;
    virtual size_t getMaterialId() const =0;
};
}  // namespace 2D
}  // namespace qui
#endif  // PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_IOBJECT_H_
