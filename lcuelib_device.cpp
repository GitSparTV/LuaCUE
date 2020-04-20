#include "lcuelib_device.h"
#include <array>

#define METATABLE_NAME "CorsairDevice"

CorsairDevice::CorsairDevice(int index) : index(index)
{
	info = CorsairGetDeviceInfo(index);
	leds = CorsairGetLedPositionsByDeviceIndex(index);
}

CorsairDevice::~CorsairDevice()
{
}

void CorsairDevice::Clear()
{
	info = NULL;
	leds = NULL;
}

void CorsairDevice::Reinitialize()
{
	info = CorsairGetDeviceInfo(index);
	leds = CorsairGetLedPositionsByDeviceIndex(index);
}

bool CorsairDevice::IsValid()
{
	return info != NULL and leds != NULL;
}

const char* CorsairDevice::GetModel()
{
	return info->model;
}

const char* CorsairDevice::GetID()
{
	return info->deviceId;
}

unsigned char CorsairDevice::GetIndex()
{
	return index;
}

bool CorsairDevice::HasCapability(CorsairDeviceCaps cap)
{
	return info->capsMask & cap;
}

int CorsairDevice::GetCapabilities()
{
	return info->capsMask;
}

int CorsairDevice::GetAllLEDsCount()
{
	return leds->numberOfLed;
}

int CorsairDevice::GetLEDsCount()
{
	return info->ledsCount;
}

CorsairLogicalLayout CorsairDevice::GetLogicalLayout()
{
	return info->logicalLayout;
}

CorsairPhysicalLayout CorsairDevice::GetPhysicalLayout()
{
	return info->physicalLayout;
}

CorsairDeviceType CorsairDevice::GetType()
{
	return info->type;
}

bool CorsairDevice::IsTypeOf(CorsairDeviceType type)
{
	return info->type == type;
}

int CorsairDevice::GetIntProperty(CorsairDevicePropertyId p)
{
	int result;
	CorsairGetInt32PropertyValue(index, p, &result);
	return result;
}

bool CorsairDevice::GetBoolProperty(CorsairDevicePropertyId p)
{
	bool result;
	CorsairGetBoolPropertyValue(index, p, &result);
	return result;
}

CorsairLedPosition* CorsairDevice::GetLEDsPos()
{
	return leds->pLedPosition;
}

bool CorsairDevice::SetLEDsColors(int size, CorsairLedColor* arr)
{
	return CorsairSetLedsColorsBufferByDeviceIndex(index, size, arr);
}

bool CorsairDevice::SetFlushLEDsColors(int size, CorsairLedColor* arr)
{
	return CorsairSetLedsColorsBufferByDeviceIndex(index, size, arr) and CorsairSetLedsColorsFlushBuffer();
}

bool CorsairDevice::FlushLEDs()
{
	return CorsairSetLedsColorsFlushBuffer();
}

CorsairLedColor CorsairDevice::GetLEDColor(CorsairLedId id)
{
	CorsairLedColor c[1] = { CorsairLedColor() };
	c[0].ledId = id;
	CorsairGetLedsColorsByDeviceIndex(index, 1, c);

	return c[0];
}

#define GetCorsairDevice CorsairDevice* device = (CorsairDevice *)luaL_checkudata(L, 1, METATABLE_NAME)
#define CheckNULL(obj) if (obj == NULL) { luaL_error(L, "CorsairDevice[%d] is NULL", device->GetIndex()+1); return 0; }
#define IsDeviceValid if (!device->IsValid()) { luaL_error(L, "CorsairDevice[%d] is NULL", device->GetIndex()+1); return 0; }

#include <map>
#include <vector>
std::vector<CorsairDevice*> Devices;
std::map<int,int> IDToRef;

function device_New(Lua) {
	int device = luaL_checkinteger(L, 1);

	if (device == 0 or device > CorsairGetDeviceCount()) {
		luaL_argerror(L, 1, "number is out of range");
		return 0;
	}

	lua_pushvalue(L, lua_upvalueindex(1));

	if (IDToRef[device]) {
		lua_rawgeti(L, -1, IDToRef[device]);

		auto d = (CorsairDevice*)lua_touserdata(L, -1);
		if (!d->IsValid()) d->Reinitialize();
		
		return 1;
	}

	auto ud = (CorsairDevice*)lua_newuserdata(L, sizeof(CorsairDevice));
	new(ud) CorsairDevice(device-1);
	Devices.push_back(ud);

	luaL_setmetatable(L, METATABLE_NAME);

	lua_pushvalue(L, -1);
	IDToRef[device] = luaL_ref(L, -3);

	return 1;
}

CorsairDevice* FindByDeviceID(const char* id) {
	for (auto Device = Devices.begin(); Device != Devices.end(); Device++) {
		if ((*Device)->IsValid() and std::strcmp((*Device)->GetID(), id) == 0) {
			return *Device;
			break;
		}
	}
	return NULL;
}

function deviceFindByDeviceID(Lua) {
	const char* id = luaL_checkstring(L, 1);

	CorsairDevice* d = FindByDeviceID(id);
	if (d == NULL) { lua_pushnil(L); return 1; }

	if (IDToRef[d->GetIndex() + 1]) {
		lua_pushvalue(L, lua_upvalueindex(1));
		lua_rawgeti(L, -1, IDToRef[d->GetIndex() + 1]);
		return 1;
	}

	lua_pushnil(L);
	return 1;
}

function device__tostring(Lua) {
	GetCorsairDevice;

	lua_pushfstring(L, "CorsairDevice[%d] [%s]", device->GetIndex()+1, device->IsValid() ? device->GetModel() : "NULL");

	return 1;
}

function device__gc(Lua) {
	GetCorsairDevice;

	delete device;

	return 0;
}

function deviceGetModel(Lua) {
	GetCorsairDevice;

	IsDeviceValid

	lua_pushstring(L, device->GetModel());

	return 1;
}

function deviceIsValid(Lua) {
	GetCorsairDevice;

	lua_pushboolean(L, device->IsValid());

	return 1;
}

function deviceGetID(Lua) {
	GetCorsairDevice;

	IsDeviceValid

	lua_pushstring(L, device->GetID());

	return 1;
}

function deviceHasCapability(Lua) {
	GetCorsairDevice;

	int cap = luaL_checkinteger(L, 2);

	IsDeviceValid

	lua_pushboolean(L, device->HasCapability((CorsairDeviceCaps)cap));

	return 1;
}

function deviceGetCapabilities(Lua) {
	GetCorsairDevice;

	IsDeviceValid

	lua_pushinteger(L, device->GetCapabilities());

	return 1;
}

function deviceGetLEDsCount(Lua) {
	GetCorsairDevice;

	IsDeviceValid

	lua_pushinteger(L, device->GetLEDsCount());

	return 1;
}

function deviceGetAllLEDsCount(Lua) {
	GetCorsairDevice;

	IsDeviceValid

	lua_pushinteger(L, device->GetAllLEDsCount());

	return 1;
}

function deviceGetLogicalLayout(Lua) {
	GetCorsairDevice;

	IsDeviceValid

	lua_pushinteger(L, device->GetLogicalLayout());

	return 1;
}

function deviceGetPhysicalLayout(Lua) {
	GetCorsairDevice;

	IsDeviceValid
	
	lua_pushinteger(L, device->GetPhysicalLayout());

	return 1;
}

function deviceGetType(Lua) {
	GetCorsairDevice;

	IsDeviceValid

	lua_pushinteger(L, device->GetType());

	return 1;
}

function deviceIsTypeOf(Lua) {
	GetCorsairDevice;

	int type = luaL_checkinteger(L, 2);

	IsDeviceValid

	lua_pushboolean(L, device->IsTypeOf((CorsairDeviceType)type));

	return 1;
}

function deviceGetProperty(Lua) {
	GetCorsairDevice;

	CorsairDevicePropertyId id = (CorsairDevicePropertyId)luaL_checkinteger(L, 2);

	IsDeviceValid

	if (!device->HasCapability(CDC_PropertyLookup)) {
		luaL_error(L, "CorsairDevice[%d] doesn't support CDC_PropertyLookup capability", device->GetIndex() + 1);
	}

	bool isbool = false;

	switch (id) {
		case CDPI_Headset_MicEnabled:
		case CDPI_Headset_SurroundSoundEnabled:
		case CDPI_Headset_SidetoneEnabled: {
			isbool = true;
			break;
		}
		case CDPI_Headset_EqualizerPreset: {
			isbool = false;
			break;
		}
		default: {
			luaL_argerror(L, 2, "CDPI_ enum expected");
			break;
		}
	}

	bool status = false;

	if (isbool) {
		lua_pushboolean(L, device->GetBoolProperty(id));
	}
	else {
		lua_pushinteger(L, device->GetIntProperty(id));
	}

	if (not status and CorsairGetLastError() == CE_InvalidArguments) luaL_error(L, "%d is not supported by CorsairDevice[%d]", id, device->GetIndex() + 1);

	return 1;
}

#include <vector>
function deviceMapLEDs(Lua) {
	GetCorsairDevice;

	luaL_checktype(L, 2, LUA_TFUNCTION);
	IsDeviceValid

	std::vector<CorsairLedColor> leds;

	const auto ledspos = device->GetLEDsPos();

	for (int i = 0; i < device->GetAllLEDsCount(); i++) {
		auto led = CorsairLedColor();

		led.ledId = ledspos[i].ledId;

		lua_pushvalue(L, 2);

		lua_pushinteger(L, ledspos[i].ledId);
		lua_pushnumber(L, ledspos[i].left);
		lua_pushnumber(L, ledspos[i].top);
		lua_pushnumber(L, ledspos[i].width);
		lua_pushnumber(L, ledspos[i].height);
		lua_call(L, 5, 3);
		
		led.r = luaL_optinteger(L, -3, 0);
		led.g = luaL_optinteger(L, -2, 0);
		led.b = luaL_optinteger(L, -1, 0);
		lua_pop(L, 3);

		leds.push_back(led);
	}

	device->SetFlushLEDsColors(device->GetAllLEDsCount(), leds.data());

	return 0;
}

function deviceSetLEDColor(Lua) {
	GetCorsairDevice;

	int id = luaL_checkinteger(L, 2);
	int r = luaL_optinteger(L, 3, 0);
	int g = luaL_optinteger(L, 4, 0);
	int b = luaL_optinteger(L, 5, 0);
	IsDeviceValid

	CorsairLedColor led[1] = { CorsairLedColor() };
	led[0].ledId = (CorsairLedId)id;
	led[0].r = r;
	led[0].g = g;
	led[0].b = b;
	device->SetLEDsColors(1, led);

	return 0;
}

function deviceSetFlushLEDColor(Lua) {
	GetCorsairDevice;

	int id = luaL_checkinteger(L, 2);
	int r = luaL_optinteger(L, 3, 0);
	int g = luaL_optinteger(L, 4, 0);
	int b = luaL_optinteger(L, 5, 0);
	IsDeviceValid

	CorsairLedColor led[1] = { CorsairLedColor() };
	led[0].ledId = (CorsairLedId)id;
	led[0].r = r;
	led[0].g = g;
	led[0].b = b;
	device->SetFlushLEDsColors(1, led);

	return 0;
}

function deviceFlushLEDs(Lua) {
	GetCorsairDevice;

	IsDeviceValid

	device->FlushLEDs();

	return 0;
}

function deviceGetLEDColor(Lua) {
	GetCorsairDevice;

	int id = luaL_checkinteger(L, 2);
	IsDeviceValid

	CorsairLedColor c = device->GetLEDColor((CorsairLedId)id);
	lua_pushinteger(L, c.r);
	lua_pushinteger(L, c.g);
	lua_pushinteger(L, c.b);

	return 3;
}

function deviceGetLEDs(Lua) {
	GetCorsairDevice;

	IsDeviceValid

	const auto ledspos = device->GetLEDsPos();
	lua_createtable(L, device->GetAllLEDsCount(), 0);

	for (int i = 0; i < device->GetAllLEDsCount(); i++) {
		lua_createtable(L, 0, 4);
		lua_pushnumber(L, ledspos[i].ledId);
		lua_setfield(L, -2, "id");
		lua_pushnumber(L, ledspos[i].left);
		lua_setfield(L, -2, "x");
		lua_pushnumber(L, ledspos[i].top);
		lua_setfield(L, -2, "y");
		lua_pushnumber(L, ledspos[i].width);
		lua_setfield(L, -2, "w");
		lua_pushnumber(L, ledspos[i].height);
		lua_setfield(L, -2, "h");
		lua_rawseti(L, -2, ledspos[i].ledId);
	}

	return 1;
}

static const struct luaL_Reg CorsairDeviceMethods[] = {
	//{"__index", device__index},
	//{"__newindex", device__newindex},
	{"__tostring", device__tostring},
	{"GetModel", deviceGetModel},
	{"IsValid", deviceIsValid},
	{"GetID", deviceGetID},
	{"HasCapability", deviceHasCapability},
	{"GetCapabilities", deviceGetCapabilities},
	{"GetLEDsCount", deviceGetLEDsCount},
	{"GetAllLEDsCount", deviceGetAllLEDsCount},
	{"GetLogicalLayout", deviceGetLogicalLayout},
	{"GetPhysicalLayout", deviceGetPhysicalLayout},
	{"GetType", deviceGetType},
	{"IsTypeOf", deviceIsTypeOf},
	{"GetProperty", deviceGetProperty},
	{"MapLEDs", deviceMapLEDs},
	{"SetLEDColor", deviceSetLEDColor},
	{"SetFlushLEDColor", deviceSetFlushLEDColor},
	{"FlushLEDs", deviceFlushLEDs},
	{"GetLEDColor", deviceGetLEDColor},
	{"GetLEDs", deviceGetLEDs},
	{NULL, NULL}
};

void cue_importdevice(Lua) {
	luaL_newmetatable(L, METATABLE_NAME);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, CorsairDeviceMethods, 0);
	lua_pop(L, 1);

	lua_createtable(L, 0, 1);
	lua_pushvalue(L, -1);
	lua_pushcclosure(L, device_New, 1);
	lua_setglobal(L, METATABLE_NAME);

	lua_getglobal(L, "cue");
	lua_pushvalue(L, -2);
	lua_pushcclosure(L, deviceFindByDeviceID, 1);
	lua_setfield(L, -2, "FindByDeviceID");
	lua_pop(L, 2);
}