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

#include <qui/ShaderManager.h>
#include <qui/GLShader.h>
#include <map>
#include <string>

namespace qui
{
UniversalHashStore<cpp0x::shared_ptr<GLShader> > ShaderManager::shaders;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

bool ShaderManager::loadShader(size_t id
                  , const std::string& vShader
                  , const std::string& fShader)
{
    GLShader* shader = qui::GLShader::initProgramWithShaders(vShader, fShader);
    if (shader == NULL)
    {
        return false;
    }
    shaders.store(id, cpp0x::shared_ptr<GLShader>(shader));
    return true;
}

cpp0x::shared_ptr<GLShader> ShaderManager::getShader(size_t id)
{
    return shaders.get(id);
}
}  // namespace qui
