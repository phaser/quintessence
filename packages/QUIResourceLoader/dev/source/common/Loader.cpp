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

#include <qui/resourceloader/Loader.h>
#include <qui/resourceloader/LoadList.h>
#include <qui/ReflectionManager.h>
#include <qui/XMLSerializer.h>
#include <qui/ReflectableObject.h>
#include <qui/TextureManager.h>
#include <qui/ShaderManager.h>
#include <qui/MaterialManager.h>
#include <qui/text/FontManager.h>
#include <qui/text/Font.h>
#include <qui/Material.h>
#include <qui/TextureAtlas.h>
#include <string>
#include <vector>

namespace qui
{
namespace resourceloader
{
Loader::Loader()
{
}

LoadList* Loader::loadList(const std::string& fileName)
{
    qui::XMLSerializer XMLSerializer(fileName);
    qui::ReflectableObject *object = XMLSerializer.deserialize("LoadList");
    LoadList* list = static_cast<LoadList*>(object);
    return list;
}

void Loader::loadResources(LoadList* list)
{
    loadShaders(list);
    loadAtlasses(list);
    loadTextures(list);
    loadMaterials(list);
    loadFonts(list);
}

void Loader::loadTextures(LoadList* list)
{
    if (!list->getTextures())
    {
        return;
    }

    qui::TextureManager tm;
    for (std::vector<TextureDescriptor*>::iterator it = list->getTextures()->begin()
       ; it != list->getTextures()->end()
       ; it++)
    {
        TextureDescriptor* element = *it;
        if (!tm.loadTexture(element->image.c_str(), element->name.c_str()))
        {
            LOG(LERROR) << "Failed to load texture: " << element->image;
        }
    }
}

void Loader::loadShaders(LoadList* list)
{
    if (!list->getShaders())
    {
        return;
    }

    qui::ShaderManager sm;
    for (std::vector<ShaderDescriptor*>::iterator it = list->getShaders()->begin()
       ; it != list->getShaders()->end()
       ; it++)
    {
        ShaderDescriptor *element = *it;
        bool result = sm.loadShader(qui::Hash(element->name.c_str()).value
                              , element->vertex.c_str()
                              , element->fragment.c_str());
        if (!result)
        {
            LOG(LERROR) << "Shader "
                        << element->name
                        << "["
                        << element->vertex
                        << "]["
                        << element->fragment
                        << "] didn't load!";
        }
    }
}

void Loader::loadAtlasses(LoadList* list)
{
    if (!list->getAtlasses())
    {
        return;
    }
    for (std::vector<AtlasDescriptor*>::iterator it = list->getAtlasses()->begin()
       ; it != list->getAtlasses()->end()
       ; it++)
    {
        qui::TextureAtlas *atlas = new qui::TextureAtlas((*it)->file);
        atlas->loadModules();
        atlas->createMaterials(HASH("qui::Q2D::textured"));
        delete atlas;
        atlas = NULL;
    }
}

void Loader::loadMaterials(LoadList* list)
{
    qui::TextureManager tm;
    qui::MaterialManager mm;
    qui::ShaderManager sm;
    for (std::vector<MaterialDescriptor*>::iterator it = list->getMaterials()->begin()
       ; it != list->getMaterials()->end()
       ; it++)
    {
        MaterialDescriptor *element = *it;
        cpp0x::shared_ptr<qui::Material> material(new qui::Material());
        if (element->shader.size() > 0)
        {
            material->setShader(sm.getShader(qui::Hash(element->shader.c_str()).value));
        }
        if (element->texture.size() > 0)
        {
            material->setTexture(tm.getTexture(qui::Hash(element->texture.c_str()).value));
        }
        mm.addMaterial(element->name.c_str(), material);
    }
}

void Loader::loadFonts(LoadList* list)
{
    qui::text::FontManager fm;
    for (std::vector<FontDescriptor*>::iterator it = list->getFonts()->begin()
       ; it != list->getFonts()->end()
       ; it++)
    {
        FontDescriptor *element = *it;
        fm.loadFont(HASH(element->fontName.c_str()), element->fileName);
        fm.getFont(HASH(element->fontName.c_str()))->setMaterial(element->material);
    }
}
}  // namespace resourceloader
}  // namespace qui
