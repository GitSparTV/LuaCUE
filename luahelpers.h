#pragma once

#define then
#define end
#define do
#define function static int
#define Lua lua_State* L
#define For(start,end) for(int i = start; i <= end; i++)
#define print(str) printf("%s\n",str)
#define and &&
#define newindexs(id,name) lua_setfield(L, id, name)
#define newindex(id,n) lua_rawseti(L, id, n)