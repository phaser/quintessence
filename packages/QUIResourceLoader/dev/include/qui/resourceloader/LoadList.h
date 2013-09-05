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

#ifndef PACKAGES_QUI_QUIRESOURCELOADER_DEV_INCLUDE_QUI_RESOURCELOADER_LOADLIST_H_
#define PACKAGES_QUI_QUIRESOURCELOADER_DEV_INCLUDE_QUI_RESOURCELOADER_LOADLIST_H_
#include <qui/ReflectableObject.h>
#include <vector>
#include <string>

namespace qui
{
namespace resourceloader
{
class TextureDescriptor : public qui::ReflectableObject
{
 public:
     std::string name;
     std::string image;

     static TypeInfo* getClassMapping(size_t* numMapTypes)
     {
        START_TYPES_DECLARATION(TextureDescriptor, 2);
        DEFINE_TYPE(0, TextureDescriptor, name, qui::STRING, sValue);
        DEFINE_TYPE(1, TextureDescriptor, image, qui::STRING, sValue);
        return mappings;
     }
     REFLECTION_FUNCTIONS(TextureDescriptor);
};

class AtlasDescriptor : public qui::ReflectableObject
{
    public:
        std::string file;
        static TypeInfo* getClassMapping(size_t* numMapTypes)
        {
            START_TYPES_DECLARATION(AtlasDescriptor, 1);
            DEFINE_TYPE(0, AtlasDescriptor, file, qui::STRING, sValue);
            return mappings;
        }
        REFLECTION_FUNCTIONS(AtlasDescriptor);
};

class ShaderDescriptor : public qui::ReflectableObject
{
 public:
     std::string name;
     std::string fragment;
     std::string vertex;

     static TypeInfo* getClassMapping(size_t* numMapTypes)
     {
         START_TYPES_DECLARATION(ShaderDescriptor, 3);
         DEFINE_TYPE(0, ShaderDescriptor, name, qui::STRING, sValue);
         DEFINE_TYPE(1, ShaderDescriptor, fragment, qui::STRING, sValue);
         DEFINE_TYPE(2, ShaderDescriptor, vertex, qui::STRING, sValue);
         return mappings;
     }
     REFLECTION_FUNCTIONS(ShaderDescriptor);
};

class MaterialDescriptor : public qui::ReflectableObject
{
 public:
     std::string name;
     std::string shader;
     std::string texture;

     static TypeInfo* getClassMapping(size_t* numMapTypes)
     {
         START_TYPES_DECLARATION(MaterialDescriptor, 3);
         DEFINE_TYPE(0, MaterialDescriptor, name, qui::STRING, sValue);
         DEFINE_TYPE(1, MaterialDescriptor, shader, qui::STRING, sValue);
         DEFINE_TYPE(2, MaterialDescriptor, texture, qui::STRING, sValue);
         return mappings;
     }
     REFLECTION_FUNCTIONS(MaterialDescriptor);
};

class FontDescriptor : public qui::ReflectableObject
{
 public:
     std::string fontName;
     std::string fileName;
     std::string material;

     static TypeInfo* getClassMapping(size_t* numMapTypes)
     {
         START_TYPES_DECLARATION(FontDescriptor, 3);
         DEFINE_TYPE(0, FontDescriptor, fontName, qui::STRING, sValue);
         DEFINE_TYPE(1, FontDescriptor, fileName, qui::STRING, sValue);
         DEFINE_TYPE(2, FontDescriptor, material, qui::STRING, sValue);
         return mappings;
     }
     REFLECTION_FUNCTIONS(FontDescriptor);
};

class LoadList : public qui::ReflectableObject
{
 public:
     LoadList();
     ~LoadList();
     std::vector<TextureDescriptor*>* getTextures() const
     {
         return textures;
     }
     std::vector<AtlasDescriptor*>* getAtlasses() const
     {
         return atlasses;
     }
     std::vector<ShaderDescriptor*>* getShaders() const
     {
         return shaders;
     }
     std::vector<MaterialDescriptor*>* getMaterials() const
     {
         return materials;
     }
     std::vector<FontDescriptor*>* getFonts() const
     {
         return fonts;
     }
     static TypeInfo* getClassMapping(size_t* numMapTypes)
     {
         START_TYPES_DECLARATION(LoadList, 5);
         DEFINE_POINTER(0, LoadList, shaders, qui::POINTER, pValue);
         DEFINE_POINTER(1, LoadList, atlasses, qui::POINTER, pValue);
         DEFINE_POINTER(2, LoadList, textures, qui::POINTER, pValue);
         DEFINE_POINTER(3, LoadList, materials, qui::POINTER, pValue);
         DEFINE_POINTER(4, LoadList, fonts, qui::POINTER, pValue);
         return mappings;
     }
     REFLECTION_FUNCTIONS(LoadList);
 private:
     std::vector<ShaderDescriptor*>* shaders;
     std::vector<AtlasDescriptor*>* atlasses;
     std::vector<TextureDescriptor*>* textures;
     std::vector<MaterialDescriptor*>* materials;
     std::vector<FontDescriptor*>* fonts;
};

const static qui::ReflectionMapping mappings[] =                                 // NOLINT
    {{"TextureDescriptor", &qui::createReflectableObject<TextureDescriptor>}     // NOLINT
   , {"AtlasDescriptor", &qui::createReflectableObject<AtlasDescriptor>}         // NOLINT
   , {"ShaderDescriptor", &qui::createReflectableObject<ShaderDescriptor>}       // NOLINT
   , {"MaterialDescriptor", &qui::createReflectableObject<MaterialDescriptor>}   // NOLINT
   , {"FontDescriptor", &qui::createReflectableObject<FontDescriptor>}           // NOLINT
   , {"LoadList", &qui::createReflectableObject<LoadList>}};                     // NOLINT
static const int NUM_MAPS = 6;
}  // namespace resourceloader
}  // namespace qui
#endif  // PACKAGES_QUI_QUIRESOURCELOADER_DEV_INCLUDE_QUI_RESOURCELOADER_LOADLIST_H_
