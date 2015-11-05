function LoadingUI_Init(args)
	local win = XEGUI.Lua:LoadUI('LoadingUI.xml')
	if nil == win then
		return
	end

	win:SetVisible(false)
end

function LoadingUI_Show(args)
	local win = XEGUI.Lua:GetWindow('LoadingWnd')
	win:SetVisible(true)
end

function LoadingUI_Hide(args)
	local win = XEGUI.Lua:GetWindow('LoadingWnd')
	win:SetVisible(false)
end

LoadingUI_Init()
