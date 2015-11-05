function MainLayer_Init(args)
	local win = XEGUI.Lua:LoadUI('MainLayer.xml')
	if nil == win then
		return
	end
	MainLayer_InitWindow(win)
	win:SetVisible(false)
end

function MainLayer_Show(args)
	local win = XEGUI.Lua:GetWindow('MainLayer')
	win:SetVisible(true)
end

function MainLayer_Hide(args)
	local win = XEGUI.Lua:GetWindow('MainLayer')
	win:SetVisible(false)
end

MainLayer_OnCPClicked = {}

function MainLayer_InitWindow(win)
	for i=1, 4 do
		MainLayer_OnCPClicked[i] = function (args)
			CLua:SelectCheckPoint(i)
		end
		local name = 'MainLayer/CP' .. i
		local btn = win:GetWindow(name)
		local label = win:GetWindow(name .. '/Txt')
		init_language_text_with_win(label)
		btn:SubscribeEvent('Clicked', 'MainLayer_OnCPClicked[' .. i .. ']')
	end
end
