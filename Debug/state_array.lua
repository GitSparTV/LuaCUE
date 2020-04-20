if cue.GetDeviceCount() == 0 then return end
local D = CorsairDevice(1)
local x, y = 1, 1
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

local ENTERx, ENTERy = 0, 0

for k, v in pairs(leds) do
	local y = math.Round10(v.y)
	m[y] = m[y] or {}
	m[y][#m[y] + 1] = v
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
	MAX = math.max(MAX, #m[v])
end

m = nil

do
	local k = 1

	while true do
		::again::
		local v = M[k]
		if not v then break end

		if #v < 2 and k > 1 then
			for _, V in ipairs(v) do
				M[k - 1][#M[k - 1] + 1] = V
			end

			table.remove(M, k)
			goto again
		end

		k = k + 1
	end
end

for k, v in ipairs(M) do
	for K, V in ipairs(v) do
		if V.id == CLK_Enter then
			x, y = K, k
		end
	end
end

local Clamp = math.Clamp

local function AddPos(_x, _y)
	y = Clamp(y + _y, 1, #M)
	x = Clamp(x + _x, 1, MAX)
end

function Update()
	local s = math.abs(math.sin(CPUClock() * 5)) * 255
	D:SetFlushLEDColor(M[y][Clamp(x, 1, #M[y])].id, s, s, s)
end

local arr = {}

function KeyboardInput(key, pressed)
	if not pressed then return end

	if key == VK_RETURN then
		arr[M[y][Clamp(x, 1, #M[y])].id] = not arr[M[y][Clamp(x, 1, #M[y])].id]
	end

	if key ~= VK_LEFT and key ~= VK_RIGHT and key ~= VK_UP and key ~= VK_DOWN then return end
	D:SetLEDColor(M[y][Clamp(x, 1, #M[y])].id, 0, 0, 0)
	AddPos(key == VK_LEFT and -1 or (key == VK_RIGHT and 1 or 0), key == VK_UP and -1 or (key == VK_DOWN and 1 or 0))

	for k, v in pairs(arr) do
		D:SetLEDColor(k, v and 255 or 0, v and 255 or 0, v and 255 or 0)
	end

	D:SetFlushLEDColor(M[y][Clamp(x, 1, #M[y])].id, 255, 255, 255)
end