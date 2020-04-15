#ifdef __APPLE__
#include <CUESDK/CUESDK.h>
#else
#include <CUESDK.h>
#endif

#include "lua.hpp"
#include "luahelpers.h"

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

const void cue_PushProtocolDetails(Lua, const CorsairProtocolDetails prot) {
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

	return;
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

function cue_GetDeviceInfo(Lua) {
	int index = luaL_checkinteger(L, 1);
	if (index <= 0 and index > CorsairGetDeviceCount()) {
		luaL_error(L, "Invalid device index.");
	}

	auto DInfo = CorsairGetDeviceInfo(index - 1);
	lua_createtable(L, 0, 8);

	lua_pushinteger(L, DInfo->type);
	newindexs(-2, "type");

	lua_pushstring(L, DInfo->model);
	newindexs(-2, "model");

	lua_pushinteger(L, DInfo->physicalLayout);
	newindexs(-2, "physicalLayout");

	lua_pushinteger(L, DInfo->logicalLayout);
	newindexs(-2, "logicalLayout");

	lua_pushinteger(L, DInfo->capsMask);
	newindexs(-2, "capsMask");

	lua_pushinteger(L, DInfo->ledsCount);
	newindexs(-2, "ledsCount");

	lua_createtable(L, DInfo->channels.channelsCount, 0);
	auto channels = DInfo->channels.channels;

	for (int i = 0; i < DInfo->channels.channelsCount; i++) {
		lua_createtable(L, 0, 2);

		lua_pushinteger(L, channels[i].totalLedsCount);
		newindexs(-2, "totalLedsCount");

		lua_createtable(L, channels[i].devicesCount, 0);

		auto devices = channels[i].devices;
		for (int i = 0; i < channels[i].devicesCount; i++) {
			lua_createtable(L, 0, 2);

			lua_pushinteger(L, devices[i].deviceLedCount);
			newindexs(-2, "deviceLedCount");

			lua_pushinteger(L, devices[i].type);
			newindexs(-2, "type");
		}
		newindex(-2, i);
	}
	newindexs(-2, "channels");

	lua_pushstring(L, DInfo->deviceId);
	newindexs(-2, "deviceId");

	return 1;
}

typedef struct EnumLookup {
	const char* name;
	int en;
} EnumLookup;

#define EnumToString(en) static const EnumLookup en ## Set[]

static int enumsize(const EnumLookup* el) {
	int size = 0;
	for (; el->name; el++) size++;
	return size;
}

EnumToString(CorsairDeviceType) = {
	{"CDT_Unknown", 0},
	{"CDT_Mouse", 1},
	{"CDT_Keyboard", 2},
	{"CDT_Headset", 3},
	{"CDT_MouseMat", 4},
	{"CDT_HeadsetStand", 5},
	{"CDT_CommanderPro", 6},
	{"CDT_LightingNodePro", 7},
	{"CDT_MemoryModule", 8},
	{"CDT_Cooler", 9},
	{NULL,NULL}
};

EnumToString(CorsairPhysicalLayout) = {
	{"CPL_Invalid", 0},

	{"CPL_US", 1},
	{"CPL_UK", 2},
	{"CPL_BR", 3},
	{"CPL_JP", 4},
	{"CPL_KR", 5},

	{"CPL_Zones1", 6},
	{"CPL_Zones2", 7},
	{"CPL_Zones3", 8},
	{"CPL_Zones4", 9},
	{NULL,NULL}
};

EnumToString(CorsairLogicalLayout) = {
	{"CLL_Invalid", 0},
	{"CLL_US_Int", 1},
	{"CLL_NA", 2},
	{"CLL_EU", 3},
	{"CLL_UK", 4},
	{"CLL_BE", 5},
	{"CLL_BR", 6},
	{"CLL_CH", 7},
	{"CLL_CN", 8},
	{"CLL_DE", 9},
	{"CLL_ES", 10},
	{"CLL_FR", 11},
	{"CLL_IT", 12},
	{"CLL_ND", 13},
	{"CLL_RU", 14},
	{"CLL_JP", 15},
	{"CLL_KR", 16},
	{"CLL_TW", 17},
	{"CLL_MEX", 18},
	{NULL,NULL}
};

EnumToString(CorsairDeviceCaps) = {
	{"CDC_None", 0x0000},
	{"CDC_Lighting", 0x0001},
	{"CDC_PropertyLookup", 0x0002},
	{NULL,NULL}
};

EnumToString(CorsairAccessMode) = {
	{"CAM_ExclusiveLightingControl", 0},
	{NULL,NULL}
};

EnumToString(CorsairError) = {
	{"CE_Success", 0},
	{"CE_ServerNotFound", 1},
	{"CE_NoControl", 2},
	{"CE_ProtocolHandshakeMissing", 3},
	{"CE_IncompatibleProtocol", 4},
	{"CE_InvalidArguments", 5},
	{NULL,NULL}
};

EnumToString(CorsairChannelDeviceType) = {
	{"CCDT_Invalid", 0},
	{"CCDT_HD_Fan", 1},
	{"CCDT_SP_Fan", 2},
	{"CCDT_LL_Fan", 3},
	{"CCDT_ML_Fan", 4},
	{"CCDT_Strip", 5},
	{"CCDT_DAP", 6},
	{"CCDT_Pump", 7},
	{NULL,NULL}
};

EnumToString(CorsairDevicePropertyType) = {
	{"CDPT_Boolean", 0x1000},
	{"CDPT_Int32", 0x2000},
	{NULL,NULL}
};

EnumToString(CorsairDevicePropertyId) = {
	{"CDPI_Headset_MicEnabled", 0x1000},
	{"CDPI_Headset_SurroundSoundEnabled", 0x1001},
	{"CDPI_Headset_SidetoneEnabled", 0x1002},
	{"CDPI_Headset_EqualizerPreset", 0x2000},
	{NULL,NULL}
};

EnumToString(CorsairEventId) = {
	{"CEI_Invalid", 0},
	{"CEI_DeviceConnectionStatusChangedEvent", 1},
	{"CEI_KeyEvent", 2},
	{NULL,NULL}
};

#define PushEnums(enname) 	for(int i = 0; i < enumsize((const EnumLookup*)enname ## Set); i++) { \
lua_pushinteger(L, enname ## Set[i].en); \
lua_setglobal(L, enname ## Set[i].name); \
} \

#define PushFunction(name) lua_pushcfunction(L,cue_ ## name); lua_setglobal(L,#name)

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

	PushFunction(GetDeviceCount);
	PushFunction(GetLastError);
	PushFunction(GetLastErrorString);
	PushFunction(GetDeviceInfo);

	return 0;
}