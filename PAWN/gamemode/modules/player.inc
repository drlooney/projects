forward UpdatePlayerStatus(playerid);
forward TeleportPlayerToSpawn(playerid);
forward SearchPlayerUseModelGun(playerid, model);
forward LoadPlayerHouse(playerid);
forward LoadPlayerGroup(playerid);
forward SaveMember(playerid, slot);
forward DeleteMember(playerid, groupid);
forward PlayerToPlayer(Float:radi, playerid, targetid);
forward GivePenalty(playerid, playerid2, time, type, value, reason[128]);
forward UpdatePlayer3DTextNick(i);
forward LoadPlayerVehicles(playerid);
forward SavePlayerStats(playerid, what);
forward CreatePlayerTDGroups(playerid);
forward PlayerHaveItemValue(playerid, type, value1);
forward HidePlayerGroups(playerid);
forward ShowPlayerGroups(playerid);
forward PlayerHaveItemWeapon(playerid);
forward PlayerHaveItemType(playerid, type);
forward PlayerHaveItemValues(playerid, type, value1, value);
forward IsPlayerItem(owner, uid);
forward ReloadAnims(playerid);
forward RemovePlayerBuild(playerid);
forward IsPlayerFishing(playerid);
forward OnPlayerUseDrug(playerid);
forward LoadPlayerDescs(playerid);
forward SendPlayerText(Float:radi, playerid, string2[], col1, col2, col3, col4, col5);

stock RGBAToHex(r, g, b, a) 
{
    return (r<<24 | g<<16 | b<<8 | a);
}

stock isNumeric(string1[])
{
	new length=strlen(string1);
	if (length==0) return false;
	for (new i = 0; i < length; i++)
	{
		if ((string1[i] > '9' || string1[i] < '0' && string1[i]!='-' && string1[i]!='+') // Not a number,'+' or '-'
             || (string1[i]=='-' && i!=0)                                             // A '-' but not at first.
             || (string1[i]=='+' && i!=0)                                             // A '+' but not at first.
         ) return false;
    }
	if (length==1 && (string1[0]=='-' || string1[0]=='+')) return false;
	return true;
}

stock PlayerName(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	return name;
}

stock PlayerName2(playerid)
{
	new name[MAX_PLAYER_NAME];

	if(!CharacterCache[playerid][pMask])
	{
		GetPlayerName(playerid, name, sizeof(name));	
	}
	else
	{
		format(name, MAX_PLAYER_NAME, "Nieznajomy_%s", CharCode(playerid));
	}

	UnderscoreToSpace(name);
	return name;
}

stock UnderscoreToSpace(name[])
{
	for(new i = 0; i < strlen(name); i++)
	{
		if(name[i] == '_') name[i] = ' ';
	}
}

stock GetAccountIP(playerid)
{
	new ip[16];
	GetPlayerIp(playerid, ip, sizeof(ip));
	return ip;
}

stock SendClientMessageEx(Float:radi, playerid, string[], col1, col2, col3, col4, col5)
{
	new Float:posx, Float:posy, Float:posz, Float:oldposx, Float:oldposy, Float:oldposz, Float:tempposx, Float:tempposy, Float:tempposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	ForeachEx(i, MAX_PLAYERS)
	{
		if(IsPlayerConnected(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
		{
			GetPlayerPos(i, posx, posy, posz);
			tempposx = (oldposx -posx);
			tempposy = (oldposy -posy);
			tempposz = (oldposz -posz);
			if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16))) SendClientMessage(i, col1, string);
			else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8))) SendClientMessage(i, col2, string);
			else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4))) SendClientMessage(i, col3, string);
			else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2))) SendClientMessage(i, col4, string);
			else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))) SendClientMessage(i, col5, string);
		}
	}
	return 1;
}

stock SendWrappedMessageToPlayerRange(playerid, colour, colour1, colour2, colour3, colour4, msg[], range = 20, maxlength=100, const prefix[]="...")
{
    new length = strlen(msg);
    if(length <= maxlength) {
        SendPlayerText(range, playerid, msg, colour, colour1, colour2, colour3, colour4);
        return 1;
    }
    new string[128], idx;
    for(new i, space, plen, bool:useprefix; i < length; i++) {
        if(i - idx + plen >= maxlength) {
            if(idx == space || i - space >= 25) {
                strmid(string, msg, idx, i);
                idx = i;
            } else {
                strmid(string, msg, idx, space);
                idx = space + 1;
            }
            if(useprefix) {
                strins(string, prefix, 0);
            } else {
                plen = strlen(prefix);
                useprefix = true;
            }
            format(string, sizeof(string), "%s...", string);
			toupper(string[0]);
            SendPlayerText(range, playerid, string, colour, colour1, colour2, colour3, colour4);
        } else if(msg[i] == ' ') {
            space = i;
        }
    }
    if(idx < length) 
	{
        strmid(string, msg, idx, length);
        strins(string, prefix, 0);
		toupper(string[0]);
        SendPlayerText(range, playerid, string, colour, colour1, colour2, colour3, colour4);
    }
    return 1;
}

stock GivePlayerCash(playerid, money)
{
    CharacterCache[playerid][pCash] += money;
    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);

   	ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, CharacterCache[playerid][pCash]);
}

stock GetClosestBusStop(playerid)
{
	new uid = 0;

	ForeachEx(i, MAX_BUSSTOP)
	{
		if(PlayerToPoint(6.0, playerid, BusStop[i][bPos][0], BusStop[i][bPos][1], BusStop[i][bPos][2]))
		{
			uid = i;
		}
	}
	
	return uid;
}

stock GetClosestPlant(playerid)
{
	new uid = 0;

	ForeachEx(i, MAX_PLANTS)
	{
		if(PlayerToPoint(2.0, playerid, PlantInfo[i][plantX], PlantInfo[i][plantY], PlantInfo[i][plantZ]))
		{
			uid = i;
		}
	}
	
	return uid;
}


stock GetClosestDoor(playerid)
{
	new uid = 0;
	ForeachEx(i, MAX_DOORS)
	{
		if(PlayerToPoint(1.0, playerid, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ]) && GetPlayerVirtualWorld(playerid) == DoorInfo[i][dEnterVw] || PlayerToPoint(1.0, playerid, DoorInfo[i][dExitX], DoorInfo[i][dExitY], DoorInfo[i][dExitZ]) && GetPlayerVirtualWorld(playerid) == DoorInfo[i][dExitVw])
		{
			uid = i;
		}
	}
	
	return uid;
}

stock GetClosestLabel(playerid)
{
	new uid = 0;

	ForeachEx(i, MAX_LABELS)
	{
		if(PlayerToPoint(5.0, playerid, LabelInfo[i][labelPos][0], LabelInfo[i][labelPos][1], LabelInfo[i][labelPos][2]) && GetPlayerVirtualWorld(playerid) == LabelInfo[i][labelVw] && GetPlayerInterior(playerid) == LabelInfo[i][labelInt])
		{
			uid = i;
		}
	}
	
	return uid;
}

stock GetObjectModelClosest( playerid, model )
{
	new uid = 0;
	ForeachEx(i, MAX_OBJECTS)
	{
		if(ObjectInfo[i][oModel] == model)
		{
			if(PlayerToPoint(5.0, playerid, ObjectInfo[i][oX], ObjectInfo[i][oY], ObjectInfo[i][oZ]))
			{
				uid = i;
			}
		}
	}
	
	return uid;
}

stock GetClosestVehicle(playerid)
{
	new Float:prevdist = 5.000, prevcar = INVALID_VEHICLE_ID;
	ForeachEx(carid, MAX_VEHICLES)
	{
		new Float:dist = GetDistanceToVehicle(playerid, carid);
		if ((dist < prevdist))
		{
			prevdist = dist;
			prevcar = carid;
		}
	}
	return prevcar;
}

stock GetObjectGateIndex( playerid, Float:range )
{
	new uid = 0;

	ForeachEx(i, MAX_OBJECTS)
	{
		if(ObjectInfo[i][oGate])
		{
			if(PlayerToPoint(range, playerid, ObjectInfo[i][oX], ObjectInfo[i][oY], ObjectInfo[i][oZ]) && ObjectInfo[i][oVW] == GetPlayerVirtualWorld(playerid) || PlayerToPoint(range, playerid, ObjectInfo[i][oGateX], ObjectInfo[i][oGateY], ObjectInfo[i][oGateZ]) && ObjectInfo[i][oVW] == GetPlayerVirtualWorld(playerid))
			{
				uid = i;
			}
		}
	}
	
	return uid;
}

stock SetPlayerHP(playerid, Float:hp)
{	
	if(hp > 100)
	{
	    CharacterCache[playerid][pHealth] = 100.0;
	    SetPlayerHealth(playerid, CharacterCache[playerid][pHealth]);
	}
	else
	{
		CharacterCache[playerid][pHealth] = hp;
		SetPlayerHealth(playerid, CharacterCache[playerid][pHealth]);
	}
}

stock AddPlayerHP(playerid, Float:hp)
{
	CharacterCache[playerid][pHealth] += hp;
	
	new Float: ghp;
	GetPlayerHealth(playerid, ghp);
	SetPlayerHealth(playerid, ghp + hp);
	
	if(CharacterCache[playerid][pHealth] > 100)
	{
	    CharacterCache[playerid][pHealth] = 100.0;
	}
}

stock PreloadAnimLib(playerid, animlib[])
{
	ApplyAnimation(playerid, animlib, "null", 0.0, 0, 0, 0, 0, 0);
	return 1;
}

stock IsOwnerItem(playerid, itemid)
{
	new data[64], mysql[128], owner, ownertype;
    
	format(mysql, sizeof(mysql), "SELECT `owner`, `ownertype` FROM `fc_items` WHERE `uid` = '%d'", itemid);
	mysql_query(mysql);
	
	mysql_store_result();
	mysql_fetch_row_format(data, "|");
 	sscanf(data, "p<|>dd", owner, ownertype);
 	mysql_free_result();
	
	if(ownertype == OWNER_PLAYER && owner == CharacterCache[playerid][pUID] ||
	   ownertype == OWNER_GROUP && owner == MemberGroup[playerid][1][GroupID] ||
	   ownertype == OWNER_GROUP && owner == MemberGroup[playerid][2][GroupID] ||
	   ownertype == OWNER_GROUP && owner == MemberGroup[playerid][3][GroupID] ||
	   CharacterCache[playerid][pAdmin] == 6)
	{
		return true;
	}
	else return false;
}

public SendPlayerText(Float:radi, playerid, string2[], col1, col2, col3, col4, col5)
{
    if(IsPlayerConnected(playerid))
    {
        new Float:posx, Float:posy, Float:posz;
        new Float:oldposx, Float:oldposy, Float:oldposz;
        new Float:tempposx, Float:tempposy, Float:tempposz;
        GetPlayerPos(playerid, oldposx, oldposy, oldposz);
        ForeachEx(i, MAX_PLAYERS)
        {
			if(IsPlayerConnected(i) && (GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)))
            {
                GetPlayerPos(i, posx, posy, posz);
                tempposx = (oldposx -posx);
                tempposy = (oldposy -posy);
                tempposz = (oldposz -posz);
                if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16)))
                {
                    SendClientMessage(i, col1, string2);
                }
                else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8)))
                {
                    SendClientMessage(i, col2, string2);
                }
                else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4)))
                {
                    SendClientMessage(i, col3, string2);
                }
                else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2)))
                {
                    SendClientMessage(i, col4, string2);
                }
                else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
                {
                    SendClientMessage(i, col5, string2);
                }
            }
        }
    }
    return 1;
}

stock IsAnyPlayerInVehicle(vehicleid)
{
	if(vehicleid)
	{
		ForeachEx(i, MAX_PLAYERS)
		{
			if(GetPlayerVehicleID(i) == vehicleid)
			{
				return true;
			}
		}
	}
	return false;
}

stock GetPlayerWeaponAmmo(playerid, weaponid)
{
	new ammo, weapons[13][2];
	ForeachEx(i, 13)
	{
		GetPlayerWeaponData(playerid, i, weapons[i][0], weapons[i][1]);
		if(weapons[i][0] == weaponid)
		{
			ammo = weapons[i][1];
		}
	}
	return ammo;
}

stock RemovePlayerWeapon(playerid, weaponid)
{
    new plyWeapons[12];
    new plyAmmo[12];

    for(new slot = 0; slot != 12; slot++)
	{
		new wep, ammo;
		GetPlayerWeaponData(playerid, slot, wep, ammo);
    	if(wep != weaponid)
    	{
    	    GetPlayerWeaponData(playerid, slot, plyWeapons[slot], plyAmmo[slot]);
    	}
	}

    ResetPlayerWeapons(playerid);
    for(new slot = 0; slot != 12; slot++)
    {
    	GivePlayerWeapon(playerid, plyWeapons[slot], plyAmmo[slot]);
    }
}

stock GetPlayerID(playeruid)
{
	new playerid = -1;

	ForeachEx(i, MAX_PLAYERS)
	{
		if(Logged[i] && CharacterCache[i][pUID] == playeruid)
		{
			playerid = i;
			break;
		}
	}
	
	return playerid;
}

stock IsPlayerPremium(playerid)
{
	if(CharacterCache[playerid][pPremium] > gettime() || CharacterCache[playerid][pPremium] == -1) return true;
	else return false;
}

public LoadPlayerDescs(playerid)
{
	new uid, data[256], i = 0;
	mysql_query_format("SELECT * FROM `fc_descriptions` WHERE `desc_char` = '%d'", CharacterCache[playerid][pUID]);
	
	mysql_store_result();
	while(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>d", uid);
		sscanf(data, "p<|>ds[32]ds[128]",
		DescInfo[uid][descID],
		DescInfo[uid][descTitle],
		DescInfo[uid][descChar],
		DescInfo[uid][descText]);

		i ++;
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d opisów z bazy danych.", i);
}

stock GetClosestBus(playerid, Float:Prevdist)
{
	new Prevbus = 0;
	
	ForeachEx(i, MAX_BUSSTOP)
	{
		new Float:Dist = GetDistanceBetweenPoints(CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1], CharacterCache[playerid][pBusPos][2], BusStop[i][bPos][0], BusStop[i][bPos][1], BusStop[i][bPos][2]);

		if(Dist < Prevdist)
		{
			Prevdist = Dist;
			Prevbus = i;
		}
	}
	
	return Prevbus;
}

stock GetPlayerSpeed(playerid, get3d)
{
	new Float: x, Float: y, Float: z;
	if (IsPlayerInAnyVehicle (playerid)) GetVehicleVelocity(GetPlayerVehicleID(playerid), x, y, z);
	else GetPlayerVelocity (playerid, x, y, z);
	return Speed(x, y, z, 100.0, get3d);
}


stock GetPlayerDoors(playerid)
{
	new list = 0;

	ForeachEx(i, MAX_DOORS)
	{
	    if(DoorInfo[i][dOwnerType] == OWNER_PLAYER && DoorInfo[i][dOwner] == CharacterCache[playerid][pUID])
	    {
	        list ++;
	    }
	}

	return list;
}

stock GetPlayerDesc(playerid)
{
	new num = 0;
	
	ForeachEx(i, MAX_DESC)
	{
		if(DescInfo[i][descChar] == CharacterCache[playerid][pUID])
		{
		    num ++;
		}
	}
	
	return num;
}

public OnPlayerUseDrug(playerid)
{
	if(CharacterCache[playerid][pDrugsTime] > 0)
	{
	    switch(CharacterCache[playerid][pDrugs])
	    {
	        case DRUG_META:
	        {
                SetPlayerDrunkLevel(playerid, 5000);
	        }
	        case DRUG_COCAINE:
	        {
	            SetPlayerWeather(playerid, -66);
                SetPlayerDrunkLevel(playerid, 5000);
                SetPlayerTime(playerid, 12, 0);
	        }
	        case DRUG_MAR:
	        {
	            SetPlayerWeather(playerid, 65);
	            SetPlayerDrunkLevel(playerid, 5000);
				SetPlayerTime(playerid, 12, 0);
	        }
	    }
	}
	else
	{
	    new hours, minutes, seconds;
	    gettime(hours, minutes, seconds);
	    
	    SetPlayerTime(playerid, hours + 1, 0);
	    SetPlayerWeather(playerid, 1);
	    
	    SetPlayerDrunkLevel(playerid, 0);
	    
		HidePlayerProgressBar(playerid, DrugsBar[playerid]);
	}
	
	return 1;
}

public IsPlayerFishing(playerid)
{
	new vehicleid = GetClosestVehicle(playerid);
	if(GetVehicleModel(vehicleid) == 452 || GetVehicleModel(vehicleid) == 453 || GetVehicleModel(vehicleid) == 454 || GetVehicleModel(vehicleid) == 473)
	{
		CharacterCache[playerid][pWater] = WATER_SALT;
	    return true;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 30.0, 2103.7791, -103.5335, 2.2457))
	{
	    CharacterCache[playerid][pWater] = WATER_SWEET;
	    return true;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 30.0, -420.8112, 1163.5447, 1.8502))
	{
	    CharacterCache[playerid][pWater] = WATER_SWEET;
	    return true;
	}
	else if(IsPlayerInRangeOfPoint(playerid, 30.0, 1426.8884, 499.9664, 1.0215))
	{
	    CharacterCache[playerid][pWater] = WATER_SALT;
	    return true;
	}
	else
	{
	    return false;
	}
}

stock SendClientMessageAroundDoor(playerid, doorid, string[])
{
    ForeachEx(i, MAX_PLAYERS)
	{
        if(IsPlayerInRangeOfPoint(i, 15.0, DoorInfo[doorid][dEnterX], DoorInfo[doorid][dEnterY], DoorInfo[doorid][dEnterZ]) && DoorInfo[doorid][dEnterVw] == GetPlayerVirtualWorld(playerid) && DoorInfo[doorid][dEnterInt] == GetPlayerInterior(playerid))
        {
        	SendClientMessage(i, KOLOR_DO, string);
        }
	}
    return 1;
}

public RemovePlayerBuild(playerid)
{
	// -- Fort Carson City
	
	RemoveBuildingForPlayer(playerid, 3365, -95.3125, 1121.3047, 18.7344, 0.25);
	RemoveBuildingForPlayer(playerid, 773, -221.2734, 829.0078, 14.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 769, -229.2266, 908.2578, 10.5156, 0.25);
	RemoveBuildingForPlayer(playerid, 780, -198.3828, 821.5313, 18.5625, 0.25);
	RemoveBuildingForPlayer(playerid, 769, -383.8594, 964.4922, 9.1328, 0.25);
	RemoveBuildingForPlayer(playerid, 773, -394.4609, 978.4844, 8.9609, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -271.2813, 980.9609, 18.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -294.9688, 1000.9141, 18.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 769, -287.8281, 976.1328, 17.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -244.8281, 976.8359, 19.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -313.7422, 1010.2500, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -321.7031, 1005.2734, 18.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -301.8203, 1001.6563, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -342.6797, 1024.2891, 18.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 773, -230.8594, 957.8672, 15.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -238.2578, 981.3438, 18.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 780, -209.1641, 1005.5625, 18.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 773, -238.0625, 1030.9063, 18.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 774, -178.8516, 949.6172, 15.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -353.6875, 1049.7656, 18.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -258.8281, 1036.1250, 18.7734, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -228.8281, 1050.7500, 18.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -240.0625, 1050.6328, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 16061, -193.3750, 1055.2891, 18.3203, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -351.9688, 1062.1719, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 774, -372.7422, 1066.2813, 17.2500, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -233.1172, 1061.6563, 18.8594, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -332.4063, 1072.2422, 18.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -239.3359, 1070.2813, 18.7813, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -289.0625, 1074.9766, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -342.0781, 1078.4609, 18.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -122.6484, 889.3047, 18.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -110.2813, 925.6797, 19.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -75.2969, 924.3906, 19.9219, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -76.3438, 891.0156, 20.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -77.9922, 957.8750, 19.1719, 0.25);
	RemoveBuildingForPlayer(playerid, 773, -154.1953, 1012.9453, 18.3281, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -64.0313, 1009.6719, 18.8438, 0.25);
	RemoveBuildingForPlayer(playerid, 774, -82.9688, 1022.7813, 18.6328, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -127.8750, 1058.6641, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 780, -147.2500, 1055.5156, 18.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -120.4766, 1061.2109, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 652, -82.2969, 1060.2734, 18.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 769, -96.9453, 1054.9297, 18.0469, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -160.5156, 1066.0703, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -164.3750, 1078.3906, 17.7656, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -48.8516, 906.8594, 20.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -0.4141, 917.2422, 21.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -36.6563, 940.9609, 18.7734, 0.25);
	RemoveBuildingForPlayer(playerid, 669, 0.2500, 970.2109, 18.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 773, -20.8281, 953.9844, 14.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 691, -51.3516, 1006.5781, 18.5625, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -39.0938, 999.8672, 19.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 652, -19.9297, 1006.3672, 18.4922, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -1.4609, 998.1094, 18.8438, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -5.0156, 1017.7266, 18.8438, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -51.6875, 1042.5938, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 652, -51.1484, 1052.1094, 18.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -51.1406, 1064.8125, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 691, 1.2578, 1027.0938, 18.5625, 0.25);
	RemoveBuildingForPlayer(playerid, 691, 11.8594, 1009.8125, 17.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 780, 26.6094, 1030.3281, 16.6016, 0.25);
	RemoveBuildingForPlayer(playerid, 691, 27.4297, 1056.7656, 18.5625, 0.25);
	RemoveBuildingForPlayer(playerid, 773, 4.9453, 1052.8906, 14.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 669, 42.2422, 958.3516, 18.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 669, 44.5469, 1003.7813, 15.8594, 0.25);
	RemoveBuildingForPlayer(playerid, 769, 53.2188, 1039.1484, 13.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 780, 60.4844, 966.2266, 15.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 691, 75.7500, 1067.0469, 11.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -334.4531, 1085.9922, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 773, -291.2578, 1085.0938, 17.6563, 0.25);
	RemoveBuildingForPlayer(playerid, 780, -325.9609, 1109.5625, 18.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -228.3828, 1111.8750, 18.8281, 0.25);
	RemoveBuildingForPlayer(playerid, 774, -245.7500, 1111.2813, 17.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -225.3125, 1127.2109, 18.8047, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -232.8125, 1139.4063, 18.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 773, -389.9453, 1162.2813, 14.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -239.8594, 1148.9609, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 16060, -192.0469, 1147.3906, 17.6953, 0.25);
	RemoveBuildingForPlayer(playerid, 769, -232.3594, 1174.4766, 18.5781, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -383.1094, 1185.4453, 17.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -375.7734, 1189.2422, 18.6484, 0.25);
	RemoveBuildingForPlayer(playerid, 3294, -100.0000, 1111.4141, 21.6406, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -120.8750, 1110.4219, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 3292, -95.3125, 1121.3047, 18.7344, 0.25);
	RemoveBuildingForPlayer(playerid, 3293, -100.0000, 1118.6250, 21.9297, 0.25);
	RemoveBuildingForPlayer(playerid, 1345, -90.6016, 1128.2188, 19.4609, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -53.2656, 1135.5781, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 652, -45.2031, 1130.4141, 17.7734, 0.25);
	RemoveBuildingForPlayer(playerid, 780, -84.8906, 1143.4375, 18.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 652, -81.0859, 1149.6406, 18.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -50.5078, 1160.9141, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -41.8125, 1160.0781, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -126.1719, 1159.0703, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -127.0000, 1173.4219, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 652, -57.3516, 1214.4297, 18.4531, 0.25);
	RemoveBuildingForPlayer(playerid, 652, -97.5938, 1241.0781, 16.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 700, -5.2188, 1112.5703, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -13.2969, 1112.2656, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 652, -31.8672, 1118.8359, 17.7734, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -36.4922, 1136.0703, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 652, 1.5000, 1133.8984, 17.7734, 0.25);
	RemoveBuildingForPlayer(playerid, 773, -18.3906, 1136.8203, 18.4609, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 3.8281, 1159.2969, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 669, -31.3203, 1160.6875, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 19.8281, 1085.3984, 19.0469, 0.25);
	RemoveBuildingForPlayer(playerid, 774, 39.5547, 1087.0938, 18.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 669, 17.1406, 1136.5938, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 33.6094, 1152.6953, 19.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 669, 30.4922, 1157.7891, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 22.2578, 1158.4766, 18.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 669, 35.9922, 1157.1875, 18.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 700, 65.0313, 1148.2344, 18.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 691, 68.7969, 1117.5781, 17.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 773, 72.9063, 1137.3281, 14.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 773, 91.9531, 910.4844, 14.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 774, 131.9688, 972.9297, 15.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 773, 159.5547, 1070.9688, 14.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 780, 160.7656, 1054.5078, 16.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 691, 92.4141, 1099.5313, 12.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 691, 79.3359, 1099.9453, 11.9219, 0.25);
	RemoveBuildingForPlayer(playerid, 691, 141.7656, 1109.8828, 11.8906, 0.25);
	RemoveBuildingForPlayer(playerid, 669, 131.4766, 1109.2734, 12.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 691, 160.6875, 1106.7344, 13.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 669, 147.9219, 1090.0625, 12.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 669, 90.0859, 1147.8828, 16.7813, 0.25);

	// -- Koniec Fort Carson City
	return 1;
}

public ReloadAnims(playerid)
{
	PreloadAnimLib(playerid, "BOMBER");
    PreloadAnimLib(playerid, "RAPPING");
    PreloadAnimLib(playerid, "SHOP");
    PreloadAnimLib(playerid, "BEACH");
    PreloadAnimLib(playerid, "SMOKING");
    PreloadAnimLib(playerid, "FOOD");
    PreloadAnimLib(playerid, "ON_LOOKERS");
    PreloadAnimLib(playerid, "DEALER");
    PreloadAnimLib(playerid, "CRACK");
    PreloadAnimLib(playerid, "CARRY");
    PreloadAnimLib(playerid, "COP_AMBIENT");
    PreloadAnimLib(playerid, "PARK");
    PreloadAnimLib(playerid, "INT_HOUSE");
    PreloadAnimLib(playerid, "INT_OFFICE");
    PreloadAnimLib(playerid, "FOOD");
    PreloadAnimLib(playerid, "PED");
    PreloadAnimLib(playerid, "POLICE");
    PreloadAnimLib(playerid, "CAR");
    PreloadAnimLib(playerid, "CAR_CHAT");
    PreloadAnimLib(playerid, "MEDIC");
    PreloadAnimLib(playerid, "GANGS");
    PreloadAnimLib(playerid, "BENCHPRESS");
    PreloadAnimLib(playerid, "HEIST9");
    PreloadAnimLib(playerid, "MISC");
    PreloadAnimLib(playerid, "OTB");
    PreloadAnimLib(playerid, "PAULNMAC");
    PreloadAnimLib(playerid, "SWEET");
    PreloadAnimLib(playerid, "GRAFFITI");
    PreloadAnimLib(playerid, "FIGHT_C");
    PreloadAnimLib(playerid, "FIGHT_B");
    PreloadAnimLib(playerid, "FIGHT_D");
    PreloadAnimLib(playerid, "WAYFARER");
    PreloadAnimLib(playerid, "BASEBALL");
    PreloadAnimLib(playerid, "GRENADE");
    PreloadAnimLib(playerid, "BSKTBALL");
    PreloadAnimLib(playerid, "RIOT");
}

public IsPlayerItem(owner, uid)
{
	new query[256];
	format(query, sizeof(query), "SELECT `uid` FROM `fc_items` WHERE `owner` = '%d' AND `ownertype` = '%d' AND `uid` = '%d'", owner, OWNER_PLAYER, uid);

	mysql_check();
	mysql_query(query);

	mysql_store_result();
	if(mysql_num_rows() > 0)
	{
		mysql_free_result();
		return true;
	}
	else
	{
		mysql_free_result();
		return false;
	}
}

stock CancelOffert(playerid)
{
	OfertaInfo[playerid][oType] = 0;
	OfertaInfo[playerid][oCustomer] = -1;
    OfertaInfo[playerid][oPrice] = 0;
    OfertaInfo[playerid][oValue1] = 0;
    OfertaInfo[playerid][oSeller] = -1;

 	PlayerTextDrawHide(playerid, Offer[playerid]);
	PlayerTextDrawHide(playerid, AcceptOffer[playerid]);
	PlayerTextDrawHide(playerid, CrossOffer[playerid]);
	PlayerTextDrawHide(playerid, InfoOffer[playerid]);
	PlayerTextDrawHide(playerid, InfoBoxOffer[playerid]);
	PlayerTextDrawHide(playerid, ModelOffer[playerid]);
	
	return 1;
}

public PlayerHaveItemValues(playerid, type, value1, value)
{
    new query[256];
    format(query, sizeof(query), "SELECT * FROM `fc_items` WHERE `kind` = '%d' AND `value1` = '%d' AND `value` = '%d' AND `owner` = '%d' AND `ownertype` = '%d'", type, value1, value, CharacterCache[playerid][pUID], OWNER_PLAYER);
    mysql_query(query);
    mysql_store_result();
    if(mysql_num_rows())
    {
        mysql_free_result();
        return true;
    }
    else
    {
        mysql_free_result();
        return false;
    }
}

public PlayerHaveItemType(playerid, type)
{
    new query[256];
    format(query, sizeof(query), "SELECT * FROM `fc_items` WHERE `kind` = '%d' AND `owner` = '%d' AND `ownertype` = '%d'", type, CharacterCache[playerid][pUID], OWNER_PLAYER);
    mysql_query(query);
    mysql_store_result();
    if(mysql_num_rows())
    {
        mysql_free_result();
        return true;
    }
    else
    {
        mysql_free_result();
        return false;
    }
}

public PlayerHaveItemWeapon(playerid)
{
    new query[256];
    format(query, sizeof(query), "SELECT * FROM `fc_items` WHERE `kind` = '%d' AND `owner` = '%d' AND `ownertype` = '%d' AND `value1` IN (22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38)", TYPE_WEAPON, CharacterCache[playerid][pUID], OWNER_PLAYER);
    mysql_query(query);
    mysql_store_result();
    if(mysql_num_rows())
    {
        mysql_free_result();
        return true;
    }
    else
    {
        mysql_free_result();
        return false;
    }
}

public ShowPlayerGroups(playerid)
{
    if(!CharacterCache[playerid][pShowGroups])
    {
        if(MemberGroup[playerid][1][GroupID] || MemberGroup[playerid][2][GroupID] || MemberGroup[playerid][3][GroupID])
        {
            new str[64];
            SelectTextDraw(playerid, 0x3E7336FF);

            CharacterCache[playerid][pShowGroups] = 1;

            PlayerTextDrawShow(playerid, Textdraw0[playerid]);

            if(MemberGroup[playerid][1][GroupID])
            {
                format(str, sizeof(str), "1               %s", GroupData[MemberGroup[playerid][1][GroupID]][Desc]);
                PlayerTextDrawSetString(playerid, Textdraw1[playerid], str);

                PlayerTextDrawShow(playerid, Textdraw1[playerid]);
                PlayerTextDrawShow(playerid, Textdraw2[playerid]);
                PlayerTextDrawShow(playerid, Textdraw3[playerid]);
                PlayerTextDrawShow(playerid, Textdraw4[playerid]);
                PlayerTextDrawShow(playerid, Textdraw5[playerid]);
                PlayerTextDrawShow(playerid, Textdraw6[playerid]);

            }
            if(MemberGroup[playerid][2][GroupID])
            {
                format(str, sizeof(str), "2               %s", GroupData[MemberGroup[playerid][2][GroupID]][Desc]);
                PlayerTextDrawSetString(playerid, Textdraw7[playerid], str);

                PlayerTextDrawShow(playerid, Textdraw7[playerid]);
                PlayerTextDrawShow(playerid, Textdraw8[playerid]);
                PlayerTextDrawShow(playerid, Textdraw9[playerid]);
                PlayerTextDrawShow(playerid, Textdraw10[playerid]);
                PlayerTextDrawShow(playerid, Textdraw11[playerid]);
                PlayerTextDrawShow(playerid, Textdraw12[playerid]);

            }
            if(MemberGroup[playerid][3][GroupID])
            {
                format(str, sizeof(str), "3               %s", GroupData[MemberGroup[playerid][3][GroupID]][Desc]);
                PlayerTextDrawSetString(playerid, Textdraw13[playerid], str);

                PlayerTextDrawShow(playerid, Textdraw13[playerid]);
                PlayerTextDrawShow(playerid, Textdraw14[playerid]);
                PlayerTextDrawShow(playerid, Textdraw15[playerid]);
                PlayerTextDrawShow(playerid, Textdraw16[playerid]);
                PlayerTextDrawShow(playerid, Textdraw17[playerid]);
                PlayerTextDrawShow(playerid, Textdraw18[playerid]);
            }
        }
        else
        {
            GameTextForPlayer(playerid, "~r~Nie znaleziono zadnej grupy!", 3000, 4);
        }
    }

    return 1;
}

public HidePlayerGroups(playerid)
{
    CharacterCache[playerid][pShowGroups] = 0;

    PlayerTextDrawHide(playerid, Textdraw0[playerid]);
    PlayerTextDrawHide(playerid, Textdraw1[playerid]);
    PlayerTextDrawHide(playerid, Textdraw2[playerid]);
    PlayerTextDrawHide(playerid, Textdraw3[playerid]);
    PlayerTextDrawHide(playerid, Textdraw4[playerid]);
    PlayerTextDrawHide(playerid, Textdraw5[playerid]);
    PlayerTextDrawHide(playerid, Textdraw6[playerid]);
    PlayerTextDrawHide(playerid, Textdraw7[playerid]);
    PlayerTextDrawHide(playerid, Textdraw8[playerid]);
    PlayerTextDrawHide(playerid, Textdraw9[playerid]);
    PlayerTextDrawHide(playerid, Textdraw10[playerid]);
    PlayerTextDrawHide(playerid, Textdraw11[playerid]);
    PlayerTextDrawHide(playerid, Textdraw12[playerid]);
    PlayerTextDrawHide(playerid, Textdraw13[playerid]);
    PlayerTextDrawHide(playerid, Textdraw14[playerid]);
    PlayerTextDrawHide(playerid, Textdraw15[playerid]);
    PlayerTextDrawHide(playerid, Textdraw16[playerid]);
    PlayerTextDrawHide(playerid, Textdraw17[playerid]);
    PlayerTextDrawHide(playerid, Textdraw18[playerid]);
    PlayerTextDrawHide(playerid, Textdraw19[playerid]);
    PlayerTextDrawHide(playerid, Textdraw20[playerid]);
    PlayerTextDrawHide(playerid, Textdraw21[playerid]);
    PlayerTextDrawHide(playerid, Textdraw22[playerid]);
    PlayerTextDrawHide(playerid, Textdraw23[playerid]);
    PlayerTextDrawHide(playerid, Textdraw24[playerid]);
    PlayerTextDrawHide(playerid, Textdraw25[playerid]);
    PlayerTextDrawHide(playerid, Textdraw26[playerid]);
    PlayerTextDrawHide(playerid, Textdraw27[playerid]);
    PlayerTextDrawHide(playerid, Textdraw28[playerid]);
    PlayerTextDrawHide(playerid, Textdraw29[playerid]);
    PlayerTextDrawHide(playerid, Textdraw30[playerid]);

    CancelSelectTextDraw(playerid);
}

public PlayerHaveItemValue(playerid, type, value1)
{
    new query[256];
    format(query, sizeof(query), "SELECT * FROM `fc_items` WHERE `kind` = '%d' AND `value1` = '%d' AND `owner` = '%d' AND `ownertype` = '%d'", type, value1, CharacterCache[playerid][pUID], OWNER_PLAYER);
    mysql_query(query);
    mysql_store_result();
    if(mysql_num_rows())
    {
        mysql_free_result();
        return true;
    }
    else
    {
        mysql_free_result();
        return false;
    }
}

public CreatePlayerTDGroups(playerid)
{
    Offer[playerid] = CreatePlayerTextDraw(playerid, 250.000000, 281.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, Offer[playerid], 255);
	PlayerTextDrawFont(playerid, Offer[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Offer[playerid], 0.250000, 0.899999);
	PlayerTextDrawColor(playerid, Offer[playerid], -1);
	PlayerTextDrawSetOutline(playerid, Offer[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Offer[playerid], 1);
	PlayerTextDrawUseBox(playerid, Offer[playerid], 1);
	PlayerTextDrawBoxColor(playerid, Offer[playerid], 85);
	PlayerTextDrawTextSize(playerid, Offer[playerid], 480.000000, 171.000000);

	AcceptOffer[playerid] = CreatePlayerTextDraw(playerid, 391.000000, 327.000000, "~g~~h~~h~Akceptuj");
	PlayerTextDrawAlignment(playerid, AcceptOffer[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, AcceptOffer[playerid], 255);
	PlayerTextDrawFont(playerid, AcceptOffer[playerid], 1);
	PlayerTextDrawLetterSize(playerid, AcceptOffer[playerid], 0.229999, 0.799997);
	PlayerTextDrawColor(playerid, AcceptOffer[playerid], -1);
	PlayerTextDrawSetOutline(playerid, AcceptOffer[playerid], 1);
	PlayerTextDrawSetProportional(playerid, AcceptOffer[playerid], 1);
	PlayerTextDrawUseBox(playerid, AcceptOffer[playerid], 1);
	PlayerTextDrawBoxColor(playerid, AcceptOffer[playerid], 85);
	PlayerTextDrawTextSize(playerid, AcceptOffer[playerid], 430.000000, 51.000000);
	PlayerTextDrawSetSelectable(playerid, AcceptOffer[playerid], 1);

	CrossOffer[playerid] = CreatePlayerTextDraw(playerid, 450.000000, 327.000000, "~r~~h~~h~Odrzuc");
	PlayerTextDrawAlignment(playerid, CrossOffer[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, CrossOffer[playerid], 255);
	PlayerTextDrawFont(playerid, CrossOffer[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CrossOffer[playerid], 0.239998, 0.799997);
	PlayerTextDrawColor(playerid, CrossOffer[playerid], -1);
	PlayerTextDrawSetOutline(playerid, CrossOffer[playerid], 1);
	PlayerTextDrawSetProportional(playerid, CrossOffer[playerid], 1);
	PlayerTextDrawUseBox(playerid, CrossOffer[playerid], 1);
	PlayerTextDrawBoxColor(playerid, CrossOffer[playerid], 85);
	PlayerTextDrawTextSize(playerid, CrossOffer[playerid], 430.000000, 51.000000);
	PlayerTextDrawSetSelectable(playerid, CrossOffer[playerid], 1);

	InfoOffer[playerid] = CreatePlayerTextDraw(playerid, 280.000000, 327.000000, "Szczegoly");
	PlayerTextDrawAlignment(playerid, InfoOffer[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, InfoOffer[playerid], 255);
	PlayerTextDrawFont(playerid, InfoOffer[playerid], 1);
	PlayerTextDrawLetterSize(playerid, InfoOffer[playerid], 0.239998, 0.799997);
	PlayerTextDrawColor(playerid, InfoOffer[playerid], -1);
	PlayerTextDrawSetOutline(playerid, InfoOffer[playerid], 1);
	PlayerTextDrawSetProportional(playerid, InfoOffer[playerid], 1);
	PlayerTextDrawUseBox(playerid, InfoOffer[playerid], 1);
	PlayerTextDrawBoxColor(playerid, InfoOffer[playerid], 85);
	PlayerTextDrawTextSize(playerid, InfoOffer[playerid], 430.000000, 51.000000);
	PlayerTextDrawSetSelectable(playerid, InfoOffer[playerid], 1);

	InfoBoxOffer[playerid] = CreatePlayerTextDraw(playerid, 140.000000, 170.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, InfoBoxOffer[playerid], 255);
	PlayerTextDrawFont(playerid, InfoBoxOffer[playerid], 1);
	PlayerTextDrawLetterSize(playerid, InfoBoxOffer[playerid], 0.310000, 0.799999);
	PlayerTextDrawColor(playerid, InfoBoxOffer[playerid], -1);
	PlayerTextDrawSetOutline(playerid, InfoBoxOffer[playerid], 1);
	PlayerTextDrawSetProportional(playerid, InfoBoxOffer[playerid], 1);
	PlayerTextDrawUseBox(playerid, InfoBoxOffer[playerid], 1);
	PlayerTextDrawBoxColor(playerid, InfoBoxOffer[playerid], 85);
	PlayerTextDrawTextSize(playerid, InfoBoxOffer[playerid], 420.000000, 0.000000);

	ModelOffer[playerid] = CreatePlayerTextDraw(playerid, 370.000000, 181.000000, "_");
	PlayerTextDrawAlignment(playerid, ModelOffer[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, ModelOffer[playerid], 255);
	PlayerTextDrawFont(playerid, ModelOffer[playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawColor(playerid, ModelOffer[playerid], -1);
	PlayerTextDrawUseBox(playerid, ModelOffer[playerid], 1);
	PlayerTextDrawBoxColor(playerid, ModelOffer[playerid], 85);
	PlayerTextDrawTextSize(playerid, ModelOffer[playerid], 40.0, 40.0);
	
    Textdraw0[playerid] = CreatePlayerTextDraw(playerid, 72.000000, 147.000000, "~g~Slot            Nazwa grupy                                                          Opcje");
    PlayerTextDrawBackgroundColor(playerid, Textdraw0[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw0[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw0[playerid], 0.259999, 1.000000);
    PlayerTextDrawColor(playerid, Textdraw0[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw0[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw0[playerid], 1);

    Textdraw1[playerid] = CreatePlayerTextDraw(playerid, 73.000000, 161.000000, "1               Los Santos Government");
    PlayerTextDrawBackgroundColor(playerid, Textdraw1[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw1[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw1[playerid], 0.259999, 1.000000);
    PlayerTextDrawColor(playerid, Textdraw1[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw1[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw1[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw1[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw1[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw1[playerid], 564.000000, 0.000000);

    Textdraw2[playerid] = CreatePlayerTextDraw(playerid, 327.000000, 162.000000, "Info");
    PlayerTextDrawAlignment(playerid, Textdraw2[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw2[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw2[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw2[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw2[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw2[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw2[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw2[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw2[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw2[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw2[playerid], 1);

    Textdraw3[playerid] = CreatePlayerTextDraw(playerid, 380.000000, 162.000000, "Pojazdy");
    PlayerTextDrawAlignment(playerid, Textdraw3[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw3[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw3[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw3[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw3[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw3[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw3[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw3[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw3[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw3[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw3[playerid], 1);

    Textdraw4[playerid] = CreatePlayerTextDraw(playerid, 433.000000, 162.000000, "Sluzba");
    PlayerTextDrawAlignment(playerid, Textdraw4[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw4[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw4[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw4[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw4[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw4[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw4[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw4[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw4[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw4[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw4[playerid], 1);

    Textdraw5[playerid] = CreatePlayerTextDraw(playerid, 486.000000, 162.000000, "Magazyn");
    PlayerTextDrawAlignment(playerid, Textdraw5[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw5[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw5[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw5[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw5[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw5[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw5[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw5[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw5[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw5[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw5[playerid], 1);

    Textdraw6[playerid] = CreatePlayerTextDraw(playerid, 539.000000, 162.000000, "On-line");
    PlayerTextDrawAlignment(playerid, Textdraw6[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw6[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw6[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw6[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw6[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw6[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw6[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw6[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw6[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw6[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw6[playerid], 1);

    Textdraw7[playerid] = CreatePlayerTextDraw(playerid, 73.000000, 174.000000, "2               Los Santos Police Department");
    PlayerTextDrawBackgroundColor(playerid, Textdraw7[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw7[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw7[playerid], 0.259999, 1.000000);
    PlayerTextDrawColor(playerid, Textdraw7[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw7[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw7[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw7[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw7[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw7[playerid], 564.000000, 0.000000);

    Textdraw8[playerid] = CreatePlayerTextDraw(playerid, 327.000000, 175.000000, "Info");
    PlayerTextDrawAlignment(playerid, Textdraw8[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw8[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw8[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw8[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw8[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw8[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw8[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw8[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw8[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw8[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw8[playerid], 1);

    Textdraw9[playerid] = CreatePlayerTextDraw(playerid, 380.000000, 175.000000, "Pojazdy");
    PlayerTextDrawAlignment(playerid, Textdraw9[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw9[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw9[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw9[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw9[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw9[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw9[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw9[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw9[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw9[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw9[playerid], 1);

    Textdraw10[playerid] = CreatePlayerTextDraw(playerid, 433.000000, 175.000000, "Sluzba");
    PlayerTextDrawAlignment(playerid, Textdraw10[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw10[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw10[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw10[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw10[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw10[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw10[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw10[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw10[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw10[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw10[playerid], 1);

    Textdraw11[playerid] = CreatePlayerTextDraw(playerid, 486.000000, 175.000000, "Magazyn");
    PlayerTextDrawAlignment(playerid, Textdraw11[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw11[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw11[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw11[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw11[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw11[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw11[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw11[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw11[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw11[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw11[playerid], 1);

    Textdraw12[playerid] = CreatePlayerTextDraw(playerid, 539.000000, 175.000000, "On-line");
    PlayerTextDrawAlignment(playerid, Textdraw12[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw12[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw12[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw12[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw12[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw12[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw12[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw12[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw12[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw12[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw12[playerid], 1);

    Textdraw13[playerid] = CreatePlayerTextDraw(playerid, 73.000000, 187.000000, "3               Los Santos Fire Department");
    PlayerTextDrawBackgroundColor(playerid, Textdraw13[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw13[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw13[playerid], 0.259999, 1.000000);
    PlayerTextDrawColor(playerid, Textdraw13[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw13[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw13[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw13[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw13[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw13[playerid], 564.000000, 0.000000);

    Textdraw14[playerid] = CreatePlayerTextDraw(playerid, 327.000000, 188.000000, "Info");
    PlayerTextDrawAlignment(playerid, Textdraw14[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw14[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw14[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw14[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw14[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw14[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw14[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw14[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw14[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw14[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw14[playerid], 1);

    Textdraw15[playerid] = CreatePlayerTextDraw(playerid, 380.000000, 188.000000, "Pojazdy");
    PlayerTextDrawAlignment(playerid, Textdraw15[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw15[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw15[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw15[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw15[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw15[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw15[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw15[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw15[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw15[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw15[playerid], 1);

    Textdraw16[playerid] = CreatePlayerTextDraw(playerid, 433.000000, 188.000000, "Sluzba");
    PlayerTextDrawAlignment(playerid, Textdraw16[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw16[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw16[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw16[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw16[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw16[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw16[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw16[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw16[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw16[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw16[playerid], 1);

    Textdraw17[playerid] = CreatePlayerTextDraw(playerid, 486.000000, 188.000000, "Magazyn");
    PlayerTextDrawAlignment(playerid, Textdraw17[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw17[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw17[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw17[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw17[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw17[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw17[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw17[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw17[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw17[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw17[playerid], 1);

    Textdraw18[playerid] = CreatePlayerTextDraw(playerid, 539.000000, 188.000000, "On-line");
    PlayerTextDrawAlignment(playerid, Textdraw18[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw18[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw18[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw18[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw18[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw18[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw18[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw18[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw18[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw18[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw18[playerid], 1);

    Textdraw19[playerid] = CreatePlayerTextDraw(playerid, 73.000000, 200.000000, "4               Department of Justice");
    PlayerTextDrawBackgroundColor(playerid, Textdraw19[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw19[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw19[playerid], 0.259999, 1.000000);
    PlayerTextDrawColor(playerid, Textdraw19[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw19[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw19[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw19[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw19[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw19[playerid], 564.000000, 0.000000);

    Textdraw20[playerid] = CreatePlayerTextDraw(playerid, 327.000000, 201.000000, "Info");
    PlayerTextDrawAlignment(playerid, Textdraw20[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw20[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw20[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw20[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw20[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw20[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw20[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw20[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw20[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw20[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw20[playerid], 1);

    Textdraw21[playerid] = CreatePlayerTextDraw(playerid, 380.000000, 201.000000, "Pojazdy");
    PlayerTextDrawAlignment(playerid, Textdraw21[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw21[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw21[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw21[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw21[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw21[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw21[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw21[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw21[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw21[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw21[playerid], 1);

    Textdraw22[playerid] = CreatePlayerTextDraw(playerid, 433.000000, 201.000000, "Sluzba");
    PlayerTextDrawAlignment(playerid, Textdraw22[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw22[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw22[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw22[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw22[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw22[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw22[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw22[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw22[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw22[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw22[playerid], 1);

    Textdraw23[playerid] = CreatePlayerTextDraw(playerid, 486.000000, 201.000000, "Magazyn");
    PlayerTextDrawAlignment(playerid, Textdraw23[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw23[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw23[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw23[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw23[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw23[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw23[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw23[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw23[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw23[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw23[playerid], 1);

    Textdraw24[playerid] = CreatePlayerTextDraw(playerid, 539.000000, 201.000000, "On-line");
    PlayerTextDrawAlignment(playerid, Textdraw24[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw24[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw24[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw24[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw24[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw24[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw24[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw24[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw24[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw24[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw24[playerid], 1);

    Textdraw25[playerid] = CreatePlayerTextDraw(playerid, 73.000000, 213.000000, "5               Federal Bureau Of Investigation");
    PlayerTextDrawBackgroundColor(playerid, Textdraw25[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw25[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw25[playerid], 0.259999, 1.000000);
    PlayerTextDrawColor(playerid, Textdraw25[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw25[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw25[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw25[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw25[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw25[playerid], 564.000000, 0.000000);

    Textdraw26[playerid] = CreatePlayerTextDraw(playerid, 327.000000, 214.000000, "Info");
    PlayerTextDrawAlignment(playerid, Textdraw26[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw26[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw26[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw26[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw26[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw26[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw26[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw26[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw26[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw26[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw26[playerid], 1);

    Textdraw27[playerid] = CreatePlayerTextDraw(playerid, 380.000000, 214.000000, "Pojazdy");
    PlayerTextDrawAlignment(playerid, Textdraw27[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw27[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw27[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw27[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw27[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw27[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw27[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw27[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw27[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw27[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw27[playerid], 1);

    Textdraw28[playerid] = CreatePlayerTextDraw(playerid, 433.000000, 214.000000, "Sluzba");
    PlayerTextDrawAlignment(playerid, Textdraw28[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw28[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw28[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw28[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw28[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw28[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw28[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw28[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw28[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw28[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw28[playerid], 1);

    Textdraw29[playerid] = CreatePlayerTextDraw(playerid, 486.000000, 214.000000, "Magazyn");
    PlayerTextDrawAlignment(playerid, Textdraw29[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw29[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw29[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw29[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw29[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw29[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw29[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw29[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw29[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw29[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw29[playerid], 1);

    Textdraw30[playerid] = CreatePlayerTextDraw(playerid, 539.000000, 214.000000, "On-line");
    PlayerTextDrawAlignment(playerid, Textdraw30[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, Textdraw30[playerid], 255);
    PlayerTextDrawFont(playerid, Textdraw30[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Textdraw30[playerid], 0.239997, 0.799996);
    PlayerTextDrawColor(playerid, Textdraw30[playerid], -1);
    PlayerTextDrawSetOutline(playerid, Textdraw30[playerid], 1);
    PlayerTextDrawSetProportional(playerid, Textdraw30[playerid], 1);
    PlayerTextDrawUseBox(playerid, Textdraw30[playerid], 1);
    PlayerTextDrawBoxColor(playerid, Textdraw30[playerid], 85);
    PlayerTextDrawTextSize(playerid, Textdraw30[playerid], 10.000000, 47.000000);
    PlayerTextDrawSetSelectable(playerid, Textdraw30[playerid], 1);
    
    TextDrawMainInfo[playerid] = CreatePlayerTextDraw(playerid, 430.000000, 133.000000, "_");
    PlayerTextDrawBackgroundColor(playerid, TextDrawMainInfo[playerid], 255);
    PlayerTextDrawFont(playerid, TextDrawMainInfo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TextDrawMainInfo[playerid], 0.290000, 1.200000);
    PlayerTextDrawColor(playerid, TextDrawMainInfo[playerid], -1);
    PlayerTextDrawSetOutline(playerid, TextDrawMainInfo[playerid], 1);
    PlayerTextDrawSetProportional(playerid, TextDrawMainInfo[playerid], 1);
    PlayerTextDrawUseBox(playerid, TextDrawMainInfo[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TextDrawMainInfo[playerid], 68);
    PlayerTextDrawTextSize(playerid, TextDrawMainInfo[playerid], 608.000000, 10.000000);

	InfoDoor[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 350.000000, "NAZWA BUDYNKU~n~~n~~y~[Reklama budynku] ~p~[Premium]~n~~n~~w~Nacisnij [ALT] + [Spacja]");
	PlayerTextDrawAlignment(playerid, InfoDoor[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, InfoDoor[playerid], 255);
	PlayerTextDrawFont(playerid, InfoDoor[playerid], 1);
	PlayerTextDrawLetterSize(playerid, InfoDoor[playerid], 0.300000, 1.000000);
	PlayerTextDrawColor(playerid, InfoDoor[playerid], -1);
	PlayerTextDrawSetOutline(playerid, InfoDoor[playerid], 0);
	PlayerTextDrawSetProportional(playerid, InfoDoor[playerid], 1);
	PlayerTextDrawSetShadow(playerid, InfoDoor[playerid], 1);
	PlayerTextDrawUseBox(playerid, InfoDoor[playerid], 1);
	PlayerTextDrawBoxColor(playerid, InfoDoor[playerid], 85);
	PlayerTextDrawTextSize(playerid, InfoDoor[playerid], 0.000000, 180.000000);

	BoxDoorIcon[playerid] = CreatePlayerTextDraw(playerid, 215.000000, 350.000000, "~n~~n~~n~~n~~n~");
	PlayerTextDrawAlignment(playerid, BoxDoorIcon[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, BoxDoorIcon[playerid], 0);
	PlayerTextDrawFont(playerid, BoxDoorIcon[playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawLetterSize(playerid, BoxDoorIcon[playerid], 0.500000, 0.500000);
	PlayerTextDrawColor(playerid, BoxDoorIcon[playerid], -1);
	PlayerTextDrawSetOutline(playerid, BoxDoorIcon[playerid], 0);
	PlayerTextDrawSetProportional(playerid, BoxDoorIcon[playerid], 1);
	PlayerTextDrawSetShadow(playerid, BoxDoorIcon[playerid], 1);
	PlayerTextDrawTextSize(playerid, BoxDoorIcon[playerid], -30.000000, 50.000000);

	BoxDoor[playerid] = CreatePlayerTextDraw(playerid, 200.000000, 350.000000, "~n~~n~~n~~n~~n~");
	PlayerTextDrawAlignment(playerid, BoxDoor[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, BoxDoor[playerid], 255);
	PlayerTextDrawFont(playerid, BoxDoor[playerid], 1);
	PlayerTextDrawLetterSize(playerid, BoxDoor[playerid], 0.300000, 1.000000);
	PlayerTextDrawColor(playerid, BoxDoor[playerid], -1);
	PlayerTextDrawSetOutline(playerid, BoxDoor[playerid], 0);
	PlayerTextDrawSetProportional(playerid, BoxDoor[playerid], 1);
	PlayerTextDrawSetShadow(playerid, BoxDoor[playerid], 1);
	PlayerTextDrawUseBox(playerid, BoxDoor[playerid], 1);
	PlayerTextDrawBoxColor(playerid, BoxDoor[playerid], 136);
	PlayerTextDrawTextSize(playerid, BoxDoor[playerid], -30.000000, 50.000000);

	IconDoorRed[playerid] = CreatePlayerTextDraw(playerid, 419.000000, 350.000000, "~n~~n~~n~~n~~n~");
	PlayerTextDrawAlignment(playerid, IconDoorRed[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, IconDoorRed[playerid], 255);
	PlayerTextDrawFont(playerid, IconDoorRed[playerid], 1);
	PlayerTextDrawLetterSize(playerid, IconDoorRed[playerid], 0.300000, 1.000000);
	PlayerTextDrawColor(playerid, IconDoorRed[playerid], -1);
	PlayerTextDrawSetOutline(playerid, IconDoorRed[playerid], 0);
	PlayerTextDrawSetProportional(playerid, IconDoorRed[playerid], 1);
	PlayerTextDrawSetShadow(playerid, IconDoorRed[playerid], 1);
	PlayerTextDrawUseBox(playerid, IconDoorRed[playerid], 1);
	PlayerTextDrawBoxColor(playerid, IconDoorRed[playerid], 0xcf2727FF);
	PlayerTextDrawTextSize(playerid, IconDoorRed[playerid], -30.000000, 8.000000);

	IconDoorPurple[playerid] = CreatePlayerTextDraw(playerid, 419.000000, 350.000000, "~n~~n~~n~~n~~n~");
	PlayerTextDrawAlignment(playerid, IconDoorPurple[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, IconDoorPurple[playerid], 255);
	PlayerTextDrawFont(playerid, IconDoorPurple[playerid], 1);
	PlayerTextDrawLetterSize(playerid, IconDoorPurple[playerid], 0.300000, 1.000000);
	PlayerTextDrawColor(playerid, IconDoorPurple[playerid], -1);
	PlayerTextDrawSetOutline(playerid, IconDoorPurple[playerid], 0);
	PlayerTextDrawSetProportional(playerid, IconDoorPurple[playerid], 1);
	PlayerTextDrawSetShadow(playerid, IconDoorPurple[playerid], 1);
	PlayerTextDrawUseBox(playerid, IconDoorPurple[playerid], 1);
	PlayerTextDrawBoxColor(playerid, IconDoorPurple[playerid], 0x642895FF);
	PlayerTextDrawTextSize(playerid, IconDoorPurple[playerid], -30.000000, 8.000000);

	IconDoorGreen[playerid] = CreatePlayerTextDraw(playerid, 419.000000, 350.000000, "~n~~n~~n~~n~~n~");
	PlayerTextDrawAlignment(playerid, IconDoorGreen[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, IconDoorGreen[playerid], 255);
	PlayerTextDrawFont(playerid, IconDoorGreen[playerid], 1);
	PlayerTextDrawLetterSize(playerid, IconDoorGreen[playerid], 0.300000, 1.000000);
	PlayerTextDrawColor(playerid, IconDoorGreen[playerid], -1);
	PlayerTextDrawSetOutline(playerid, IconDoorGreen[playerid], 0);
	PlayerTextDrawSetProportional(playerid, IconDoorGreen[playerid], 1);
	PlayerTextDrawSetShadow(playerid, IconDoorGreen[playerid], 1);
	PlayerTextDrawUseBox(playerid, IconDoorGreen[playerid], 1);
	PlayerTextDrawBoxColor(playerid, IconDoorGreen[playerid], 0x1b8f1bFF);
	PlayerTextDrawTextSize(playerid, IconDoorGreen[playerid], -30.000000, 8.000000);

    RadioFM[playerid] = CreatePlayerTextDraw(playerid, 1.000000, 438.000000, "~y~~h~        ~>~ ~w~Aktualnie nadawany jest standardowy blok reklamowy!");
	PlayerTextDrawBackgroundColor(playerid, RadioFM[playerid], 17);
	PlayerTextDrawFont(playerid, RadioFM[playerid], 1);
	PlayerTextDrawLetterSize(playerid, RadioFM[playerid], 0.239999, 0.899999);
	PlayerTextDrawColor(playerid, RadioFM[playerid], -1027424103);
	PlayerTextDrawSetOutline(playerid, RadioFM[playerid], 1);
	PlayerTextDrawSetProportional(playerid, RadioFM[playerid], 1);
	PlayerTextDrawUseBox(playerid, RadioFM[playerid], 1);
	PlayerTextDrawBoxColor(playerid, RadioFM[playerid], 34);
	PlayerTextDrawTextSize(playerid, RadioFM[playerid], 650.000000, 0.000000);

	AdminDuty[playerid] = CreatePlayerTextDraw(playerid, 552.000000, 26.000000, "~r~~h~~h~~h~ADM ~>~ ~g~T~w~/N");
	PlayerTextDrawBackgroundColor(playerid, AdminDuty[playerid], 17);
	PlayerTextDrawFont(playerid, AdminDuty[playerid], 2);
	PlayerTextDrawLetterSize(playerid, AdminDuty[playerid], 0.289999, 0.999998);
	PlayerTextDrawColor(playerid, AdminDuty[playerid], -1027424103);
	PlayerTextDrawSetOutline(playerid, AdminDuty[playerid], 1);
	PlayerTextDrawSetProportional(playerid, AdminDuty[playerid], 1);

	Panorama1[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 337.000000, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~");
	PlayerTextDrawAlignment(playerid, Panorama1[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, Panorama1[playerid], 255);
	PlayerTextDrawFont(playerid, Panorama1[playerid], 0);
	PlayerTextDrawLetterSize(playerid, Panorama1[playerid], 1.000000, 3.300000);
	PlayerTextDrawColor(playerid, Panorama1[playerid], -1);
	PlayerTextDrawSetOutline(playerid, Panorama1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Panorama1[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Panorama1[playerid], 1);
	PlayerTextDrawUseBox(playerid, Panorama1[playerid], 1);
	PlayerTextDrawBoxColor(playerid, Panorama1[playerid], 255);
	PlayerTextDrawTextSize(playerid, Panorama1[playerid], 0.000000, 640.000000);

	Panorama2[playerid] = CreatePlayerTextDraw(playerid, 650.000000, 0.000000, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~");
	PlayerTextDrawBackgroundColor(playerid, Panorama2[playerid], 255);
	PlayerTextDrawFont(playerid, Panorama2[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Panorama2[playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, Panorama2[playerid], -1);
	PlayerTextDrawSetOutline(playerid, Panorama2[playerid], 0);
	PlayerTextDrawSetProportional(playerid, Panorama2[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Panorama2[playerid], 1);
	PlayerTextDrawUseBox(playerid, Panorama2[playerid], 1);
	PlayerTextDrawBoxColor(playerid, Panorama2[playerid], 255);
	PlayerTextDrawTextSize(playerid, Panorama2[playerid], -10.000000, 10.000000);

	BlackScreen[playerid] = CreatePlayerTextDraw(playerid, 1.000000,1.000000," ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~ ~n~");
	PlayerTextDrawUseBox(playerid, BlackScreen[playerid], 1);
	PlayerTextDrawBoxColor(playerid, BlackScreen[playerid], 0x000000ff);
	PlayerTextDrawTextSize(playerid, BlackScreen[playerid], 640.000000,0.000000);
	PlayerTextDrawAlignment(playerid, BlackScreen[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, BlackScreen[playerid], 0x000000ff);
	PlayerTextDrawFont(playerid, BlackScreen[playerid], 3);
	PlayerTextDrawLetterSize(playerid, BlackScreen[playerid], 1.000000,1.000000);
	PlayerTextDrawColor(playerid, BlackScreen[playerid], 0xffffffff);
	PlayerTextDrawSetOutline(playerid, BlackScreen[playerid], 1);
	PlayerTextDrawSetProportional(playerid, BlackScreen[playerid], 1);
	PlayerTextDrawSetShadow(playerid, BlackScreen[playerid], 1);
	
	TextPenaltyType[playerid] = CreatePlayerTextDraw(playerid, 40.000000, 241.000000, "~n~~n~~n~~n~");
    PlayerTextDrawAlignment(playerid, TextPenaltyType[playerid], 2);
    PlayerTextDrawBackgroundColor(playerid, TextPenaltyType[playerid], 255);
    PlayerTextDrawFont(playerid, TextPenaltyType[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TextPenaltyType[playerid], 0.300000, 1.000000);
    PlayerTextDrawColor(playerid, TextPenaltyType[playerid], -1);
	PlayerTextDrawSetOutline(playerid, TextPenaltyType[playerid], 1);
    PlayerTextDrawSetProportional(playerid, TextPenaltyType[playerid], 1);
    PlayerTextDrawUseBox(playerid, TextPenaltyType[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TextPenaltyType[playerid], 1721494579);
    PlayerTextDrawTextSize(playerid, TextPenaltyType[playerid], 35.000000, 6.000000);

    TextPenalty[playerid] = CreatePlayerTextDraw(playerid, 59.000000, 240.000000, "_");
    PlayerTextDrawBackgroundColor(playerid, TextPenalty[playerid], 255);
    PlayerTextDrawFont(playerid, TextPenalty[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TextPenalty[playerid], 0.300000, 1.000000);
	PlayerTextDrawColor(playerid, TextPenalty[playerid], -1);
    PlayerTextDrawSetOutline(playerid, TextPenalty[playerid], 1);
    PlayerTextDrawSetProportional(playerid, TextPenalty[playerid], 1);
    PlayerTextDrawUseBox(playerid, TextPenalty[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TextPenalty[playerid], 0);
    PlayerTextDrawTextSize(playerid, TextPenalty[playerid], 220.000000, 0.000000);

    new string_name[64];
    new year, mies, day;
    getdate(year, mies, day);

    format(string_name, sizeof(string_name), "www.in-rp.net ~w~~h~%d.%d.%d", day, mies, year);

    IRPName[playerid] = CreatePlayerTextDraw(playerid, 20.000000, 425.000000, string_name);
	PlayerTextDrawBackgroundColor(playerid, IRPName[playerid], 0x88CC54FF);
	PlayerTextDrawFont(playerid, IRPName[playerid], 3);
	PlayerTextDrawLetterSize(playerid, IRPName[playerid], 0.350000, 0.850000);
	PlayerTextDrawColor(playerid, IRPName[playerid], -1);
	PlayerTextDrawSetOutline(playerid, IRPName[playerid], 1);
	PlayerTextDrawSetProportional(playerid, IRPName[playerid], 1);
	
	TextDrawAudioError[playerid] = CreatePlayerTextDraw(playerid, 520.000000, 10.500000, "Brak klienta audio");
	PlayerTextDrawBackgroundColor(playerid, TextDrawAudioError[playerid], -16776961);
	PlayerTextDrawFont(playerid, TextDrawAudioError[playerid], 3);
	PlayerTextDrawLetterSize(playerid, TextDrawAudioError[playerid], 0.350000, 0.850000);
	PlayerTextDrawColor(playerid, TextDrawAudioError[playerid], -1);
	PlayerTextDrawSetOutline(playerid, TextDrawAudioError[playerid], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawAudioError[playerid], 1);
	
	AdminInfo[playerid] = CreatePlayerTextDraw(playerid, 580.000000, 419.000000, "_");
	PlayerTextDrawAlignment(playerid, AdminInfo[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid, AdminInfo[playerid], 255);
	PlayerTextDrawFont(playerid, AdminInfo[playerid], 1);
	PlayerTextDrawLetterSize(playerid, AdminInfo[playerid], 0.240000, 0.799999);
	PlayerTextDrawColor(playerid, AdminInfo[playerid], 1721494783);
	PlayerTextDrawSetOutline(playerid, AdminInfo[playerid], 0);
	PlayerTextDrawSetProportional(playerid, AdminInfo[playerid], 1);
	PlayerTextDrawSetShadow(playerid, AdminInfo[playerid], 1);
}

stock GetPlayerStatusInfo(playerid)
{
    new status[24], main_status[128];

    format(main_status, sizeof(main_status), "");

    if(CharacterCache[playerid][pStatus] & STATUS_UNCON)
    {
        if(!CharacterCache[playerid][pSex])     format(status, sizeof(status), "nieprzytomny");
        else                                    format(status, sizeof(status), "nieprzytomna");

        if(strlen(main_status) > 0)
        {
            strcat(main_status, ", ", sizeof(main_status));
        }
        strcat(main_status, status, sizeof(main_status));
    }

    if(CharacterCache[playerid][pStatus] & STATUS_AFK)
    {
	    new year, month, day, hour, minute;
		timestamp_to_date(CharacterCache[playerid][pAFKTime], year, month, day, hour, minute);

        format(status, sizeof(status), "AFK od %02d:%02d", hour + 1, minute);

        if(strlen(main_status) > 0)
        {
            strcat(main_status, ", ", sizeof(main_status));
        }
        strcat(main_status, status, sizeof(main_status));
    }
    
    if(CharacterCache[playerid][pStatus] & STATUS_KNEBEL)
    {
        format(status, sizeof(status), "knebel");

        if(strlen(main_status) > 0)
        {
            strcat(main_status, ", ", sizeof(main_status));
        }
        strcat(main_status, status, sizeof(main_status));
    }
    
    if(CharacterCache[playerid][pStatus] & STATUS_WOREK)
    {
        format(status, sizeof(status), "worek");

        if(strlen(main_status) > 0)
        {
            strcat(main_status, ", ", sizeof(main_status));
        }
        strcat(main_status, status, sizeof(main_status));
    }
    
    if(CharacterCache[playerid][pStatus] & STATUS_HEALTH)
    {
        if(!CharacterCache[playerid][pSex])     format(status, sizeof(status), "ranny");
        else                                    format(status, sizeof(status), "ranna");

        if(strlen(main_status) > 0)
        {
            strcat(main_status, ", ", sizeof(main_status));
        }
        strcat(main_status, status, sizeof(main_status));
    }
    
    if(CharacterCache[playerid][pStatus] & STATUS_CUFFED)
    {
        if(!CharacterCache[playerid][pSex])     format(status, sizeof(status), "skuty");
        else                                    format(status, sizeof(status), "skuta");

        if(strlen(main_status) > 0)
        {
            strcat(main_status, ", ", sizeof(main_status));
        }
        strcat(main_status, status, sizeof(main_status));
    }

    if(strlen(main_status)) format(main_status, sizeof(main_status), "(%s)", main_status);

    return main_status;
}

public UpdatePlayerStatus(playerid)
{
    // Status "AFK"
    if(CharacterCache[playerid][pAFK] <= 0 && !(CharacterCache[playerid][pStatus] & STATUS_AFK))
	{
		CharacterCache[playerid][pStatus] += STATUS_AFK;
		CharacterCache[playerid][pAFKTime] = gettime();
	}
    else if(CharacterCache[playerid][pAFK] > 0 && (CharacterCache[playerid][pStatus] & STATUS_AFK))                 CharacterCache[playerid][pStatus] -= STATUS_AFK;

    // Status "nieprzytomny"
    if(CharacterCache[playerid][pBW] && !(CharacterCache[playerid][pStatus] & STATUS_UNCON))                        CharacterCache[playerid][pStatus] += STATUS_UNCON;
    else if(!CharacterCache[playerid][pBW] && (CharacterCache[playerid][pStatus] & STATUS_UNCON))                   CharacterCache[playerid][pStatus] -= STATUS_UNCON;

	// Status "knebel"
    if(CharacterCache[playerid][pKnebel] && !(CharacterCache[playerid][pStatus] & STATUS_KNEBEL))                   CharacterCache[playerid][pStatus] += STATUS_KNEBEL;
    else if(!CharacterCache[playerid][pKnebel] && (CharacterCache[playerid][pStatus] & STATUS_KNEBEL))              CharacterCache[playerid][pStatus] -= STATUS_KNEBEL;
    
    // Status "worek"
    if(CharacterCache[playerid][pWorek] && !(CharacterCache[playerid][pStatus] & STATUS_WOREK))                     CharacterCache[playerid][pStatus] += STATUS_WOREK;
    else if(!CharacterCache[playerid][pWorek] && (CharacterCache[playerid][pStatus] & STATUS_WOREK))                CharacterCache[playerid][pStatus] -= STATUS_WOREK;

    // Status "ranny"
    if(CharacterCache[playerid][pHealth] < 45.0 && !(CharacterCache[playerid][pStatus] & STATUS_HEALTH))            CharacterCache[playerid][pStatus] += STATUS_HEALTH;
    else if(CharacterCache[playerid][pHealth] > 45.0 && (CharacterCache[playerid][pStatus] & STATUS_HEALTH))        CharacterCache[playerid][pStatus] -= STATUS_HEALTH;

	return 1;
}

public TeleportPlayerToSpawn(playerid)
{
    if(CharacterCache[playerid][pAJ])
    {
        SetPlayerPos(playerid, -207.9819, 1062.1416, 19.7422);

        SetPlayerInterior(playerid, 0);
        SetPlayerVirtualWorld(playerid, playerid + 1000);
    }
    else if(CharacterCache[playerid][pJailTime] > 0)
    {
        OnPlayerEnterDoor(playerid, CharacterCache[playerid][pJailID]);
        
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Czas Twojej odsiadki nie dobieg³ koñca.\nPowracasz do celi, w której zosta³eœ zamkniêty.", "Zamknij", "");
    }
    else if(CharacterCache[playerid][pBW])
    {
        SetPlayerPos(playerid, CharacterCache[playerid][pPos][0], CharacterCache[playerid][pPos][1], CharacterCache[playerid][pPos][2]);

        SetPlayerInterior(playerid, CharacterCache[playerid][pInt]);
        SetPlayerVirtualWorld(playerid, CharacterCache[playerid][pVW]);

        SetPlayerCameraPos(playerid, CharacterCache[playerid][pPos][0] + 3, CharacterCache[playerid][pPos][1] + 4, CharacterCache[playerid][pPos][2] + 7);
        SetPlayerCameraLookAt(playerid, CharacterCache[playerid][pPos][0], CharacterCache[playerid][pPos][1], CharacterCache[playerid][pPos][2]);

        TogglePlayerControllable(playerid, 0);
    }
    else
    {
	    SetPlayerPos(playerid, 1225.4353, 362.1379, 19.5547);
	    SetPlayerFacingAngle(playerid, 245.9456);
	    SetCameraBehindPlayer(playerid);
		        
		SetPlayerVirtualWorld(playerid, 0);
	    SetPlayerInterior(playerid, 0);
	}

    Logged[playerid] = true;
    Logged[playerid] = true;
    return 1;
}

public SearchPlayerUseModelGun(playerid, model)
{
    new query[256];
    format(query, sizeof(query), "SELECT `uid` FROM `fc_items` WHERE `owner` = '%d' AND `ownertype` = '%d' AND `used` = 1 AND `value1` = '%d' AND (`kind` = '%d' OR `kind` = '%d' OR `kind` = '%d')", CharacterCache[playerid][pUID], OWNER_PLAYER, model, TYPE_WEAPON, TYPE_INHIBITOR, TYPE_PAINT);
    mysql_check(); mysql_query(query);

    mysql_store_result();
    if(mysql_num_rows() > 0)
    {
        mysql_free_result();
        return mysql_insert_id();
    }
    else
    {
        mysql_free_result();
        return 0;
    }
}

public LoadPlayerHouse(playerid)
{
	ForeachEx(doorid, MAX_DOORS)
	{
	    MemberHome[playerid][doorid][homeDoorID] = 0;
     	MemberHome[playerid][doorid][homePerm] = 0;
		MemberHome[playerid][doorid][homeRank] = 0;
		MemberHome[playerid][doorid][homePrice] = 0;
		MemberHome[playerid][doorid][homeCharID] = 0;
	}
	
	new data[64];
	
	mysql_check();
	mysql_query_format("SELECT * FROM `fc_member_door` WHERE `char_id` = '%d'", CharacterCache[playerid][pUID]);
	
	mysql_store_result();
	
	while(mysql_fetch_row_format(data, "|"))
	{
	    new doorid;
	    sscanf(data, "p<|>d", doorid);
	    sscanf(data, "p<|>dds[32]dd",   MemberHome[playerid][doorid][homeDoorID],
	                                    MemberHome[playerid][doorid][homePerm],
										MemberHome[playerid][doorid][homeRank],
										MemberHome[playerid][doorid][homePrice],
										MemberHome[playerid][doorid][homeCharID]);
	}
	
	printf("[LOAD] Zaladowano pomyslnie mieszkania gracza %s", PlayerName2(playerid));
	mysql_free_result();
}

public LoadPlayerGroup(playerid)
{
    for(new slot = 1; slot < 4; slot++)
    {
        MemberGroup[playerid][slot][GroupID] = 0;
        MemberGroup[playerid][slot][GroupCash] = 0;
        MemberGroup[playerid][slot][GroupRank] = 0;
        MemberGroup[playerid][slot][GroupPerm] = 0;
        MemberGroup[playerid][slot][GroupSkin] = 0;
        MemberGroup[playerid][slot][GroupTime] = 0;
        MemberGroup[playerid][slot][GroupSubGroup] = 0;
    }

    new result[128], i = 1;
    
    mysql_check();
    mysql_query_format("SELECT m.group_id, IFNULL(r.name, 'Brak') AS name, IFNULL(r.permissions,0) AS permissions, IFNULL(r.skin,0) AS skin, IFNULL(r.payout,0) AS payout, m.subgroup, m.time FROM fc_member_groups m LEFT JOIN fc_groups g ON ( g.uid = m.group_id ) LEFT JOIN fc_ranks r ON ( r.uid = m.rank_uid ) WHERE m.player_uid = '%d' LIMIT 3", CharacterCache[playerid][pUID]);

    mysql_store_result();
    while(mysql_fetch_row_format(result, "|") == 1)
    {
        sscanf(result,  "p<|>ds[32]ddddd",      MemberGroup[playerid][i][GroupID],
                                                MemberGroup[playerid][i][GroupRank],
                                                MemberGroup[playerid][i][GroupPerm],
                                                MemberGroup[playerid][i][GroupSkin],
                                                MemberGroup[playerid][i][GroupCash],
                                                MemberGroup[playerid][i][GroupSubGroup],
                                                MemberGroup[playerid][i][GroupTime]);
        i++;
    }

    for(new slot = 1; slot < 4; slot++)
    {
        if(MemberGroup[playerid][slot][GroupID])        LoadGroup(MemberGroup[playerid][slot][GroupID]);
        if(MemberGroup[playerid][slot][GroupSubGroup])  LoadSubGroup(MemberGroup[playerid][slot][GroupSubGroup]);
    }

    printf("[LOAD] Zaladowano pomyslnie grupy gracza %s", PlayerName2(playerid));
    mysql_free_result();
    return 1;
}

public SaveMember(playerid, slot)
{
    new query[256];
    format(query, sizeof(query), "UPDATE `fc_member_groups` SET `subgroup` = '%d', `time` = '%d' WHERE `player_uid` = '%d' AND `group_id` = '%d'",
    MemberGroup[playerid][slot][GroupSubGroup],
    MemberGroup[playerid][slot][GroupTime],
    CharacterCache[playerid][pUID],
    MemberGroup[playerid][slot][GroupID]);

    mysql_query(query);
}

public DeleteMember(playerid, groupid)
{
    new query[256];
    format(query, sizeof(query), "DELETE FROM `fc_member_groups` WHERE `player_uid` = '%d' AND `group_id` = '%d'",
    CharacterCache[playerid][pUID],
    groupid);

    mysql_query(query);

    LoadPlayerGroup(playerid);
}

public PlayerToPlayer(Float:radi, playerid, targetid)
{
    if(Logged[playerid] && Logged[targetid])
    {
        new Float:posx, Float:posy, Float:posz;
        new Float:oldposx, Float:oldposy, Float:oldposz;
        new Float:tempposx, Float:tempposy, Float:tempposz;

        GetPlayerPos(playerid, oldposx, oldposy, oldposz);
        GetPlayerPos(targetid, posx, posy, posz);

        tempposx = (oldposx -posx);
        tempposy = (oldposy -posy);
        tempposz = (oldposz -posz);

        if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
        {
            return 1;
        }
    }
    return 0;
}

public GivePenalty(playerid, playerid2, time, type, value, reason[128])
{
    if(!Logged[playerid] || !Logged[playerid2]) return 1;
    EscapePL(reason);

    new str[512], typs[64], nadawca[128];
    if(playerid2 == -1)
        format(str, sizeof(str), "INSERT INTO `fc_penalty` VALUES (NULL, %d, %d, -1, %d, 0, %d, %d, '%s', 0, '%d');", CharacterCache[playerid][pUID], CharacterCache[playerid][pGID], time, type, gettime(), reason, value);
    else
        format(str, sizeof(str), "INSERT INTO `fc_penalty` VALUES (NULL, %d, %d, %d, %d, 0, %d, %d, '%s', 0, '%d');", CharacterCache[playerid][pUID], CharacterCache[playerid][pGID], CharacterCache[playerid2][pGID], time, type, gettime(), reason, value);

    mysql_check(); mysql_query(str);

    switch(type)
    {
        case PENALTY_KICK:  typs = "Kick";
        case PENALTY_WARN:  typs = "Ostrzezenie";
        case PENALTY_BAN:   typs = "Ban";
        case PENALTY_AJ:    typs = "Admin Jail";
        case PENALTY_BLOCK: typs = "Blokada konta";
        case PENALTY_SCORE: typs = "GameScore";
    }

    if(playerid2 != -1)
    {
        if(CharacterCache[playerid2][pAdmin] > 0 && CharacterCache[playerid2][pAdmin] < 6)
        {
        	format(nadawca, sizeof(nadawca), "Support %s", AssCode(playerid2));
        }
        else
        {
        	format(nadawca, sizeof(nadawca), "%s", CharacterCache[playerid2][pGlobalNick]);
        }
    }
    else
    {
        format(nadawca, sizeof(nadawca), "%s", "System");
    }

    format(str, sizeof(str), "~y~Nadawca:~w~ %s~n~~y~Odbiorca:~w~ %s~n~~y~Typ:~w~ %s~n~~r~~h~~h~Powod:~w~ %s", nadawca, PlayerName2(playerid), typs, reason);

	ForeachEx(i, MAX_PLAYERS)
	{
	    PlayerTextDrawSetString(i, TextPenalty[i], str);

	    PlayerTextDrawShow(i, TextPenalty[i]);
	    PlayerTextDrawShow(i, TextPenaltyType[i]);
    }
    
    PenaltyAll ++;
    DeletePenalty = 8;
    
    return 1;
}

public UpdatePlayer3DTextNick(i)
{
    new nick[64];

	if(CharacterCache[i][pAdminDuty])
	{
	    switch(CharacterCache[i][pAdmin])
	   	{
	        case 1: format(nick, sizeof(nick), "Support %s (%d)", AssCode(i), i);
	        case 2: format(nick, sizeof(nick), "Support %s (%d)", AssCode(i), i);
	        case 3: format(nick, sizeof(nick), "Support %s (%d)", AssCode(i), i);
	        case 4: format(nick, sizeof(nick), "Support %s (%d)", AssCode(i), i);
	        case 5: format(nick, sizeof(nick), "Support %s (%d)", AssCode(i), i);
	    	case 6: format(nick, sizeof(nick), "%s (%d)\n{d80000}Administrator (A1)", CharacterCache[i][pGlobalNick], i);
	    	case 7: format(nick, sizeof(nick), "%s (%d)\n{d80000}Administrator (A2)", CharacterCache[i][pGlobalNick], i);
	    	case 8: format(nick, sizeof(nick), "%s (%d)\n{d80000}Administrator (A3)", CharacterCache[i][pGlobalNick], i);
	    	case 9: format(nick, sizeof(nick), "%s (%d)\n{d80000}Administrator (GA)", CharacterCache[i][pGlobalNick], i);
		}
	}
	else
	{
	    if(CharacterCache[i][pStatus])
	   	{
	        if(IsPlayerOfficalGroup(i))
	        {
	            format(nick, sizeof(nick), "%s (%d)\n%s\n%s", PlayerName2(i), i, GetPlayerStatusInfo(i), getPlayerOfficalGroup(i));
	        }
	        else
	       	{
	        	format(nick, sizeof(nick), "%s (%d)\n%s", PlayerName2(i), i, GetPlayerStatusInfo(i));
			}
		}
		else
	   	{
	     	if(IsPlayerOfficalGroup(i))
			{
	        	format(nick, sizeof(nick), "%s (%d)\n%s", PlayerName2(i), i, getPlayerOfficalGroup(i));
	        }
	        else
	       	{
	        	format(nick, sizeof(nick), "%s (%d)", PlayerName2(i), i);
	    	}
		}
	}

    Update3DTextLabelText(Text3D:NameTags[i], CharacterCache[i][pNickColor], nick);
}

public LoadPlayerVehicles(playerid)
{
	ForeachEx(i, MAX_VEHICLES)
	{
	    if(VehicleInfo[i][vGameID] && VehicleInfo[i][vOwnerType] == OWNER_PLAYER && VehicleInfo[i][vOwner] == CharacterCache[playerid][pUID])
	    {
     		CharacterCache[playerid][pCarSpawned] ++;
	    }
	}
}

stock Infobox(playerid, time, message[])
{
    EscapePL(message);

    PlayerTextDrawSetString(playerid, TextDrawMainInfo[playerid], message);
    PlayerTextDrawShow(playerid, TextDrawMainInfo[playerid]);

    CharacterCache[playerid][pShowInfoText] = time;
    return 1;
}

stock ShowPlayerStats(i, playerid)
{
    new string[2048];

    format(string, sizeof(string), "{88CC54}1. Podstawowe informacje");
    format(string, sizeof(string), "%s\n\tIdentyfikator:\t\t%d", string, CharacterCache[playerid][pUID]);
    format(string, sizeof(string), "%s\n\tImiê nazwisko:\t\t%s", string, PlayerName2(playerid));
    format(string, sizeof(string), "%s\n\tKonto globalne:\t%s (GID: %d)", string, CharacterCache[playerid][pGlobalNick], CharacterCache[playerid][pGID]);
    format(string, sizeof(string), "%s\n\tPorftel:\t\t\t$ %d", string, CharacterCache[playerid][pCash]);
    format(string, sizeof(string), "%s\n\tCzas gry:\t\t%dh, %dmin", string, CharacterCache[playerid][pHours], CharacterCache[playerid][pMinutes]);
    format(string, sizeof(string), "%s\n\tP³eæ:\t\t\t%s", string, GetSexName(CharacterCache[playerid][pSex]));
    format(string, sizeof(string), "%s\n\tWiek:\t\t\t%d", string, CharacterCache[playerid][pAge]);
    format(string, sizeof(string), "%s\n\tZdrowie:\t\t%0.1f", string, CharacterCache[playerid][pHealth]);
    format(string, sizeof(string), "%s\n\tUbranie:\t\t%d", string, CharacterCache[playerid][pSkin]);
    format(string, sizeof(string), "%s\n{88CC54}2. Bankowoœæ", string);
    format(string, sizeof(string), "%s\n\tKonto bankowe:\t$ %d", string, CharacterCache[playerid][pBankCash]);
    format(string, sizeof(string), "%s\n\tKonto kredytowe:\t$ %d", string, 0);
    format(string, sizeof(string), "%s\n\tKonto ubez.:\t\t$ %d", string, 0);
    format(string, sizeof(string), "%s\n\tNumer konta:\t\t%d", string, CharacterCache[playerid][pBankNumber]);
    format(string, sizeof(string), "%s\n{88CC54}3. Pozosta³e informacje", string);
    format(string, sizeof(string), "%s\n\tVirtual World:\t\t%d", string, GetPlayerVirtualWorld(playerid));
    format(string, sizeof(string), "%s\n\tDrzwi:\t\t\t%d", string, PlayerDoor[playerid]);
    format(string, sizeof(string), "%s\n\tStrefa:\t\t\t%d", string, GetPlayerArea(playerid));
    format(string, sizeof(string), "%s\n\tAdmin Jail:\t\t%d", string, (CharacterCache[playerid][pAJ]/60));
    format(string, sizeof(string), "%s\n\tBrutally Wounded:\t%d", string, (CharacterCache[playerid][pBW]/60));
	format(string, sizeof(string), "%s\n\tAreszt:\t\t\t%dmin", string, CharacterCache[playerid][pJailTime]);
	format(string, sizeof(string), "%s\n\tPunkty karne:\t\t%d/24", string, CharacterCache[playerid][pPenaltyPoints]);

    ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_LIST, " Statystyki postaci", string, "Zamknij", "");
    return 1;
}

stock GetSexName(sex)
{
    new name[32];
    if(!sex) name = "Mê¿czyzna";
    else name = "Kobieta";
    return name;
}

public SavePlayerStats(playerid, what)
{
    if(!Logged[playerid]) return 1;
    mysql_check();
    
    if(what == SAVE_PLAYER_BASIC)
    {
        mysql_query_format("UPDATE `fc_characters` SET `age` = '%d', `sex` = '%d', `cash` = '%d', `hours` = '%d', `minutes` = '%d', `skin` = '%d', `bw` = '%d', `aj` = '%d', `health` = '%f', `job` = '%d', `block` = '%d', `penalty_points` = '%d', `food` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
        CharacterCache[playerid][pAge],
        CharacterCache[playerid][pSex],
        CharacterCache[playerid][pCash],
        CharacterCache[playerid][pHours],
        CharacterCache[playerid][pMinutes],
        CharacterCache[playerid][pSkin],
        CharacterCache[playerid][pBW],
        CharacterCache[playerid][pAJ],
        CharacterCache[playerid][pHealth],
        CharacterCache[playerid][pJob],
        CharacterCache[playerid][pBlock],
        CharacterCache[playerid][pPenaltyPoints],
        CharacterCache[playerid][pFood],
        CharacterCache[playerid][pUID]);
    }

    if(what == SAVE_PLAYER_SETTING)
    {
        mysql_query_format("UPDATE `fc_characters` SET `tog` = '%d', `option` = '%d', `editor` = '%d', `document` = '%d', `insurance_cash` = '%d', `phone` = '%d', `last_skin` = '%d', `drugs_type` = '%d', `drugs_time` = '%d', `sell_drug` = '%d', `jail_time` = '%d', `jail_id` = '%d', `permit_time` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
        CharacterCache[playerid][pTog],
        CharacterCache[playerid][pOption],
        CharacterCache[playerid][pEditor],
        CharacterCache[playerid][pDocument],
        CharacterCache[playerid][pInsurance],
        CharacterCache[playerid][pPhone],
        CharacterCache[playerid][pLastSkin],
        CharacterCache[playerid][pDrugs],
		CharacterCache[playerid][pDrugsTime],
		CharacterCache[playerid][pSellDrug],
		CharacterCache[playerid][pJailTime],
		CharacterCache[playerid][pJailID],
		CharacterCache[playerid][pPermit],
        CharacterCache[playerid][pUID]);
    }

    if(what == SAVE_PLAYER_POS)
    {
        mysql_query_format("UPDATE `fc_characters` SET `pos_x` = '%f', `pos_y` = '%f', `pos_z` = '%f', `vw` = '%d', `int` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
        CharacterCache[playerid][pPos][0],
        CharacterCache[playerid][pPos][1],
        CharacterCache[playerid][pPos][2],
        CharacterCache[playerid][pVW],
        CharacterCache[playerid][pInt],
        CharacterCache[playerid][pUID]);
    }

    if(what == SAVE_PLAYER_GLOBAL)
    {
        mysql_query_format("UPDATE `ipb_members` SET `score` = '%d', `admin` = '%d' WHERE `member_id` = '%d' LIMIT 1",
        CharacterCache[playerid][pGlobalScore],
        CharacterCache[playerid][pAdmin],
        CharacterCache[playerid][pGID]);
    }

    return 1;
}
