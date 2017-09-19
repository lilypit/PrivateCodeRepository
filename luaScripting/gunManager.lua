
--[[

Gun management functions. This entire script handles animation sequences, firerate, bulletspread, damage, and sounds.

]]






local tool, player = script.Parent, game:GetService("Players").LocalPlayer

-- CONFIGURATION --
WeaponName = "Crusader";						-- Weapon Name that shows up on the GUI text.
BulletSpread = 0.1;								-- Number of studs the bullet is offset (0 = no spread).
WeaponType = "Auto";							-- "Auto" / "Semi"	
BulletColor = BrickColor.new("Cool yellow");	-- BrickColor of the bullet.
BulletTransparency = 0							-- Transparency of the bullet.
BulletOrigin = tool:WaitForChild("Barrel");		-- What the bullet will shoot from.
HitDamage = 10;									-- How much damage the gun does.
ObjectMultiplier = .3;							-- Have an object you want to destroy? Object must have value of "Health" 
Cursor = "rbxasset://textures\\GunCursor.png";	-- Cursor that shows when the gun is equipped.
HitSoundId = "rbxassetid://131864673";			-- Id of the HitSound
HitSoundVolume = .7;								-- Volume of the HitSound (make 0 if you don't want players to hear)
MaxAmmo = 35;									-- Maximum ammo per clip.
FireRate = 0.11;								    -- Time between each shot.
MeshType = "Cylinder";								-- What kind of bullet you want shooting out of the gun (Block/Cylinder).

local Handle = tool:WaitForChild("Handle")
local Barrel = tool:WaitForChild("Barrel")
local Flashlight = tool:WaitForChild("Flashlight")
local FakeLight = tool:WaitForChild("Light")
local Conditions = tool:WaitForChild("Conditions")
local AmmoCount = Conditions:WaitForChild("Ammo")		
local CanFire = Conditions:WaitForChild("CanFire")

local Teams, ReplicatedStorage, UserInputService, RunService, Debris, Create = game:GetService("Teams"), game:GetService("ReplicatedStorage"), game:GetService("UserInputService"), game:GetService("RunService"), game:GetService("Debris"), LoadLibrary("RbxUtility").Create
local Camera, PlayerGui, Backpack = workspace.CurrentCamera, player:WaitForChild("PlayerGui"), player:WaitForChild("Backpack")
local BulletDump = workspace:WaitForChild("BulletDump") -- Required
local ToolReplicator = ReplicatedStorage:WaitForChild("ToolReplicator") -- Required
local HitSound = player.Backpack:FindFirstChild("HitSound") or Create("Sound"){Name = "HitSound", Pitch = 0.8, SoundId = HitSoundId, Volume = HitSoundVolume, Parent = player.Backpack}
local FireSound, ReloadSound, EmptyMagSound,FlashSound = Handle:FindFirstChild("Fire"), Handle:FindFirstChild("Reload"), Handle:FindFirstChild("EmptyMag"), Handle:FindFirstChild("FlashSound")
local Equipped, Reloading, Firing, MouseDown, Holster = false, false, false, false, false

--animations are autismo dont even bother

local ArmCFrames = {
	Left = CFrame.new(-0.232401475, 0.731157064, 1.02414107, 0.103974499, 0.97441268, -0.199301302, -0.473240495, 0.22472018, 0.851790786, 0.87477237, 0.00575334439, 0.484494328), 
	Right = CFrame.new(-1.00000823, -0.100011915, 0.200000018, 0.866025448, 5.32910745e-014, -0.499999881, 0.499999881, -4.37115588e-008, 0.866025448, -2.18557332e-008, -0.999999881, -3.78553544e-008)
}

local HolsterCFrames = {
	Left = CFrame.new(-0.586823761, 0.480985105, 0.906768203, -0.0642859489, 0.782161772, -0.619750977, -0.431978822, 0.538023889, 0.723826647, 0.899590433, 0.314251065, 0.303290009), 
	Right = CFrame.new(-0.973636985, -0.650349975, 0.0138454549, 0.696540296, 0.00785090867, -0.717475176, 0.682276845, 0.302280575, 0.665676713, 0.222104996, -0.95318675, 0.205194116)
}

local ReloadSequence = {
	{Time = 0.4, Left = CFrame.new(-0.209011436, 0.76324892, 0.78975606, -0.282254279, 0.907642782, 0.310671985, -0.493101478, -0.415047199, 0.76458323, 0.822911561, 0.0626139268, 0.564708829), Right = CFrame.new(-0.55685395, 0.463526368, 0.53752619, 0.954750538, -0.271960884, -0.120368935, 0.071148172, -0.184115022, 0.980326295, -0.288772106, -0.944531083, -0.156434402)},
	{Time = 0.6, Left = CFrame.new(-0.325837493, 0.707264721, 0.802219033, -0.2016415, 0.961395979, 0.187239349, -0.545462966, -0.269001901, 0.79379344, 0.81351763, 0.0579295866, 0.578647852), Right = CFrame.new(-0.736077189, 0.532853663, 0.507766426, 0.942081809, -0.258100748, -0.214163035, 0.11451336, -0.35264346, 0.928724527, -0.315227658, -0.899459004, -0.302662909)},
	{Time = 0.7, Left = CFrame.new(-0.495625108, 0.81194824, 0.587404788, -0.48886016, 0.869798005, 0.0668373406, -0.435639948, -0.309788495, 0.845132411, 0.755800009, 0.384034574, 0.53036195), Right = CFrame.new(-0.833003342, 0.573787272, 0.232965112, 0.942081809, -0.216990575, -0.255728126, 0.11451336, -0.50855732, 0.85337919, -0.315227658, -0.83323729, -0.45425418)},
	{Time = 0.8, Left = CFrame.new(-0.495624006, 0.672275305, 0.883890748, -0.488860488, 0.869798422, 0.0668372884, -0.722871542, -0.446785659, 0.52710402, 0.488336921, 0.209365755, 0.847167552), Right = CFrame.new(-0.898164988, 0.582640946, -0.0121643245, 0.938896179, -0.190729454, -0.286524475, 0.103399783, -0.63769573, 0.76331681, -0.328302413, -0.74630177, -0.57900846)},
	{Time = 0.9, Left = CFrame.new(-0.373379707, 0.768625379, 0.494097263, -0.313948035, 0.946735382, -0.0716073662, -0.406596929, -0.0659107566, 0.911226451, 0.857971728, 0.315193295, 0.405632436), Right = CFrame.new(-0.932295918, 0.531932712, 0.158023566, 0.917598903, -0.210251763, -0.337352186, 0.159367502, -0.582896173, 0.796764791, -0.364162415, -0.784873366, -0.501357317)},
	{Time = 1.1, Left = CFrame.new(-0.649042845, 0.6334849, 0.524738669, -0.338284612, 0.867902994, -0.363741338, -0.509759367, 0.155902475, 0.846073508, 0.791017711, 0.47163415, 0.389682144), Right = CFrame.new(-0.787839651, 0.494286418, 0.505542278, 0.917598903, -0.280750751, -0.281409532, 0.159367502, -0.388723493, 0.907466888, -0.364162415, -0.877537966, -0.311949492)},
	{Time = 1.2, Left = CFrame.new(-0.765217423, 0.393802643, 0.583889008, -0.262994021, 0.845609963, -0.464519083, -0.55953896, 0.258544832, 0.787445486, 0.785971105, 0.467010081, 0.405155957), Right = CFrame.new(-0.965098858, 0.319458991, 0.614931285, 0.957236052, -0.105651543, -0.269326746, 0.242726684, -0.213278487, 0.946359336, -0.15742588, -0.971261859, -0.178513214)},
	{Time = 1.4, Left = CFrame.new(-0.388958633, 0.387100548, 1.23408377, 0.198175311, 0.970845222, -0.134855196, -0.738777578, 0.238368183, 0.630387425, 0.644153416, -0.0252991598, 0.764476895), Right = CFrame.new(-0.850272775, -9.7155571e-006, 0.720583975, 0.957235992, -0.209575221, -0.199442521, 0.242726728, 0.206652865, 0.947828233, -0.157425791, -0.95570457, 0.248685315)},
	{Time = 1.6, Left = CFrame.new(-0.307948738, 0.580714345, 0.879842877, 0.0535680652, 0.998491168, -0.0120923854, -0.691506028, 0.0458293781, 0.720915675, 0.720381916, -0.0302561019, 0.692917407), Right = CFrame.new(-0.942968845, 0.159364432, 0.402672172, 0.957235992, -0.155100465, -0.244219035, 0.242726728, -0.0287858695, 0.969667554, -0.157425791, -0.987478495, 0.0100925863)},	
	{Time = 1.8, Left = ArmCFrames.Left, Right = ArmCFrames.Right},
}

local LightSequence = {
	{Time = 0.2, Left = CFrame.new(-0.209011436, 0.76324892, 0.78975606, -0.282254279, 0.907642782, 0.310671985, -0.493101478, -0.415047199, 0.76458323, 0.822911561, 0.0626139268, 0.564708829)},
	{Time = 0.4, Left = ArmCFrames.Left, Right = ArmCFrames.Right}, --im lazy as fuck and dont want to understand this
}



local CoreBullet = Create("Part"){
	Name = "Bullet";
	BrickColor = BulletColor;
	Material = Enum.Material.Neon;
	FormFactor = Enum.FormFactor.Custom;
	Size = Vector3.new(1, 1, 1);
	Transparency = 0.7;
	Anchored = true;
	CanCollide = false;
	Locked = true;
	
	Create(MeshType == "Block" and "BlockMesh" or MeshType == "Cylinder" and "CylinderMesh" or "BlockMesh"){
		Name = "Mesh",
		Scale = Vector3.new(0.15, 0.15, 1)
	}
}

local CoreBullet2 = Create("Part"){
	Name = "ShowBullet";
	BrickColor = BulletColor;
	Material = Enum.Material.SmoothPlastic;
	FormFactor = Enum.FormFactor.Custom;
	Size = Vector3.new(1, 1, 1);
	Transparency = 0.5;
	Anchored = true;
	CanCollide = false;
	Locked = true;
	
	Create(MeshType == "Block" and "BlockMesh" or MeshType == "Cylinder" and "CylinderMesh" or "BlockMesh"){
		Name = "Mesh",
		Scale = Vector3.new(0.1, 0.1, 1)
	}
}
AmmoCount.Value = MaxAmmo
UserInputService.MouseIconEnabled = true
repeat wait(0.03) until player.Character
repeat wait(0.03) until #player.Character:GetChildren() > 10

function TweenWeld(arm, newCFrame, seconds)
	local torso = player.Character:FindFirstChild("Torso")
	local weld = arm == "Left" and torso:FindFirstChild("LeftArmWeld") or arm == "Right" and torso:FindFirstChild("RightArmWeld")
	if weld then
		local startCF, endCF = weld.C1, newCFrame
		local startPos, startRot = startCF.p, Vector3.new(startCF:toEulerAnglesXYZ())
		local endPos, endRot = endCF.p, Vector3.new(endCF:toEulerAnglesXYZ())
		local diffPos, diffRot = (endPos - startPos), (endRot - startRot)
		local new
		for i = 0, 1, 1/seconds/30 do
			if not weld or not Equipped then break end
			new = CFrame.new(startPos+diffPos * i) * CFrame.Angles(startRot.X+diffRot.X * i, startRot.Y+diffRot.Y * i, startRot.Z+diffRot.Z * i)
			weld.C1 = new
			wait()
		end
		weld.C1 = endCF
	end
end

function WeldArms(c1,lArm,rArm)
	local prop = c1 and "C1" or "C0"
	local char = player.Character
	local torso = char:WaitForChild("Torso")
	local lShoulder,rShoulder = torso:FindFirstChild("Left Shoulder"),torso:FindFirstChild("Right Shoulder")
	if lArm and lShoulder then
		lShoulder.Part1 = nil
		Create("Weld"){
			Name = "LeftArmWeld",
			[prop] = lArm,
			Part0 = torso,
			Part1 = char:FindFirstChild("Left Arm"),
			Parent = torso
		}
	elseif lShoulder and torso:FindFirstChild("LeftArmWeld") then
		torso["LeftArmWeld"]:Remove()
		lShoulder.Part1 = char:FindFirstChild("Left Arm")
	end
	if rArm and rShoulder then
		rShoulder.Part1 = nil
		Create("Weld"){
			Name = "RightArmWeld",
			[prop] = rArm,
			Part0 = torso,
			Part1 = char:FindFirstChild("Right Arm"),
			Parent = torso
		}
	elseif rShoulder and torso:FindFirstChild("RightArmWeld") then
		torso["RightArmWeld"]:Remove()
		rShoulder.Part1 = char:FindFirstChild("Right Arm")
	end
end

function PseudoArms(bool)
	if not type(bool) == "boolean" then print("not a boolean parameter") return end

	local function destroy()
		if Camera:FindFirstChild("FakeArms") then
			Camera:FindFirstChild("FakeArms"):Destroy()
		end
	end	
	
	local function create()
		destroy()
		
		local ArmsModel = Create("Model"){
			Name = "FakeArms",
			Parent = Camera,
			
			Create("Humanoid"){Name = "_"},
		}
		local FakeShirt = player.Character:FindFirstChild("Shirt")
		if FakeShirt then FakeShirt:Clone().Parent = ArmsModel end
		local FakeLeftArm = player.Character:FindFirstChild("Left Arm"):Clone()
		FakeLeftArm.Size = Vector3.new(0.9, 2, 0.9)
		FakeLeftArm.Parent = ArmsModel
		local FakeRightArm = player.Character:FindFirstChild("Right Arm"):Clone()
		FakeRightArm.Size = Vector3.new(0.9, 2, 0.9)
		FakeRightArm.Parent = ArmsModel
		
		Create("Weld"){
			Parent = ArmsModel,
			Name = "FakeLeftShoulder",
			Part0 = player.Character["Left Arm"],
			Part1 = FakeLeftArm
		}		
		Create("Weld"){
			Parent = ArmsModel,
			Name = "FakeRightShoulder",
			Part0 = player.Character["Right Arm"],
			Part1 = FakeRightArm
		}
	end
	
	if bool then
		create()
	else
		destroy()
	end
end

function Light(bool,rate)
	if not type(bool) == "boolean" then print("not a boolean parameter") return end
	Barrel.Flash.Rate = rate
	Barrel.Light.Enabled = bool
	
end

function GetGUI()
	local result = PlayerGui:FindFirstChild("CrusaderGui")
	
	if result then
		return result
	end
end

function UpdateGUI()
	local Gui = GetGUI()
	Gui.Weapon.WeaponName.Text = WeaponName
	Gui.Weapon.Ammo.Text = AmmoCount.Value
end

function GetHumanoid(target)
	local humanoid
	
	humanoid = target.Parent:FindFirstChild("Humanoid")
	if not humanoid and target.Parent.Parent ~= nil then
		humanoid = target.Parent.Parent:FindFirstChild("Humanoid")
	end
	
	return humanoid
end

function IsADefender(me, victim)
	if me.TeamColor == victim.TeamColor then
		return true
	end
	
	return false
end

function DrawLaser(init, at)
	local length = (at-init).magnitude
	local origin = CFrame.new(init, at)
	
	local Laser1 = CoreBullet:Clone()
	Laser1.CFrame = origin * CFrame.new(0, 0, -length/2) * CFrame.Angles(math.rad(90), 0, 0)
	Laser1.Mesh.Scale = Vector3.new(Laser1.Mesh.Scale.x, length, Laser1.Mesh.Scale.x)
	Laser1.Parent = BulletDump
	
	Debris:AddItem(Laser1, 0.03)
	
	local Laser2 = CoreBullet2:Clone()
	Laser2.CFrame = origin * CFrame.new(0, 0, -length/2) * CFrame.Angles(math.rad(90), 0, 0)
	Laser2.Mesh.Scale = Vector3.new(Laser1.Mesh.Scale.x*.5, length, Laser1.Mesh.Scale.x*.5)
	Laser2.Parent = BulletDump
	
	Debris:AddItem(Laser2, 0.03)
end

function CreateRaycast(root, last, ignore)
	local direction = (last - root).unit
	local ray = Ray.new(root, direction * 999)
	local hit, at, surface  = workspace:FindPartOnRayWithIgnoreList(ray, ignore)
	tool.SurfacePos.Value = surface
	if hit and hit.Name == "Ray" then
		hit, at, surface = CreateRaycast(at, direction * 999, ignore)
	end
	
	return hit, at, surface

end


function CreateEffect(position, part)

local dot = game.ReplicatedStorage.dot:Clone()
dot.Parent = workspace.BulletDump
dot.CFrame = position	
print(part.Parent.Name)

if not part.Parent:FindFirstChild("Humanoid")and part.Parent:IsA("Tool") == false and part.Parent:IsA("Hat") == false then 
if part.Material == Enum.Material.Plastic or part.Material == Enum.Material.SmoothPlastic then
ToolReplicator:FireServer("ChangePlasticEffect", dot)
elseif part.Material == Enum.Material.Grass then print("Grass") -- grass
ToolReplicator:FireServer("ChangeGrassEffect", dot)
elseif part.Material == Enum.Material.Wood then print("Wood")  -- wood
ToolReplicator:FireServer("ChangeWoodEffect", dot)
elseif part.Material == Enum.Material.Metal then print("Metal") -- metal
ToolReplicator:FireServer("ChangeMetalEffect", dot)
end
elseif part.Parent:FindFirstChild("Humanoid") or part.Parent:IsA("Hat") then
ToolReplicator:FireServer("ChangeBloodEffect",dot) 

elseif part.Parent:IsA("Tool") then
ToolReplicator:FireServer("ChangeMetalEffect", dot)
end

local rel = tool.SurfacePos.Value  -- Calculating the face. annoying shit man
if (math.abs(rel.Z) > math.abs(rel.Y) and math.abs(rel.Z) > math.abs(rel.X)) then
if (rel.Z > 0) then
dot.Effect.EmissionDirection = "Back"
dot.Dust.EmissionDirection = "Back"
		else
	dot.Effect.EmissionDirection  = "Front"
	dot.Dust.EmissionDirection  = "Front"
end
elseif (math.abs(rel.Y) > math.abs(rel.Z) and math.abs(rel.Y) > math.abs(rel.X)) then
	if (rel.Y > 0) then
	dot.Effect.EmissionDirection  = "Top"
	dot.Dust.EmissionDirection  = "Top"
		else
	dot.Effect.EmissionDirection  = "Bottom"
	dot.Dust.EmissionDirection  = "Bottom"
	end    
elseif (math.abs(rel.X) > math.abs(rel.Z) and math.abs(rel.X) > math.abs(rel.Y)) then
	if (rel.X > 0) then
	dot.Effect.EmissionDirection  = "Right"
	dot.Dust.EmissionDirection  = "Right"
		else
	dot.Effect.EmissionDirection  = "Left"
	dot.Dust.EmissionDirection  = "Left"
	end    
end
Debris:AddItem(dot, 0.3)
end 


function FireLaser(mouse, count)
	local aimPos = mouse.hit.p
	local bulletOrigin = BulletOrigin.Position
	local distance = (bulletOrigin - aimPos).magnitude
	for i = 1, count do
		local aimWithSpread = Vector3.new((aimPos.x)+(math.random(-(BulletSpread/10)*distance,(BulletSpread/10)*distance)),(aimPos.y)+(math.random(-(BulletSpread/10)*distance,(BulletSpread/10)*distance)),(aimPos.z)+(math.random(-(BulletSpread/10)*distance,(BulletSpread/10)*distance)))
		local collision, collisionPos = CreateRaycast(player.Character.Head.Position, aimWithSpread, { player.Character, Camera, workspace.BulletDump})
		DrawLaser(bulletOrigin, collisionPos)
		if collision then		
		CreateEffect(CFrame.new(collisionPos), collision)
			local humanoid = GetHumanoid(collision)
			if humanoid and humanoid:IsA("Humanoid") and game.Players:FindFirstChild(humanoid.Parent.Name) then
				local target = game.Players:FindFirstChild(humanoid.Parent.Name)
				if target and (not IsADefender(player, target) or target.Neutral) then
					ToolReplicator:FireServer("DamageHumanoid", humanoid, HitDamage)
					local Gui = GetGUI()
					Gui.MouseIcon.Hit.Visible = true
					HitSound:Play()
					delay(0.1, function() Gui.MouseIcon.Hit.Visible = false end)
				end				
			elseif 	collision and collision.Parent.Parent.Name == "DestroyableObjects" then
					ToolReplicator:FireServer("DamageObject", collision, HitDamage)

			elseif collision and collision.Name == "Glass" then
					ToolReplicator:FireServer("DestroyWindows",collision)
					-- i could be camming nina right now
			end
	end
end
end

function FireBullet(mouse)
	CanFire.Value = false
	Barrel.Light.Angle = math.random(75, 200)
	Light(true,50)
	FireLaser(mouse, 1)
	local sound = Instance.new("Sound")
	sound.PlayOnRemove = true
	sound.SoundId = "http://www.roblox.com/asset/?id=274924676"
	sound.Parent = game.Players.LocalPlayer.Character.Torso
	sound:Destroy()
	AmmoCount.Value = AmmoCount.Value - 1
	wait(FireRate)
	CanFire.Value = true
end

function ReloadAnimation()
	local Animation = ReloadSequence
	for index, keyframe in next, Animation do
		for limb, cframe in next, keyframe do
			if limb ~= "Time" then
				spawn(function()
					local prevKeyframe = Animation[index - 1]
					local waitTime = prevKeyframe and prevKeyframe.Time or 0
					wait(waitTime)
					if not Equipped then return end
					TweenWeld(limb, cframe, keyframe.Time - waitTime)
				end)
			end
		end
	end
	
	wait(Animation[#Animation].Time)
end

function LightAnimation() 
	local Animation = LightSequence
	for index, keyframe in next, Animation do
		for limb, cframe in next, keyframe do
			if limb ~= "Time" then
				spawn(function()
					local prevKeyframe = Animation[index - 1]
					local waitTime = prevKeyframe and prevKeyframe.Time or 0
					wait(waitTime)
					if not Equipped then return end
					TweenWeld(limb, cframe, keyframe.Time - waitTime)
				end)
			end
		end
	end	
	wait(Animation[#Animation].Time)
end
function Reload()
	if AmmoCount.Value == MaxAmmo then return end
	EmptyMagSound:Play()
	Reloading = true
	Light(false,0)
	local sound = Instance.new("Sound")
	sound.Parent = game.Players.LocalPlayer.Character:FindFirstChild("Head")
	sound.SoundId = "http://www.roblox.com/asset/?id=2697432"
	sound.PlayOnRemove = true
	sound:Destroy()
	local Gui = GetGUI()
	spawn(function()
		for i = 0, 0.5, 0.05 do
			wait(0)
			pcall(function()
				Gui.Weapon.Logo.ImageTransparency = i
			end)
		end
	end)
	Gui.Weapon.Ammo.Text = "REL"
	ReloadAnimation()
	spawn(function()
		for i = 0.5, 0, -0.05 do
			wait(0)
			pcall(function()
				Gui.Weapon.Logo.ImageTransparency = i
			end)
		end
	end)
	if not Reloading then return end
	AmmoCount.Value = MaxAmmo
	Reloading = false
end

function ForceProperWelds()
	coroutine.wrap(TweenWeld)("Left", ArmCFrames.Left, 0.1)
	coroutine.wrap(TweenWeld)("Right", ArmCFrames.Right, 0.1)
end

function KeyPressed(mouse, key)
	key = key:lower()
	
	if key == "r" and not Reloading and Equipped then
		Reload()
	elseif key == "e" and Equipped then -- no deb because fapping, aight?
		LightAnimation()
		FlashSound:Play()
		Flashlight.Light.Enabled = not Flashlight.Light.Enabled
			if FakeLight.Material == Enum.Material.Neon then FakeLight.Material = Enum.Material.SmoothPlastic else
			FakeLight.Material = Enum.Material.Neon
			end
	elseif key == "f" and not Reloading and not Firing and Equipped then
		if not Holster then
			Holster = true
			coroutine.wrap(TweenWeld)("Left", HolsterCFrames.Left, 0.1)
			coroutine.wrap(TweenWeld)("Right", HolsterCFrames.Right, 0.1)
			player.Character.Humanoid.WalkSpeed = 24
		else
			Holster = false
			ForceProperWelds()
			player.Character.Humanoid.WalkSpeed = 16
		end
	end
end

function InitiateFire(mouse)
	if Reloading or Firing or not MouseDown or not CanFire.Value or (player.Character.Humanoid and player.Character.Humanoid.Health <= 0) then return end
	Firing = true
	if WeaponType == "Auto" then
		while MouseDown and Equipped and AmmoCount.Value > 0 and CanFire.Value and Firing and not Reloading and (player.Character.Humanoid and player.Character.Humanoid.Health > 0) do
			FireBullet(mouse)
		end
	elseif WeaponType == "Semi" then
		if Equipped and not Reloading then
			FireBullet(mouse)
		end
	end
	if AmmoCount.Value <= 0 then
		Reload()
	end
	Firing = false
	Light(false,0)
end

function Mouse1Down(mouse)
	if player.Character.Humanoid.Health <= 0 or not Equipped then return end
	if not Firing and not MouseDown and not Reloading and player.Character.Humanoid.Health > 0 and CanFire.Value then
		MouseDown = true
		player.Character.Humanoid.WalkSpeed = 16
		if Holster then
			Holster = false
			ForceProperWelds()
		end
		if AmmoCount.Value <= 0 then
			Reload()
		end
		InitiateFire(mouse)
	end
end

function Mouse1Up(mouse)
	MouseDown = false
	Light(false,0)
end

player.Character:WaitForChild("Humanoid").Died:connect(function()
	UserInputService.MouseIconEnabled = true
	if PlayerGui:FindFirstChild("CrusaderGui") then
		PlayerGui.CrusaderGui:Destroy()
	end
	if Camera:FindFirstChild("FakeArms") then
		Camera:FindFirstChild("FakeArms"):Destroy()
	end
end)


tool.Equipped:connect(function(mouse)
	UserInputService.MouseIconEnabled = false
	local newCrusGui
	if script:FindFirstChild("CrusaderGui") then
		newCrusGui = script.CrusaderGui:Clone()
		newCrusGui.Parent = PlayerGui
		newCrusGui:FindFirstChild("Weapon"):TweenPosition(UDim2.new(0.8, 0,0.8, 0), "Out", "Quad", .7, true)
	end
	Equipped = true
	WeldArms("C1", ArmCFrames.Left, ArmCFrames.Right)
	
	mouse.Button1Down:connect(function() Mouse1Down(mouse) end)
	mouse.Button1Up:connect(function() Mouse1Up(mouse) end)
	mouse.KeyDown:connect(function(key) KeyPressed(mouse, key) end)
	mouse.Move:connect(function()
		if newCrusGui then
			local mTarget = mouse.Target
			if mTarget and mTarget.Parent then
				local humanoid = GetHumanoid(mTarget)
				if humanoid and humanoid:IsA("Humanoid") and game.Players:FindFirstChild(humanoid.Parent.Name) then
					local target = game.Players:FindFirstChild(humanoid.Parent.Name)
					if target and (not IsADefender(player, target) or target.Neutral) then
						newCrusGui.MouseIcon.Icon.ImageColor3 = Color3.new(255/255, 0, 0)
					elseif target and (IsADefender(player, target) and not target.Neutral) then
						newCrusGui.MouseIcon.Icon.ImageColor3 = Color3.new(0, 255/255, 0)
					end
				else
					newCrusGui.MouseIcon.Icon.ImageColor3 = Color3.new(255/255, 255/255, 255/255)
				end
			end
			newCrusGui.MouseIcon.Position = UDim2.new(0, mouse.X - 35, 0, mouse.Y - 35)
		end
	end)
	AmmoCount.Changed:connect(function()
		UpdateGUI()
	end)
	
	local pMouse = player:GetMouse()
	newCrusGui.MouseIcon.Position = UDim2.new(0, pMouse.X - 35, 0, pMouse.Y - 35)
	PseudoArms(true)
	UpdateGUI()
	player.Character.Humanoid.WalkSpeed = 16
end)

tool.AncestryChanged:connect(function()
	print("AH")
	if PlayerGui:FindFirstChild("CrusaderGui") then
	PlayerGui.CrusaderGui:Destroy()
	end
	UserInputService.MouseIconEnabled = true
	Equipped = false
	Firing = false
	MouseDown = false
	Reloading = false
	Holster = false
	Light(false,0)
	WeldArms("")
	PseudoArms(false)
	Flashlight.Light.Enabled = false
	player.Character.Humanoid.WalkSpeed = 16
end)
 	