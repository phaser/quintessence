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

#ifndef PACKAGES_QUI_QUIREFLECTION_DEV_INCLUDE_QUI_REFLECTIONMANAGER_H_
#define PACKAGES_QUI_QUIREFLECTION_DEV_INCLUDE_QUI_REFLECTIONMANAGER_H_
#include <qui/cpp11compat.h>
#include <string>
#include <map>
namespace qui
{
class ReflectableObject;
struct Mapping;
typedef struct Mapping ReflectionMapping;
typedef qui::ReflectableObject* (*ReflectableObjectConstructor) ();
struct TypeInfo;
class TypeMappingBase;

class ReflectionManager
{
 public:
    ReflectionManager();
    ReflectableObject* getInstanceForClassName(const std::string& className);
    cpp0x::shared_ptr<TypeMappingBase> getType(const std::string& memberName);
    void setClassMappings(const qui::ReflectionMapping mappings[], size_t count);
    void setTypesMappings(qui::TypeInfo* mappings, size_t count);

    template <typename T>
    void setTypeMappings()
    {
        size_t num = 0;
        qui::TypeInfo* types = T::getClassMapping(&num);
        setTypesMappings(types, num);
        delete [] types;
    }
 protected:
    ReflectionManager(const ReflectionManager&)
    {
    }
 private:
    static std::map<std::string, ReflectableObjectConstructor> classes;
    static std::map<std::string, cpp0x::shared_ptr<TypeMappingBase> > types;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIREFLECTION_DEV_INCLUDE_QUI_REFLECTIONMANAGER_H_
