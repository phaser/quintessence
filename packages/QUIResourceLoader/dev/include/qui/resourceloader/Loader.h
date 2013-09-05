// Copyright (C) 2013 Cristian Bidea
// This file is part of QUIResourceLoader.
//
//    QUIResourceLoader is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIResourceLoader is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIResourceLoader.  If not, see <http://www.gnu.org/licenses/>.

#ifndef PACKAGES_QUI_QUIRESOURCELOADER_DEV_INCLUDE_QUI_RESOURCELOADER_LOADER_H_
#define PACKAGES_QUI_QUIRESOURCELOADER_DEV_INCLUDE_QUI_RESOURCELOADER_LOADER_H_
#include <qui/resourceloader/LoadList.h>
#include <string>

namespace qui
{
namespace resourceloader
{
class Loader
{
 public:
     Loader();
     LoadList* loadList(const std::string& fileName);
     void loadResources(LoadList* list);
 private:
     void loadTextures(LoadList* list);
     void loadAtlasses(LoadList* list);
     void loadShaders(LoadList* list);
     void loadMaterials(LoadList* list);
     void loadFonts(LoadList* list);
};
}  // namespace resourceloader
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRESOURCELOADER_DEV_INCLUDE_QUI_RESOURCELOADER_LOADER_H_
