# LuaCUE
Corsair Utility Engine bindings for Lua. Standalone app and library.

This projects binds CUE SDK and wraps in Lua environment.

Built with LuaJIT 2.1.0-beta3 x32.

Consult with this [page](https://corsairofficial.github.io/cue-sdk/) about enums and internal functions.

Unimplemented: DYI device channels.

# API


## Globals

### ProtocolDetails

- breakingChanges
- sdkProtocolVersion
- sdkVersion
- serverProtocolVersion
- serverVersion

### CPUClock

Uses Windows [CPU clock functions](https://docs.microsoft.com/ru-ru/windows/win32/sysinfo/acquiring-high-resolution-time-stamps).

### IsKeyDown

Uses Windows function [GetKeyState](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate).

### printt

Prints table recursively with anti-loop protection.

### LEDID

Converts A-Z to CorsairLedId. Yeah, only them.

### CorsairDevice(number)

Returns `CorsairDevice` object. Indexes start from 1.

### function Update()

General function for continuous actions.

### function KeyboardInput(key, pressed)

Keyboard callback. Uses Windows hooks.

### function DeviceStatusChanged(deviceID,connected)

Called when device changes state. (Connected / Disconnected)

### function CorsairKeysInput(deviceID, pressed, keyID)

Corsair M and G buttons callback.


## cue

### CorsairDevice FindByDeviceID(deviceID)

### string GetLastErrorString()

### number GetDeviceCount()

### boolean ReleaseControl()

### boolean RequestControl()

### number GetLastError()

CorsairError (CE_) enum.

### SetPriority(number)


## math

### number math.Clamp(number, number, number)


## CorsairDevice methods

### __tostring

Prints `CorsairDevice[index] [model]`.

### string GetModel()

### boolean IsValid()

Checks if internal pointers are valid. SDK didn't provide any solution to check, so it listens for `DeviceStatusChanged` callback.

### string GetID()

### HasCapability(number)

CorsairDeviceCaps (CDC_) enum.

### number GetCapabilities()

CorsairDeviceCaps mask

### number GetLEDsCount()

Number of controllable LEDs.

### number GetAllLEDsCount()

The size of LED array.

### number GetLogicalLayout()

CorsairLogicalLayout (CLL_) enum.

### number GetPhysicalLayout()

CorsairPhysicalLayout (CPL_) enum.

### number GetType()

CorsairDeviceType (CDT_) enum.

### boolean IsTypeOf(number)

### GetProperty(number)

CorsairDevicePropertyId (CDPI_) enum.

### MapLEDs(function(ledID, x, y, w, h) return r, g, b end)

Function to set all LEDs.

### SetLEDColor(ledID, r, g, b)

### SetFlushLEDColor(ledID, r, g, b)

### FlushLEDs()

### number, number, number GetLEDColor(ledID)

Returns r, g, b.

### table GetLEDs()

Returns all LEDs and their colors.

- id
- x
- y
- w
- h