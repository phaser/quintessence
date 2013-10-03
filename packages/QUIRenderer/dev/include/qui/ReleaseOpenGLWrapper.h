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

#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_RELEASEOPENGLWRAPPER_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_RELEASEOPENGLWRAPPER_H_
#include <qui/IOpenGLWrapper.h>
#include <string>
#include <stdint.h>

namespace qui
{
enum OpenGLCapabilities
{
    GLW_GL_BLEND = 1 << 0
};

class ReleaseOpenGLWrapper : public IOpenGLWrapper
{
 public:
     ReleaseOpenGLWrapper()
         : currentActiveTexture(0xFFFFFFFF)
         , currentProgram(0xFFFFFFFF)
         , enabledCap(0)
     {
     }
     inline void activeTexture(GLenum texture);
     inline void attachShader(GLuint program, GLuint shader) const;
     inline void bindAttribLocation(GLuint program, GLuint index, const char* name) const;
     inline void bindBuffer(GLenum target, GLuint buffer) const;
     inline void bindTexture(GLenum target, GLuint texture) const;
     inline void bufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) const;
     inline void compileShader(GLuint shader) const;
     inline GLuint createShader(GLenum type) const;
     inline GLuint createProgram(void) const;
     inline void deleteProgram(GLuint program) const;
     inline void deleteShader(GLuint shader) const;
     inline void drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) const;
     inline void enable(GLenum cap);
     inline void blendFunc(GLenum sfactor, GLenum dfactor) const;
     inline void disable(GLenum cap);
     inline void enableVertexAttribArray(GLuint index) const;
     inline void genBuffers(GLsizei n, GLuint* buffers) const;
     inline void genTextures(GLsizei n, GLuint* textures) const;
     inline int  getAttribLocation(GLuint program, const char* name) const;
     inline void getProgramiv(GLuint program, GLenum pname, GLint* params) const;
     inline void getProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog) const;
     inline void getShaderiv(GLuint shader, GLenum pname, GLint* params) const;
     inline void getShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog) const;
     inline int  getUniformLocation(GLuint program, const char* name) const;
     inline void linkProgram(GLuint program) const;
     inline void pixelStorei(GLenum pname, GLint param) const;
     inline void shaderSource(GLuint shader, GLsizei count, const char** string, const GLint* length) const;
     inline void texImage2D(GLenum target
                           , GLint level
                           , GLint internalformat
                           , GLsizei width
                           , GLsizei height
                           , GLint border
                           , GLenum format
                           , GLenum type
                           , const void* pixels);
     inline void texParameteri(GLenum target, GLenum pname, GLint param) const;
     inline void uniform1i(GLint location, GLint x) const;
     inline void uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) const;
     inline void useProgram(GLuint program);
     inline void vertexAttribPointer(GLuint indx
                                    , GLint size
                                    , GLenum type
                                    , GLboolean normalized
                                    , GLsizei stride
                                    , const void* ptr) const;

 private:
     GLenum currentActiveTexture;
     GLuint currentProgram;
     uint32_t enabledCap;
};
}  // namespace qui

void qui::ReleaseOpenGLWrapper::activeTexture(GLenum texture)
{
    if (texture == currentActiveTexture)
    {
        return;
    }
    currentActiveTexture = texture;
    glActiveTexture(texture);
}

void qui::ReleaseOpenGLWrapper::attachShader(GLuint program, GLuint shader) const
{
    glAttachShader(program, shader);
}

void qui::ReleaseOpenGLWrapper::bindAttribLocation(GLuint program, GLuint index, const char* name) const
{
    glBindAttribLocation(program, index, name);
}

inline void qui::ReleaseOpenGLWrapper::bindBuffer(GLenum target, GLuint buffer) const
{
    glBindBuffer(target, buffer);
}

void qui::ReleaseOpenGLWrapper::bufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) const
{
    glBufferData(target, size, data, usage);
}

void qui::ReleaseOpenGLWrapper::bindTexture(GLenum target, GLuint texture) const
{
    glBindTexture(target, texture);
}

void qui::ReleaseOpenGLWrapper::compileShader(GLuint shader) const
{
    glCompileShader(shader);
}

GLuint qui::ReleaseOpenGLWrapper::createShader(GLenum type) const
{
    return glCreateShader(type);
}

GLuint qui::ReleaseOpenGLWrapper::createProgram(void) const
{
    return glCreateProgram();
}

void qui::ReleaseOpenGLWrapper::deleteProgram(GLuint program) const
{
    glDeleteProgram(program);
}

void qui::ReleaseOpenGLWrapper::deleteShader(GLuint shader) const
{
    glDeleteShader(shader);
}

void qui::ReleaseOpenGLWrapper::drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) const
{
    glDrawElements(mode, count, type, indices);
}

void qui::ReleaseOpenGLWrapper::enable(GLenum cap)
{
    if (cap == GL_BLEND)
    {
        if ((enabledCap & GLW_GL_BLEND) == 0)
        {
            enabledCap |= GLW_GL_BLEND;
            glEnable(cap);
        }
    }
    else
    {
        glEnable(cap);
    }
}

void qui::ReleaseOpenGLWrapper::blendFunc(GLenum sfactor, GLenum dfactor) const
{
    glBlendFunc(sfactor, dfactor);
}

void qui::ReleaseOpenGLWrapper::disable(GLenum cap)
{
    if (cap == GL_BLEND)
    {
        if ((enabledCap & GLW_GL_BLEND) != 0)
        {
            enabledCap &= (~GLW_GL_BLEND);
            glDisable(cap);
        }
    }
    else
    {
        glDisable(cap);
    }
}

void qui::ReleaseOpenGLWrapper::enableVertexAttribArray(GLuint index) const
{
    glEnableVertexAttribArray(index);
}

void qui::ReleaseOpenGLWrapper::genBuffers(GLsizei n, GLuint* buffers) const
{
    glGenBuffers(n, buffers);
}

void qui::ReleaseOpenGLWrapper::genTextures(GLsizei n, GLuint* textures) const
{
    glGenTextures(n, textures);
}

int  qui::ReleaseOpenGLWrapper::getAttribLocation(GLuint program, const char* name) const
{
    return glGetAttribLocation(program, name);
}

void qui::ReleaseOpenGLWrapper::getProgramiv(GLuint program, GLenum pname, GLint* params) const
{
    glGetProgramiv(program, pname, params);
}

void qui::ReleaseOpenGLWrapper::getProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, char* infolog) const
{
    glGetProgramInfoLog(program, bufsize, length, infolog);
}

void qui::ReleaseOpenGLWrapper::getShaderiv(GLuint shader, GLenum pname, GLint* params) const
{
    glGetShaderiv(shader, pname, params);
}

void qui::ReleaseOpenGLWrapper::getShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, char* infolog) const
{
    glGetShaderInfoLog(shader, bufsize, length, infolog);
}

int qui::ReleaseOpenGLWrapper::getUniformLocation(GLuint program, const char* name) const
{
    return glGetUniformLocation(program, name);
}

void qui::ReleaseOpenGLWrapper::linkProgram(GLuint program) const
{
    glLinkProgram(program);
}

void qui::ReleaseOpenGLWrapper::pixelStorei(GLenum pname, GLint param) const
{
    glPixelStorei(pname, param);
}

void qui::ReleaseOpenGLWrapper::shaderSource(GLuint shader
                                           , GLsizei count
                                           , const char** string
                                           , const GLint* length) const
{
    glShaderSource(shader, count, string, length);
}

void qui::ReleaseOpenGLWrapper::texImage2D(GLenum target
                                                 , GLint level
                                                 , GLint internalformat
                                                 , GLsizei width
                                                 , GLsizei height
                                                 , GLint border
                                                 , GLenum format
                                                 , GLenum type
                                                 , const void* pixels)
{
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

inline void qui::ReleaseOpenGLWrapper::texParameteri(GLenum target, GLenum pname, GLint param) const
{
    glTexParameteri(target, pname, param);
}

void qui::ReleaseOpenGLWrapper::uniform1i(GLint location, GLint x) const
{
    glUniform1i(location, x);
}

void qui::ReleaseOpenGLWrapper::uniformMatrix4fv(GLint location
                                               , GLsizei count
                                               , GLboolean transpose
                                               , const GLfloat* value) const
{
    glUniformMatrix4fv(location, count, transpose, value);
}

void qui::ReleaseOpenGLWrapper::useProgram(GLuint program)
{
    if (currentProgram == program)
    {
        return;
    }
    currentProgram = program;
    glUseProgram(program);
}

void qui::ReleaseOpenGLWrapper::vertexAttribPointer(GLuint indx
                                                   , GLint size
                                                   , GLenum type
                                                   , GLboolean normalized
                                                   , GLsizei stride
                                                   , const void* ptr) const
{
    glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
}

#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_RELEASEOPENGLWRAPPER_H_
