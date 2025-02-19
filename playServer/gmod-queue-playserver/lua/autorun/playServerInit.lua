if SERVER then
    CreateConVar("webServerIP", "193.31.28.96", FCVAR_NONE, "The IP of the webserver.")
    
    util.AddNetworkString("NotifyServerOfClientReady")

    require("queuePlayServer")

    ConnectToWebServer(game.GetIPAddress(), GetConVar("webServerIP"):GetString(), 8080)
    
    net.Receive("NotifyServerOfClientReady", function(len, ply)
        -- SendToWebServer("{ \"steamid\": \"" .. ply:SteamID64() .. "\" }")
    end)

    hook.Add("ShutDown", "MyModShutDown", function()
        DisconnectWebServer()
    end)
end

if CLIENT then
    hook.Add("InitPostEntity", "PlayerReadyForQueue", function()
        net.Start("NotifyServerOfClientReady")
        net.SendToServer()
    end)
end