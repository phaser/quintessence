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

#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_GLVERTEXBUFFEROBJECT_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_GLVERTEXBUFFEROBJECT_H_

#include <GLES2/gl2.h>
#include <qui/GLShader.h>
#include <string>

namespace qui
{
class GLTexture;

class GLVertexBufferObject
{
 public:
    GLVertexBufferObject(size_t materialId, bool hasColor = false);
    ~GLVertexBufferObject();
    void prepareForPaint();
    void setVertices(GLfloat* vertices, GLuint size);
    GLfloat*& getVertices();
    void setIndices(GLushort* indices, GLuint size);
    void paint();
 protected:
    GLuint shaderVertexHandle;
    GLuint shaderTextureHandle;
    GLuint shaderColorHandle;
    GLuint vertexStride;
    GLuint vSize;
    GLuint iSize;
    GLfloat* vertices;
    GLushort* indices;
    GLuint vertexVBOHandle;
    GLuint indexVBOHandle;
 private:
    void freeVertices();
    void freeIndices();
    size_t materialId;
    GLTexture* texture;
    bool hasColor;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_GLVERTEXBUFFEROBJECT_H_
