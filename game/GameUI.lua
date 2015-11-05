------------------------
-- init_language_text_with_win
------------------------
function init_language_text_with_win(args)
	local text = args:GetText()
	local value = XCli.CLanguage:GetContent(text)
	args:SetText(value)
end

------------------------
-- init_load_lua
------------------------
function init_load_lua(args)
	XE.Lua:LoadLuaFile('ui/ControllerUI.lua')
	XE.Lua:LoadLuaFile('ui/LoadingUI.lua')
	XE.Lua:LoadLuaFile('ui/SelectLSUI.lua')
	XE.Lua:LoadLuaFile('ui/MessageBoxUI.lua')
	XE.Lua:LoadLuaFile('ui/MainUI.lua')
	XE.Lua:LoadLuaFile('ui/LoginUI.lua')

	XE.Lua:LoadLuaFile('ui/GameLayer.lua')
	XE.Lua:LoadLuaFile('ui/MainLayer.lua')
end
