/*
	CMD:namierz
	CMD:ulecz
	CMD:reanimuj
	CMD:reklama
	CMD:zbadaj
	CMD:zbierz
	CMD:d
	CMD:lot
	CMD:magazyn
	CMD:worek
	CMD:knebel
	CMD:megafon
	CMD:przeszukaj
	CMD:zabierz
	CMD:aresztuj
	CMD:wypusc
	CMD:kajdanki
	CMD:napad
*/

CMD:namierz(playerid, params[])
{
    if(!IsPermGroupTypeOnType(playerid, GROUP_BORDER))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
	    return 1;
	}
	
	if(CharacterCache[playerid][pDetect])
	{
	    GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~Namierzanie: ~r~wylaczone", 3000, 4);
	    
	    TogglePlayerControllable(playerid, 1);
	    SetCameraBehindPlayer(playerid);
	    
	    CharacterCache[playerid][pDetect] = false;
    	CharacterCache[playerid][pDetectNumber] = 0;
		CharacterCache[playerid][pDetectPlayerID] = INVALID_PLAYER_ID;
	}
	else
	{
		new number;
		if(sscanf(params, "d", number))
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /namierz [numer telefonu]", "Zamknij", "");
	        return 1;
		}
		else
		{
	        new playerid2 = GetPhoneID(number);
	        if(playerid2 < 0 || playerid2 == INVALID_PLAYER_ID || playerid2 == -1)
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Abonament telefonu znajduje siê poza zasiêgiem sieci.", "Zamknij", "");
		        return 1;
		    }
		    if(playerid == playerid2)
		    {
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie jesteœ w stanie znaleŸæ swojego numeru telefonu.", "Zamknij", "");
		        return 1;
		    }
		    if(GetPlayerVirtualWorld(playerid2) != 0)
		    {
		    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Abonament telefonu znajduje siê poza zasiêgiem sieci.", "Zamknij", "");
		        return 1;
		    }

		    CharacterCache[playerid][pDetect] = true;
		    CharacterCache[playerid][pDetectNumber] = number;
		    CharacterCache[playerid][pDetectPlayerID] = playerid2;
		    CharacterCache[playerid][pDetectProgress] = 110;
		    
		    TogglePlayerControllable(playerid, 0);
		    
		    GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~System lokalizacji~n~~g~inicjalizacja", 3000, 4);
		}
	}
	
	return 1;
}

CMD:ulecz(playerid, params[])
{
	if(!IsPermGroupTypeOnType(playerid, GROUP_MC) && !IsPermGroupTypeOnType(playerid, GROUP_FD))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
	    return 1;
	}
	
	new playerid2, string[128];
	if(sscanf(params, "i", playerid2))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ulecz [ID gracza]", "Zamknij", "");
        return 1;
	}
	else
	{
	    if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
	    {
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany przez Ciebie gracz nie jest zalogowany.", "Zamknij", "");
		    return 1;
	    }
	    if(!PlayerToPlayer(5.0, playerid, playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od gracza.", "Zamknij", "");
	    	return 1;
	    }
	    if(CharacterCache[playerid2][pBW])
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz jest w stanie nieprzytomnoœci.\nZastosuj pierw reanimacjê.", "Zamknij", "");
	    	return 1;
	    }
	    
	    AddPlayerHP(playerid2, 50.0);
	    
	    format(string, sizeof(string), "Zosta³eœ uleczony przez medyka %s.\nTwój stan zdrowia jest dobry, lecz wymaga hospitalizacji.", PlayerName2(playerid));
	    ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	    
	    format(string, sizeof(string), "Pomyœlnie uleczy³eœ gracza %s.", PlayerName2(playerid2));
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	}
	return 1;
}

CMD:reanimuj(playerid, params[])
{
	if(!IsPermGroupTypeOnType(playerid, GROUP_MC) && !IsPermGroupTypeOnType(playerid, GROUP_FD))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
	    return 1;
	}

	new playerid2;
	if(sscanf(params, "i", playerid2))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /reanimuj [ID gracza]", "Zamknij", "");
        return 1;
	}
	else
	{
	    if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
	    {
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany przez Ciebie gracz nie jest zalogowany.", "Zamknij", "");
		    return 1;
	    }
	    if(!PlayerToPlayer(5.0, playerid, playerid2))
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Znajdujesz siê zbyt daleko od gracza.", "Zamknij", "");
	    	return 1;
	    }
	    if(!CharacterCache[playerid2][pBW])
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz nie jest w stanie nieprzytomnoœci.\nNie jesteœ w stanie mu pomóc.", "Zamknij", "");
	    	return 1;
	    }

	    CharacterCache[playerid][pReanimation] = 30;
	    CharacterCache[playerid][pReanimationID] = playerid2;
	    
	    GameTextForPlayer(playerid, "~n~~n~~n~~n~~g~~h~Trwa reanimacja...", 1000, 5);
		GameTextForPlayer(playerid2, "~n~~n~~n~~n~~g~~h~Trwa reanimacja...", 1000, 5);
	}
	return 1;
}

CMD:reklama(playerid, params[])
{
	if(!IsPermGroupTypeOnType(playerid, GROUP_RADIO))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
	    return 1;
	}
	
	new time, text[128], string[256];
	if(sscanf(params, "ds[128]", time, text))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /reklama [czas reklamy (minuty)] [treœæ]", "Zamknij", "");
        return 1;
	}
	else
	{
	    if(time < 0 || time > 5)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony czas nie jest prawid³owy. Maksymalny czas to 5 minut.", "Zamknij", "");
	    	return 1;
	    }
	    if(AdvertiseTime)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aktualnie nadawana jest jedna z reklam.\nOdczekaj a¿ zakoñczy siê jej nadawanie.", "Zamknij", "");
	    	return 1;
	    }
	    if(UsingRadio)
	    {
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W radiu nadawana jest audycja, odczekaj a¿ zakoñczy siê jej nadawanie.", "Zamknij", "");
	    	return 1;
	    }
	    
	    if(IsPlayerInAnyVehicle(playerid))
	    {
	        new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
	        if(VehicleInfo[vehid][vOwnerType] != OWNER_GROUP || VehicleInfo[vehid][vOwner] != IsPermGroupTypeOnType(playerid, GROUP_RADIO))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pojeŸdzie grupy News.", "Zamknij", "");
	    		return 1;
	        }
	    }
		else
		{
	        new doorid = PlayerDoor[playerid];
	        if(!doorid)
			{
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pomieszczeniu grupy News.", "Zamknij", "");
	    		return 1;
	        }
	        if(DoorInfo[doorid][dOwnerType] != OWNER_GROUP || DoorInfo[doorid][dOwner] != IsPermGroupTypeOnType(playerid, GROUP_RADIO))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pomieszczeniu grupy News.", "Zamknij", "");
	    		return 1;
	        }
	        
	        EscapePL(text);
	        EscapeTildes(text);
	        
	        format(string, sizeof(string), "~y~~h~        %s ~>~ ~w~%s", PlayerName2(playerid), text);
	        
	        ForeachEx(i, MAX_PLAYERS)
	        {
	            if(!(CharacterCache[i][pTog] & TOG_FM))
	            {
	                PlayerTextDrawSetString(i, RadioFM[i], string);
	                PlayerTextDrawShow(i, RadioFM[i]);
	            }
	        }
	        
	        AdvertiseTime = time;
			UsingRadio = true;
	    }
	}
	
	return 1;
}

CMD:zbadaj(playerid, params[])
{
    if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
	    return 1;
	}
	
	new comm1[32], comm2[64];
	if(sscanf(params, "s[32]S()[64]", comm1, comm2))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /zbadaj [zw³oki | gracz]", "Zamknij", "");
        return 1;
	}
	else
 	{
	    if(!strcmp(comm1, "zw³oki", true) || !strcmp(comm1, "zwloki", true))
	    {
	        if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI))
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
			    return 1;
			}
	
	        new corner_id;
	        if(sscanf(comm2, "d", corner_id))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /zbadaj zw³oki [ID zw³ok]", "Zamknij", "");
        		return 1;
	        }
	        else
	        {
	            if(!CorpseInfo[corner_id][cUID])
	            {
	            	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W systemie nie znaleziono zw³ok o danym ID.", "Zamknij", "");
	    			return 1;
	            }
				if(!IsPlayerInRangeOfPoint(playerid, 5.0, CorpseInfo[corner_id][cPos][0], CorpseInfo[corner_id][cPos][1], CorpseInfo[corner_id][cPos][2]))
				{
				    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w pobli¿u danych zw³ok.", "Zamknij", "");
	    			return 1;
				}
				
				new string[512], title[32], year, month, day, hours, minutes;
				timestamp_to_date(CorpseInfo[corner_id][cDate], year, month, day, hours, minutes);
				
				format(title, sizeof(title), "Zw³oki - ID: %d", CorpseInfo[corner_id][cUID]);
				
				format(string, sizeof(string), "Identyfikator:\t\t%d", CorpseInfo[corner_id][cUID]);
				format(string, sizeof(string), "%s\nOsoba:\t\t\t%s (UID: %d)", string, GetPlayerSQLName(CorpseInfo[corner_id][cChar]), CorpseInfo[corner_id][cChar]);

				switch(CorpseInfo[corner_id][cReason])
				{
					case 1..46:
					{
					    new gunname[32];
					    GetWeaponName(CorpseInfo[corner_id][cReason], gunname, sizeof(gunname));
					    
					    format(string, sizeof(string), "%s\nSposób zabicia:\t\tBroñ (%s [ID: %d])", string, gunname, CorpseInfo[corner_id][cWeaponUID]);
					}
					case 49:
					{
					    new vehid = CorpseInfo[corner_id][cWeaponUID];
					    format(string, sizeof(string), "%s\nSposób zabicia:\t\tPotr¹cenie (%s [ID: %d])", string, GetVehicleModelName(VehicleInfo[vehid][vModel]), VehicleInfo[vehid][vUID]);
					}
					case 50:
					{
					    format(string, sizeof(string), "%s\nSposób zabicia:\t\tRozciêcie œmig³owcem");
					}
					case 51:
					{
					    format(string, sizeof(string), "%s\nSposób zabicia:\t\tEksplozja", string);
					}
					case 54:
					{
					    format(string, sizeof(string), "%s\nSposób zabicia:\t\tŒmieræ naturalna", string);
					}
				}
				
				if(CorpseInfo[corner_id][cStatus] >= 75)
				{
					format(string, sizeof(string), "%s\nStan zw³ok:\t\t{8CD147}Dobry", string);
				}
				else if(CorpseInfo[corner_id][cStatus] < 75)
				{
				    format(string, sizeof(string), "%s\nStan zw³ok:\t\t{FFC675}Rozk³adaj¹cy", string);
				}
				else if(CorpseInfo[corner_id][cStatus] <= 30)
				{
				    format(string, sizeof(string), "%s\nStan zw³ok:\t\t{FF9C9D}Niszczej¹cy", string);
				}
				
				format(string, sizeof(string), "%s\nData zabójstwa:\t\t%d.%d.%d, %d:%d", string, day, month, year, hours + 1, minutes);
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, title, string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "gracz", true))
	    {
	        if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER))
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
			    return 1;
			}
	
			new playerid2, string[128];
	        if(sscanf(comm2, "i", playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /zbadaj gracz [ID gracza]", "Zamknij", "");
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
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie znajduje siê w pobli¿u Ciebie.", "Zamknij", "");
	    			return 1;
				}
				
				format(string, sizeof(string), "Badany:\t\t\t%s", PlayerName2(playerid2));
				
				if(CharacterCache[playerid][pDrugs]) format(string, sizeof(string), "%s\n\nNaæpany:\t\t\tTak (%s)", ItemTypeInfo[GetTypeDrug(CharacterCache[playerid][pDrugs])][iTypeName], string);
				else format(string, sizeof(string), "%s\n\nNaæpany:\t\t\tNie", string);
				
				format(string, sizeof(string), "%s\nNietrzeŸwoœæ:\t\tNie", string);

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	        }
	    }
	}
	
	return 1;
}

CMD:zbierz(playerid, params[])
{
	new plantid = GetClosestPlant(playerid);
	if(!plantid || !PlantInfo[plantid][plantUID])
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie znajdujesz siê w pobli¿u ¿adnej z roœlin.", "Zamknij", "");
     	return 1;
	}
	if(IsPlayerInAnyVehicle(playerid))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Znajdujesz siê w pojeŸdzie dlatego nie mo¿esz zebraæ roœliny.", "Zamknij", "");
     	return 1;
	}
	if(PlantInfo[plantid][plantProgress] < 80)
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Roœlina nie jest jeszcze gotowa do zebrania.", "Zamknij", "");
  		return 1;
	}
	if(IsPermGroupTypeOnType(playerid, GROUP_PD) || IsPermGroupTypeOnType(playerid, GROUP_FBI) || IsPermGroupTypeOnType(playerid, GROUP_BORDER) || IsPermGroupTypeOnType(playerid, GROUP_SS))
	{
	    DeletePlant(plantid);
	    
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Narkotyk z plantacji zosta³ zabrany do magazynu grupy.\nA nastêpnie zniszczony przez techników.\n\nRoœlina zosta³a usuniêta, nie pojawi siê w Twoim ekwipunku.", "Zamknij", "");
	}
	else
	{
	    new rand = (random(4) + 1);
	    new type = GetTypeDrug(PlantInfo[plantid][plantType]);
	    
		ForeachEx(i, rand)
		{
		    CreatePlayerItem(playerid, NamePlant(PlantInfo[plantid][plantType]), type, 1, 1, 1);
		}
		
		DeletePlant(plantid);
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pomyœlnie uda³o Ci siê zebraæ narkotyk z roœliny.\n\nPojawi³ siê on w Twoim ekwipunku.", "Zamknij", "");
	}
	return 1;
}

CMD:d(playerid, params[])
{
    if(!IsPermGroupFlag(playerid, FLAG_DEPARTMENT))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "¯adna z Twoich grup nie posiada flagi grupowej, która pozwala na rozmowy na czacie.", "Zamknij", "");
        return 1;
    }
    if(!PlayerHaveItemType(playerid, TYPE_RADIO))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz w swoim ekwipunku radia.", "Zamknij", "");
        return 1;
    }
    if(CharacterCache[playerid][pBW] || CharacterCache[playerid][pAJ])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W stanie nieprzytomnoœci lub Admin Jaila nie jesteœ w stanie pisaæ na czacie.", "Zamknij", "");
        return 1;
    }
    if(CharacterCache[playerid][pKnebel])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ teraz z tej komendy.", "Zamknij", "");
        return 1;
    }

    new text[128];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /d [tekst]", "Zamknij", "");
        return 1;
    }
    else
    {
        new groupid = IsPermGroupFlag(playerid, FLAG_DEPARTMENT);

        ForeachEx(i, MAX_PLAYERS)
        {
            if(IsPermGroupFlag(i, FLAG_DEPARTMENT) && PlayerHaveItemType(i, TYPE_RADIO))
            {
                SendClientMessageFormat(i, 0xff8282FF, "** (%s) %s: %s", GroupData[groupid][Tag], PlayerName2(playerid), text);
            }
        }

		new str[256];
        format(str, sizeof(str), "%s (radio): %s", PlayerName2(playerid), text);
        SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, str, 25);
    }

    return 1;
}

CMD:lot(playerid, params[])
{
	if(!IsAircraft(GetVehicleModel(GetPlayerVehicleID(playerid))) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ z czêstotliwoœci lotniczej poza samolotem.", "Zamknij", "");
        return 1;
	}
 	if(CharacterCache[playerid][pBW] || CharacterCache[playerid][pAJ])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W stanie nieprzytomnoœci lub Admin Jaila nie jesteœ w stanie pisaæ na czacie.", "Zamknij", "");
        return 1;
    }
    if(CharacterCache[playerid][pKnebel])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz skorzystaæ teraz z tej komendy.", "Zamknij", "");
        return 1;
    }
	
	new text[128];
    if(sscanf(params, "s[128]", text))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /lot [tekst]", "Zamknij", "");
        return 1;
	}
	else
	{
		ForeachEx(i, MAX_PLAYERS)
		{
			if(IsAircraft(GetVehicleModel(GetPlayerVehicleID(i))) || IsPermGroupTypeOnType(i, GROUP_BORDER))
			{
   				SendClientMessageFormat(i, 0x1F51ADFF, "** (LOT) %s: %s", PlayerName2(playerid), text);
			}
		}

		new str[256];
	 	format(str, sizeof(str), "%s (radio): %s", PlayerName2(playerid), text);
	  	SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, str, 25);
  	}
  	return 1;
}

CMD:magazyn(playerid, params[])
{
	if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_THINGS) && !IsPlayerPermGroupType(playerid, GROUP_SYNDYCATE, PANEL_PANEL))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
	    return 1;
	}
	if(!IsPlayerInRangeOfPoint(playerid, 10.0, -927.3229, 2026.0327, 61.0654))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w magazynie broni.\nSkontaktuj siê z administratorem, a przeka¿e Ci on owe informacje.", "Zamknij", "");
	    return 1;
	}
	
    ShowPlayerMagazine(playerid);
    return 1;
}

CMD:worek(playerid, params[])
{
	new giveplayer_id, me[64];
	if(!IsPlayerKindGroup(playerid, GROUP_MAFIA) && !IsPlayerKindGroup(playerid, GROUP_GANG) && !IsPlayerKindGroup(playerid, GROUP_DRIVERS))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
	    return 1;
	}
	if(sscanf(params, "i", giveplayer_id))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /worek [id osoby]", "Zamknij", "");
        return 1;
	}
	else
 	{
	    if(CharacterCache[giveplayer_id][pWorek])
	    {
	        PlayerTextDrawHide(giveplayer_id, BlackScreen[giveplayer_id]);
	        
	        CharacterCache[giveplayer_id][pWorek] = false;
	        
	        format(me, sizeof(me), "zdejmuje z g³owy worek %s.", PlayerName2(giveplayer_id));
	        cmd_me(playerid, me);
	    }
	    else
	    {
	        PlayerTextDrawShow(giveplayer_id, BlackScreen[giveplayer_id]);
	        
	        CharacterCache[giveplayer_id][pWorek] = true;
	        
	        format(me, sizeof(me), "zak³ada worek na g³owê %s.", PlayerName2(giveplayer_id));
	        cmd_me(playerid, me);
	    }
	}
	
	return 1;
}

CMD:knebel(playerid, params[])
{
	new giveplayer_id;
	if(!IsPlayerKindGroup(playerid, GROUP_MAFIA) && !IsPlayerKindGroup(playerid, GROUP_GANG) && !IsPlayerKindGroup(playerid, GROUP_DRIVERS))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia tej komendy.", "Zamknij", "");
	    return 1;
	}
	if(sscanf(params, "i", giveplayer_id))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /knebel [id osoby]", "Zamknij", "");
        return 1;
	}
	else
 	{
	    if(CharacterCache[giveplayer_id][pKnebel])
	    {
	        CharacterCache[giveplayer_id][pKnebel] = false;

	       	GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~~h~Knebel zostal zdjety!", 3500, 3);
	    }
	    else
	    {
	        CharacterCache[giveplayer_id][pKnebel] = true;

	        GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~~h~Knebel zalozony!", 3500, 3);
	    }
	}

	return 1;
}

CMD:megafon(playerid, params[])
{
    if(!IsPermGroupFlag(playerid, FLAG_MEGAPHONE))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ywania megafonu.", "Zamknij", "");
        return 1;
    }
	/*if(!PlayerHaveItemType(playerid, TYPE_MEGAPHONE))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz przy sobie przedmiotu megafonu.", "Zamknij", "");
        return 1;
	}*/
    new text[128], string[256];
    if(sscanf(params, "s[128]", text))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /m(egafon) [tekst]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(IsPermGroupTypeOnType(playerid, GROUP_PD))
        {
            cmd_m(playerid, "Los Santos Police Department! ZjedŸ na pobocze i zgaœ silnik!");
            return 1;
        }
        if(IsPermGroupTypeOnType(playerid, GROUP_BORDER))
        {
			cmd_m(playerid, "U.S. Border Patrol! ZjedŸ na pobocze i zgaœ silnik!");
			return 1;
        }

		new groupid = IsPermGroupFlag(playerid, FLAG_MEGAPHONE);
		
        format(string, sizeof(string), "* (%s) %s (megafon) o:< %s", GroupData[groupid][Tag], PlayerName2(playerid), text);
        ProxDetector(25.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    }
    return 1;
}
CMD:m(playerid, params[]) return cmd_megafon(playerid, params);

CMD:przeszukaj(playerid, params[])
{
	if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER) && !IsPermGroupTypeOnType(playerid, GROUP_SS))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia komendy.", "Zamknij", "");
	    return 1;
	}
	
	new comm1[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /przeszukaj [gracz, pojazd]", "Zamknij", "");
        return 1;
	}
	else
	{
	    if(!strcmp(comm1, "gracz", true))
	    {
	        new playerid2, str[64];
	        if(sscanf(comm2, "i", playerid2))
	        {
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /przeszukaj gracz [ID gracza]", "Zamknij", "");
        		return 1;
	        }
	        else
	        {
	            if(!Logged[playerid2])
	            {
	            	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            		return 1;
	            }
	            if(playerid == playerid2)
	            {
	            	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie mo¿esz przeszukaæ samego siebie.", "Zamknij", "");
            		return 1;
	            }
	            if(!PlayerToPlayer(5.0, playerid, playerid2))
	            {
	            	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie znajduje siê obok Ciebie.", "Zamknij", "");
            		return 1;
	            }

	            ListPlayerItemsForPlayer(playerid, playerid2);
				
	            format(str, sizeof(str), "przeszukuje %s.", PlayerName2(playerid2));
	            cmd_me(playerid, str);
	            
	            format(str, sizeof(str), "~n~~n~~n~~n~~w~~h~Zostales przeszukany przez gracza ~g~~h~%s~w~~h~.", PlayerName2(playerid));
	            GameTextForPlayer(playerid2, str, 3000, 5);
	        }
	    }
	    else if(!strcmp(comm1, "pojazd", true) )
	    {
     		new vehicleid = GetClosestVehicle(playerid);
		    new vehid = GetVehicleUID(vehicleid);
		    new item_uid, item_name[32];
		    new data[64], query[256], list_items[512];
		    
		    if(vehicleid == INVALID_VEHICLE_ID || !vehid)
		    {
		    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "W pobli¿u nie znaleziono pojazdu do przeszukania.", "Zamknij", "");
            	return 1;
		    }
		    
		    format(query, sizeof(query), "SELECT `uid`, `name` FROM `fc_items` WHERE `ownertype` = '%d' AND `owner` = '%d'", OWNER_VEHICLE, VehicleInfo[vehid][vUID]);
		    
      		mysql_check();
 			mysql_query(query);
		    mysql_store_result();
		    
		    while(mysql_fetch_row_format(data, "|"))
		    {
		        sscanf(data, "p<|>ds[32]", item_uid, item_name);
		        format(list_items, sizeof(list_items), "%s\n%d\t%s", list_items, item_uid, item_name);
		    }
		    
		    mysql_free_result();

		    if(strlen(list_items) != 0)
		    {
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Lista przedmiotów w pojeŸdzie", list_items, "Zamknij", "");
			}
		    else
		    {
		        Infobox(playerid, 5, "Nie znaleziono ~g~~h~zadnych~w~~h~ przedmiotow w pojezdzie.");
		        return 1;
		    }
	    }
	}
	
	return 1;
}

CMD:zabierz(playerid, params[])
{
	if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER) && !IsPermGroupTypeOnType(playerid, GROUP_SS))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia komendy.", "Zamknij", "");
	    return 1;
	}
	
	new comm1[32], comm2[32], string[256];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /zabierz [prawko | niekaralnoœæ | przedmiot]", "Zamknij", "");
        return 1;
	}
	else
	{
		if(!strcmp(comm1, "prawko", true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
		    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /zabierz prawko [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
		    {
				if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER) && !IsPermGroupTypeOnType(playerid, GROUP_SS))
				{
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia komendy.", "Zamknij", "");
				    return 1;
				}
		        if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany w grze.", "Zamknij", "");
		            return 1;
		        }
		        if(!PlayerToPlayer(5.0, playerid, playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie znajduje siê obok Ciebie.", "Zamknij", "");
		            return 1;
		        }
		        if(!(CharacterCache[playerid2][pDocument] & DOC_DRIVER))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie posiada prawa jazdy.", "Zamknij", "");
		            return 1;
		        }
		        
		        CharacterCache[playerid2][pDocument] -= DOC_DRIVER;
		        
		        format(string, sizeof(string), "Pomyœlnie zabra³eœ graczowi %s (ID: %d) prawo jazdy.\nPamiêtaj o zabieraniu prawa jazdy zgodnie z zasadami.", PlayerName2(playerid2), playerid2);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

		        format(string, sizeof(string), "%s (ID: %d) zabra³ Tobie prawo jazdy.\nJe¿eli uwa¿asz, ¿e zrobi³ to bezprawnie - powiadom administracjê.\n\nZrobienie screena z tej wiadomoœci lub godziny pomo¿e administracji.", PlayerName2(playerid), playerid);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		    }
		}
		else if(!strcmp(comm1, "niekaralnoœæ", true) || !strcmp(comm1, "niekaralnosc", true))
		{
		    new playerid2;
		    if(sscanf(comm2, "i", playerid2))
		    {
		    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /zabierz niekaralnoœæ [ID gracza]", "Zamknij", "");
        		return 1;
		    }
		    else
			{
				if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER) && !IsPermGroupTypeOnType(playerid, GROUP_SS))
				{
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia komendy.", "Zamknij", "");
				    return 1;
				}
		        if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany w grze.", "Zamknij", "");
		            return 1;
		        }
		        if(!PlayerToPlayer(5.0, playerid, playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie znajduje siê obok Ciebie.", "Zamknij", "");
		            return 1;
		        }
		        if(!(CharacterCache[playerid2][pDocument] & DOC_POLICE))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie posiada dokumentu niekaralnoœci.", "Zamknij", "");
		            return 1;
		        }
		        
		        CharacterCache[playerid2][pDocument] -= DOC_POLICE;

		        format(string, sizeof(string), "Pomyœlnie zabra³eœ graczowi %s (ID: %d) dokument niekaralnoœci.\nPamiêtaj o zabieraniu dokumentu zgodnie z zasadami.", PlayerName2(playerid2), playerid2);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

		        format(string, sizeof(string), "%s (ID: %d) zabra³ Tobie dokument niekaralnoœci.\nJe¿eli uwa¿asz, ¿e zrobi³ to bezprawnie - powiadom administracjê.\n\nZrobienie screena z tej wiadomoœci lub godziny pomo¿e administracji.", PlayerName2(playerid), playerid);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}
		}
		else if(!strcmp(comm1, "przedmiot", true))
		{
		    new playerid2;
			if(sscanf(comm2, "i", playerid2))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /zabierz przedmiot [ID gracza]", "Zamknij", "");
        		return 1;
			}
			else
			{
				if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_MAFIA) && !IsPermGroupTypeOnType(playerid, GROUP_GANG) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER) && !IsPermGroupTypeOnType(playerid, GROUP_SS))
				{
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia komendy.", "Zamknij", "");
				    return 1;
				}
		        if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany w grze.", "Zamknij", "");
		            return 1;
		        }
		        if(!PlayerToPlayer(5.0, playerid, playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie znajduje siê obok Ciebie.", "Zamknij", "");
		            return 1;
		        }
		        if(!CharacterCache[playerid2][pBW])
		        {
		        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz nie posiada stanu nieprzytomnoœci, abyœ móg³ zabraæ mu przedmiot.", "Zamknij", "");
		            return 1;
		        }
		        
		        SetPVarInt(playerid, "ItemPlayerID2", playerid2);
		        
          		new data[128], list_items[1024], query[256];
			    new item_uid, item_name[32], item_value1, item_value2;

			    format(query, sizeof(query), "SELECT `uid`, `name`, `value1`, `value2` FROM `fc_items` WHERE `owner` = '%d' AND `ownertype` = '%d' AND `used` = 0", CharacterCache[playerid2][pUID], OWNER_PLAYER);
			    mysql_check(); mysql_query(query);

			    mysql_store_result();
			    
			    while(mysql_fetch_row_format(data, "|"))
			    {
			        sscanf(data, "p<|>ds[32]dd", item_uid, item_name, item_value1, item_value2);

					format(list_items, sizeof(list_items), "%s\n{000000}%d\t%d\t%d\t{878A87}%s", list_items, item_uid, item_value1, item_value2, item_name);
			    }
			    mysql_free_result();

			    if(strlen(list_items)) ShowPlayerDialog(playerid, D_OUT_ITEM, DIALOG_STYLE_LIST, " Lista przedmiotów gracza", list_items, "Zabierz", "Zamknij");
			    else Infobox(playerid, 5, "Gracz nie posiada ~g~~h~¿adnych~w~~h~ przedmiotów.");
			}
		}
	}
	
	return 1;
}

CMD:aresztuj(playerid, params[])
{
	if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER) && !IsPermGroupTypeOnType(playerid, GROUP_SS))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia komendy.", "Zamknij", "");
		return 1;
	}
	
	new playerid2, time, doorid = GetClosestDoor(playerid), string[128];
	if(sscanf(params, "id", playerid2, time))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /aresztuj [ID gracza] [czas (minuty max. 1200)]", "Zamknij", "");
   		return 1;
	}
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
    	{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany w grze.", "Zamknij", "");
			return 1;
		}
		if(!PlayerToPlayer(5.0, playerid, playerid2))
 		{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie znajduje siê obok Ciebie.", "Zamknij", "");
			return 1;
 		}
 		if(time > 1200 || time < 1)
    	{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Czas aresztu jest niepoprawny.", "Zamknij", "");
			return 1;
		}
		if(CharacterCache[playerid2][pJailTime] > 0)
    	{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz jest ju¿ aresztowany.", "Zamknij", "");
			return 1;
		}
		if(DoorInfo[doorid][dOwnerType] != OWNER_JAIL)
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz sie przy miejscu aresztu.", "Zamknij", "");
			return 1;
		}
		
		CharacterCache[playerid2][pJailTime] = time;
		CharacterCache[playerid2][pJailID] = doorid;
		
		OnPlayerEnterDoor(playerid2, doorid);
		
		format(string, sizeof(string), "Aresztowa³eœ gracza %s (ID: %d) w celi na %d minut.", PlayerName2(playerid2), playerid2, time);
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		
		format(string, sizeof(string), "Gracz %s (ID: %d) aresztowa³ Ciê w celi na %d minut.", PlayerName2(playerid), playerid, time);
		ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	}
	
	return 1;
}
CMD:areszt(playerid, params[]) return cmd_aresztuj(playerid, params);

CMD:wypusc(playerid, params[])
{
	if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER) && !IsPermGroupTypeOnType(playerid, GROUP_SS))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia komendy.", "Zamknij", "");
		return 1;
	}

	new playerid2, string[128];
	if(sscanf(params, "id", playerid2))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /wypuœæ [ID gracza]", "Zamknij", "");
   		return 1;
	}
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
    	{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany w grze.", "Zamknij", "");
			return 1;
		}
		if(!PlayerToPlayer(5.0, playerid, playerid2))
 		{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie znajduje siê obok Ciebie.", "Zamknij", "");
			return 1;
 		}
		if(CharacterCache[playerid2][pJailTime] < 1)
    	{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest w stanie aresztowania.", "Zamknij", "");
			return 1;
		}

		CharacterCache[playerid2][pJailTime] = 0;
		CharacterCache[playerid2][pJailID] = 0;

		TeleportPlayerToSpawn(playerid2);

		format(string, sizeof(string), "Wypuœci³eœ gracza %s (ID: %d) z celi.", PlayerName2(playerid2), playerid2);
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

		format(string, sizeof(string), "Gracz %s (ID: %d) wypuœci³ Ciê z celi.", PlayerName2(playerid), playerid);
		ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	}
	
	return 1;
}

CMD:kajdanki(playerid, params[])
{
	if(!IsPermGroupTypeOnType(playerid, GROUP_PD) && !IsPermGroupTypeOnType(playerid, GROUP_FBI) && !IsPermGroupTypeOnType(playerid, GROUP_BORDER) && !IsPermGroupTypeOnType(playerid, GROUP_SS))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do u¿ycia komendy.", "Zamknij", "");
		return 1;
	}
				
	new playerid2, string[128];
	if(sscanf(params, "i", playerid2))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /kajdanki [ID gracza]", "Zamknij", "");
   		return 1;
	}
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
    	{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany w grze.", "Zamknij", "");
			return 1;
		}
		if(!PlayerToPlayer(5.0, playerid, playerid2))
 		{
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie znajduje siê obok Ciebie.", "Zamknij", "");
			return 1;
 		}
 		
		if(CharacterCache[playerid2][pCuffed] != INVALID_PLAYER_ID)
		{
		    CharacterCache[playerid2][pCuffed] = INVALID_PLAYER_ID;
		    CharacterCache[playerid2][pStatus] -= STATUS_CUFFED;

            PlayerPlaySound(playerid, 1190, 0.0, 0.0, 0.0);
            
		    SetPlayerSpecialAction(playerid2, 0);
		    RemovePlayerAttachedObject(playerid2, 5);

		    format(string, sizeof(string), "odkuwa kajdankami %s.", PlayerName2(playerid2));
			cmd_me(playerid, string);
		}
		else
		{
  			CharacterCache[playerid2][pCuffed] = playerid;
  			CharacterCache[playerid2][pStatus] += STATUS_CUFFED;
  			
            PlayerPlaySound(playerid, 1190, 0.0, 0.0, 0.0);
            
		    SetPlayerSpecialAction(playerid2, 24);
		    SetPlayerAttachedObject(playerid2, 5, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);

		    format(string, sizeof(string), "skuwa kajdankami %s.", PlayerName2(playerid2));
			cmd_me(playerid, string);
		}
	}
	
	return 1;
}
CMD:skuj(playerid, params[]) return cmd_kajdanki(playerid, params);
CMD:cuff(playerid, params[]) return cmd_kajdanki(playerid, params);

CMD:napad(playerid, params[])
{
    new doorid = PlayerDoor[playerid];
    new ownerid = DoorInfo[doorid][dOwner];
    new groupid = IsPermGroupTypeOnType(playerid, GROUP_GANG);

    if(!groupid)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawieñ do napadów na sklepy.", "Zamknij", "");
        return 1;
    }
    if(!doorid)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w ¿adnym ze sklepów.", "Zamknij", "");
        return 1;
    }
    if(GroupData[groupid][LimitVehicles])
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W tym dniu Twoja grupa dokona³a ju¿ napadu na sklep.\nSpróbuj ponownie za parê dni.", "Zamknij", "");
        return 1;
    }
    if(DoorInfo[doorid][dOwnerType] != OWNER_GROUP)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê w ¿adnym ze sklepów.", "Zamknij", "");
        return 1;
    }
    if(GroupData[ownerid][Kind] != GROUP_SHOP)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Napady s¹ mo¿liwe tylko w sklepie 24/7.", "Zamknij", "");
        return 1;
    }
    if(CountMembersCrimeInDoor(DutyGroup[playerid], doorid) < 2)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W sklepie nie znajduje siê odpowiednia iloœæ przestêpców z Twojej grupy (min. 3).\nKa¿dy z nich musi posiadaæ broñ paln¹ (lub kij) oraz posiadaæ na sobie maskê.", "Zamknij", "");
        return 1;
    }
    if(CountMembersGroup(GROUP_PD) < 3)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Na s³u¿bie policyjnej nie znajduje siê odpowiednia iloœæ funkcjonariuszy (min. 3).", "Zamknij", "");
        return 1;
    }

    CharacterCache[playerid][pRobberyID] = groupid;
    CharacterCache[playerid][pRobbery] = 180;

    ForeachEx(i, MAX_PLAYERS)
    {
        if(IsPlayerInGroup(i, groupid))
        {
            GameTextForPlayer(i, "~n~~n~Napad na sklep zostal rozpoczety!", 5000, 4);
        }
    }

    return 1;
}