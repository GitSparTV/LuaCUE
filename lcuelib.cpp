#include "lcuelib.h"

const char* ErrorToString(CorsairError error)
{
	switch (error) {
	case CE_Success:
		return "CE_Success";
	case CE_ServerNotFound:
		return "CE_ServerNotFound";
	case CE_NoControl:
		return "CE_NoControl";
	case CE_ProtocolHandshakeMissing:
		return "CE_ProtocolHandshakeMissing";
	case CE_IncompatibleProtocol:
		return "CE_IncompatibleProtocol";
	case CE_InvalidArguments:
		return "CE_InvalidArguments";
	default:
		return "Unknown error";
	}
}

void cue_PushProtocolDetails(Lua, const CorsairProtocolDetails prot) {
	lua_createtable(L, 0, 5);
	lua_pushboolean(L, prot.breakingChanges);
	lua_setfield(L, -2, "breakingChanges");
	lua_pushinteger(L, prot.sdkProtocolVersion);
	lua_setfield(L, -2, "sdkProtocolVersion");
	lua_pushstring(L, prot.sdkVersion);
	lua_setfield(L, -2, "sdkVersion");
	lua_pushinteger(L, prot.serverProtocolVersion);
	lua_setfield(L, -2, "serverProtocolVersion");
	lua_pushstring(L, prot.serverVersion);
	lua_setfield(L, -2, "serverVersion");

	lua_setglobal(L, "ProtocolDetails");
}

function cue_GetDeviceCount(Lua) {
	lua_pushinteger(L, CorsairGetDeviceCount());
	return 1;
}

function cue_GetLastError(Lua) {
	lua_pushinteger(L, CorsairGetLastError());
	return 1;
}

function cue_GetLastErrorString(Lua) {
	lua_pushstring(L, ErrorToString(CorsairGetLastError()));
	return 1;
}

function cue_LEDID(Lua) {
	const char * s = luaL_checkstring(L, 1);
	lua_pushinteger(L,CorsairGetLedIdForKeyName(s[0]));
	return 1;
}

#include <Windows.h>
#include <conio.h>
#include <stdio.h>
function cue_IsKeyDown(Lua) {
	if (GetKeyState(luaL_checkinteger(L,1)) & 0x8000) {
		lua_pushinteger(L, true);
		return 1;
	}
	lua_pushboolean(L, false);
	return 1;
}

function cue_CPUClock(Lua) {
	LARGE_INTEGER t, f;
	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);

	lua_pushnumber(L, (double)t.QuadPart / (double)f.QuadPart);
	return 1;
}

function cue_SetPriority(Lua) {
	int priority = luaL_checkinteger(L, 1);
	luaL_argcheck(L, priority < 0 or priority > 255, 1, "Range [0;255] expected");

	lua_pushboolean(L, CorsairSetLayerPriority(priority));
	
	return 1;
}

function cue_RequestControl(Lua) {
	lua_pushboolean(L, CorsairRequestControl(CAM_ExclusiveLightingControl));
	return 1;
}

function cue_CorsairReleaseControl(Lua) {
	lua_pushboolean(L, CorsairReleaseControl(CAM_ExclusiveLightingControl));
	return 1;
}

static int enumsize(const EnumLookup* el) {
	int size = 0;
	for (; el->name; el++) size++;
	return size;
}

#define PushEnums(enname) 	for(int i = 0; i < enumsize((const EnumLookup*)enname ## Set); i++) { \
lua_pushinteger(L, enname ## Set[i].en); \
lua_setglobal(L, enname ## Set[i].name); \
} \

static const struct luaL_Reg CorsairLibraryFunctions[] = {
	{"GetDeviceCount",cue_GetDeviceCount},
	{"GetLastError", cue_GetLastError},
	{"GetLastErrorString", cue_GetLastErrorString},
	{"SetPriority", cue_SetPriority},
	{"RequestControl", cue_RequestControl},
	{"ReleaseControl", cue_CorsairReleaseControl},
	{NULL, NULL}
};

LUALIB_API int luaopen_cue(Lua) {

	// CorsairError
	PushEnums(CorsairDeviceType);
	PushEnums(CorsairPhysicalLayout);
	PushEnums(CorsairLogicalLayout);
	PushEnums(CorsairDeviceCaps);
	PushEnums(CorsairAccessMode);
	PushEnums(CorsairError);
	PushEnums(CorsairChannelDeviceType);
	PushEnums(CorsairDevicePropertyType);
	PushEnums(CorsairDevicePropertyId);
	PushEnums(CorsairEventId);
	PushEnums(CorsairLedId);

	luaL_newlib(L, CorsairLibraryFunctions);

	lua_setglobal(L, "cue");
	lua_register(L, "IsKeyDown", cue_IsKeyDown);
	lua_register(L, "LEDID", cue_LEDID);
	lua_register(L, "CPUClock", cue_CPUClock);

	cue_importdevice(L);

	return 0;
}