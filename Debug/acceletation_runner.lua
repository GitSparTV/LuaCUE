local DEVICES = cue.GetDeviceCount()

local D = CorsairDevice(1)
-- print(D)
-- print("GetModel:", D:GetModel())
-- print("GetID:", D:GetID())
-- print("HasCapability CDC_PropertyLookup:", D:HasCapability(CDC_PropertyLookup))
-- print("GetCapabilities:", D:GetCapabilities())
-- print("GetLEDsCount:", D:GetLEDsCount())
-- print("GetLogicalLayout:", D:GetLogicalLayout())
-- print("GetPhysicalLayout:", D:GetPhysicalLayout())
-- print("GetType:", D:GetType())
-- print("IsTypeOf CDT_Keyboard:", D:IsTypeOf(CDT_Keyboard))

local leds = D:GetLEDs()
local m = {}

local floor = math.floor

function math.Round10(num)
	local mod = num % 10
	if num % 10 < 5 then
		return num - mod
	else
		return num + (10 - mod)
	end
end

for k, v in pairs(leds) do
	local y = math.Round10(v.y)
	if not m[y] then
		m[y] = {}
	end

	local line = m[y]
	line[#line + 1] = v
end

local function sorter(a, b)
	return a.x < b.x
end

local keys = {}
for k, v in pairs(m) do
	keys[#keys + 1] = k
	table.sort(v, sorter)
end

table.sort(keys)

local M = {}

local MAX = 0
for k, v in ipairs(keys) do
	M[k] = m[v]
	MAX = math.max(MAX,#m[v])
end

m = nil
local k = 1

while true do
	::again::
	local v = M[k]
	if not v then break end

	if #v < 2 and k > 1 then
		for _, v in ipairs(v) do
			M[k - 1][#M[k - 1] + 1] = v
		end
		table.remove(M,k)
		goto again
	end

	k = k + 1
end

local x,y = 1,#M-1
local vx,vy = 0,0
local ceil = math.ceil
local function SetPos(_x,_y)
	y = math.Clamp(_y > 0 and floor(_y) or ceil(_y),1,#M - 1)
	x = math.Clamp(_x > 0 and floor(_x) or ceil(_x),1,MAX)
end

local function AddVel(_x,_y)
	vx = math.Clamp(vx + _x,-5,5)
	vy = math.Clamp(vy + _y,-5,5)
end

local Hold = {}
function Update()
	D:SetLEDColor(M[y][math.Clamp(x,1,#M[y])].id, 0, 0, 0)
	if Hold[VK_LEFT] then
		AddVel(-1,0)
	elseif Hold[VK_RIGHT] then
		AddVel(1,0)
	elseif Hold[VK_UP] then
		AddVel(0,-1)
	elseif Hold[VK_DOWN] then
		AddVel(0,1)
	end
	AddVel(vx > 0 and -0.5 or (vx == 0 and 0 or 0.5),vy > 0 and -0.5 or (vy == 0 and 0 or 0.5))
	SetPos(x + vx,y + vy)
	D:SetFlushLEDColor(M[y][math.Clamp(x,1,#M[y])].id, 255, 0, 0)
end

function KeyboardInput(key, pressed)
	if key == VK_RETURN then print(x,y) printt(M[x][math.Clamp(x,1,#M[y])]) return end
	if key ~= VK_UP and key ~= VK_LEFT and key ~= VK_RIGHT and key ~= VK_DOWN then return end
	if not pressed then Hold[key] = false return end
	if key == VK_DOWN then AddVel(0,1) end
	Hold[key] = true
	Update()
end

print(D)
function DeviceStatusChanged(deviceID,connected)
	print(deviceID,connected)
	D = CorsairDevice(1)
	-- print(cue.FindByDeviceID(deviceID))
end