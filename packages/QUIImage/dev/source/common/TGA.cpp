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
#include <qui/TGA.h>
#include <qui/log.h>
#include <string.h>
#include <stdlib.h>
#include <qui/VirtualFS.h>
#include <GLES2/gl2.h>
#include <string>

namespace qui
{
TGA::TGA(const std::string& fileName)
    : Image()
    , header(NULL)
    , fileName(fileName)
{
}

void TGA::logHeader()
{
    LOG(INFO) <<  "idlength: \t\t"         << static_cast<int>(header->idlength);
    LOG(INFO) <<  "colourmaptype: \t\t"    << static_cast<int>(header->colourmaptype);
    LOG(INFO) <<  "datatypecode: \t\t"     << static_cast<int>(header->datatypecode);
    LOG(INFO) <<  "colourmaporigin: \t"    << header->colourmaporigin;
    LOG(INFO) <<  "colourmaplength: \t"    << header->colourmaplength;
    LOG(INFO) <<  "colourmapdepth: \t"     << static_cast<int>(header->colourmapdepth);
    LOG(INFO) <<  "x_origin: \t\t"         << header->x_origin;
    LOG(INFO) <<  "y_origin: \t\t"         << header->y_origin;
    LOG(INFO) <<  "width: \t\t\t"            << header->width;
    LOG(INFO) <<  "height: \t\t"           << header->height;
    LOG(INFO) <<  "bitsperpixel: \t\t"       << static_cast<int>(header->bitsperpixel);
    LOG(INFO) <<  "imagedescriptor: \t"    << static_cast<int>(header->imagedescriptor);
}

cpp0x::shared_ptr<unsigned char> TGA::getImageData()
{
    if (imgData.get() != NULL)
    {
        return imgData;
    }

    qui::VirtualFS fs;
    int imgLen;
    cpp0x::shared_ptr<char> fileContents = fs.getFileContents(fileName, &imgLen, 0);
    unsigned char *img = (unsigned char*)(fileContents.get());
    header = static_cast<TGAHeader*>(malloc(sizeof(TGAHeader)));
    memcpy(header, img, sizeof(TGAHeader));
    unsigned char *data = (img + sizeof(TGAHeader));
    this->width = header->width;
    this->height = header->height;
    logHeader();
    if (header->idlength > 0)
    {
        LOG(WARNING) << "Here should be some skipping but it's not yet implemented!";
    }

    unsigned char* buf = new unsigned char[getWidth() * getHeight() * 3];
    switch (header->datatypecode)
    {
    case(DT_UNMAPPED_RGB):
        memcpy(buf, data, getWidth() * getHeight() * 3);
        unsigned char aux;
        for (int i = 0; i < getHeight(); i++)
        {
            for (int j = 0; j < getWidth(); j++)
            {
                aux = buf[3*(i*getWidth() + j)];
                buf[3*(i*getWidth() + j)] = buf[3*(i*getWidth() + j) + 2];
                buf[3*(i*getWidth() + j) + 2] = aux;
            }
        }
        imgData = cpp0x::shared_ptr<unsigned char>(buf, array_deleter<unsigned char>());
        break;
    default:
        LOG(LERROR) << "Image datatype not supported: " << header->datatypecode;
    }
    free(header);
    header = NULL;
    return imgData;
}

unsigned char* TGA::getUnmappedRGB()
{
    return NULL;
}

unsigned int TGA::getImageDataFormat() const
{
    return GL_RGB;
}

TGA::~TGA()
{
    LOG(INFO) <<  "~TGA()";
    if (header != NULL)
    {
        LOG(WARNING) << "Header not freed!";
        free(header);
        header = NULL;
    }
}
}  // namespace qui
