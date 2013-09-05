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
#ifndef PACKAGES_QUI_QUIIMAGE_DEV_INCLUDE_QUI_IMAGE_H_
#define PACKAGES_QUI_QUIIMAGE_DEV_INCLUDE_QUI_IMAGE_H_

#include <qui/cpp11compat.h>
#include <string>

namespace qui
{
class Image
{
 public:
    Image();
    virtual unsigned int getWidth() const;
    virtual unsigned int getHeight() const;
    virtual unsigned int getImageDataFormat() const =0;
    virtual cpp0x::shared_ptr<unsigned char> getImageData() =0;
    virtual ~Image();
 protected:
    unsigned int width;
    unsigned int height;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIIMAGE_DEV_INCLUDE_QUI_IMAGE_H_
