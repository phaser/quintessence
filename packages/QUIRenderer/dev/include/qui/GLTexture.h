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

#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_GLTEXTURE_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_GLTEXTURE_H_

#include <GLES2/gl2.h>
#include <string>

namespace qui
{
class Image;
class GLShader;

class GLTexture
{
 public:
    explicit GLTexture(Image& img);  // NOLINT
    ~GLTexture();
    void enable(const GLShader& shader);
    GLuint getTextureId();

    inline GLuint getWidth() const
    {
        return this->width;
    }

    inline GLuint getHeight() const
    {
        return this->height;
    }

    inline GLuint getFormat() const
    {
        return this->format;
    }
 private:
    GLuint textureId;
    GLuint width;
    GLuint height;
    GLuint format;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_GLTEXTURE_H_
