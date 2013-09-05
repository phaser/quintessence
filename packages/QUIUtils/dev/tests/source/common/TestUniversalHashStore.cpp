// Copyright (C) 2013 Cristian Bidea
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
#include <qui/UniversalHashStore.h>
#include <qui/Hash.h>
#include <memory>

class TestUniversalHashStore : public testing::Test
{
};

struct TestStruct
{
    int a;
};

TEST_F(TestUniversalHashStore, TestStoreGet)  // NOLINT
{
    qui::UniversalHashStore<struct TestStruct*> store;
    std::auto_ptr<struct TestStruct> obj(new struct TestStruct());
    obj->a = 10;
    size_t static_hash = qui::Hash("Test string").value;
    store.store(static_hash, obj.get());
    struct TestStruct *result = store.get(static_hash);
    EXPECT_EQ(result->a, 10);
}

