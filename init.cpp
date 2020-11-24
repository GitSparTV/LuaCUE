#define CORSAIR_LIGHTING_SDK_DISABLE_DEPRECATION_WARNINGS

#include <CUESDK.h>

#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <windows.h>
#include <signal.h>
#include "lua.hpp"
#include "lcuelib.h"
#include "luahelpers.h"

lua_State* L;

static int cue_error(Lua) {
	MessageBoxA(NULL, lua_tostring(L, -1), "Lua Error", MB_OK | MB_ICONWARNING);
	return 0;
}

//double getKeyboardWidth(CorsairLedPositions* ledPositions)
//{
//	const auto minmaxLeds = std::minmax_element(ledPositions->pLedPosition, ledPositions->pLedPosition + ledPositions->numberOfLed,
//		[](const CorsairLedPosition& clp1, const CorsairLedPosition& clp2) {
//			return clp1.left < clp2.left;
//		});
//	return minmaxLeds.second->left + minmaxLeds.second->width - minmaxLeds.first->left;
//}
#include "poller.h"
Poller p;

void CorsairEventCallback(void* _, const CorsairEvent* event) {
	CorsairDevice* d;
	switch (event->id) {
		case CEI_Invalid:
			break;
		case CEI_DeviceConnectionStatusChangedEvent:
			if (!event->deviceConnectionStatusChangedEvent->isConnected) {
				d = FindByDeviceID(event->deviceConnectionStatusChangedEvent->deviceId);
				if (d) {
					d->Clear();
				}
			}

			p.Add(new Event(EVENT_CORSAIR, CEI_DeviceConnectionStatusChangedEvent, event->deviceConnectionStatusChangedEvent->deviceId, event->deviceConnectionStatusChangedEvent->isConnected));
			break;

		case CEI_KeyEvent:
			p.Add(new Event(EVENT_CORSAIR, CEI_KeyEvent, event->keyEvent->deviceId, event->keyEvent->isPressed, event->keyEvent->keyId));
			break;

		default:
			break;
	}
}

static void OnSignalInterrupt(int id) {
	print("Signal");
	signal(id, SIG_DFL);
}


#include <array>
HHOOK _hook;

std::array<bool, 0xFF> KeysState;
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) return CallNextHookEx(_hook, nCode, wParam, lParam);

	KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
	unsigned char key = (unsigned char)kbdStruct.vkCode;
	
	switch (wParam) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN: {
			if (KeysState[key]) break;
			KeysState[key] = true;
			p.Add(new Event(EVENT_KEY, key, true));
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP: {
			KeysState[key] = false;
			p.Add(new Event(EVENT_KEY, key, false));
			break;
		}
	}

	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

//int WinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR    lpCmdLine,
//	int       nCmdShow)
//{
int LUA_ERRORINDEX;

int main() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	signal(SIGBREAK, OnSignalInterrupt);
	signal(SIGINT, OnSignalInterrupt);
	const auto ProtDetails = CorsairPerformProtocolHandshake();

	if (const auto error = CorsairGetLastError()) {
		std::cout << "Handshake failed: " << ErrorToString(error) << "\nPress any key to quit." << std::endl;
		getchar();
		return -1;
	}

	L = luaL_newstate();
	lua_pushcfunction(L, ErrorHandler);
	LUA_ERRORINDEX = luaL_ref(L, LUA_REGISTRYINDEX);
	lua_atpanic(L, cue_error);

	luaL_openlibs(L);
	
	luaopen_cue(L);
	cue_PushProtocolDetails(L, ProtDetails);
	
	CorsairSubscribeForEvents(CorsairEventCallback, NULL);

	lua_errhandler;
	auto status = luaL_loadfile(L, "init.lua");
	xpcall(0, 0);

	std::thread KeyPress([] {
		_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	});

	while (true) {
		Event* e = nullptr;
		while (p.Pop(e)) {
			e->ToLua(L);
			delete e;
		}
		lua_getglobal(L, "Update");
		lua_pcall(L, 0, 0, 1);

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	KeyPress.join();
	//CorsairReleaseControl(CAM_ExclusiveLightingControl);
	return 0;
}
