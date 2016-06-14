forward CreatePlayerItem(playerid, ItemName[], ItemType, ItemValue1, ItemValue2, ItemValues);
forward DeleteItem(itemuid);
forward ListPlayerItemsForPlayer(playerid, giveplayer_id);
forward OnPlayerDropItem(playerid, itemid);
forward ListPlayerNearItems(playerid);
forward OnPlayerRaiseItem(playerid, itemuid);
forward UnloadPlayerItems(playerid);
forward OnPlayerUseItem(playerid, itemid);
forward LoadItem(itemuid);
forward LoadPlayerItems(playerid);
forward ListPlayerItems(playerid);
forward ShowPlayerMagazine(playerid);

public CreatePlayerItem(playerid, ItemName[], ItemType, ItemValue1, ItemValue2, ItemValues)
{
	new item_uid, itemid, mysql[256];
	
	//if(ItemType == TYPE_PHONE) 		ItemValue1 = 100000 + random(899999);
	if(ItemType == TYPE_INHIBITOR) 	ItemValue1 = 22;
	if(ItemType == TYPE_PAINT) 		ItemValue1 = 41;
	
	mysql_real_escape_string(ItemName, ItemName);
	format(mysql, sizeof(mysql), "INSERT INTO `fc_items` VALUES (NULL, '%s', '%d', '%d', '%d', '%d', '%d', 0, 0, 0, 0, 0, '%d', 0, 0, 0)", ItemName, ItemValue1, ItemValue2, ItemType, OWNER_PLAYER, CharacterCache[playerid][pUID], ItemValues);
	mysql_query(mysql);
	
	itemid = GetFreeItemID();
	item_uid = mysql_insert_id();
	
	ItemInfo[itemid][iUID] = item_uid;
	strmid(ItemInfo[itemid][iName], ItemName, 0, strlen(ItemName), 32);
	
	ItemInfo[itemid][iValue1] = ItemValue1;
	ItemInfo[itemid][iValue2] = ItemValue2;
	
	ItemInfo[itemid][iType] = ItemType;
	
	ItemInfo[itemid][iPlace] = OWNER_PLAYER;
	ItemInfo[itemid][iOwner] = CharacterCache[playerid][pUID];

	ItemInfo[itemid][iValues] = ItemValues;
	
	return item_uid;
}

public DeleteItem(itemuid)
{
	new mysql[128], itemid = GetItemID(itemuid);
	format(mysql, sizeof(mysql), "DELETE FROM `fc_items` WHERE `uid` = '%d' LIMIT 1", itemuid);
	mysql_query(mysql);
	
	ItemInfo[itemid][iUID] = 0;
	
	ItemInfo[itemid][iValue1] = 0;
	ItemInfo[itemid][iValue2] = 0;
	
	ItemInfo[itemid][iType] = 0;
	
	ItemInfo[itemid][iPlace] = 0;
	ItemInfo[itemid][iOwner] = 0;

	ItemInfo[itemid][iValues] = 0;
	return 1;
}

stock GetItemID(itemuid)
{
	new itemid;
 	ForeachEx(i, MAX_ITEMS)
	{
	    if(ItemInfo[i][iUID] == itemuid)
	    {
	        itemid = i;
	        break;
	    }
	}
	return itemid;
}

stock GetFreeItemID()
{
	new itemid;
    ForeachEx(i, MAX_ITEMS)
	{
	    if(!ItemInfo[i][iUID])
	    {
	        itemid = i;
	        break;
	    }
	}
	return itemid;
}

stock GetItemObjectID(itemuid)
{
	new object_id;
 	for (new obj = 1; obj < MAX_ITEMS; obj++)
	{
	    if(ItemObject[obj][objItemUID] == itemuid)
	    {
	        object_id = obj;
	        break;
	    }
	}
	return object_id;
}

stock GetFreeItemObjectID()
{
	new object_id;
    for (new obj = 1; obj < MAX_ITEMS; obj++)
	{
	    if(!ItemObject[obj][objItemUID])
	    {
	        object_id = obj;
	        break;
	    }
	}
	return object_id;
}

stock GetTypeDrug(kind)
{
	new type = 0;
	
	switch(kind)
	{
	    case DRUG_META: type = TYPE_META;
	    case DRUG_MAR: type = TYPE_MAR;
	    case DRUG_COCAINE: type = TYPE_COCAINE;
	}
	
	return type;
}

public ListPlayerItemsForPlayer(playerid, giveplayer_id)
{
    new string[128], mysql[128];

    format(mysql, sizeof(mysql), "SELECT `uid`, `name`, `value1`, `value2` FROM `fc_items` WHERE `ownertype` = '%d' AND `owner` = '%d'", OWNER_PLAYER, CharacterCache[giveplayer_id][pUID]);
    mysql_check(); mysql_query(mysql);

    new data[128], list_items[512],
        item_uid, item_name[32], item_value1, item_value2;

    mysql_store_result();
    while(mysql_fetch_row_format(data, "|"))
    {
        sscanf(data, "p<|>ds[32]dd", item_uid, item_name, item_value1, item_value2);
        format(list_items, sizeof(list_items), "%s\n{000000}%d\t%d\t%d\t{FFFFFF}%s", list_items, item_uid, item_value1, item_value2, item_name);
    }
    mysql_free_result();
    if(!strlen(list_items))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie znaleziono ¿adnych przedmiotów w ekwipunku.", "Zamknij", "");
        return 1;
    }
    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, "Znaleziono przedmioty", list_items, "Zamknij", "");

    format(string, sizeof(string), "~n~~n~~n~~n~~n~~n~~n~~n~~n~~y~Gotowka gracza ~r~%s~y~: ~g~$%d~y~.", PlayerName2(giveplayer_id), CharacterCache[giveplayer_id][pCash]);
    GameTextForPlayer(playerid, string, 6000, 3);
    return 1;
}

public OnPlayerDropItem(playerid, itemid)
{
    new string[128];

    if(CharacterCache[playerid][pGetWeapon] && CharacterCache[playerid][pWeaponUID] == ItemInfo[itemid][iUID])
    {
        ResetPlayerWeapons(playerid);

        ItemInfo[itemid][iUsed]     = 0;
        ItemInfo[itemid][iValue2]   = 0;

        new mysql[128];
        format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `used` = 0, `value2` = '%d' WHERE `uid` = '%d'", CharacterCache[playerid][pWeaponAmmo], ItemInfo[itemid][iUID]);
        mysql_check(); mysql_query(mysql);

        CharacterCache[playerid][pWeaponUID]    = 0;
        CharacterCache[playerid][pWeaponID]     = 0;
        CharacterCache[playerid][pWeaponAmmo]   = 0;
        CharacterCache[playerid][pGetWeapon]    = false;
    }
    
    if(ItemInfo[itemid][iType] == TYPE_PHONE)
    {
        CharacterCache[playerid][pPhone] = 0;
    }
    
    if(ItemInfo[itemid][iType] == TYPE_ATTACH)
	{
	    new attach_id = CheckItemAttach(ItemInfo[itemid][iUID]);
	    if(attach_id) DeleteAttach(attach_id);
	}

    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new Float:PosX, Float:PosY, Float:PosZ, Float:PosA, virtual_world = GetPlayerVirtualWorld(playerid);

        GetPlayerPos(playerid, PosX, PosY, PosZ);
        GetPlayerFacingAngle(playerid, PosA);

        format(string, sizeof(string), "%s coœ odk³ada.", PlayerName2(playerid));
        ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.1,0,0,0,0,0,1);

        new mysql[256];
        format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `pos_x` = '%f', `pos_y` = '%f', `pos_z` = '%f', `ownertype` = '%d', `world` = '%d' WHERE `uid` = '%d' LIMIT 1", PosX, PosY, PosZ, OWNER_NONE, virtual_world, ItemInfo[itemid][iUID]);
        mysql_check(); mysql_query(mysql);

        new object_id = GetFreeItemObjectID();
        ItemObject[object_id][objItemUID] = ItemInfo[itemid][iUID];

        if(ItemInfo[itemid][iType] == TYPE_WEAPON || ItemInfo[itemid][iType] == TYPE_INHIBITOR || ItemInfo[itemid][iType] == TYPE_PAINT)
        {
            ItemObject[object_id][objID] = CreateDynamicObject(WeaponModel[ItemInfo[itemid][iValue1]], PosX, PosY, PosZ - 1.0, 80.0, 0.0, -PosA, virtual_world, -1, -1, 80.0);
        }
        else if(ItemInfo[itemid][iType] == TYPE_ATTACH)
		{
		    ItemObject[object_id][objID] = CreateDynamicObject(ItemInfo[itemid][iValue1], PosX, PosY, PosZ - 1.0, 80.0, 0.0, 0, virtual_world, -1, -1, 80.0);
		}
        else
        {
            ItemObject[object_id][objID] = CreateDynamicObject(ItemTypeInfo[ItemInfo[itemid][iType]][iTypeObjModel], PosX, PosY, PosZ - 1.0, ItemTypeInfo[ItemInfo[itemid][iType]][iTypeObjRotX], ItemTypeInfo[ItemInfo[itemid][iType]][iTypeObjRotY], -PosA, virtual_world, -1, -1, 80.0);
        }

        Streamer_Update(playerid);
    }
    else if(IsPlayerInAnyVehicle(playerid))
    {
        new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));

        format(string, sizeof(string), "%s odk³ada coœ w pojeŸdzie.", PlayerName2(playerid));
        ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

        ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);

        new mysql[256];
        format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `ownertype` = '%d', `owner` = '%d' WHERE `uid` = '%d' LIMIT 1", OWNER_VEHICLE, VehicleInfo[vehid][vUID], ItemInfo[itemid][iUID]);
        mysql_check(); mysql_query(mysql);
    }

    ItemInfo[itemid][iUID] = 0;
    ItemInfo[itemid][iValue1] = 0;
    ItemInfo[itemid][iValue2] = 0;
    ItemInfo[itemid][iType] = 0;

    ItemInfo[itemid][iPlace] = 0;
    ItemInfo[itemid][iOwner] = 0;
    
	ItemInfo[itemid][iValues] = 0;
    return 1;
}

public ListPlayerNearItems(playerid)
{
    new data[64], list_items[512], mysql[512];
    if(!IsPlayerInAnyVehicle(playerid))
    {
        new Float:PosX, Float:PosY, Float:PosZ;
        GetPlayerPos(playerid, PosX, PosY, PosZ);

        format(mysql, sizeof(mysql), "SELECT `uid`, `name` FROM `fc_items` WHERE `pos_x` < %f + 2 AND `pos_x` > %f - 2 AND `pos_y` < %f + 2 AND `pos_y` > %f - 2 AND `pos_z` < %f + 2 AND `pos_z` > %f - 2 AND `ownertype` = '%d' AND `world` = '%d'", PosX, PosX, PosY, PosY, PosZ, PosZ, OWNER_NONE, GetPlayerVirtualWorld(playerid));
        mysql_check(); mysql_query(mysql);
    }
    else
    {
        new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
        if(VehicleInfo[vehid][vOwnerType] == OWNER_PLAYER && VehicleInfo[vehid][vOwner] != CharacterCache[playerid][pUID] && CharacterCache[playerid][pAdmin] < 7)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz podnosiæ przedmiotów z tego pojazdu.", "Zamknij", "");
            return 1;
        }
        if(VehicleInfo[vehid][vOwnerType] == OWNER_GROUP && CharacterCache[playerid][pAdmin] < 7)
        {
            return 1;
            // Uprawnienia grupowe
        }

        format(mysql, sizeof(mysql), "SELECT `uid`, `name` FROM `fc_items` WHERE `ownertype` = '%d' AND `owner` = '%d'", OWNER_VEHICLE, VehicleInfo[vehid][vUID]);
        mysql_check(); mysql_query(mysql);
    }

    new item_uid, item_name[32];

    mysql_store_result();
    while(mysql_fetch_row_format(data, "|"))
    {
        sscanf(data, "p<|>ds[32]", item_uid, item_name);
        format(list_items, sizeof(list_items), "%s\n%d\t%s", list_items, item_uid, item_name);
    }
    mysql_free_result();

    if(!strlen(list_items))
    {
        Infobox(playerid, 5, "Nie znaleziono ~g~~h~zadnych~w~~h~ przedmiotow w poblizu.");
        return 1;
    }

    ShowPlayerDialog(playerid, D_RAISE_ITEM, DIALOG_STYLE_LIST, "Pobliskie przedmioty", list_items, "Podnieœ", "Anuluj");
    return 1;
}

public OnPlayerRaiseItem(playerid, itemuid)
{
    new string[128], data[64],
        ItemName[32], ItemPlace, ItemKind, ItemOwner, ItemValue1,
        mysql[256];

    format(mysql, sizeof(mysql), "SELECT `name`, `ownertype`, `kind`, `owner`, `value1` FROM `fc_items` WHERE `uid` = '%d' LIMIT 1", itemuid);
    mysql_check(); mysql_query(mysql);

    mysql_store_result();
    if(mysql_fetch_row_format(data, "|"))
    {
        sscanf(data, "p<|>s[32]dddd", ItemName, ItemPlace, ItemKind, ItemOwner, ItemValue1);
    }
    mysql_free_result();

    if(ItemPlace != OWNER_NONE && ItemPlace != OWNER_VEHICLE)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Tego przedmiotu nie ma w pobli¿u.", "Zamknij", "");
        return 1;
    }

    format(string, sizeof(string), "%s podnosi przedmiot %s.", PlayerName2(playerid), ItemName);
    ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

    ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.1,0,0,0,0,0,1);

    format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `ownertype` = '%d', `owner` = '%d' WHERE `uid` = '%d' LIMIT 1", OWNER_PLAYER, CharacterCache[playerid][pUID], itemuid);
    mysql_check(); mysql_query(mysql);

    if(ItemPlace != OWNER_VEHICLE)
    {
        new object_id = GetItemObjectID(itemuid);
        DestroyDynamicObject(ItemObject[object_id][objID]);
    }
    else
    {
        if(ItemKind == TYPE_POLICE)
        {
            new vehid = GetVehicleID(ItemOwner);

            DestroyObject(VehicleInfo[vehid][vPolice]);
            VehicleInfo[vehid][vPolice] = 0;
        }
    }

    LoadItem(itemuid);
    return 1;
}

public UnloadPlayerItems(playerid)
{
    new item;

    ForeachEx(itemid, MAX_ITEMS)
    {
        if(ItemInfo[itemid][iPlace] == OWNER_PLAYER && ItemInfo[itemid][iOwner] == CharacterCache[playerid][pUID])
        {
            ItemInfo[itemid][iUID] = 0;

            ItemInfo[itemid][iValue1] = 0;
            ItemInfo[itemid][iValue2] = 0;
            ItemInfo[itemid][iType] = 0;

            ItemInfo[itemid][iPlace] = 0;
            ItemInfo[itemid][iOwner] = 0;

            ItemInfo[itemid][iUsed] = 0;
            item++;
        }
    }

    return 1;
}

public OnPlayerUseItem(playerid, itemid)
{
    if(ItemInfo[itemid][iType] == TYPE_WEAPON || ItemInfo[itemid][iType] == TYPE_INHIBITOR || ItemInfo[itemid][iType] == TYPE_PAINT)
    {
        new mysql[128],
            ammo;

        if(ItemInfo[itemid][iValue2] <= 0 && !ItemInfo[itemid][iUsed])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W wybranej broni nie znajduje siê odpowiednia iloœæ amunicji.", "Zamknij", "");
            return 1;
        }

        if(ItemInfo[itemid][iUsed])
		{
            if(CharacterCache[playerid][pWeaponAmmo] <= 0)  ammo = 0;
            else                                            ammo = CharacterCache[playerid][pWeaponAmmo];

            format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `used` = 0, `value2` = '%d' WHERE `uid` = '%d'", ammo, ItemInfo[itemid][iUID]);
            mysql_check(); mysql_query(mysql);

            CharacterCache[playerid][pWeaponUID]    = 0;
            CharacterCache[playerid][pWeaponID]     = 0;
            CharacterCache[playerid][pWeaponAmmo]   = 0;
            CharacterCache[playerid][pGetWeapon]    = false;

            ItemInfo[itemid][iUsed] = 0;
            ItemInfo[itemid][iValue2] = ammo;

            RemovePlayerWeapon(playerid, ItemInfo[itemid][iValue1]);
            
            if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON))
	    	{
				RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
			}
        }
        else
        {
            if(CharacterCache[playerid][pGetWeapon] || CharacterCache[playerid][pWeaponID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W tym samym momencie mo¿esz posiadaæ tylko jedn¹ broñ.\nSchowaj aktualnie u¿ywan¹ broñ.", "Zamknij", "");
	            return 1;
	        }
	        
            CharacterCache[playerid][pWeaponUID]    = ItemInfo[itemid][iUID];
            CharacterCache[playerid][pWeaponID]     = ItemInfo[itemid][iValue1];
            CharacterCache[playerid][pWeaponAmmo]   = ItemInfo[itemid][iValue2];
            CharacterCache[playerid][pGetWeapon]    = true;

            GivePlayerWeapon(playerid, ItemInfo[itemid][iValue1], ItemInfo[itemid][iValue2]);

            ItemInfo[itemid][iUsed] = 1;

            format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", ItemInfo[itemid][iUID]);
            mysql_check(); mysql_query(mysql);
        }
    }
    if(ItemInfo[itemid][iType] == TYPE_FIRE)
    {
        new doorid = GetClosestDoor(playerid);
        if(doorid)
        {
            DoorInfo[doorid][dFireValue] = 5;
            DoorInfo[doorid][dFireUse] = true;
            DoorInfo[doorid][dFireObject] = CreateObject(18735, DoorInfo[doorid][dEnterX], DoorInfo[doorid][dEnterY], DoorInfo[doorid][dEnterZ] - 2.6, 0, 0, 0);

            DeleteItem(itemid);
        }
    }
    if(ItemInfo[itemid][iType] == TYPE_PICKLOCK)
    {
        new vehicleid = GetClosestVehicle(playerid);
        new rand = random(100);
        new procent = 15;
        new vehid = GetVehicleUID(vehicleid);
        
        if(GetPlayerArea(playerid))
        {
            procent += 5;
        }
        if(IsPlayerKindGroup(playerid, GROUP_DRIVERS))
        {
            procent += 5;
        }
        
        if(rand <= procent)
        {
            CharacterCache[playerid][pVehicleThief] = 100;
            CharacterCache[playerid][pVehicleThiefID] = vehid;
            
            UpdateDynamic3DTextLabelText(StatusTag[playerid], 0xFFFFFFCC, "(( Kradzie¿ pojazdu ))");
            
            new string[256];
            format(string, sizeof(string), "Rozpocze³eœ kradzie¿ pojazdu %s (UID: %d).\nUwa¿aj na patrol policyjny, który mo¿e pojawiæ siê w pobli¿u.\n\nNie oddalaj siê od pojazdu, odgrywaj rezlutnie akcjê.", GetVehicleModelName(VehicleInfo[vehid][vModel]), VehicleInfo[vehid][vUID]);
            
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "", "Zamknij", "");
        }
        else
        {
            DeleteItem(ItemInfo[itemid][iUID]);
            
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Próba rozpoczêcia w³amania do pojazdu nie powiod³a siê.\nWytrych uleg³ zniszczeniu w wyniku tej akcji.", "Zamknij", "");
        }
    }
    if(ItemInfo[itemid][iType] == TYPE_ROD)
    {
        new mysql[128];
        
    	if(!IsPlayerFishing(playerid))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", " Nie znajdujesz siê w miejscu ³owieckim.\nNa mapie ikonami zosta³y zaznaczone miejsca po³owu.", "Zamknij", "");
	        return 1;
	    }
	    if(!ItemInfo[itemid][iUsed])
	    {
	        if(!CharacterCache[playerid][pBait])
	    	{
	    	    new item = CharacterCache[playerid][pFishingRodUID];
	    	    
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", " Nie za³o¿y³eœ przynêty na wêdkê. Zrób to, a nastêpnie rozpocznij po³ów.", "Zamknij", "");

				CharacterCache[playerid][pFishTaking] = false;
		        CharacterCache[playerid][pFishingRodUID] = 0;
   				CharacterCache[playerid][pFished] = false;
   				
   				ItemInfo[item][iUsed] = 0;
   				
   				format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", ItemInfo[item][iUID]);
	            mysql_check(); mysql_query(mysql);

	   			RemovePlayerAttachedObject(playerid, SLOT_CASE);
				ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0);
   				return 1;
		    }
	    
		    ItemInfo[itemid][iUsed] = 1;

            format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", ItemInfo[itemid][iUID]);
            mysql_check(); mysql_query(mysql);
            
		    CharacterCache[playerid][pFishingRodUID] = itemid;
		    CharacterCache[playerid][pFished] = true;

   			SetPlayerAttachedObject(playerid, SLOT_CASE, 18632, 6, 0.079376, 0.037070, 0.007706, 181.482910, 0.0, 0.0, 1.0, 1.0, 1.0);
			ApplyAnimation(playerid, "CAMERA", "camstnd_lkabt", 4.1, 0, 0, 0, 1, 0, 1);

			Infobox(playerid, 10, "~h~~h~Proces polowu ~g~~h~ryb ~h~~h~w toku.~n~~h~~h~Odczekaj kilka chwil na zdobycz.");
		}
		else
		{
  			ItemInfo[itemid][iUsed] = 0;

            format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", ItemInfo[itemid][iUID]);
            mysql_check(); mysql_query(mysql);
            
		    CharacterCache[playerid][pFishingRodUID] = 0;
		    CharacterCache[playerid][pFished] = false;

   			RemovePlayerAttachedObject(playerid, SLOT_CASE);
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0);
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0);
		}
	}
	if(ItemInfo[itemid][iType] == TYPE_BAIT)
    {
        if(ItemInfo[itemid][iValues] <= 0)
        {
        	DeleteItem(ItemInfo[itemid][iUID]);
        }
        else
        {
            if(CharacterCache[playerid][pBait])
            {
	            CharacterCache[playerid][pBait] = ItemInfo[itemid][iValue1];

	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Przynêta z haczyka wêdki zosta³a zmieniona na inn¹.", "Zamknij", "");

	            ItemInfo[itemid][iValues] --;
				if(ItemInfo[itemid][iValues] <= 0)
				{
				    DeleteItem(ItemInfo[itemid][iUID]);
				}
			}
			else
			{
	            CharacterCache[playerid][pBait] = ItemInfo[itemid][iValue1];

	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Przynêta zosta³a pomyœlnie za³o¿ona na haczyk wêdki.", "Zamknij", "");

	            ItemInfo[itemid][iValues] --;
				if(ItemInfo[itemid][iValues] <= 0)
				{
				    DeleteItem(ItemInfo[itemid][iUID]);
				}
			}
        }
    }
    if(ItemInfo[itemid][iType] == TYPE_FISH)
    {
        if(ItemInfo[itemid][iValue2])
		{
		    if(IsPlayerInRangeOfPoint(playerid, 30.0, SettingInfo[sMagazineX], SettingInfo[sMagazineY], SettingInfo[sMagazineZ]))
		    {
		        new string[128];
		        
		        if(ItemInfo[itemid][iValue2] == WATER_SALT)
		        {
		            format(string, sizeof(string), "Pomyœlnie sprzeda³eœ rybê %s za cenê $%d.", ItemInfo[itemid][iName], SettingInfo[sFishSalt]);
		            
		            GivePlayerCash(playerid, SettingInfo[sFishSalt]);
		        }
		        else
		        {
		            format(string, sizeof(string), "Pomyœlnie sprzeda³eœ rybê %s za cenê $%d.", ItemInfo[itemid][iName], SettingInfo[sFishSweet]);
		            
		            GivePlayerCash(playerid, SettingInfo[sFishSweet]);
		        }
		        
		        DeleteItem(ItemInfo[itemid][iUID]);
		        DisablePlayerCheckpoint(playerid);
		        
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		    }
		    else
			{
			    if(CharacterCache[playerid][pPackage])
				{
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Podczas dostarczania paczki nie mo¿esz sprzedaæ ryby.", "Zamknij", "");
					return 1;
				}

			    SetPlayerCheckpoint(playerid, SettingInfo[sMagazineX], SettingInfo[sMagazineY], SettingInfo[sMagazineZ], 10.0);
			    
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w magazynie, aby móc sprzedaæ dan¹ rybê.", "Zamknij", "");
            	return 1;
			}
        }
		else
		{
			DeleteItem(ItemInfo[itemid][iUID]);

            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Z³owiona ryba nie jest poprawna.\nMog³o to wyst¹piæ na skutek uszkodzenia systemu.\nRyba zosta³a usuniêta.", "Zamknij", "");
            return 1;
		}
    }
    if(ItemInfo[itemid][iType] == TYPE_PHONE)
    {
        if(CharacterCache[playerid][pPhone] == ItemInfo[itemid][iUID])
        {
	        mysql_check();
			mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", ItemInfo[itemid][iUID]);

	        cmd_telefon(playerid, " ");
        }
        else
        {
            CharacterCache[playerid][pPhone] = ItemInfo[itemid][iUID];
            ItemInfo[itemid][iUsed] = 1;
            
            SavePlayerStats(playerid, SAVE_PLAYER_SETTING);
            
	        mysql_check();
			mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", ItemInfo[itemid][iUID]);

	        cmd_telefon(playerid, " ");
        }
    }
	if(ItemInfo[itemid][iType] == TYPE_MASK)
	{
	    if(CharacterCache[playerid][pMask])
	    {
	        CharacterCache[playerid][pMask] = false;
	        
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Maska zosta³a pomyœlnie zdjêta.", "Zamknij", "");
	    }
	    else
	    {
			if(ItemInfo[itemid][iValues] <= 0)
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Iloœæ u¿yæ w masce skoñczy³a siê.\nZosta³a usuniêta z ekwipunku.", "Zamknij", "");
			    
			    DeleteItem(ItemInfo[itemid][iUID]);
			    return 1;
			}
			
	        CharacterCache[playerid][pMask] = true;
	        
	        ItemInfo[itemid][iValue1] --;
	        
	        if(ItemInfo[itemid][iValue1] > 0)
	        {
		        new query[128];
		        format(query, sizeof(query), "UPDATE `fc_items` SET `value1` = `value1` - 1 WHERE `uid` = '%d'", ItemInfo[itemid][iUID]);
		        
		        mysql_check();
				mysql_query(query);
	        }
	        else
	        {
	            DeleteItem(ItemInfo[itemid][iUID]);
	        }

	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Maska zosta³a pomyœlnie za³o¿ona.\nJedno u¿ycie zosta³o zabrane.\n\nTwój nick do teraz bêdzie niewidoczny.", "Zamknij", "");
	    }
	}
	if(ItemInfo[itemid][iType] == TYPE_META)
	{
	    CharacterCache[playerid][pDrugs] = DRUG_META;
	    CharacterCache[playerid][pDrugsTime] = 100;
	    
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);
	    ShowPlayerProgressBar(playerid, DrugsBar[playerid]);
	    
	    SetPlayerProgressBarValue(playerid, DrugsBar[playerid], CharacterCache[playerid][pDrugsTime]);
	    UpdatePlayerProgressBar(playerid, DrugsBar[playerid]);
	    
	    OnPlayerUseDrug(playerid);
	    
	    DeleteItem(ItemInfo[itemid][iUID]);
	}
	if(ItemInfo[itemid][iType] == TYPE_COCAINE)
	{
	    CharacterCache[playerid][pDrugs] = DRUG_COCAINE;
	    CharacterCache[playerid][pDrugsTime] = 100;
	    
		SetPlayerProgressBarValue(playerid, DrugsBar[playerid], CharacterCache[playerid][pDrugsTime]);
	    UpdatePlayerProgressBar(playerid, DrugsBar[playerid]);

	    OnPlayerUseDrug(playerid);
	    
	    DeleteItem(ItemInfo[itemid][iUID]);
	}
	if(ItemInfo[itemid][iType] == TYPE_MAR)
	{
	    CharacterCache[playerid][pDrugs] = DRUG_MAR;
	    CharacterCache[playerid][pDrugsTime] = 100;

	    SetPlayerProgressBarValue(playerid, DrugsBar[playerid], CharacterCache[playerid][pDrugsTime]);
	    UpdatePlayerProgressBar(playerid, DrugsBar[playerid]);

	    OnPlayerUseDrug(playerid);
	    
	    DeleteItem(ItemInfo[itemid][iUID]);
	}
	if(ItemInfo[itemid][iType] == TYPE_ATTACH)
	{
	    PlayerItemIndex[playerid] = itemid;
		ShowPlayerDialog(playerid, D_ATTACH_USE, DIALOG_STYLE_MSGBOX, " Informacja", "W jaki sposób chcesz u¿yæ ten przedmiot?", "U¿yj", "Dopasuj");
	}
	if(ItemInfo[itemid][iType] == TYPE_PLANT)
    {
        new areaid = GetPlayerArea(playerid);
        if(AreaInfo[areaid][aOwnerType] != OWNER_NONE)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aby posadziæ roœlinê musisz znajdowaæ siê na strefie wolnej od w³aœciciela.", "Zamknij", "");
            return 1;
        }
        if(PlayerDoor[playerid])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê w drzwiach dlatego nie mo¿esz posiadziæ ¿adnej z roœlin.", "Zamknij", "");
            return 1;
        }
        if(IsPlayerInAnyVehicle(playerid))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W momencie sadzenia roœliny nie mo¿esz znajdowaæ siê w pojeŸdzie.", "Zamknij", "");
            return 1;
        }
        
        AddPlant(playerid, ItemInfo[itemid][iValue1]);
        DeleteItem(ItemInfo[itemid][iUID]);
        
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Uda³o Ci siê pomyœlnie posiadziæ roœlinê.\nŒredni czas jej wzrostu to 20 godzin.\n\nZebranie jest mo¿liwe gdy osi¹gnie ona minium 80 procent.\nPamiêtaj o jej pilnowaniu, ka¿dy z graczy mo¿e j¹ zebraæ.", "Zamknij", "");
    }
    if(ItemInfo[itemid][iType] == TYPE_FOOD)
    {
        if(CharacterCache[playerid][pFood] >= 100)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Jesteœ ju¿ w pe³ni najedzony. Nie potrzebujesz wiêcej jedzenia.", "Zamknij", "");
            return 1;
        }
        
        if((ItemInfo[itemid][iValue1] + CharacterCache[playerid][pFood]) > CharacterCache[playerid][pFood])
        {
            CharacterCache[playerid][pFood] = 100;
            SetPlayerDrunkLevel(playerid, 0);
            
            SetPlayerProgressBarValue(playerid, FoodBar[playerid], CharacterCache[playerid][pFood]);
			UpdatePlayerProgressBar(playerid, FoodBar[playerid]);
        }
        else
        {
            CharacterCache[playerid][pFood] += ItemInfo[itemid][iValue1];
            
            if(CharacterCache[playerid][pFood] <= 45)
            {
                SetPlayerDrunkLevel(playerid, 15000);
            }
            
            SetPlayerProgressBarValue(playerid, FoodBar[playerid], CharacterCache[playerid][pFood]);
			UpdatePlayerProgressBar(playerid, FoodBar[playerid]);
        }
        
        DeleteItem(ItemInfo[itemid][iUID]);
        
        new string[64];
        format(string, sizeof(string), "spo¿ywa produkt %s.", ItemInfo[itemid][iName]);
        
        cmd_me(playerid, string);
    }
    if(ItemInfo[itemid][iType] == TYPE_MONEY)
    {
        GivePlayerCash(playerid, ItemInfo[itemid][iValue1]);
        
        new string[256];
        format(string, sizeof(string), "otwiera ³adunek z plikami pieniêdzy. ($%d)", ItemInfo[itemid][iValue1]);
        
        cmd_me(playerid, string);
    }
    if(ItemInfo[itemid][iType] == TYPE_REGISTER)
    {
		new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
        if(!IsPlayerInAnyVehicle(playerid) || !vehid)
        {
        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w ¿adnym z pojazdów.", "Zamknij", "");
            return 1;
        }
        if(!IsOwnerVehicle(playerid, vehid))
        {
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do edycji tego pojazdu.", "Zamknij", "");
            return 1;
        }
        if(!IsPlayerKindGroup(playerid, GROUP_DRIVERS))
        {
        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aby zmieniæ tablicê musisz byæ w grupie przestêpczej (œciganci).", "Zamknij", "");
            return 1;
        }

        format(VehicleInfo[vehid][vRegister], 12, "LS-%d", random(998) + 1);

		SetVehicleNumberPlate(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vRegister]);
		SetVehicleToRespawn(VehicleInfo[vehid][vGameID]);

		SaveVehicle(vehid, SAVE_VEH_THINGS);
				
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Tablice w pojeŸdzie zosta³y pomyœlnie zmienione.\nPojazd zosta³ zrespawnowany na miejsce spawnu.", "Zamknij", "");
    }
    return 1;
}

public LoadItem(itemuid)
{
    new data[128], itemid = GetFreeItemID(), query[256];

    format(query, sizeof(query), "SELECT `uid`, `name`, `value1`, `value2`, `kind`, `ownertype`, `owner`, `used`, `value`, `flag` FROM `fc_items` WHERE uid = '%d' LIMIT 1", itemuid);
    mysql_check(); mysql_query(query);

    mysql_store_result();
    if(mysql_fetch_row_format(data, "|"))
    {
        sscanf(data, "p<|>ds[32]dddddddd",
        ItemInfo[itemid][iUID],
        ItemInfo[itemid][iName],
        ItemInfo[itemid][iValue1],
        ItemInfo[itemid][iValue2],
        ItemInfo[itemid][iType],
        ItemInfo[itemid][iPlace],
        ItemInfo[itemid][iOwner],
        ItemInfo[itemid][iUsed],
		ItemInfo[itemid][iValues],
		ItemInfo[itemid][iFlags]);
    }

    mysql_free_result();
    return itemid;
}

public LoadPlayerItems(playerid)
{
    new query[256], data[128], itemid, item;

    format(query, sizeof(query), "SELECT `uid`, `name`, `value1`, `value2`, `kind`, `ownertype`, `owner`, `used`, `value`, `flag` FROM `fc_items` WHERE `ownertype` = '%d' AND `owner` = '%d'", OWNER_PLAYER, CharacterCache[playerid][pUID]);
    mysql_check(); mysql_query(query);

    mysql_store_result();
    while(mysql_fetch_row_format(data, "|"))
    {
        item++;
        itemid = GetFreeItemID();

        sscanf(data, "p<|>ds[32]dddddddd",
        ItemInfo[itemid][iUID],
        ItemInfo[itemid][iName],
        ItemInfo[itemid][iValue1],
        ItemInfo[itemid][iValue2],
        ItemInfo[itemid][iType],
        ItemInfo[itemid][iPlace],
        ItemInfo[itemid][iOwner],
        ItemInfo[itemid][iUsed],
        ItemInfo[itemid][iValues],
		ItemInfo[itemid][iFlags]);
    }
    mysql_free_result();
    return 1;
}

public ListPlayerItems(playerid)
{
    new data[128], list_items[1024], query[256];
    new item_uid, item_name[32], item_value1, item_value2, item_use;
    
    format(query, sizeof(query), "SELECT `uid`, `name`, `value1`, `value2`, `used` FROM `fc_items` WHERE `owner` = '%d' AND `ownertype` = '%d'", CharacterCache[playerid][pUID], OWNER_PLAYER);
    mysql_check(); mysql_query(query);
    
    mysql_store_result();
    
    format(list_items, sizeof(list_items), "{C0C0C0}-- Lista dostêpnych przedmiotów");
    
    while(mysql_fetch_row_format(data, "|"))
    {
        sscanf(data, "p<|>ds[32]ddd", item_uid, item_name, item_value1, item_value2, item_use);

        if(item_use)
        {
            format(list_items, sizeof(list_items), "%s\n{000000}%d\t%d\t%d\t{164713}%s", list_items, item_uid, item_value1, item_value2, item_name);
        }
        else format(list_items, sizeof(list_items), "%s\n{000000}%d\t%d\t%d\t{878A87}%s", list_items, item_uid, item_value1, item_value2, item_name);
    }
    mysql_free_result();

    if(strlen(list_items)) ShowPlayerDialog(playerid, D_ITEM, DIALOG_STYLE_LIST, "Lista przedmiotów", list_items, "U¿yj", "Opcje");
    else Infobox(playerid, 5, "Nie posiadasz ~g~~h~¿adnych~w~~h~ przedmiotów.");
}

public ShowPlayerMagazine(playerid)
{
	new data[128], list_items[1024];
	new item_uid, item_name[32], item_value1, item_value2, item_value, item_kind, item_cash;
	
    mysql_check(); mysql_query("SELECT * FROM `fc_magazine` WHERE `value` <> 0");
    mysql_store_result();
    
    format(list_items, sizeof(list_items), "{C0C0C0}-- Lista dostêpnych przedmiotów");
    
    while(mysql_fetch_row_format(data, "|"))
    {
        sscanf(data, "p<|>ds[32]ddddd", item_uid, item_name, item_value1, item_value2, item_value, item_kind, item_cash);

        format(list_items, sizeof(list_items), "%s\n%d\t$%d\t\t%d sztuk\t\t%s", list_items, item_uid, item_cash, item_value, item_name);
    }
    mysql_free_result();

    if(strlen(list_items)) ShowPlayerDialog(playerid, D_MAGAZINE, DIALOG_STYLE_LIST, " Magazyn przestêpczy:", list_items, "Zakup", "Zamknij");
    else Infobox(playerid, 5, "Brak ~g~~h~dostepnych~w~~h~ przedmiotow w magazynie.");
}