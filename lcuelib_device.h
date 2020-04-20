#pragma once
#ifdef __APPLE__
#include <CUESDK/CUESDK.h>
#else
#include <CUESDK.h>
#endif
#include "lua.hpp"
#include "luahelpers.h"

class CorsairDevice
{
public:
	CorsairDevice(int index);
	~CorsairDevice();
	bool IsValid();
	const char* GetModel();
	const char* GetID();
	unsigned char GetIndex();
	bool HasCapability(CorsairDeviceCaps cap);
	int GetCapabilities();
	int GetAllLEDsCount();
	int GetLEDsCount();
	CorsairLedPosition* GetLEDsPos();
	CorsairLogicalLayout GetLogicalLayout();
	CorsairPhysicalLayout GetPhysicalLayout();
	CorsairDeviceType GetType();
	bool IsTypeOf(CorsairDeviceType type);
	int GetIntProperty(CorsairDevicePropertyId p);
	bool GetBoolProperty(CorsairDevicePropertyId p);
	bool SetLEDsColors(int size, CorsairLedColor* arr);
	bool SetFlushLEDsColors(int size, CorsairLedColor* arr);
	bool FlushLEDs();
	CorsairLedColor GetLEDColor(CorsairLedId id);
	void Clear();
	void Reinitialize();

private:
	int index;
	CorsairDeviceInfo* info;
	CorsairLedPositions* leds;
};

void cue_importdevice(Lua);
CorsairDevice* FindByDeviceID(const char* id);