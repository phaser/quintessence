// Copyright (C) 2012 Cristian Bidea
#include <qui/MemoryProfile.h>
#include <qui/cpp11compat.h>
#include <qui/log.h>
#include <ext/malloc_allocator.h>
#include <utility>
#include <functional>

#if 0
uint64_t currentUsedMemory = 0;
uint64_t memoryUsedBeforeInit = 0;
std::auto_ptr <cpp0x::unordered_map <
              size_t
            , size_t
            , cpp0x::hash<size_t>
            , std::equal_to<size_t>
            , __gnu_cxx::malloc_allocator<std::pair<const size_t&, size_t> >
> > allocPointers(new cpp0x::unordered_map<
              size_t
            , size_t
            , cpp0x::hash<size_t>
            , std::equal_to<size_t>
            , __gnu_cxx::malloc_allocator<std::pair<const size_t&, size_t> > >());

size_t getPointerSize(size_t address)
{
    if (allocPointers.get())
    {
        return 0;
    }

    cpp0x::unordered_map<size_t, size_t>::iterator it = allocPointers->find(address);
    if (it != allocPointers->end())
    {
        return it->second;
    }
    else
    {
        LOG(LERROR) << "pointer: " << address << " doesn't exists in list!";
        return 0;
    }
    return 0;
}

void* customAllocMemory(size_t sz)
{
    void *ptr = malloc(sz);
    if (ptr != nullptr && allocPointers.get())
    {
        size_t address = (size_t)ptr;
        allocPointers->insert(std::make_pair(address, sz));
        currentUsedMemory += sz;
    }
    else
    {
        memoryUsedBeforeInit += sz;
    }
    return ptr;
}

void *operator new(size_t sz) throw(std::bad_alloc)
{
    return customAllocMemory(sz);
}

void *operator new[](size_t sz) throw(std::bad_alloc)
{
    return customAllocMemory(sz);
}

void operator delete (void* ptr) throw()
{
    if (currentUsedMemory != 0)
    {
        currentUsedMemory -= getPointerSize((size_t)ptr);
    }
    if (ptr == allocPointers.get())
    {
        LOG(INFO) << "Current use memory: " << currentUsedMemory;
    }
    free(ptr);
}

void operator delete[] (void* ptr) throw()
{
    if (currentUsedMemory != 0)
    {
        currentUsedMemory -= getPointerSize((size_t)ptr);
    }
    free(ptr);
}
#endif
#include <qui/log.h>
class MemoryUtils
{
public:
    ~MemoryUtils()
    {
        LOG(INFO) << "Current mem: " << currentUsedMemory;
    }
    static uint64_t currentUsedMemory;
};
uint64_t MemoryUtils::currentUsedMemory = 0;
static MemoryUtils mutils;

void *operator new(size_t sz) throw(std::bad_alloc)
{
    MemoryUtils::currentUsedMemory += sz;
    return malloc(sz);
}

void *operator new[](size_t sz) throw(std::bad_alloc)
{
    MemoryUtils::currentUsedMemory += sz;
    return malloc(sz);
}
void operator delete(void* ptr, size_t sz) throw()
{
    MemoryUtils::currentUsedMemory -= sz;
    free(ptr);
}

void operator delete[](void* ptr, size_t sz) throw()
{
    MemoryUtils::currentUsedMemory -= sz;
    free(ptr);
}
