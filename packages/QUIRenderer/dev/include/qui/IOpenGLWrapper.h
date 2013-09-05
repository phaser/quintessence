// Copyright(C) 2012 Cristian Bidea
// This file is part of QUIRenderer.
//
//    QUIRenderer is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//    QUIRenderer is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIRenderer.  If not, see <http://www.gnu.org/licenses/>.

#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_IOPENGLWRAPPER_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_IOPENGLWRAPPER_H_

#include <GLES2/gl2.h>
#include <string>

namespace qui
{
class IOpenGLWrapper
{
 public:
    virtual ~IOpenGLWrapper()
    {
    }
    virtual void activeTexture(GLenum texture) =0;
    virtual void attachShader(GLuint program, GLuint shader) const =0;
    virtual void bindAttribLocation(GLuint program, GLuint index, const char* name) const =0;
    virtual void bindBuffer(GLenum target, GLuint buffer) const =0;
    virtual void bindTexture(GLenum target, GLuint texture) const =0;
    virtual void bufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) const =0;
    virtual void compileShader(GLuint shader) const =0;
    virtual GLuint createShader(GLenum type) const =0;
    virtual GLuint createProgram(void) const =0;
    virtual void deleteProgram(GLuint program) const =0;
    virtual void deleteShader(GLuint shader) const =0;
    virtual void drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) const =0;
    virtual void enable(GLenum cap) =0;
    virtual void blendFunc(GLenum sfactor, GLenum dfactor) const =0;
    virtual void disable(GLenum cap) =0;
    virtual void enableVertexAttribArray(GLuint index) const =0;
    virtual void genBuffers(GLsizei n, GLuint* buffers) const =0;
    virtual void genTextures(GLsizei n, GLuint* textures) const =0;
    virtual int  getAttribLocation(GLuint program, const char* name) const =0;
    virtual void getProgramiv(GLuint program, GLenum pname, GLint* params) const =0;
    virtual void getProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog) const =0;
    virtual void getShaderiv(GLuint shader, GLenum pname, GLint* params) const =0;
    virtual void getShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog) const =0;
    virtual int getUniformLocation(GLuint program, const char* name) const =0;
    virtual void linkProgram(GLuint program) const =0;
    virtual void pixelStorei(GLenum pname, GLint param) const =0;
    virtual void shaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length) const =0;
    virtual void texImage2D(GLenum target
                           , GLint level
                           , GLint internalformat
                           , GLsizei width
                           , GLsizei height
                           , GLint border
                           , GLenum format
                           , GLenum type
                           , const void* pixels) =0;
    virtual void texParameteri(GLenum target, GLenum pname, GLint param) const =0;
    virtual void uniform1i(GLint location, GLint x) const =0;
    virtual void uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) const =0;
    virtual void useProgram(GLuint program) =0;
    virtual void vertexAttribPointer(GLuint indx
                                   , GLint size
                                    , GLenum type
                                    , GLboolean normalized
                                    , GLsizei stride
                                    , const void* ptr) const =0;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_IOPENGLWRAPPER_H_
