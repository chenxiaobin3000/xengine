function MessageBox_Init(args)
	local win = XEGUI.Lua:LoadUI('MessageBoxUI.xml')
	if nil == win then
		return
	end

	-- ok/cancel
	local btn_ok        = XEGUI.Lua:GetWindow('MessageBox/Ok')
	local label_ok      = XEGUI.Lua:GetWindow('MessageBox/Ok/Txt')
	local btn_cancel    = XEGUI.Lua:GetWindow('MessageBox/Cancel')
	local label_cancel  = XEGUI.Lua:GetWindow('MessageBox/Cancel/Txt')

	init_language_text_with_win(label_ok)
	init_language_text_with_win(label_cancel)

	btn_ok:SubscribeEvent('Clicked', 'MessageBox_Ok')
	btn_cancel:SubscribeEvent('Clicked', 'MessageBox_Cancel')

	win:SetVisible(false)
end

function MessageBox(args_t, args_c)
	local win = XEGUI.Lua:GetWindow('MessageBox')
	if nil == win then
		return
	end
	win:SetVisible(false)

	-- title
	local label_title = XEGUI.Lua:GetWindow('MessageBox/Title')
	local title = CLanguage:GetContent(args_t)
	label_title:SetText(title)

	-- content
	local label_content = XEGUI.Lua:GetWindow('MessageBox/Content')
	local content = CLanguage:GetContent(args_c)
	label_content:SetText(content)

	win:SetVisible(true)
	win:SetModalState(true)
end

function MessageBox_Ok(args)
	local win = XEGUI.Lua:GetWindow('MessageBox')
	win:SetModalState(false)
	win:SetVisible(false)
	CLua:MessageBoxOk()
end

function MessageBox_Cancel(args)
	local win = XEGUI.Lua:GetWindow('MessageBox')
	win:SetModalState(false)
	win:SetVisible(false)
	CLua:MessageBoxCancel()
end

MessageBox_Init()
