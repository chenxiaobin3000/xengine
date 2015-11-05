function LoginUI_Init(args)
	local win = XEGUI.Lua:LoadUI('LoginUI.xml')
	if nil == win then
		return
	end

	local label_account = XEGUI.Lua:GetWindow('LoginWnd/Account')
	local label_pwd     = XEGUI.Lua:GetWindow('LoginWnd/Password')
	local btn_lg        = XEGUI.Lua:GetWindow('LoginWnd/LoginBtn')
	local label_lg      = XEGUI.Lua:GetWindow('LoginWnd/LoginBtn/Txt')
	local btn_reg       = XEGUI.Lua:GetWindow('LoginWnd/RegisterBtn')
	local label_reg     = XEGUI.Lua:GetWindow('LoginWnd/RegisterBtn/Txt')

	init_language_text_with_win(label_account)
	init_language_text_with_win(label_pwd)
	init_language_text_with_win(label_lg)
	init_language_text_with_win(label_reg)

	btn_lg:SubscribeEvent('Clicked', 'LoginUI_Login')
	btn_reg:SubscribeEvent('Clicked', 'LoginUI_Register')

	win:SetVisible(false)
end

function LoginUI_Show(args)
	local win = XEGUI.Lua:GetWindow('LoginWnd')
	win:SetVisible(true)
end

function LoginUI_Hide(args)
	local win = XEGUI.Lua:GetWindow('LoginWnd')
	win:SetVisible(false)
end

function LoginUI_SetAccountText(args)
	local win_account = XEGUI.Lua:GetWindow('LoginWnd/AccountEditor')
	win_account:SetText(args)
end

function LoginUI_SetPasswordText(args)
	local win_pwd = XEGUI.Lua:GetWindow('LoginWnd/PwdEditor')
	win_pwd:SetText(args)
end

function LoginUI_Login(args)
	local win_account = XEGUI.Lua:GetWindow('LoginWnd/AccountEditor')
	local win_pwd     = XEGUI.Lua:GetWindow('LoginWnd/PwdEditor')
	local account     = win_account:GetText()
	local pwd         = win_pwd:GetText()
	CLua:Login(account, pwd)
end

function LoginUI_Register(args)
	CLua:ShowRegisterUI()
end

LoginUI_Init()
