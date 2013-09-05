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

#include <qui/TextureManager.h>
#include <qui/Hash.h>
#include <qui/PNG.h>
#include <qui/log.h>
#include <qui/GLTexture.h>

namespace qui
{
UniversalHashStore<cpp0x::shared_ptr<GLTexture> > TextureManager::textures;

cpp0x::shared_ptr<GLTexture> TextureManager::getTexture(size_t id) const
{
    if (!textures.exists(id))
    {
        return cpp0x::shared_ptr<GLTexture>();
    }
    return textures.get(id);
}

bool TextureManager::loadTexture(const char* textureFile, const char* name)
{
    size_t textureId;
    if (name == NULL)
    {
        textureId = qui::Hash(textureFile).value;
    }
    else
    {
        textureId = qui::Hash(name).value;
    }

    if (textures.exists(textureId))
    {
        LOG(WARNING) << "Texture " << textureFile << " already loaded!";
        return true;
    }

    cpp0x::shared_ptr<qui::Image> image(new qui::PNG(textureFile));
    if (image.get() == NULL)
    {
        LOG(LERROR) << "Image " << textureFile << " not found or error on loading.";
        return false;
    }
    textures.store(textureId, cpp0x::shared_ptr<GLTexture>(new GLTexture(*image.get())));
    return true;
}
}  // namespace qui
