// Copyright (C) 2013 Cristian Bidea
// This file is part of QUIText.
//
//    QUIText is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIText is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIText.  If not, see <http://www.gnu.org/licenses/>.
#include <qui/text/Font.h>
#include <qui/VirtualFS.h>
#include <qui/log.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "./Glyph.h"

namespace qui
{
namespace text
{
Font::Font(const std::string fileName)
    : fileName(fileName)
    , size(0)
    , fontName("")
    , material("")
    , currentFilePos(0)
{
}

Font::~Font()
{
}

bool Font::load()
{
    qui::VirtualFS fs;
    cpp0x::shared_ptr<char> contents = fs.getFileContentsAsText(fileName);
    if (contents.get() == NULL)
    {
        LOG(LERROR) << "Couldn't read file " << fileName;
        return false;
    }
    std::string fileContents(fs.getFileContentsAsText(fileName).get());
    if (!hasNextLine(fileContents))
    {
        LOG(LERROR) << "File is too short!";
        return false;
    }
    std::string line = getNextLine(fileContents);
    if (line.find("info") == std::string::npos)
    {
        LOG(LERROR) << "No \"info\" section present";
        return false;
    }
    fontName = getEnclosedValue(line, "face=\"", "\"");
    if (hasNextLine(fileContents))
    {
        getNextLine(fileContents);
    }
    if (!hasNextLine(fileContents))
    {
        LOG(LERROR) << "File is too short!";
        return false;
    }
    line = getNextLine(fileContents);
    material = getEnclosedValue(line, "file=\"", "\"");
    if (!hasNextLine(fileContents))
    {
        LOG(LERROR) << "File is too short!";
        return false;
    }
    line = getNextLine(fileContents);
    std::string strValue = getEnclosedValue(line, "chars count=", "\n");
    int noChars = atoi(strValue.c_str());
    for (int i = 0; i < noChars; i++)
    {
        if (!hasNextLine(fileContents))
        {
            LOG(LERROR) << "File is too short!";
            return false;
        }
        line = getNextLine(fileContents);
        cpp0x::shared_ptr<Glyph> glyph(new Glyph());
        strValue = getEnclosedValue(line, "char id=", " ");
        glyph->charId = atoi(strValue.c_str());
        strValue = getEnclosedValue(line, "x=", " ");
        glyph->position.x = atoi(strValue.c_str());
        strValue = getEnclosedValue(line, "y=", " ");
        glyph->position.y = atoi(strValue.c_str());
        strValue = getEnclosedValue(line, "width=", " ");
        glyph->size.x = atoi(strValue.c_str());
        strValue = getEnclosedValue(line, "height=", " ");
        glyph->size.y = atoi(strValue.c_str());
        strValue = getEnclosedValue(line, "xoffset=", " ");
        glyph->offset.x = atoi(strValue.c_str());
        strValue = getEnclosedValue(line, "yoffset=", " ");
        glyph->offset.y = atoi(strValue.c_str());
        strValue = getEnclosedValue(line, "xadvance=", " ");
        glyph->xadvance = atoi(strValue.c_str());
        chars[glyph->charId] = glyph;
    }
    return true;
}

cpp0x::shared_ptr<Glyph> Font::getGlyphForChar(int32_t chr)
{
    if (chars.find(chr) == chars.end())
    {
        return chars.begin()->second;
    }
#ifdef PLATFORM_WIN32
    cpp0x::shared_ptr<Glyph> result = chars.at(chr);
#else
    cpp0x::shared_ptr<Glyph> result = chars.find(chr)->second;
#endif
    return result;
}

std::string Font::getNextLine(const std::string& fileContents)
{
    size_t pos = fileContents.find("\n", currentFilePos);
    if (pos == std::string::npos)
    {
        if (currentFilePos < fileContents.size())
        {
            pos = fileContents.size();
        }
    }
    std::string result = fileContents.substr(currentFilePos, pos - currentFilePos + 1);
    currentFilePos = pos + 1;
    return result;
}

bool Font::hasNextLine(const std::string& fileContents)
{
    size_t pos = fileContents.find("\n", currentFilePos);
    return (pos != std::string::npos);
}

std::string Font::getEnclosedValue(const std::string& content, const char* begin, const char* end, size_t startPos)
{
    size_t bsize = strlen(begin);
    size_t pos = content.find(begin);
    size_t pos2 = content.find(end, pos + bsize);
    return content.substr(pos + bsize, pos2 - pos - bsize);
}
}  // namespace text
}  // namespace qui
