#include "./LuaResourceLoadingFunctions.h"

EXPORT_OOLUA_FUNCTIONS_1_NON_CONST(LuaResourceLoadingFunctions
                                 , texture)
                                   
bool LuaResourceLoadingFunctions::texture(const char* texture)
{
    return true;
}
