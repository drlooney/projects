/*

  	Autorem zawartoœci tego pliku jest Filip Sosnowski.
    Wszelkie prawa zastrze¿one.

*/

#include "/includes/a_samp.inc"
#include "/includes/a_mysql.inc"
//#include "/includes/FCNPC.inc"
#include "/includes/lookup.inc"
#include "/includes/md5.inc"
#include "/includes/progress.inc"
#include "/includes/sscanf2.inc"
#include "/includes/streamer.inc"

#include "\includes\YSI\y_bit.inc"
#include "\includes\YSI\y_colours.inc"
#include "\includes\YSI\y_va.inc"

#include "/includes/zcmd.inc"

#include "/modules/definitions.inc"
#include "/modules/header.inc"
#include "/modules/core.inc"
#include "/modules/config.inc"

#include "/modules/login.inc"

#include "/modules/admin.inc"
#include "/modules/areas.inc"
#include "/modules/doors.inc"
#include "/modules/groups.inc"
#include "/modules/items.inc"
//#include "/modules/npc.inc"
#include "/modules/objects.inc"
#include "/modules/offers.inc"
#include "/modules/other.inc"
#include "/modules/player.inc"
#include "/modules/vehicles.inc"

#include "/modules/dialog.inc"
#include "/modules/load.inc"
#include "/modules/timers.inc"

#include "/modules/cmd_admin.inc"
#include "/modules/cmd_group.inc"
#include "/modules/cmd_player.inc"

main()
{
    print("----------------------------------");
    printf("|		%s	|", DEF_NAME);
    print("----------------------------------");
}

public OnGameModeInit()
{
    mysql_debug(1);
    mysql_connect(SQL_HOST, SQL_USER, SQL_DB, SQL_PASS);

    if(mysql_ping())
    {
		if(gettime() >= 1498855600)
		{
		    SetGameModeText("LICENSE EXPIRED");

		    SendRconCommand("password licensetoexpiredworked");
		    SendRconCommand("mapname LICENSE EXPIRED");
		    SendRconCommand("hostname (LICENSE) Licencja oprogramowania wygas³a!");

			return 1;
		}

        print("----------------------------------------------");
        print("     Po³¹czono z serwerem MySQL poprawnie     ");
        print("----------------------------------------------");

		// Nazwy
        mysql_set_charset("utf-8");
        SetGameModeText("RP v0.1c");

		// Ustawienia
		ShowNameTags(0);
        ShowPlayerMarkers(0);
        AllowInteriorWeapons(0);
        EnableStuntBonusForAll(0);
        DisableInteriorEnterExits();
        ManualVehicleEngineAndLights();

        // Timery
        SetTimer("TimerSecond", 1000, 1);
        SetTimer("TimerMinute", (1000 * 60), 1);

        //Logowanie graczy
        mysql_check();
		mysql_query_format("UPDATE `fc_characters` SET `logged` = '0', `in_game` = '%d'", gettime());

        // Ustawienia serwera
        mysql_check();
        mysql_query("UPDATE `fc_setting` SET `status` = 1 AND `password` = 0");

        new godzina, minuta;
        gettime(godzina, minuta);
        SetWorldTime(godzina + 1);

        ForeachEx(i, MAX_PLAYERS)
        {
            StatusTag[i] = CreateDynamic3DTextLabel(" ", 0x326FA5FF, 0.0, 0.0, 0.4, 25.0, i, INVALID_VEHICLE_ID, 1);

            CharacterCache[i][pDescTag] = Create3DTextLabel(" ", 0x7290C4FF, 0.0, 0.0, -0.6, 5.0, 1);
            NameTags[i] = Create3DTextLabel(" ", 0xFFFFFFBB, 0.0, 0.0, 0.2, 15.0, 0, 1);
        }

        ForeachEx(veh, MAX_VEHICLES)
        {
            VehicleTag[veh] = CreateDynamic3DTextLabel(" ", 0x326FA5FF, 0.0, 0.0, 1.1, 25.0, INVALID_PLAYER_ID, veh, 1);
        }

        Icons = TextDrawCreate(623.000000, 425.000000, " ");
		TextDrawUseBox(Icons, 1);
		TextDrawBoxColor(Icons, 0x00000000);
		TextDrawTextSize(Icons, 626.000000, 0.000000);
		TextDrawAlignment(Icons, 3);
		TextDrawBackgroundColor(Icons, 0x000000ff);
		TextDrawFont(Icons, 3);
		TextDrawLetterSize(Icons, 0.299999, 0.899999);
		TextDrawColor(Icons, 0xffffffff);
		TextDrawSetOutline(Icons, 1);
		TextDrawSetProportional(Icons, 1);
		TextDrawSetShadow(Icons, 1);
		TextDrawShowForAll(Icons);

        LoadVehicles();

        LoadGroups();
        LoadItems();

        LoadAreas();
        LoadDoors();

        LoadObjects();
        LoadTexture();
		LoadMaterialText();

		LoadAttachedItems();

		LoadSensors();

        LoadBusStop();
        LoadSettings();

        LoadCorps();
        //LoadGangs();

        LoadBurgers();
        LoadPlants();
    }
    else
    {
        SetGameModeText("B³¹d MYSQL");
    }

    AddPlayerClass(0, -1979.6364, 883.7577, 45.2031, 3.8626, 0, 0, 0, 0, 0, 0);
    return 1;
}

public OnGameModeExit()
{
	mysql_query("UPDATE `fc_setting` SET `status` = 0 AND `password` = 0");

    mysql_close();
    print("[dev] koñczê dzia³anie gamemode...");
    return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    ForeachEx(i, 40) SendClientMessage(playerid, -1, " ");
    TogglePlayerSpectating(playerid, true);

    SetPlayerVirtualWorld(playerid, 255);
    SetPlayerColor(playerid, 0x000000FF);

    CreatePlayerTDGroups(playerid);

    PlayerTextDrawShow(playerid, Panorama1[playerid]);
    PlayerTextDrawShow(playerid, Panorama2[playerid]);

    new string[256];
    format(string, sizeof(string), "{FFFFFF}Witamy na polskim serwerze roleplay {88CC54}"DEF_NAME"{FFFFFF}.\n{FFFFFF}Zalogowaæ siê mo¿esz przy u¿yciu nazwy swojej postaci.");
    format(string, sizeof(string), "%s\n\n{FFFFFF}Wpisz has³o, aby do³¹czyæ do najbardziej oczekiwanego projektu RolePlay.", string);

    ShowPlayerDialog(playerid, D_LOGIN_GLOBAL, DIALOG_STYLE_PASSWORD, " Logowanie do platformy", string, "Zaloguj", "Zamknij");
    return 1;
}

public OnPlayerConnect(playerid)
{
    ClearCache(playerid);

    SetPlayerColor(playerid, 0x000000FF);
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    if(CharacterCache[playerid][pUID])
    {
        mysql_check();
		mysql_query_format("UPDATE `fc_characters` SET `last_online` = '%d', `logged` = '0', `in_game` = '%d' WHERE `player_uid` = '%d'", gettime(), gettime(), CharacterCache[playerid][pUID]);

        mysql_check();
		mysql_query_format("INSERT INTO `fc_logs` SET `ip` = '%s', `char_id` = '%d', `date` = '%d', `ingame` = '%d', `afk_second` = '%d'", CharacterCache[playerid][pIP], CharacterCache[playerid][pUID], gettime(), CharacterOnline[playerid], PlayerAFK[playerid]);

        if(CharacterCache[playerid][pWeaponID])
        {
            new itemid = GetItemID(CharacterCache[playerid][pWeaponUID]);

            mysql_check();
			mysql_query_format("UPDATE `fc_items` SET `value2` = '%d', `used` = 0 WHERE `uid` = '%d' LIMIT 1", CharacterCache[playerid][pWeaponAmmo], CharacterCache[playerid][pWeaponUID]);

            ResetPlayerWeapons(playerid);

            ItemInfo[itemid][iUsed] = 0;
            ItemInfo[itemid][iValue2] = CharacterCache[playerid][pWeaponAmmo];

            CharacterCache[playerid][pWeaponUID]    = 0;
            CharacterCache[playerid][pWeaponID]     = 0;
            CharacterCache[playerid][pWeaponAmmo]   = 0;
            CharacterCache[playerid][pGetWeapon]    = false;
        }

        mysql_check();
		mysql_query_format("UPDATE `fc_items` SET `used` = 0 WHERE `ownertype` = '%d' AND `owner` = '%d'", OWNER_PLAYER, CharacterCache[playerid][pUID]);

        UnloadPlayerItems(playerid);

		if(CharacterCache[playerid][pPackage])
		{
		    mysql_check();
		    mysql_query_format("UPDATE `fc_orders` SET `driver` = 0 WHERE `order_id` = '%d'", CharacterCache[playerid][pPackageID]);

			CharacterCache[playerid][pPackage] = false;
			CharacterCache[playerid][pPackageID] = 0;
			CharacterCache[playerid][pPackageDoor] = 0;
			CharacterCache[playerid][pPackageTime] = 0;
  		}

  		if(GetPlayerSkin(playerid) > 0 && GetPlayerSkin(playerid) < 300)
  		{
  		    CharacterCache[playerid][pLastSkin] = GetPlayerSkin(playerid);
  		}

  		if(CharacterCache[playerid][pTaxiVeh] != INVALID_VEHICLE_ID)
	 	{
	  		new driverid = GetVehicleDriver(CharacterCache[playerid][pTaxiVeh]), price = CharacterCache[playerid][pTaxiPay];

			if(price > 0)
	  		{
	  			new business_cash = floatround(0.90 * price),
					playercash = floatround(0.10 * price);

	    		GivePlayerCash(playerid, -price);
	      		GivePlayerCash(driverid, playercash);

				new group_id = CharacterCache[driverid][pTaxiGroup];
	   			GroupData[group_id][Cash] += business_cash;

				SaveGroup(group_id);

				new string[128];
				format(string, sizeof(string), "Otrzyma³eœ premie w wysokoœci $%d!\nNa konto grupy dodano: $%d", playercash, business_cash);

				ShowPlayerDialog(driverid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}

			CharacterCache[driverid][pTaxiPassenger] = INVALID_PLAYER_ID;
		}

  		if(CharacterCache[playerid][pPackage])
  		{
  		    mysql_check();
			mysql_query_format("UPDATE `fc_orders` SET `drive` = 0 WHERE `order_uid` = '%d'", CharacterCache[playerid][pPackageID]);

			CharacterCache[playerid][pPackage] = false;
			CharacterCache[playerid][pPackageID] = 0;
			CharacterCache[playerid][pPackageDoor] = 0;
			CharacterCache[playerid][pPackageTime] = 0;
  		}

        SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
        SavePlayerStats(playerid, SAVE_PLAYER_SETTING);
        SavePlayerStats(playerid, SAVE_PLAYER_POS);
        SavePlayerStats(playerid, SAVE_PLAYER_GLOBAL);
    }

    ClearCache(playerid);
    return 1;
}

public OnPlayerSpawn(playerid)
{
	TeleportPlayerToSpawn(playerid);
    return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
    UpdatePlayer3DTextNick(playerid);
    UpdatePlayer3DTextNick(forplayerid);
    return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
    UpdatePlayer3DTextNick(playerid);
    UpdatePlayer3DTextNick(forplayerid);
    return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
    return 1;
}

public OnPlayerUpdate(playerid)
{
    CharacterCache[playerid][pAFK] = 5;
    
    // Przyczepienie obiektu broni
	if(CharacterCache[playerid][pWeaponUID])
	{
	    new weapon = GetPlayerWeapon(playerid);
		if(weapon == 0)
		{
		    new weapon_id = CharacterCache[playerid][pWeaponID];
			if(!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON))
			{
			    new weapon_type = GetWeaponType(weapon_id);
			    switch(weapon_type)
			    {
			        case WEAPON_TYPE_LIGHT:
			        {
			            SetPlayerAttachedObject(playerid, SLOT_WEAPON, WeaponModel[weapon_id], 8, 0.0, -0.1, 0.15, -100.0, 0.0, 0.0);
			        }
			        case WEAPON_TYPE_MELEE:
			        {
			            SetPlayerAttachedObject(playerid, SLOT_WEAPON, WeaponModel[weapon_id], 7, 0.0, 0.0, -0.18, 100.0, 45.0, 0.0);
			        }
			        case WEAPON_TYPE_HEAVY:
			        {
			            SetPlayerAttachedObject(playerid, SLOT_WEAPON, WeaponModel[weapon_id], 1, 0.2, -0.125, -0.1, 0.0, 25.0, 180.0);
			        }
			    }
			}
		}
		else
		{
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON))
			{
				RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
			}
		}
	}
	
	if(CharacterCache[playerid][pMove3DText])
	{
		new keysa, uda, lra, label_id = CharacterCache[playerid][pMove3DText];
		GetPlayerKeys(playerid, keysa, uda, lra);
		
		if(uda < 0) // Strza³ka w góre
		{
			if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_UDRL)
			{
				LabelInfo[label_id][labelPos][2] += 0.1;

				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0] + 3, LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}
			else if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_FB)
			{
			    LabelInfo[label_id][labelPos][0] += 0.1;

   				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2] + 3);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}

			DestroyDynamic3DTextLabel(LabelInfo[label_id][label3D]);
			
			EscapeLabel(LabelInfo[label_id][labelText]);
			
			LabelInfo[label_id][label3D] = CreateDynamic3DTextLabel(WordWrap(LabelInfo[label_id][labelText], 7), 0xFFFFFFFF, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2], LabelInfo[label_id][labelRange], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LabelInfo[label_id][labelVw], LabelInfo[label_id][labelInt], -1, 80.0);

			Streamer_Update(playerid);
		}
		else if(uda > 0) // Strza³ka w dó³
		{
			if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_UDRL)
			{
				LabelInfo[label_id][labelPos][2] -= 0.1;

				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0] + 3, LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}
			else if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_FB)
			{
			    LabelInfo[label_id][labelPos][0] -= 0.1;

   				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2] + 3);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}

			DestroyDynamic3DTextLabel(LabelInfo[label_id][label3D]);
			
			EscapeLabel(LabelInfo[label_id][labelText]);
			
			LabelInfo[label_id][label3D] = CreateDynamic3DTextLabel(WordWrap(LabelInfo[label_id][labelText], 7), 0xFFFFFFFF, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2], LabelInfo[label_id][labelRange], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LabelInfo[label_id][labelVw], LabelInfo[label_id][labelInt], -1, 80.0);

			Streamer_Update(playerid);
		}
		else if(lra < 0) // Strza³ka w prawo
		{
			if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_UDRL)
			{
				LabelInfo[label_id][labelPos][1] -= 0.1;

				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0] + 3, LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}
			else if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_FB)
			{
			    LabelInfo[label_id][labelPos][1] += 0.1;

   				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2] + 3);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}

			DestroyDynamic3DTextLabel(LabelInfo[label_id][label3D]);
			
			EscapeLabel(LabelInfo[label_id][labelText]);
			
			LabelInfo[label_id][label3D] = CreateDynamic3DTextLabel(WordWrap(LabelInfo[label_id][labelText], 7), 0xFFFFFFFF, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2], LabelInfo[label_id][labelRange], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LabelInfo[label_id][labelVw], LabelInfo[label_id][labelInt], -1, 80.0);

			Streamer_Update(playerid);
		}
		else if(lra > 0) // Strza³ka w lewo
		{
			if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_UDRL)
			{
				LabelInfo[label_id][labelPos][1] += 0.1;

				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0] + 3, LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}
			else if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_FB)
			{
			    LabelInfo[label_id][labelPos][1] -= 0.1;

   				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2] + 3);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}

			DestroyDynamic3DTextLabel(LabelInfo[label_id][label3D]);
			
			EscapeLabel(LabelInfo[label_id][labelText]);
			
			LabelInfo[label_id][label3D] = CreateDynamic3DTextLabel(WordWrap(LabelInfo[label_id][labelText], 7), 0xFFFFFFFF, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2], LabelInfo[label_id][labelRange], INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LabelInfo[label_id][labelVw], LabelInfo[label_id][labelInt], -1, 80.0);

			Streamer_Update(playerid);
		}
 	}
 	
 	if(CharacterCache[playerid][pBusStatus] == BUS_SEARCH)
 	{
 		new keysa, uda, lra;
		GetPlayerKeys(playerid, keysa, uda, lra);
		
		if(uda < 0) // Strza³ka w góre
		{
		    CharacterCache[playerid][pBusPos][1] += 5.0;
		    
			SetPlayerCameraPos(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1] - 2, CharacterCache[playerid][pBusPos][2] + 50);
			SetPlayerCameraLookAt(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1], CharacterCache[playerid][pBusPos][2]);
		}
		else if(uda > 0) // Strza³ka w dó³
		{
		    CharacterCache[playerid][pBusPos][1] -= 5.0;
		    
			SetPlayerCameraPos(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1] - 2, CharacterCache[playerid][pBusPos][2] + 50);
			SetPlayerCameraLookAt(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1], CharacterCache[playerid][pBusPos][2]);
		}
		else if(lra < 0) // Strza³ka w prawo
		{
		    CharacterCache[playerid][pBusPos][0] -= 5.0;
		    
			SetPlayerCameraPos(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1] - 2, CharacterCache[playerid][pBusPos][2] + 50);
			SetPlayerCameraLookAt(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1], CharacterCache[playerid][pBusPos][2]);
		}
		else if(lra > 0) // Strza³ka w lewo
		{
		    CharacterCache[playerid][pBusPos][0] += 5.0;
		    
			SetPlayerCameraPos(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1] - 2, CharacterCache[playerid][pBusPos][2] + 50);
			SetPlayerCameraLookAt(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1], CharacterCache[playerid][pBusPos][2]);
		}
 	}
 	
 	new string[128];
 	ForeachEx(i, MAX_SENSORS)
 	{
		if(IsPlayerInRangeOfPoint(playerid, 50, SensorInfo[i][sensorPos][0], SensorInfo[i][sensorPos][1], SensorInfo[i][sensorPos][2]))
		{
		    if(IsPlayerInAnyVehicle(playerid))
		    {
		        new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
		        new groupid = GetGroupKind(GROUP_BORDER);

				if(VehicleInfo[vehid][vOwnerType] == OWNER_GROUP && VehicleInfo[vehid][vOwner] != GroupData[groupid][UID])
				{
					if(!VehicleInfo[vehid][vSensor])
					{
				        format(string, sizeof(string), "[CZUJNIK] Czujnik %s wykry³ pojazd w okolicy. (( %s ))", SensorInfo[i][sensorName], GetVehicleModelName(VehicleInfo[vehid][vModel]));
						SendMessageToGroup(GroupData[groupid][UID], MakeColorLighter(GroupData[groupid][Chat][0], GroupData[groupid][Chat][1], GroupData[groupid][Chat][2], 30), string);

						VehicleInfo[vehid][vSensor] = 90;
					}
				}
		    }
		    else
		    {
		        if(!IsPlayerKindGroup(playerid, GROUP_BORDER))
		        {
			 	    if(!CharacterCache[playerid][pSensor])
			 	    {
			 	        new groupid = GetGroupKind(GROUP_BORDER);
			 	        
			 	        format(string, sizeof(string), "[CZUJNIK] Czujnik %s wykry³ ruch w okolicy. (( %s ))", SensorInfo[i][sensorName], PlayerName2(playerid));
						SendMessageToGroup(GroupData[groupid][UID], MakeColorLighter(GroupData[groupid][Chat][0], GroupData[groupid][Chat][1], GroupData[groupid][Chat][2], 30), string);

						CharacterCache[playerid][pSensor] = 90;
			 	    }
		 	    }
	 	    }
 	    }
 	}
 	
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new vehid = GetPlayerVehicleID(playerid);

        if(newkeys == KEY_HANDBRAKE + KEY_FIRE)
        {
            cmd_silnik(playerid, "");
            return 1;
        }

        // Zapalanie œwiate³
        if(newkeys & 1)
        {
            if(GetVehicleLightsStatus(vehid) == 1)
            {
                ChangeVehicleLightsStatus(vehid, false);
            }
            else
            {
                ChangeVehicleLightsStatus(vehid, true);
            }
        }
    }

    if(newkeys == KEY_SPRINT)
	{
		if(CharacterCache[playerid][pMove3DText])
	    {
	        new label_id = CharacterCache[playerid][pMove3DText];
	        if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_UDRL)
	        {
	            CharacterCache[playerid][pMove3DTextPhase] = PHASE_FB;

 				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2] + 3);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}
	        else if(CharacterCache[playerid][pMove3DTextPhase] == PHASE_FB)
	        {
	            CharacterCache[playerid][pMove3DTextPhase] = PHASE_UDRL;

				SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0] + 3, LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
				SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
			}
	    }
	}
	
	if(newkeys == KEY_SECONDARY_ATTACK)
	{
		if(CharacterCache[playerid][pMove3DText])
	    {
			new label_id = CharacterCache[playerid][pMove3DText];
			SaveLabel(label_id);

			CharacterCache[playerid][pMove3DText] = INVALID_3DTEXT_ID;
			CharacterCache[playerid][pMove3DTextPhase] = PHASE_NONE;

			TogglePlayerControllable(playerid, 1);
			SetCameraBehindPlayer(playerid);
	    }
	    
	    if(CharacterCache[playerid][pBusStatus] == BUS_TARGET)
	    {
	        SetCameraBehindPlayer(playerid);
            TogglePlayerControllable(playerid, 0);
            
	        new busid = CharacterCache[playerid][pBusTarget];
	        new string[128];
	        new Float:Pos[3];
	        GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
            
            CharacterCache[playerid][pBusStatus] = BUS_GOTO;
            CharacterCache[playerid][pBusTime] = 12;
            
            format(string, sizeof(string), "wsiad³ do autobusu jad¹cego w kierunku przystanku %s.", BusStop[busid][bName]);
			cmd_me(playerid, string);
			
			InterpolateCameraPos(playerid, Pos[0], Pos[1] - 2, Pos[2] + 100, BusStop[busid][bPos][0], BusStop[busid][bPos][1] - 2, BusStop[busid][bPos][2] + 25, 12000, CAMERA_MOVE);
			InterpolateCameraLookAt(playerid, Pos[0], Pos[1], Pos[2], BusStop[busid][bPos][0], BusStop[busid][bPos][1], BusStop[busid][bPos][2], 12000, CAMERA_MOVE);
	    }
	    
	    if(CharacterCache[playerid][pBusStatus] == BUS_SEARCH)
	    {
	        new busid = GetClosestBus(playerid, 5000.0);
	        
	        if(busid)
	        {
	            CharacterCache[playerid][pBusTarget] = busid;
	            CharacterCache[playerid][pBusStatus] = BUS_TARGET;
	            
		        InterpolateCameraPos(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1] - 2, CharacterCache[playerid][pBusPos][2] + 50, BusStop[busid][bPos][0], BusStop[busid][bPos][1] - 2, BusStop[busid][bPos][2] + 15, 1500, CAMERA_MOVE);
				InterpolateCameraLookAt(playerid, CharacterCache[playerid][pBusPos][0], CharacterCache[playerid][pBusPos][1], CharacterCache[playerid][pBusPos][2], BusStop[busid][bPos][0], BusStop[busid][bPos][1], BusStop[busid][bPos][2], 1500, CAMERA_MOVE);

				new string[256];
				format(string, sizeof(string), "~w~~h~Przystanek: ~g~~h~%s~n~~w~~h~Koszt biletu: ~g~~h~Darmowy~n~~w~~h~Czas podrozy: ~g~~h~12s.~n~~n~Nacisnij ~g~~h~RETURN~w~~h~ by potwierdzic lub ~g~~h~LSHIFT~w~~h~ by anulowac wybor.", BusStop[busid][bName]);

				Infobox(playerid, 10, string);
			}
			else
			{
			    GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~r~Nie ma innego przystanku blizej tej lokalizacji.", 3000, 4);
			}
	    }
	}
	
	if(newkeys & KEY_JUMP)
	{
	    if(CharacterCache[playerid][pBusStatus] == BUS_SEARCH)
	    {
	        SetCameraBehindPlayer(playerid);
            TogglePlayerControllable(playerid, 1);
            
            CharacterCache[playerid][pBusStatus] = BUS_NONE;
            CharacterCache[playerid][pBusTarget] = 0;
	    }
	    if(CharacterCache[playerid][pBusStatus] == BUS_TARGET)
	    {
	        new busid = CharacterCache[playerid][pBusTarget];
	        
	        CharacterCache[playerid][pBusStatus] = BUS_SEARCH;
	        CharacterCache[playerid][pBusTarget] = 0;

		    CharacterCache[playerid][pBusPos][0] = BusStop[busid][bPos][0];
			CharacterCache[playerid][pBusPos][1] = BusStop[busid][bPos][1];
			CharacterCache[playerid][pBusPos][2] = BusStop[busid][bPos][2];

		    InterpolateCameraPos(playerid, BusStop[busid][bPos][0], BusStop[busid][bPos][1] - 2, BusStop[busid][bPos][2] + 15, BusStop[busid][bPos][0], BusStop[busid][bPos][1] - 2, BusStop[busid][bPos][2] + 50, 1500, CAMERA_MOVE);
			InterpolateCameraLookAt(playerid, BusStop[busid][bPos][0], BusStop[busid][bPos][1], BusStop[busid][bPos][2], BusStop[busid][bPos][0], BusStop[busid][bPos][1], BusStop[busid][bPos][2], 1500, CAMERA_MOVE);
  		}
	}
	
	if(newkeys & KEY_FIRE)
	{
	    if(CharacterCache[playerid][pFished] && CharacterCache[playerid][pFishTaking])
	    {
	        new random_value = random(60), string[64], name[32];
			switch(random_value)
	        {
	            case 21:
	            {
	                GameTextForPlayer(playerid, "~w~Zylka zostala ~r~zerwana", 5000, 3);
	                CharacterCache[playerid][pFishTaking] = false;
	            }
	            case 14:
	            {
	                if(CharacterCache[playerid][pWater] == WATER_SWEET)
	                {
						new fish_id = random(sizeof(FishSweet));
						new kg = random(6);

		                format(string, sizeof(string), "~w~Zlowiles rybe ~g~%s (%d kg)", FishSweet[fish_id][fName], kg + 1);
		                GameTextForPlayer(playerid, string, 5000, 3);

		                CharacterCache[playerid][pFishTaking] = false;
		                
		                format(name, sizeof(name), "%s (%d kg)", FishSweet[fish_id][fName], kg + 1);
		                CreatePlayerItem(playerid, name, TYPE_FISH, FishSweet[fish_id][fValue1], WATER_SWEET, 1);
	                }
	                else
	                {
						new fish_id = random(sizeof(FishSalt));
						new kg = random(6);

		                format(string, sizeof(string), "~w~Zlowiles rybe ~g~%s (%d kg)", FishSalt[fish_id][fName], kg + 1);
		                GameTextForPlayer(playerid, string, 5000, 3);

		                CharacterCache[playerid][pFishTaking] = false;
		                
		                format(name, sizeof(name), "%s (%d kg)", FishSweet[fish_id][fName], kg + 1);
		                CreatePlayerItem(playerid, name, TYPE_FISH, FishSalt[fish_id][fValue1], WATER_SALT, 1);
	                }
	            }
	        }
	        
	        CharacterCache[playerid][pBait] = 0;
	        
	        ApplyAnimation(playerid, "CAMERA", "picstnd_out", 4.1, 0, 0, 0, 1, 0, 1);
	    }
	}
    if(newkeys == (KEY_WALK + KEY_SPRINT))
    {
        if(!IsPlayerInAnyVehicle(playerid))
        {
            ForeachEx(i, MAX_DOORS)
            {
                if(PlayerToPoint(2.0, playerid, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ]) && GetPlayerVirtualWorld(playerid) == DoorInfo[i][dEnterVw])
                {
                    if(DoorInfo[i][dOwnerType] == OWNER_GROUP)
                    {
                        if(GroupData[DoorInfo[i][dOwner]][License] == -1)
                        {
                            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Lokal zosta³ zamkniêty przez urz¹d Los Santos Government.\nUdaj siê do urzêdu w celu wyjaœnienia sprawy zajêcia lokalu.", "Zamknij", "");
                            return 1;
                        }
                    }
                    if(DoorInfo[i][dBlock])
                    {
                        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Lokal zosta³ zamkniêty przez urz¹d Los Santos Government.\nZosta³ on doszczêtnie spalony podczas po¿aru.", "Zamknij", "");
                        return 1;
                    }
                    if(DoorInfo[i][dLock] == 1)
                    {
                        if(CharacterCache[playerid][pCash] >= DoorInfo[i][dEnterCash]) GivePlayerCash(playerid, -DoorInfo[i][dEnterCash]);
                        else ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie staæ Ciê na wejœcie do tego lokalu.", "Zamknij", "");

                        if(IsPlayerInAnyVehicle(playerid)) return 1;
                        OnPlayerEnterDoor(playerid, i);
                    }
                    else
                    {
                        GameTextForPlayer(playerid, "~n~~n~~n~~r~~h~Drzwi zamkniete!", 2000, 5);
                        return 1;
                    }
                    break;
                }
                else if(PlayerToPoint(2.0, playerid, DoorInfo[i][dExitX], DoorInfo[i][dExitY], DoorInfo[i][dExitZ]) && GetPlayerVirtualWorld(playerid) == DoorInfo[i][dExitVw])
                {
                    if(DoorInfo[i][dOwnerType] == OWNER_GROUP)
                    {
                        if(GroupData[DoorInfo[i][dOwner]][License] == -1)
                        {
                            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Lokal zosta³ zamkniêty przez urz¹d Los Santos Government.\nUdaj siê do urzêdu w celu wyjaœnienia sprawy zajêcia lokalu.", "Zamknij", "");
                            return 1;
                        }
                    }
                    if(DoorInfo[i][dBlock])
                    {
                        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Lokal zosta³ zamkniêty przez urz¹d Los Santos Government.\nZosta³ on doszczêtnie spalony podczas po¿aru.", "Zamknij", "");
                        return 1;
                    }

                    if(DoorInfo[i][dLock] == 1)
                    {
                        if(IsPlayerInAnyVehicle(playerid)) return 1;
                        OnPlayerExitDoor(playerid, i, 0, DoorInfo[i][dEnVw]);
                    }
                    else
                    {
                        GameTextForPlayer(playerid, "~n~~n~~n~~r~~h~Drzwi zamkniete!", 2000, 5);
                        return 1;
                    }
                    break;
                }
            }
        }
    }

    return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
    return 1;
}

public OnPlayerExitedMenu(playerid)
{
    return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
    return 1;
}

public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	ForeachEx(i, MAX_BURGERS)
	{
	    if(BurgerInfo[i][burgerMarker] == checkpointid)
	    {
			ShowPlayerDialog(playerid, D_BURGER_BUY, DIALOG_STYLE_LIST, " Wybór zestawu do kupna:", "1. Moo Kids Meal ($10)\n2. Beef Tower ($25)\n3. Meet Stack ($50)\n4. Salad Meal ($25)\n5. Cluckin' Little Meal ($10)\n6. Cluckin' Big Meal ($25)\n7. Cluckin' Huge Meal ($50)\n8. Big Salad Meal ($50)", "Kup", "Zamknij");
	    }
	}
	return 1;
}

public OnPlayerLeaveDynamicCP(playerid, checkpointid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
    return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
    return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        Infobox(playerid, 10, "Wcisnij ~g~~h~~k~~VEHICLE_HANDBRAKE~ + ~k~~VEHICLE_FIREWEAPON~~w~~h~ jednoczesnie, aby uruchomic silnik.~n~~n~Klawisz ~g~~h~~k~~VEHICLE_FIREWEAPON_ALT~~w~~h~ kontroluje swiatla w pojezdzie.");
        return 1;
    }
    if(newstate == PLAYER_STATE_SPECTATING)
    {
        if(!CharacterCache[playerid][pUID])
        {
            SetPlayerCameraPos(playerid, 216.280807, -1856.756835, 3.723000);
            SetPlayerCameraLookAt(playerid, 216.280807, -1856.756835, 3.723000);
        }
    }
   	if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)
	{
	    if(CharacterCache[playerid][pTaxiPassenger] != INVALID_PLAYER_ID)
	    {
	        new passenger_id = CharacterCache[playerid][pTaxiPassenger], price = CharacterCache[passenger_id][pTaxiPay];

	        if(price > 0)
	        {
      			new business_cash = floatround(0.90 * price),
					playercash = floatround(0.10 * price),
					string[128];

		        GivePlayerCash(passenger_id, -price);
		        GivePlayerCash(playerid, playercash);

		        new group_id = CharacterCache[playerid][pTaxiGroup];
		        GroupData[group_id][Cash] += business_cash;

		        SaveGroup(group_id);

       			format(string, sizeof(string), "Zap³aci³eœ $%d za przejazd taksówk¹.", price);
				ShowPlayerDialog(passenger_id, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

				format(string, sizeof(string), "Otrzyma³eœ premie w wysokoœci $%d!\nNa konto grupowe dodano: $%d", playercash, business_cash);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}

			CharacterCache[playerid][pTaxiPassenger] = INVALID_PLAYER_ID;
			CharacterCache[playerid][pTaxiGroup] = 0;

			CharacterCache[passenger_id][pTaxiVeh] = INVALID_VEHICLE_ID;
			CharacterCache[passenger_id][pTaxiPay] = 0;
			CharacterCache[passenger_id][pTaxiPrice] = 0;
	    }
	}
	

	if(oldstate == PLAYER_STATE_PASSENGER && newstate == PLAYER_STATE_ONFOOT)
	{
		if(CharacterCache[playerid][pTaxiVeh] != INVALID_VEHICLE_ID)
		{
			new driverid = GetVehicleDriver(CharacterCache[playerid][pTaxiVeh]), price = CharacterCache[playerid][pTaxiPay];

	        if(price > 0)
			{
	      		new business_cash = floatround(0.90 * price),
					playercash = floatround(0.10 * price),
					string[128];

		        GivePlayerCash(playerid, -price);
		        GivePlayerCash(driverid, playercash);

		        new group_id = CharacterCache[driverid][pTaxiGroup];
		        GroupData[group_id][Cash] += business_cash;

		        SaveGroup(group_id);

       			format(string, sizeof(string), "Zap³aci³eœ %d za przejazd taksówk¹.", price);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");

				format(string, sizeof(string), "Otrzyma³eœ premie w wysokoœci $%d!\nNa konto grupy dodano: $%d", playercash, business_cash);
				ShowPlayerDialog(driverid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");
			}

			CharacterCache[driverid][pTaxiPassenger] = INVALID_PLAYER_ID;
			CharacterCache[driverid][pTaxiGroup] = 0;

			CharacterCache[playerid][pTaxiVeh] = INVALID_VEHICLE_ID;
			CharacterCache[playerid][pTaxiPay] = 0;
			CharacterCache[playerid][pTaxiPrice] = 0;
		}
	}
    return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	if(CharacterCache[playerid][pReportPD])
	{
	    DisablePlayerCheckpoint(playerid);
	}
    return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
    return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
    return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
    return 1;
}

public OnPlayerRequestSpawn(playerid)
{
    return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(CharacterCache[playerid][pAdmin] && CharacterCache[playerid][pAdminDuty])
	{
    	SetPlayerPosFindZ(playerid, fX, fY, fZ);
    }
    return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	// Oferty
	if(playertextid == AcceptOffer[playerid])
    {
         Zaakceptuj(playerid, ACCEPT);
         CancelSelectTextDraw(playerid);
    }
    if(playertextid == CrossOffer[playerid])
    {
         Zaakceptuj(playerid, REJECT);
         CancelSelectTextDraw(playerid);
    }
	if(playertextid == InfoOffer[playerid])
	{
	    ShowPlayerOutInfo(playerid);
	    SelectTextDraw(playerid, 0xD4C598AA);
	}
	
    // GRUPA 1
    if(playertextid == Textdraw2[playerid])
    {
        cmd_g(playerid, "1 info");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw3[playerid])
    {
        cmd_g(playerid, "1 v");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw4[playerid])
    {
        cmd_g(playerid, "1 duty");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw5[playerid])
    {
        cmd_g(playerid, "1 magazyn");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw6[playerid])
    {
        cmd_g(playerid, "1 online");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    // GRUPA 2
    if(playertextid == Textdraw8[playerid])
    {
        cmd_g(playerid, "2 info");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw9[playerid])
    {
        cmd_g(playerid, "2 v");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw10[playerid])
    {
        cmd_g(playerid, "2 duty");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw11[playerid])
    {
        cmd_g(playerid, "2 magazyn");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw12[playerid])
    {
        cmd_g(playerid, "2 online");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    // GRUPA 3
    if(playertextid == Textdraw14[playerid])
    {
        cmd_g(playerid, "3 info");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw15[playerid])
    {
        cmd_g(playerid, "3 v");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw16[playerid])
    {
        cmd_g(playerid, "3 duty");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw17[playerid])
    {
        cmd_g(playerid, "3 magazyn");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw18[playerid])
    {
        cmd_g(playerid, "3 online");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    // GRUPA 4
    if(playertextid == Textdraw20[playerid])
    {
        cmd_g(playerid, "4 info");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw21[playerid])
    {
        cmd_g(playerid, "4 v");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw22[playerid])
    {
        cmd_g(playerid, "4 duty");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw23[playerid])
    {
        cmd_g(playerid, "4 magazyn");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw24[playerid])
    {
        cmd_g(playerid, "4 online");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    // GRUPA 5
    if(playertextid == Textdraw26[playerid])
    {
        cmd_g(playerid, "5 info");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw27[playerid])
    {
        cmd_g(playerid, "5 v");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw28[playerid])
    {
        cmd_g(playerid, "5 duty");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw29[playerid])
    {
        cmd_g(playerid, "5 magazyn");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }

    if(playertextid == Textdraw30[playerid])
    {
        cmd_g(playerid, "5 online");

        CancelSelectTextDraw(playerid);
        HidePlayerGroups(playerid);
    }
    return 1;
}

public OnPlayerText(playerid, text[])
{
    if(!CharacterCache[playerid][pUID]) return 0;
    
    if(CallNow[playerid])
    {
        new playerid2 = CallTo[playerid];
        new itemid = GetItemID(CharacterCache[playerid][pPhone]);
        new string[256];
        
        format(string, sizeof(string), "[Telefon] %d: %s", ItemInfo[itemid][iValue1], text);
	    SendClientMessage(playerid2, ZOLTY, string);

   		format(string, sizeof(string), "%s (telefon): %s", PlayerName2(playerid), text);
   		ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
   		return 0;
    }
    
    if(CharacterCache[playerid][pKnebel] || CharacterCache[playerid][pAJ] || CharacterCache[playerid][pBW])
    {
        return 0;
    }

	if(CharacterCache[playerid][pAdmin] && CharacterCache[playerid][pAdminDuty])
	{
	    if(text[0] == '#')
    	{
    	    SendAdminMessageFormat(0x68B322FF, "* [A] %s (ID: %d):%s", CharacterCache[playerid][pGlobalNick], playerid, text[1]);
    	    return 0;
    	}
	}
	
    if(text[0] == '@')
    {
        if(CharacterCache[playerid][pTog] & TOG_OOC)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Posiadasz zablokowany podgl¹d czatów OOC.\nAby go odblokowaæ u¿yj '/tog'.", "Zamknij", "");
            return 0;
        }

        if(text[1] == '1' || text[1] == '2' || text[1] == '3' || text[1] == '4' || text[1] == '5')
        {
            new slot = strval(text[1]);
            if(slot > 5 || slot == 0 || slot < 0) return 0;

            if(MemberGroup[playerid][slot][GroupID])
            {
                new groupid = MemberGroup[playerid][slot][GroupID];

                ForeachEx(i, MAX_PLAYERS)
                {
                    if(IsPlayerInGroup(i, groupid))
                    {
                        if(!(CharacterCache[i][pOption] & TOG_OOC))
                        {
                            SendClientMessageFormat(i, MakeColorDarker(GroupData[groupid][Chat][0], GroupData[groupid][Chat][1], GroupData[groupid][Chat][2], 30), "(( [%s] %s (%d):%s ))", GroupData[groupid][Tag], PlayerName2(playerid), playerid, text[2]);
                        }
                    }
                }
                return 0;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(text[1] == '@')
            {
                new slot = strval(text[2]);

                if(slot > 5 || slot == 0 || slot < 0) return 0;
                if(MemberGroup[playerid][slot][GroupSubGroup])
                {
                    new subid = MemberGroup[playerid][slot][GroupSubGroup];

                    ForeachEx(i, MAX_PLAYERS)
                    {
                        if(IsPlayerInSubGroup(i, subid))
                        {
                            if(!(CharacterCache[i][pOption] & TOG_OOC))
                            {
                                SendClientMessageFormat(i, MakeColorDarker(SubData[subid][sChat][0], SubData[subid][sChat][1], SubData[subid][sChat][2], 30), "(( [%s] %s (%d):%s ))", SubData[subid][sTag], PlayerName2(playerid), playerid, text[3]);
                            }
                        }
                    }
                    return 0;
                }
                else
                {
                    return 0;
                }
            }
        }
    }

    if(text[0] == '!')
    {
        if(text[1] == '1' || text[1] == '2' || text[1] == '3' || text[1] == '4' || text[1] == '5')
        {
            new slot = strval(text[1]);
            if(slot > 5 || slot == 0 || slot < 0) return 0;

            if(MemberGroup[playerid][slot][GroupID])
            {
                new groupid = MemberGroup[playerid][slot][GroupID];

                ForeachEx(i, MAX_PLAYERS)
                {
                    if(DutyGroup[i] == GroupData[groupid][UID])
                    {
                        SendClientMessageFormat(i, MakeColorLighter(GroupData[groupid][Chat][0], GroupData[groupid][Chat][1], GroupData[groupid][Chat][2], 30), "** [%s] %s (%d):%s **", GroupData[groupid][Tag], PlayerName2(playerid), playerid, text[2]);
                    }
                }
                return 0;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(text[1] == '!')
            {
                new slot = strval(text[2]);

                if(slot > 5 || slot == 0 || slot < 0) return 0;
                if(MemberGroup[playerid][slot][GroupSubGroup])
                {
                    new subid = MemberGroup[playerid][slot][GroupSubGroup];

                    ForeachEx(i, MAX_PLAYERS)
                    {
                        if(IsPlayerInSubGroup(i, subid))
                        {
                            SendClientMessageFormat(i, MakeColorLighter(SubData[subid][sChat][0], SubData[subid][sChat][1], SubData[subid][sChat][2], 30), "** [%s] %s (%d):%s **", SubData[subid][sTag], PlayerName2(playerid), playerid, text[3]);
                        }
                    }
                    return 0;
                }
                else
                {
                    return 0;
                }
            }
        }
    }

    new str[256];
    if(!strcmp(text, ":)", true) || !strcmp(text, " :)", true) || !strcmp(text, ":) ", true) || !strcmp(text, ":)", true))
    {
        format(str, sizeof(str), "* %s uœmiecha siê.", PlayerName2(playerid));
        SendClientMessageEx(10.0, playerid, str, 0xC6A2EEFF, 0xA582BDFF, 0x8C75A5FF, 0x846994FF, 0x73617BFF);
        return 0;
    }
    else if(!strcmp(text, ":(", true) || !strcmp(text, " :(", true) || !strcmp(text, ":( ", true) || !strcmp(text, ";(", true) || !strcmp(text, ";0", true))
    {
        format(str, sizeof(str), "* %s robi smutn¹ minê.", PlayerName2(playerid));
        SendClientMessageEx(10.0, playerid, str, 0xC6A2EEFF, 0xA582BDFF, 0x8C75A5FF, 0x846994FF, 0x73617BFF);
        return 0;
    }
    else if(!strcmp(text, ":D", true) || !strcmp(text, " :D", true) || !strcmp(text, ":D ", true) || !strcmp(text, ";D", true))
    {
        format(str, sizeof(str), "* %s œmieje siê.", PlayerName2(playerid));
        SendClientMessageEx(10.0, playerid, str, 0xC6A2EEFF, 0xA582BDFF, 0x8C75A5FF, 0x846994FF, 0x73617BFF);
        ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.1, 0, 0, 0, 0, 0, 1);
        return 0;
    }
    else if(!strcmp(text, ":P", true) || !strcmp(text, " :P", true) || !strcmp(text, ":P ", true) || !strcmp(text, ";P", true))
    {
        format(str, sizeof(str), "* %s wystawia jêzyk.", PlayerName2(playerid));
        SendClientMessageEx(10.0, playerid, str, 0xC6A2EEFF, 0xA582BDFF, 0x8C75A5FF, 0x846994FF, 0x73617BFF);
        return 0;
    }
    else if(!strcmp(text, ":/", true) || !strcmp(text, " :/", true) || !strcmp(text, ":/ ", true) || !strcmp(text, ";/", true))
    {
        format(str, sizeof(str), "* %s krzywi siê.", PlayerName2(playerid));
        SendClientMessageEx(10.0, playerid, str, 0xC6A2EEFF, 0xA582BDFF, 0x8C75A5FF, 0x846994FF, 0x73617BFF);
        return 0;
    }
    else if(!strcmp(text, ":o", true) || !strcmp(text, " :o", true) || !strcmp(text, ":o ", true) || !strcmp(text, ";o", true))
    {
        format(str, sizeof(str), "* %s robi zdziwion¹ minê.", PlayerName2(playerid));
        SendClientMessageEx(10.0, playerid, str, 0xC6A2EEFF, 0xA582BDFF, 0x8C75A5FF, 0x846994FF, 0x73617BFF);
        return 0;
    }
    else if(!strcmp(text, ";)", true) || !strcmp(text, " ;)", true) || !strcmp(text, ";) ", true) || !strcmp(text, ";)", true))
    {
        format(str, sizeof(str), "* %s puszcza oczko.", PlayerName2(playerid));
        SendClientMessageEx(10.0, playerid, str, 0xC6A2EEFF, 0xA582BDFF, 0x8C75A5FF, 0x846994FF, 0x73617BFF);
        return 0;
    }
    else if(!strcmp(text, ":*", true) || !strcmp(text, " :*", true) || !strcmp(text, ":* ", true) || !strcmp(text, ":*", true))
    {
        format(str, sizeof(str), "* %s daje buziaka.", PlayerName2(playerid));
        SendClientMessageEx(10.0, playerid, str, 0xC6A2EEFF, 0xA582BDFF, 0x8C75A5FF, 0x846994FF, 0x73617BFF);
        return 0;
    }

    if(CharacterCache[playerid][pAdminDuty])
    {
        new name[64];

        switch(CharacterCache[playerid][pAdmin])
        {
            case 1: format(name, sizeof(name), "{E6E6E6}Assistance %s ({6495ED}ASS1{E6E6E6})", AssCode(playerid), CharacterCache[playerid][pGlobalNick]);
            case 2: format(name, sizeof(name), "{E6E6E6}Assistance %s ({6495ED}ASS2{E6E6E6})", AssCode(playerid), CharacterCache[playerid][pGlobalNick]);
            case 3: format(name, sizeof(name), "{E6E6E6}Assistance %s ({6495ED}ASS3{E6E6E6})", AssCode(playerid), CharacterCache[playerid][pGlobalNick]);
            case 4: format(name, sizeof(name), "{E6E6E6}Assistance %s ({6495ED}ASS4{E6E6E6})", AssCode(playerid), CharacterCache[playerid][pGlobalNick]);
            case 5: format(name, sizeof(name), "{E6E6E6}Assistance %s ({6495ED}ASS5{E6E6E6})", AssCode(playerid), CharacterCache[playerid][pGlobalNick]);
            case 6: format(name, sizeof(name), "{E6E6E6}%s ({25b000}A1{E6E6E6})", CharacterCache[playerid][pGlobalNick]);
            case 7: format(name, sizeof(name), "{E6E6E6}%s ({25b000}A2{E6E6E6})", CharacterCache[playerid][pGlobalNick]);
            case 8: format(name, sizeof(name), "{E6E6E6}%s ({25b000}A3{E6E6E6})", CharacterCache[playerid][pGlobalNick]);
            case 9: format(name, sizeof(name), "{E6E6E6}%s ({CC2929}GA{E6E6E6})", CharacterCache[playerid][pGlobalNick]);
        }

        format(str, sizeof(str), "%s: %s", name, text);
        SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, str, 25);
    }
    else
    {
        if(!(CharacterCache[playerid][pOption] & OPTION_SAY))
        {
            ApplyAnimation(playerid, "PED", "IDLE_chat", 1.0, 0, 0, 0, 0, 0);
        }

        format(str, sizeof(str), "%s mówi: %s", PlayerName2(playerid), text);
        SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, str, 25);
    }
    return 0;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	new vehid = GetVehicleID(vehicleid);
	
    if(!VehicleInfo[vehid][vCompLoaded])
	{
	    new data[12], componentid;
		mysql_query_format("SELECT `value1` FROM `fc_items` WHERE `ownertype` = '%d' AND `owner` = '%d' AND `kind` = '%d'", OWNER_VEHICLE, VehicleInfo[vehid][vUID], TYPE_TUNING);

		mysql_store_result();
		
		while(mysql_fetch_row_format(data, "|"))
		{
		    sscanf(data, "p<|>d", componentid);
		    irp_AddVehicleComponent(vehid, componentid);
		}
		
		mysql_free_result();

		ChangeVehiclePaintjob(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vPaintJob]);
		VehicleInfo[vehid][vCompLoaded] = true;
	}
    return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
    return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	new vehid = GetVehicleUID(vehicleid);
	
	GetVehicleHealth(vehicleid, VehicleInfo[vehid][vHP]);
	GetVehicleDamageStatus(vehicleid, VehicleInfo[vehid][vVisual][0], VehicleInfo[vehid][vVisual][1], VehicleInfo[vehid][vVisual][2], VehicleInfo[vehid][vVisual][3]);
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
    return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
    return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
    return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	new vehid = GetVehicleUID(vehicleid);
    if((CharacterCache[playerid][pBW] || VehicleInfo[vehid][vLocked] || CharacterCache[playerid][pParalizeTime]) && !ispassenger)
    {
        new Float:PosX, Float:PosY, Float:PosZ;
        GetPlayerPos(playerid, PosX, PosY, PosZ);

        SetPlayerPos(playerid, PosX, PosY, PosZ);
        return 0;
    }
    if(IsAircraft(GetVehicleModel(vehicleid)))
    {
        SendClientMessage(playerid, SZARY, "(INFO) Aby nadawaæ na czêstotliwoœci lotniczej u¿yj komendy /lot.");
    }
    
    CharacterCache[playerid][pVehicleWarring] = 0;
    return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
    CharacterCache[playerid][pVehicleWarring] = 0;
    return 1;
}

public OnVehicleSpawn(vehicleid)
{
    new vehid = GetVehicleUID(vehicleid);
    
	if(VehicleInfo[vehid][vCompLoaded])
	{
	    ChangeVehiclePaintjob(vehicleid, VehicleInfo[vehid][vPaintJob]);
		ForeachEx(i, 14)
		{
		    if(VehicleInfo[vehid][vComponent][i] != 0)
		    {
				AddVehicleComponent(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vComponent][i] + 999);
		    }
		}
	}
    return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	new vehid = GetVehicleUID(vehicleid);
	
	GetVehicleDamageStatus(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vVisual][0], VehicleInfo[vehid][vVisual][1], VehicleInfo[vehid][vVisual][2], VehicleInfo[vehid][vVisual][3]);
    VehicleInfo[vehid][vHP] = 300.0;
    
    GetVehiclePos(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vPosX], VehicleInfo[vehid][vPosY], VehicleInfo[vehid][vPosZ]);
    GetVehicleZAngle(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vPosA]);

	VehicleInfo[vehid][vInteriorID] = 0;
	VehicleInfo[vehid][vWorldID] = GetVehicleVirtualWorld(VehicleInfo[vehid][vGameID]);

	SaveVehicle(vehid, SAVE_VEH_POS);
    SaveVehicle(vehid, SAVE_VEH_COUNT);
    return 1;
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
    if(!CharacterCache[playerid][pShowDoors])
    {
        new doorid = GetPickupID(pickupid),
            name_door[128];

        PlayerTextDrawHide(playerid, InfoDoor[playerid]);
        PlayerTextDrawHide(playerid, BoxDoor[playerid]);
        PlayerTextDrawHide(playerid, BoxDoorIcon[playerid]);
        PlayerTextDrawHide(playerid, IconDoorRed[playerid]);
        PlayerTextDrawHide(playerid, IconDoorPurple[playerid]);
        PlayerTextDrawHide(playerid, IconDoorGreen[playerid]);

        if(DoorInfo[doorid][dOwnerType] != OWNER_NONE && DoorInfo[doorid][dOwnerType] != OWNER_JAIL)
        {
            if(!DoorInfo[doorid][dExitX] || !DoorInfo[doorid][dExitY])
            {
                PlayerTextDrawShow(playerid, IconDoorPurple[playerid]);
            }
            else
            {
                if(!DoorInfo[doorid][dLock])
                {
                    PlayerTextDrawShow(playerid, IconDoorRed[playerid]);
                }
                else
                {
                    PlayerTextDrawShow(playerid, IconDoorGreen[playerid]);
                }
            }

            if(CharacterCache[playerid][pAdmin] < 6)
            {
                format(name_door, sizeof(name_door), "%s~n~~n~~y~[Brak informacji]~n~~n~~w~Nacisnij [ALT] + [SPACE]", DoorInfo[doorid][dName]);
            }
            else
            {
                format(name_door, sizeof(name_door), "%s~n~IDENTYFIKATOR: %d~n~~y~[Brak informacji]~n~~n~~w~Nacisnij [ALT] + [SPACE]", DoorInfo[doorid][dName], DoorInfo[doorid][dUID]);
            }

            PlayerTextDrawSetString(playerid, InfoDoor[playerid], name_door);
            PlayerTextDrawSetPreviewModel(playerid, BoxDoorIcon[playerid], DoorInfo[doorid][dPickupID]);

            PlayerTextDrawShow(playerid, InfoDoor[playerid]);
            PlayerTextDrawShow(playerid, BoxDoor[playerid]);
            PlayerTextDrawShow(playerid, BoxDoorIcon[playerid]);

            CharacterCache[playerid][pShowDoors] = 3;
        }
    }
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    if(CharacterCache[playerid][pBW])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Posiadasz ju¿ stan nieprzytomnoœci dlatego nie otrzymasz ponownego BW.", "Zamknij", "");
        return 1;
    }

    if(killerid != INVALID_PLAYER_ID)
    {
        if(CharacterCache[killerid][pHours] >= 20)
        {
            CharacterCache[playerid][pBW] = 10 * 60;

            if(CharacterCache[killerid][pGetWeapon])
            {
            	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Zosta³eœ postrzelony z broni. Twój aktualny stan nie pozwala na poruszanie siê.\nMusisz przeczekaæ stan nieprzytomnoœci, a¿ siê ockniesz lub zostaniesz uratowany.", "Zamknij", "");
			}
			else
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Zosta³eœ brutalnie pobity. Twój aktualny stan nie pozwala na poruszanie siê.\nMusisz przeczekaæ stan nieprzytomnoœci, a¿ siê ockniesz lub zostaniesz uratowany.", "Zamknij", "");
			}
		}
        else
        {
            CharacterCache[playerid][pBW] = 5 * 60;

            if(CharacterCache[playerid][pGetWeapon])
            {
            	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Zosta³eœ postrzelony z broni. Twój aktualny stan nie pozwala na poruszanie siê.\nMusisz przeczekaæ stan nieprzytomnoœci, a¿ siê ockniesz lub zostaniesz uratowany.", "Zamknij", "");
			}
			else
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Zosta³eœ brutalnie pobity. Twój aktualny stan nie pozwala na poruszanie siê.\nMusisz przeczekaæ stan nieprzytomnoœci, a¿ siê ockniesz lub zostaniesz uratowany.", "Zamknij", "");
			}
		}
    }
    else
    {
        CharacterCache[playerid][pBW] = 7 * 60;

        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Zosta³eœ brutalnie pobity. Twój aktualny stan nie pozwala na poruszanie siê.\nMusisz przeczekaæ stan nieprzytomnoœci, a¿ siê ockniesz lub zostaniesz uratowany.", "Zamknij", "");
    }

    GetPlayerPos(playerid, CharacterCache[playerid][pPos][0], CharacterCache[playerid][pPos][1], CharacterCache[playerid][pPos][2]);

    CharacterCache[playerid][pInt] = GetPlayerInterior(playerid);
    CharacterCache[playerid][pVW] = GetPlayerVirtualWorld(playerid);

    CharacterCache[playerid][pDeathReason] = reason;
    
    if(reason == 49)
    {
        CharacterCache[playerid][pDeathWeapon] = GetVehicleUID(GetPlayerVehicleID(killerid));
    }
    else
    {
    	CharacterCache[playerid][pDeathWeapon] = CharacterCache[killerid][pWeaponUID];
    }
    
    SetPlayerHealth(playerid, 100);

    SavePlayerStats(playerid, SAVE_PLAYER_POS);

    if(CharacterCache[playerid][pWeaponID])
    {
        new itemid = GetItemID(CharacterCache[playerid][pWeaponUID]);
        new mysql[128];

        format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `value2` = '%d', `used` = '0' WHERE `uid` = '%d' LIMIT 1", CharacterCache[playerid][pWeaponAmmo], CharacterCache[playerid][pWeaponUID]);
        mysql_query(mysql);

        ResetPlayerWeapons(playerid);

        ItemInfo[itemid][iUsed] = 0;
        ItemInfo[itemid][iValue2] = CharacterCache[playerid][pWeaponAmmo];

        CharacterCache[playerid][pWeaponUID]    = 0;
        CharacterCache[playerid][pWeaponID]     = 0;
        CharacterCache[playerid][pWeaponAmmo]   = 0;
        CharacterCache[playerid][pGetWeapon]    = false;
        
        if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON))
		{
			RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
		}
    }
    
    if(killerid == INVALID_PLAYER_ID)
    {
    	SendAdminMessageFormat(0xD96A6AFF, "[AI] %s (ID: %d) zosta³ zabity œmierci¹ naturaln¹.", PlayerName2(playerid), playerid);
    }
    else
    {
        SendAdminMessageFormat(0xD96A6AFF, "[AI] %s (ID: %d) zosta³ zabity przez %s (ID: %d).", PlayerName2(playerid), playerid, PlayerName2(killerid), killerid);
    }
    
    return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	new rand = random(20);
	if(bodypart == 9 && rand == 5)
	{
        // Informowanie graczy
		SendClientMessageToAllFormat(0xf74b4bFF, "Postaæ %s zosta³a uœmiercona.", PlayerName2(playerid));

		// Dodanie zw³ok
		AddCorpse(playerid, weaponid, weaponid);

		// Zapis postaci
		CharacterCache[playerid][pBlock] += BLOCK_CHAR;
		
		// Informacja
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Inforamcja", "Twoja postaæ zosta³a zabita z procentowej szansy.\nProcentowa szansa pozwala na zabicie postaci przez system.\n\nOdblokowanie postaci nie bêdzie mo¿liwe.", "Zamknij", "");

		// Wyrzucenie
		KickWithWait(playerid);
	}
	else
	{
	    if(CharacterCache[playerid][pDrugs])
	    {
	        new hp = floatround(amount / 2);
	        
	        AddPlayerHP(playerid, hp);
	    }
	}
	
    CharacterCache[playerid][pNickColor] = 0xD6363699;
    CharacterCache[playerid][pTakeDamage] = 3;
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(hittype == BULLET_HIT_TYPE_VEHICLE)
	{
	    if(GetVehicleModel(hitid) == 528 || GetVehicleModel(hitid) == 601 || GetVehicleModel(hitid) == 427 || GetVehicleModel(hitid) == 428)
	    {
	        return 0;
	    }
	}
	if(hittype == BULLET_HIT_TYPE_PLAYER)
	{
	    if(CharacterCache[hitid][pAdmin] == 9 && CharacterCache[hitid][pAdminDuty])
	    {
	        return 0;
	    }
	    else
	    {
	        if(CharacterCache[playerid][pDrugs])
	        {
				new rand = random(5);
				
				if(rand == 2)
				{
				    return 0;
				}
	        }
	        
	        new itemid = GetItemID(CharacterCache[playerid][pWeaponUID]);
			if(ItemInfo[itemid][iFlags] & ITEM_FLAG_PARALIZE)
			{
				ShowPlayerDialog(hitid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Jesteœ sparali¿owany, poniewa¿ zosta³eœ postrzelony paralizatorem.\nZostajesz pozbawiony ruchu na kilka sekund.", "Zamknij", "");

				CharacterCache[hitid][pParalizeTime] = 10;
				ApplyAnimation(hitid, "CRACK", "crckdeth2", 4.0, 0, 0, 0, 1, 0, 1);
			}
			if(ItemInfo[itemid][iFlags] & ITEM_FLAG_NODMG)
			{
			    return 0;
			}
	    }
	}
	
	// Zapis amunicji
 	if(CharacterCache[playerid][pWeaponID])
    {
    	if(!CharacterCache[playerid][pGetWeapon])
        {
        	if(CharacterCache[playerid][pWeaponID] > 15 && CharacterCache[playerid][pWeaponID] < 44)
            {
            	new ammo = GetPlayerWeaponAmmo(playerid, CharacterCache[playerid][pWeaponID]);
                CharacterCache[playerid][pWeaponAmmo] --;

                if(ammo != CharacterCache[playerid][pWeaponAmmo])
				{
				    CharacterCache[playerid][pWeaponAmmo] = ammo;
    				SetPlayerAmmo(playerid, CharacterCache[playerid][pWeaponID], CharacterCache[playerid][pWeaponAmmo]);
        		}
                if(ammo <= 0)
                {
                	new itemid = GetItemID(CharacterCache[playerid][pWeaponUID]);
                    new string[128];

                    format(string, sizeof(string), "UPDATE `fc_items` SET `value2` = '0', `used` = '0' WHERE `uid` = '%d' LIMIT 1", CharacterCache[playerid][pWeaponUID]);
                    mysql_query(string);

                    ResetPlayerWeapons(playerid);

                    ItemInfo[itemid][iUsed] = 0;
                    ItemInfo[itemid][iValue2] = 0;

                    CharacterCache[playerid][pWeaponUID]   = 0;
                    CharacterCache[playerid][pWeaponID]    = 0;
                    CharacterCache[playerid][pWeaponAmmo]  = 0;
                    CharacterCache[playerid][pGetWeapon]   = false;

                    if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON))
		    		{
						RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
					}
        		}
    		}
      	}
        else
        {
        	CharacterCache[playerid][pGetWeapon] = false;
        }
	}
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
    if(CharacterCache[playerid][pUID] == 0) return 1;
    if(!success) return PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
    return 1;
}

public OnPlayerCommandReceived(playerid, cmdtext[])
{
    if(!CharacterCache[playerid][pUID])
    {
        return 0;
    }
    if(strcmp(cmdtext, "/w", true) && strcmp(cmdtext, "/report", true))
    {
        if(CharacterCache[playerid][pAJ] && !CharacterCache[playerid][pAdmin])
        {
            return 0;
        }
    }
    return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    return 0;
}

public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	new searchid = GetObjectIndex(objectid);
	PlayerEditObject[playerid] = searchid;
	EditDynamicObject(playerid, objectid);
	
	Infobox(playerid, 5, "Edycja obiektu zostala ~g~~h~rozpoczeta~w~~h~.");
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
    if(response)
    {
        if(CheckItemAttach(ItemInfo[PlayerItemIndex[playerid]][iUID]))
        {
            new attach_id = CheckItemAttach(ItemInfo[PlayerItemIndex[playerid]][iUID]);

            AttachInfo[attach_id][afOffsetX] = fOffsetX;
            AttachInfo[attach_id][afOffsetY] = fOffsetY;
            AttachInfo[attach_id][afOffsetZ] = fOffsetZ;

            AttachInfo[attach_id][afRotX] = fRotX;
            AttachInfo[attach_id][afRotY] = fRotY;
            AttachInfo[attach_id][afRotZ] = fRotZ;

            AttachInfo[attach_id][afScaleX] = fScaleX;
            AttachInfo[attach_id][afScaleY] = fScaleY;
            AttachInfo[attach_id][afScaleZ] = fScaleZ;

            SaveAttach(attach_id);
        }
        else
        {
            AddAttach(modelid, ItemInfo[PlayerItemIndex[playerid]][iUID], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
        }

        PlayerItemIndex[playerid] = 0;
        SetPlayerAttachedObject(playerid, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
        
        Infobox(playerid, 5, "Obiekt zostal pomyslnie ~g~~h~zapisany~w~~h~.");
    }
    else
    {
        new indexItem = PlayerItemIndex[playerid];
        
        mysql_query_format("UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", ItemInfo[indexItem][iUID]);
        PlayerItemIndex[playerid] = 0;

        RemovePlayerAttachedObject(playerid, index);
        Infobox(playerid, 5, "Obiekt zostal pomyslnie ~g~~h~usuniety~w~~h~.");
    }
    return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	// Definiowanie zmiennych
	new Float:Pos[3], Float:Rot[3];
	new uid = PlayerEditObject[playerid];

	// Przypisywanie pozycji obiektu
	GetDynamicObjectPos(objectid, Pos[0], Pos[1], Pos[2]);
	GetDynamicObjectRot(objectid, Rot[0], Rot[1], Rot[2]);

	switch(response)
	{
	    case EDIT_RESPONSE_CANCEL: // Przerwanie edycji obiektu
	    {
			if(PlayerEditGate[playerid])
			{
				// Przenieœ obiekt na pozycjê
			    SetDynamicObjectPos(objectid, Pos[0], Pos[1], Pos[2]);
				SetDynamicObjectRot(objectid, Rot[0], Rot[1], Rot[2]);

				// Aktualizowanie zmiennych
				ObjectInfo[uid][oX] = Pos[0];
				ObjectInfo[uid][oY] = Pos[1];
				ObjectInfo[uid][oZ] = Pos[2];

				ObjectInfo[uid][oRX] = Rot[0];
				ObjectInfo[uid][oRY] = Rot[1];
				ObjectInfo[uid][oRZ] = Rot[2];

				ObjectInfo[uid][oGateX] = x;
				ObjectInfo[uid][oGateY] = y;
				ObjectInfo[uid][oGateZ] = z;
				
				ObjectInfo[uid][oGateRX] = rx;
				ObjectInfo[uid][oGateRY] = ry;
				ObjectInfo[uid][oGateRZ] = rz;

                ObjectInfo[uid][oGate] = 1;
				ObjectInfo[uid][oGateOpen] = false;

				// Zapisywanie obiektu i bramy
				SaveObject(uid);
				SaveObjectGate(uid);

				// Zakoñcz edycjê obiektu
				PlayerEditObject[playerid] = 0;
				PlayerEditGate[playerid] = false;

				// Wyœlij informacjê dla gracza
				Infobox(playerid, 5, "Brama zostala pomyslnie ~g~~h~zapisana~w~~h~.");
			}
			else if(PlayerEditObject[playerid])
	        {
		        // Przenieœ obiekt na pozycjê
		    	SetDynamicObjectPos(objectid, Pos[0], Pos[1], Pos[2]);
				SetDynamicObjectRot(objectid, Rot[0], Rot[1], Rot[2]);

				// Aktualizowanie zmiennych
				ObjectInfo[uid][oX] = Pos[0];
				ObjectInfo[uid][oY] = Pos[1];
				ObjectInfo[uid][oZ] = Pos[2];
				ObjectInfo[uid][oRX] = Rot[0];
				ObjectInfo[uid][oRY] = Rot[1];
				ObjectInfo[uid][oRZ] = Rot[2];

				// Zapisywanie obiektu
				SaveObject(uid);

	            // Zakoñcz edycjê obiektu
				PlayerEditObject[playerid] = 0;

	            // Wyœlij informacjê dla gracza
				Infobox(playerid, 5, "Edycja obiektu zostala ~g~~h~przerwana~w~~h~.");
			}
	    }
	    case EDIT_RESPONSE_FINAL: // Zakoñczenie edycji obiektu
	 	{
	 	    if(EditBusStop[playerid])
   			{
   			    // Tworzenie zmiennej
				new busid = EditBusStop[playerid];
				
				// Aktualizowanie zmiennych
				BusStop[busid][bPos][0] = x;
				BusStop[busid][bPos][1] = y;
				BusStop[busid][bPos][2] = z;
				
				BusStop[busid][bRot][0] = rx;
				BusStop[busid][bRot][1] = ry;
				BusStop[busid][bRot][2] = rz;
				
				// Zapisz przystanek
				SaveBusStop(busid);
				
				// Zakoñcz edycjê przystanku
				EditBusStop[playerid] = 0;
				
				// Wyœlij informacjê dla gracza
				Infobox(playerid, 5, "Przystanek zostal ~g~~h~zapisany~w~~h~.");
			}
	 	    else
	 	    {
		 	    if(ObjectInfo[uid][oOwnerType] == OWNER_AREA)
		 	    {
		 	        if(IsPositionInArea(ObjectInfo[uid][oOwner], x, y))
		 	        {
			 	        // Przenieœ obiekt na pozycjê
				        SetDynamicObjectPos(objectid, x, y, z);
						SetDynamicObjectRot(objectid, rx, ry, rz);

						// Aktualizowanie zmiennych
						ObjectInfo[uid][oX] = x;
						ObjectInfo[uid][oY] = y;
						ObjectInfo[uid][oZ] = z;
						
						ObjectInfo[uid][oRX] = rx;
						ObjectInfo[uid][oRY] = ry;
						ObjectInfo[uid][oRZ] = rz;

						// Zapisywanie obiektu
						SaveObject(uid);

						// Zakoñcz edycjê obiektu
						PlayerEditObject[playerid] = 0;

						// Wyœlij informacjê dla gracza
						Infobox(playerid, 5, "Obiekt zostal ~g~~h~zapisany~w~~h~.");
		 	        }
		 	        else
	     			{
		 	        	// Przenieœ obiekt na pozycjê
				    	SetDynamicObjectPos(objectid, Pos[0], Pos[1], Pos[2]);
						SetDynamicObjectRot(objectid, Rot[0], Rot[1], Rot[2]);

						// Aktualizowanie zmiennych
						ObjectInfo[uid][oX] = Pos[0];
						ObjectInfo[uid][oY] = Pos[1];
						ObjectInfo[uid][oZ] = Pos[2];
						ObjectInfo[uid][oRX] = Rot[0];
						ObjectInfo[uid][oRY] = Rot[1];
						ObjectInfo[uid][oRZ] = Rot[2];

						// Zapisywanie obiektu
						SaveObject(uid);

			            // Zakoñcz edycjê obiektu
						PlayerEditObject[playerid] = 0;

			            // Wyœlij informacjê dla gracza
						Infobox(playerid, 5, "Edycja obiektu zostala ~g~~h~przerwana~w~~h~.~n~~n~~r~Obiekt nie znajduje sie  w strefie.");
		 	        }
		 	    }
		 	    else
		 	    {
			 	    // Przenieœ obiekt na pozycjê
	        		SetDynamicObjectPos(objectid, x, y, z);
					SetDynamicObjectRot(objectid, rx, ry, rz);

					// Aktualizowanie zmiennych
					ObjectInfo[uid][oX] = x;
					ObjectInfo[uid][oY] = y;
					ObjectInfo[uid][oZ] = z;

					ObjectInfo[uid][oRX] = rx;
					ObjectInfo[uid][oRY] = ry;
					ObjectInfo[uid][oRZ] = rz;

					// Zapisywanie obiektu
					SaveObject(uid);

					// Zakoñcz edycjê obiektu
					PlayerEditObject[playerid] = 0;

					// Wyœlij informacjê dla gracza
					Infobox(playerid, 5, "Edycja obiektu zostala ~g~~h~zapisana~w~~h~.");
				}
			}
	    }
	}
	return 1;
}

public OnObjectMoved(objectid)
{
    return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
    return 1;
}

public OnRconCommand(cmd[])
{
    return 1;
}
