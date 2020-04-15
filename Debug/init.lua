local DEVICES = GetDeviceCount()

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
			printt(v, indent + 1, antiloop)
		else
			io.write(v)
			io.write("\n")
		end
	end
end

printt(GetDeviceInfo(1))

function update()
	error("test")
end