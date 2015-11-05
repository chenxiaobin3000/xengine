function GameLayer_Init(args)
	local win = XEGUI.Lua:LoadUI('GameLayer.xml')
	if nil == win then
		return
	end

	local btn = win:GetWindow('GameLayer/Back')
	local label = win:GetWindow('GameLayer/Back/Txt')

	init_language_text_with_win(label)

	btn:SubscribeEvent('Clicked', 'GameLayer_OnBackClicked')

	win:SetVisible(false)
end

function GameLayer_Show(args)
	local win = XEGUI.Lua:GetWindow('GameLayer')
	win:SetVisible(true)
end

function GameLayer_Hide(args)
	local win = XEGUI.Lua:GetWindow('GameLayer')
	win:SetVisible(false)
end

function GameLayer_OnBackClicked(args)
	CLua:BackMainLayer()
end
