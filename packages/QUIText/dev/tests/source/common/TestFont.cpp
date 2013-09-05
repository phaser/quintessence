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
#include <gtest/gtest.h>
#include <qui/text/Font.h>
#include <qui/VirtualFS.h>
#include <string.h>
#include "../../../source/common/Glyph.h"

class FontTests : public testing::Test
{
};

TEST_F(FontTests, Font_load)  // NOLINT
{
    qui::VirtualFS fs;
    fs.addRelativePath("../../../");
    qui::text::Font font("tools/testdata/testfont.fnt");
    font.load();
    // Test some header properties
    const char *result = strstr(font.getFontName(), "HeadLineA");
    EXPECT_EQ((result != NULL), true);
    result = strstr(font.getMaterial(), "testfont.png");
    EXPECT_EQ((result != NULL), true);

    // Test that I get a null shared_ptr if the character
    // doesn't exists
    EXPECT_TRUE(font.getGlyphForChar(200).get() != NULL);

    // Test the properties of a couple of characters to
    // verify that the load is correct
    cpp0x::shared_ptr<Glyph> glyph = font.getGlyphForChar(33);
    EXPECT_EQ(glyph->charId, 33);
    EXPECT_EQ(glyph->position.x, 360);
    EXPECT_EQ(glyph->position.y, 72);
    EXPECT_EQ(glyph->size.x, 20);
    EXPECT_EQ(glyph->size.y, 44);
    EXPECT_EQ(glyph->xadvance, 20);

    glyph = font.getGlyphForChar(74);
    EXPECT_EQ(glyph->charId, 74);
    EXPECT_EQ(glyph->position.x, 114);
    EXPECT_EQ(glyph->position.y, 164);
    EXPECT_EQ(glyph->size.x, 30);
    EXPECT_EQ(glyph->size.y, 44);
    EXPECT_EQ(glyph->xadvance, 29);
}

