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

#include <qui/XMLSerializer.h>
#include <qui/ReflectableObject.h>
#include <qui/ReflectionManager.h>
#include <qui/VirtualFS.h>
#include <tinyxml.h>
#include <string>
#include <vector>

namespace qui
{
XMLSerializer::XMLSerializer(const std::string& fileName)
    : fileName(fileName)
{
}

XMLSerializer::~XMLSerializer()
{
}

qui::ReflectableObject* XMLSerializer::deserialize(const std::string& className)
{
    qui::VirtualFS fs;
    qui::ReflectionManager rm;

    cpp0x::shared_ptr<char> contents = fs.getFileContentsAsText(this->fileName);
    if (!contents.get())
    {
        LOG(LERROR) << "Error occured while reading file -> " << this->fileName << "!";
        return NULL;
    }
    TiXmlDocument document;
    document.Parse(contents.get(), 0, TIXML_ENCODING_UTF8);
    const TiXmlElement* root = document.FirstChildElement("object");
    if (!root)
    {
        LOG(LERROR) << "Bad serialization format: couldn't find object tag!";
        return NULL;
    }
    const char* xmlClassName = root->Attribute("class");
    if (!xmlClassName)
    {
        LOG(LERROR) << "Bad serialization format: object doesn't have a class attribute!";
        return NULL;
    }
    // TODO(cbidea): Verify if xmlClassName == className
    return processObject(root, xmlClassName);
}


void XMLSerializer::processMember(const TiXmlElement *child, qui::ReflectableObject *object)
{
    qui::ReflectionManager rm;
    std::string memberId = child->Attribute("id");
    std::string memberType = child->Attribute("type");
    if (memberType.find("array") == std::string::npos)
    {
        std::string value = child->GetText();
        object->setValue(memberId, value);
    }
    else
    {
        std::vector<ReflectableObject*>* array = new std::vector<ReflectableObject*>();
        child = child->FirstChildElement("object");
        while (child)
        {
            std::string xmlClassName = child->Attribute("class");
            ReflectableObject *object = processObject(child, xmlClassName);
            if (object)
            {
                array->push_back(object);
            }
            else
            {
                LOG(LERROR) << "Couldn't parse object!";
            }
            child = child->NextSiblingElement();
        }
        object->setPointer(memberId, array);
    }
}

ReflectableObject* XMLSerializer::processObject(const TiXmlElement* root, const std::string& xmlClassName)
{
    qui::ReflectionManager rm;
    qui::ReflectableObject *object = rm.getInstanceForClassName(xmlClassName);
    if (!object)
    {
        LOG(LERROR) << "Deserialization error! Class is not reflectable!";
        return NULL;
    }
    const TiXmlElement* child = root->FirstChildElement("member");
    if (!child)
    {
        return object;
    }
    while (child)
    {
        processMember(child, object);
        child = child->NextSiblingElement();
    }
    return object;
}
}  // namespace qui
