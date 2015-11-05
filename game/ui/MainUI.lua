function MainUI_Init(args)
	local win = XEGUI.Lua:LoadUI('MainUI.xml')
	if nil == win then
		return
	end

	local btn_menu   = XEGUI.Lua:GetWindow('MainWnd/MenuBtn')
	local label_menu = XEGUI.Lua:GetWindow('MainWnd/MenuBtn/Txt')

	init_language_text_with_win(label_menu)

	btn_menu:SubscribeEvent('Clicked', 'MainUI_Menu')

	win:SetVisible(false)
end

function MainUI_Show(args)
	local win = XEGUI.Lua:GetWindow('MainWnd')
	win:SetVisible(true)
end

function MainUI_Hide(args)
	local win = XEGUI.Lua:GetWindow('MainWnd')
	win:SetVisible(false)
end

function MainUI_Menu(args)
	CLua:ExitGame()
end

MainUI_Init()
