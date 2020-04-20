#pragma once
#include <Windows.h>

#define function static int
#define Lua lua_State* L
#define For(start,end) for(int i = start; i <= end; i++)
#define print(str) printf("%s\n",str)
#define newindexs(id,name) lua_setfield(L, id, name)
#define newindex(id,n) lua_rawseti(L, id, n)
#define lua_errhandler lua_rawgeti(L,LUA_REGISTRYINDEX,LUA_ERRORINDEX)
#define xpcall(args,rets) if (lua_pcall(L, args, rets, -(args) - 2) != LUA_OK) lua_pop(L,1);

extern int LUA_ERRORINDEX;
static HANDLE hConsole;

static void PrintStack(Lua, int blist = 0)
{
	int top = lua_gettop(L);
	SetConsoleTextAttribute(hConsole, 14);
	printf("Stack (%d):\n", top);
	SetConsoleTextAttribute(hConsole, 10);
	for (int i = 1; i <= top; i++) {
		if (i == blist) continue;
		lua_getglobal(L, "tostring");
		lua_pushvalue(L, i);
		lua_call(L, 1, 1);
		printf("  %d  =  %s (%s)\n", i, lua_tostring(L, -1), luaL_typename(L, i));
		lua_pop(L, 1);
	}
	SetConsoleTextAttribute(hConsole, 15);
	printf("\n");
	return;
}

static void l_message(const char* pname, const char* msg)
{
	if (pname) { fputs(pname, stderr); fputc(':', stderr); fputc(' ', stderr); }
	fputs(msg, stderr); fputc('\n\n', stderr);
	fflush(stderr);
}

static void PrintError(lua_State* L)
{
	if (!lua_isnil(L, -1)) {
		const char* msg = lua_tostring(L, -1);
		if (msg == NULL) msg = "(error object is not a string)";
		l_message("LuaCUE", msg);
		lua_pop(L, 1);
	}
}

static int ErrorHandler(lua_State* L)
{
	SetConsoleTextAttribute(hConsole, 12);
	if (!lua_isstring(L, 1)) { /* Non-string error object? Try metamethod. */
		if (lua_isnoneornil(L, 1) || !luaL_callmeta(L, 1, "__tostring") || !lua_isstring(L, -1)) {
			PrintError(L);
			return 1;  /* Return non-string error object. */
		}
		lua_remove(L, 1);  /* Replace object by result of __tostring metamethod. */
	}
	luaL_traceback(L, L, lua_tostring(L, 1), 1);
	PrintError(L);
	SetConsoleTextAttribute(hConsole, 15);
	return 1;
}