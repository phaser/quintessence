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
#ifndef PACKAGES_QUI_QUIIMAGE_DEV_INCLUDE_QUI_TGA_H_
#define PACKAGES_QUI_QUIIMAGE_DEV_INCLUDE_QUI_TGA_H_

#include <qui/Image.h>
#include <stdio.h>
#include <qui/cpp11compat.h>
#include <stdint.h>
#include <string>

#define DT_UNMAPPED_RGB 2

/**
 * Specifies packing alignment for structure, union, and class members.
 * http://msdn.microsoft.com/en-us/library/2e70t5y1(VS.80).aspx
 *
 * I use pack so I can fetch the structure from file in one read!
 */
#pragma pack(push, 1)
typedef struct
{
    int8_t  idlength;
    int8_t  colourmaptype;
    int8_t  datatypecode;
    int16_t colourmaporigin;
    int16_t colourmaplength;
    int8_t  colourmapdepth;
    int16_t x_origin;
    int16_t y_origin;
    int16_t width;
    int16_t height;
    int8_t  bitsperpixel;
    int8_t  imagedescriptor;
}
TGAHeader;
#pragma pack(pop)

namespace qui
{
class TGA: public Image
{
 public:
    explicit TGA(const std::string& fileName);
    cpp0x::shared_ptr<unsigned char> getImageData();
    unsigned int getImageDataFormat() const;
    ~TGA();
 private:
    TGAHeader* header;
    std::string fileName;

    void logHeader();
    unsigned char* getUnmappedRGB();
    cpp0x::shared_ptr<unsigned char> imgData;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIIMAGE_DEV_INCLUDE_QUI_TGA_H_
