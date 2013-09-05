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
#ifndef PACKAGES_QUI_QUITEXT_DEV_INCLUDE_QUI_TEXT_FONTMANAGER_H_
#define PACKAGES_QUI_QUITEXT_DEV_INCLUDE_QUI_TEXT_FONTMANAGER_H_
#include <qui/UniversalHashStore.h>
#include <qui/cpp11compat.h>
#include <string>

namespace qui
{
namespace text
{
class Font;
class FontManager
{
 public:
    FontManager();
    ~FontManager();
    bool loadFont(size_t fontId, const std::string& path);
    cpp0x::shared_ptr<Font> getFont(size_t fontId);
 private:
    static UniversalHashStore<cpp0x::shared_ptr<Font> > fonts;
};
}  // namespace text
}  // namespace qui
#endif  // PACKAGES_QUI_QUITEXT_DEV_INCLUDE_QUI_TEXT_FONTMANAGER_H_

