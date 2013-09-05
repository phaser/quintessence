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

#include <qui/GLTexture.h>
#include <qui/RenderOptions.h>
#include <qui/Image.h>
#include <qui/GLShader.h>

namespace qui
{
GLTexture::GLTexture(Image& img)  // NOLINT
    : textureId(0)
{
    GL->genTextures(1, &this->textureId);
    GL->pixelStorei(GL_UNPACK_ALIGNMENT, 1);
    GL->bindTexture(GL_TEXTURE_2D, this->textureId);
    cpp0x::shared_ptr<unsigned char> imgData = img.getImageData();
    this->width = img.getWidth();
    this->height = img.getHeight();
    this->format = img.getImageDataFormat();
    GL->texImage2D(GL_TEXTURE_2D
                 , 0
                 , this->getFormat()
                 , this->getWidth()
                 , this->getHeight()
                 , 0
                 , this->getFormat()
                 , GL_UNSIGNED_BYTE
                 , static_cast<GLubyte*>(imgData.get()));
    GL->texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GL->texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GLTexture::~GLTexture()
{
}

void GLTexture::enable(const GLShader& shader)
{
    GL->activeTexture(GL_TEXTURE0);
    GL->bindTexture(GL_TEXTURE_2D, this->textureId);
    GL->uniform1i(shader.getSamplerLocation(), 0);
}

GLuint GLTexture::getTextureId()
{
    return textureId;
}
}  // namespace qui
