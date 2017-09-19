
--[[

This program, again using lua, uses screen color as a linear function of player damage. As the player is damaged, 
the screen gets more blurry and the screen goes to a darker shade of red. 

]]

local player = game.Players.LocalPlayer
local hum = player.Character:FindFirstChild("Humanoid")


if  game.Workspace.CurrentCamera:FindFirstChild("Blur") and game.Workspace.CurrentCamera:FindFirstChild("ColorCorrection") then
	game.Workspace.CurrentCamera:FindFirstChild("Blur").Size = 0 
	game.Workspace.CurrentCamera:FindFirstChild("ColorCorrection").TintColor = Color3.new(255/255,255/255,255/255)
	else
end
	
function BlurScreen(player, health)
	local blurIntensity = 1
	if not game.Workspace.CurrentCamera:FindFirstChild("Blur") then
		Instance.new("BlurEffect").Parent = workspace.CurrentCamera
	end
	if not game.Workspace.CurrentCamera:FindFirstChild("ColorCorrection") then
		Instance.new("ColorCorrectionEffect").Parent = workspace.CurrentCamera
	end
		local Blur = game.Workspace.CurrentCamera:FindFirstChild("Blur")
		Blur.Size =  math.floor(60/hum.Health + 0.01) * blurIntensity + hum.Health * .01

		local ColorCorrection = game.Workspace.CurrentCamera:FindFirstChild("ColorCorrection")
		ColorCorrection.TintColor = Color3.new(255/255,(255 - (255/hum.Health * 9))/255,(255 - (255/hum.Health * 9))/255)
end

 player.Character:FindFirstChild("Humanoid").Changed:connect(function()
	if hum.Health >= 3 or hum.Health == 0 then
	BlurScreen(player,hum.Health)
	else 
	end
	
	if hum.Health <=10 then
		game.Players.LocalPlayer.PlayerGui:FindFirstChild("Heartbeat"):Play()
	end
	
	if hum.Health > 80 then
		game.Workspace.CurrentCamera:FindFirstChild("Blur").Size = 0 
		game.Workspace.CurrentCamera:FindFirstChild("ColorCorrection").TintColor = Color3.new(255/255,255/255,255/255)
	end
end)

