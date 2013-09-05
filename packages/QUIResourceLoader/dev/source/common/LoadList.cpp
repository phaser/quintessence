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

#include <qui/resourceloader/LoadList.h>
#include <vector>

namespace qui
{
namespace resourceloader
{
LoadList::LoadList()
    : shaders(NULL)
    , atlasses(NULL)
    , textures(NULL)
    , materials(NULL)
    , fonts(NULL)
{
}

LoadList::~LoadList()
{
     if (shaders)
     {
         // Clear shaders
         for (std::vector<ShaderDescriptor*>::iterator it = shaders->begin()
            ; it != shaders->end()
            ; it++)
         {
             ShaderDescriptor* element = *it;
             delete element;
             element = NULL;
         }
         shaders->clear();
         delete shaders;
         shaders = NULL;
     }
     if (atlasses)
     {
         for (std::vector<AtlasDescriptor*>::iterator it = atlasses->begin()
            ; it != atlasses->end()
            ; it++)
         {
             AtlasDescriptor* element = *it;
             delete element;
             element = NULL;
         }
         atlasses->clear();
         delete atlasses;
         atlasses = NULL;
     }
     if (textures)
     {
         // Clear textures
         for (std::vector<TextureDescriptor*>::iterator it = textures->begin()
             ; it != textures->end()
             ; it++)
         {
             TextureDescriptor* element = *it;
             delete element;
             element = NULL;
         }
         textures->clear();
         delete textures;
         textures = NULL;
     }
     if (materials)
     {
         // Clear materials
         for (std::vector<MaterialDescriptor*>::iterator it = materials->begin()
            ; it != materials->end()
            ; it++)
         {
             MaterialDescriptor* element = *it;
             delete element;
             element = NULL;
         }
         materials->clear();
         delete materials;
         materials = NULL;
     }
     if (fonts)
     {
         for (std::vector<FontDescriptor*>::iterator it = fonts->begin()
            ; it != fonts->end()
            ; it++)
         {
             FontDescriptor* element = *it;
             delete element;
             element = NULL;
         }
         fonts->clear();
         delete fonts;
         fonts = NULL;
     }
}
}  // namespace resourceloader
}  // namespace qui
