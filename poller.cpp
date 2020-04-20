#include "poller.h"

Event::Event(EventType et, int v1, bool v2) : evtype(et), type1(LUA_TNUMBER), type2(LUA_TBOOLEAN)
{
	value1.i = v1;
	value2.b = v2;
}

Event::Event(EventType et, CorsairEventId v1, const CorsairDeviceId v2, const bool v3) : evtype(et), type1(LUA_TNUMBER), type2(LUA_TSTRING), type3(LUA_TBOOLEAN)
{
	value1.i = v1;
	strcpy_s(value2.s, v2);
	value3.b = v3;
}

Event::Event(EventType et, CorsairEventId v1, const CorsairDeviceId v2, const bool v3, const CorsairKeyId v4) : evtype(et), type1(LUA_TNUMBER), type2(LUA_TSTRING), type3(LUA_TBOOLEAN), type4(LUA_TNUMBER)
{
	value1.i = v1;
	strcpy_s(value2.s, v2);
	value3.b = v3;
	value4.i = v4;
}

Event::~Event()
{
}

void Event::ToLua(Lua)
{
	switch (evtype) {
		case EVENT_KEY: {
			lua_getglobal(L, "KeyboardInput");
			lua_pushinteger(L,value1.i);
			lua_pushboolean(L, value2.b);
			if (lua_pcall(L, 2, 0, 1) != LUA_OK) lua_remove(L,-1);
			break;
		}
		case EVENT_CORSAIR:
			if (value1.i == CEI_DeviceConnectionStatusChangedEvent) {
				lua_getglobal(L, "DeviceStatusChanged");
				lua_pushstring(L, value2.s);
				lua_pushboolean(L, value3.b);
				if (lua_pcall(L, 2, 0, 1) != LUA_OK) lua_remove(L, -1);
			}
			else {
				lua_getglobal(L, "CorsairKeysInput");
				lua_pushstring(L, value2.s);
				lua_pushboolean(L, value3.b);
				lua_pushinteger(L, value4.i);
				if (lua_pcall(L, 2, 0, 1) != LUA_OK) lua_remove(L, -1);
			}
			break;
		default:
			break;
	}
}

Poller::Poller() {}
Poller::~Poller() {}

void Poller::Add(Event* ev) {
	std::lock_guard<std::mutex> l(lock);
	q.push(ev);
}

bool Poller::Pop(Event*& e) {
	std::lock_guard<std::mutex> l(lock);
	if (q.empty()) { return false; }
	e = q.front();
	q.pop();
	return true;
}