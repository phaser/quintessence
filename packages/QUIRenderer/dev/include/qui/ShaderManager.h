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

#ifndef PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_SHADERMANAGER_H_
#define PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_SHADERMANAGER_H_

#include <qui/cpp11compat.h>
#include <qui/UniversalHashStore.h>
#include <map>
#include <string>

namespace qui
{
class GLShader;
class ShaderManager
{
 public:
    ShaderManager();
    ~ShaderManager();
    bool loadShader(size_t id
                  , const std::string& vShader
                  , const std::string& fShader);
    cpp0x::shared_ptr<GLShader> getShader(size_t id);
 private:
    static UniversalHashStore<cpp0x::shared_ptr<GLShader> > shaders;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRENDERER_DEV_INCLUDE_QUI_SHADERMANAGER_H_
