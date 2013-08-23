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

#ifndef PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_HASH_H_
#define PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_HASH_H_
#include <string.h>
#ifdef PLATFORM_WIN32
#define ME_INLINE __forceinline
#else
#define ME_INLINE __attribute__((always_inline))
#endif
/*
 * This code is taken from
 * http://www.altdevblogaday.com/2011/10/27/quasi-compile-time-string-hashing/
 */
#include <stdint.h>
#define CT_ITOA(x) #x
#define HASH(x) qui::Hash(x).value
typedef unsigned int int_hash;
namespace qui
{
template <unsigned int N, unsigned int I>
struct FnvHash
{
  static ME_INLINE unsigned int DoHash(const char (&str)[N])
  {
    return (FnvHash<N, I-1>::DoHash(str) ^ str[I-1])*16777619u;
  }
};

template <unsigned int N>
struct FnvHash<N, 1>
{
  static ME_INLINE unsigned int DoHash(const char (&str)[N])
  {
    return (2166136261u ^ str[0])*16777619u;
  }
};

class Hash
{
 public:
    unsigned int CalculateFNV(const char* str)
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

    template <unsigned int N>
    ME_INLINE Hash(const char (&str)[N])
        : value(FnvHash<N, N>::DoHash(str))
    {
    }

    struct ConstCharWrapper
    {
        inline ConstCharWrapper(const char* str) : m_str(str)  // NOLINT
        {
        }
        const char* m_str;
    };

    Hash(ConstCharWrapper str)  // NOLINT
        : value(CalculateFNV(str.m_str))
    {
    }

    unsigned int value;
};
}  // namespace qui
#endif  // PACKAGES_QUI_QUIUTILS_DEV_INCLUDE_QUI_HASH_H_
