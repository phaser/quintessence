// Copyright (C) 2012 Cristian Bidea
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

#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_CAMERA_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_CAMERA_H_
#include <GLES2/gl2.h>
#include <glm/glm.hpp>

namespace qui
{
class Camera
{
 public:
    Camera(GLfloat l
         , GLfloat r
         , GLfloat t
         , GLfloat b
         , GLfloat n
         , GLfloat f)
        : l(l)
        , r(r)
        , t(t)
        , b(b)
        , n(n)
        , f(f)
    {
    }
    virtual ~Camera()
    {
    }
    virtual glm::mat4* getProjectionMatrix() = 0;
    static void setActiveCamera(Camera* defaultCamera);
    static Camera* getActiveCamera();
 protected:
    GLfloat l;
    GLfloat r;
    GLfloat t;
    GLfloat b;
    GLfloat n;
    GLfloat f;
 private:
    static Camera *activeCamera;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_CAMERA_H_
