#pragma once
#ifdef __APPLE__
#include <CUESDK/CUESDK.h>
#else
#include <CUESDK.h>
#endif
#include "lua.hpp"
#include "luahelpers.h"
#include <queue>
//#include <vector>

#include <mutex>

union Value
{
	int i;
	bool b;
	char s[CORSAIR_DEVICE_ID_MAX];
};

enum EventType
{
	EVENT_CORSAIR,
	EVENT_KEY,
};

class Event
{
public:
	Event(EventType et, int v1, bool v2);
	Event(EventType et, CorsairEventId v1, const CorsairDeviceId v2, const bool v3);
	Event(EventType et, CorsairEventId v1, const CorsairDeviceId v2, const bool v3, const CorsairKeyId v4);
	~Event();
	void ToLua(Lua);

private:
	int type1;
	int type2;
	int type3;
	int type4;
	EventType evtype;
	Value value1;
	Value value2;
	Value value3;
	Value value4;
};

class Poller
{
public:
	Poller();
	~Poller();
	void Add(Event* ev);
	bool Pop(Event*& ev);

private:
	std::queue<Event*> q;
	std::mutex lock;
};