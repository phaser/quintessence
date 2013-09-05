/** 
 * @file OrthoCamera.cpp
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
#include <qui/OrthoCamera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace qui
{
OrthoCamera::OrthoCamera(GLfloat l
              , GLfloat r
              , GLfloat t
              , GLfloat b
              , GLfloat n
              , GLfloat f)
    : Camera(l, r, t, b, n, f)
{
    projectionMatrix = glm::ortho(l, r, b, t, n, f);
}

OrthoCamera::~OrthoCamera()
{
}

glm::mat4* OrthoCamera::getProjectionMatrix()
{
    return &projectionMatrix;
}
}  // namespace qui
