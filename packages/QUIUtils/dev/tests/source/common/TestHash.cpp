// Copyright (C) 2012 Cristian Bidea
// This file is part of QUIUtils.
//
//    QUIUtils is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIUtils is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIUtils.  If not, see <http://www.gnu.org/licenses/>.

#include <gtest/gtest.h>
#include <qui/Hash.h>
#include <stdint.h>

class TestHash : public testing::Test
{
};

unsigned int calculateFNV(const char* str)
{
  const unsigned int length = strlen(str) + 1;
  unsigned int hash = 2166136261u;
  for (unsigned int i = 0; i < length; ++i)
  {
    hash ^= *str++;
    hash *= 16777619u;
  }

  return hash;
}

TEST_F(TestHash, TestStaticHash)  // NOLINT
{
    unsigned int rt_hash = calculateFNV("Test string");
    unsigned int static_hash = qui::Hash("Test string").value;
    EXPECT_EQ(rt_hash, static_hash);
}
