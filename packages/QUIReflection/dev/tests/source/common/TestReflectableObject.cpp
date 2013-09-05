// Copyright (C) 2012 Cristian Bidea
// This file is part of QUIReflection.
//
//    QUIReflection is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    QUIReflection is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with QUIReflection.  If not, see <http://www.gnu.org/licenses/>.

#include <qui/ReflectionManager.h>
#include <qui/ReflectableObject.h>
#include <gtest/gtest.h>
#include <stdio.h>
#include <string>

class TestReflectableObject : public testing::Test
{
};

class MyClass : public qui::ReflectableObject
{
 public:
    MyClass()
        : i(123)
    {
    }

    int i;
    std::string v;

    static qui::TypeInfo* getClassMapping(size_t* numMapTypes)
    {
       START_TYPES_DECLARATION(MyClass, 2);
       DEFINE_TYPE(0, MyClass, i, qui::INT, iValue);
       DEFINE_TYPE(1, MyClass, v, qui::STRING, sValue);
       return mappings;
    }
    REFLECTION_FUNCTIONS(MyClass);
};

class TestPrivateMembers : public qui::ReflectableObject
{
 public:
    static qui::TypeInfo* getClassMapping(size_t* numMapTypes)
    {
       START_TYPES_DECLARATION(TestPrivateMembers, 2);
       DEFINE_TYPE(0, TestPrivateMembers, i, qui::INT, iValue);
       DEFINE_TYPE(1, TestPrivateMembers, v, qui::STRING, sValue);
       return mappings;
    }
    REFLECTION_FUNCTIONS(TestPrivateMembers);

    int getI() const
    {
        return i;
    }

    std::string getV() const
    {
        return v;
    }
 private:
    int i;
    std::string v;
};

TEST_F(TestReflectableObject, BasicTests)  // NOLINT
{
    qui::ReflectionMapping mappings[] = {{"MyClass", &qui::createReflectableObject<MyClass>}};  // NOLINT
    qui::ReflectionManager rm;
    rm.setTypeMappings<MyClass>();
    rm.setClassMappings(mappings, 1);

    MyClass* testClass = reinterpret_cast<MyClass*>(rm.getInstanceForClassName("MyClass"));
    ASSERT_TRUE(testClass);
    ASSERT_EQ(testClass->i, 123);
    testClass->setValue("i", "423");
    ASSERT_EQ(testClass->i, 423);
    testClass->setValue("v", "test simplu");
    ASSERT_EQ(testClass->v.find("test simplu"), 0);
    delete testClass;
}

TEST_F(TestReflectableObject, TestPrivateMembers)  // NOLINT
{
    qui::ReflectionMapping mappings[] = {{"TestPrivateMembers", &qui::createReflectableObject<TestPrivateMembers>}};  // NOLINT
    qui::ReflectionManager rm;
    rm.setTypeMappings<TestPrivateMembers>();
    rm.setClassMappings(mappings, 1);

    TestPrivateMembers* testClass = reinterpret_cast<TestPrivateMembers*>
                                    (rm.getInstanceForClassName("TestPrivateMembers"));
    ASSERT_TRUE(testClass);
    testClass->setValue("i", "423");
    ASSERT_EQ(testClass->getI(), 423);
    testClass->setValue("v", "test simplu");
    ASSERT_EQ(testClass->getV().find("test simplu"), 0);
    delete testClass;
}


