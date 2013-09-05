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

#include <gtest/gtest.h>
#include <qui/XMLSerializer.h>
#include <qui/ReflectableObject.h>
#include <qui/ReflectionManager.h>
#include <qui/VirtualFS.h>
#include <string>
#include <vector>

class TestSerializer : public testing::Test
{
};

class TextureDescriptor : public qui::ReflectableObject
{
 public:
     TextureDescriptor()
     {
     }
     std::string name;
     std::string image;

     static qui::TypeInfo* getClassMapping(size_t* numMapTypes)
     {
        START_TYPES_DECLARATION(TextureDescriptor, 2);
        DEFINE_TYPE(0, TextureDescriptor, name, qui::STRING, sValue);
        DEFINE_TYPE(1, TextureDescriptor, image, qui::STRING, sValue);
        return mappings;
     }
     REFLECTION_FUNCTIONS(TextureDescriptor);
};

class ResourcesLibrary : public qui::ReflectableObject
{
 public:
     ResourcesLibrary()
     {
     }

     ~ResourcesLibrary()
     {
         for (std::vector<TextureDescriptor*>::iterator it = textures->begin()
            ; it != textures->end()
            ; it++)
         {
             TextureDescriptor* element = *it;
             delete element;
             element = NULL;
         }
         textures->clear();
         delete textures;
         textures = NULL;
     }
     std::vector<TextureDescriptor*>* textures;

     static qui::TypeInfo* getClassMapping(size_t* numMapTypes)
     {
        START_TYPES_DECLARATION(ResourcesLibrary, 1);
        DEFINE_POINTER(0, ResourcesLibrary, textures, qui::POINTER, pValue);
        return mappings;
     }
     REFLECTION_FUNCTIONS(ResourcesLibrary);
};

qui::ReflectionMapping mappings[] =                                            // NOLINT
    {{"TextureDescriptor", &qui::createReflectableObject<TextureDescriptor>}   // NOLINT
   , {"ResourcesLibrary", &qui::createReflectableObject<ResourcesLibrary>}};   // NOLINT

TEST_F(TestSerializer, TestDeserialize)  // NOLINT
{
    qui::ReflectionManager rm;
    rm.setClassMappings(mappings, 2);
    rm.setTypeMappings<TextureDescriptor>();
    rm.setTypeMappings<ResourcesLibrary>();
    qui::VirtualFS fs;
    fs.addRelativePath("../../../");
    qui::XMLSerializer xmlSerializer("tools/testdata/testrefl.xml");
    std::auto_ptr<qui::ReflectableObject> object(xmlSerializer.deserialize("ResourcesLibrary"));
    ASSERT_TRUE(object.get());
    ResourcesLibrary* library = reinterpret_cast<ResourcesLibrary*>(object.get());
    ASSERT_TRUE(library->textures);
    ASSERT_EQ(library->textures->size(), 2);
    TextureDescriptor *descriptor = library->textures->at(0);
    ASSERT_NE(descriptor->name.find("Boat"), std::string::npos);
    ASSERT_NE(descriptor->image.find("assets/boat.png"), std::string::npos);
    descriptor = library->textures->at(1);
    ASSERT_NE(descriptor->name.find("Test"), std::string::npos);
    ASSERT_NE(descriptor->image.find("testimg.png"), std::string::npos);
}
