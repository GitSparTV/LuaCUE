#pragma once
#ifdef __APPLE__
#include <CUESDK/CUESDK.h>
#else
#include <CUESDK.h>
#endif
#include "lua.hpp"

const char* ErrorToString(CorsairError error);
LUALIB_API int luaopen_cue(lua_State* L);
void cue_PushProtocolDetails(lua_State* L, const CorsairProtocolDetails prot);