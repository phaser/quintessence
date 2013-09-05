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

#include <qui/GLShader.h>
#include <qui/RenderOptions.h>
#include <qui/VirtualFS.h>
#include <qui/log.h>
#include <string>

namespace qui
{
/* ======================================================================= *
 * Public Functions Implementation
 * ======================================================================= */
/**
 * 
 */
GLShader::GLShader()
    : ready(false)
    , vertexShader(0)
    , fragmentShader(0)
{
}

GLShader::~GLShader()
{
}

/**
 * Getter. Returns the value of the vertex shader id.
 */
GLuint GLShader::getVertexShader()
{
    return vertexShader;
}

/**
 * 
 */
void GLShader::setVertexShader(GLuint vShader)
{
    this->vertexShader = vShader;
}

GLuint GLShader::getFragmentShader()
{
    return fragmentShader;
}

void GLShader::setFragmentShader(GLuint fShader)
{
    this->fragmentShader = fShader;
}

GLuint GLShader::getProgramObject()
{
    return programObject;
}

void GLShader::setProgramObject(GLuint pObject)
{
    this->programObject = pObject;
}

void GLShader::bindAttribute(GLuint index, const char* name)
{
    GL->bindAttribLocation(this->getProgramObject(), index, name);
}

/**
 * Load a vertex shader or fragment shader.
 * @param type GL_VERTEX_SHADER for vertex shader and 
 *             GL_FRAGMENT_SHADER for fragment shader
 * @param source an istream
 * @return 0 if the shader was not loaded and something
 *         else if it was loaded.
 */
GLuint GLShader::loadShader(GLenum type, const char* buffer)
{
    GLuint shader = 0;
    GLint compiled;

    shader = GL->createShader(type);
    if (0 == shader)
    {
        return 0;
    }

    GL->shaderSource(shader, 1, &buffer, NULL);
    GL->compileShader(shader);
    GL->getShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infolen = 0;
        GL->getShaderiv(shader, GL_INFO_LOG_LENGTH, &infolen);
        if (infolen > 1)
        {
            char* infoLog = new char[infolen];
            GL->getShaderInfoLog(shader, infolen, NULL, infoLog);
            LOG(LERROR) << "Error compiling shader: " << infoLog;
            delete [] infoLog;
        }
        delete [] buffer;
        GL->deleteShader(shader);
        return 0;
    }
    return shader;
}

/**
 * Create the program object and attach the loaded vertex and
 * fragment shaders to it.
 */
void GLShader::compile()
{
    ready = false;
    if (this->getProgramObject() == 0)
    {
        LOG(LERROR) << "Program object must be created first. "
                        "Please call CreateProgramAndAttachShaders() first.";
        return;
    }

    GLint linked;
    // Link the program
    GL->linkProgram(getProgramObject());

    // Check the link status
    GL->getProgramiv(getProgramObject(), GL_LINK_STATUS, &linked);

    if (!linked)
    {
        GLint infoLen = 0;
        GL->getProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            char* infoLog = new char[infoLen];
            GL->getProgramInfoLog(programObject, infoLen, NULL, infoLog);
            LOG(LERROR) << "Error linking program: " << std::endl << infoLog;
            delete [] infoLog;
        }
        GL->deleteProgram(programObject);
        return;
    }
    ready = true;
}

void GLShader::saveSamplerLoc(const std::string& uName)
{
    this->samplerLoc = GL->getUniformLocation(this->getProgramObject()
                                            , uName.c_str());
}

GLuint GLShader::getSamplerLocation() const
{
    return this->samplerLoc;
}

void GLShader::createProgramAndAttachShaders()
{
    if (0 == vertexShader || 0 == fragmentShader)
    {
        LOG(FATAL) << "Before compile set the"
                      " vertex shader and fragment shader.";
        ready = false;
        return;
    }

    // Create the program object
    this->setProgramObject(GL->createProgram());
    if (0 == this->getProgramObject())
    {
        LOG(LERROR) << "Could not create program object!";
        ready = false;
        return;
    }

    GL->attachShader(this->getProgramObject(), this->getVertexShader());
    GL->attachShader(this->getProgramObject(), this->getFragmentShader());
}

/**
 * Loads the vertex and fragment shader, compiles the program and returns a
 * new and ready for use GLShader* object.
 */
GLShader* GLShader::initProgramWithShaders(const std::string& vertexShaderFile
                                         , const std::string& fragmentShaderFile)
{
    GLShader* shader = new GLShader();
    qui::VirtualFS fs;
    cpp0x::shared_ptr<char> vertexFile = fs.getFileContentsAsText(vertexShaderFile);
    char *vertexShader = vertexFile.get();
    if (vertexShader == NULL)
    {
        LOG(FATAL) << "Vertex Shader wasn't loaded!";
        return NULL;
    }

    GLuint vsh = qui::GLShader::loadShader(GL_VERTEX_SHADER, vertexShader);
    cpp0x::shared_ptr<char> fragmentFile = fs.getFileContentsAsText(fragmentShaderFile);
    char *fragmentShader = fragmentFile.get();
    if (fragmentShader == NULL)
    {
        LOG(FATAL) << "Fragment Shader wasn't loaded!";
        return NULL;
    }
    GLuint fsh = qui::GLShader::loadShader(GL_FRAGMENT_SHADER, fragmentShader);
    shader->setVertexShader(vsh);
    shader->setFragmentShader(fsh);
    shader->createProgramAndAttachShaders();
    shader->compile();
    return shader;
}

void GLShader::useProgram()
{
    GL->useProgram(this->getProgramObject());
}
}  // namespace qui
