/** 
 * @file OrthoCamera.h
 * @author Cristian Bidea
 * @copyright 2012 Cristian Bidea
 *
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

#ifndef PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_ORTHOCAMERA_H_
#define PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_ORTHOCAMERA_H_
#include <qui/Camera.h>
#include <glm/glm.hpp>
namespace qui
{
class OrthoCamera : public Camera
{
 public:
    OrthoCamera(GLfloat l
              , GLfloat r
              , GLfloat t
              , GLfloat b
              , GLfloat n
              , GLfloat f);
    ~OrthoCamera();
    glm::mat4* getProjectionMatrix();
 private:
    glm::mat4 projectionMatrix;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUI2D_DEV_INCLUDE_QUI_ORTHOCAMERA_H_
