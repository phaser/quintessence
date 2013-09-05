// Copyright (C) 2012 Cristian Bidea
// This file is part of QUIImage.
//
//    QUIImage is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIImage is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIImage.  If not, see <http://www.gnu.org/licenses/>.
#ifndef PACKAGES_QUI_QUIIMAGE_DEV_INCLUDE_QUI_DEFAULTIMAGE_H_
#define PACKAGES_QUI_QUIIMAGE_DEV_INCLUDE_QUI_DEFAULTIMAGE_H_

#include <qui/cpp11compat.h>
#include <GLES2/gl2.h>
#include <string>

namespace qui
{
class DefaultImage : public Image
{
 public:
    DefaultImage() : Image()
    {
        imgData = cpp0x::shared_ptr<unsigned char>(new unsigned char[64*64*3]);
        for (int i = 0; i < 64*64*3; i+=3)
        {
            imgData.get()[i] = (i % 256);
            imgData.get()[i+1] = ((i + 23) % 256);
            imgData.get()[i+2] = ((i + 7) % 256);
        }
    }
    unsigned int GetWidth() const
    {
        return 64;
    }
    unsigned int GetHeight() const
    {
        return 64;
    }
    unsigned int GetImageDataFormat() const
    {
        return GL_RGB;
    }
    cpp0x::shared_ptr<unsigned char> GetImageData()
    {
        return imgData;
    };
    virtual ~DefaultImage()
    {
    }
 protected:
    std::string file;
    int width;
    int height;
    cpp0x::shared_ptr<unsigned char> imgData;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIIMAGE_DEV_INCLUDE_QUI_DEFAULTIMAGE_H_
