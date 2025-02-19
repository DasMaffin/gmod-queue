if SERVER then
    CreateConVar("webServerIP", "193.31.28.96", FCVAR_NONE, "The IP of the webserver.")
    
    util.AddNetworkString("NotifyServerOfClientReady")

    require("queuePlayServer")
    
    net.Receive("NotifyServerOfClientReady", function(len, ply)
        SendToWebServer(ply:SteamID64())
    end)

    hook.Add( "GetGameDescription" , "SV_IDENT:GetGameDescription" , function()
        local ip = game.GetIPAddress()
        if not string.StartWith( ip , "0.0.0.0" ) then            
            ConnectToWebServer(ip, GetConVar("webServerIP"):GetString(), 8080)
            hook.Remove( "GetGameDescription" , "SV_IDENT:GetGameDescription")
        end
    end )

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