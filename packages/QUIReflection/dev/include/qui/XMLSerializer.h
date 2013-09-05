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

#ifndef PACKAGES_QUI_QUIREFLECTION_DEV_INCLUDE_QUI_XMLSERIALIZER_H_
#define PACKAGES_QUI_QUIREFLECTION_DEV_INCLUDE_QUI_XMLSERIALIZER_H_
#include <string>

class TiXmlElement;

namespace qui
{
class ReflectableObject;

class XMLSerializer
{
 public:
     explicit XMLSerializer(const std::string& fileName);
     ~XMLSerializer();
     qui::ReflectableObject* deserialize(const std::string& className);
 private:
     std::string fileName;

     void processMember(const TiXmlElement *child, qui::ReflectableObject *object);
     ReflectableObject* processObject(const TiXmlElement* root, const std::string& xmlClassName);
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIREFLECTION_DEV_INCLUDE_QUI_XMLSERIALIZER_H_
