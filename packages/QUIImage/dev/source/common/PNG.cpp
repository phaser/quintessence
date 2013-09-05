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
#include <qui/PNG.h>
#include <qui/log.h>
#include <qui/VirtualFS.h>
#include <GLES2/gl2.h>
#include <lodepng.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include <string>

namespace qui
{
PNG::PNG(const std::string& filename)
    : Image()
    , fileName(filename)
{
    LOG(LDEBUG) << "PNG( " << filename << " )";
}

PNG::~PNG()
{
    LOG(LDEBUG) << "~PNG( " << this->fileName << " )";
}

cpp0x::shared_ptr<unsigned char> PNG::getImageData()
{
    if (imgData.get() != NULL)
    {
        return imgData;
    }

    qui::VirtualFS fs;
    std::vector<unsigned char> *image = new std::vector<unsigned char>();  // the raw pixels
    cpp0x::shared_ptr<unsigned char> null_result(static_cast<unsigned char*>(NULL), array_deleter<unsigned char>());

    int len;
    cpp0x::shared_ptr<char> fileContents = fs.getFileContents(fileName, &len);
    if (fileContents.get() == NULL)
    {
        LOG(LERROR) << "Could not load filename " << fileName <<". Contents is NULL!";
        return null_result;
    }
    unsigned char* buffer = reinterpret_cast<unsigned char*>(fileContents.get());
    // decode
    unsigned error = lodepng::decode(*image
                                   , this->width
                                   , this->height
                                   , buffer
                                   , len
                                   , LCT_RGBA
                                   , 8);

    // if there's an error, display it
    if (error)
    {
        LOG(LERROR) << "decoder error " << error << ": " << lodepng_error_text(error)
                    << std::endl << "... on file " << fileName;
        return null_result;
    }
    imgData = cpp0x::shared_ptr<unsigned char>(static_cast<unsigned char*>(&(*image)[0])
                                                                         , array_deleter<unsigned char>());
    return imgData;
}

unsigned int PNG::getImageDataFormat() const
{
    return GL_RGBA;
}
}  // namespace qui
