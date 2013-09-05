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
#ifndef PACKAGES_QUI_QUITEXT_DEV_INCLUDE_QUI_TEXT_FONT_H_
#define PACKAGES_QUI_QUITEXT_DEV_INCLUDE_QUI_TEXT_FONT_H_
#include <qui/cpp11compat.h>
#include <string>

struct Glyph;

namespace qui
{
namespace text
{
class Font
{
 public:
    explicit Font(const std::string fileName);
    ~Font();
    bool load();
    cpp0x::shared_ptr<Glyph> getGlyphForChar(int32_t chr);
    inline const char* getFontName() const;
    inline const char* getMaterial() const;
    inline void setMaterial(const std::string& material);
    inline int getSize() const;
 private:
    cpp0x::unordered_map<int32_t, cpp0x::shared_ptr<Glyph> > chars;
    std::string fileName;
    uint8_t size;
    std::string fontName;
    std::string material;
    size_t currentFilePos;

    std::string getNextLine(const std::string& fileContents);
    bool hasNextLine(const std::string& fileContents);
    std::string getEnclosedValue(const std::string& content, const char* begin, const char* end, size_t startPos = 0);
};

inline const char* Font::getFontName() const
{
    return fontName.c_str();
}

inline const char* Font::getMaterial() const
{
    return material.c_str();
}

void Font::setMaterial(const std::string& material)
{
    this->material = material;
}

inline int Font::getSize() const
{
    return this->size;
}
}  // namespace text
}  // namespace qui
#endif  // PACKAGES_QUI_QUITEXT_DEV_INCLUDE_QUI_TEXT_FONT_H_
