function ScriptTest_Start (object)
	print "Start from Lua!"
	comp = GetNativeComponent(object, "NativeTest")
	CallNativeComponent(comp, "Hello")
end
function ScriptTest_Update (object)
end
function ScriptTest_Delete (object)
end

function ScriptTest_Hello (object)
	print "Hello from Lua"
end