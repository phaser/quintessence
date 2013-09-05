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
#include <qui/text/FontManager.h>
#include <qui/text/Font.h>
#include <qui/log.h>
#include <string>

namespace qui
{
namespace text
{
UniversalHashStore<cpp0x::shared_ptr<Font> > FontManager::fonts;

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

bool FontManager::loadFont(size_t fontId, const std::string& path)
{
    cpp0x::shared_ptr<qui::text::Font> font(new qui::text::Font(path));
    if (!font->load())
    {
        LOG(LERROR) << "Font " << font->getFontName() << " did not load!";
        return false;
    }
    fonts.store(fontId, font);
    return true;
}

cpp0x::shared_ptr<Font> FontManager::getFont(size_t fontId)
{
    if (fonts.exists(fontId))
    {
        return fonts.get(fontId);
    }
    return cpp0x::shared_ptr<Font>(reinterpret_cast<Font*>(NULL));
}
}  // namespace text
}  // namespace qui
