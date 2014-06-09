#pragma once
#include <oolua.h>
#include <lua_table.h>

class LuaResourceLoadingFunctions
{
public:
    unsigned int texture(const char* texture);
    unsigned int shader(const char* name, const char* vertex, const char* fragment);
    bool atlas(const char* filename);
    bool material(const char* name, unsigned int shader, unsigned int texture); 
    bool font(const char* name, const char* filename, const char* material);
};

OOLUA_CLASS_NO_BASES(LuaResourceLoadingFunctions)
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
    OOLUA_MEM_FUNC(unsigned int, texture, const char*)
    OOLUA_MEM_FUNC(unsigned int, shader, const char*, const char*, const char*)
    OOLUA_MEM_FUNC(bool, atlas, const char*)
    OOLUA_MEM_FUNC(bool, material, const char*, unsigned int, unsigned int)
    OOLUA_MEM_FUNC(bool, font, const char*, const char*, const char*)
OOLUA_CLASS_END
