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
#include <qui/log.h>
#include <map>
#include <string>
#include <algorithm>

namespace qui
{
std::map<std::string, ReflectableObjectConstructor> ReflectionManager::classes;
std::map<std::string, cpp0x::shared_ptr<TypeMappingBase> > ReflectionManager::types;

ReflectionManager::ReflectionManager()
{
}

ReflectableObject* ReflectionManager::getInstanceForClassName(const std::string& className)
{
    std::map<std::string, ReflectableObjectConstructor>::iterator it = classes.find(className);
    if (it != classes.end())
    {
        ReflectableObject* obj = ((*it->second)());
        obj->setClassName(className);
        return obj;
    }
    LOG(LERROR) << "Class " << className << " doesn't exist or it wasn't mapped!";
    return NULL;
}

void ReflectionManager::setClassMappings(const qui::ReflectionMapping mappings[], size_t count)
{
    std::transform(mappings
                 , mappings + count
                 , inserter(classes, classes.begin())
                 , mem_fun_ref(&qui::ReflectionMapping::makepair));
}

void ReflectionManager::setTypesMappings(qui::TypeInfo* mappings, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        types.insert(mappings[i].makepair());
    }
}

cpp0x::shared_ptr<TypeMappingBase> ReflectionManager::getType(const std::string& memberName)
{
    std::map<std::string, cpp0x::shared_ptr<TypeMappingBase> >::iterator it = types.find(memberName);
    if (it == types.end())
    {
        return cpp0x::shared_ptr<TypeMappingBase>(static_cast<TypeMappingBase*>(NULL));
    }
    return it->second;
}
}  // namespace qui
