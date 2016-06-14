forward OnPlayerExitDoor(playerid, doorid, vehicle, vw);
forward SaveDoors(uid);
forward DeleteDoors(itemid);
forward AddDoors(playerid, ownertype, owner, comment[31]);
forward OnPlayerEnterDoor(playerid, doorid);

stock GetPickupID(pickup)
{
	new uid = 0;
	ForeachEx(i, MAX_DOORS)
	{
	    if(DoorInfo[i][Pickup] == pickup)
	    {
	        uid = i;
	    }
	}
	return uid;
}

stock IsOwnerDoor(playerid, doorid)
{
    if(DoorInfo[doorid][dOwnerType] == OWNER_PLAYER && CharacterCache[playerid][pUID] == DoorInfo[doorid][dOwner] ||
       DoorInfo[doorid][dOwnerType] == OWNER_GROUP && MemberGroup[playerid][1][GroupID] == DoorInfo[doorid][dOwner] && IsPlayerPermInGroup(playerid, MemberGroup[playerid][1][GroupID], PANEL_DOOR) ||
       DoorInfo[doorid][dOwnerType] == OWNER_GROUP && MemberGroup[playerid][2][GroupID] == DoorInfo[doorid][dOwner] && IsPlayerPermInGroup(playerid, MemberGroup[playerid][2][GroupID], PANEL_DOOR) ||
       DoorInfo[doorid][dOwnerType] == OWNER_GROUP && MemberGroup[playerid][3][GroupID] == DoorInfo[doorid][dOwner] && IsPlayerPermInGroup(playerid, MemberGroup[playerid][3][GroupID], PANEL_DOOR) ||
       DoorInfo[doorid][dOwnerType] == OWNER_JAIL && IsPlayerKindGroup(playerid, GROUP_PD) ||
       CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_DOORS)
    {
        return true;
    }
    else return false;
}

stock IsOwnerDoorUnPermission(playerid, doorid)
{
    if(DoorInfo[doorid][dOwnerType] == OWNER_PLAYER && CharacterCache[playerid][pUID] == DoorInfo[doorid][dOwner] ||
       DoorInfo[doorid][dOwnerType] == OWNER_GROUP && MemberGroup[playerid][1][GroupID] == DoorInfo[doorid][dOwner] ||
       DoorInfo[doorid][dOwnerType] == OWNER_GROUP && MemberGroup[playerid][2][GroupID] == DoorInfo[doorid][dOwner] ||
       DoorInfo[doorid][dOwnerType] == OWNER_GROUP && MemberGroup[playerid][3][GroupID] == DoorInfo[doorid][dOwner] ||
       DoorInfo[doorid][dOwnerType] == OWNER_JAIL && IsPlayerKindGroup(playerid, GROUP_PD) ||
       CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_DOORS)
    {
        return true;
    }
    else return false;
}

public OnPlayerExitDoor(playerid, doorid, vehicle, vw)
{
    if(CharacterCache[playerid][pBW])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Jesteœ w stanie nieprzytomnoœci dlatego nie mo¿esz odgrywaæ akcji wejœcia do budynku.", "Zamknij", "");
        return 1;
    }

    if(vw == 0) vw = DoorInfo[doorid][dEnterVw];

    SetPlayerVirtualWorld(playerid, DoorInfo[doorid][dEnterVw]);
    SetPlayerInterior(playerid, DoorInfo[doorid][dEnterInt]);
    SetPlayerPos(playerid, DoorInfo[doorid][dEnterX], DoorInfo[doorid][dEnterY], DoorInfo[doorid][dEnterZ]);
    SetPlayerFacingAngle(playerid, DoorInfo[doorid][dEnterAng]);

    PlayerTextDrawHide(playerid, InfoDoor[playerid]);
    PlayerTextDrawHide(playerid, BoxDoor[playerid]);
    PlayerTextDrawHide(playerid, BoxDoorIcon[playerid]);
    PlayerTextDrawHide(playerid, IconDoorRed[playerid]);
    PlayerTextDrawHide(playerid, IconDoorPurple[playerid]);
    PlayerTextDrawHide(playerid, IconDoorGreen[playerid]);
    
    new godzina, minuta;
    gettime(godzina, minuta);
    
    SetWorldTime(godzina + 1);
    SetPlayerWeather(playerid, 1);

    if(GetPlayerVirtualWorld(playerid) == 0)
    {
        PlayerDoor[playerid] = 0;
    }
    else PlayerDoor[playerid] = doorid;

    if(vw != 0) SetPlayerVirtualWorld(playerid, DoorInfo[doorid][dEnterVw]);

    StopAudioStreamForPlayer(playerid);
    return 1;
}

public SaveDoors(uid)
{
    new query[850];
    if(strfind(DoorInfo[uid][dName], "`", true) >= 0) return 1;
    if(strlen(DoorInfo[uid][dName]) > 31) return 1;

    format(query, sizeof(query), "UPDATE `fc_doors` SET `ownertype` = '%d', `owner` = '%d', `enterx` = '%f', `entery` = '%f', `enterz` = '%f', `enterang` = '%f', `enterint` = '%d', `entervw` = '%d', `exitx` = '%f', `exity` = '%f', `exitz` = '%f', `exitang` = '%f', `exitint` = '%d', `exitvw` = '%d', `lock` = '%d', `pickupid` = '%d', `name` = '%s', `garage` = '%d', `value` = '%d', `enter_price` = '%d', `audio_url` = '%s', `object` = '%d', `block` = '%d' WHERE `uid` = '%d'",
            DoorInfo[uid][dOwnerType],
            DoorInfo[uid][dOwner],
            DoorInfo[uid][dEnterX],
            DoorInfo[uid][dEnterY],
            DoorInfo[uid][dEnterZ],
            DoorInfo[uid][dEnterAng],
            DoorInfo[uid][dEnterInt],
            DoorInfo[uid][dEnterVw],
            DoorInfo[uid][dExitX],
            DoorInfo[uid][dExitY],
            DoorInfo[uid][dExitZ],
            DoorInfo[uid][dExitAng],
            DoorInfo[uid][dExitInt],
            DoorInfo[uid][dExitVw],
            DoorInfo[uid][dLock],
            DoorInfo[uid][dPickupID],
            DoorInfo[uid][dName],
            DoorInfo[uid][dGarage],
            DoorInfo[uid][dValue],
            DoorInfo[uid][dEnterCash],
            DoorInfo[uid][dAudioURL],
            DoorInfo[uid][dObject],
            DoorInfo[uid][dBlock],
            uid);
    mysql_check();
    mysql_query(query);
    mysql_free_result();

    return 1;
}

public DeleteDoors(itemid)
{
    new query[100];
    format(query, sizeof(query), "DELETE FROM `fc_doors` WHERE `uid` = '%d'", itemid);

    mysql_check();
    mysql_query(query);

    DestroyDynamicPickup(DoorInfo[itemid][Pickup]);
    DoorInfo[itemid][dUID]       = 0;
    DoorInfo[itemid][dOwnerType] = 0;
    DoorInfo[itemid][dOwner]     = 0;
    DoorInfo[itemid][dEnterX]    = 0.0;
    DoorInfo[itemid][dEnterY]    = 0.0;
    DoorInfo[itemid][dEnterZ]    = 0.0;
    DoorInfo[itemid][dEnterAng]  = 0;
    DoorInfo[itemid][dEnterInt]  = 0;
    DoorInfo[itemid][dEnterVw]   = 0;
    DoorInfo[itemid][dExitX]     = 0.0;
    DoorInfo[itemid][dExitY]     = 0.0;
    DoorInfo[itemid][dExitZ]     = 0.0;
    DoorInfo[itemid][dExitAng]   = 0.0;
    DoorInfo[itemid][dExitInt]   = 0;
    DoorInfo[itemid][dExitVw]    = 0;
    DoorInfo[itemid][dLock]      = 0;
    DoorInfo[itemid][dPickupID] = 0;
    DoorInfo[itemid][dValue] = 0;
    DoorInfo[itemid][dEnterCash] = 0;

    format(DoorInfo[itemid][dAudioURL], 128, "");
    format(DoorInfo[itemid][dName], 31, "");

    DoorInfo[itemid][dGarage]     = 0;
    DoorInfo[itemid][dObject] = 0;
    DoorInfo[itemid][dBlock] = 0;

    mysql_free_result();
    return 1;
}

public AddDoors(playerid, ownertype, owner, comment[31])
{
    if(strlen(comment) >= 32) return 1;
    new Float:X, Float:Y, Float:Z, Float:Ang;
    GetPlayerPos(playerid, X, Y, Z);
    GetPlayerFacingAngle(playerid, Ang);

    new query[512], comment1[31];

    mysql_real_escape_string(comment, comment1);

    format(query, sizeof(query), "INSERT INTO `fc_doors` (`ownertype`, `owner`, `enterx`, `entery`, `enterz`, `enterang`, `enterint`, `entervw`, `exitx`, `exity`, `exitz`, `exitang`, `exitint`, `exitvw`, `lock`, `pickupid`, `name`, `garage`) VALUES ('%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%s', '%d')",
    ownertype, owner, X, Y, Z, Ang, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 1239, comment1, 0);

    mysql_check();
    mysql_query(query);

    new itemid = mysql_insert_id();

    DoorInfo[itemid][dUID] = itemid;

    DoorInfo[itemid][dOwnerType] = ownertype;
    DoorInfo[itemid][dOwner] = owner;

    DoorInfo[itemid][dEnterX]   = X;
    DoorInfo[itemid][dEnterY]   = Y;
    DoorInfo[itemid][dEnterZ]   = Z;
    DoorInfo[itemid][dEnterAng] = Ang;
    DoorInfo[itemid][dEnterInt] = GetPlayerInterior(playerid);
    DoorInfo[itemid][dEnterVw]  = GetPlayerVirtualWorld(playerid);

    DoorInfo[itemid][dExitX] = X;
    DoorInfo[itemid][dExitY] = Y;
    DoorInfo[itemid][dExitZ] = Z;
    DoorInfo[itemid][dExitAng] = Ang;
    DoorInfo[itemid][dExitInt] = 0;
    DoorInfo[itemid][dExitVw] = itemid;
    DoorInfo[itemid][dEnterCash] = 0;

    format(DoorInfo[itemid][dAudioURL], 128, "");
    format(DoorInfo[itemid][dName], 31, "%s", comment);
    DoorInfo[itemid][dLock] = 0;
    DoorInfo[itemid][dPickupID] = 1239;
    DoorInfo[itemid][dGarage] = 0;
    DoorInfo[itemid][dValue] = 0;
    DoorInfo[itemid][dObject] = 0;
    DoorInfo[itemid][dBlock] = 0;

    mysql_free_result();
    SaveDoors(itemid);

    DoorInfo[itemid][Pickup] = CreateDynamicPickup(DoorInfo[itemid][dPickupID], 1, DoorInfo[itemid][dEnterX], DoorInfo[itemid][dEnterY], DoorInfo[itemid][dEnterZ], DoorInfo[itemid][dEnterVw], DoorInfo[itemid][dEnterInt]);
    PickupInfo[DoorInfo[itemid][Pickup]][Name] = DoorInfo[itemid][dName];
    return itemid;
}

public OnPlayerEnterDoor(playerid, doorid)
{
    if(CharacterCache[playerid][pBW])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Jesteœ w stanie nieprzytomnoœci dlatego nie mo¿esz odgrywaæ akcji wejœcia do budynku.", "Zamknij", "");
        return 1;
    }

    PlayerDoor[playerid] = doorid;

    SetPlayerVirtualWorld(playerid, DoorInfo[doorid][dExitVw]);
    SetPlayerInterior(playerid, DoorInfo[doorid][dExitInt]);
    SetPlayerPos(playerid, DoorInfo[doorid][dExitX], DoorInfo[doorid][dExitY], DoorInfo[doorid][dExitZ]);
    SetPlayerFacingAngle(playerid, DoorInfo[doorid][dExitAng]);

    if(DoorInfo[doorid][dAudioURL])
    {
        StopAudioStreamForPlayer(playerid);
        PlayAudioStreamForPlayer(playerid, DoorInfo[doorid][dAudioURL]);
    }
    if(DoorInfo[doorid][dAlarm])
    {
        new string[128];
        format(string, sizeof(string), "** W lokalu %s s³ychaæ g³oœny dŸwiêk alarmu **", DoorInfo[doorid][dName]);
        
        SendClientMessageAroundDoor(playerid, doorid, string);
    }
    if(DoorInfo[doorid][dValue] & DOOR_GATE)
    {
        if(PlayerHaveItemWeapon(playerid))
        {
	    	new string[128];
	        format(string, sizeof(string), "** W lokalu %s s³ychaæ g³oœny dŸwiêk bramek metalowych **", DoorInfo[doorid][dName]);

	        SendClientMessageAroundDoor(playerid, doorid, string);
        }
    }

    PlayerTextDrawHide(playerid, InfoDoor[playerid]);
    PlayerTextDrawHide(playerid, BoxDoor[playerid]);
    PlayerTextDrawHide(playerid, BoxDoorIcon[playerid]);
    PlayerTextDrawHide(playerid, IconDoorRed[playerid]);
    PlayerTextDrawHide(playerid, IconDoorPurple[playerid]);
    PlayerTextDrawHide(playerid, IconDoorGreen[playerid]);

    SetPlayerWeather(playerid, 1);
    return 1;
}