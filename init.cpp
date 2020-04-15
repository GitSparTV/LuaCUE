#define CORSAIR_LIGHTING_SDK_DISABLE_DEPRECATION_WARNINGS

#ifdef __APPLE__
#include <CUESDK/CUESDK.h>
#else
#include <CUESDK.h>
#endif

#include <iostream>
#include <thread>
#include <cstdlib>
#include <windows.h>
#include "lua.hpp"
#include "lcuelib.h"
#include "luahelpers.h"

HANDLE hConsole;
lua_State* L;

static void PrintStack(Lua, int blist = 0)
{
	int top = lua_gettop(L);
	SetConsoleTextAttribute(hConsole, 14);
	print("Stack:");
	SetConsoleTextAttribute(hConsole, 10);
	for (int i = 1; i <= top; i++) {
		if (i == blist) { continue; }
		lua_getglobal(L, "tostring");
		lua_pushvalue(L, i);
		lua_call(L, 1, 1);
		printf("\t%d\t=\t%s \t(%s)\n", i, lua_tostring(L, -1), lua_typename(L, i));
		lua_pop(L, 3);
	}
	printf("\n");
	SetConsoleTextAttribute(hConsole, 15);
	return;
}

static int cue_error(Lua) {
	MessageBoxA(NULL, lua_tostring(L, -1), "Lua Error", MB_OK | MB_ICONWARNING);
	return 0;
}

void atexit() {
	lua_close(L);
}

//double getKeyboardWidth(CorsairLedPositions* ledPositions)
//{
//	const auto minmaxLeds = std::minmax_element(ledPositions->pLedPosition, ledPositions->pLedPosition + ledPositions->numberOfLed,
//		[](const CorsairLedPosition& clp1, const CorsairLedPosition& clp2) {
//			return clp1.left < clp2.left;
//		});
//	return minmaxLeds.second->left + minmaxLeds.second->width - minmaxLeds.first->left;
//}

void EventCallback(void* _, const CorsairEvent* event) {
	switch (event->id) {
	case CEI_DeviceConnectionStatusChangedEvent: {
		print("CEI_DeviceConnectionStatusChangedEvent");
		print(event->deviceConnectionStatusChangedEvent->deviceId);
		printf("IsConnected: %d\n", event->deviceConnectionStatusChangedEvent->isConnected);
		break;
	}
	case CEI_KeyEvent: {
		print("CEI_KeyEvent");
		print(event->keyEvent->deviceId);
		printf("Pressed: %d\n", event->keyEvent->isPressed);
		printf("KeyId: %d\n", event->keyEvent->keyId);
		break;
	}
	case CEI_Invalid: {
		print("CEI_Invalid");
		break;
	}
	default:
		break;
	}
}

//int WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR    lpCmdLine,
//	int       nCmdShow)
//{
int main() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::atexit(atexit);
	const auto ProtDetails = CorsairPerformProtocolHandshake();

	if (const auto error = CorsairGetLastError()) {
		std::cout << "Handshake failed: " << ErrorToString(error) << "\nPress any key to quit." << std::endl;
		getchar();
		return -1;
	}

	L = luaL_newstate();
	//lua_atpanic(L, cue_error);
	luaL_openlibs(L);
	luaopen_cue(L);
	cue_PushProtocolDetails(L, ProtDetails);
	PrintStack(L);

	CorsairSubscribeForEvents(EventCallback, NULL);

	auto status = luaL_loadfile(L, "init.lua");
	lua_call(L, 0, 0);

	while (true) {
		lua_getglobal(L, "update");
		lua_call(L, 0, 0);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	lua_close(L);

	return 0;
}