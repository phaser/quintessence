#pragma once
#include <oolua.h>
#include <lua_table.h>

class LuaResourceLoadingFunctions
{
    bool texture(const char* texture);
};

OOLUA_CLASS_NO_BASES(LuaResourceLoadingFunctions)
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
    OOLUA_MEM_FUNC(void, texture, const char*)
OOLUA_CLASS_END
