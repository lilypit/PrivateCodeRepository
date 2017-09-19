--[[


This script is used to managed zombies for an old ROBLOX game that I made. By using a mix of raycasting and magnitude, the script handles both the movement
of the zombie entities and the damage that they do to players. 




]]



wait(3)				--todo remove and fix

local connections = {}

local dum = workspace.Dummies:GetChildren()[1]:Clone()
local p=game:GetService("PathfindingService")
--p.EmptyCutoff=0

Distance = 1000						--todo impliment			-- distance zombies will go to find a torso





function findNearestTorso(pos)									-- function to find nearest torso to each zombie, arg = position of zombies' torso
    local list = game.Workspace:children()						-- all things in workspace
    local torso = nil											-- current torso, set to nil to initialize/reset
    local dist = 1000											-- distance zombies will go to find a torso
    local temp = nil											-- to find right arm
    local human = nil											-- to find humanoid
    local temp2 = nil
    for x = 1, #list do
        temp2 = list[x]
		local healthVal = 300 
        if (temp2.className == "Model") and (temp2 ~= script.Parent) then
            temp = temp2:findFirstChild("Right Arm")
            human = temp2:findFirstChild("Humanoid")
			if (temp ~= nil) and (human ~= nil) and (human.Health > 0) then
				if (temp.Position - pos).magnitude < dist then
					torso = temp
					dist = (temp.Position - pos).magnitude
				end
			end
        end
    end
	return torso
end
    
function addz(v)
    Spawn(function() -- spawn function
		local zombType = v.ZombieType

        v:WaitForChild("Humanoid").WalkSpeed=workspace.Configerations:FindFirstChild(zombType.Value).Speed.Value
        local parts={}
        local target=v.Torso
		local c1
      	c1 = v:FindFirstChild("Humanoid").Died:connect(function() c1:Disconnect() wait(3) v:Destroy() dum:Clone().Parent = workspace.Dummies end) 
		table.insert(connections,c1) 
		--will manage respawns, if Mode == on, then 
		
		while c1 do wait()
			
			target = findNearestTorso(v.Torso.Position)
			if target ~= nil then
			for _,v in pairs(parts)do v:Destroy()end parts={}
			local path=p:ComputeRawPathAsync(v.Torso.Position,target.Position,500)
			
			if(v.Torso.Position-target.Position).magnitude<6 and target~=v.Torso and v.Humanoid.Health > 0 and v.CanAttack.Value == true then		
				v.CanAttack.Value = false
				Spawn(function() 
					wait(.5)					
					v.CanAttack.Value = true
				end)
				target.Parent:FindFirstChild("Humanoid"):TakeDamage(workspace.Configerations:FindFirstChild(zombType.Value).Damage.Value)
				
        local parts={}
			end
			local points=path:GetPointCoordinates()
			if #points>1 and c1 then
				for i=1, workspace.Configerations:FindFirstChild(zombType.Value).Iterations.Value do
					local part,point=workspace:FindPartOnRay(Ray.new(points[math.min(#points,i)],Vector3.new(0,-10,0)))
					local part,point2=workspace:FindPartOnRay(Ray.new(points[math.min(#points,i+1)],Vector3.new(0,-10,0)))
					local count=0
					while math.min((point2-v.Torso.Position).magnitude,(point*Vector3.new(1,0,1)-v.Torso.Position*Vector3.new(1,0,1)).magnitude)>3 and count<50 do
						count=count+1			
						v.Humanoid:MoveTo(point2)
						if workspace:FindPartOnRayWithIgnoreList(Ray.new(v.Torso.Position,CFrame.new(v.Torso.Position*Vector3.new(1,0,1),point2*Vector3.new(1,0,1)).lookVector*4),workspace.Dummies:GetChildren())then
							v.Humanoid:MoveTo(point)
						end
						if workspace:FindPartOnRayWithIgnoreList(Ray.new(v.Torso.Position,CFrame.new(v.Torso.Position*Vector3.new(1,0,1),point*Vector3.new(1,0,1)).lookVector*3),workspace.Dummies:GetChildren())then
							v.Humanoid.Jump=true
						end
						wait()
					end
				end
			else
				v.Humanoid:MoveTo(target.Position)
				if target.Position.Y>=v.Humanoid.Torso.Position.Y+3 then
					v.Humanoid.Jump=true
				end
			end
			end
		end
	end)
end




for _,v in pairs(workspace.Dummies:GetChildren())do
	addz(v)
end

workspace.Dummies.ChildAdded:connect(function(child)
	addz(child) 
end)

game.Players.PlayerRemoving:connect(function()
	
	for i=1,#connections do
		connections[i]:Disconnect() 
	end
	
	wait(.1) 
	
	for _,v in pairs(workspace.Dummies:GetChildren())do
		wait(.1)
	addz(v)
end
	
	
end) 

