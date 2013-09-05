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

#include <qui/GLVertexBufferObject.h>
#include <qui/GLShader.h>
#include <qui/GLTexture.h>
#include <qui/RenderOptions.h>
#include <qui/IMaterial.h>
#include <qui/MaterialManager.h>
#include <qui/Material.h>

namespace qui
{
/* ======================================================================= *
 * Public Functions Implementation
 * ======================================================================= */
/**
 * Constructor.
 */
GLVertexBufferObject::GLVertexBufferObject(size_t materialId, bool hasColor)
    : vSize(0)
    , iSize(0)
    , vertices(NULL)
    , indices(NULL)
    , materialId(materialId)
    , hasColor(hasColor)
{
    qui::MaterialManager mm;
    cpp0x::shared_ptr<qui::IMaterial> material = mm.getMaterial(materialId);
    GLuint programObject = material->getShader()->getProgramObject();
    shaderVertexHandle = GL->getAttribLocation(programObject, qui::SHADER_VERTEX_POSITION);
    if (hasColor)
    {
        shaderColorHandle = GL->getAttribLocation(programObject, qui::SHADER_COLOR);
    }
    else
    {
        shaderTextureHandle = GL->getAttribLocation(programObject, qui::SHADER_TEXTURE_COORDS);
    }
}

/**
 * Destructor.
 */
GLVertexBufferObject::~GLVertexBufferObject()
{
    freeVertices();
    freeIndices();
}

/**
 * Buffers the data using VBOs
 */
void GLVertexBufferObject::prepareForPaint()
{
}

/**
 * Use to set the vertex data along with the normals (optional) and UV (optional)
 */
void GLVertexBufferObject::setVertices(GLfloat* vertices, GLuint size)
{
    freeVertices();
    this->vertices = vertices;
    this->vSize = size;
}

/**
 * Used to set the indices (optional). You can still call paint without calling
 * setIndices(...) first and the paint will just draw triangles from the vertex
 * buffer.
 */
void GLVertexBufferObject::setIndices(GLushort* indices, GLuint size)
{
    freeIndices();
    this->indices = indices;
    this->iSize = size;
}

/**
 * Draws the model using
 */
void GLVertexBufferObject::paint()
{
    GLuint stride = (hasColor ? 7 : 5);
    GL->enableVertexAttribArray(shaderVertexHandle);
    if (hasColor)
    {
        GL->enableVertexAttribArray(shaderColorHandle);
    }
    else
    {
        GL->enableVertexAttribArray(shaderTextureHandle);
    }

    // Load the vertex position
    GL->vertexAttribPointer(shaderVertexHandle
                        , 3
                        , GL_FLOAT
                        , GL_FALSE
                        , stride * sizeof(GLfloat)
                        , &vertices[0]);

    if (hasColor)
    {
        // Load the texture coordinate
        GL->vertexAttribPointer(shaderColorHandle
                              , 4
                              , GL_FLOAT
                              , GL_FALSE
                              , stride * sizeof(GLfloat)
                              , &vertices[3]);
    }
    else
    {
        // Load the texture coordinate
        GL->vertexAttribPointer(shaderTextureHandle
                              , 2
                              , GL_FLOAT
                              , GL_FALSE
                              , stride * sizeof(GLfloat)
                              , &vertices[3]);
    }
    GL->drawElements(GL_TRIANGLES, iSize, GL_UNSIGNED_SHORT, indices);
}

GLfloat*& GLVertexBufferObject::getVertices()
{
    return this->vertices;
}

/* ======================================================================= *
 * Private Functions Implementation
 * ======================================================================= */
/**
 * On the destructor of the model the vertices arrays are freed.
 */
void GLVertexBufferObject::freeVertices()
{
    if (this->vertices != NULL)
    {
        delete [] vertices;
    }
}

/**
 * On the destructor of the model the indices arrays are freed.
 */
void GLVertexBufferObject::freeIndices()
{
    if (indices != NULL)
    {
        delete [] indices;
    }
}
}  // namespace qui
