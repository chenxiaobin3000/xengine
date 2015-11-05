function ControllerUI_Init(args)
	local win = XEGUI.Lua:LoadUI('ControllerUI.xml')
	if nil == win then
		return
	end

	local btn_LeftBtn = win:GetWindow('ControllerWnd/LeftBtn')
	local btn_RightBtn = win:GetWindow('ControllerWnd/RightBtn')
	local btn_A = win:GetWindow('ControllerWnd/A')
	local label_ATxt = win:GetWindow('ControllerWnd/A/Txt')
	local btn_L1 = win:GetWindow('ControllerWnd/L1')
	local label_L1Txt = win:GetWindow('ControllerWnd/L1/Txt')
	local btn_R1 = win:GetWindow('ControllerWnd/R1')
	local label_R1Txt = win:GetWindow('ControllerWnd/R1/Txt')

	init_language_text_with_win(label_ATxt)
	init_language_text_with_win(label_L1Txt)
	init_language_text_with_win(label_R1Txt)

	btn_LeftBtn:SubscribeEvent('Clicked', 'ControllerUI_OnLeftBtnClicked')
	btn_RightBtn:SubscribeEvent('Clicked', 'ControllerUI_OnRightBtnClicked')
	btn_A:SubscribeEvent('Clicked', 'ControllerUI_OnAClicked')
	btn_L1:SubscribeEvent('Clicked', 'ControllerUI_OnL1Clicked')
	btn_R1:SubscribeEvent('Clicked', 'ControllerUI_OnR1Clicked')

	win:SetVisible(false)
end

function ControllerUI_Show(args)
	local win = XEGUI.Lua:GetWindow('ControllerWnd')
	win:SetVisible(true)
end

function ControllerUI_Hide(args)
	local win = XEGUI.Lua:GetWindow('ControllerWnd')
	win:SetVisible(false)
end

function ControllerUI_OnLeftBtnClicked(args)
	XE.Lua:Input(XI.XInputObserver.E_Left)
end

function ControllerUI_OnRightBtnClicked(args)
	XE.Lua:Input(XI.XInputObserver.E_Right)
end

function ControllerUI_OnAClicked(args)
	XE.Lua:Input(XI.XInputObserver.E_A)
end

function ControllerUI_OnL1Clicked(args)
	XE.Lua:Input(XI.XInputObserver.E_L1)
end

function ControllerUI_OnR1Clicked(args)
	XE.Lua:Input(XI.XInputObserver.E_R1)
end

ControllerUI_Init()
