public FCNPC_OnCreate(npcid)
{
	return 1;
}

public FCNPC_OnSpawn(npcid)
{
	new uid = GetFCNPCID(npcid);
	
	if(GangInfo[uid][gangID] == 1)
	{
 		FCNPC_SetHealth(npcid, 10000000.0);
	     
	    FCNPC_SetWeapon(npcid, 5);
	    FCNPC_SetAmmo(npcid, 1);
	    

	}
	
    SetPlayerColor(99, 0xFFFFFF00);
    SetPlayerColor(98, 0xFFFFFF00);
    SetPlayerColor(97, 0xFFFFFF00);
    SetPlayerColor(96, 0xFFFFFF00);
    SetPlayerColor(95, 0xFFFFFF00);
    SetPlayerColor(94, 0xFFFFFF00);
    SetPlayerColor(93, 0xFFFFFF00);
    SetPlayerColor(92, 0xFFFFFF00);
    SetPlayerColor(91, 0xFFFFFF00);
	return 1;
}

public FCNPC_OnReachDestination(npcid)
{
	new uid = GetFCNPCID(npcid);
	new playerid = GangInfo[uid][gangToPlayer];
	
	if(GangInfo[uid][gangStatus] == NPC_RUN_TO)
	{
	    GangInfo[uid][gangStatus] = NPC_CLOSE;
	    
	    if(IsPlayerPremium(playerid))
	    {
	    	if(CharacterCache[playerid][pSellDrug] > 5)
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "{C0C0C0}W tym dniu sprzeda³eœ ju¿ zbyt du¿¹ iloœæ narkotyków.\nDzienna porcja to {FCDB6D}5{C0C0C0}. Spróbuj ponownie jutro.", "Zamknij", "");
		        return 1;
		    }
	    }
		else
		{
		    if(CharacterCache[playerid][pSellDrug] > 3)
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "{C0C0C0}W tym dniu sprzeda³eœ ju¿ zbyt du¿¹ iloœæ narkotyków.\nDzienna porcja to 3. Spróbuj ponownie jutro.", "Zamknij", "");
		        return 1;
		    }
	    }
	    
	    new data[64], item_id, name[32], list_items[256];
	    mysql_query_format("SELECT `uid`, `name` FROM `fc_items` WHERE `kind` IN (%d,%d,%d) AND `ownertype` = '%d' AND `owner` = '%d' AND `value` = 1", TYPE_META, TYPE_MAR, TYPE_COCAINE, OWNER_PLAYER, CharacterCache[playerid][pUID]);
	    
	    mysql_store_result();
	    
		while(mysql_fetch_row_format(data, "|"))
		{
			sscanf(data, "p<|>ds[32]", item_id, name);
		    format(list_items, sizeof(list_items), "%s\n%d\t%s", list_items, item_id, name);
		}
		
		mysql_free_result();
	    
    	if(strlen(list_items) != 0) ShowPlayerDialog(playerid, D_DRUG_OUT, DIALOG_STYLE_LIST, " Lista dostêpnych narkotyków:", list_items, "Sprzedaj", "Zamknij");
    	else Infobox(playerid, 5, "Nie posiadasz zadnych ~g~~h~narkotykow ~w~~h~na sprzedaz.");
	}
	else if(GangInfo[uid][gangStatus] == NPC_RUN_OUT)
	{
	    GangInfo[uid][gangStatus] = NPC_FREE;
	    GangInfo[uid][gangToPlayer] = INVALID_PLAYER_ID;
	}
	else
	{
	    GangInfo[uid][gangStatus] = NPC_FREE;
	    GangInfo[uid][gangToPlayer] = INVALID_PLAYER_ID;
	    
	}
	return 1;
}