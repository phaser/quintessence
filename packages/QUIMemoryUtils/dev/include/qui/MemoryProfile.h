// Copyright (C) 2012 Cristian Bidea
#ifndef PACKAGES_QUI_QUIMEMORYUTILS_DEV_INCLUDE_QUI_MEMORYPROFILE_H_
#define PACKAGES_QUI_QUIMEMORYUTILS_DEV_INCLUDE_QUI_MEMORYPROFILE_H_
#include <stdlib.h>
#include <stdint.h>
#include <qui/cpp11compat.h>
#include <ext/malloc_allocator.h>

void *operator new(size_t sz) throw(std::bad_alloc);
void *operator new[](size_t sz) throw(std::bad_alloc);
void operator delete(void* ptr) throw();
void operator delete[](void* ptr) throw();

#endif  // PACKAGES_QUI_QUIMEMORYUTILS_DEV_INCLUDE_QUI_MEMORYPROFILE_H_
