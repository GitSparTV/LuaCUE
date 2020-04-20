function printt(t, indent, antiloop)
	indent = indent or 0

	antiloop = antiloop or {
		[t] = true
	}

	for k, v in pairs(t) do
		io.write(string.rep("\t", indent))
		io.write(k)
		io.write("\t=\t")

		if type(v) == "table" and not antiloop[v] then
			io.write("\n")
			antiloop[v] = true
			printt(v, indent + 1, antiloop)
		else
			io.write(tostring(v))
			io.write("\n")
		end
	end
end

function math.Clamp(v,m,x)
	return math.min(math.max(v,m),x)
end

VK_RETURN = 0x0D
VK_LEFT = 0x25
VK_UP = 0x26
VK_RIGHT = 0x27
VK_DOWN = 0x28

function Update() end
function KeyboardInput(key, pressed) end
function DeviceStatusChanged(deviceID,connected) end
function CorsairKeysInput(deviceID, pressed, keyID) end

-- require("acceletation_runner")
require("state_array")