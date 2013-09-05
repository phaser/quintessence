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

#ifndef PACKAGES_QUI_QUIREFLECTION_DEV_INCLUDE_QUI_REFLECTABLEOBJECT_H_
#define PACKAGES_QUI_QUIREFLECTION_DEV_INCLUDE_QUI_REFLECTABLEOBJECT_H_

#include <qui/log.h>
#include <qui/cpp11compat.h>
#include <qui/ReflectionManager.h>
#include <string>
#include <utility>
#include <map>
#include <algorithm>
#include <memory>

#define REFLECTION_FUNCTIONS(MY_TYPE) \
    void setValue(const std::string& memberName, const std::string& value)\
    {  /* NOLINT */\
        this->setValueT<MY_TYPE>(memberName, value);\
    }  /* NOLINT */\
    void setPointer(const std::string& memberName, void* value)\
    {  /* NOLINT */\
        this->setValueT<MY_TYPE>(memberName, value);\
    }  /* NOLINT */

#define START_TYPES_DECLARATION(CLASS_NAME, NUM_TYPES) \
    *numMapTypes = NUM_TYPES;\
    qui::TypeInfo* mappings = new qui::TypeInfo[NUM_TYPES];\
    qui::TypeMapping<CLASS_NAME> *tmp;

#define DEFINE_TYPE(TYPE_NUM, CLASS_NAME, NAME, TYPE, POINTER) \
    tmp = new qui::TypeMapping<CLASS_NAME>();\
    mappings[TYPE_NUM].className = #CLASS_NAME;\
    mappings[TYPE_NUM].typeName = #NAME;\
    tmp->type = TYPE;\
    tmp->value.POINTER = &CLASS_NAME::NAME;\
    mappings[TYPE_NUM].type = tmp;

#define DEFINE_POINTER(TYPE_NUM, CLASS_NAME, NAME, TYPE, POINTER) \
    tmp = new qui::TypeMapping<CLASS_NAME>();\
    mappings[TYPE_NUM].className = #CLASS_NAME;\
    mappings[TYPE_NUM].typeName = #NAME;\
    tmp->type = TYPE;\
    tmp->value.POINTER = reinterpret_cast<void* CLASS_NAME::*>(&CLASS_NAME::NAME);\
    mappings[TYPE_NUM].type = tmp;

namespace qui
{
enum ReflectableMemberType
{
    INT = 0
  , STRING
  , POINTER
};

template <typename T>
union TypePointer
{
    int T::*iValue;
    float T::*fValue;
    double T::*dValue;
    std::string T::*sValue;
    void* T::*pValue;
};

class TypeMappingBase
{
 public:
    ReflectableMemberType type;
};

template <typename T>
class TypeMapping : public TypeMappingBase
{
 public:
    union TypePointer<T> value;
};

struct TypeInfo
{
    std::string className;
    std::string typeName;
    TypeMappingBase* type;
    std::pair<std::string, cpp0x::shared_ptr<TypeMappingBase> >
    makepair() const
    {
        return std::make_pair(className + typeName, cpp0x::shared_ptr<TypeMappingBase>(type));
    }
};

class ReflectableObject
{
 public:
    ReflectableObject()
    {
    }

    virtual ~ReflectableObject()
    {
    }

    template <typename T>
    void setValueT(const std::string& memberName, const std::string& value)
    {
        ReflectionManager rm;
        std::string newMemberName = getClassName() + memberName;
        cpp0x::shared_ptr<TypeMappingBase> type = rm.getType(newMemberName);
        if (!type.get())
        {
            LOG(LERROR) << "Member " << memberName << " is not mapped!";
            return;
        }

        TypeMapping<T>* typeMapping = static_cast<TypeMapping<T>*>(type.get());
        switch (type->type)
        {
        case(INT):
        {
            static_cast<T*>(this)->*(typeMapping->value.iValue) = atoi(value.c_str());
            break;
        }
        case(STRING):
        {
            static_cast<T*>(this)->*(typeMapping->value.sValue) = value;
            break;
        }
        default:
            LOG(LERROR) << "Invalid type!";
        }
    }

    template <typename T>
    void setValueT(const std::string& memberName, void* value)
    {
        ReflectionManager rm;
        std::string newMemberName = getClassName() + memberName;
        cpp0x::shared_ptr<TypeMappingBase> type = rm.getType(newMemberName);
        if (!type.get())
        {
            LOG(LERROR) << "Member " << memberName << " is not mapped!";
            return;
        }

        TypeMapping<T>* typeMapping = static_cast<TypeMapping<T>*>(type.get());
        switch (type->type)
        {
        case(POINTER):
        {
            static_cast<T*>(this)->*(typeMapping->value.pValue) = value;
            break;
        }
        default:
            LOG(LERROR) << "Invalid type!";
        }
    }

    virtual void setValue(const std::string& memberName, const std::string& value)
    {
        LOG(WARNING) << "This should not get called. Have you forgot to overload it?";
    }

    virtual void setPointer(const std::string& memberName, void* ptr)
    {
        LOG(WARNING) << "This should not get called. Have you forgot to overload it?";
    }

    void setClassName(const std::string& className)
    {
        this->className = className;
    }

    const std::string& getClassName() const
    {
        return this->className;
    }

 private:
    std::string className;
};

template <typename T>
qui::ReflectableObject* createReflectableObject()
{
    return new T();
}

typedef qui::ReflectableObject* (*ReflectableObjectConstructor) ();

struct Mapping
{
    std::string className;
    ReflectableObjectConstructor constructor;
    std::pair<std::string, ReflectableObjectConstructor>
    makepair() const
    {
        return std::make_pair(className, constructor);
    }
};

typedef struct Mapping ReflectionMapping;

}  // namespace qui
#endif  // PACKAGES_QUI_QUIREFLECTION_DEV_INCLUDE_QUI_REFLECTABLEOBJECT_H_
