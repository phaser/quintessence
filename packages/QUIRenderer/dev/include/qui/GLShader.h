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

#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_GLSHADER_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_GLSHADER_H_

#include <GLES2/gl2.h>
#include <iostream>
#include <string>

namespace qui
{
const char SHADER_TEXTURE_SAMPLER[]                 = "s_texture";
const char SHADER_VERTEX_POSITION[]                 = "a_position";
const char SHADER_TEXTURE_COORDS[]                  = "a_texCoord";
const char SHADER_COLOR[]                           = "a_color";
const char SHADER_PROJECTION_MODEL_VIEW_MATRIX[]    = "PMVMATRIX";

const int SHADER_ATTR_VERTEX_IDX = 0;
class GLShader
{
 public:
    GLShader();
    ~GLShader();
    GLuint getVertexShader();
    void setVertexShader(GLuint vShader);
    GLuint getFragmentShader();
    void setFragmentShader(GLuint fShader);
    GLuint getProgramObject();
    void createProgramAndAttachShaders();
    void bindAttribute(GLuint index, const char* name);
    void compile();
    void saveSamplerLoc(const std::string& name);
    GLuint getSamplerLocation() const;
    static GLuint loadShader(GLenum type, const char* buffer);
    static GLShader* initProgramWithShaders(const std::string& vertexShaderFile
                                          , const std::string& fragmentShaderFile);
    void useProgram();
 private:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLuint samplerLoc;
    bool ready;

    void setProgramObject(GLuint pObject);
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_GLSHADER_H_
