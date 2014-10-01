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

#ifndef PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_CPP11COMPAT_H_
#define PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_CPP11COMPAT_H_

#if defined(PLATFORM_WEB) || defined(PLATFORM_WIN32) || defined(PLATFORM_OSX) || defined(PLATFORM_IOS) || defined(PLATFORM_QT5)
#include <unordered_map>
#include <memory>
namespace cpp0x = std;
#else
#include <tr1/memory>  // NOLINT
#include <tr1/unordered_map>  // NOLINT
namespace cpp0x = std::tr1;
#endif

#if _MSC_VER
#define snprintf _snprintf
#endif

template<typename T>
struct array_deleter
{
    void operator()(T* p)
    {
        if (!p)
        {
            return;
        }
        delete [] p;
        p = NULL;
    }
};

#endif  // PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_CPP11COMPAT_H_
