// Copyright (C) 2013 Cristian Bidea
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
#include <qui/TextureAtlas.h>
#include <qui/VirtualFS.h>
#include <qui/log.h>
#include <qui/TextureAtlasModule.h>
#include <qui/TextureManager.h>
#include <qui/MaterialManager.h>
#include <qui/ShaderManager.h>
#include <qui/Material.h>
#include <qui/Hash.h>
#include <tinyxml.h>
#include <string>
#include <vector>

namespace qui
{
TextureAtlas::TextureAtlas(const std::string& fileName)
    : fileName(fileName)
    , image("")
    , size(glm::vec2(0.f, 0.f))
{
}

bool TextureAtlas::loadModules()
{
    qui::VirtualFS fs;
    cpp0x::shared_ptr<char> contents = fs.getFileContentsAsText(this->fileName);
    if (!contents.get())
    {
        LOG(LERROR) << "Error occured while reading file " << this->fileName << "!";
        return false;
    }
    TiXmlDocument document;
    document.Parse(contents.get(), 0, TIXML_ENCODING_UTF8);
    const TiXmlElement* root = document.FirstChildElement("TextureAtlas");
    if (!root)
    {
        LOG(LERROR) << "Bad xml format!";
        return false;
    }
    const char* imagePath = root->Attribute("imagePath");
    if (!imagePath)
    {
        LOG(LERROR) << "Bad xml format: no imagePath attribute present!";
        return false;
    }
    image = imagePath;
    const char* width = root->Attribute("width");
    const char* height = root->Attribute("height");
    if (!(width && height))
    {
        LOG(LERROR) << "Bad xml format!";
        return false;
    }
    size = glm::vec2(atoi(width), atoi(height));
    const TiXmlElement* sprite = root->FirstChildElement("sprite");
    while (sprite)
    {
        cpp0x::shared_ptr<TextureAtlasModule> module(new TextureAtlasModule());
        module->name = sprite->Attribute("n");
        const char* posx = sprite->Attribute("x");
        const char* posy = sprite->Attribute("y");
        module->pos = glm::vec2(atoi(posx), atoi(posy));
        const char* sizex = sprite->Attribute("w");
        const char* sizey = sprite->Attribute("h");
        module->size = glm::vec2(atoi(sizex), atoi(sizey));
/*
        const char* oPosX = sprite->Attribute("oX");
        const char* oPosY = sprite->Attribute("oY");
        module->oPos = glm::vec2(atoi(oPosX), atoi(oPosY));
        const char* oSizeX = sprite->Attribute("oW");
        const char* oSizeY = sprite->Attribute("oH");
        module->oSize = glm::vec2(atoi(oSizeX), atoi(oSizeY));
 */
        const char* rot = sprite->Attribute("r");
        module->rotated = (rot ? true : false);
        modules.push_back(module);
        sprite = sprite->NextSiblingElement();
    }
}

bool TextureAtlas::createMaterials(size_t shaderId)
{
    qui::TextureManager tm;
    qui::MaterialManager mm;
    qui::ShaderManager sm;
    tm.loadTexture(this->image.c_str());
    unsigned int textureId = HASH(this->image.c_str());
    for (std::vector<cpp0x::shared_ptr<TextureAtlasModule> >::iterator it = modules.begin()
       ; it != modules.end()
       ; it++)
    {
        cpp0x::shared_ptr<TextureAtlasModule> module = *it;
        cpp0x::shared_ptr<qui::Material> material(new qui::Material());
        material->setShader(sm.getShader(shaderId));
        material->setTexture(tm.getTexture(textureId));
        material->setTextureAtlasModule(module);
        mm.addMaterial(module->name.c_str(), material);
    }
}
}  // namespace qui
