forward Oferta(playerid, playerid2, typ, cena, value1);
forward ShowPlayerOutInfo(playerid);
forward Zaakceptuj(playerid, accept);

public Oferta(playerid, playerid2, typ, cena, value1)
{
	if(SendOffer[playerid]) return Infobox(playerid, 5, "Oferta zostala wyslana, zaczekaj na reakcje klienta.");
    if(!IsPlayerConnected(playerid2))
	{
	    Infobox(playerid, 5, "Gracz nie jest podlaczony,");
		return 1;
	}
	if(!PlayerToPlayer(5.0, playerid, playerid2))
	{
	    Infobox(playerid, 5, "Aby oferowac, musisz znajdowac sie kolo gracza.");
		return 1;
	}
	if(cena < 0)
	{
	    Infobox(playerid, 5, "Cena nie moze byc mniejsza niz zero.");
		return 1;
	}
	if(CharacterCache[playerid2][pCash] < cena)
	{
	    Infobox(playerid, 5, "Gracz nie posiada wystarczajacej ilosci gotowki.");
	    return 1;
	}

	new offer_title[64], offer_name[64], offer_value[64];
	
	OfertaInfo[playerid][oType] = typ;
    OfertaInfo[playerid][oCustomer] = playerid2;
    OfertaInfo[playerid][oPrice] = cena;
    OfertaInfo[playerid][oValue1] = value1;
    OfertaInfo[playerid2][oSeller] = playerid;

	if(typ == OFFER_ITEM)
	{
	    new data[64], name[32], value_1, value2, query[256];
		format(query, sizeof(query), "SELECT `name`, `value1`, `value2` FROM `fc_items` WHERE `uid` = '%d'", value1);

		mysql_check();
		mysql_query(query);

		mysql_store_result();
		mysql_fetch_row_format(data, "|");

		sscanf(data, "p<|>s[32]dd", name, value_1, value2);
		mysql_free_result();
	
		offer_title = "Przedmiot";
		format(offer_name, sizeof(offer_name), "%s", name);
		format(offer_value, sizeof(offer_value), "(%d, %d)", value_1, value2);
	}
	if(typ == OFFER_VEHICLE)
	{
		new uid, model, color1, color2, query[256], data[64];
		format(query, sizeof(query), "SELECT `uid`, `model`, `color_1`, `color_2` FROM `fc_vehicles` WHERE `uid` = '%d'", value1);

		mysql_check();
		mysql_query(query);

		mysql_store_result();
		mysql_fetch_row_format(data, "|");

		sscanf(data, "p<|>dddd", uid, model, color1, color2);
		mysql_free_result();
	
		offer_title = "Pojazd";
		format(offer_name, sizeof(offer_name), "%s", GetVehicleModelName(model));
		format(offer_value, sizeof(offer_value), "(%d, %d)", color1, color2);
	}
	if(typ == OFFER_FUEL)
	{
		offer_title = "Tankowanie";
		format(offer_name, sizeof(offer_name), "%s", GetVehicleModelName(VehicleInfo[value1][vModel]));
		format(offer_value, sizeof(offer_value), "(%d litrow)", cena / 3);
	}
	if(typ == OFFER_REPAIR_JOB)
	{
		offer_title = "Naprawa pojazdu";
		format(offer_name, sizeof(offer_name), "%s", GetVehicleModelName(VehicleInfo[value1][vModel]));
		format(offer_value, sizeof(offer_value), "(100 sekund)");
	}
	if(typ == OFFER_ID)
	{
	    offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Dowod osobisty");
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_DRIVER)
	{
	    offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Prawo jazdy");
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_FISH)
	{
	    offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Karta rybacka");
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_PASSPORT)
	{
    	offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Paszport");
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_POLICE)
	{
    	offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Niekaralnosc");
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_MEDICAL)
	{
    	offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Metryczke");
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_LICENSE)
	{
		offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Licencja na bron");
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_REGISTER)
	{
		offer_title = "Rejestracja pojazdu";
		format(offer_name, sizeof(offer_name), "%s", GetVehicleModelName(VehicleInfo[value1][vModel]));
		format(offer_value, sizeof(offer_value), "(UID: %s)", VehicleInfo[value1][vUID]);
	}
	if(typ == OFFER_INSURANCE)
	{
		offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Ubezpieczenie");
		format(offer_value, sizeof(offer_value), "($20 / dzien)");
	}
	if(typ == OFFER_ALARM)
	{
		offer_title = "Alarm";
		format(offer_name, sizeof(offer_name), "Alarm w %s", DoorInfo[value1][dName]);
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_GATE)
 	{
	    offer_title = "Bramki";
		format(offer_name, sizeof(offer_name), "Bramki w lokalu %s", DoorInfo[value1][dName]);
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_VCARD)
	{
	    offer_title = "VCARD";
		format(offer_name, sizeof(offer_name), "Nowy kontakt w telefonie");
		format(offer_value, sizeof(offer_value), "");
	}
	if(typ == OFFER_MANDAT)
	{
		offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Mandat");
		format(offer_value, sizeof(offer_value), "($%d, %d punktow)", cena, value1);
	}
	if(typ == OFFER_PASSAGE)
	{
		offer_title = "Taxi";
		format(offer_name, sizeof(offer_name), "Przejazd taxi");
		format(offer_value, sizeof(offer_value), "($%d za 100 metrow)", cena);
	}
	if(typ == OFFER_PERMIT)
	{
		offer_title = "Dokument";
		format(offer_name, sizeof(offer_name), "Przepustka U.S Border Patrol");
		format(offer_value, sizeof(offer_value), "");
	}
	
	new string[256];
	format(string, sizeof(string), "~b~Oferta od ~w~%s ~b~~>~ %s~n~~n~Nazwa: ~w~%s ~y~~h~~h~%s~n~~g~~h~~h~Koszt:~w~ $%d~n~~n~~n~", PlayerName2(playerid), offer_title, offer_name, offer_value, cena);
	PlayerTextDrawSetString(playerid2, Offer[playerid2], string);

	PlayerTextDrawShow(playerid2, Offer[playerid2]);
	PlayerTextDrawShow(playerid2, AcceptOffer[playerid2]);
	PlayerTextDrawShow(playerid2, CrossOffer[playerid2]);
	if(typ == OFFER_ITEM || typ == OFFER_VEHICLE) PlayerTextDrawShow(playerid2, InfoOffer[playerid2]);

	SelectTextDraw(playerid2, 0xD4C598AA);
    SendClientMessageFormat(playerid, ZOLTY, "** Oferta zosta³a wys³ana graczu %s. **", PlayerName2(playerid2));
	SendOffer[playerid] = true;
    return 1;
}

public Zaakceptuj(playerid, accept)
{
	new sellerid = OfertaInfo[playerid][oSeller];
	new type = OfertaInfo[sellerid][oType];
	new cena = OfertaInfo[sellerid][oPrice];
	new value1 = OfertaInfo[sellerid][oValue1];
	new data[64], query[256], name[32], value_1, value2, kind, work, value, owner, price_id;
	
	SendOffer[sellerid] = false;
	
	format(query, sizeof(query), "SELECT `name`, `value1`, `value2`, `kind`, `work`, `value`, `owner`, `price` FROM `fc_items` WHERE `uid` = '%d'", value1);

	mysql_check();
	mysql_query(query);

	mysql_store_result();
	mysql_fetch_row_format(data, "|");
	
	sscanf(data, "p<|>s[32]ddddddd", name, value_1, value2, kind, work, value, owner, price_id);
	mysql_free_result();

	if(accept == REJECT)
	{
	    CharacterCache[playerid][pShowInfoOffer] = false;
	    CharacterCache[playerid][pShowInfoOffer] = false;
	    
		CancelOffert(playerid);
		CancelOffert(sellerid);

        SendClientMessageFormat(playerid, ZOLTY, "** Zrezygnowa³es z oferty gracza %s. **", PlayerName2(sellerid));
	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zrezygnowa³ z Twojej oferty. **", PlayerName2(playerid));
	    return 1;
	}
	if(CharacterCache[playerid][pCash] < cena)
	{
	    Infobox(playerid, 5, "Nie posiadasz tylu pieniedzy.");
	    return 1;
	}
	if(type == OFFER_ITEM)
	{
	    if(!IsPlayerItem(CharacterCache[sellerid][pUID], value1))
		{
		    CancelOffert(playerid);
		    CancelOffert(sellerid);

		    Infobox(sellerid, 5, "Brak przedmiotu o takim UID.");
		    Infobox(playerid, 5, "Brak przedmiotu o takim UID.");
		    return 1;
		}
	    if(kind == TYPE_WEAPON && value1 == CharacterCache[sellerid][pWeaponUID])
	    {
	    	new itemid = GetItemID(CharacterCache[playerid][pWeaponUID]);

            format(query, sizeof(query), "UPDATE `fc_items` SET `value2` = '%d', `used` = '0' WHERE `uid` = '%d' LIMIT 1", CharacterCache[sellerid][pWeaponAmmo], CharacterCache[sellerid][pWeaponUID]);
            mysql_check(); mysql_query(query);

            ResetPlayerWeapons(sellerid);

            ItemInfo[itemid][iUsed] = 0;
            ItemInfo[itemid][iValue2] = CharacterCache[sellerid][pWeaponAmmo];

            CharacterCache[sellerid][pWeaponUID]    = 0;
            CharacterCache[sellerid][pWeaponID]     = 0;
            CharacterCache[sellerid][pWeaponAmmo]   = 0;
            CharacterCache[sellerid][pGetWeapon]    = false;
	    }
		
	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ ofertê. Przedmiot %s zosta³ sprzedany. **", PlayerName2(playerid), name, value1, cena);

		format(query, sizeof(query), "UPDATE `fc_items` SET `owner` = '%d', `ownertype` = '%d' WHERE `uid` = '%d'", CharacterCache[playerid][pUID], OWNER_PLAYER, value1);
        mysql_check();
		mysql_query(query);
	
		GivePlayerCash(playerid, -cena);
	    GivePlayerCash(sellerid, cena);
	    
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
	    SavePlayerStats(sellerid, SAVE_PLAYER_BASIC);
	}
	if(type == OFFER_VEHICLE)
	{
	    GivePlayerCash(playerid, -cena);
	    GivePlayerCash(sellerid, cena);
	    
	    format(query, sizeof(query), "UPDATE `fc_vehicles` SET `owner` = '%d', `ownertype` = '%d' WHERE `uid` = '%d'", CharacterCache[playerid][pUID], OWNER_PLAYER, value1);
        mysql_check();
		mysql_query(query);
		
	    SaveVehicle(value1, SAVE_VEH_THINGS);
	    
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
	    SavePlayerStats(sellerid, SAVE_PLAYER_BASIC);
	    
	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte. **", PlayerName2(playerid));
	}
	if(type == OFFER_FUEL)
	{
	    GivePlayerCash(playerid, -cena);
	    GivePlayerCash(sellerid, floatround(cena / 3));
	    
	    VehicleInfo[value1][vFuel] = floatadd(VehicleInfo[value1][vFuel], floatround(cena / 3));
		SaveVehicle(value1, SAVE_VEH_COUNT);
	
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
	    SavePlayerStats(sellerid, SAVE_PLAYER_BASIC);
	    
	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte paliwa. **", PlayerName2(playerid));
	}
	if(type == OFFER_REPAIR_JOB)
	{
	    SetPVarInt(sellerid, "RepairPlayerID", playerid);
	    SetPVarInt(sellerid, "RepairPrice", floatround(cena / 3));
	    
	    CharacterCache[sellerid][pRepair] = 100;
	    CharacterCache[sellerid][pRepairVehicle] = value1;
	    
	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte naprawy. **", PlayerName2(playerid));
	}
	if(type == OFFER_ID)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
	    
	    GroupData[GetGroupKind(GROUP_GOV)][Cash] += cena;
	    SaveGroup(GetGroupKind(GROUP_GOV));
	    
	    CharacterCache[playerid][pDocument] += DOC_ID;
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);
	    
	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte dowodu osobistego. **", PlayerName2(playerid));
	}
	if(type == OFFER_DRIVER)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);

	    GroupData[GetGroupKind(GROUP_GOV)][Cash] += cena;
	    SaveGroup(GetGroupKind(GROUP_GOV));

	    CharacterCache[playerid][pDocument] += DOC_DRIVER;
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);

	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte prawa jazdy. **", PlayerName2(playerid));
	}
	if(type == OFFER_FISH)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);

	    GroupData[GetGroupKind(GROUP_GOV)][Cash] += cena;
	    SaveGroup(GetGroupKind(GROUP_GOV));

	    CharacterCache[playerid][pDocument] += DOC_FISH;
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);

	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte karty rybackiej. **", PlayerName2(playerid));
	}
	if(type == OFFER_PASSPORT)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);

	    GroupData[GetGroupKind(GROUP_GOV)][Cash] += cena;
	    SaveGroup(GetGroupKind(GROUP_GOV));

	    CharacterCache[playerid][pDocument] += DOC_PASSPORT;
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);

	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte paszportu. **", PlayerName2(playerid));
	}
	if(type == OFFER_POLICE)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);

	    GroupData[GetGroupKind(GROUP_GOV)][Cash] += cena;
	    SaveGroup(GetGroupKind(GROUP_GOV));

	    CharacterCache[playerid][pDocument] += DOC_POLICE;
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);

	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte niekaralnoœci. **", PlayerName2(playerid));
	}
	if(type == OFFER_MEDICAL)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);

	    GroupData[GetGroupKind(GROUP_GOV)][Cash] += cena;
	    SaveGroup(GetGroupKind(GROUP_GOV));

	    CharacterCache[playerid][pDocument] += DOC_MEDICAL;
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);

	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte metryczki. **", PlayerName2(playerid));
	}
	if(type == OFFER_REGISTER)
	{
		GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
	    
	    GroupData[GetGroupKind(GROUP_GOV)][Cash] += cena;
	    SaveGroup(GetGroupKind(GROUP_GOV));
	    
	    format(VehicleInfo[value1][vRegister], 12, "SA-%d", VehicleInfo[value1][vUID]);
	    SaveVehicle(value1, SAVE_VEH_THINGS);
	    
	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte rejestracji pojazdu. **", PlayerName2(playerid));
	}
	if(type == OFFER_LICENSE)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);

	    GroupData[GetGroupKind(GROUP_GOV)][Cash] += cena;
	    SaveGroup(GetGroupKind(GROUP_GOV));

	    CharacterCache[playerid][pDocument] += DOC_LICENSE;
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);

	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte licencji na broñ. **", PlayerName2(playerid));
	}
	if(type == OFFER_INSURANCE)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
	    
	    CharacterCache[playerid][pDocument] += DOC_INSURANCE;
	    
	    CharacterCache[playerid][pInsurance] += 20;
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);

        SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte ubezpieczenia. **", PlayerName2(playerid));
	}
	if(type == OFFER_ALARM)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
	    
	    DoorInfo[value1][dValue] += DOOR_ALARM;
	    
	    new groupid = IsPlayerKindGroup(sellerid, GROUP_SECURITY);
	    GroupData[groupid][Cash] += cena;
	    
	    SaveDoors(value1);
	    SaveGroup(groupid);
	    
	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte alarmu w drzwiach. **", PlayerName2(playerid));
	}
	if(type == OFFER_GATE)
	{
	    GivePlayerCash(playerid, -cena);
	    SavePlayerStats(playerid, SAVE_PLAYER_BASIC);

	    DoorInfo[value1][dValue] += DOOR_GATE;

	    new groupid = IsPlayerKindGroup(sellerid, GROUP_SECURITY);
	    GroupData[groupid][Cash] += cena;

	    SaveDoors(value1);
	    SaveGroup(groupid);

	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte bramek w drzwiach. **", PlayerName2(playerid));
	}
	if(type == OFFER_VCARD)
	{
	    new str[64];
	    new itemid_playerid = GetItemID(CharacterCache[playerid][pPhone]);
	    new itemid_playerid2 = GetItemID(CharacterCache[sellerid][pPhone]);
	    
	    format(query, sizeof(query), "INSERT INTO `fc_vcards` VALUES (NULL, '%s', '%d', '%d')", PlayerName2(sellerid), ItemInfo[itemid_playerid2][iValue1], ItemInfo[itemid_playerid][iValue1]);
	    
	    mysql_check();
	    mysql_query(query);
	    
	    format(query, sizeof(query), "INSERT INTO `fc_vcards` VALUES (NULL, '%s', '%d', '%d')", PlayerName2(playerid), ItemInfo[itemid_playerid][iValue1], ItemInfo[itemid_playerid2][iValue1]);

	    mysql_check();
	    mysql_query(query);
	    
	    format(str, sizeof(str), "zaoferowa³ vCard %s.", PlayerName2(playerid));
	    cmd_me(sellerid, str);
	    
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nowy kontakt zosta³ dodany do listy.\nU¿yj /tel aby zarz¹dzaæ kontaktami.", "Zamknij", "");
	    ShowPlayerDialog(sellerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nowy kontakt zosta³ dodany do listy.\nU¿yj /tel aby zarz¹dzaæ kontaktami.", "Zamknij", "");
	}
	if(type == OFFER_MANDAT)
	{
	    new groupid = GetGroupKind(GROUP_PD);
	    
	    GivePlayerCash(playerid, -cena);
	    CharacterCache[playerid][pPenaltyPoints] += value1;
	    
	    GroupData[groupid][Cash] += floatround(cena / 2);
	    SaveGroup(groupid);
	    
	    GroupData[GetGroupKind(GROUP_GOV)][Cash] += floatround(cena / 2);
	    SaveGroup(GetGroupKind(GROUP_GOV));
	    
	    if(CharacterCache[playerid][pPenaltyPoints] >= 24)
	    {
	        CharacterCache[playerid][pPenaltyPoints] = 0;
	        CharacterCache[playerid][pDocument] -= DOC_DRIVER;
	        
	        SendClientMessage(playerid, 0xCACACAFF, "** Prawo jazdy zosta³o Ci zabrane z powodu zbyt du¿ej iloœci punktów. **");
	        SendClientMessageFormat(sellerid, 0xCACACAFF, "** %s zosta³o zabrane prawo jazdy z powodu zbyt du¿ej iloœci punktów. **", PlayerName2(playerid));
	    }
	    
	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte mandatu. **", PlayerName2(playerid));
	}
	if(type == OFFER_PASSAGE)
	{
	    CharacterCache[sellerid][pTaxiPassenger] = playerid;
	    CharacterCache[sellerid][pTaxiGroup] = IsPermGroupTypeOnType(sellerid, GROUP_TAXI);

		CharacterCache[playerid][pTaxiVeh] = value1;
		CharacterCache[playerid][pTaxiPrice] = cena;

		SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte przejazdu. **", PlayerName2(playerid));
	}
	if(type == OFFER_PERMIT)
	{
	    CharacterCache[playerid][pPermit] = gettime() + 900;
	    SavePlayerStats(playerid, SAVE_PLAYER_SETTING);

	    SendClientMessageFormat(sellerid, ZOLTY, "** Gracz %s zaakceptowa³ Twoj¹ oferte przepustki. **", PlayerName2(playerid));
	}
	
	if(type != OFFER_VCARD) SendClientMessageFormat(playerid, ZOLTY, "** Zaakceptowa³eœ oferte gracza %s. **", PlayerName2(sellerid));

	CancelOffert(playerid);
	CancelOffert(sellerid);
    return 1;
}

public ShowPlayerOutInfo(playerid)
{
    new sellerid = OfertaInfo[playerid][oSeller];
 	new type_id = OfertaInfo[sellerid][oType], info_td[512];

	if(type_id == OFFER_ITEM)
	{
	    new uid, kind, value1, value2, name[32], data[256], query[256];

    	format(query, sizeof(query), "SELECT `uid`, `kind`, `value1`, `value2`, `name` FROM `fc_items` WHERE `uid` = '%d'", OfertaInfo[sellerid][oValue1]);
    	mysql_check(); mysql_query(query);

		mysql_store_result();
		mysql_fetch_row_format(data, "|");

	 	sscanf(data, "p<|>dddds[32]", uid, kind, value1, value2, name);
	 	mysql_free_result();

        if(kind == TYPE_WEAPON) PlayerTextDrawSetPreviewModel(playerid, ModelOffer[playerid], WeaponModel[value1]);
        else PlayerTextDrawSetPreviewModel(playerid, ModelOffer[playerid], ItemTypeInfo[kind][iTypeObjModel]);

	    format(info_td, sizeof(info_td), "~n~~y~UID:~w~ %d~n~~n~~y~Typ:~w~ %d~n~~y~Wartosc #1:~w~ %d~n~~n~~y~Wartosc #2:~w~ %d~n~~n~~y~Nazwa:~w~ %s~n~~n~~n~", uid, ItemTypeInfo[kind][iTypeName], value1, value2, name);
	    PlayerTextDrawSetString(playerid, InfoBoxOffer[playerid], info_td);

	    if(!CharacterCache[playerid][pShowInfoOffer])
	    {
	    	PlayerTextDrawShow(playerid, InfoBoxOffer[playerid]);
	    	PlayerTextDrawShow(playerid, ModelOffer[playerid]);
		}
		else
		{
			PlayerTextDrawHide(playerid, InfoBoxOffer[playerid]);
			PlayerTextDrawHide(playerid, ModelOffer[playerid]);
		}
	}

	if(type_id == OFFER_VEHICLE)
	{
	    new uid, model, color1, color2, Float:fuel, Float:hp, data[256], query[256];

    	format(query, sizeof(query), "SELECT `uid`, `model`, `color_1`, `color_2`, `fuel`, `hp` FROM `fc_vehicles` WHERE `uid` = '%d'", OfertaInfo[sellerid][oValue1]);
		mysql_check(); mysql_query(query);

		mysql_store_result();
		mysql_fetch_row_format(data, "|");

	 	sscanf(data, "p<|>ddddff", uid, model, color1, color2, fuel, hp);
	 	mysql_free_result();

	    PlayerTextDrawSetPreviewModel(playerid, ModelOffer[playerid], model);
	    PlayerTextDrawSetPreviewVehCol(playerid, ModelOffer[playerid], color1, color2);

	    format(info_td, sizeof(info_td), "~n~~y~UID:~w~ %d~n~~n~~y~Model:~w~ %d~n~~y~Kolory:~w~ %d:%d~n~~n~~y~Paliwo:~w~ %0.1f/%0.1fL~n~~y~Rodzaj paliwa:~w~ Benzyna~n~~n~~y~Stan techniczny:~w~ %0.1f HP~n~~n~", uid, model, color1, color2, fuel, GetVehicleMaxFuel(model), hp);
	    PlayerTextDrawSetString(playerid, InfoBoxOffer[playerid], info_td);

	    if(!CharacterCache[playerid][pShowInfoOffer])
	    {
	    	PlayerTextDrawShow(playerid, InfoBoxOffer[playerid]);
			PlayerTextDrawShow(playerid, ModelOffer[playerid]);
		}
		else
		{
			PlayerTextDrawHide(playerid, InfoBoxOffer[playerid]);
			PlayerTextDrawHide(playerid, ModelOffer[playerid]);
		}
	}

	if(CharacterCache[playerid][pShowInfoOffer]) CharacterCache[playerid][pShowInfoOffer] = false;
	else CharacterCache[playerid][pShowInfoOffer] = true;

	SelectTextDraw(playerid, 0xD4C598AA);
}