function SelectLSUI_Init(args)
	local win = XEGUI.Lua:LoadUI('SelectLSUI.xml')
	if nil == win then
		return
	end

	local win_list = XEGUI.Lua:GetWindow('SelectLSWnd/List')

	win_list:SubscribeEvent('SelectionChanged', 'SelectLSUI_SelectionChanged')

	win:SetVisible(false)
end

function SelectLSUI_Show(args)
	local win = XEGUI.Lua:GetWindow('SelectLSWnd')
	win:SetVisible(true)
end

function SelectLSUI_Hide(args)
	local win = XEGUI.Lua:GetWindow('SelectLSWnd')
	win:SetVisible(false)
end

function SelectLSUI_SelectionChanged(args)
	local win  = XEGUI.Lua:GetWindow('SelectLSWnd/List')
	local list = XEGUI.Lua:ToList(win)
	local num = list:GetSelected()
	CLua:SelectLS(num)
end

SelectLSUI_Init()
