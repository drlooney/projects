/*
	CMD:cicho
	CMD:krzyk
	CMD:l
	CMD:b
	CMD:w
	CMD:re
	CMD:oferuj
	CMD:akceptuj
	CMD:pokaz
	CMD:telefon
	CMD:sms
	CMD:call
	CMD:odbierz
	CMD:zakoncz
	CMD:alarm
	CMD:bank
	CMD:zadanie
	CMD:paczka
	CMD:opis
	CMD:login
	CMD:plac
	CMD:bus
	CMD:tankuj
	CMD:dom
	CMD:przejazd
	CMD:wyscig
	CMD:pomoc
	CMD:tog
	CMD:me
	CMD:do
	CMD:report
	CMD:sprobuj
	CMD:stats
	CMD:silnik
	CMD:przedmiot
	CMD:grupa
	CMD:pojazd
	CMD:drzwi
	CMD:tc
	CMD:tsel
	CMD:tsave
	CMD:tdel
	CMD:mc
	CMD:msel
	CMD:msave
	CMD:mdel
	CMD:mrx
	CMD:mry
	CMD:mrz
	CMD:mgate
	CMD:mmat
	CMD:brama
	CMD:admins
*/

CMD:c(playerid, params[])
{
    if(CharacterCache[playerid][pBW])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ teraz z tej komendy.", "Zamknij", "");
        return 1;
    }
    if(CharacterCache[playerid][pKnebel])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ teraz z tej komendy.", "Zamknij", "");
        return 1;
    }
    new text[128], string[256];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /cicho [tekst]", "Zamknij", "");
        return 1;
    }
	else
	{
		text[0] = chrtoupper(text[0]);

		if(strlen(text) < 78)
		{
			format(string, sizeof(string), "%s szepcze: %s", PlayerName2(playerid), text);
			ProxDetector(5.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		}
		else
		{
			new pos = strfind(text, " ", true, strlen(text) / 2);
			if(pos != -1)
			{
				new text2[64];

				strmid(text2, text, pos + 1, strlen(text));
				strdel(text, pos, strlen(text));

				format(string, sizeof(string), "%s szepcze: %s...", PlayerName2(playerid), text);
				ProxDetector(5.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

				format(string, sizeof(string), "            ...%s", text2);
				ProxDetector(5.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
			}
		}
	}
    return 1;
}
CMD:cicho(playerid, params[]) return cmd_c(playerid, params);

CMD:k(playerid, params[])
{
    if(CharacterCache[playerid][pBW])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ teraz z tej komendy.", "Zamknij", "");
        return 1;
    }
    if(CharacterCache[playerid][pKnebel])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ teraz z tej komendy.", "Zamknij", "");
        return 1;
    }
    new text[128], string[256];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /k [tekst]", "Zamknij", "");
        return 1;
    }
	else
	{
		text[0] = chrtoupper(text[0]);

		if(strlen(text) < 78)
		{
			format(string, sizeof(string), "%s krzyczy: %s!!", PlayerName2(playerid), text);
			ProxDetector(25.0, playerid, string, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2);
		}
		else
		{
			new pos = strfind(text, " ", true, strlen(text) / 2);
			if(pos != -1)
			{
				new text2[64];

				strmid(text2, text, pos + 1, strlen(text));
				strdel(text, pos, strlen(text));

				format(string, sizeof(string), "%s krzyczy: %s...", PlayerName2(playerid), text);
				ProxDetector(25.0, playerid, string, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2);

				format(string, sizeof(string), "            ...%s!!", text2);
				ProxDetector(25.0, playerid, string, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2);
			}
		}
		
		if(!(CharacterCache[playerid][pOption] & OPTION_KRZYK))
		{
			ApplyAnimation(playerid, "ON_LOOKERS", "shout_01", 4.0, 0, 0, 0, 0, 0);
		}
	}
    return 1;
}
CMD:s(playerid, params[])       return cmd_k(playerid, params);
CMD:krzycz(playerid, params[])  return cmd_k(playerid, params);
CMD:krzyk(playerid, params[])   return cmd_k(playerid, params);

CMD:l(playerid, params[])
{
    if(CharacterCache[playerid][pBW])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ teraz z tej komendy.", "Zamknij", "");
        return 1;
    }
    if(CharacterCache[playerid][pKnebel])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ teraz z tej komendy.", "Zamknij", "");
        return 1;
    }
    new text[128], string[256];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /l [tekst]", "Zamknij", "");
        return 1;
    }
    text[0] = chrtoupper(text[0]);

    if(strlen(text) < 78)
    {
        format(string, sizeof(string), "%s mówi: %s", PlayerName2(playerid), text);
        ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
    }
    else
    {
        new pos = strfind(text, " ", true, strlen(text) / 2);
        if(pos != -1)
        {
            new text2[64];

            strmid(text2, text, pos + 1, strlen(text));
            strdel(text, pos, strlen(text));

            format(string, sizeof(string), "%s mówi: %s...", PlayerName2(playerid), text);
            ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

            format(string, sizeof(string), "            ...%s", text2);
            ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
        }
    }
    return 1;
}

CMD:b(playerid, params[])
{
    if(CharacterCache[playerid][pBW])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ teraz z tej komendy.", "Zamknij", "");
        return 1;
    }
    if(CharacterCache[playerid][pAdminDuty])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Znajduj¹c siê na s³u¿bie administracyjnej nie jesteœ zmuszony do pisania za pomoc¹ /b.\nFunkcje administratora uprawniaj¹ Ciê do pisania na czacie g³ównym.", "Zamknij", "");
        return 1;
    }
    
    new text[128], string[256];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /b [tekst]", "Zamknij", "");
        return 1;
    }
    else
    {
	    text[0] = chrtoupper(text[0]);

	    if(strlen(text) < 78)
	    {
	        format(string, sizeof(string), "(( %s: %s ))", PlayerName2(playerid), text);
	        ProxDetector(10.0, playerid, string, COLOR_GREY, COLOR_GREY, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	    }
	    else
	    {
	        new pos = strfind(text, " ", true, strlen(text) / 2);
	        if(pos != -1)
	        {
	            new text2[64];

	            strmid(text2, text, pos + 1, strlen(text));
	            strdel(text, pos, strlen(text));

	            format(string, sizeof(string), "(( %s: %s...", PlayerName2(playerid), text);
	            ProxDetector(10.0, playerid, string, COLOR_GREY, COLOR_GREY, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

	            format(string, sizeof(string), "...%s ))", text2);
	            ProxDetector(10.0, playerid, string, COLOR_GREY, COLOR_GREY, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	        }
	    }
    }
    return 1;
}

CMD:w(playerid, params[])
{
    new giveplayer_id, text[128], string[256];
    if(sscanf(params, "us[128]", giveplayer_id, text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /w [ID gracza] [wiadomoœæ]", "Zamknij", "");
        return 1;
    }
    else
    {
	    if(giveplayer_id == playerid)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz wysy³aæ prywatnej wiadomoœci do siebie.", "Zamknij", "");
	        return 1;
	    }
	    if(!Logged[giveplayer_id])
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
	        return 1;
	    }
	    if(CharacterCache[giveplayer_id][pAdminDuty] && !(CharacterCache[giveplayer_id][pOption] & OPTION_TOKEN))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Ten gracz jest administratorem na s³u¿bie, aby zg³osiæ siê z swoj¹ spraw¹ u¿yj komendy /report.", "Zamknij", "");
	        return 1;
	    }
	    if(CharacterCache[giveplayer_id][pTog] & TOG_PW)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Ten gracz ma wy³¹czone otrzymywanie prywatnych wiadomoœci.", "Zamknij", "");
	        return 1;
	    }
	    if(CharacterCache[playerid][pBW] && !PlayerToPlayer(25.0, playerid, giveplayer_id) && CharacterCache[giveplayer_id][pAdmin] == 0)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Podczas stanu nieprzytomnoœci, wiadomoœci prywatne mo¿esz wysy³aæ na okreœlon¹ odleg³oœæ.", "Zamknij", "");
	        return 1;
	    }
	    if(CharacterCache[giveplayer_id][pKnebel] || CharacterCache[giveplayer_id][pWorek] || CharacterCache[playerid][pKnebel] || CharacterCache[playerid][pWorek])
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Ty lub gracz do którego chcesz wys³aæ wiadomoœæ aktualnie s¹ niedostêpni.\nOznacza to, ¿e znajduj¹ siê w grze jednak prowadz¹ akcjê z innymi osobami.\nKomunikacja OOC w takim wypadku zosta³a zabroniona.", "Zamknij", "");
	        return 1;
	    }

		if(CharacterCache[giveplayer_id][pOption] & OPTION_TOKEN && CharacterCache[giveplayer_id][pAdminDuty])
		{
			new key[32];
		    new val = random(500);
		    
		    format(key, sizeof(key), "%s%s%s", dechex(val), dechex(val + val), dechex(val + val + 2));
		    
		    text[0] = chrtoupper(text[0]);
		    
		    CharacterCache[playerid][pKey] = key;
		    CharacterCache[playerid][pPrivTo] = giveplayer_id;
		    CharacterCache[playerid][pPrivMess] = text;
		    
		    format(string, sizeof(string), "Administrator bêd¹cy na s³u¿bie wymusi³ przepisanie tokena.\nPrzepisz token administracyjny w pole poni¿ej, aby napisaæ wiadomoœæ.\n\n%s\n\nPamietaj, ¿e wiadomoœæ musi byæ sensowna i treœciwa.", key);
		    ShowPlayerDialog(playerid, D_PRIV_MSG, DIALOG_STYLE_INPUT, "Wiadomoœæ do administratora", string, "Wyœlij", "Zamknij");
		}
		else
		{
		    text[0] = chrtoupper(text[0]);

			if(CharacterCache[playerid][pAdmin] > 0 && CharacterCache[playerid][pAdmin] < 6 && CharacterCache[playerid][pAdminDuty])
			{
		    	format(string, sizeof(string), "(( « Support %s : %s ))", AssCode(playerid), text);
		    }
		    else
		    {
		    	format(string, sizeof(string), "(( « %s [%d]: %s ))", PlayerName2(playerid), playerid, text);
		    }

		    SendClientMessage(giveplayer_id, COLOR_GOT_PW, string);

			if(CharacterCache[giveplayer_id][pAdmin] > 0 && CharacterCache[giveplayer_id][pAdmin] < 6 && CharacterCache[giveplayer_id][pAdminDuty])
			{
				format(string, sizeof(string), "(( » Support %s : %s ))", AssCode(giveplayer_id), text);
			}
			else
			{
		    	format(string, sizeof(string), "(( » %s [%d]: %s ))", PlayerName2(giveplayer_id), giveplayer_id, text);
		    }

		    SendClientMessage(playerid, COLOR_SEND_PW, string);

		    CharacterCache[giveplayer_id][pLastW] = playerid;
			CharacterCache[playerid][pLastW] = giveplayer_id;

			PlayerPlaySound(giveplayer_id, 1057, 0, 0, 0);

		    if(CharacterCache[playerid][pTog] & TOG_PW)
		    {
		        Infobox(playerid, 3, "Pamietaj, ze masz ~r~wylaczona ~w~mozliwosc otrzymywania prywatnych ~y~wiadomosci~w~.");
		        return 1;
		    }
		    if(CharacterCache[playerid][pAFK] <= 0)
		    {
		    	Infobox(playerid, 3, "Gracz do ktorego chcesz wyslac wiadomosc jest aktualnie ~g~AFK~w~~h~.");
		        return 1;
		    }
	    }
    }
    return 1;
}
CMD:pm(playerid, params[]) return cmd_w(playerid, params);
CMD:wiadomosc(playerid, params[]) return cmd_w(playerid, params);

CMD:re(playerid, params[])
{
    if(CharacterCache[playerid][pLastW] == INVALID_PLAYER_ID)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Z nikim nie pisa³eœ przez ostatni czas.", "Zamknij", "");
        return 1;
    }
    new text[128], string[256];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /re [wiadomoœæ]", "Zamknij", "");
        return 1;
    }

    format(string, sizeof(string), "%d %s", CharacterCache[playerid][pLastW], text);
    cmd_w(playerid, string);
    return 1;
}

CMD:oferuj(playerid, params[])
{
	new	comm1[32], comm2[128];
	if(sscanf(params, "s[32]S()[128]", comm1, comm2))
	{
	    new title[1024], string[1024];
	    
	    format(string, sizeof(string), "%s\n» akceptuj", string);
	    format(string, sizeof(string), "%s\n» odrzuæ", string);
	    format(string, sizeof(string), "%s\n» przedmiot", string);
     	format(string, sizeof(string), "%s\n» pojazd", string);
     	format(string, sizeof(string), "%s\n» vcard", string);
     	
     	// Pomocnik stacji
     	if(CharacterCache[playerid][pJob]) format(string, sizeof(string), "%s\n» tankowanie", string);
     	if(CharacterCache[playerid][pJob]) format(string, sizeof(string), "%s\n» naprawa", string);
     	
     	// Urzêdnik
     	if(IsPermGroupTypeOnType(playerid, GROUP_GOV)) format(string, sizeof(string), "%s\n» dowód", string);
     	if(IsPermGroupTypeOnType(playerid, GROUP_GOV)) format(string, sizeof(string), "%s\n» prawko", string);
     	if(IsPermGroupTypeOnType(playerid, GROUP_GOV)) format(string, sizeof(string), "%s\n» karta", string);
     	if(IsPermGroupTypeOnType(playerid, GROUP_GOV)) format(string, sizeof(string), "%s\n» rejestracja", string);
     	if(IsPermGroupTypeOnType(playerid, GROUP_GOV)) format(string, sizeof(string), "%s\n» paszport", string);
     	if(IsPermGroupTypeOnType(playerid, GROUP_GOV)) format(string, sizeof(string), "%s\n» ubezpieczenie", string);
     	
     	// Police Department
     	if(IsPermGroupTypeOnType(playerid, GROUP_PD)) format(string, sizeof(string), "%s\n» licencje", string);
     	if(IsPermGroupTypeOnType(playerid, GROUP_PD)) format(string, sizeof(string), "%s\n» niekaralnoœci", string);
     	if(IsPermGroupTypeOnType(playerid, GROUP_PD)) format(string, sizeof(string), "%s\n» mandat", string);
     	
     	// Medyk
     	if(IsPermGroupTypeOnType(playerid, GROUP_MC)) format(string, sizeof(string), "%s\n» metryczka", string);
     	
     	// Ochrona
     	if(IsPermGroupTypeOnType(playerid, GROUP_SECURITY)) format(string, sizeof(string), "%s\n» alarm", string);
        if(IsPermGroupTypeOnType(playerid, GROUP_SECURITY)) format(string, sizeof(string), "%s\n» bramki", string);
        
        // Taxi
        if(IsPermGroupTypeOnType(playerid, GROUP_TAXI)) format(string, sizeof(string), "%s\n» przejazd", string);
        
        // Stra¿ graniczna
        if(IsPermGroupTypeOnType(playerid, GROUP_BORDER)) format(string, sizeof(string), "%s\n» przepustka", string);

     	format(title, sizeof(title), "U¿yj: /o(feruj) [parametr]\n%s", string);
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", title, "Zamknij", "");
		return 1;
	}
	else if(!strcmp(comm1, "akceptuj", true))
	{
	    if(OfertaInfo[playerid][oSeller] == -1)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aktualnie nie posiadasz dostêpnej ¿adnej oferty.", "Zamknij", "");
	        return 1;
	    }

	    Zaakceptuj(playerid, ACCEPT);
     	CancelSelectTextDraw(playerid);
	}
	else if(!strcmp(comm1, "odrzuæ", true) || !strcmp(comm1, "odrzuc", true))
	{
	    if(OfertaInfo[playerid][oSeller] == -1)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aktualnie nie posiadasz dostêpnej ¿adnej oferty.", "Zamknij", "");
	        return 1;
	    }

	    Zaakceptuj(playerid, REJECT);
     	CancelSelectTextDraw(playerid);
	}
	else if(!strcmp(comm1,"przedmiot",true))
	{
	    new cena;
		if(sscanf(comm2, "d", cena))
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) przedmiot [cena]", "Zamknij", "");
			return 1;
		}
		else
		{
			new data[128], list_items[1024], query[256];
    		new item_uid, item_name[32], item_value1, item_value2, item_use;

			format(query, sizeof(query), "SELECT `uid`, `name`, `value1`, `value2` FROM `fc_items` WHERE `used` = 0 AND `owner` = '%d' AND `ownertype` = '%d'", CharacterCache[playerid][pUID], OWNER_PLAYER);
		    mysql_check(); mysql_query(query);

		    mysql_store_result();

		    while(mysql_fetch_row_format(data, "|"))
		    {
		        sscanf(data, "p<|>ds[32]ddd", item_uid, item_name, item_value1, item_value2, item_use);

		        format(list_items, sizeof(list_items), "%s\n{000000}%d\t%d\t%d\t{878A87}%s", list_items, item_uid, item_value1, item_value2, item_name);
		    }
		    mysql_free_result();
		    
		    SetPVarInt(playerid, "OfferItemCash", cena);

			if(strlen(list_items) != 0) ShowPlayerDialog(playerid, D_OFFER_ITEMS, DIALOG_STYLE_LIST, "Oferta przedmiotu", list_items, "Oferuj", "Zamknij");
			else Infobox(playerid, 5, "Nie posiadasz ~g~~h~zadnych~w~~h~ przedmiotow w ekwipunku.");
		}
	}
	else if(!strcmp(comm1,"pojazd",true))
	{
 		new cena;
		if(sscanf(comm2, "d", cena))
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) pojazd [cena]", "Zamknij", "");
			return 1;
		}
		else
		{
		    new uid, model, strx[512], data[256], list, query[256];
            format(query, sizeof(query), "SELECT `uid`, `model` FROM `fc_vehicles` WHERE `ownertype` = '%d' AND `owner` = '%d'", OWNER_PLAYER, CharacterCache[playerid][pUID]);
            mysql_check(); mysql_query(query);

            mysql_store_result();

            while(mysql_fetch_row_format(data, "|"))
            {
                list ++;
                sscanf(data, "p<|>dd", uid, model);

                format(strx, sizeof strx, "%s\n%d\t\t%s", strx, uid, GetVehicleModelName(model));
            }
            mysql_free_result();
            
			SetPVarInt(playerid, "OfferVehicleCash", cena);
			
			if(strlen(strx) != 0) ShowPlayerDialog(playerid, D_OFFER_VEHICLES, DIALOG_STYLE_LIST, "Oferta pojazdu", strx, "Oferuj", "Zamknij");
			else Infobox(playerid, 5, "Nie posiadasz ~g~~h~zadnych~w~~h~ pojazdow.");
		}
	}
	else if(!strcmp(comm1, "tankowanie", true))
	{
		if(!CharacterCache[playerid][pDutyJob])
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Musisz znajdowaæ siê na s³u¿bie w pracy pomocnika stacji.\nU¿yj do tego komendy /duty p(raca).", "Zamknij", "");
		    return 1;
	    }
	    
	    new fuel;
		if(sscanf(comm2, "d", fuel))
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) tankowanie [paliwo (litry)]", "Zamknij", "");
			return 1;
		}
		else
		{
		    new vehicleid = GetClosestVehicle(playerid);
		    new vehid = GetVehicleUID(vehicleid);
		    new giveplayer_id = GetVehicleDriver(vehicleid);
		    
			if(vehid == INVALID_VEHICLE_ID)
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znaleziono w pobli¿u ¿adnego pojazdu.", "Zamknij", "");
			    return 1;
			}
			if(fuel < 1)
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona wartoœæ paliwa jest nieprawid³owa.", "Zamknij", "");
			    return 1;
			}
			if(fuel + VehicleInfo[vehid][vFuel] > GetVehicleMaxFuel(VehicleInfo[vehid][vModel]))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Iloœæ paliwa, któr¹ chcesz zatankowaæ nie zmieœci siê w pojeŸdzie.", "Zamknij", "");
			    return 1;
			}
			if(!Logged[giveplayer_id] || CharacterCache[giveplayer_id][pStatus] & STATUS_AFK)
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz znajduj¹cy siê w pojeŸdzie nie jest dostêpny lub jest AFK.", "Zamknij", "");
			    return 1;
			}
			if(CharacterCache[giveplayer_id][pCash] < (fuel * SettingInfo[sFuel]))
   			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Kierowca nie posiada takiej iloœci gotówki, aby zatankowaæ pojazd.", "Zamknij", "");
			    return 1;
			}
			if(!IsOwnerVehicle(giveplayer_id, vehid))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz znajduj¹cy siê w pojeŸdzie nie posiada uprawnieñ do tego pojazdu.", "Zamknij", "");
			    return 1;
			}
			
			Oferta(playerid, giveplayer_id, OFFER_FUEL, (fuel * SettingInfo[sFuel]), vehid);
		}
	}
	else if(!strcmp(comm1, "naprawa", true))
	{
	    if(!CharacterCache[playerid][pDutyJob])
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Musisz znajdowaæ siê na s³u¿bie w pracy pomocnika stacji.\nU¿yj do tego komendy /duty p(raca).", "Zamknij", "");
		    return 1;
	    }
	    
		new cash;
		if(sscanf(comm2, "d", cash))
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) naprawa [robocizna (max. $150)]", "Zamknij", "");
			return 1;
		}
		else
		{
		    new vehicleid = GetClosestVehicle(playerid);
		    new vehid = GetVehicleUID(vehicleid);
		    new giveplayer_id = GetVehicleDriver(vehicleid);
		    
			if(vehid == INVALID_VEHICLE_ID)
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znaleziono w pobli¿u ¿adnego pojazdu.", "Zamknij", "");
			    return 1;
			}
			if(cash > 150 || cash < 1)
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona cena  jest nieprawid³owa.", "Zamknij", "");
			    return 1;
			}
			if(VehicleInfo[vehid][vHP] == 1000 || VehicleInfo[vehid][vHP] < 850)
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Pojazd nie jest w stanie zniszczenia lub zosta³ zbyt mocno zniszczony.\nUdaj siê do warsztatu samochodowego, aby go naprawiæ.", "Zamknij", "");
			    return 1;
			}
			if(!Logged[giveplayer_id] || CharacterCache[giveplayer_id][pStatus] & STATUS_AFK)
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz znajduj¹cy siê w pojeŸdzie nie jest dostêpny lub jest AFK.", "Zamknij", "");
			    return 1;
			}
			if(!IsOwnerVehicle(giveplayer_id, vehid))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz znajduj¹cy siê w pojeŸdzie nie posiada uprawnieñ do tego pojazdu.", "Zamknij", "");
			    return 1;
			}
			
			new Float:health = 1000 - VehicleInfo[vehid][vHP];
			new price = floatround(health / 2);
			
			if(CharacterCache[giveplayer_id][pCash] < (price + cash))
   			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Kierowca nie posiada takiej iloœci gotówki, aby zatankowaæ pojazd.", "Zamknij", "");
			    return 1;
			}

			Oferta(playerid, giveplayer_id, OFFER_REPAIR_JOB, (price + cash), vehid);
		}
	}
	else if(!strcmp(comm1, "dowód", true) || !strcmp(comm1, "dowod", true))
	{
	    new doorid = PlayerDoor[playerid];
	    if(GroupData[DoorInfo[doorid][dOwner]][Kind] != GROUP_GOV)
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w urzêdzie San Fierro Government.", "Zamknij", "");
		    return 1;
	    }
	    if(!IsPermGroupTypeOnType(playerid, GROUP_GOV))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wydawania dokumentów - dowodu.", "Zamknij", "");
		    return 1;
	    }
	    
	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) dowód [ID gracza]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(CharacterCache[playerid2][pCash] < SettingInfo[sDocID])
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie.", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(CharacterCache[playerid2][pDocument] & DOC_ID)
		 	{
		 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient posiada ju¿ dowód osobisty.", "Zamknij", "");
			    return 1;
		 	}
		 	
		 	Oferta(playerid, playerid2, OFFER_ID, SettingInfo[sDocID], 0);
	    }
	}
	else if(!strcmp(comm1, "prawko", true))
	{
	    new doorid = PlayerDoor[playerid];
	    if(GroupData[DoorInfo[doorid][dOwner]][Kind] != GROUP_GOV)
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w urzêdzie San Fierro Government.", "Zamknij", "");
		    return 1;
	    }
	    if(!IsPermGroupTypeOnType(playerid, GROUP_GOV))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wydawania dokumentów - prawa jazdy.", "Zamknij", "");
		    return 1;
	    }
	    
	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) prawko [ID gracza]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(CharacterCache[playerid2][pCash] < SettingInfo[sDocDriver])
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie.", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(CharacterCache[playerid2][pDocument] & DOC_DRIVER)
		 	{
		 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient posiada ju¿ prawo jazdy.", "Zamknij", "");
			    return 1;
		 	}

		 	Oferta(playerid, playerid2, OFFER_DRIVER, SettingInfo[sDocDriver], 0);
	    }
	}
	else if(!strcmp(comm1, "karta", true))
	{
	    new doorid = PlayerDoor[playerid];
	    if(GroupData[DoorInfo[doorid][dOwner]][Kind] != GROUP_GOV)
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w urzêdzie San Fierro Government.", "Zamknij", "");
		    return 1;
	    }
	    if(!IsPermGroupTypeOnType(playerid, GROUP_GOV))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wydawania dokumentów - karty rybackiej.", "Zamknij", "");
		    return 1;
	    }
	    
	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) karta [ID gracza]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(CharacterCache[playerid2][pCash] < SettingInfo[sDocFish])
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie.", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(CharacterCache[playerid2][pDocument] & DOC_FISH)
		 	{
		 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient posiada ju¿ kartê ryback¹.", "Zamknij", "");
			    return 1;
		 	}

		 	Oferta(playerid, playerid2, OFFER_FISH, SettingInfo[sDocFish], 0);
	    }
	}
	else if(!strcmp(comm1, "rejestracja", true))
	{
	    if(!IsPermGroupTypeOnType(playerid, GROUP_GOV))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wydawania dokumentów - rejestracji.", "Zamknij", "");
		    return 1;
	    }
	    
	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) rejestracja [ID gracza]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
	        if(!IsPlayerInAnyVehicle(playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie znajduje siê w ¿adnym pojeŸdzie.", "Zamknij", "");
			    return 1;
	        }
	        if(CharacterCache[playerid2][pCash] < SettingInfo[sDocRegister])
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie.", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(!IsOwnerVehicle(playerid, vehid))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do zarejestrowania pojazdu.", "Zamknij", "");
			    return 1;
		 	}
		 	
	        Oferta(playerid, playerid2, OFFER_REGISTER, SettingInfo[sDocRegister], vehid);
	    }
	}
	else if(!strcmp(comm1, "paszport", true))
	{
	    new doorid = PlayerDoor[playerid];
	    if(GroupData[DoorInfo[doorid][dOwner]][Kind] != GROUP_GOV)
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w urzêdzie San Fierro Government.", "Zamknij", "");
		    return 1;
	    }
	    if(!IsPermGroupTypeOnType(playerid, GROUP_GOV))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wydawania dokumentów - paszportu.", "Zamknij", "");
		    return 1;
	    }

	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) karta [ID gracza]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(CharacterCache[playerid2][pCash] < SettingInfo[sDocPassport])
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie.", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(CharacterCache[playerid2][pDocument] & DOC_PASSPORT)
		 	{
		 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient posiada ju¿ paszport.", "Zamknij", "");
			    return 1;
		 	}

		 	Oferta(playerid, playerid2, OFFER_PASSPORT, SettingInfo[sDocPassport], 0);
	    }
 	}
 	else if(!strcmp(comm1, "ubezpieczenie", true))
	{
	    return 1;
	}
	else if(!strcmp(comm1, "niekaralnoœæ", true) || !strcmp(comm1, "niekaralnosc", true))
	{
	    new doorid = PlayerDoor[playerid];
	    if(GroupData[DoorInfo[doorid][dOwner]][Kind] != GROUP_PD)
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w siedzibie San Fierro Police Department.", "Zamknij", "");
		    return 1;
	    }
	    if(!IsPermGroupTypeOnType(playerid, GROUP_PD))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wydawania dokumentów - niekaralnoœci.", "Zamknij", "");
		    return 1;
	    }

	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) niekaralnoœæ [ID gracza]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(CharacterCache[playerid2][pCash] < SettingInfo[sDocPolice])
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie.", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(CharacterCache[playerid2][pDocument] & DOC_POLICE)
		 	{
		 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient posiada ju¿ zaœwiadczenie o niekaralnoœci.", "Zamknij", "");
			    return 1;
		 	}

		 	Oferta(playerid, playerid2, OFFER_POLICE, SettingInfo[sDocPolice], 0);
	    }
 	}
	else if(!strcmp(comm1, "metryczka", true))
	{
	    new doorid = PlayerDoor[playerid];
	    if(GroupData[DoorInfo[doorid][dOwner]][Kind] != GROUP_MC)
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w urzêdzie San Fierro Government.", "Zamknij", "");
		    return 1;
	    }
	    if(!IsPermGroupTypeOnType(playerid, GROUP_MC))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wydawania dokumentów - metryczek.", "Zamknij", "");
		    return 1;
	    }

	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) metryczka [ID gracza]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(CharacterCache[playerid2][pCash] < SettingInfo[sDocMedical])
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie.", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(CharacterCache[playerid2][pDocument] & DOC_MEDICAL)
		 	{
		 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient posiada ju¿ metryczkê zdrowia.", "Zamknij", "");
			    return 1;
		 	}

		 	Oferta(playerid, playerid2, OFFER_MEDICAL, SettingInfo[sDocMedical], 0);
	    }
 	}
	else if(!strcmp(comm1, "licencje", true))
	{
	    new doorid = PlayerDoor[playerid];
	    if(GroupData[DoorInfo[doorid][dOwner]][Kind] != GROUP_PD)
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w siedzibie San Fierro Police Department.", "Zamknij", "");
		    return 1;
	    }
	    if(!IsPermGroupTypeOnType(playerid, GROUP_PD))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wydawania dokumentów - pozwolenie na broñ.", "Zamknij", "");
		    return 1;
	    }

	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) licencje [ID gracza]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(CharacterCache[playerid2][pCash] < SettingInfo[sDocLicense])
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie.", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(CharacterCache[playerid2][pDocument] & DOC_LICENSE)
		 	{
		 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient posiada ju¿ pozwolenie na broñ.", "Zamknij", "");
			    return 1;
		 	}

		 	Oferta(playerid, playerid2, OFFER_LICENSE, SettingInfo[sDocLicense], 0);
	    }
 	}
 	else if(!strcmp(comm1, "mandat", true))
	{
	    if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wystawienia mandatu.", "Zamknij", "");
		    return 1;
	    }
	    
	    new playerid2, cash, points;
	    if(sscanf(comm2, "idd", playerid2, cash, points))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) mandat [ID gracza] [kwota] [punkty karne]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(CharacterCache[playerid2][pCash] < cash)
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Petent nie posiada odpowiedniej iloœci gotówki na swoim koncie.", "Zamknij", "");
			    return 1;
	        }
	    	if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	
		 	Oferta(playerid, playerid2, OFFER_MANDAT, cash, points);
	    }
	}
 	else if(!strcmp(comm1, "alarm", true))
 	{
 	    if(!IsPermGroupTypeOnType(playerid, GROUP_SECURITY))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do zak³adania alarmów w drzwiach.", "Zamknij", "");
		    return 1;
	    }
	    if(!PlayerDoor[playerid])
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w ¿adnych z drzwi do których chcesz zamontowaæ alarm.", "Zamknij", "");
		    return 1;
	    }
	    
	    new playerid2, cash, doorid = PlayerDoor[playerid];
 	    if(sscanf(comm2, "id", playerid2, cash))
 	    {
 	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) alarm [ID gracza] [robocizna]", "Zamknij", "");
			return 1;
 	    }
 	    else
 	    {
	        if(CharacterCache[playerid2][pCash] < (1500 + cash))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie ($1500 + robocizna).", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(!IsOwnerDoor(playerid2, doorid))
			{
		 	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest liderem tego typu drzwi.", "Zamknij", "");
			    return 1;
		 	}
		 	if(DoorInfo[doorid][dValue] & DOOR_ALARM)
		 	{
		 	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W tych drzwiach zosta³ ju¿ zamontowany alarm.", "Zamknij", "");
			    return 1;
		 	}
		 	
		 	Oferta(playerid, playerid2, OFFER_ALARM, (1500 + cash), doorid);
 	    }
 	}
 	else if(!strcmp(comm1, "bramki", true))
 	{
 	    if(!IsPermGroupTypeOnType(playerid, GROUP_SECURITY))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do zak³adania bramek w drzwiach.", "Zamknij", "");
		    return 1;
	    }
	    if(!PlayerDoor[playerid])
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w ¿adnych z drzwi do których chcesz zamontowaæ bramki.", "Zamknij", "");
		    return 1;
	    }

	    new playerid2, cash, doorid = PlayerDoor[playerid];
 	    if(sscanf(comm2, "id", playerid2, cash))
 	    {
 	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) bramki [ID gracza] [robocizna]", "Zamknij", "");
			return 1;
 	    }
 	    else
 	    {
	        if(CharacterCache[playerid2][pCash] < (2500 + cash))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Klient nie posiada odpowiedniej iloœci gotówki na swoim koncie ($2500 + robocizna).", "Zamknij", "");
			    return 1;
	        }
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}
		 	if(!IsOwnerDoor(playerid2, doorid))
			{
		 	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest liderem tego typu drzwi.", "Zamknij", "");
			    return 1;
		 	}
		 	if(DoorInfo[doorid][dValue] & DOOR_GATE)
		 	{
		 	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W tych drzwiach zosta³y ju¿ zamontowane bramki.", "Zamknij", "");
			    return 1;
		 	}

		 	Oferta(playerid, playerid2, OFFER_GATE, (2500 + cash), doorid);
 	    }
 	}
	else if(!strcmp(comm1, "vcard", true))
	{
	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) vcard [ID gracza]", "Zamknij", "");
			return 1;
	    }
		else
		{
		    if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest aktualnie zalogowany.", "Zamknij", "");
			    return 1;
		    }
		    if(!CharacterCache[playerid][pPhone])
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz aktywowanego ¿adnego telefonu komórkowego.", "Zamknij", "");
			    return 1;
		    }
		    if(!CharacterCache[playerid2][pPhone])
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie posiada aktywowanego ¿adnego telefonu komórkowego.", "Zamknij", "");
			    return 1;
		    }
		    if(!PlayerToPlayer(5.0, playerid, playerid2))
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie znajduje siê w pobli¿u Ciebie.", "Zamknij", "");
			    return 1;
		    }
		   
		    Oferta(playerid, playerid2, OFFER_VCARD, 0, 0);
		}
	}
	else if(!strcmp(comm1, "przejazd", true))
	{
	    if(!IsPermGroupTypeOnType(playerid, GROUP_TAXI))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do przejazdu osób.", "Zamknij", "");
		    return 1;
	    }
	    
	    new playerid2, cash;
	    if(sscanf(comm2, "id", playerid2, cash))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) przejazd [ID gracza] [cena (100 metrów)]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(CharacterCache[playerid][pTaxiPassenger] != INVALID_PLAYER_ID)
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie mo¿esz zaoferowaæ przeja¿dŸki drugiej osobie.", "Zamknij", "");
		        return 1;
		    }
		    if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Musisz siedziea w pojeŸdzie taksówkarskim jako kierowca, aby móc zaoferowaæ przejazd.", "Zamknij", "");
		        return 1;
	    	}
	    	if(playerid2 == playerid)
	    	{
	     		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie mo¿esz zaoferowaæ czegoœ sobie.", "Zamknij", "");
	       		return 1;
	    	}
	   		if(playerid2 == INVALID_PLAYER_ID)
			{
	  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Podano b³êdne ID gracza.", "Zamknij", "");
		    	return 1;
			}
			if(!Logged[playerid2])
			{
	  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
		    	return 1;
			}
			if(!PlayerToPlayer(5.0, playerid, playerid2))
			{
	  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz o podanym ID znajduje sie zbyt daleko od Ciebie.", "Zamknij", "");
		    	return 1;
			}
			if(CharacterCache[playerid2][pBW])
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Ten gracz ma stan nieprzytomnoœci.", "Zamknij", "");
			    return 1;
			}
			if(GetPlayerState(playerid2) != PLAYER_STATE_PASSENGER || GetPlayerVehicleID(playerid2) != GetPlayerVehicleID(playerid))
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz musi siedzieæ w taksówce jako pasa¿er.", "Zamknij", "");
			    return 1;
			}
			
			Oferta(playerid, playerid2, OFFER_PASSAGE, cash, GetPlayerVehicleID(playerid));
	    }
	}
	else if(!strcmp(comm1, "przepustka", true))
	{
	    if(!IsPermGroupTypeOnType(playerid, GROUP_BORDER))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wydawania dokumentów - przepustki.", "Zamknij", "");
		    return 1;
	    }

	    new playerid2;
	    if(sscanf(comm2, "i", playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /o(feruj) przepustka [ID gracza]", "Zamknij", "");
			return 1;
	    }
	    else
	    {
	        if(!PlayerToPlayer(5.0, playerid, playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danego gracza.", "Zamknij", "");
			    return 1;
		 	}

		 	Oferta(playerid, playerid2, OFFER_PERMIT, 0, 0);
	    }
 	}
	return 1;
}
CMD:o(playerid, params[]) return cmd_oferuj(playerid, params);

CMD:akceptuj(playerid, params[])
{
	new type[12];
	if(sscanf(params, "s[12]", type))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /akceptuj [œmieræ | oferte]", "Zamknij", "");
        return 1;
	}
	else
	{
	    if(!strcmp(type, "œmieræ", true) || !strcmp(type, "smierc", true))
	 	{
	        if(!CharacterCache[playerid][pBW])
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz stanu nieprzytomnoœci, aby uœmierciæ postaæ.", "Zamknij", "");
        		return 1;
	        }
	        
	        // Informowanie graczy
			SendClientMessageToAllFormat(0xf74b4bFF, "Postaæ %s zosta³a uœmiercona.", PlayerName2(playerid));
			
			// Dodanie zw³ok
			AddCorpse(playerid, CharacterCache[playerid][pDeathReason], CharacterCache[playerid][pDeathWeapon]);
			
			// Zapis postaci
			CharacterCache[playerid][pBlock] += BLOCK_CHAR;
			
			KickWithWait(playerid);
	    }
	    else if(!strcmp(type, "oferte", true))
	 	{
	 	    cmd_oferuj(playerid, "akceptuj");
	 	    return 1;
	 	}
	}
	
	return 1;
}

CMD:pokaz(playerid, params[])
{
	new comm1[32], comm2[64], text[256];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /poka¿ [dowód | prawko | karta | paszport | metryczka | niekaralnoœæ | licencje | przepustka]", "Zamknij", "");
        return 1;
	}
	else
	{
	    if(!strcmp(comm1,"dowód",true) || !strcmp(comm1,"dowod",true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /poka¿ dowód [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
		    {
		        if(!Logged[playerid2])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany na serwerze.", "Zamknij", "");
			        return 1;
			    }
			    if(!PlayerToPlayer(5.0, playerid, playerid2))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od tego gracza.", "Zamknij", "");
			        return 1;
			    }
			    if(!(CharacterCache[playerid][pDocument] & DOC_ID))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz dowodu osobistego.", "Zamknij", "");
			        return 1;
			    }

				format(text, sizeof(text), "Imiê Nazwisko:\t\t%s\nP³eæ:\t\t\t%s\nWiek:\t\t\t%d lat", PlayerName2(playerid), GetSexName(CharacterCache[playerid][pSex]), CharacterCache[playerid][pAge]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Dowód osobisty", text, "Zamknij", "");
			}
		}
		else if(!strcmp(comm1,"prawko",true) || !strcmp(comm1,"prawo",true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /poka¿ prawko [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
		    {
		        if(!Logged[playerid2])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany na serwerze.", "Zamknij", "");
			        return 1;
			    }
			    if(!PlayerToPlayer(5.0, playerid, playerid2))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od tego gracza.", "Zamknij", "");
			        return 1;
			    }
			    if(!(CharacterCache[playerid][pDocument] & DOC_DRIVER))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz prawa jazdy.", "Zamknij", "");
			        return 1;
			    }

				format(text, sizeof(text), "Imiê Nazwisko:\t\t%s\nP³eæ:\t\t\t%s\nWiek:\t\t\t%d lat\n\nUprawniony do poruszania siê pojazdami.", PlayerName2(playerid), GetSexName(CharacterCache[playerid][pSex]), CharacterCache[playerid][pAge]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Prawo jazdy", text, "Zamknij", "");
			}
		}
		else if(!strcmp(comm1,"karta",true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /poka¿ karta [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
		    {
		        if(!Logged[playerid2])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany na serwerze.", "Zamknij", "");
			        return 1;
			    }
			    if(!PlayerToPlayer(5.0, playerid, playerid2))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od tego gracza.", "Zamknij", "");
			        return 1;
			    }
			    if(!(CharacterCache[playerid][pDocument] & DOC_FISH))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz karty rybackiej.", "Zamknij", "");
			        return 1;
			    }

				format(text, sizeof(text), "Imiê Nazwisko:\t\t%s\nWiek:\t\t\t%d lat\n\nWydane przez urz¹d Los Santos Government.", PlayerName2(playerid), CharacterCache[playerid][pAge]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Karta rybacka", text, "Zamknij", "");
			}
		}
		else if(!strcmp(comm1,"paszport",true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /poka¿ paszport [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
		    {
		        if(!Logged[playerid2])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany na serwerze.", "Zamknij", "");
			        return 1;
			    }
			    if(!PlayerToPlayer(5.0, playerid, playerid2))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od tego gracza.", "Zamknij", "");
			        return 1;
			    }
			    if(!(CharacterCache[playerid][pDocument] & DOC_PASSPORT))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz paszportu.", "Zamknij", "");
			        return 1;
			    }

				format(text, sizeof(text), "Imiê Nazwisko:\t\t%s\nWiek:\t\t\t%d lat\n\nWydane przez urz¹d Los Santos Government.", PlayerName2(playerid), CharacterCache[playerid][pAge]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Paszport", text, "Zamknij", "");
			}
		}
		else if(!strcmp(comm1,"niekaralnoœæ",true) || !strcmp(comm1,"niekaralnosc",true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /poka¿ karta [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
		    {
		        if(!Logged[playerid2])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany na serwerze.", "Zamknij", "");
			        return 1;
			    }
			    if(!PlayerToPlayer(5.0, playerid, playerid2))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od tego gracza.", "Zamknij", "");
			        return 1;
			    }
			    if(!(CharacterCache[playerid][pDocument] & DOC_POLICE))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz zaœwiadczenia o niekaralnoœci.", "Zamknij", "");
			        return 1;
			    }

				format(text, sizeof(text), "Imiê Nazwisko:\t\t%s\nWiek:\t\t\t%d lat\n\nWydane przez Los Santos Police Department.", PlayerName2(playerid), CharacterCache[playerid][pAge]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Zaœwiadczenie o niekaralnoœci", text, "Zamknij", "");
			}
		}
		else if(!strcmp(comm1,"metryczka",true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /poka¿ metryczka [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
		    {
		        if(!Logged[playerid2])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany na serwerze.", "Zamknij", "");
			        return 1;
			    }
			    if(!PlayerToPlayer(5.0, playerid, playerid2))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od tego gracza.", "Zamknij", "");
			        return 1;
			    }
			    if(!(CharacterCache[playerid][pDocument] & DOC_MEDICAL))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz metryczki zdrowia.", "Zamknij", "");
			        return 1;
			    }

				format(text, sizeof(text), "Imiê Nazwisko:\t\t%s\nWiek:\t\t\t%d lat\n\nWydane przez Los Santos Police Department.", PlayerName2(playerid), CharacterCache[playerid][pAge]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Metryczka zdrowia", text, "Zamknij", "");
			}
		}
		else if(!strcmp(comm1,"licencje",true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /poka¿ karta [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
		    {
		        if(!Logged[playerid2])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany na serwerze.", "Zamknij", "");
			        return 1;
			    }
			    if(!PlayerToPlayer(5.0, playerid, playerid2))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od tego gracza.", "Zamknij", "");
			        return 1;
			    }
			    if(!(CharacterCache[playerid][pDocument] & DOC_LICENSE))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz licencji na broñ.", "Zamknij", "");
			        return 1;
			    }

				format(text, sizeof(text), "Imiê Nazwisko:\t\t%s\nWiek:\t\t\t%d lat\n\nWydane przez Los Santos Police Department.", PlayerName2(playerid), CharacterCache[playerid][pAge]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Licencja na broñ", text, "Zamknij", "");
			}
		}
		else if(!strcmp(comm1,"przepustka",true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /poka¿ przepustka [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
		    {
		        if(!Logged[playerid2])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany na serwerze.", "Zamknij", "");
			        return 1;
			    }
			    if(!PlayerToPlayer(5.0, playerid, playerid2))
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od tego gracza.", "Zamknij", "");
			        return 1;
			    }
			    
			    new day, hour, minute, year, mies;
        		timestamp_to_date(CharacterCache[playerid][pPermit], year, mies, day, hour, minute);
        
			    if(CharacterCache[playerid][pPermit] > gettime())
			    {
					format(text, sizeof(text), "{FFFFFF}Imiê Nazwisko:\t\t%s\nWiek:\t\t\t%d lat\n{228B22}Wa¿na przepustka (%d-%d-%d, %d:%d)\n\n{FFFFFF}Wydane przez U.S Border Patrol.", PlayerName2(playerid), CharacterCache[playerid][pAge], mies, day, year, hour + 1, minute);
					ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Przepustka", text, "Zamknij", "");
			    }
			    else
			    {
			        if(!CharacterCache[playerid][pPermit])
			        {
						format(text, sizeof(text), "{FFFFFF}Imiê Nazwisko:\t\t%s\nWiek:\t\t\t%d lat\n{ff8282}Brak wa¿nej przepustki (Nigdy)\n\n{FFFFFF}Wydane przez U. Border Patrol.", PlayerName2(playerid), CharacterCache[playerid][pAge]);
						ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Przepustka", text, "Zamknij", "");
			        }
			        else
			        {
						format(text, sizeof(text), "{FFFFFF}Imiê Nazwisko:\t\t%s\nWiek:\t\t\t%d lat\n{ff8282}Brak wa¿nej przepustki (%d-%d-%d, %d:%d)\n\n{FFFFFF}Wydane przez U.S Border Patrol.", PlayerName2(playerid), CharacterCache[playerid][pAge], mies, day, year, hour + 1, minute);
						ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Przepustka", text, "Zamknij", "");
					}
			    }
			}
		}
	}
	
	return 1;
}

CMD:telefon(playerid, params[])
{
	new itemid = GetItemID(CharacterCache[playerid][pPhone]);
	new title[32];
	
	if(!CharacterCache[playerid][pPhone])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz w³¹czonego ¿adnego telefonu.\nZrób to u¿waj¹c telefon poprzez komendê '/p'.", "Zamknij", "");
		return 1;
	}
	if(!PlayerHaveItemValue(playerid, TYPE_PHONE, ItemInfo[itemid][iValue1]))
	{
	    CharacterCache[playerid][pPhone] = 0;
	    
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz w³¹czonego ¿adnego telefonu.\nZrób to u¿waj¹c telefon poprzez komendê '/p'.", "Zamknij", "");
		return 1;
	}
	
	format(title, sizeof(title), "Telefon [%d]", ItemInfo[itemid][iValue1]);
	ShowPlayerDialog(playerid, D_PHONE, DIALOG_STYLE_LIST, title, "# Zadzwoñ do numeru\n# Napisz SMS\n# Kontakty\n# Ustawienia", "Wybierz", "Zamknij");
 	return 1;
}
CMD:tel(playerid, params[]) return cmd_telefon(playerid, params);
CMD:t(playerid, params[]) return cmd_telefon(playerid, params);

CMD:sms(playerid, params[])
{
	if(CharacterCache[playerid][pBW])
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W stanie nieprzytomnoœci nie jesteœ w stanie rozmawiaæ przez telefon.", "Zamknij", "");
	    return 1;
	}
	if(CharacterCache[playerid][pAJ])
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W czasie kary Admin Jail nie mo¿esz u¿ywaæ telefonu.", "Zamknij", "");
	    return 1;
	}
	if(!PlayerHaveItemType(playerid, TYPE_PHONE))
    {
    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz przy sobie ¿adnego telefonu.", "Zamknij", "");
	    return 1;
    }
    if(!CharacterCache[playerid][pPhone])
    {
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Telefon, który posiadasz nie zosta³ w³¹czony.", "Zamknij", "");
		return 1;
    }
	
	new number, text[128];
	if(sscanf(params, "ds[128]", number, text))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "U¿yj: /sms [numer telefonu] [wiadomoœæ]", "Zamknij", "");
	    return 1;
	}
	else
	{
	    new playerid2 = GetPhoneID(number);
	    new itemid = GetItemID(CharacterCache[playerid][pPhone]);
	    
	    if(playerid2 <= 0 || playerid2 == INVALID_PLAYER_ID || playerid2 == -1)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany abonament jest poza zasiêgiem.", "Zamknij", "");
	        return 1;
	    }
	    if(playerid == playerid2)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie jesteœ w stanie wysy³aæ wiadomoœci do samego siebie.", "Zamknij", "");
	        return 1;
	    }
	    if(number == 911 || number == 777 || number == 778 || number == 444 || number == 333)
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony numer jest nieprawid³owy.\nNie mo¿esz wysy³aæ SMS do instytucji pañstwowych.", "Zamknij", "");
	        return 1;
	    }
	    
	    SendClientMessageFormat(playerid, ZOLTY, "[SMS] %d » %s", number, text);
	    SendClientMessageFormat(playerid2, ZOLTY, "[SMS] %d « %s", ItemInfo[itemid][iValue1], text);
	    
	    cmd_me(playerid, "wyci¹ga telefon i wysy³a SMS.");
	    cmd_do(playerid2, "S³ychaæ dŸwiêk przychodz¹cego SMS.");
	}
	
	return 1;
}

CMD:call(playerid, params[])
{
	if(CharacterCache[playerid][pBW])
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W stanie nieprzytomnoœci nie jesteœ w stanie rozmawiaæ przez telefon.", "Zamknij", "");
	    return 1;
	}
	if(CharacterCache[playerid][pAJ])
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W czasie kary Admin Jail nie mo¿esz u¿ywaæ telefonu.", "Zamknij", "");
	    return 1;
	}
	if(!PlayerHaveItemType(playerid, TYPE_PHONE))
    {
    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz przy sobie ¿adnego telefonu.", "Zamknij", "");
	    return 1;
    }
    if(!CharacterCache[playerid][pPhone])
    {
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Telefon, który posiadasz nie zosta³ w³¹czony.", "Zamknij", "");
		return 1;
    }
    if(CallTo[playerid] != INVALID_PLAYER_ID)
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Rozmawiasz ju¿ z kimœ.", "Zamknij", "");
	    return 1;
	}
    
    new number, string[128];
    if(sscanf(params, "d", number))
    {
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "U¿yj: /zadzwoñ [numer telefonu]", "Zamknij", "");
		return 1;
    }
    else
    {
        if(number == 911)
		{
			new list_groups[512];

			ForeachEx(i, MAX_GROUPS)
			{
			    if(GroupData[i][Flags] & FLAG_CALL_911)
			    {
			        format(list_groups, sizeof(list_groups), "%s\n%d\t%s (%d na s³u¿bie)", list_groups, GroupData[i][UID], GroupData[i][Desc], CountMemberGroupOnDuty(i));
			    }
			}

			ShowPlayerDialog(playerid, D_CALL_911, DIALOG_STYLE_LIST, " Telefony alarmowe", list_groups, "Wybierz", "Zamknij");
		}
		else if(number == 777)
		{
   			new doorid = PlayerDoor[playerid];
   			if(!doorid)
 			{
          		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w ¿adnych drzwiach grupowych.", "Zamknij", "");
          		return 1;
          	}
          	if(DoorInfo[doorid][dOwnerType] != OWNER_GROUP)
          	{
          		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w ¿adnych drzwiach grupowych.", "Zamknij", "");
	    		return 1;
          	}
          	if(DoorInfo[doorid][dEnterVw] != 0)
          	{
          		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Drzwi musz¹ byæ drzwiami wejœciowymi do budynku.", "Zamknij", "");
	    		return 1;
          	}
          	if(!IsPlayerPermInGroup(playerid, DoorInfo[doorid][dOwner], PANEL_PRODUCT))
          	{
          		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do zamawiania produktów.", "Zamknij", "");
          	    return 1;
         	}

            SetPVarInt(playerid, "ProductDoor", doorid);

            format(string, sizeof(string), "%s (telefon): Las Venturas Transport Logistic.", PlayerName2(playerid));
			ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
			
			new list_type[1024], data[64], uid, name[32];
			mysql_query_format("SELECT * FROM `fc_orders_type`");

			mysql_store_result();

			while(mysql_fetch_row_format(data, "|"))
			{
				sscanf(data, "p<|>ds[32]", uid, name);

				format(list_type, sizeof(list_type), "%s\n%d\t%s", list_type, uid, name);
			}

			mysql_free_result();

			ShowPlayerDialog(playerid, D_ORDER_CATEGORY, DIALOG_STYLE_LIST, " Wybierz kategoriê produktów", list_type, "Wybierz", "Zamknij");
 		}
   		else if(number == 778)
       	{
       		format(string, sizeof(string), "%s (telefon): Las Venturas Magazine.", PlayerName2(playerid));
   			ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

          	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Magazyn nie jest niedostêpny.", "Wybierz", "Zamknij");
		}
		else if(number == 444)
       	{
       		format(string, sizeof(string), "%s (telefon): Los Santos FM.", PlayerName2(playerid));
   			ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);

          	ShowPlayerDialog(playerid, D_RADIO, DIALOG_STYLE_INPUT, " Informacja", "WprowadŸ informacjê, któr¹ chcesz przekazaæ radiu Los Santos FM.", "Przeka¿", "Zamknij");
		}
		else if(number == 333)
       	{
       		new list_taxi[1024];

       		ForeachEx(i, MAX_GROUPS)
       		{
       			if(GroupData[i][Kind] == GROUP_TAXI)
       			{
       				format(list_taxi, sizeof(list_taxi), "%s\n%d\t%s (%d na s³u¿bie)", list_taxi, GroupData[i][UID], GroupData[i][Desc], CountMemberGroupOnDuty(i));
				}
       		}

   			ShowPlayerDialog(playerid, D_TAXI, DIALOG_STYLE_LIST, " Korporacje taksówkarskie", list_taxi, "Wybierz", "Zamknij");
	    }
	    else
	    {
	   	    new playerid2 = GetPhoneID(number);
		    new itemid = GetItemID(CharacterCache[playerid][pPhone]);

		    if(playerid2 < 0 || playerid2 == INVALID_PLAYER_ID || playerid2 == -1)
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany abonament jest poza zasiêgiem.", "Zamknij", "");
		        return 1;
		    }
		    if(playerid == playerid2)
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie jesteœ w stanie wysy³aæ wiadomoœci do samego siebie.", "Zamknij", "");
		        return 1;
		    }

		    CallTo[playerid] = playerid2;
		    CallTo[playerid2] = playerid;

		    CallTime[playerid] = 10;
		    CallTime[playerid2] = 10;

		    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);

		    SendClientMessageFormat(playerid, ZOLTY, "** Dzwonisz do numeru %d, zaczekaj a¿ odbierze. **", number);
	        SendClientMessageFormat(playerid2, ZOLTY, "** Telefon dzwoni, aby odebraæ wpisz /odbierz (%d). **", ItemInfo[itemid][iValue1]);

	        cmd_do(playerid2, "S³ychaæ dzwonienie telefonu");
        }
	}
	return 1;
}
CMD:zadzwon(playerid, params[]) return cmd_call(playerid, params);
CMD:dzwon(playerid, params[]) return cmd_call(playerid, params);

CMD:odbierz(playerid, params[])
{
	if(CallTo[playerid] == INVALID_PLAYER_ID)
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nikt aktualnie do Ciebie nie dzwoni.", "Zamknij", "");
	    return 1;
	}
	
	new playerid2 = CallTo[playerid];
	
	CallNow[playerid] = true;
	CallNow[playerid2] = true;
	
	CallTime[playerid] = -1;
	CallTime[playerid2] = -1;
	
	SendClientMessage(playerid, ZOLTY, "** Odebra³eœ telefon, aby zakoñczyæ u¿yj '/z(akoncz)'. **");
	SendClientMessage(playerid2, ZOLTY, "** Osoba odebra³a telefon, aby zakoñczyæ u¿yj '/z(akoncz)'. **");
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	
	return 1;
}

CMD:zakoncz(playerid, params[])
{
    if(CallTo[playerid] == INVALID_PLAYER_ID || CallTo[playerid] == -1)
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nikt aktualnie do Ciebie nie dzwoni.", "Zamknij", "");
	    return 1;
	}
	
	new playerid2 = CallTo[playerid];

	CallNow[playerid] = false;
	CallNow[playerid2] = false;
	
	CallTo[playerid] = INVALID_PLAYER_ID;
	CallTo[playerid2] = INVALID_PLAYER_ID;
	
	CallTime[playerid] = -1;
	CallTime[playerid2] = -1;
	
	SendClientMessage(playerid, ZOLTY, "** Rozmowa zosta³a pomyœlnie zakoñczona. **");
	SendClientMessage(playerid2, ZOLTY, "** Rozmowa zosta³a pomyœlnie zakoñczona. **");
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
    SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_STOPUSECELLPHONE);
    
	return 1;
}
CMD:z(playerid, params[]) return cmd_zakoncz(playerid, params);

CMD:alarm(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	new vehid = GetVehicleUID(vehicleid);
	if(GetVehicleModel(vehicleid) == 428 && IsGroupHaveFlag(DutyGroup[playerid], FLAG_ALARM))
	{
	    new string[128];
	    new groupid = GetGroupKind(GROUP_PD);
	    new color = MakeColorLighter(GroupData[groupid][Chat][0], GroupData[groupid][Chat][1], GroupData[groupid][Chat][2], 30);
	    
	    AddReport(playerid, GroupData[groupid][UID], "Napad na furgonetke z pieniedzmi.");
	    
	    format(string, sizeof(string), "(ALARM) Furgonetka: %s (%s) (/g {slot} zgloszenia)", GetVehicleModelName(VehicleInfo[vehid][vModel]), VehicleInfo[vehid][vRegister]);
	    
		SendMessageToGroup(GroupData[groupid][UID], color, "(ALARM) Uruchomiony zosta³ alarm w furgonetce opancerzonej.");
		SendMessageToGroup(GroupData[groupid][UID], color, string);
		
 		ProxDetector(10.0, playerid, "** Z furognetki wydobywa siê g³oœny dŸwiêk alarmu. **", COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO);
	}
	else
	{
		if(!(DoorInfo[PlayerDoor[playerid]][dValue] & DOOR_ALARM))
		{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Lokal nie posiada zainstalowanego alarmu w drzwiach.", "Zamknij", "");
		    return 1;
		}
	    if(!IsOwnerDoorUnPermission(playerid, PlayerDoor[playerid]))
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do uruchomienia alarmu w lokalu.", "Zamknij", "");
		    return 1;
		}

		new comm1[32], doorid = PlayerDoor[playerid];
		if(sscanf(params, "s[32]", comm1))
		{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /alarm [w³¹cz | wy³¹cz]", "Zamknij", "");
	        return 1;
		}
		else
		{
		    if(!strcmp(comm1, "w³¹cz", true) || !strcmp(comm1, "wlacz", true))
			{
			    DoorInfo[doorid][dAlarm] = true;

			    new string[128];
			    format(string, sizeof(string), "(ALARM) Lokal %s uruchamia alarm w swoim pomieszczeniu.");

			    SendMessageToGroup(GetGroupKind(GROUP_SECURITY), ZIELONY, string);
			    SendMessageToGroup(GetGroupKind(GROUP_PD), ZIELONY, string);

	        	format(string, sizeof(string), "** W lokalu %s s³ychaæ g³oœny dŸwiêk alarmu **", DoorInfo[doorid][dName]);
	        	SendClientMessageAroundDoor(playerid, doorid, string);

			    cmd_me(playerid, "w³¹cza alarm w lokalu za pomoc¹ pilota.");
			}
			else if(!strcmp(comm1, "wy³¹cz", true) || !strcmp(comm1, "wylacz", true))
			{
			    DoorInfo[doorid][dAlarm] = false;

			    new string[128];
			    format(string, sizeof(string), "[ALARM] Lokal %s wy³¹czy³ alarm w swoim pomieszczeniu.", DoorInfo[doorid][dName]);

			    SendMessageToGroup(GetGroupKind(GROUP_SECURITY), ZIELONY, string);
			    SendMessageToGroup(GetGroupKind(GROUP_PD), ZIELONY, string);

			    cmd_me(playerid, "wy³¹cza alarm w lokalu za pomoc¹ pilota.");
			}
		}
	}
	return 1;
}

CMD:bank(playerid, params[])
{
	new doorid = PlayerDoor[playerid];
	new groupid = DoorInfo[doorid][dOwner];
	new title[64];
	
	if(!doorid)
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w ¿adnym pomieszczeniu.", "Zamknij", "");
	    return 1;
	}
	if(DoorInfo[doorid][dOwnerType] != OWNER_GROUP || GroupData[groupid][Kind] != GROUP_BANK)
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pomieszczeniu banku.", "Zamknij", "");
	    return 1;
	}

	format(title, sizeof(title), "Bank: %s", GroupData[groupid][Desc]);
	ShowPlayerDialog(playerid, D_BANK, DIALOG_STYLE_LIST, title, "#\tStwórz now¹ kartê\n#\tLista posiadanych kart\n#\tKredyt bankowy", "Wybierz", "Zamknij");

	return 1;
}

CMD:zadanie(playerid, params[])
{
	new reportid = CharacterCache[playerid][pReportPD];
	if(!reportid)
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aktualnie nie zajmujesz siê ¿adnym zg³oszeniem.", "Zamknij", "");
	    return 1;
	}
	if(ReportInfo[reportid][reportStatus] != CharacterCache[playerid][pUID])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do zarz¹dzania tym zg³oszeniem.", "Zamknij", "");
		return 1;
	}
	
	ShowPlayerDialog(playerid, D_REPORT_OPTIONS, DIALOG_STYLE_LIST, " Zarz¹dzanie zg³oszeniem", "1. Zakoñcz zg³oszenie\n2. Anuluj zg³oszenie\n3. Informacje o zg³oszeniu", "Wybierz", "Zamknij");
	return 1;
}

CMD:paczka(playerid, params[])
{
	if(CharacterCache[playerid][pPackageTime] > gettime())
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Musisz odczekaæ chwilê czasu by móc sprawdziæ ponownie czas magazynu.", "Zamknij", "");
  		return 1;
	}
	
	CharacterCache[playerid][pPackageTime] = gettime() + 60;
	
	if(IsPlayerInRangeOfPoint(playerid, 30.0, SettingInfo[sMagazineX], SettingInfo[sMagazineY], SettingInfo[sMagazineZ]))
	{
		new data[32], list_pack[1024], uid, doorid;

		mysql_query("SELECT `order_uid`, `door_uid` FROM `fc_orders` WHERE `status` = 0 AND `driver` = 0");
		mysql_store_result();

		while(mysql_fetch_row_format(data, "|"))
		{
		    sscanf(data, "p<|>dd", uid, doorid);

		    format(list_pack, sizeof(list_pack), "%s\n%d\t%s", list_pack, uid, GroupData[DoorInfo[doorid][dOwner]][Desc]);
		}
		
		mysql_free_result();

		if(strlen(list_pack) != 0) ShowPlayerDialog(playerid, D_ORDER_MAGAZINE, DIALOG_STYLE_LIST, " Lista paczek", list_pack, "Wybierz", "Zamknij");
		else Infobox(playerid, 5, "W magazynie ~g~~h~nie znajduje~w~~h~ sie zadna paczka.");
	}
	else
	{
	    if(CharacterCache[playerid][pPackage])
	    {
	        new doorid = CharacterCache[playerid][pPackageDoor];
	        new pack_id = CharacterCache[playerid][pPackageID];
	        
	        if(!IsPlayerInRangeOfPoint(playerid, 3.0, DoorInfo[doorid][dEnterX], DoorInfo[doorid][dEnterY], DoorInfo[doorid][dEnterZ]))
	        {
	            SetPlayerCheckpoint(playerid, DoorInfo[doorid][dEnterX], DoorInfo[doorid][dEnterY], DoorInfo[doorid][dEnterZ], 3.0);
	            
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w drzwiach dostarczenia paczki.\nPunkt zosta³ ukazany Ci na mapie.", "Zamknij", "");
	            return 1;
	        }
			
			new data[64], value1, value2, name, value, kind;
			mysql_query_format("SELECT `value1`, value2`, `name`, `value`, `kind` FROM `fc_orders` WHERE `uid` = '%d' AND `drive` = '%d'", pack_id, CharacterCache[playerid][pUID]);
			
			mysql_store_result();
			mysql_fetch_row_format(data, "|");
			
			sscanf(data, "p<|>dds[32]dd", value1, value2, name, value, kind);
			mysql_free_result();
			
			mysql_query_format("INSERT INTO `fc_items` (`name`, `value1`, `value2`, `kind`, `ownertype`, `owner`, `value`) VALUES ('%s', '%d', '%d', '%d', '%d', '%d', '%d')", name, value1, value2, kind, OWNER_GROUP, DoorInfo[doorid][dOwner], value);
			mysql_query_format("UPDATE `fc_orders` SET `status` = 1 WHERE `uid` = '%d'", pack_id);
			
			DisablePlayerCheckpoint(playerid);
			
			GivePlayerCash(playerid, value * 3);
			
   			CharacterCache[playerid][pPackage] = false;
			CharacterCache[playerid][pPackageID] = 0;
			CharacterCache[playerid][pPackageDoor] = 0;
			CharacterCache[playerid][pPackageTime] = 0;
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Paczka zosta³a pomyœlnie dostarczona.", "Zamknij", "");
	    }
	    else
	    {
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê na terenie magazynu.\nMiejsce magazynu ukazane jest na mapie za pomoc¹ ikony.", "Zamknij", "");
		    return 1;
	    }
	}
	return 1;
}

CMD:opis(playerid, params[])
{
	new options[1024];
	
	format(options, sizeof(options), "1. Lista dostêpnych opisów", options);
	format(options, sizeof(options), "%s\n2. Stwórz nowy opis", options);
	format(options, sizeof(options), "%s\n3. Usuñ zapisany opis", options);
	format(options, sizeof(options), "%s\n4. Poka¿ aktualny opis", options);
	format(options, sizeof(options), "%s\n{D42A2A}5. Usuñ wszystkie opisy", options);
	if(CharacterCache[playerid][pUseDesc]) format(options, sizeof(options), "%s\n{228B22}6. Usuñ aktualny opis", options);
	
	format(options, sizeof(options), "%s\n------------", options);
	
	if(IsPlayerPremium(playerid)) format(options, sizeof(options), "%s\n{C0C0C0}Twoje konto pozwala na zapis maksymalnie {FCDB6D}5 opisów{C0C0C0}.", options);
	else format(options, sizeof(options), "%s\n{C0C0C0}Twoje konto pozwala na zapis maksymalnie 3 opisów.", options);
	
	format(options, sizeof(options), "%s\n{C0C0C0}Nale¿y unikaæ zapisu z u¿ytymi znakami polskimi.", options);
	
	ShowPlayerDialog(playerid, D_DESCRIPTIONS, DIALOG_STYLE_LIST, " Informacja", options, "Wybierz", "Zamknij");
	return 1;
}

CMD:login(playerid, params[])
{
	new giveplayer_id;
	if(sscanf(params, "i", giveplayer_id))
	{
	    if(CharacterCache[playerid][pAdmin] > 1)
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /login [ID gracza]", "Zamknij", "");
        	return 1;
	    }
	    else
	    {
		    OnPlayerDisconnect(playerid, 1);
			OnPlayerConnect(playerid);
			OnPlayerRequestClass(playerid, 1);
		}
	}
	else
	{
	    if(!IsPlayerConnected(giveplayer_id) || !Logged[giveplayer_id])
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany.", "Zamknij", "");
        	return 1;
	    }
	    
		OnPlayerDisconnect(giveplayer_id, 1);
		OnPlayerConnect(giveplayer_id);
		OnPlayerRequestClass(giveplayer_id, 1);
	}
	return 1;
}

CMD:plac(playerid, params[])
{
	new playerid2, cash, string[256];
	if(sscanf(params, "id", playerid2, cash))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /p³aæ [ID gracza] [kwota]", "Zamknij", "");
        return 1;
	}
	else
	{
	    if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany.", "Zamknij", "");
        	return 1;
	    }
	    if(!PlayerToPlayer(5.0, playerid, playerid2))
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz znajduje siê zbyt daleko Ciebie.", "Zamknij", "");
        	return 1;
	    }
	    if(CharacterCache[playerid2][pHours] < 1 || CharacterCache[playerid2][pHours] < 1)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Jeden z graczy posiada zbyt ma³¹ iloœæ godzin, do przekazywania gotówki.", "Zamknij", "");
        	return 1;
	    }
	    if(CharacterCache[playerid][pCash] < cash || cash < 1)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz takiej iloœci gotówki na swoim koncie.", "Zamknij", "");
        	return 1;
	    }
	    
	    if(cash >= 300)
	    {
			SendAdminMessageFormat(0xD96A6AFF, "[AI] %s (ID: %d) przekaza³ graczowi %s (ID: %d) - $%d.", PlayerName2(playerid), playerid, PlayerName2(playerid2), playerid2, cash);
	    }
	    
	    GivePlayerCash(playerid, -cash);
	    GivePlayerCash(playerid2, cash);
	    
		format(string, sizeof(string), "Przekaza³eœ graczowi %s (ID: %d) kwotê $%d.", PlayerName2(playerid2), playerid2, cash);
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		
		format(string, sizeof(string), "Gracz %s (ID: %d) przekaza³ Tobie $%d.", PlayerName2(playerid), playerid, cash);
		ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	}
	
	return 1;
}
CMD:pay(playerid, params[]) return cmd_plac(playerid, params);

CMD:bus(playerid, params[])
{
	new busid = GetClosestBusStop(playerid);
	
	if(!busid)
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u ¿adnego z przystanków.", "Zamknij", "");
	    return 1;
	}
	else
	{
		if(CharacterCache[playerid][pBusStatus])
		{
		    CharacterCache[playerid][pBusStatus] = BUS_NONE;

		    CharacterCache[playerid][pBusPos][0] = 0;
			CharacterCache[playerid][pBusPos][1] = 0;
			CharacterCache[playerid][pBusPos][2] = 0;

		    TogglePlayerControllable(playerid, 1);
		    SetCameraBehindPlayer(playerid);
		}
		else
		{
		    CharacterCache[playerid][pBusStatus] = BUS_SEARCH;

		    TogglePlayerControllable(playerid, 0);

		    new Float:Pos[3];
		    GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

		    CharacterCache[playerid][pBusPos][0] = Pos[0];
			CharacterCache[playerid][pBusPos][1] = Pos[1];
			CharacterCache[playerid][pBusPos][2] = Pos[2];

		    InterpolateCameraPos(playerid, Pos[0], Pos[1], Pos[2], Pos[0], Pos[1] - 2, Pos[2] + 50, 1500, CAMERA_MOVE);
			InterpolateCameraLookAt(playerid, Pos[0], Pos[1], Pos[2], Pos[0], Pos[1], Pos[2], 1500, CAMERA_MOVE);

			Infobox(playerid, 7, "Uzyj strzalek podczas widoku z lotu ptaka, by wybrac docelowa lokalizacje.~n~~n~Wcisnij ~g~~h~RETURN ~w~~h~by wybrac najblizszy przystanek lub ~g~~h~LSHIFT ~w~~h~by anulowac przejazd.");
		}
	}
	return 1;
}

CMD:tankuj(playerid, params[])
{
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Tankowanie samemu swojego pojazdu zosta³o zablokowane.\nAby zatankowaæ pojazd u¿yj do tej akcji pomocnika stacji.\n\nPomocnikiem stacji jest ka¿da z osób znajduj¹cych siê na s³u¿bie pracy.\nAby wejœæ na s³u¿bê pomocnika u¿yj /duty p(raca).", "Zamknij", "");
	return 1;
}

CMD:dom(playerid, params[])
{
	new comm1[32], comm2[32], string[256];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
	{
	    SendClientMessage(playerid, SZARY, "U¿yj: /dom [lista | zaproœ | wyproœ | czynsz | online]");
	    
	    if(GetPlayerDoors(playerid) != 0)
	    {
	        new list_doors[1024];
	        
	        ForeachEx(i, MAX_DOORS)
	        {
	            if(DoorInfo[i][dOwnerType] == OWNER_PLAYER && DoorInfo[i][dOwner] == CharacterCache[playerid][pUID])
	            {
					format(list_doors, sizeof(list_doors), "%s\n%d\t%s", list_doors, DoorInfo[i][dUID], DoorInfo[i][dName]);
				}
			}
			
			format(list_doors, sizeof(list_doors), "%s\n------------", list_doors);
			
			format(list_doors, sizeof(list_doors), "%s\n{C0C0C0}Na Twoim koncie znajduj¹ siê przypisane drzwi.", list_doors);
			format(list_doors, sizeof(list_doors), "%s\n{C0C0C0}Nie posiadaj¹ one jednak utworzonego mieszkania.", list_doors);
			format(list_doors, sizeof(list_doors), "%s\n{C0C0C0}Aby to zrobiæ, przepisz drzwi powy¿ej do swojego konta, jako mieszkanie.", list_doors);
			
			if(IsPlayerPremium(playerid)) format(list_doors, sizeof(list_doors), "%s\n{C0C0C0}Maksymalna iloœæ posiadanych domów na Twoim koncie to {FCDB6D}3 drzwi{C0C0C0}.", list_doors);
			else format(list_doors, sizeof(list_doors), "%s\n{C0C0C0}Maksymalna iloœæ posiadanych domów na Twoim koncie to 1.", list_doors);
	
			ShowPlayerDialog(playerid, D_REWRITE_DOOR, DIALOG_STYLE_LIST, " Informacja", list_doors, "Przepisz", "Zamknij");
	    }
	    else
	    {
	        new list_doors[512];
	        
	        ForeachEx(i, MAX_DOORS)
	        {
	            if(DoorInfo[i][dOwnerType] == OWNER_HOUSE && (MemberHome[playerid][i][homePerm] & PERM_HOUSE_LEADER || MemberHome[playerid][i][homePerm] & PERM_HOUSE_MEMBER))
	            {
					format(list_doors, sizeof(list_doors), "%s\n%d\t%s", list_doors, DoorInfo[i][dUID], DoorInfo[i][dName]);
				}
			}
			
			if(strlen(list_doors) != 0) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Informacja", list_doors, "Zamknij", "");
			else Infobox(playerid, 5, "Nie znaleziono ~b~~h~zadnych ~w~~h~mieszkan.");
	    }
	}
	else
	{
	    if(!strcmp(comm1, "lista", true))
        {
            new list_doors[512];

	        ForeachEx(i, MAX_DOORS)
	        {
	            if(DoorInfo[i][dOwnerType] == OWNER_HOUSE && (MemberHome[playerid][i][homePerm] & PERM_HOUSE_LEADER || MemberHome[playerid][i][homePerm] & PERM_HOUSE_MEMBER))
	            {
					format(list_doors, sizeof(list_doors), "%s\n%d\t%s", list_doors, DoorInfo[i][dUID], DoorInfo[i][dName]);
				}
			}

            if(strlen(list_doors) != 0) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Informacja", list_doors, "Zamknij", "");
			else Infobox(playerid, 5, "Nie znaleziono ~b~~h~zadnych ~w~~h~mieszkan.");
        }
        else if(!strcmp(comm1, "zaproœ", true) || !strcmp(comm1, "zapros", true))
        {
            new doorid = PlayerDoor[playerid];
			new playerid2;
			
			if(sscanf(comm2, "i", playerid2))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /dom zaproœ [ID gracza]", "Zamknij", "");
        		return 1;
			}
			else
			{
	            if(!doorid)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie znajdujesz siê w ¿adnych ze drzwi.", "Zamknij", "");
	                return 1;
	            }
	            if(DoorInfo[doorid][dOwnerType] != OWNER_HOUSE)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Drzwi, w których siê znajdujesz nie s¹ ustawione jako mieszkalne.\nJe¿eli nale¿¹ do Ciebie, u¿yj komendy /dom.", "Zamknij", "");
	                return 1;
	            }
	            if(!(MemberHome[playerid][doorid][homePerm] & PERM_HOUSE_LEADER))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie posiadasz uprawnieñ do zapraszania cz³onków, do domu.", "Zamknij", "");
	                return 1;
	            }
	            if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Wybrany przez Ciebie gracz, nie jest zalogowany.", "Zamknij", "");
	                return 1;
	            }
	            if(!PlayerToPlayer(5.0, playerid, playerid2))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie znajdujesz siê w pobli¿u wybranego gracza.", "Zamknij", "");
	                return 1;
	            }
	            if(MemberHome[playerid2][doorid][homeDoorID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Gracz znajduje siê ju¿ w Twoim mieszkaniu.", "Zamknij", "");
	                return 1;
	            }
	            
				mysql_query_format("INSERT INTO `fc_member_door` VALUES ('%d', '%d', '%s', '%d', '%d')", DoorInfo[doorid][dUID], PERM_HOUSE_MEMBER, "Mieszkaniec", 0, CharacterCache[playerid2][pUID]);
				
				LoadPlayerHouse(playerid2);
				
				format(string, sizeof(string), "Zaprosi³eœ gracza %s (ID: %d) do swojego mieszkania (UID: %d).", PlayerName2(playerid2), playerid2, DoorInfo[doorid][dUID]);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
				
				format(string, sizeof(string), "%s (ID: %d) zaprosi³ Ciebie do mieszkania (UID: %d).", PlayerName2(playerid), playerid, DoorInfo[doorid][dUID]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
            }
		}
		else if(!strcmp(comm1, "wyproœ", true) || !strcmp(comm1, "wypros", true))
        {
            new doorid = PlayerDoor[playerid];
            new playerid2;
            
   			if(sscanf(comm2, "i", playerid2))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /dom wyproœ [ID gracza]", "Zamknij", "");
        		return 1;
			}
			else
			{
				if(!doorid)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie znajdujesz siê w ¿adnych ze drzwi.", "Zamknij", "");
	                return 1;
	            }
	            if(DoorInfo[doorid][dOwnerType] != OWNER_HOUSE)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Drzwi, w których siê znajdujesz nie s¹ ustawione jako mieszkalne.\nJe¿eli nale¿¹ do Ciebie, u¿yj komendy /dom.", "Zamknij", "");
	                return 1;
	            }
	            if(!(MemberHome[playerid][doorid][homePerm] & PERM_HOUSE_LEADER))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie posiadasz uprawnieñ do wypraszania cz³onków mieszkania.", "Zamknij", "");
	                return 1;
	            }
			    if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Wybrany przez Ciebie gracz, nie jest zalogowany.", "Zamknij", "");
	                return 1;
	            }
	            if(!MemberHome[playerid2][doorid][homeDoorID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Gracz nie nale¿y do wybranego mieszkania.", "Zamknij", "");
	                return 1;
	            }
	            
	            mysql_query_format("DELETE FROM `fc_member_door` WHERE `char_id` = '%d' AND `doorid` = '%d'", CharacterCache[playerid2][pUID], DoorInfo[doorid][dUID]);
	            
	            LoadPlayerHouse(playerid2);
	            
   				format(string, sizeof(string), "Wyprosi³eœ gracza %s (ID: %d) ze swojego mieszkania (UID: %d).", PlayerName2(playerid2), playerid2, DoorInfo[doorid][dUID]);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

				format(string, sizeof(string), "%s (ID: %d) wyprosi³ Ciebie z mieszkania (UID: %d).", PlayerName2(playerid), playerid, DoorInfo[doorid][dUID]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}
        }
        else if(!strcmp(comm1, "czynsz", true))
        {
            new doorid = PlayerDoor[playerid];
        	new playerid2, cash;
        	
   			if(sscanf(comm2, "id", playerid2, cash))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /dom czynsz [ID gracza] [kwota]", "Zamknij", "");
        		return 1;
			}
			else
			{
				if(!doorid)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie znajdujesz siê w ¿adnych ze drzwi.", "Zamknij", "");
	                return 1;
	            }
	            if(DoorInfo[doorid][dOwnerType] != OWNER_HOUSE)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Drzwi, w których siê znajdujesz nie s¹ ustawione jako mieszkalne.\nJe¿eli nale¿¹ do Ciebie, u¿yj komendy /dom.", "Zamknij", "");
	                return 1;
	            }
	            if(!(MemberHome[playerid][doorid][homePerm] & PERM_HOUSE_LEADER))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie posiadasz uprawnieñ do ustawiania czynszu najemc¹ mieszkania.", "Zamknij", "");
	                return 1;
	            }
			    if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Wybrany przez Ciebie gracz, nie jest zalogowany.", "Zamknij", "");
	                return 1;
	            }
	            if(!MemberHome[playerid2][doorid][homeDoorID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Gracz nie nale¿y do wybranego mieszkania.", "Zamknij", "");
	                return 1;
	            }
	            
	            MemberHome[playerid2][doorid][homePrice] = cash;
	            
   				format(string, sizeof(string), "Zmieni³eœ graczowi %s (ID: %d) kwotê czynszu w mieszkaniu (UID: %d) na $%d.", PlayerName2(playerid2), playerid2, DoorInfo[doorid][dUID], cash);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

				format(string, sizeof(string), "%s (ID: %d) zmieni³ Tobie kwotê czynszu w mieszkaniu (UID: %d) na $%d.", PlayerName2(playerid), playerid, DoorInfo[doorid][dUID], cash);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}
        }
        else if(!strcmp(comm1, "online", true))
        {
            new list_online[256];
			new doorid = PlayerDoor[playerid];
            
        	if(!doorid)
         	{
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie znajdujesz siê w ¿adnych ze drzwi.", "Zamknij", "");
	            return 1;
          	}
	        if(DoorInfo[doorid][dOwnerType] != OWNER_HOUSE)
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Drzwi, w których siê znajdujesz nie s¹ ustawione jako mieszkalne.\nJe¿eli nale¿¹ do Ciebie, u¿yj komendy /dom.", "Zamknij", "");
	            return 1;
          	}

			ForeachEx(i, MAX_DOORS)
			{
			    if(MemberHome[i][doorid][homePerm] & PERM_HOUSE_MEMBER || MemberHome[i][doorid][homePerm] & PERM_HOUSE_LEADER)
			    {
			        format(list_online, sizeof(list_online), "%s\n%d\t%s", list_online, i, PlayerName2(i));
			    }
			}
			
			if(strlen(list_online) != 0) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Informacja", list_online, "Zamknij", "");
			else Infobox(playerid, 5, "Brak ~g~~h~wolnych ~w~~h~mieszkan.");
        }
	}
	
	return 1;
}

CMD:przejazd(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
    if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        ForeachEx(i, MAX_DOORS)
		{
			if(PlayerToPoint(5.0, playerid, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ]) && GetPlayerVirtualWorld(playerid) == DoorInfo[i][dEnterVw] && DoorInfo[i][dLock] == 1)
			{
                if(DoorInfo[i][dGarage] == 1)
				{
					SetVehicleVirtualWorld(vehicleid, DoorInfo[i][dExitVw]);
					SetVehiclePos(vehicleid, DoorInfo[i][dExitX], DoorInfo[i][dExitY], DoorInfo[i][dExitZ]);
					SetVehicleZAngle(vehicleid, DoorInfo[i][dExitAng]);
					LinkVehicleToInterior(vehicleid, DoorInfo[i][dExitInt]);
					ForeachEx(x, MAX_PLAYERS)
					{
					    if(GetPlayerVehicleID(x) == GetPlayerVehicleID(playerid))
					    {
							SetPlayerVirtualWorld(x, DoorInfo[i][dExitVw]);
							SetPlayerInterior(x, DoorInfo[i][dExitInt]);
						}
					}
				}
			}
			if(PlayerToPoint(5.0, playerid, DoorInfo[i][dExitX], DoorInfo[i][dExitY], DoorInfo[i][dExitZ]) && GetPlayerVirtualWorld(playerid) == DoorInfo[i][dExitVw] && DoorInfo[i][dLock] == 1)
			{
			    if(DoorInfo[i][dGarage] == 1)
				{
					SetVehicleVirtualWorld(vehicleid, DoorInfo[i][dEnterVw]);
					SetVehiclePos(vehicleid, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ]);
					SetVehicleZAngle(vehicleid, DoorInfo[i][dEnterAng]);
					LinkVehicleToInterior(vehicleid, DoorInfo[i][dEnterInt]);
					ForeachEx(x, MAX_PLAYERS)
					{
					    if(GetPlayerVehicleID(x) == GetPlayerVehicleID(playerid))
					    {
							SetPlayerVirtualWorld(x, DoorInfo[i][dEnterVw]);
							SetPlayerInterior(x, DoorInfo[i][dEnterInt]);
						}
					}
				}
			}
		}
	}
	return 1;
}

CMD:wyscig(playerid, params[])
{
	new comm1[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /wyscig [lista | stwórz]", "Zamknij", "");
	    return 1;
	}
	else
	{
	    if(!strcmp(comm1, "lista", true))
	    {
	        new list_races[512];
	        
	        ForeachEx(i, MAX_RACES)
	        {
	            if(RaceInfo[i][raceCreated] == CharacterCache[playerid][pUID])
	            {
	                format(list_races, sizeof(list_races), "%s\n%d\t%s", list_races, RaceInfo[i][raceID], RaceInfo[i][raceName]);
	            }
	        }
	        
	        if(strlen(list_races) != 0) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Informacja", list_races, "Rozpocznij", "Zamknij");
	        else Infobox(playerid, 5, "Brak ~g~~h~~h~dostepnych ~w~~h~wyscigow.");
	    }
	    else if(!strcmp(comm1, "stwórz", true) || !strcmp(comm1, "stworz", true))
	    {
	        new name[32], string[32];
	        if(sscanf(comm2, "s[32]", name))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /wyscig stwórz [nazwa wyœcigu]", "Zamknij", "");
	    		return 1;
	        }
	        else
		 	{
		 	    //AddRace(CharacterCache[playerid][pUID], name);
		 	    
		 	    format(string, sizeof(string), "~r~CheckPoint ~w~%d/30", 0);
				GameTextForPlayer(playerid, string, 60000, 4);
			
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pomyœlnie stworzy³eœ now¹ trasê wyœcigu.\nUstaw teraz CheckPointy na mapie za pomoc¹ klawisza PPM.\n\nPo zakoñczeniu tworzenia trasy u¿yj komendy /wyscig zakoncz.", "Zamknij", "");
		 	}
	    }
	}
	return 1;
}

CMD:pomoc(playerid, params[])
{
	new string[1024];
	
	if(CharacterCache[playerid][pAdmin])
	{
	    if(CharacterCache[playerid][pAdmin] == 9)
			format(string, sizeof(string), "{CC2929}# Administracja\n\t{CC1010}- Komendy\n");
		else if(CharacterCache[playerid][pAdmin] < 9 && CharacterCache[playerid][pAdmin] > 5)
		    format(string, sizeof(string), "{25b000}# Administracja\n\t{CC1010}- Komendy\n");
		else if(CharacterCache[playerid][pAdmin] < 6 && CharacterCache[playerid][pAdmin] > 0)
		    format(string, sizeof(string), "{538668}# Administracja\n\t{CC1010}- Komendy\n");
	}

  	format(string, sizeof(string), "%s{6B6969}# Informacje podstawowe\n\t{ABA9A9}- Administracja\n", string);
	format(string, sizeof(string), "%s{6B6969}# Grupy\n\t{ABA9A9}- Zarz¹dzanie grupami\n\t{ABA9A9}- Zastosowania grup\n", string);
	format(string, sizeof(string), "%s{6B6969}# Pojazdy\n\t{ABA9A9}- Zarz¹dzanie pojazdami\n\t{ABA9A9}- Kupno pojazdu\n\t{ABA9A9}- Mo¿liwoœci pojazdów\n\t{ABA9A9}- Tuning pojazdów\n\t{ABA9A9}- Zabezpieczenie pojazdów\n", string);
	format(string, sizeof(string), "%s{6B6969}# Przedmioty\n\t{ABA9A9}- Zarz¹dzanie przedmiotami\n", string);
	format(string, sizeof(string), "%s{6B6969}# Strefy\n\t{ABA9A9}- Kupno stref\n\t{ABA9A9}- Dzia³anie stref\n\t{ABA9A9}- Przejmowanie strefy\n", string);
	format(string, sizeof(string), "%s{6B6969}# Drzwi\n\t{ABA9A9}- Zarz¹dzanie drzwiami\n", string);
	format(string, sizeof(string), "%s{6B6969}# Gracz\n\t{ABA9A9}- Oferty z graczami\n\t{ABA9A9}- Darowanie gotówki\n\t{ABA9A9}- Zg³aszanie graczy", string);
	
	ShowPlayerDialog(playerid, D_HELP, DIALOG_STYLE_LIST, " Centrum pomocy", string, "Wybierz", "Zamknij");
	return 1;
}

CMD:tog(playerid, params[])
{
    new string[1024];

    format(string, sizeof(string), "{88CC54}-- Ustawienia blokad");

    // Blokada wiadomoœci (PW)
    if(CharacterCache[playerid][pTog] & TOG_PW)
        format(string, sizeof(string), "%s\n\tBlokada wiadomoœci\t\t\t{99FF00}T", string);
    else
        format(string, sizeof(string), "%s\n\tBlokada wiadomoœci\t\t\t{990000}N", string);

    // Textdrawy z audio pluginem
    if(CharacterCache[playerid][pTog] & TOG_AUDIO)
        format(string, sizeof(string), "%s\n\tTextdraw Audio\t\t\t\t{99FF00}T", string);
    else
        format(string, sizeof(string), "%s\n\tTextdraw Audio\t\t\t\t{990000}N", string);

    // Textdraw z nazw¹ serwera
    if(CharacterCache[playerid][pTog] & TOG_NAME)
        format(string, sizeof(string), "%s\n\tTextdraw Serwera\t\t\t{99FF00}T", string);
    else
        format(string, sizeof(string), "%s\n\tTextdraw Serwera\t\t\t{990000}N", string);

    // Textdraw z radiem
    if(CharacterCache[playerid][pTog] & TOG_FM)
        format(string, sizeof(string), "%s\n\tTextdraw Radia\t\t\t\t{99FF00}T", string);
    else
        format(string, sizeof(string), "%s\n\tTextdraw Radia\t\t\t\t{990000}N", string);
        
    // Chaty OOC grup
    if(CharacterCache[playerid][pTog] & TOG_OOC)
        format(string, sizeof(string), "%s\n\tCzaty grupowe OOC\t\t\t{99FF00}T", string);
    else
        format(string, sizeof(string), "%s\n\tCzaty grupowe OOC\t\t\t{990000}N", string);

    format(string, sizeof(string), "%s\n{88CC54}-- Ustawienia konta", string);

    // Edytor klawiszowy obiektów
    if(CharacterCache[playerid][pEditor] == OPTION_EDITOR_KEY)
        format(string, sizeof(string), "%s\n\tEdytor obiektów:\t\t\tKlawiszowy", string);

    // Edytor manualny obiektów
    if(CharacterCache[playerid][pEditor] == OPTION_EDITOR_MACHINE)
        format(string, sizeof(string), "%s\n\tEdytor obiektów:\t\t\tAutomatyczny", string);

    // Freeze po wejœciu do drzwi
    if(CharacterCache[playerid][pOption] & OPTION_FREEZE)
        format(string, sizeof(string), "%s\n\tFreeze w drzwiach:\t\t\t{99FF00}T", string);
    else
        format(string, sizeof(string), "%s\n\tFreeze w drzwiach:\t\t\t{990000}N", string);

    // Animacja mowy
    if(!(CharacterCache[playerid][pOption] & OPTION_SAY))
        format(string, sizeof(string), "%s\n\tAnimacja mowy:\t\t\t\t{99FF00}T", string);
    else
        format(string, sizeof(string), "%s\n\tAnimacja mowy:\t\t\t\t{990000}N", string);

    // Animacja krzyku
    if(!(CharacterCache[playerid][pOption] & OPTION_KRZYK))
        format(string, sizeof(string), "%s\n\tAnimacja krzyku:\t\t\t{99FF00}T", string);
    else
        format(string, sizeof(string), "%s\n\tAnimacja krzyku:\t\t\t{990000}N", string);
        
    // Panoramiczny ekran
    if(CharacterCache[playerid][pOption] & OPTION_PANORAMIC)
        format(string, sizeof(string), "%s\n\tPanoramiczny ekran:\t\t\t{99FF00}T", string);
    else
        format(string, sizeof(string), "%s\n\tPanoramiczny ekran:\t\t\t{990000}N", string);

	if(CharacterCache[playerid][pAdmin])
	{
	    // Token administracyjny
	    if(CharacterCache[playerid][pOption] & OPTION_TOKEN)
	        format(string, sizeof(string), "%s\n\tToken administracyjny:\t\t\t{99FF00}T", string);
	    else
	        format(string, sizeof(string), "%s\n\tToken administracyjny:\t\t\t{990000}N", string);
 	}

    ShowPlayerDialog(playerid, D_TOG, DIALOG_STYLE_LIST, " Informacja", string, "Wybierz", "Zamknij");
    return 1;
}

CMD:me(playerid, params[])
{
    new text[128], string[256];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /me [akcja]", "Zamknij", "");
        return 1;
    }
    else
    {
	    text[0] = chrtolower(text[0]);

	    if(strlen(text) < 78)
	    {
	        format(string, sizeof(string), "* %s %s", PlayerName2(playerid), text);
	        ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	    }
	    else
	    {
	        new pos = strfind(text, " ", true, strlen(text) / 2);
	        if(pos != -1)
	        {
	            new text2[64];

	            strmid(text2, text, pos + 1, strlen(text));
	            strdel(text, pos, strlen(text));

	            format(string, sizeof(string), "* %s %s...", PlayerName2(playerid), text);
	            ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

	            format(string, sizeof(string), "            ...%s", text2);
	            ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	        }
	    }
    }
    return 1;
}
CMD:ja(playerid, params[]) return cmd_me(playerid, params);

CMD:do(playerid, params[])
{
    new text[128], string[256];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /do [sytuacja]", "Zamknij", "");
        return 1;
    }
    else
    {
	    text[0] = chrtoupper(text[0]);

	    if(strlen(text) < 78)
	    {
	        format(string, sizeof(string), "* %s (( %s ))", text, PlayerName2(playerid));
	        ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO);
	    }
	    else
	    {
	        new pos = strfind(text, " ", true, strlen(text) / 2);
	        if(pos != -1)
	        {
	            new text2[64];

	            strmid(text2, text, pos + 1, strlen(text));
	            strdel(text, pos, strlen(text));

	            format(string, sizeof(string), "* %s...", text);
	            ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO);

	            format(string, sizeof(string), "            ...%s (( %s ))", text2, PlayerName2(playerid));
	            ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO);
	        }
	    }
    }
    return 1;
}

CMD:report(playerid, params[])
{
    new playerid2, report[128];
    if(sscanf(params, "us[128]", playerid2, report))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /report [ID gracza] [powód]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest aktualnie w grze.", "Zamknij", "");
            return 1;
        }
        if((CharacterCache[playerid][pReport] + 60) > gettime())
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Odczekaj 60 sekund przed napisaniem kolejnego zg³oszenia.", "Zamknij", "");
            return 1;
        }
        if(strfind(report, ":)", true) >= 0 || strfind(report, ":D", true) >= 0  || strfind(report, ":/", true) >= 0  || strfind(report, ":P", true) >= 0  ||
  		   strfind(report, ";)", true) >= 0  || strfind(report, ";D", true) >= 0  || strfind(report, ";/", true) >= 0  || strfind(report, ";P", true) >= 0  ||
	       strfind(report, ";p", true) >= 0  || strfind(report, ":p", true) >= 0  || strfind(report, ":x", true) >= 0 )
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W treœci przesy³anej administratorowi nie u¿ywaj emotikonek.\nNie przyœpieszaj¹ one Twojego zg³oszenia.", "Zamknij", "");
		    return 1;
		}
		if(strfind(report, "kurwa", true) >= 0  || strfind(report, "chuj", true) >= 0  || strfind(report, "wypier", true) >= 0  || strfind(report, "spierd", true) >= 0  || strfind(report, "dupa", true) >= 0  || strfind(report, "cipa", true) >= 0 )
	    {
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W treœci przesy³anej administratorowi zosta³y zawarte wulgaryzmy.\n\nAdministrator udzielaj¹cy Ci pomocy robi to bezinteresownie.\nPraca administratora ma charakter wolontariatu, dlatego uszanuj jego pracê.", "Zamknij", "");
		    return 1;
	    }
	    
        CharacterCache[playerid][pReport] = gettime();

        ForeachEx(i, MAX_PLAYERS)
        {
            if(CharacterCache[i][pAdminDuty])
            {
                if(IsPlayerPremium(playerid)) SendClientMessageFormat(i, 0xF7F0B7FF, "[REPORT][PREMIUM] %s (%d) zg³osi³ gracza %s (%d), powodem: %s", PlayerName2(playerid), playerid, PlayerName2(playerid2), playerid2, report);
                else SendClientMessageFormat(i, 0xF595A0FF, "[REPORT] %s (%d) zg³osi³ gracza %s (%d), powodem: %s", PlayerName2(playerid), playerid, PlayerName2(playerid2), playerid2, report);
            }
        }

        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zg³oszenie zosta³o pomyœlnie wys³ane.\nOczekuj rekacji administratora.\n\nWa¿ne zasady:\n\t1. Pamiêtaj o zachowaniu kultury wobec administratora.\n\t2. Inni gracze te¿ potrzebuj¹ pomocy - oczekuj w spokoju.\n\t3. Wysy³anie ci¹g³ych zg³oszeñ nie przyœpieszy czasu realizacji.", "Zamknij", "");
    }
    return 1;
}

CMD:sprobuj(playerid, params[])
{
    new text[128], string[256];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /sprobuj [akcja np. podnieœæ ciê¿arek]", "Zamknij", "");
        return 1;
    }
    new loss = random(2);
    switch(loss)
    {
        case 0:
        {
            if(!CharacterCache[playerid][pSex])
            {
                format(string, sizeof(string), "%s zawiód³ próbuj¹c %s", PlayerName2(playerid), text);
                ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
            }
            else
            {
                format(string, sizeof(string), "%s zawiod³a próbuj¹c %s", PlayerName2(playerid), text);
                ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
            }
        }
        case 1:
        {
            if(!CharacterCache[playerid][pSex])
            {
                format(string, sizeof(string), "%s odniós³ sukces próbuj¹c %s", PlayerName2(playerid), text);
                ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
            }
            else
            {
                format(string, sizeof(string), "%s odnios³a sukces próbuj¹c %s", PlayerName2(playerid), text);
                ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
            }
        }
    }
    return 1;
}

CMD:stats(playerid, params[])
{
    new id;
    if(sscanf(params, "i", id))
    {
        ShowPlayerStats(playerid, playerid);
    }
    else
    {
        if(CharacterCache[id][pAdmin] == 0) return PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        else if(CharacterCache[id][pUID] == 0) return PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        else
        {
            ShowPlayerStats(playerid, id);
        }
    }

    return 1;
}

CMD:silnik(playerid, params[])
{
    new string[256];
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new vehid = GetVehicleUID(GetPlayerVehicleID(playerid)), model = GetVehicleModel(vehid);
        if(model == 509 || model == 510 || model == 481)
        {
            return 1;
        }
        if(!IsOwnerVehicle(playerid, vehid))
		{
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Silnik w tym pojeŸdzie jest ca³kowicie zniszczony.", "Zamknij", "");
            return 1;
        }
        if(VehicleInfo[vehid][vEngineTogged])
        {
            VehicleInfo[vehid][vEngineTogged] = false;
            ChangeVehicleEngineStatus(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vEngineTogged]);

            format(string, sizeof(string), "** %s gasi silnik pojazdu %s.", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[vehid][vModel]));
            ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
        }
        else
        {
            format(string, sizeof(string), "** %s odpala silnik pojazdu %s.", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[vehid][vModel]));
            ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

            GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~Trwa odpalanie silnika...", 3500, 3);
            SetTimerEx("OnVehicleEngineStarted", 2000, 0, "d", vehid);
        }
    }
    return 1;
}

CMD:przedmiot(playerid, params[])
{
    new type[24], varchar[24];
    if(sscanf(params, "s[24]S()[24]", type, varchar))
    {
        SendClientMessage(playerid, SZARY, "U¿yj: /p(rzedmiot) [podnieœ | szukaj | poka¿]");
        ListPlayerItems(playerid);
        return 1;
    }
    else if(!strcmp(type, "podnieœ", true) || !strcmp(type, "podnies", true) || !strcmp(type, "szukaj", true))
    {
        ListPlayerNearItems(playerid);
    }
    else if(!strcmp(type, "poka¿", true) || !strcmp(type, "pokaz", true))
    {
        new giveplayer_id;
        if(sscanf(varchar, "i", giveplayer_id))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /p(rzedmiot) poka¿ [ID gracza]", "Zamknij", "");
            return 1;
        }
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }
        if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID znajduje siê zbyt daleko od Ciebie.", "Zamknij", "");
            return 1;
        }

        ListPlayerItemsForPlayer(giveplayer_id, playerid);
    }
    return 1;
}
CMD:p(playerid, params[]) return cmd_przedmiot(playerid, params);

CMD:grupa(playerid, params[])
{
    new slot, type[32], varchar[128];
    if(sscanf(params, "ds[32]S()[128]", slot, type, varchar))
    {
        if(CharacterCache[playerid][pShowGroups])
        {
            HidePlayerGroups(playerid);
        }
        else
        {
            ShowPlayerGroups(playerid);
        }
        SendClientMessage(playerid, SZARY, "U¿yj: /g(rupa) {slot (1-3)} [info | przebierz | online | duty | zaproœ | wyproœ | zg³oszenia]");
    }
    else if(slot > 3 || slot == 0 || slot < 0)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony slot grupy jest niepoprawny.", "Zamknij", "");
        return 1;
    }
    else if(MemberGroup[playerid][slot][GroupID] == 0)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Na tym slocie nie posiadasz ¿adnej grupy.", "Zamknij", "");
        return 1;
    }
    else if(!strcmp(type, "info", true))
    {
        new string[1024];
        new hours, minutes, second;
        new groupid = MemberGroup[playerid][slot][GroupID];

        GetPlayedTimeSecZ(MemberGroup[playerid][slot][GroupTime], hours, minutes, second);

        format(string, sizeof(string), "{88CC54}Identyfikator:{FFFFFF}\t\t\t%d", GroupData[groupid][UID]);
        format(string, sizeof(string), "%s\n{88CC54}Nazwa grupy:{FFFFFF}\t\t\t%s", string, GroupData[groupid][Desc]);
        format(string, sizeof(string), "%s\n{88CC54}Tag grupy:{FFFFFF}\t\t\t%s", string, GroupData[groupid][Tag]);
        format(string, sizeof(string), "%s\n{88CC54}Typ grupy:{FFFFFF}\t\t\t%s", string, GroupInfo[GroupData[groupid][Kind]][gName]);
        if(GroupData[groupid][Points] > 800)
            format(string, sizeof(string), "%s\n{88CC54}Punkty aktywnoœci:{FFFFFF}\t\t{8CD147}%d{FFFFFF}", string, GroupData[groupid][Points]);
        else
            format(string, sizeof(string), "%s\n{88CC54}Punkty aktywnoœci:{FFFFFF}\t\t{FFC675}%d{FFFFFF}", string, GroupData[groupid][Points]);
        //format(string, sizeof(string), "%s\n{88CC54}Limit pojazdów:{FFFFFF}\t\t\t0 / %d", string, GroupData[groupid][LimitVehicles]);
        format(string, sizeof(string), "%s\n{88CC54}Stan konta:{FFFFFF}\t\t\t{008000}${FFFFFF} %d", string, GroupData[groupid][Cash]);
        format(string, sizeof(string), "%s\n{88CC54}Kolor grupy:{FFFFFF}\t\t\t{%06x}%x", string, Convert_RGBToHex(GroupData[groupid][Chat][0], GroupData[groupid][Chat][1], GroupData[groupid][Chat][2]), Convert_RGBToHex(GroupData[groupid][Chat][0], GroupData[groupid][Chat][1], GroupData[groupid][Chat][2]));
        if(MemberGroup[playerid][slot][GroupSubGroup])
        {
            new subid = MemberGroup[playerid][slot][GroupSubGroup];
            format(string, sizeof(string), "%s\n--------", string);
            if(SubData[subid][sDesc])
                format(string, sizeof(string), "%s\n{88CC54}Podgrupa:{FFFFFF}\t\t\t%s", string, SubData[subid][sDesc]);
            else
                format(string, sizeof(string), "%s\n{88CC54}Podgrupa:{FFFFFF}\t\t\t%s", string, "Brak");

            if(SubData[subid][sTag])
                format(string, sizeof(string), "%s\n{88CC54}Tag podgrupy:{FFFFFF}\t\t\t%s", string, SubData[subid][sTag]);
            else
                format(string, sizeof(string), "%s\n{88CC54}Tag podgrupy:{FFFFFF}\t\t\t%s", string, "Brak");
        }
        format(string, sizeof(string), "%s\n--------", string);
        format(string, sizeof(string), "%s\n{88CC54}Stanowisko:{FFFFFF}\t\t\t%s", string, MemberGroup[playerid][slot][GroupRank]);
        format(string, sizeof(string), "%s\n{88CC54}Wyp³ata:{FFFFFF}\t\t\t{008000}${FFFFFF} %d", string, MemberGroup[playerid][slot][GroupCash]);
        format(string, sizeof(string), "%s\n{88CC54}Czas s³u¿by:{FFFFFF}\t\t\t%dh, %dmin, %dsek", string, hours, minutes, second);

        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Informacje o grupie", string, "Zamknij", "");
    }
    else if(!strcmp(type, "przebierz", true))
    {
        if(!MemberGroup[playerid][slot][GroupSkin])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Lider grupy nie ustawi³ Tobie ubrania pracowniczego.", "Zamknij", "");
            return 1;
        }
        if(GetPlayerState(playerid) == 4 || GetPlayerState(playerid) == 5 || GetPlayerState(playerid) == 6)
		{
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			return 1;
		}
		
		if(GetPlayerSkin(playerid) == MemberGroup[playerid][slot][GroupSkin])
		{
        	SetPlayerSkin(playerid, CharacterCache[playerid][pSkin]);
        	
        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pomyœlnie za³o¿y³eœ swoje ubranie codzienne.", "Zamknij", "");
        }
        else
        {
       		SetPlayerSkin(playerid, MemberGroup[playerid][slot][GroupSkin]);

        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pomyœlnie za³o¿y³eœ na siebie ubranie pracownicze.", "Zamknij", "");
        }
    }
    else if(!strcmp(type, "online", true))
    {
        new groupid = MemberGroup[playerid][slot][GroupID];
        new string[1024];
        ForeachEx(i, MAX_PLAYERS)
        {
            if(MemberGroup[i][1][GroupID] == groupid || MemberGroup[i][2][GroupID] == groupid || MemberGroup[i][3][GroupID] == groupid)
            {
                if(DutyGroup[i] == groupid) format(string, sizeof(string), "%s\n%d\t%s {FFC675}(S³u¿ba){FFFFFF}", string, i, PlayerName2(i));
                else format(string, sizeof(string), "%s\n%d\t%s{FFFFFF}", string, i, PlayerName2(i));
            }
        }

        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Pracownicy online", string, "Zamknij", "");
    }
    else if(!strcmp(type, "pojazdy", true) || !strcmp(type, "v", true))
    {
        new groupid = MemberGroup[playerid][slot][GroupID];
        new uid, model, strx[256], data[256], list, query[256];

        format(query, sizeof(query), "SELECT `uid`, `model` FROM `fc_vehicles` WHERE `ownertype` = '%d' AND `owner` = '%d'", OWNER_GROUP, groupid);
        mysql_check(); mysql_query(query);

        mysql_store_result();
        while(mysql_fetch_row_format(data, "|"))
        {
            list ++;
            sscanf(data, "p<|>dd", uid, model);
            if(VehicleInfo[uid][vSpawned]) format(strx, sizeof strx, "%s\n%d\tZespawnowany\t\t%s", strx, uid, GetVehicleModelName(model));
            else format(strx, sizeof strx, "%s\n%d\tOdspawnowany\t\t%s", strx, uid, GetVehicleModelName(model));
        }
        mysql_free_result();

        if(strlen(strx) != 0)
        {
            ShowPlayerDialog(playerid, D_VEHICLE_GROUP_OPTIONS, DIALOG_STYLE_LIST, " Pojazdy grupowe:", strx, "Opcje", "Zamknij");
        }
        else
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Grupa nie posiada ¿adnych pojazdów.", "Zamknij", "");
        }
    }
    else if(!strcmp(type, "duty", true) || !strcmp(type, "slu¿ba", true) || !strcmp(type, "sluzba", true))
    {
        if(CharacterCache[playerid][pAdminDuty])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aby wejœæ na s³u¿bê w grupie musisz zakoñczyæ swoj¹ s³u¿bê administracyjn¹.", "Zamknij", "");
            return 1;
        }

        new groupid = MemberGroup[playerid][slot][GroupID];

        if(MemberGroup[playerid][slot][GroupID] == DutyGroup[playerid])
        {
            new hours, minutes, second;
            new color = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0xFF;

            GetPlayedTimeSecZ(DutyGroupTime[playerid], hours, minutes, second);
            SendClientMessageFormat(playerid, color, " » Zszed³eœ ze s³u¿by w grupie %s (%d). Przepracowa³eœ %dh, %dmin, %dsek.", GroupData[groupid][Desc], GroupData[groupid][UID], hours, minutes, second);

            if(minutes > 0) GroupData[groupid][Points] += (minutes * 3);
            SaveMember(playerid, slot);

            if(IsPlayerPremium(playerid)) CharacterCache[playerid][pNickColor] = 0xFCDF1E99;
			else CharacterCache[playerid][pNickColor] = 0xFFFFFF99;
		
            UpdatePlayer3DTextNick(playerid);

            DutyGroup[playerid] = 0;
            DutyGroupSlot[playerid] = 0;
            DutyGroupTime[playerid] = 0;
            
            ReloadGroupIcons();
        }
        else if(DutyGroup[playerid] != 0 && MemberGroup[playerid][slot][GroupID] != DutyGroup[playerid])
        {
            new color = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0xFF;
            new color_nick = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0x99;
            
            SaveMember(playerid, slot);

            DutyGroup[playerid] = GroupData[groupid][UID];
            DutyGroupSlot[playerid] = slot;
            DutyGroupTime[playerid] = 0;

            if(IsGroupHaveFlag(groupid, FLAG_NICK))
            {
                CharacterCache[playerid][pNickColor] = color_nick;
                UpdatePlayer3DTextNick(playerid);
                
                ReloadGroupIcons();
            }

            SendClientMessageFormat(playerid, color, " » Wszed³eœ na s³u¿bê grupy %s (%d). Aby zejœæ ze s³u¿by wpisz /g %d duty.", GroupData[groupid][Desc], GroupData[groupid][UID], slot);
        }
        else if(!DutyGroup[playerid])
        {
            new color = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0xFF;
            new color_nick = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0x99;
            
            DutyGroup[playerid] = GroupData[groupid][UID];
            DutyGroupSlot[playerid] = slot;
            DutyGroupTime[playerid] = 0;

            if(IsGroupHaveFlag(groupid, FLAG_NICK))
            {
                CharacterCache[playerid][pNickColor] = color_nick;
                UpdatePlayer3DTextNick(playerid);
                
                ReloadGroupIcons();
            }

            SendClientMessageFormat(playerid, color, " » Wszed³eœ na s³u¿bê grupy %s (%d). Aby zejœæ ze s³u¿by wpisz /g %d duty.", GroupData[groupid][Desc], GroupData[groupid][UID], slot);
        }
    }
    else if(!strcmp(type, "zaproœ", true) || !strcmp(type, "zapros", true) || !strcmp(type, "invite", true))
    {
        new groupid = MemberGroup[playerid][slot][GroupID];
        new giveplayer_id, string[256];

        if(sscanf(varchar, "i", giveplayer_id))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /g {slot (1-5)} zaproœ [ID gracza]", "Zamknij", "");
            return 1;
        }
        else
        {
            if(!Logged[giveplayer_id])
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz o wybranym 'id' nie jest zalogowany.", "Zamknij", "");
                return 1;
            }
            if(IsPlayerInGroup(giveplayer_id, groupid))
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz o wybranym 'id' znajduje siê ju¿ w Twojej grupie.", "Zamknij", "");
                return 1;
            }

            AddMember(giveplayer_id, groupid, false, false);

            format(string, sizeof(string), "Zaprosi³eœ gracza %s do grupy %s (UID: %d).\nPamiêtaj o ustawieniu mu odpowiednich uprawnieñ w panelu grupy.", PlayerName2(giveplayer_id), GroupData[groupid][Desc], GroupData[groupid][UID]);
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

            format(string, sizeof(string), "Zosta³eœ zaproszony do grupy %s (UID: %d) przez gracza %s.\nUprawnienia dotycz¹ce grupy zostan¹ za³adowane po przelogowaniu.", GroupData[groupid][Desc], GroupData[groupid][UID], PlayerName2(playerid));
            ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
        }
    }
    else if(!strcmp(type, "wyproœ", true) || !strcmp(type, "wypros", true) || !strcmp(type, "out", true))
    {
        new groupid = MemberGroup[playerid][slot][GroupID];
        new giveplayer_id, string[256];

        if(sscanf(varchar, "i", giveplayer_id))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /g {slot (1-5)} wyproœ [ID gracza]", "Zamknij", "");
            return 1;
        }
        else
        {
            if(!Logged[giveplayer_id])
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz o wybranym 'id' nie jest zalogowany.", "Zamknij", "");
                return 1;
            }
            if(!IsPlayerInGroup(giveplayer_id, groupid))
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz o wybranym 'id' nie znajduje siê w Twojej grupie.", "Zamknij", "");
                return 1;
            }
            if(CharacterCache[giveplayer_id][pAdmin] == 9 && CharacterCache[playerid][pAdminDuty])
            {
            	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie mo¿esz usun¹æ osoby Zarz¹du z grupy, w której siê znajduje.\nPotrzeba bycia w grupie mo¿e zale¿eæ od pomocy, któr¹ niesie graczowi.", "Zamknij", "");
                return 1;
            }

            DeleteMember(giveplayer_id, groupid);

            format(string, sizeof(string), "Wyprosi³eœ gracza %s z grupy %s (UID: %d).\nJego uprawnienia zosta³y zabrane.", PlayerName2(giveplayer_id), GroupData[groupid][Desc], GroupData[groupid][UID]);
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

            format(string, sizeof(string), "Zosta³eœ wyproszony z grupy %s (UID: %d) przez gracza %s.\nUprawnienia dotycz¹ce grupy zosta³y zabrane.", GroupData[groupid][Desc], GroupData[groupid][UID], PlayerName2(playerid));
            ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
        }
    }
    else if(!strcmp(type, "gps", true) || !strcmp(type, "police", true))
    {
        if(!IsPermGroupFlag(playerid, FLAG_GPS))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ywania nadajnika GPS.", "Zamknij", "");
	        return 1;
	    }
        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aby uruchomiæ nadajnik GPS musisz znajdowaæ siê w pojeŸdzie.", "Zamknij", "");
            return 1;
        }
        if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Uruchomiæ nadajnik GPS mo¿esz tylko znajduj¹c siê poza budynkiem.", "Zamknij", "");
            return 1;
        }

        new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
        if(!VehicleInfo[vehid][vUseGPS])
        {
            VehicleInfo[vehid][vUseGPS] = true;

            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nadajnik GPS w pojeŸdzie zosta³ pomyœlnie w³¹czony.", "Zamknij", "");
        }
        else
        {
            VehicleInfo[vehid][vUseGPS] = false;

            ForeachEx(player, MAX_PLAYERS)
                ForeachEx(i, 100)
                    if(i > 5)
                    	RemovePlayerMapIcon(player, i);

            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nadajnik GPS w pojeŸdzie zosta³ pomyœlnie wy³¹czony.", "Zamknij", "");
        }
    }
    else if(!strcmp(type, "zg³oszenia", true) || !strcmp(type, "zgloszenia", true) || !strcmp(type, "z", true))
    {
        new groupid = MemberGroup[playerid][slot][GroupID];
        new list_reports[1024];
        
        if(!(GroupData[groupid][Flags] & FLAG_REPORTS))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Grupa nie posiada uprawnieñ do zarz¹dzania zg³oszeniami grupowymi.", "Zamknij", "");
            return 1;
        }
        
        ForeachEx(i, MAX_REPORTS)
        {
            if(ReportInfo[i][reportGroup] == GroupData[groupid][UID])
            {
				if(ReportInfo[i][reportStatus] == CharacterCache[playerid][pUID]) format(list_reports, sizeof(list_reports), "%s\n%d\t%s {FFC675}[W trakcie]", list_reports, ReportInfo[i][reportID], ReportInfo[i][reportCharName]);
                else format(list_reports, sizeof(list_reports), "%s\n%d\t%s", list_reports, ReportInfo[i][reportID], ReportInfo[i][reportCharName]);
            }
        }
        
        if(strlen(list_reports) != 0) ShowPlayerDialog(playerid, D_REPORTS, DIALOG_STYLE_LIST, " Zg³oszenia grupowe", list_reports, "Wybierz", "Zamknij");
        else Infobox(playerid, 5, "Brak ~g~~h~~h~dostepnych ~w~~h~zgloszen grupowych.");
    }
    else if(!strcmp(type, "magazyn", true))
    {
        new groupid = MemberGroup[playerid][slot][GroupID];
        
        new data[64], list_items[1024], query[256];
	    new item_uid, item_name[32], item_value1, item_value2, item_value;

	    format(query, sizeof(query), "SELECT `uid`, `name`, `value1`, `value2`, `value` FROM `fc_items` WHERE `owner` = '%d' AND `ownertype` = '%d'", GroupData[groupid][UID], OWNER_GROUP);
	    mysql_check(); mysql_query(query);

	    mysql_store_result();

	    while(mysql_fetch_row_format(data, "|"))
	    {
	        sscanf(data, "p<|>ds[32]ddd", item_uid, item_name, item_value1, item_value2, item_value);

	        format(list_items, sizeof(list_items), "%s\n{000000}%d\t%d\t%d\t{FFFFFF}%s (%d sztuk)", list_items, item_uid, item_value1, item_value2, item_name, item_value);
	    }
	    mysql_free_result();

	    if(strlen(list_items) != 0) ShowPlayerDialog(playerid, D_GROUP_MAGAZINE, DIALOG_STYLE_LIST, " Magazyn grupy", list_items, "Wyci¹gnij", "Zamknij");
	    else Infobox(playerid, 5, "Nie znaleziono ~g~~h~¿adnych~w~~h~ przedmiotów w magazynie.");
    }
    return 1;
}
CMD:g(playerid, params[]) return cmd_grupa(playerid, params);

CMD:pojazd(playerid, params[])
{
    new type[32], varchar[128];
    if(sscanf(params, "s[32]S()[128]", type, varchar))
    {
        if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            new vehid = GetPlayerVehicleID(playerid);

            new list_manage[512];
            if(GetVehicleBonnetStatus(vehid)  != 1)     strcat(list_manage, "Maska:\t\t{CC1010}Zamkniêta\n");
            else                                        strcat(list_manage, "Maska:\t\t{89C217}Otwarta\n");

            if(GetVehicleBootStatus(vehid) != 1)        strcat(list_manage, "Baga¿nik:\t{CC1010}Zamkniêty\n");
            else                                        strcat(list_manage, "Baga¿nik:\t{89C217}Otwarty\n");

            if(GetVehicleLightsStatus(vehid)  != 1)     strcat(list_manage, "Œwiat³a:\t\t{CC1010}Zgaszone\n");
            else                                        strcat(list_manage, "Œwiat³a:\t\t{89C217}Zapalone\n");

            strcat(list_manage, "{6B6969}-- Opcje dotycz¹ce pojazdu\n");
            strcat(list_manage, "{ABA9A9}#{FFFFFF} Informacje o pojeŸdzie\n");
            strcat(list_manage, "{ABA9A9}#{FFFFFF} Przeszukaj pojazd\n");
            strcat(list_manage, "{ABA9A9}#{FFFFFF} Przepisz pojazd\n");
			strcat(list_manage, "{ABA9A9}#{FFFFFF} Poka¿ tuning\n");

            ShowPlayerDialog(playerid, D_MANAGE_VEH, DIALOG_STYLE_LIST, " Zarz¹dzanie pojazdem", list_manage, "Wybierz", "Anuluj");
        }
        else
        {
            cmd_pojazd(playerid, "lista");
            SendClientMessage(playerid, SZARY, "U¿yj: /pojazd [lista | namierz | zaparkuj | przypisz | zamknij | info | tuning | kogut]");
        }
    }
    else
    {
        if(!strcmp(type, "lista", true))
        {
            new uid, model, strx[512], data[256], list = 0, query[256];
            format(query, sizeof(query), "SELECT `uid`, `model` FROM `fc_vehicles` WHERE `ownertype` = '%d' AND `owner` = '%d'", OWNER_PLAYER, CharacterCache[playerid][pUID]);
            mysql_check(); mysql_query(query);

            mysql_store_result();

            format(strx, sizeof strx, "{C0C0C0}-- Lista dostêpnych pojazdów");

            while(mysql_fetch_row_format(data, "|"))
            {
                list ++;
                sscanf(data, "p<|>dd", uid, model);

                if(VehicleInfo[uid][vGameID])
                    format(strx, sizeof strx, "%s\n%d\tZespawnowany\t\t%s", strx, uid, GetVehicleModelName(model));
                else
                    format(strx, sizeof strx, "%s\n%d\tOdspawnowany\t\t%s", strx, uid, GetVehicleModelName(model));
            }
            mysql_free_result();

            if(list != 0)
            {
                ShowPlayerDialog(playerid, D_LIST_PLAYER_CARS, DIALOG_STYLE_LIST, " Lista posiadanych pojazdów:", strx, "(Un)spawn", "Zamknij");
            }
            else
            {
                Infobox(playerid, 5, "Nie posiadasz ~g~~h~¿adnych~w~~h~ pojazdów.");
            }
        }
        else if(!strcmp(type, "zamknij", true) || !strcmp(type, "z", true))
        {
            new vehid = GetVehicleUID(GetClosestVehicle(playerid)), string[128];

            if(!IsOwnerVehicle(playerid, vehid))
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz kluczyków do tego pojazdu.", "Zamknij", "");
                return 1;
            }
            new Float:VehX, Float:VehY, Float:VehZ;
            GetVehiclePos(vehid, VehX, VehY, VehZ);

            if(VehicleInfo[vehid][vLocked])
            {
                GameTextForPlayer(playerid, "~w~Pojazd ~g~otwarty", 4000, 6);

                ApplyAnimation(playerid,"INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
                PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

                format(string, sizeof(string), "** %s otwiera pojazd %s.", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[vehid][vModel]));
                ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

                VehicleInfo[vehid][vLocked] = false;
                SetVehicleLock(VehicleInfo[vehid][vGameID], false);
            }
            else
            {
                GameTextForPlayer(playerid, "~w~Pojazd ~r~zamkniety", 4000, 6);

                ApplyAnimation(playerid,"INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
                PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

                format(string, sizeof(string), "** %s zamyka pojazd %s.", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[vehid][vModel]));
                ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);

                VehicleInfo[vehid][vLocked] = true;
                SetVehicleLock(VehicleInfo[vehid][vGameID], true);
            }

            SaveVehicle(vehid, SAVE_VEH_COUNT);
        }
        else if(!strcmp(type, "namierz", true))
        {
            if(Checkpoint[playerid])
            {
                DisablePlayerCheckpoint(playerid);

                Checkpoint[playerid] = 0;

                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Namierzanie zosta³o wy³¹czone.", "Zamknij", "");
                return 1;
            }

            new list_veh[256];
            ForeachEx(vehid, MAX_VEHICLES)
            {
                if(VehicleInfo[vehid][vOwnerType] == OWNER_PLAYER && VehicleInfo[vehid][vOwner] == CharacterCache[playerid][pUID] && VehicleInfo[vehid][vSpawned])
                {
                    format(list_veh, sizeof(list_veh), "%s\n%d\t\t%s", list_veh, vehid, GetVehicleModelName(VehicleInfo[vehid][vModel]));
                }
            }

            if(strlen(list_veh) != 0)
            {
                ShowPlayerDialog(playerid, D_LIST_SPAWNED_CARS, DIALOG_STYLE_LIST, "Pojazdy zespawnowane:", list_veh, "Namierz", "Zamknij");
            }
            else
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz ¿adnych pojazdów zespawnowanych w tym momencie.", "Zamknij", "");
            }
        }
        else if(!strcmp(type, "zaparkuj", true))
        {
            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Musisz siedzieæ w pojeŸdzie jako kierowca, aby móc u¿yæ tej komendy.", "Zamknij", "");
                return 1;
            }
            new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
            if(!IsOwnerVehicle(playerid, vehid))
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz kluczyków do tego pojazdu.", "Zamknij", "");
                return 1;
            }
            if(!IsParkingPlaceFree(vehid))
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "To miejsce parkingowe jest ju¿ zajête.", "Zamknij", "");
                return 1;
            }
            new vehuid = VehicleInfo[vehid][vUID];

            GetVehiclePos(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vPosX], VehicleInfo[vehid][vPosY], VehicleInfo[vehid][vPosZ]);
            GetVehicleZAngle(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vPosA]);

            VehicleInfo[vehid][vInteriorID] = GetPlayerInterior(playerid);
            VehicleInfo[vehid][vWorldID] = GetPlayerVirtualWorld(playerid);

            SaveVehicle(vehid, SAVE_VEH_POS);

            new seatid = GetPlayerVehicleSeat(playerid);

            UnspawnVehicle(vehuid);
            LoadVehicle(vehuid);

            ChangeVehicleEngineStatus(VehicleInfo[vehuid][vGameID], VehicleInfo[vehid][vEngineTogged]);

            OnVehicleSpawn(VehicleInfo[vehuid][vGameID]);
            PutPlayerInVehicle(playerid, VehicleInfo[vehuid][vGameID], seatid);

            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pojazd zosta³ zaparkowany pomyœlnie.", "Zamknij", "");
        }
        else if(!strcmp(type, "info", true))
        {
            if(!IsPlayerInAnyVehicle(playerid))
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Musisz siedzieæ w pojeŸdzie, aby móc u¿yæ tej komendy.", "Zamknij", "");
                return 1;
            }
            new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
            if(!IsOwnerVehicle(playerid, vehid))
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz kluczyków do tego pojazdu.", "Zamknij", "");
                return 1;
            }

            ShowPlayerVehicleInfo(playerid, vehid);
        }
        else if(!strcmp(type, "przepisz", true))
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
                new string[512];
                new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
                SetPVarInt(playerid, "VehicleChangeID", vehid);

                if(VehicleInfo[vehid][vOwnerType] == OWNER_PLAYER && VehicleInfo[vehid][vOwner] == CharacterCache[playerid][pUID])
                {
                    if(MemberGroup[playerid][1][GroupID])
                    {
                        new groupid_1 = MemberGroup[playerid][1][GroupID];
                        format(string, sizeof(string), "%s\n%d - %s", string, GroupData[groupid_1][UID], GroupData[groupid_1][Desc]);
                    }
                    if(MemberGroup[playerid][2][GroupID])
                    {
                        new groupid_2 = MemberGroup[playerid][1][GroupID];
                        format(string, sizeof(string), "%s\n%d - %s", string, GroupData[groupid_2][UID], GroupData[groupid_2][Desc]);
                    }
                    if(MemberGroup[playerid][3][GroupID])
                    {
                        new groupid_3 = MemberGroup[playerid][1][GroupID];
                        format(string, sizeof(string), "%s\n%d - %s", string, GroupData[groupid_3][UID], GroupData[groupid_3][Desc]);
                    }

                    ShowPlayerDialog(playerid, D_CHANGE_VEHICLE, DIALOG_STYLE_LIST, " Przepisywanie pojazdu", string, "Przepisz", "Anuluj");
                }
                else if(VehicleInfo[vehid][vOwnerType] == OWNER_GROUP)
                {
                    if(IsPlayerPermInGroup(playerid, VehicleInfo[vehid][vOwner], PANEL_OPTION_VEH))
                    {
                        ShowPlayerDialog(playerid, D_SLOT_VEHICLE, DIALOG_STYLE_LIST, " Zamiana uprawnieñ pojazdu", "1. Ustaw jako pojazd zwyk³y\n2. Ustaw jako pojazd specjalny (*)\n3. Przepisz na podgrupê", "Ustaw", "Zamknij");
                    }
                    else
                    {
                        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do zmiany poziomu pojazdu.", "Zamknij", "");
                        return 1;
                    }
                }
                else
                {
                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do przepisania pojazdu na inn¹ grupê.", "Zamknij", "");
                    return 1;
                }
            }
            else
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aby przepisaæ pojazd na inn¹ grupê, musisz znajdowaæ siê w œrodku pojazdu.", "Zamknij", "");
                return 1;
            }
        }
        else if(!strcmp(type, "kogut", true))
        {
            new vehicleid = GetVehicleUID(GetPlayerVehicleID(playerid));
            new syrenaid = Sirene(vehicleid);

            if(!vehicleid)
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pojeŸdzie aby móc w³¹czyæ syrenê.", "Zamknij", "");
                return 1;
            }
            if(!VehicleHaveItemType(vehicleid, TYPE_POLICE))
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W pojeŸdzie nie znajduje siê syrena policyjna.", "Zamknij", "");
                return 1;
            }
            if(!syrenaid)
            {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Na ten model pojazdu nie mo¿na za³o¿yæ koguta policyjnego.", "Zamknij", "");
                return 1;
            }

            if(VehicleInfo[vehicleid][vPolice] == 0)
            {
                VehicleInfo[vehicleid][vPolice] = CreateObject(18646,0,0,0,0,0,0);
                AttachObjectToVehicle(VehicleInfo[vehicleid][vPolice], VehicleInfo[vehicleid][vGameID], SyrenaPos[syrenaid][sX], SyrenaPos[syrenaid][sY], SyrenaPos[syrenaid][sZ], 0.0, 0.0, 0.0);

                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Kogut policyjny zosta³ pomyœlnie wyjêty na dach pojazdu.", "Zamknij", "");
            }
            else
            {
                DestroyObject(VehicleInfo[vehicleid][vPolice]);
                VehicleInfo[vehicleid][vPolice] = 0;

                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Kogut policyjny zosta³ pomyœlnie schowany do schowka pojazdu.", "Zamknij", "");
            }
        }
        else if(!strcmp(type, "tuning", true))
        {
            new vehicleid = GetVehicleUID(GetPlayerVehicleID(playerid));
            new data[64], list_tuning[256];
			new uid, name[32];
            
            mysql_check();
            mysql_query_format("SELECT * FROM `fc_items` WHERE `owner` = '%d' AND `ownertype` = '%d'", VehicleInfo[vehicleid][vUID], OWNER_VEHICLE);
            
            mysql_store_result();
            
            while(mysql_fetch_row_format(data, "|"))
            {
                sscanf(data, "p<|>ds[32]", uid, name);
                
                format(list_tuning, sizeof(list_tuning), "%s\n%d\t%d", list_tuning, uid, name);
            }
            
            mysql_free_result();
            
            if(strlen(list_tuning) != 0) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Informacja", list_tuning, "Zamknij", "");
            else Infobox(playerid, 5, "Brak ~g~~h~tuningu ~w~~h~w pojezdzie.");
        }
    }
    return 1;
}
CMD:v(playerid, params[]) return cmd_pojazd(playerid, params);

CMD:drzwi(playerid, params[])
{
    new comm1[32], comm2[128];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /drzwi [zamknij | opcje]", "Zamknij", "");
        return 1;
    }
    else if(!strcmp(comm1,"opcje",true))
    {
        if(!PlayerDoor[playerid])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy.", "Zamknij", "");
            return 1;
        }
        if(!IsOwnerDoor(playerid, PlayerDoor[playerid]))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie jesteœ w³aœcicielem tego budynku.", "Zamknij", "");
            return 1;
        }

        new doorid = PlayerDoor[playerid];
        new string[128];

        format(string, sizeof(string), "%s (UID: %d) » Opcje", DoorInfo[doorid][dName], DoorInfo[doorid][dUID]);
        if(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_DOORS) ShowPlayerDialog(playerid, D_DOOR_OPTIONS, DIALOG_STYLE_LIST, string, "1. Zmieñ nazwê drzwi\n2. Ustal koszt wstêpu\n3. Wczytaj obiekty\n4. Muzyka spoza gry\n5. Mo¿liwoœæ przejazdu\n6. Ustaw pozycje wejœcia\n7. Poka¿ schowek drzwi\n8. Usuñ ostatni stworzony obiekt\n{D42A2A}9. Usuñ wszystkie obiekty", "Wybierz", "Anuluj");
        else ShowPlayerDialog(playerid, D_DOOR_OPTIONS, DIALOG_STYLE_LIST, string, "1. Zmieñ nazwê drzwi\n2. Ustal koszt wstêpu\n3. Wczytaj obiekty\n4. Muzyka spoza gry\n5. Mo¿liwoœæ przejazdu\n6. Ustaw pozycje wejœcia\n7. Poka¿ schowek drzwi\n8. Usuñ ostatni stworzony obiekt", "Wybierz", "Anuluj");
    }
    else if(!strcmp(comm1,"schowek",true))
    {
        new doorid = PlayerDoor[playerid];
        if(!doorid)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy.", "Zamknij", "");
            return 1;
        }
        if(!IsOwnerDoor(playerid, PlayerDoor[playerid]))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie jesteœ w³aœcicielem tego budynku.", "Zamknij", "");
            return 1;
        }

        new data[64], uid, name[32], value;
        new list_items[512], temp = 0, mysql[256];

        format(mysql, sizeof(mysql), "SELECT `uid`, `name`, `value` FROM `fc_items` WHERE `owner` = '%d' AND `ownertype` = '%d'", DoorInfo[doorid][dUID], OWNER_DOOR);
        mysql_query(mysql);

        mysql_store_result();
        while(mysql_fetch_row_format(data, "|"))
        {
            sscanf(data, "p<|>ds[32]d", uid, name, value);
            format(list_items, sizeof(list_items), "%s\n%d\t%s (%d sztuk)", list_items, uid, name, value);
            temp++;
        }
        mysql_free_result();

        if(strlen(list_items) != 0)
        {
            ShowPlayerDialog(playerid, D_DOOR_ITEMS, DIALOG_STYLE_LIST, "Przedmioty ze schowka", list_items, "Wyci¹gnij", "Zamknij");
        }
        else Infobox(playerid, 5, "Nie znaleziono ~g~~h~zadnych~w~~h~ przedmiotow w schowku.");
    }
    else if(!strcmp(comm1,"zamknij",true) || !strcmp(comm1,"z",true))
    {
        new doorid = GetClosestDoor(playerid);
        if(!doorid)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie jesteœ w pobli¿u ¿adnych drzwi.", "Zamknij", "");
            return 1;
        }
        if(!IsOwnerDoorUnPermission(playerid, PlayerDoor[playerid]))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie jesteœ w³aœcicielem tego budynku.", "Zamknij", "");
            return 1;
        }
        if(DoorInfo[doorid][dLock] == 1)
        {
            GameTextForPlayer(playerid, "~n~~n~~n~~r~~h~Drzwi zamkniete!", 2000, 5);

            DoorInfo[doorid][dLock] = 0;

            ForeachEx(x, MAX_PLAYERS)
            {
                if(PlayerToPlayer(10.0, playerid, x))
                {
                    PlayerPlaySound(x, 1145, 0.0, 0.0, 0.00);
                }
            }

            if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid,"INT_HOUSE","wash_up",4.1,0,0,0,0,0);
            cmd_me(playerid, "zamyka drzwi za pomoc¹ klucza.");
        }
        else
        {
            GameTextForPlayer(playerid, "~n~~n~~n~~g~~h~Drzwi otwarte!", 2000, 5);

            DoorInfo[doorid][dLock] = 1;

            ForeachEx(x, MAX_PLAYERS)
            {
                if(PlayerToPlayer(10.0, playerid, x))
                {
                    PlayerPlaySound(x, 1145, 0.0, 0.0, 0.00);
                }
            }

            if(!IsPlayerInAnyVehicle(playerid)) ApplyAnimation(playerid,"INT_HOUSE","wash_up",4.1,0,0,0,0,0);
            cmd_me(playerid, "otwiera drzwi za pomoc¹ klucza.");
        }
    }
    return 1;
}

CMD:tc(playerid, params[])
{
	if(!IsPlayerPremium(playerid))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz aktywnego konta premium.\nZakup konto poprzez dostêpny panel na stronie.", "Zamknij", "");
	    return 1;
	}
	
	new Float:range, text[256];
	if(sscanf(params, "fs[256]", range, text))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /tc [zasiêg tekstu] [tekst]", "Zamknij", "");
		return 1;
	}
	else
	{
	    new string[256];
	    new doorid = PlayerDoor[playerid];
	    
	    if(IsOwnerDoor(playerid, doorid))
	    {
	        new uid = AddLabel(playerid, OWNER_DOOR, doorid, range, text, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	        
	        format(string, sizeof(string), "Tekst (UID: %d) zosta³ pomyœlnie stworzony.\nAby rozpocz¹æ edycjê u¿yj komendy /tc.", uid);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", string, "Zamknij", "");
	    }
	    else if(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_OBJECT)
	    {
     		new uid = AddLabel(playerid, OWNER_ADMIN, CharacterCache[playerid][pUID], range, text, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

	        format(string, sizeof(string), "Tekst (UID: %d) zosta³ pomyœlnie stworzony.\nAby rozpocz¹æ edycjê u¿yj komendy /tc.", uid);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", string, "Zamknij", "");
	    }
	    else
	    {
	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do stworzenia nowego 3D Tekstu.", "Zamknij", "");
         	return 1;
	    }
	}
	
	return 1;
}

CMD:tsel(playerid, params[])
{
	if(!IsPlayerPremium(playerid))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz aktywnego konta premium.\nZakup konto poprzez dostêpny panel na stronie.", "Zamknij", "");
	    return 1;
	}
	if(CharacterCache[playerid][pMove3DText])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie edytujesz ju¿ jeden z napisów.", "Zamknij", "");
		return 1;
	}
	
    new label_id = GetClosestLabel(playerid);
    
    if(!label_id)
    {
    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W pobli¿u nie znaleziono ¿adnego z 3d tekstów.", "Zamknij", "");
    	return 1;
    }
    
    CharacterCache[playerid][pMove3DText] = label_id;
    CharacterCache[playerid][pMove3DTextPhase] = PHASE_UDRL;

	TogglePlayerControllable(playerid, 0);

	SetPlayerCameraPos(playerid, LabelInfo[label_id][labelPos][0] + 3, LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
	SetPlayerCameraLookAt(playerid, LabelInfo[label_id][labelPos][0], LabelInfo[label_id][labelPos][1], LabelInfo[label_id][labelPos][2]);
	
	Infobox(playerid, 10, "Edycja obiektu tekstu zostala ~g~~h~rozpoczeta~w~~h~.~n~~n~~g~~h~ENTER ~w~~h~- pozwala na zapis tekstu.~n~~g~~h~Strzalki ~w~~h~- poruszanie tekstem~n~~g~~h~Shift ~w~~h~- zmiana trybu edycji tekstu.");
    return 1;
}

CMD:tsave(playerid, params[])
{
    if(!IsPlayerPremium(playerid))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz aktywnego konta premium.\nZakup konto poprzez dostêpny panel na stronie.", "Zamknij", "");
	    return 1;
	}
    if(!CharacterCache[playerid][pMove3DText])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "W tym momencie nie edytujesz ¿adnego z napisów.", "Zamknij", "");
		return 1;
	}
	
	new label_id = CharacterCache[playerid][pMove3DText];
	SaveLabel(label_id);

	CharacterCache[playerid][pMove3DText] = 0;
	CharacterCache[playerid][pMove3DTextPhase] = PHASE_NONE;

	TogglePlayerControllable(playerid, 1);
	SetCameraBehindPlayer(playerid);
	
	Infobox(playerid, 5, "Tekst zosta³ zapisany.");
	return 1;
}

CMD:tdel(playerid, params[])
{
    if(!IsPlayerPremium(playerid))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz aktywnego konta premium.\nZakup konto poprzez dostêpny panel na stronie.", "Zamknij", "");
	    return 1;
	}
    if(!CharacterCache[playerid][pMove3DText])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "W tym momencie nie edytujesz ¿adnego z napisów.", "Zamknij", "");
		return 1;
	}

	new label_id = CharacterCache[playerid][pMove3DText];
	DeleteLabel(label_id);

	CharacterCache[playerid][pMove3DText] = 0;
	CharacterCache[playerid][pMove3DTextPhase] = PHASE_NONE;

	TogglePlayerControllable(playerid, 1);
	SetCameraBehindPlayer(playerid);
	
	Infobox(playerid, 5, "Tekst zosta³ usuniêty pomyœlnie.");
	return 1;
}

CMD:mc(playerid, params[])
{
	new model;
    if(sscanf(params, "d", model))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /mc [ID obiektu]", "Zamknij", "");
		return 1;
	}
	else
	{
	    new areaid = GetPlayerArea(playerid); // Definiowanie strefy
	    new doorid = PlayerDoor[playerid]; // Definiowanie drzwi
	    new vw = GetPlayerVirtualWorld(playerid); // Definiowanie œwiata
	    new interior = GetPlayerInterior(playerid); // Definiowanie interioru
	    new Float:Pos[3]; // Definiowanie pozycji
	    
	    // Przypisywanie pozycji
	    GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	    
	    if(IsOwnerDoor(playerid, doorid)) // Tworzenie obiektów gdy jest siê w drzwiach
	    {
	        // Tworzenie obiektu
	        new uid = AddObject(model, OWNER_DOOR, DoorInfo[doorid][dOwner], vw, interior, Pos[0], Pos[1] + 2.0, Pos[2], 0.0, 0.0, 0.0);
	        
	        // Informacja
	        ObjectInfo[uid][oDoor] = doorid;
	        
	        // Definiowanie zmiennych
	        PlayerEditObject[playerid] = uid;
	        EditDynamicObject(playerid, ObjectInfo[uid][oObject]);

			// Informacja o komendach dla gracza
			Infobox(playerid, 10, "Rozpoczeles ~g~~h~edycje obiektu~w~~h~.~n~~n~Aby zapisac edycje nacisnij~n~~g~~h~dyskietke~w~~h~, aby anulowac nacisnij ~r~ESC~w~~h~.");

            // Aktualizowanie pozycji
         	Streamer_Update(playerid);
	    }
	    else if(IsOwnerArea(playerid, areaid)) // Tworzenie obiektów gdy jest siê w strefie
	    {
	        // Tworzenie obiektu
	        new uid = AddObject(model, OWNER_AREA, DoorInfo[doorid][dOwner], vw, interior, Pos[0], Pos[1] + 2.0, Pos[2], 0.0, 0.0, 0.0);

			// Informacja
			ObjectInfo[uid][oDoor] = areaid;

			// Definiowanie zmiennych
	        PlayerEditObject[playerid] = uid;
	        EditDynamicObject(playerid, ObjectInfo[uid][oObject]);

			// Informacja o komendach dla gracza
			Infobox(playerid, 10, "Rozpoczeles ~g~~h~edycje obiektu~w~~h~.~n~~n~Aby zapisac edycje nacisnij~n~~g~~h~dyskietke~w~~h~, aby anulowac nacisnij ~r~ESC~w~~h~.");

	        // Aktualizowanie pozycji
	        Streamer_Update(playerid);
	    }
	    else if(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_OBJECT) // Tworzenie obiektów gdy jest siê administratorem
	    {
	        // Tworzenie obiektu
	        new uid = AddObject(model, OWNER_ADMIN, 0, vw, interior, Pos[0], Pos[1] + 2.0, Pos[2], 0.0, 0.0, 0.0);

            // Definiowanie zmiennych
	        PlayerEditObject[playerid] = uid;
	        EditDynamicObject(playerid, ObjectInfo[uid][oObject]);
	        
			// Informacja o komendach dla gracza
			Infobox(playerid, 10, "Rozpoczeles ~g~~h~edycje obiektu~w~~h~.~n~~n~Aby zapisac edycje nacisnij~n~~g~~h~dyskietke~w~~h~, aby anulowac nacisnij ~r~ESC~w~~h~.");

	        // Aktualizowanie pozycji
	        Streamer_Update(playerid);
	    }
	    else // Informacja o b³êdzie w tworzeniu obiektów
	    {
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do tworzenia obiektów w tym miejscu.", "Zamknij", "");
			return 1;
	    }
	}
	return 1;
}

CMD:msel(playerid, params[])
{
 	new modelid;
 	if(sscanf(params, "d", modelid))
 	{
     	SelectObject(playerid);
  	}
 	else
 	{
     	new searchid = GetObjectModelClosest(playerid, modelid);

     	if(modelid == 0 || modelid < 0)
  		{
         	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony format modelu jest nieprawid³owy.", "Zamknij", "");
         	return 1;
     	}
  		if(!searchid)
  		{
         	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W pobli¿u nie znaleziono obiektu o podanym ID.", "Zamknij", "");
         	return 1;
     	}

  		// Definiowanie zmiennych
     	PlayerEditObject[playerid] = searchid;
     	EditDynamicObject(playerid, searchid);
 	}
 	return 1;
}

CMD:msave(playerid, params[])
{
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	
	// Pobieranie ID obiektu
	new objectid = PlayerEditObject[playerid];
	
	// Pobieranie pozycji obiektu
	GetDynamicObjectPos(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]);
	GetDynamicObjectRot(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
	
	// Zapisywanie obiektu
	SaveObject(objectid);
	
	// Informowanie gracza
	Infobox(playerid, 5, "Obiekt zostal ~g~~h~pomyslnie ~w~~h~zapisany.");
	
	// Zerowanie zmiennych
	CancelEdit(playerid);
 	PlayerEditObject[playerid] = 0;
	    
	return 1;
}

CMD:mdel(playerid, params[])
{
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}

	// Pobieranie ID obiektu
	new objectid = PlayerEditObject[playerid];

	// Usuwanie obiektu
	DeleteObject(objectid);

	// Informowanie gracza
	Infobox(playerid, 5, "Obiekt zostal ~g~~h~pomyslnie ~w~~h~usuniety.");

	// Zerowanie zmiennych
	CancelEdit(playerid);
 	PlayerEditObject[playerid] = 0;

	return 1;
}

CMD:mx(playerid, params[])
{
	new Float: pos_x;
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	if(sscanf(params, "f", pos_x))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /mx [pozycja X]", "Zamknij", "");
        return 1;
	}
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		new Float:Pos[3];
		
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], Pos[1], Pos[2]);
		SetDynamicObjectRot(ObjectInfo[objectid][oObject], pos_x, Pos[1], Pos[2]);
		
		// Informowanie gracza
		Infobox(playerid, 5, "Pozycja obiektu ~g~~h~X ~w~~h~zostala zmieniona.");
	}
	return 1;
}
CMD:mrx(playerid, params[]) return cmd_mx(playerid, params);

CMD:my(playerid, params[])
{
	new Float: pos_y;
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	if(sscanf(params, "f", pos_y))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /my [pozycja Y]", "Zamknij", "");
        return 1;
	}
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		new Float:Pos[3];

		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], Pos[1], Pos[2]);
		SetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], pos_y, Pos[2]);

		// Informowanie gracza
		Infobox(playerid, 5, "Pozycja obiektu ~g~~h~Y ~w~~h~zostala zmieniona.");
	}
	return 1;
}
CMD:mry(playerid, params[]) return cmd_my(playerid, params);

CMD:mz(playerid, params[])
{
	new Float: pos_z;
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	if(sscanf(params, "f", pos_z))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /mz [pozycja Z]", "Zamknij", "");
        return 1;
	}
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		new Float:Pos[3];

		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], Pos[1], Pos[2]);
		SetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], Pos[1], pos_z);

		// Informowanie gracza
		Infobox(playerid, 5, "Pozycja obiektu ~g~~h~Z ~w~~h~zostala zmieniona.");
	}
	return 1;
}
CMD:mrz(playerid, params[]) return cmd_mz(playerid, params);

CMD:mgate(playerid, params[])
{
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}

	// Zakoñczenie edycji bramy
	PlayerEditGate[playerid] = true;

	// Zerowanie edycji
	CancelEdit(playerid);

	// Informowanie gracza
	Infobox(playerid, 5, "Brama zostala ~g~~h~pomyslnie ~w~~h~zapisana.");
	return 1;
}

CMD:mmat(playerid, params[])
{
    if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	
	new index, type, comm1[256];
	if(sscanf(params, "ddS()[256]", index, type, comm1))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /mmat [index (0 - 5)] [0 - tekstura / 1 - napis] [parametry]", "Zamknij", "");
        return 1;
	}
	else
	{
	    if(index < 0 || index > 5)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony index jest nieprawid³owy.\nMaksymalny index to 5.", "Zamknij", "");
	        return 1;
	    }
	    if(type != 0 && type != 1)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Parametr typu jest nieprawid³owy.\nMo¿liwy to 0 lub 1.", "Zamknij", "");
	        return 1;
	    }
	    
	    if(type) // Napis
	    {
	        new object = PlayerEditObject[playerid];
	        new matsize, fontsize, bold, fontcolor, backcolor, align, fontface[32], text[64];
	        
			if(sscanf(comm1, "dddxxds[32]s[64]", matsize, fontsize, bold, fontcolor, backcolor, align, fontface, text))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /mmat [index (0 - 5)] 1 [matsize] [fontsize] [bold] [fontcolor] [backcolor] [align] [font] [text]", "Zamknij", "");
        		return 1;
			}
			else
			{
			    new color_font = ShiftRGBAToABGR(fontcolor);
			    new color_back = ShiftRGBAToABGR(backcolor);
			    
			    EscapeMMAT(text);
			    
                SetDynamicObjectMaterialText(ObjectInfo[object][oObject], index, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
                
                ObjectInfo[object][oMMAT] = 1;
			    
			    SaveObject(ObjectInfo[object][oUID]);

				mysql_query_format("DELETE FROM `fc_mmat_text` WHERE `index` = '%d' AND `object_id` = '%d'", index, ObjectInfo[object][oUID]);
                mysql_query_format("INSERT INTO `fc_mmat_text` VALUES ('%d', '%d', '%d', '%d', '%d', '%x', '%x', '%d', '%s', '%s')", ObjectInfo[object][oUID], index, matsize, fontsize, bold, color_font, color_back, align, fontface, text);
			}
	    }
	    else // Tekstura
	    {
	        new object = PlayerEditObject[playerid];
	        new modelid, txdname[32], texturename[32], materialcolor;
	        
			if(sscanf(comm1, "xds[32]s[32]", materialcolor, modelid, txdname, texturename))
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /mmat [index (0 - 5)] 0 [materialcolor] [modelid] [txdname] [texturename]", "Zamknij", "");
        		return 1;
			}
			else
			{
			    SetDynamicObjectMaterial(ObjectInfo[object][oObject], index, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));
			    
			    ObjectInfo[object][oMMAT] = 0;
			    
			    SaveObject(ObjectInfo[object][oUID]);
                
                mysql_query_format("DELETE FROM `fc_mmat_texture` WHERE `index` = '%d' AND `object_id` = '%d'", index, ObjectInfo[object][oUID]);
			    mysql_query_format("INSERT INTO `fc_mmat_texture` VALUES ('%d', '%d', '%x', '%d', '%s', '%s')", ObjectInfo[object][oUID], index, ShiftRGBAToABGR(materialcolor), modelid, txdname, texturename);
			}
	    }
	}
	
	return 1;
}

CMD:brama(playerid, params[])
{
	new gateid;
     
	if(IsPlayerInAnyVehicle(playerid))
	{
	   	gateid = GetObjectGateIndex(playerid, 15.0);
	}
	else
	{
		gateid = GetObjectGateIndex(playerid, 2.0);
	}
	
	if(!gateid)
	{
	    return 1;
	}
	
	if(ObjectInfo[gateid][oGateOpen])
 	{
		MoveDynamicObject(ObjectInfo[gateid][oObject], ObjectInfo[gateid][oX], ObjectInfo[gateid][oY], ObjectInfo[gateid][oZ], 5.0, ObjectInfo[gateid][oRX], ObjectInfo[gateid][oRY], ObjectInfo[gateid][oRZ]);
		ObjectInfo[gateid][oGateOpen] = false;
	}
	else
 	{
	    MoveDynamicObject(ObjectInfo[gateid][oObject], ObjectInfo[gateid][oGateX], ObjectInfo[gateid][oGateY], ObjectInfo[gateid][oGateZ], 5.0, ObjectInfo[gateid][oGateRX], ObjectInfo[gateid][oGateRY], ObjectInfo[gateid][oGateRZ]);
        ObjectInfo[gateid][oGateOpen] = true;
	}
	return 1;
}
CMD:br(playerid, params[]) return cmd_brama(playerid, params);

CMD:admins(playerid, params[])
{
    new list_admin[2048], list = 0;

    format(list_admin, sizeof(list_admin), "{C0C0C0}ID\tGrupa\t\t\tPoziom\t\tNazwa");
    
    ForeachEx(i, MAX_PLAYERS)
    {
        if(CharacterCache[i][pAdmin] != 0 && CharacterCache[i][pAdminDuty])
        {
            switch(CharacterCache[i][pAdmin])
            {
                case 1: format(list_admin, sizeof(list_admin), "%s\n%d\t{538668}Support{FFFFFF}\t\t%d\t\t%s", list_admin, i, CharacterCache[i][pAdmin], AssCode(i));
                case 2: format(list_admin, sizeof(list_admin), "%s\n%d\t{538668}Support{FFFFFF}\t\t%d\t\t%s", list_admin, i, CharacterCache[i][pAdmin], AssCode(i));
                case 3: format(list_admin, sizeof(list_admin), "%s\n%d\t{538668}Support{FFFFFF}\t\t%d\t\t%s", list_admin, i, CharacterCache[i][pAdmin], AssCode(i));
                case 4: format(list_admin, sizeof(list_admin), "%s\n%d\t{538668}Support{FFFFFF}\t\t%d\t\t%s", list_admin, i, CharacterCache[i][pAdmin], AssCode(i));
                case 5: format(list_admin, sizeof(list_admin), "%s\n%d\t{538668}Support{FFFFFF}\t\t%d\t\t%s", list_admin, i, CharacterCache[i][pAdmin], AssCode(i));
                case 6: format(list_admin, sizeof(list_admin), "%s\n%d\t{d80000}Administrator{FFFFFF}\t\t%d\t\t%s", list_admin, i, CharacterCache[i][pAdmin] - 5, CharacterCache[i][pGlobalNick]);
                case 7: format(list_admin, sizeof(list_admin), "%s\n%d\t{d80000}Administrator{FFFFFF}\t\t%d\t\t%s", list_admin, i, CharacterCache[i][pAdmin] - 5, CharacterCache[i][pGlobalNick]);
                case 8: format(list_admin, sizeof(list_admin), "%s\n%d\t{d80000}Administrator{FFFFFF}\t\t%d\t\t%s", list_admin, i, CharacterCache[i][pAdmin] - 5, CharacterCache[i][pGlobalNick]);
                case 9: format(list_admin, sizeof(list_admin), "%s\n%d\t{d80000}Administrator{FFFFFF}\t\t\t%d\t\t%s", list_admin, i, CharacterCache[i][pAdmin] - 5, CharacterCache[i][pGlobalNick]);
            }

            list++;
        }
    }

    if(list) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, "Lista administratorów", list_admin, "Zamknij", "");
    else Infobox(playerid, 5, "Brak ~g~~h~administratorow~w~~h~ online.");
    return 1;
}
CMD:a(playerid, params[]) return cmd_admins(playerid, params);