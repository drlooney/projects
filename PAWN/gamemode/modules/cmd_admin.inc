/*
	CMD:agrupa
	CMD:aroslina
	CMD:aczujnik
	CMD:aburger
	CMD:abus
	CMD:aprodukt
	CMD:apojazd
	CMD:astrefa
	CMD:adrzwi
	CMD:aprzedmiot
	CMD:set
	CMD:duty
	CMD:bw
	CMD:glob
	CMD:restart
	CMD:slap
	CMD:warn
	CMD:kick
	CMD:aj
	CMD:unaj
	CMD:block
	CMD:ban
	CMD:gamescore
	CMD:to
	CMD:tm
	CMD:ptp
	CMD:rc
*/

CMD:agrupa(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_GROUPS)) return 1;
    new comm1[32], comm2[128], string[256];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /agrupa [lista | stwórz | usuñ | edytuj]", "Zamknij", "");
        return 1;
    }
    else if(!strcmp(comm1, "edytuj", true))
    {
		if(EditGroup[playerid])
		{
		    new groupid = EditGroup[playerid];
		    new title[64];
		    new list_options[512];
		    
		    format(title, sizeof(title), "Edycja grupy %s (UID: %d)", GroupData[groupid][Desc], GroupData[groupid][UID]);

			format(list_options, sizeof(list_options), "1. Zmiana nazwy grupy");
			format(list_options, sizeof(list_options), "%s\n2. Zmiana tagu grupy", list_options);
			format(list_options, sizeof(list_options), "%s\n3. Zmiana flag grupowych", list_options);
			format(list_options, sizeof(list_options), "%s\n4. Zmiana limitu pojazdów", list_options);
			format(list_options, sizeof(list_options), "%s\n5. Uzupe³nij podatek grupy", list_options);
			format(list_options, sizeof(list_options), "%s\n6. Zmiana typu grupy", list_options);
			format(list_options, sizeof(list_options), "%s\n7. Nadaj lidera grupy", list_options);
			format(list_options, sizeof(list_options), "%s\n{D42A2A}8. Usuñ pracowników z grupy", list_options);
			format(list_options, sizeof(list_options), "%s\n{D42A2A}9. Usuñ grupê", list_options);
		    
		    ShowPlayerDialog(playerid, D_EDIT_GROUP, DIALOG_STYLE_LIST, title, list_options, "Edytuj", "Zamknij");
		}
		else
		{
		    ShowPlayerDialog(playerid, D_CHECK_GROUP, DIALOG_STYLE_INPUT, "Edycja grupy", "WprowadŸ ID grupy, któr¹ chcesz edytowaæ.", "WprowadŸ", "Zamknij");
		}
    }
    else if(!strcmp(comm1, "stwórz", true) || !strcmp(comm1, "stworz", true))
    {
        ShowPlayerDialog(playerid, D_CREATE_GROUP_NAME, DIALOG_STYLE_INPUT, " Tworzenie grupy", "WprowadŸ nazwê do tworzonej nowej grupy:", "Dalej", "Zamknij");
    }
    else if(!strcmp(comm1, "usuñ", true) || !strcmp(comm1, "usun", true))
    {
        new uid;
        if(sscanf(comm2, "d", uid))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /agrupa usuñ [ID grupy]", "Zamknij", "");
            return 1;
        }
        if(!GroupData[uid][UID])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID grupy jest niepoprawne.", "Zamknij", "");
            return 1;
        }

        SetPVarInt(playerid, "DeleteGroup", uid);

        format(string, sizeof(string), "Czy na pewno chcesz usun¹æ grupê %s (UID: %d) ?", GroupData[uid][Desc], GroupData[uid][UID]);
        ShowPlayerDialog(playerid, D_DELETE_GROUP, DIALOG_STYLE_MSGBOX, " Informacja", string, "Tak", "Nie");
    }
    else if(!strcmp(comm1, "limit", true))
    {
        new uid, limit;
        if(sscanf(comm2, "dd", uid, limit))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /agrupa limit [ID grupy] [iloœæ pojazdów]", "Zamknij", "");
            return 1;
        }
        if(!GroupData[uid][UID])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID grupy jest niepoprawne.", "Zamknij", "");
            return 1;
        }
        if(limit < 1)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona iloœæ pojazdów jest niepoprawna.", "Zamknij", "");
            return 1;
        }

        GroupData[uid][LimitVehicles] = limit;
        SaveGroup(uid);
        
        InfoAdminFormat(playerid, "zmienil limit pojazdow w grupie ~y~~h~~h~%s (UID:%d)~w~~h~ na %d.", GroupData[uid][Desc], GroupData[uid][UID], limit);

        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Iloœæ pojazdów w grupie zosta³a zmieniona.", "Zamknij", "");
    }
    else if(!strcmp(comm1, "cash", true))
    {
        new uid, cash;
        if(sscanf(comm2, "dd", uid, cash))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /agrupa cash [ID grupy] [kwota]", "Zamknij", "");
            return 1;
        }
        if(!GroupData[uid][UID])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID grupy jest niepoprawne.", "Zamknij", "");
            return 1;
        }
        if(cash < 0 || cash == 0)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona kwota jest niepoprawna.", "Zamknij", "");
            return 1;
        }

        GroupData[uid][Cash] = cash;
        SaveGroup(uid);

        InfoAdminFormat(playerid, "zmienil stan gotowki w grupie ~y~~h~~h~%s (UID:%d)~w~~h~ na %d.", GroupData[uid][Desc], GroupData[uid][UID], cash);
        
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Stan konta w grupie zosta³ zmieniony.", "Zamknij", "");
    }
    else if(!strcmp(comm1, "podatek", true))
    {
        new uid, day;
        if(sscanf(comm2, "dd", uid, day))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /agrupa podatek [ID grupy] [czas (dni)]", "Zamknij", "");
            return 1;
        }
        if(!GroupData[uid][UID])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID grupy jest niepoprawne.", "Zamknij", "");
            return 1;
        }
        if(day < 0 || day == 0)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona iloœæ dni jest niepoprawna.", "Zamknij", "");
            return 1;
        }

        GroupData[uid][License] = gettime() + ((day * 60) * 60);
        SaveGroup(uid);

        InfoAdminFormat(playerid, "oplacil podatek w grupie ~y~~h~~h~%s (UID:%d)~w~~h~ na czas %d dni.", GroupData[uid][Desc], GroupData[uid][UID], day);
        
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Podatek w grupie zosta³ zmieniony.", "Zamknij", "");
    }
    else if(!strcmp(comm1, "typ", true))
    {
        new uid, type;
        if(sscanf(comm2, "dd", uid, type))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /agrupa typ [ID grupy] [typ]", "Zamknij", "");
            return 1;
        }
        if(!GroupData[uid][UID])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID grupy jest niepoprawne.", "Zamknij", "");
            return 1;
        }

        GroupData[uid][Kind] = type;
        SaveGroup(uid);
        
        InfoAdminFormat(playerid, "zmienil typ w grupie ~y~~h~~h~%s (UID:%d)~w~~h~ na %d.", GroupData[uid][Desc], GroupData[uid][UID], type);

        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Rodzaj grupy zosta³ pomyœlnie zmieniony.", "Zamknij", "");
    }
    else if(!strcmp(comm1, "nazwa", true))
    {
        new uid, name[32];
        if(sscanf(comm2, "ds[32]", uid, name))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /agrupa nazwa [ID grupy] [nazwa]", "Zamknij", "");
            return 1;
        }
        if(!GroupData[uid][UID])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID grupy jest niepoprawne.", "Zamknij", "");
            return 1;
        }

        format(GroupData[uid][Desc], 32, "%s", name);
        SaveGroup(uid);
        
        InfoAdminFormat(playerid, "zmienil nazwe w grupie ~y~~h~~h~%s (UID:%d)~w~~h~ na %s.", GroupData[uid][Desc], GroupData[uid][UID], name);

        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nazwa grupy zosta³a pomyœlnie zmieniona.", "Zamknij", "");
    }
    else if(!strcmp(comm1, "tag", true))
    {
        new uid, tag[12];
        if(sscanf(comm2, "ds[12]", uid, tag))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /agrupa tag [ID grupy] [tag]", "Zamknij", "");
            return 1;
        }
        if(!GroupData[uid][UID])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID grupy jest niepoprawne.", "Zamknij", "");
            return 1;
        }

        GroupData[uid][Tag] = tag;
        SaveGroup(uid);
        
        InfoAdminFormat(playerid, "zmienil nazwe w grupie ~y~~h~~h~%s (UID:%d)~w~~h~ na %s.", GroupData[uid][Desc], GroupData[uid][UID], tag);

        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Tag grupy zosta³ pomyœlnie zmieniony.", "Zamknij", "");
    }
    else if(!strcmp(comm1, "lider", true))
    {
        new giveplayer_id, uid;
        if(sscanf(comm2, "dd", giveplayer_id, uid))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /agrupa lider [ID gracza] [ID grupy]", "Zamknij", "");
            return 1;
        }
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz o wybranym 'id' nie jest zalogowany.", "Zamknij", "");
            return 1;
        }
        if(!GroupData[uid][UID])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Grupa o wybranym 'id' nie istnieje w bazie danych.", "Zamknij", "");
            return 1;
        }
        if(!HaveFreeSlotGroup(giveplayer_id))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz o wybranym 'id' nie posiada wolnego slotu grupowego.", "Zamknij", "");
            return 1;
        }
        if(IsPlayerInGroup(giveplayer_id, uid))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz o wybranym 'id' nale¿y ju¿ do tej grupy.", "Zamknij", "");
            return 1;
        }

        SetPVarInt(playerid, "CheckLeaderGroupID", uid),
        SetPVarInt(playerid, "CheckLeaderPlayerID", giveplayer_id);

        format(string, sizeof(string), "Czy chcesz aby gracz %s (ID: %d, UID: %d) zosta³ liderem g³ównym?", PlayerName2(giveplayer_id), giveplayer_id, CharacterCache[giveplayer_id][pUID]);
        ShowPlayerDialog(playerid, D_CHECK_LEADER, DIALOG_STYLE_MSGBOX, " Informacja", string, "Tak", "Nie");
    }
    else if(!strcmp(comm1, "flagi", true))
    {
        new uid, list_flags[1024], title[128];
        if(sscanf(comm2, "d", uid))
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ag flagi [uid grupy]", "Zamknij", "");
            return 1;
        }
        else
        {
            if(!GroupData[uid][UID]) return 1;

            format(title, sizeof(title), " %s (UID: %d) [Flagi grupowe]", GroupData[uid][Desc], GroupData[uid][UID]);

            CharacterCache[playerid][pGroupFlag] = GroupData[uid][UID];

            if(!(GroupData[uid][Flags] & FLAG_DEPARTMENT)) format(list_flags, sizeof(list_flags), "%s\nCzat departamentowy:\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nCzat departamentowy:\t\t\t{99FF00}T", list_flags);

            if(!(GroupData[uid][Flags] & FLAG_MEGAPHONE)) format(list_flags, sizeof(list_flags), "%s\nU¿ywanie megafonu:\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nU¿ywanie megafonu:\t\t\t{99FF00}T", list_flags);

            if(!(GroupData[uid][Flags] & FLAG_NICK)) format(list_flags, sizeof(list_flags), "%s\nKolorowa nazwa nicku:\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nKolorowa nazwa nicku:\t\t\t{99FF00}T", list_flags);

            if(!(GroupData[uid][Flags] & FLAG_OUT)) format(list_flags, sizeof(list_flags), "%s\nOpuszczanie grupy:\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nOpuszczanie grupy:\t\t\t{99FF00}T", list_flags);

            if(!(GroupData[uid][Flags] & FLAG_CASH)) format(list_flags, sizeof(list_flags), "%s\nWyp³acanie gotówki z konta:\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nWyp³acanie gotówki z konta:\t\t{99FF00}T", list_flags);

            if(!(GroupData[uid][Flags] & FLAG_DB)) format(list_flags, sizeof(list_flags), "%s\nDrive-By:\t\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nDrive-By:\t\t\t\t{99FF00}T", list_flags);

            if(!(GroupData[uid][Flags] & FLAG_BLOCK)) format(list_flags, sizeof(list_flags), "%s\nUstawianie blokad:\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nUstawianie blokad:\t\t\t{99FF00}T", list_flags);

            if(!(GroupData[uid][Flags] & FLAG_DETENTION)) format(list_flags, sizeof(list_flags), "%s\nPrzetrzymywanie grupowe:\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nPrzetrzymywanie grupowe:\t\t{99FF00}T", list_flags);

            if(!(GroupData[uid][Flags] & FLAG_ITEM)) format(list_flags, sizeof(list_flags), "%s\nZabieranie przedmiotów:\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nZabieranie przedmiotów:\t\t{99FF00}T", list_flags);
            
            if(!(GroupData[uid][Flags] & FLAG_CALL_911)) format(list_flags, sizeof(list_flags), "%s\nTelefon alarmowy:\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nTelefon alarmowy:\t\t\t{99FF00}T", list_flags);
            
            if(!(GroupData[uid][Flags] & FLAG_REPORTS)) format(list_flags, sizeof(list_flags), "%s\nZg³oszenia grupowe:\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nZg³oszenia grupowe:\t\t\t{99FF00}T", list_flags);
            
            if(!(GroupData[uid][Flags] & FLAG_GPS)) format(list_flags, sizeof(list_flags), "%s\nGPS w pojazdach:\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nGPS w pojazdach:\t\t\t{99FF00}T", list_flags);
            
            if(!(GroupData[uid][Flags] & FLAG_ALARM)) format(list_flags, sizeof(list_flags), "%s\nAlarm w furgonetce:\t\t\t{990000}N", list_flags);
            else format(list_flags, sizeof(list_flags), "%s\nAlarm w furgonetce:\t\t\t{99FF00}T", list_flags);

            ShowPlayerDialog(playerid, D_FLAG_GROUP, DIALOG_STYLE_LIST, title, list_flags, "Zmieñ", "Zamknij");
        }
    }
    else if(!strcmp(comm1, "lista", true) || !strcmp(comm1, "list", true))
    {
        new list_group[2048];

        format(list_group, sizeof(list_group), "{C0C0C0}ID\tStan konta\tPunkty\t\tNazwa");
        ForeachEx(i, MAX_GROUPS)
        {
            if(GroupData[i][UID])
            {
                format(list_group, sizeof(list_group), "%s\n%d\t$%d\t\t%d\t\t%s", list_group, GroupData[i][UID], GroupData[i][Cash], GroupData[i][Points], GroupData[i][Desc]);
            }
        }

        ShowPlayerDialog(playerid, D_CHECK_GROUP, DIALOG_STYLE_LIST, " Lista wszystkich grup", list_group, "Edytuj", "Zamknij");
    }
    return 1;
}
CMD:ag(playerid, params[]) return cmd_agrupa(playerid, params);

CMD:aroslina(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_PLANTS)) return 1;
	new comm1[32], comm2[128], string[128];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ar(oœlina) [lista | usuñ | goto]", "Zamknij", "");
        return 1;
    }
    else
	{
    	if(!strcmp(comm1, "lista", true) || !strcmp(comm1, "list", true))
    	{
    	    new list_plants[1024];

    	    ForeachEx(i, MAX_PLANTS)
    	    {
    	        if(PlantInfo[i][plantUID])
    	        {
    	            format(list_plants, sizeof(list_plants), "%s\n%d\t%s", list_plants, PlantInfo[i][plantUID], GetPlayerSQLName(PlantInfo[i][plantChar]));
    	        }
			}

			if(strlen(list_plants) != 0) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Informacja", list_plants, "Zamknij", "");
			else Infobox(playerid, 5, "Nie znaleziono ~g~~h~zadnej ~w~~h~rosliny.");
    	}
    	else if(!strcmp(comm1, "usuñ", true) || !strcmp(comm1, "usun", true))
    	{
    	    new uid;
			if(sscanf(comm2, "d", uid))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ar(oœlina) usuñ [ID roœliny]", "Zamknij", "");
        		return 1;
			}
			else
			{
			    if(!PlantInfo[uid][plantUID])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W bazie danych nie znaleziono roœliny.", "Zamknij", "");
			        return 1;
			    }

			    DeletePlant(uid);

			    format(string, sizeof(string), "Roœlina (UID: %d) zosta³a pomyœlnie usuniêta.", uid);
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}
    	}
    	else if(!strcmp(comm1, "goto", true))
    	{
    	    new uid;
    	    if(sscanf(comm2, "d", uid))
    	    {
    	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ar(oœlina) goto [ID czujnika]", "Zamknij", "");
        		return 1;
    	    }
    	    else
    	    {
    	        if(!PlantInfo[uid][plantUID])
    	        {
    	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrana roœlina nie istnieje w bazie danych.", "Zamknij", "");
    	        	return 1;
    	        }

    	        SetPlayerPos(playerid, PlantInfo[uid][plantX], PlantInfo[uid][plantY], PlantInfo[uid][plantZ]);
    	        SetPlayerVirtualWorld(playerid, PlantInfo[uid][plantVw]);
    	        SetPlayerInterior(playerid, PlantInfo[uid][plantInt]);

    	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zosta³eœ pomyœlnie przeniesiony do czujnika.", "Zamknij", "");
    	    }
    	}
	}
	
	return 1;
}
CMD:ar(playerid, params[]) return cmd_aroslina(playerid, params);

CMD:aczujnik(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_SENSORS)) return 1;
	new comm1[32], comm2[128], string[128];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ac(zujnik) [lista | stwórz | usuñ | goto]", "Zamknij", "");
        return 1;
    }
    else
	{
		if(!strcmp(comm1, "stwórz", true) || !strcmp(comm1, "stworz", true))
    	{
    	    new name[32];
    	    if(sscanf(comm2, "s[32]", name))
    	    {
    	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ac(zujnik) stwórz [nazwa czujnika]", "Zamknij", "");
        		return 1;
    	    }
    	    else
    	    {
    	        new uid = AddSensor(playerid, name);
    	        
    	        format(string, sizeof(string), "Pomyœlnie stworzy³eœ czujnik (UID: %d) o nazwie %s.", uid, name);
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
    	    }
		}
    	else if(!strcmp(comm1, "usuñ", true) || !strcmp(comm1, "usun", true))
    	{
    	    new uid;
			if(sscanf(comm2, "d", uid))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ac(zujnik) usuñ [ID czujnika]", "Zamknij", "");
        		return 1;
			}
			else
			{
			    if(!SensorInfo[uid][sensorID])
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W bazie danych nie znaleziono czujnika.", "Zamknij", "");
			        return 1;
			    }
			    
			    DeleteSensor(uid);
			    
			    format(string, sizeof(string), "Czujnik (UID: %d) zosta³ pomyœlnie usuniêty.", uid);
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}
    	}
    	else if(!strcmp(comm1, "lista", true) || !strcmp(comm1, "list", true))
    	{
    	    new list_sensors[512];
    	    
    	    ForeachEx(i, MAX_SENSORS)
    	    {
    	        if(SensorInfo[i][sensorID])
    	        {
    	            format(list_sensors, sizeof(list_sensors), "%s\n%d\t%s", list_sensors, SensorInfo[i][sensorID], SensorInfo[i][sensorName]);
    	        }
			}
			
			if(strlen(list_sensors) != 0) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Informacja", list_sensors, "Zamknij", "");
			else Infobox(playerid, 5, "Nie znaleziono ~g~~h~zadnego ~w~~h~czujnika.");
    	}
    	else if(!strcmp(comm1, "goto", true))
    	{
    	    new uid;
    	    if(sscanf(comm2, "d", uid))
    	    {
    	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ac(zujnik) goto [ID czujnika]", "Zamknij", "");
        		return 1;
    	    }
    	    else
    	    {
    	        if(!SensorInfo[uid][sensorID])
    	        {
    	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany czujnik nie istnieje w bazie danych.", "Zamknij", "");
    	        	return 1;
    	        }
    	        
    	        SetPlayerPos(playerid, SensorInfo[uid][sensorPos][0], SensorInfo[uid][sensorPos][1], SensorInfo[uid][sensorPos][2]);
    	        SetPlayerVirtualWorld(playerid, 0);
    	        SetPlayerInterior(playerid, 0);
    	        
    	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zosta³eœ pomyœlnie przeniesiony do czujnika.", "Zamknij", "");
    	    }
    	}
	}
	
	return 1;
}
CMD:ac(playerid, params[]) return cmd_aczujnik(playerid, params);

CMD:aburger(playerid, params[])
{
	if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_BURGER)) return 1;
	new comm1[32], comm2[128];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /aburger [stwórz | usuñ]", "Zamknij", "");
        return 1;
    }
    else
    {
	    if(!strcmp(comm1, "stwórz", true) || !strcmp(comm1, "stworz", true))
	    {
	        ShowPlayerDialog(playerid, D_CHOOSE_BURGER, DIALOG_STYLE_MSGBOX, " Informacja", "Czy na pewno chcesz stworzyæ w tym miejscu stoisko z jedzeniem?", "Tak", "Nie");
	    }
	    else if(!strcmp(comm1, "usuñ", true) || !strcmp(comm1, "usun", true))
	    {
			new uid;
	        if(sscanf(comm2, "d", uid))
		 	{
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /aburger usuñ [ID burgera]", "Zamknij", "");
        		return 1;
	        }
	        else
	        {
	            if(!BurgerInfo[uid][burgerID])
			    {
			    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrane ID miejsca nie jest prawid³owe.", "Zamknij", "");
	            	return 1;
			    }

			    DeleteBurger(uid);

			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Miejsce z jedzeniem zosta³o pomyœlnie usuniête.", "Zamknij", "");
	        }
	    }
    }
    return 1;
}

CMD:abus(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_BUS)) return 1;
	new comm1[32], comm2[128], string[256];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ab(us) [lista | stwórz | usuñ]", "Zamknij", "");
        return 1;
    }
    else if(!strcmp(comm1, "stwórz", true) || !strcmp(comm1, "stworz", true))
    {
        new name[32];
        if(sscanf(comm2, "s[32]", name))
        {
        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /abus stwórz [nazwa przystanku]", "Zamknij", "");
            return 1;
        }
        else
        {
	        if(PlayerEditObject[playerid])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W trakcie edycji obiektu nie mo¿esz tworzyæ przystanku.", "Zamknij", "");
	            return 1;
	        }

	        new uid = AddBusStop(playerid, name);

			EditBusStop[playerid] = uid;
			EditDynamicObject(playerid, BusStop[uid][bObject]);

			format(string, sizeof(string), "Pomyœlnie stworzy³eœ przystanek.\n\nNazwa przystanku:\t%s\nIdentyfikator przystanku:\t%d", name, uid);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Inforamcje", string, "Zamknij", "");
        }
    }
    else if(!strcmp(comm1, "usuñ", true) || !strcmp(comm1, "usun", true))
    {
        new uid;
        if(sscanf(comm2, "d", uid))
        {
        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /abus usuñ [ID przystanku]", "Zamknij", "");
            return 1;
        }
		else
		{
		    if(!BusStop[uid][bUID])
		    {
		    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrane ID przystanku nie jest prawid³owe.", "Zamknij", "");
            	return 1;
		    }
		    
		    DeleteBusStop(uid);
		    
		    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Przystanek zosta³ pomyœlnie usuniêty.", "Zamknij", "");
		}
    }
    else if(!strcmp(comm1, "lista", true))
    {
        new list_bus[1024];
        
		ForeachEx(i, MAX_BUSSTOP)
		{
		    if(BusStop[i][bUID])
		    {
		        format(list_bus, sizeof(list_bus), "%s\n%d - %s", list_bus, BusStop[i][bUID], BusStop[i][bName]);
		    }
		}
		
		if(strlen(list_bus) != 0) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Lista przystanków tramwajowych", list_bus, "Zamknij", "");
		else ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie znaleziono ¿adnych przystanków w systemie.", "Zamknij", "");
    }
    
    return 1;
}
CMD:ab(playerid, params[]) return cmd_abus(playerid, params);

CMD:aprodukt(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_THINGS)) return 1;
	new comm1[32], comm2[64];
	if(sscanf(params, "s[32]S()[64]", comm1, comm2))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /aprodukt [stwórz]", "Zamknij", "");
        return 1;
	}
	else
	{
	    if(!strcmp(comm1, "stwórz", true) || !strcmp(comm1, "stworz", true))
	    {
			new list_type[1024], data[64], uid, name[32];
			mysql_query_format("SELECT * FROM `fc_orders_type`");

			mysql_store_result();

			while(mysql_fetch_row_format(data, "|"))
			{
			    sscanf(data, "p<|>ds[32]", uid, name);

			    format(list_type, sizeof(list_type), "%s\n%d\t%s", list_type, uid, name);
			}

			mysql_free_result();
			
	        ShowPlayerDialog(playerid, D_PRODUCT_TYPE, DIALOG_STYLE_LIST, " Informacja", list_type, "Wybierz", "Zamknij");
	    }
	}
	return 1;
}

CMD:apojazd(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_VEHICLES)) return 1;
    new comm1[32], comm2[128], string[256];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd [lista | stwórz | usuñ | przepisz | model | spawn | unspawn | gethere | goto | kolor | paliwo | hp | respawn | zaparkuj | id | tablica]", "Zamknij", "");
        return 1;
    }
    else
    {
	    if(!strcmp(comm1, "stwórz", true) || !strcmp(comm1, "stworz", true))
	    {
	        new modelid, color1, color2;
	        if(sscanf(comm2, "ddd", modelid, color1, color2))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd stwórz [model pojazdu] [kolor 1] [kolor 2]", "Zamknij", "");
	            return 1;
	        }
	        if(modelid < 400 || modelid > 611)
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Model pojazdu nie mo¿e byæ mniejszy ni¿ 400 oraz wiêkszy ni¿ 611.", "Zamknij", "");
	            return 1;
	        }
	        if(color1 < 0 || color1 > 255 || color2 < 0 || color2 > 255)
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "ID koloru nie mo¿e byæ mniejsze ni¿ 0 a tak¿e wiêksze ni¿ 255.", "Zamknij", "");
	            return 1;
	        }

	        new Float:x, Float:y, Float:z, gameid;
	        GetPlayerPos(playerid, x, y, z);

	        gameid = CreateCar(modelid, x, y - 2.0, z, 0.0, color1, color2, GetPlayerVirtualWorld(playerid));

	        SendClientMessageFormat(playerid, SZARY, "(INFO) Pojazd %s zosta³ stworzony pomyœlnie (UID: %d).", GetVehicleModelName(modelid), VehicleInfo[gameid][vUID]);
	    }
	    else if(!strcmp(comm1, "lista", true) || !strcmp(comm1, "list", true))
	    {
	        new list_vehicles[2048],
	            uid,
	            model,
	            data[256];

	        mysql_check();
	        mysql_query("SELECT `uid`, `model` FROM `fc_vehicles` ORDER BY `uid` ASC");

	        mysql_store_result();

	        format(list_vehicles, sizeof(list_vehicles), "{C0C0C0}UID\t\tNazwa pojazdu");
	        while(mysql_fetch_row_format(data, "|"))
	        {
	            sscanf(data, "p<|>dd", uid, model);

	            format(list_vehicles, sizeof(list_vehicles), "%s\n%d\t\t%s", list_vehicles, uid, GetVehicleModelName(model));
	        }
	        mysql_free_result();

	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Lista wszystkich pojazdów:", list_vehicles, "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "usuñ", true) || !strcmp(comm1, "usun", true))
	    {
	        new vehid;
	        if(sscanf(comm2, "d", vehid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd usuñ [ID pojazdu]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }

	        DeleteVehicle(vehid);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Powodzenie", "Pojazd zosta³ pomyœlnie usuniêty z bazy danych.", "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "przepisz", true))
	    {
	        new vehid, owner_type[24], varchar2[24];
	        if(sscanf(comm2, "ds[24]S()[24]", vehid, owner_type, varchar2))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd przypisz [ID pojazdu] [Typ (gracz, grupa, podgrupa)]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vUID] || !VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }
	        if(!strcmp(owner_type, "gracz", true))
	        {
	            new giveplayer_id;
	            if(sscanf(varchar2, "i", giveplayer_id))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd przypisz [ID pojazdu] gracz [ID gracza]", "Zamknij", "");
	                return 1;
	            }
	            if(!Logged[giveplayer_id])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
	                return 1;
	            }

				if(VehicleInfo[vehid][vOwnerType] == OWNER_PLAYER)
				{
				    new getplayerid = GetPlayerID(VehicleInfo[vehid][vOwner]);
				    if(getplayerid != INVALID_PLAYER_ID && Logged[getplayerid])
				    {
				    	CharacterCache[getplayerid][pCarSpawned] --;
					}
				}

	            VehicleInfo[vehid][vOwnerType] = OWNER_PLAYER;
	            VehicleInfo[vehid][vOwner] = CharacterCache[giveplayer_id][pUID];

	            SaveVehicle(vehid, SAVE_VEH_THINGS);

				if(IsPlayerPremium(giveplayer_id))
				{
				    if(CharacterCache[giveplayer_id][pCarSpawned] >= 5)
					{
						UnspawnVehicle(VehicleInfo[vehid][vUID]);
					}
					else
					{
					    CharacterCache[giveplayer_id][pCarSpawned] ++;
					}
				}
				else
				{
					if(CharacterCache[giveplayer_id][pCarSpawned] >= 3)
					{
						UnspawnVehicle(VehicleInfo[vehid][vUID]);
					}
					else
					{
					    CharacterCache[giveplayer_id][pCarSpawned] ++;
					}
				}

	            format(string, sizeof(string), "Pojazd %s (sampID: %d, UID: %d) zosta³ przypisany pomyœlnie.\n\nTyp w³aœciciela: gracz\nW³aœciciel: %s (ID: %d, UID: %d)", GetVehicleModelName(VehicleInfo[vehid][vModel]), vehid, VehicleInfo[vehid][vUID], PlayerName2(giveplayer_id), giveplayer_id, CharacterCache[giveplayer_id][pUID]);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	        }
	        if(!strcmp(owner_type, "grupa", true))
	        {
	            new group_id;
	            if(sscanf(varchar2, "d", group_id))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd przypisz [ID pojazdu] grupa [ID grupy]", "Zamknij", "");
	                return 1;
	            }
	            if(!GroupData[group_id][UID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID grupy.", "Zamknij", "");
	                return 1;
	            }

				if(VehicleInfo[vehid][vOwnerType] == OWNER_PLAYER)
				{
				    new getplayerid = GetPlayerID(VehicleInfo[vehid][vOwner]);
				    if(getplayerid != INVALID_PLAYER_ID && Logged[getplayerid])
				    {
				    	CharacterCache[getplayerid][pCarSpawned] --;
					}
				}

	            VehicleInfo[vehid][vOwnerType] = OWNER_GROUP;
	            VehicleInfo[vehid][vOwner] = GroupData[group_id][UID];

	            SaveVehicle(vehid, SAVE_VEH_THINGS);

	            format(string, sizeof(string), "Pojazd %s (sampID: %d, UID: %d) zosta³ przypisany pomyœlnie.", GetVehicleModelName(VehicleInfo[vehid][vModel]), vehid, VehicleInfo[vehid][vUID]);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	        }
	        if(!strcmp(owner_type, "podgrupa", true))
	        {
	            new group_id;
	            if(sscanf(varchar2, "d", group_id))
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd przypisz [ID pojazdu] podgrupa [ID podgrupy]", "Zamknij", "");
	                return 1;
	            }
	            if(!SubData[group_id][sUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID podgrupy.", "Zamknij", "");
	                return 1;
	            }

				if(VehicleInfo[vehid][vOwnerType] == OWNER_PLAYER)
				{
				    new getplayerid = GetPlayerID(VehicleInfo[vehid][vOwner]);
				    if(getplayerid != INVALID_PLAYER_ID && Logged[getplayerid])
				    {
				    	CharacterCache[getplayerid][pCarSpawned] --;
					}
				}

	            VehicleInfo[vehid][vOwnerType] = OWNER_SUBGROUP;
	            VehicleInfo[vehid][vOwner] = SubData[group_id][sUID];

	            SaveVehicle(vehid, SAVE_VEH_THINGS);

	            format(string, sizeof(string), "Pojazd %s (sampID: %d, UID: %d) zosta³ przypisany pomyœlnie.", GetVehicleModelName(VehicleInfo[vehid][vModel]), vehid, VehicleInfo[vehid][vUID]);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "model", true))
	    {
	        new vehid, modelid;
	        if(sscanf(comm2, "dd", vehid, modelid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd model [ID pojazdu] [model]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }
	        if(modelid < 400 || modelid > 611)
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Model pojazdu nie mo¿e byæ mniejszy ni¿ 400 oraz wiêkszy ni¿ 611.", "Zamknij", "");
	            return 1;
	        }
	        new Float:x, Float:y, Float:z, Float:a;
	        GetVehiclePos(vehid, x, y, z);
	        GetVehicleZAngle(vehid, a);

	        VehicleInfo[vehid][vModel] = modelid;
	        VehicleInfo[vehid][vFuel] = GetVehicleMaxFuel(modelid);

	        SaveVehicle(vehid, SAVE_VEH_THINGS);

	        UnspawnVehicle(vehid);
	        LoadVehicle(vehid);

	        format(string, sizeof(string), "Model pojazdu zosta³ zmieniony. Nowy model: %d", modelid);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "spawn", true))
	    {
	        new vehid;
	        if(sscanf(comm2, "d", vehid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd spawn [ID pojazdu]", "Zamknij", "");
	            return 1;
	        }
	        if(VehicleInfo[vehid][vGameID])
	        {
	            format(string, sizeof(string), "Ten pojazd jest ju¿ zespawnowany (sampID: %d, UID: %d).", VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vUID]);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", string, "Zamknij", "");
	            return 1;
	        }

	        LoadVehicle(vehid);

	        format(string, sizeof(string), "Pojazd %s (UID: %d) zosta³ zespawnowany pomyœlnie.", GetVehicleModelName(VehicleInfo[vehid][vModel]), VehicleInfo[vehid][vUID]);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "unspawn", true))
	    {
	        new vehid;
	        if(sscanf(comm2, "d", vehid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd unspawn [ID pojazdu]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }

			if(VehicleInfo[vehid][vOwnerType] == OWNER_PLAYER)
			{
			    new giveplayer_id = GetPlayerID(VehicleInfo[vehid][vOwner]);
			    if(giveplayer_id == INVALID_PLAYER_ID)
			    {
			        return 1;
			    }
			    if(!Logged[giveplayer_id])
			    {
			        return 1;
			    }

				CharacterCache[giveplayer_id][pCarSpawned] --;
			}
			
			format(string, sizeof(string), "Pojazd %s (UID: %d) zosta³ odspawnowany pomyœlnie.", GetVehicleModelName(VehicleInfo[vehid][vModel]), VehicleInfo[vehid][vUID]);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

	        UnspawnVehicle(vehid);
	    }
	    else if(!strcmp(comm1, "id", true))
	    {
	        new vehid = GetClosestVehicle(playerid);
	        if(!vehid)
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie znaleziono ¿adnego pojazdu w pobli¿u.", "Zamknij", "");
	            return 1;
	        }

	        format(string, sizeof(string), "Najbli¿szy pojazd to %s (sampID: %d, UID: %d).", GetVehicleModelName(VehicleInfo[vehid][vModel]), vehid, GetVehicleUID(vehid));
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	    }
		else if(!strcmp(comm1, "tablica", true))
	    {
			new vehid, plate[12];
			if(sscanf(comm2, "ds[12]", vehid, plate))
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd tablica [ID pojazdu] [nazwa tablicy]", "Zamknij", "");
	            return 1;
			}
			else
			{
			    if(!VehicleInfo[vehid][vGameID])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
		            return 1;
		        }
		        
		        format(VehicleInfo[vehid][vRegister], 12, "%s", plate);
		        
   				SetVehicleNumberPlate(VehicleInfo[vehid][vGameID], plate);
				SetVehicleToRespawn(VehicleInfo[vehid][vGameID]);
				
				SaveVehicle(vehid, SAVE_VEH_THINGS);
				
				format(string, sizeof(string), "Tablica w pojeŸdzie %s (UID: %d) zosta³a zmieniona na %s.", GetVehicleModelName(VehicleInfo[vehid][vModel]), vehid, plate);
	        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}
		}
		else if(!strcmp(comm1, "hp", true))
	    {
	        new vehid, Float:health;
	        if(sscanf(comm2, "df", vehid, health))
	        {
             	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd hp [ID pojazdu] [HP]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }
	        if(health < 350 || health > 1000)
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "HP pojazdu nie mo¿e byæ mniejsze ni¿ 350 oraz wiêksze od 1000.", "Zamknij", "");
	            return 1;
	        }

	        VehicleInfo[vehid][vHP] = health;
	        SetVehicleHealth(VehicleInfo[vehid][vGameID], health);

	        if(health == 1000)
	            RepairVehicle(VehicleInfo[vehid][vGameID]);

	        SaveVehicle(vehid, SAVE_VEH_COUNT);

	        format(string, sizeof(string), "Stan techniczny pojazdu zosta³ zmieniony.\nHP pojazdu wynosi teraz: %.0f HP.", VehicleInfo[vehid][vHP]);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "respawn", true))
	    {
	        ForeachEx(vehid, MAX_VEHICLES)
	        {
	            if(!IsAnyPlayerInVehicle(vehid))
	            {
	                SetVehicleToRespawn(vehid);
	                UpdateVehicleDamageStatus(vehid, VehicleInfo[vehid][vVisual][0], VehicleInfo[vehid][vVisual][1], VehicleInfo[vehid][vVisual][2], VehicleInfo[vehid][vVisual][3]);
	            }
	        }

	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Wszystkie nieu¿ywane pojazdy zosta³y przywrócone na miejsce spawnu.", "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "zaparkuj", true))
	    {
	        new vehid;
	        if(sscanf(comm2, "d", vehid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd zaparkuj [ID pojazdu]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }

	        GetVehiclePos(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vPosX], VehicleInfo[vehid][vPosY], VehicleInfo[vehid][vPosZ]);
	        GetVehicleZAngle(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vPosA]);

	        VehicleInfo[vehid][vInteriorID] = GetPlayerInterior(playerid);
	        VehicleInfo[vehid][vWorldID] = GetPlayerVirtualWorld(playerid);

	        SaveVehicle(vehid, SAVE_VEH_POS);

	        UnspawnVehicle(vehid);
	        LoadVehicle(vehid);

	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pojazd zosta³ zaparkowany w miejscu, na którym w³aœnie stoi.", "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "kolor", true))
	    {
	        new vehid, color1, color2;
	        if(sscanf(comm2, "ddd", vehid, color1, color2))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd kolor [ID pojazdu] [kolor 1] [kolor 2]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }
	        if(color1 < 0 || color1 > 255 || color2 < 0 || color2 > 255)
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "ID koloru nie mo¿e byæ mniejsze ni¿ 0 a tak¿e wiêksze ni¿ 255.", "Zamknij", "");
	            return 1;
	        }

	        VehicleInfo[vehid][vColor1] = color1;
	        VehicleInfo[vehid][vColor2] = color2;

	        ChangeVehicleColor(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vColor1], VehicleInfo[vehid][vColor2]);

	        SaveVehicle(vehid, SAVE_VEH_ACCESS);

	        format(string, sizeof(string), "Kolor pojazdu zosta³ zmieniony. Nowy kolor: %d / %d", color1, color2);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "paliwo", true))
	    {
	        new vehid, Float:fuel;
	        if(sscanf(comm2, "df", vehid, fuel))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd paliwo [ID pojazdu] [litry]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }
	        if(fuel > GetVehicleMaxFuel(VehicleInfo[vehid][vModel]))
	        {
	            format(string, sizeof(string), "Nie mo¿esz ustaliæ wiêcej paliwa ni¿ zmieœci siê w baku.\nPojemnoœæ baku wynosi: %d litry/ów.", GetVehicleMaxFuel(VehicleInfo[vehid][vModel]));
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", string, "Zamknij", "");
	            return 1;
	        }

	        VehicleInfo[vehid][vFuel] = fuel;
	        SaveVehicle(vehid, SAVE_VEH_COUNT);

	        format(string, sizeof(string), "Ustalono %.0f litry/ów paliwa w pojeŸdzie %s.", fuel, GetVehicleModelName(VehicleInfo[vehid][vModel]));
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "gethere", true))
	    {
	        new vehid;
	        if(sscanf(comm2, "d", vehid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd gethere [ID pojazdu]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }
	        new Float:PosX, Float:PosY, Float:PosZ,
	            interior_id, virtual_world;

	        GetPlayerPos(playerid, PosX, PosY, PosZ);

	        interior_id = GetPlayerInterior(playerid);
	        virtual_world = GetPlayerVirtualWorld(playerid);

	        SetVehiclePos(VehicleInfo[vehid][vGameID], PosX - 2.0, PosY, PosZ);

	        LinkVehicleToInterior(VehicleInfo[vehid][vGameID], interior_id);
	        SetVehicleVirtualWorld(VehicleInfo[vehid][vGameID], virtual_world);
	    }
	    else if(!strcmp(comm1, "goto", true))
	    {
	        new vehid;
	        if(sscanf(comm2, "d", vehid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /apojazd goto [ID pojazdu]", "Zamknij", "");
	            return 1;
	        }
	        if(!VehicleInfo[vehid][vGameID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID pojazdu.", "Zamknij", "");
	            return 1;
	        }
	        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Aby móc przeteleportowaæ siê do pojazdu, nie mo¿esz siedzieæ w innym.", "Zamknij", "");
	            return 1;
	        }
	        new virtual_world = GetVehicleVirtualWorld(VehicleInfo[vehid][vGameID]);

	        PutPlayerInVehicle(playerid, VehicleInfo[vehid][vGameID], 0);
	        SetPlayerVirtualWorld(playerid, virtual_world);

	        SetPlayerInterior(playerid, VehicleInfo[vehid][vInteriorID]);

	        format(string, sizeof(string), "Zosta³eœ przeteleportowany do pojazdu %s (sampID: %d, UID: %d).", GetVehicleModelName(VehicleInfo[vehid][vModel]), vehid, VehicleInfo[vehid][vUID]);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	    }
	}
    return 1;
}
CMD:av(playerid, params[]) return cmd_apojazd(playerid, params);

CMD:astrefa(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_AREA)) return 1;
    new comm1[32], comm2[128];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /as(trefa) [przepisz | obiekty | goto]", "Zamknij", "");
        return 1;
    }
    else
    {
	    if(!strcmp(comm1, "przepisz", true))
	    {
	        new comm3[32], comm4[12];
	        if(sscanf(comm2, "s[32]S()[12]", comm3, comm4))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /as(trefa) przepisz [nikt, grupa]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!strcmp(comm3, "nikt", true))
	            {
	                new uid = GetPlayerArea(playerid);
	                
	                AreaInfo[uid][aOwnerType] = OWNER_NONE;
	            	AreaInfo[uid][aOwner] = 0;
	                
	                SaveArea(uid);
	                
	                GangZoneDestroy(AreaInfo[uid][aGangID]);
	                
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Strefa zosta³a pomyœlnie odpisana od graczy.", "Zamknij", "");
	            }
	            else if(!strcmp(comm3, "grupa", true))
	            {
	                new owner;
	                if(sscanf(comm4, "d", owner))
	                {
	                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /as(trefa) przepisz grupa [ID grupy]", "Zamknij", "");
	            		return 1;
	                }
	                else
	                {
						new uid = GetPlayerArea(playerid);
                        if(AreaInfo[uid][aOwnerType] == OWNER_GROUP) GangZoneDestroy(AreaInfo[uid][aGangID]);
                        
			            AreaInfo[uid][aOwnerType] = OWNER_GROUP;
			            AreaInfo[uid][aOwner] = owner;

			            SaveArea(uid);
			            
			            AreaInfo[uid][aGangID] = GangZoneCreate(AreaInfo[uid][aPos_x][1], AreaInfo[uid][aPos_y][1], AreaInfo[uid][aPos_x][0], AreaInfo[uid][aPos_y][0]);

			            new groupid = AreaInfo[uid][aOwner];
						new color = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0x66;

			            GangZoneShowForAll(AreaInfo[uid][aGangID], color);

			            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Strefa zosta³a pomyœlnie zapisana.", "Zamknij", "");
		            }
	            }
	        }
	    }
	    else if(!strcmp(comm1, "goto", true))
	    {
		    new uid;
	        if(sscanf(comm2, "d", uid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /as(trefa) goto [ID strefy]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!AreaInfo[uid][aUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne ID strefy.\nNie znajduje siê ona w bazie danych.", "Zamknij", "");
	                return 1;
	            }

	            SetPlayerPosFindZ(playerid, AreaInfo[uid][aPos_x][0], AreaInfo[uid][aPos_y][0], 0);

	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zosta³eœ teleportowany do strefy.", "Zamknij", "");
	        }
	    }
	}
    return 1;
}
CMD:as(playerid, params[]) return cmd_astrefa(playerid, params);

CMD:adrzwi(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_DOORS)) return 1;
    new comm1[32], comm2[128], info_box[128];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) [stwórz | usuñ | nazwa | w³aœciciel | wejœcie | wyjœcie | goto | pickup | gara¿ | uid]", "Zamknij", "");
        return 1;
    }
    else
    {
	    if(!strcmp(comm1, "uid", true))
	    {
	        new find = GetClosestDoor(playerid);

	        SendClientMessageFormat(playerid, SZARY, "Znalezione w pobli¿u drzwi » [UID: %d]", find);
	    }
	    else if(!strcmp(comm1, "stwórz", true) || !strcmp(comm1, "stworz", true))
	    {
	        new owner, ownertype, comment[31];
	        if(sscanf(comm2, "dds[31]", ownertype, owner, comment))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) stwórz [rodzaj w³aœciciela] [w³aœciciel] [nazwa drzwi]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(strlen(comment) > 31 || strlen(comment) == 0 || strlen(comment) < 0)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona nazwa drzwi jest nieprawid³owa.\nMog³a doprowadziæ do zbugowania serwera!", "Zamknij", "");
	                return 1;
	            }

	            new uid = AddDoors(playerid, ownertype, owner, comment);

	            SendClientMessageFormat(playerid, SZARY, "(INFO) Pomyœlnie stworzy³eœ drzwi %s (UID: %d).", DoorInfo[uid][dName], DoorInfo[uid][dUID]);
	        }
	    }
	    else if(!strcmp(comm1, "lista", true) || !strcmp(comm1, "list", true))
	    {
	        new string[2096];

	        format(string, sizeof(string), "%s\n{C0C0C0}UID\tNazwa drzwi", string);
	        ForeachEx(uid, MAX_DOORS)
	        {
	            if(DoorInfo[uid][dUID])
	            {
	                format(string, sizeof(string), "%s\n{FFFFFF}%d\t%s", string, DoorInfo[uid][dUID], DoorInfo[uid][dName]);
	            }
	        }

	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Informacja", string, "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "gara¿", true) || !strcmp(comm1, "garaz", true) || !strcmp(comm1, "garage", true))
	    {
	        new doorid, garage;
	        if(sscanf(comm2, "ddd", doorid, garage))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) gara¿ [uid drzwi] [1 - tak / 0 - nie]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!DoorInfo[doorid][dUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID drzwi jest nieprawid³owe.", "Zamknij", "");
	                return 1;
	            }

	            DoorInfo[doorid][dGarage] = garage;
	            SaveDoors(doorid);

	            format(info_box, sizeof(info_box), "Wjazd do drzwi %s (uid: %d) zosta³ zmieniony na %d.", DoorInfo[doorid][dName], DoorInfo[doorid][dUID], garage);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", info_box, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "usuñ", true) || !strcmp(comm1, "usun", true))
	    {
	        new doorid;
	        if(sscanf(comm2, "d", doorid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) usuñ [uid drzwi]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!DoorInfo[doorid][dUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID drzwi jest nieprawid³owe.", "Zamknij", "");
	                return 1;
	            }

	            DeleteDoors(doorid);

	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Drzwi zosta³y usuniête z bazy danych.", "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "nazwa", true))
	    {
	        new doorid, name[50];
	        if(sscanf(comm2, "ds[50]", doorid, name))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) nazwa [uid drzwi] [nazwa]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!DoorInfo[doorid][dUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID drzwi jest nieprawid³owe.", "Zamknij", "");
	                return 1;
	            }
	            if(strlen(name) > 31 || strlen(name) == 0 || strlen(name) < 0)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona nazwa drzwi jest nieprawid³owa.\nMog³a doprowadziæ do zbugowania serwera!", "Zamknij", "");
	                return 1;
	            }

	            format(DoorInfo[doorid][dName], 31, "%s", name);
	            format(PickupInfo[DoorInfo[doorid][Pickup]][Name], 31, "%s", name);

	            SaveDoors(doorid);

	            format(info_box, sizeof(info_box), "Nazwa drzwi %s (uid: %d) zosta³a pomyœlnie zmieniona na %s.", DoorInfo[doorid][dName], DoorInfo[doorid][dUID], name);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", info_box, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "w³aœciciel", true) || !strcmp(comm1, "wlasciciel", true) || !strcmp(comm1, "owner", true))
	    {
	        new doorid, ownertype, owner;
	        if(sscanf(comm2, "ddd", doorid, ownertype, owner))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) wlasciciel [uid drzwi] [typ w³aœciciela] [w³aœciciel]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!DoorInfo[doorid][dUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID drzwi jest nieprawid³owe.", "Zamknij", "");
	                return 1;
	            }

	            DoorInfo[doorid][dOwnerType] = ownertype;
	            DoorInfo[doorid][dOwner] = owner;

	            SaveDoors(doorid);

	            format(info_box, sizeof(info_box), "W³aœciciel drzwi %s (uid: %d) zosta³ zmieniony na %d, %d.", DoorInfo[doorid][dName], DoorInfo[doorid][dUID], ownertype, owner);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", info_box, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1,"wejœcie",true) || !strcmp(comm1,"wejscie",true))
	    {
	        new doorid;
	        if(sscanf(comm2, "d", doorid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) wejœcie [uid drzwi]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!DoorInfo[doorid][dUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID drzwi jest nieprawid³owe.", "Zamknij", "");
	                return 1;
	            }

	            new Float:X, Float:Y, Float:Z, Float:Ang;
	            GetPlayerPos(playerid, X, Y, Z);
	            GetPlayerFacingAngle(playerid, Ang);

	            DoorInfo[doorid][dEnterX] = X;
	            DoorInfo[doorid][dEnterY] = Y;
	            DoorInfo[doorid][dEnterZ] = Z;
	            DoorInfo[doorid][dEnterAng] = Ang;
	            DoorInfo[doorid][dEnterInt] = GetPlayerInterior(playerid);
	            DoorInfo[doorid][dEnterVw] = GetPlayerVirtualWorld(playerid);

	            SaveDoors(doorid);

	            DestroyDynamicPickup(DoorInfo[doorid][Pickup]);
	            DoorInfo[doorid][Pickup] = CreateDynamicPickup(DoorInfo[doorid][dPickupID], 23, DoorInfo[doorid][dEnterX], DoorInfo[doorid][dEnterY], DoorInfo[doorid][dEnterZ], DoorInfo[doorid][dEnterVw], DoorInfo[doorid][dEnterInt]);

	            PickupInfo[DoorInfo[doorid][Pickup]][Name] = DoorInfo[doorid][dName];

	            format(info_box, sizeof(info_box), "Miejsce wejœciowe w drzwiach %s (UID:%d) zosta³o zmienione.", DoorInfo[doorid][dName], DoorInfo[doorid][dUID]);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", info_box, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1,"goto",true))
	    {
	        new doorid;
	        if(sscanf(comm2, "d", doorid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) goto [uid drzwi]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!DoorInfo[doorid][dUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID drzwi jest nieprawid³owe.", "Zamknij", "");
	                return 1;
	            }

	            SetPlayerPos(playerid, DoorInfo[doorid][dEnterX], DoorInfo[doorid][dEnterY], DoorInfo[doorid][dEnterZ]);
	            SetPlayerVirtualWorld(playerid, DoorInfo[doorid][dEnterVw]);
	            SetPlayerInterior(playerid, DoorInfo[doorid][dEnterInt]);

	            format(info_box, sizeof(info_box), "Zosta³eœ przeteleportowany do drzwi %s (UID:%d).", DoorInfo[doorid][dName], doorid);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", info_box, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1,"wyjœcie",true) || !strcmp(comm1,"wyjscie",true))
	    {
	        new doorid;
	        if(sscanf(comm2, "d", doorid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) wyjœcie [uid drzwi]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!DoorInfo[doorid][dUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID drzwi jest nieprawid³owe.", "Zamknij", "");
	                return 1;
	            }

	            new Float:X, Float:Y, Float:Z, Float:Ang;
	            GetPlayerPos(playerid, X, Y, Z);
	            GetPlayerFacingAngle(playerid, Ang);

	            DoorInfo[doorid][dExitX] = X;
	            DoorInfo[doorid][dExitY] = Y;
	            DoorInfo[doorid][dExitZ] = Z;
	            DoorInfo[doorid][dExitAng] = Ang;
	            DoorInfo[doorid][dExitInt] = GetPlayerInterior(playerid);
	            DoorInfo[doorid][dExitVw] = GetPlayerVirtualWorld(playerid);

	            SaveDoors(doorid);

	            format(info_box, sizeof(info_box), "Miejsce wyjœciowe w drzwiach %s (UID:%d) zosta³o zmienione.", DoorInfo[doorid][dName], DoorInfo[doorid][dUID]);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", info_box, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1,"pickup",true) )
	    {
	        new doorid, pickupid;
	        if(sscanf(comm2, "dd", doorid, pickupid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /ad(rzwi) pickup [uid drzwi] [id pickupa]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!DoorInfo[doorid][dUID])
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone ID drzwi jest nieprawid³owe.", "Zamknij", "");
	                return 1;
	            }
	            if(pickupid > 25)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Model jest tylko od 1 do 25.", "Zamknij", "");
	                return 1;
	            }

	            new pickup_model = PickupIDs[pickupid];

	            DoorInfo[doorid][dPickupID] = pickup_model;

	            DestroyDynamicPickup(DoorInfo[doorid][Pickup]);
	            DoorInfo[doorid][Pickup] = CreateDynamicPickup(DoorInfo[doorid][dPickupID], 23, DoorInfo[doorid][dEnterX], DoorInfo[doorid][dEnterY], DoorInfo[doorid][dEnterZ], DoorInfo[doorid][dEnterVw], DoorInfo[doorid][dEnterInt]);
	            PickupInfo[DoorInfo[doorid][Pickup]][Name] = DoorInfo[doorid][dName];

	            SaveDoors(doorid);

	            format(info_box, sizeof(info_box), "Pickup w drzwiach %s (UID:%d) zosta³ zmieniony na %d.", DoorInfo[doorid][dName], DoorInfo[doorid][dUID], pickupid);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", info_box, "Zamknij", "");
	        }
	    }
	}
    return 1;
}
CMD:ad(playerid, params[]) return cmd_adrzwi(playerid, params);

CMD:aprzedmiot(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_THINGS)) return 1;
    new comm1[32], comm2[128], string[256];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /aprzedmiot [stwórz | usuñ | przepisz | typ | nazwa | value | flagi]", "Zamknij", "");
        return 1;
    }
    else
    {
		if(!strcmp(comm1, "stwórz", true) || !strcmp(comm1, "stworz", true))
	    {
	        ShowPlayerDialog(playerid, D_ITEM_NAME, DIALOG_STYLE_INPUT, " Informacja", "Podaj nazwê nowo tworzonego przedmiotu:", "Wybierz", "Zamknij");
	    }
	    else if(!strcmp(comm1, "usuñ", true) || !strcmp(comm1, "usun", true))
	    {
	        new item_uid;
	        if(sscanf(comm2, "d", item_uid))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "/aprzedmiot usuñ [UID przedmiotu]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        new itemid = GetItemID(item_uid);
		        if(!ItemInfo[itemid][iUID])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza.", "Zamknij", "");
		            return 1;
		        }

		        format(string, sizeof(string), "Usun¹³eœ przedmiot %s (UID: %d) pomyœlnie.", ItemInfo[itemid][iName], ItemInfo[itemid][iUID]);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");
		        
		        DeleteItem(ItemInfo[itemid][iUID]);
	        }
	    }
	    else if(!strcmp(comm1, "przepisz", true) || !strcmp(comm1, "przypisz", true))
	    {
	        new item_uid, playerid2, mysql[256];
	        if(sscanf(comm2, "dd", item_uid, playerid2))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "/aprzedmiot przepisz [UID przedmiotu] [ID gracza]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        new itemid = GetItemID(item_uid);
		        if(!ItemInfo[itemid][iUID])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza.", "Zamknij", "");
		            return 1;
		        }
		        if(!Logged[playerid2])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzone ID gracza jest nieprawid³owe.\nNie znajduje siê on w grze.", "Zamknij", "");
		            return 1;
		        }

		        ItemInfo[itemid][iPlace] = OWNER_PLAYER;
		        ItemInfo[itemid][iOwner] = CharacterCache[playerid2][pUID];

		        format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `ownertype` = '%d', `owner` = '%d' WHERE `uid` = '%d' LIMIT 1", OWNER_PLAYER, CharacterCache[playerid2][pUID], ItemInfo[itemid][iUID]);
		        mysql_check(); mysql_query(mysql);

		        format(string, sizeof(string), "W³aœciciel przedmiotu %s (UID: %d) zosta³ pomyœlnie zmieniony.\nNowy w³aœciciel: %s.", ItemInfo[itemid][iName], ItemInfo[itemid][iUID], ItemInfo[itemid][iValue2], PlayerName2(playerid2));
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "typ", true) || !strcmp(comm1, "kind", true))
	    {
	        new item_uid, item_type, mysql[256];
	        if(sscanf(comm2, "dd", item_uid, item_type))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "/aprzedmiot typ [UID przedmiotu] [typ]", "Zamknij", "");
	            return 1;
	        }
	        new itemid = GetItemID(item_uid);
	        if(!ItemInfo[itemid][iUID])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza.", "Zamknij", "");
	            return 1;
	        }

	        ItemInfo[itemid][iType] = item_type;
	        format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `kind` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[itemid][iType], ItemInfo[itemid][iUID]);
	        mysql_check(); mysql_query(mysql);

	        format(string, sizeof(string), "Typ przedmiotu %s (UID: %d) zosta³ pomyœlnie zmieniony.\nNowy typ przedmiotu: %s.", ItemInfo[itemid][iName], ItemInfo[itemid][iUID], ItemTypeInfo[ItemInfo[itemid][iType]][iTypeName]);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacje", string, "Zamknij", "");
	    }
	    else if(!strcmp(comm1, "nazwa", true) || !strcmp(comm1, "name", true))
	    {
	        new item_uid, item_name[32], mysql[128];
	        if(sscanf(comm2, "ds[32]", item_uid, item_name))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "/aprzedmiot nazwa [UID przedmiotu] [nazwa]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        new itemid = GetItemID(item_uid);
		        if(!ItemInfo[itemid][iUID])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza.", "Zamknij", "");
		            return 1;
		        }

		        format(string, sizeof(string), "Nazwa przedmiotu %s (UID: %d) zosta³a pomyœlnie zmieniona.\nNowa nazwa przedmiotu: %s.", ItemInfo[itemid][iName], ItemInfo[itemid][iUID], item_name);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");

		        mysql_real_escape_string(item_name, item_name);
		        strmid(ItemInfo[itemid][iName], item_name, 0, strlen(item_name), 32);

		        format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `name` = '%s' WHERE `uid` = '%d' LIMIT 1", ItemInfo[itemid][iName], ItemInfo[itemid][iUID]);
		        mysql_check(); mysql_query(mysql);
	        }
	    }
	    else if(!strcmp(comm1, "wartoœæ", true) || !strcmp(comm1, "wartoœæ", true) || !strcmp(comm1, "value", true))
	    {
	        new item_uid, item_value1, item_value2, mysql[256];
	        if(sscanf(comm2, "ddd", item_uid, item_value1, item_value2))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "/aprzedmiot wartoœæ [UID przedmiotu] [wartoœæ 1] [wartoœæ 2]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        new itemid = GetItemID(item_uid);
		        if(!ItemInfo[itemid][iUID])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza.", "Zamknij", "");
		            return 1;
		        }

		        ItemInfo[itemid][iValue1] = item_value1;
		        ItemInfo[itemid][iValue2] = item_value2;

		        format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `value1` = '%d', `value2` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[itemid][iValue1], ItemInfo[itemid][iValue2], ItemInfo[itemid][iUID]);
		        mysql_check(); mysql_query(mysql);

		        format(string, sizeof(string), "Wartoœci przedmiotu %s (UID: %d) zosta³y pomyœlnie zmienione.\nNowe wartoœci przedmiotu: %d / %d.", ItemInfo[itemid][iName], ItemInfo[itemid][iUID], ItemInfo[itemid][iValue1], ItemInfo[itemid][iValue2]);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "flagi", true) || !strcmp(comm1, "flag", true) || !strcmp(comm1, "flags", true))
	    {
	        new item_id, flag;
	        if(sscanf(comm2, "dd", item_id, flag))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "/aprzedmiot wartoœæ [UID przedmiotu] [wartoœæ 1] [wartoœæ 2]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            new itemid = GetItemID(item_id);
		        if(!ItemInfo[itemid][iUID])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza.", "Zamknij", "");
		            return 1;
		        }
		        
		        ItemInfo[itemid][iFlags] += flag;
		        
		        mysql_check();
		        mysql_query_format("UPDATE `fc_items` SET `flag` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[itemid][iFlags], ItemInfo[itemid][iUID]);
		        
		        format(string, sizeof(string), "Flagi przedmiotu %s (UID: %d) zosta³y pomyœlnie zmienione.\nNowe flagi przedmiotu: %d.", ItemInfo[itemid][iName], ItemInfo[itemid][iUID], ItemInfo[itemid][iFlags]);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");
	        }
	    }
	}
    return 1;
}
CMD:ap(playerid, params[]) return cmd_aprzedmiot(playerid, params);

CMD:set(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_PLAYER)) return 1;
    new comm1[32], comm2[128];
    if(sscanf(params, "s[32]S()[128]", comm1, comm2))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set [admin(istrator) | SUPP(istance) | cash | bank | hours | minutes | hp | skin | job | aj | score | pogoda | czas | vw | int | narkotyk | paczka | pos | load]", "Zamknij", "");
        return 1;
    }
    else
    {
	   	if(!strcmp(comm1, "administrator", true) || !strcmp(comm1, "admin", true))
	    {
	        new playerid2, level, string[256];
	        if(sscanf(comm2, "id", playerid2, level))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set administrator [ID gracza] [poziom (1-4)]\n\n1 - Administratro poziomu 1\n2 - Administrator poziomu 2\n3 - Administrator poziomu 3\n4 - Zarz¹d", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(level > 4 || level < 0)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony poziom administratora jest nieprawid³owy.", "Zamknij", "");
		            return 1;
		        }
		        if(CharacterCache[playerid][pAdmin] != 9)
		        {
		        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do zmiany poziomu administratora.\nTwój poziom jest zbyt niski.", "Zamknij", "");
		            return 1;
		        }

				if(level == 0) CharacterCache[playerid2][pAdmin] = 0;
				else CharacterCache[playerid2][pAdmin] = level + 5;

			    CharacterCache[playerid2][pAdminDuty] = false;

		        if(IsPlayerPremium(playerid2)) CharacterCache[playerid2][pNickColor] = 0xFCDF1E99;
				else CharacterCache[playerid2][pNickColor] = 0xFFFFFF99;

			    UpdatePlayer3DTextNick(playerid2);

		        SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);

		        format(string, sizeof(string), "Poziom administratora %s (ID: %d) zosta³ zmieniony na %d.", PlayerName2(playerid2), playerid2, level);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój poziom administratora na %d.", PlayerName2(playerid), playerid, level);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "support", true) || !strcmp(comm1, "supp", true))
	    {
	        new playerid2, level, string[256];
	        if(sscanf(comm2, "id", playerid2, level))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set support [ID gracza] [poziom (1-5)]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(level > 5 || level < 0)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony poziom support jest nieprawid³owy.", "Zamknij", "");
		            return 1;
		        }
		        if(CharacterCache[playerid][pAdmin] != 9)
		        {
		        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do zmiany poziomu supportu.\nTwój poziom jest zbyt niski.", "Zamknij", "");
		            return 1;
		        }

		        if(level == 0) CharacterCache[playerid2][pAdmin] = 0;
		        else CharacterCache[playerid2][pAdmin] = level;

		        CharacterCache[playerid2][pAdminDuty] = false;

				if(IsPlayerPremium(playerid2)) CharacterCache[playerid2][pNickColor] = 0xFCDF1E99;
				else CharacterCache[playerid2][pNickColor] = 0xFFFFFF99;

				UpdatePlayer3DTextNick(playerid2);

				SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);

				format(string, sizeof(string), "Poziom supportera %s (ID: %d) zosta³ zmieniony na %d.", PlayerName2(playerid2), playerid2, level);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój poziom supportera na %d.", PlayerName2(playerid), playerid, level);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
			}
	    }
	    else if(!strcmp(comm1, "cash", true))
	    {
	        if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_CASH)) return 1;
	        new playerid2, cash, string[256];
	        if(sscanf(comm2, "id", playerid2, cash))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set cash [ID gracza] [stan gotówki]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(cash < 1 || cash > 10000)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony stan gotówki jest nieprawid³owy.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[playerid2][pCash] = cash;
		        SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);

		        ResetPlayerMoney(playerid2);
		        GivePlayerMoney(playerid2, CharacterCache[playerid2][pCash]);

		        SendAdminMessageFormat(0xD96A6AFF, "[AI] %s (ID: %d) zmieni³ stan gotówki gracza %s (ID: %d) na $%d.", PlayerName2(playerid), playerid, PlayerName2(playerid2), playerid2, cash);

		        format(string, sizeof(string), "Gotówka gracza %s (ID: %d) zosta³a zmieniona na $%d.", PlayerName2(playerid2), playerid2, cash);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój stan gotówki na $%d.", PlayerName2(playerid), playerid, cash);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "bank", true))
	    {
	        if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_CASH)) return 1;
	        new playerid2, bank, string[256];
	        if(sscanf(comm2, "id", playerid2, bank))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set bank [ID gracza] [stan gotówki]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(bank < 0 || bank > 5000)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony stan gotówki w banku jest nieprawid³owy.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[playerid2][pBankCash] = bank;
		        SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);

		        format(string, sizeof(string), "Gotówka w banku gracza %s (ID: %d) zosta³a zmieniona na $%d.", PlayerName2(playerid2), playerid2, bank);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój stan gotówki bankowej na $%d.", PlayerName2(playerid), playerid, bank);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "hours", true))
	    {
	        new playerid2, hours, string[256];
	        if(sscanf(comm2, "id", playerid2, hours))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set hours [ID gracza] [iloœæ godzin]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(hours < 0)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona iloœæ godzin jest nieprawid³owa.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[playerid2][pHours] = hours;
		        SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);

		        format(string, sizeof(string), "Godziny gracza %s (ID: %d) zosta³y zmienione na %d.", PlayerName2(playerid2), playerid2, hours);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twoj¹ iloœæ godzin na %d.", PlayerName2(playerid), playerid, hours);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "minutes", true))
	    {
	        new playerid2, minutes, string[256];
	        if(sscanf(comm2, "id", playerid2, minutes))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set minutes [ID gracza] [iloœæ minut (1 - 60)]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(minutes < 0 || minutes == 0 || minutes > 60)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona iloœæ minut jest nieprawid³owy.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[playerid2][pMinutes] = minutes;
		        SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);

		        format(string, sizeof(string), "Iloœæ minut gracza %s (ID: %d) zosta³a zmieniona na %d.", PlayerName2(playerid2), playerid2, minutes);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twoj¹ iloœæ minut na %d.", PlayerName2(playerid), playerid, minutes);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "hp", true))
	    {
	        new playerid2, Float:health, string[256];
	        if(sscanf(comm2, "if", playerid2, health))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set hp [ID gracza] [stan zdrowia]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(health < 0 || health == 0 || health > 100)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony stan zdrowia jest nieprawid³owy.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[playerid2][pHealth] = health;
		        SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);

		        SetPlayerHealth(playerid2, CharacterCache[playerid2][pHealth]);

		        format(string, sizeof(string), "Stan zdrowia gracza %s (ID: %d) zosta³ zmieniony na %0.1f.", PlayerName2(playerid2), playerid2, health);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój stan zdrowia na %0.1f.", PlayerName2(playerid), playerid, health);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "skin", true))
	    {
	        new playerid2, skin, string[256];
	        if(sscanf(comm2, "id", playerid2, skin))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set skin [ID gracza] [ID skina (0 - 299)]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(skin < 0 || skin > 299)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' skina jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[playerid2][pSkin] = skin;
		        SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);

		        SetPlayerSkin(playerid2, CharacterCache[playerid2][pSkin]);

		        format(string, sizeof(string), "Skin gracza %s (ID: %d) zosta³a zmieniona na %d.", PlayerName2(playerid2), playerid2, skin);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój skin na %d.", PlayerName2(playerid), playerid, skin);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "job", true))
	    {
	        new playerid2, job, string[256];
	        if(sscanf(comm2, "id", playerid2, job))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set job [ID gracza] [ID pracy (1)]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(job != 1)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' pracy jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[playerid2][pJob] = job;
		        SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);

		        format(string, sizeof(string), "Praca gracza %s (ID: %d) zosta³a zmieniona na %d.", PlayerName2(playerid2), playerid2, job);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twoj¹ pracê dorywcz¹ na %d.", PlayerName2(playerid), playerid, job);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "aj", true))
	    {
	        new playerid2, aj, string[256];
	        if(sscanf(comm2, "id", playerid2, aj))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set aj [ID gracza] [czas (0 - 120)]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(aj < 0 || aj > 120 || aj == 0)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony czas Admin Jail jest nieprawid³owy.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[playerid2][pAJ] = aj * 60;
		        SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);

		        format(string, sizeof(string), "Czas Admin Jail %s (ID: %d) zosta³ zmieniony na %d min.", PlayerName2(playerid2), playerid2, aj);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój czas Admin Jail na %d min.", PlayerName2(playerid), playerid, aj);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "score", true))
	    {
	        new playerid2, score, string[256];
	        if(sscanf(comm2, "id", playerid2, score))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set score [ID gracza] [iloœæ (max. 10000)]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(score < 0 || score > 10000 || score == 0)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona iloœæ cPoints jest nieprawid³owa.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[playerid2][pGlobalScore] = score;
		        SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);

		        SetPlayerScore(playerid2, CharacterCache[playerid2][pGlobalScore]);

		        format(string, sizeof(string), "Iloœæ GameScore gracza %s (ID: %d) zosta³a zmieniona na %d.", PlayerName2(playerid2), playerid2, score);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");

		        format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twoj¹ iloœæ GameScore na %d.", PlayerName2(playerid), playerid, score);
		        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "pogoda", true))
	    {
	        new weather_id;
	        if(sscanf(comm2, "d", weather_id))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set pogoda [ID pogody]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            SetWeather(weather_id);

	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pogoda zosta³a pomyœlnie zmieniona.", "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "czas", true))
	    {
	        new time_id;
	        if(sscanf(comm2, "d", time_id))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /set czas [godzina]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(time_id > 24 || time_id == 0 || time_id < 0)
	            {
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony czas jest nieprawid³owy.", "Zamknij", "");
	                return 1;
	            }

	            SetWorldTime(time_id);

	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Czas gry zosta³ pomyœlnie zmieniony.", "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "vw", true))
	    {
	        new playerid2, vw, string[128];
	        if(sscanf(comm2, "dd", playerid2, vw))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /set vw [id gracza] [vw]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            SetPlayerVirtualWorld(playerid2, vw);

	            format(string, sizeof(string), "Pomyœlnie zmieni³eœ graczowi %s Virtual World na %d.", PlayerName2(playerid2), vw);
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

	            format(string, sizeof(string), "Administrator %s zmieni³ Tobie Virtual World na %d.", PlayerName2(playerid), vw);
	            ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "int", true))
	    {
	        new name[32], interior, string[1024];
	        if(sscanf(comm2, "s[32]", name))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /set int [id interioru nazwa]", "Zamknij", "");
	            return 1;
	        }
	        if(isNumeric(name))
	        {
	            interior = strval(name);

	            SetPlayerPos(playerid, Interior[interior][INTERIOR_X], Interior[interior][INTERIOR_Y], Interior[interior][INTERIOR_Z]);
	            SetPlayerFacingAngle(playerid, Interior[interior][INTERIOR_A]);
	            SetPlayerInterior(playerid, Interior[interior][INTERIOR_ID]);
	        }
	        else
	        {
	            ForeachEx(i, sizeof(Interior))
	            {
	                if(strfind(Interior[i][INTERIOR_NAME], name, true) >= 0)
	                {
	                    format(string, sizeof(string), "%s\n%d - %s", string, i, Interior[i][INTERIOR_NAME]);
	                }
	            }

	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, " Interior", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "narkotyk", true))
	    {
	        new playerid2;
	        if(sscanf(comm2, "i", playerid2))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /set narkotyk [ID gracza]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
				{
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(!CharacterCache[playerid2][pDrugs] || !CharacterCache[playerid2][pDrugsTime])
				{
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest pod wyp³ywem narkotyków.", "Zamknij", "");
		            return 1;
		        }

	            CharacterCache[playerid2][pDrugs] = DRUG_MAR;
			    CharacterCache[playerid2][pDrugsTime] = 0;

			    OnPlayerUseDrug(playerid2);

			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Dzia³anie narkotyku dla gracza zosta³o wy³¹czone.", "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "paczka", true))
	    {
	        new playerid2;
	        if(sscanf(comm2, "i", playerid2))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /set paczka [ID gracza]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            if(!Logged[playerid2] || !IsPlayerConnected(playerid2))
				{
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzone 'id' gracza jest nieprawid³owe.", "Zamknij", "");
		            return 1;
		        }
		        if(!CharacterCache[playerid2][pPackage])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Gracz nie dostarcza ¿adnej z paczek.", "Zamknij", "");
		            return 1;
		        }

	            mysql_query_format("UPDATE `fc_orders` SET `driver` = 0 WHERE `order_id` = '%d'", CharacterCache[playerid2][pPackageID]);

				CharacterCache[playerid2][pPackage] = false;
				CharacterCache[playerid2][pPackageID] = 0;
				CharacterCache[playerid2][pPackageDoor] = 0;
				CharacterCache[playerid2][pPackageTime] = 0;

			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Dostarczana paczka przez gracza zosta³a pomyœlnie anulowana.", "Zamknij", "");
			    ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Administrator przerwa³ Tobie dostarczanie paczki.", "Zamknij", "");
	        }
	    }
	    else if(!strcmp(comm1, "pos", true))
	    {
	    	new Pos[3];
	        if(sscanf(comm2, "fff", Pos[0], Pos[1], Pos[2]))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /set pos [X] [Y] [Z]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            SetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	            
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zosta³eœ teleportowany na pozycjê.", "Zamknij", "");
	        }
	 	}
	 	else if(!strcmp(comm1, "load", true))
	    {
	        new vw;
	        if(sscanf(comm2, "d", vw))
	        {
	         	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Zastosowanie komendy", "U¿yj: /set vw [ID œwiata]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
	            LoadObjectInDoor(vw);
	            
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Obiekty na œwiecie zosta³y prze³adowane.", "Zamknij", "");
	        }
	    }
	}
    return 1;
}

CMD:duty(playerid, params[])
{
    new comm1[32];
    new hours, minutes, seconds;
    gettime(hours, minutes, seconds);
            
    if(sscanf(params, "s[32]", comm1))
    {
        if(CharacterCache[playerid][pAdmin])
        {
        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /duty [a(dmin) | SUPP(istance) | p(raca)]", "Zamknij", "");
		}
		else
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /duty [p(raca)]", "Zamknij", "");
		}
		return 1;
    }
    else if(!strcmp(comm1, "admin", true) || !strcmp(comm1, "a", true))
    {
        if(DutyGroup[playerid])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aby wejœæ na s³u¿bê administratora musisz zejœæ ze s³u¿by w grupie.", "Zamknij", "");
            return 1;
        }

		if(CharacterCache[playerid][pAdmin] > 5)
		{
	        if(CharacterCache[playerid][pAdmin] == 9)
	        {
	            if(CharacterCache[playerid][pAdminDuty])
	            {
	                CharacterCache[playerid][pAdminDuty] = false;
	                SendClientMessageFormat(playerid, COLOR_ADMIN_GA, " » Zszed³eœ ze s³u¿by Zarz¹du, godzina zakoñczenia %02d:%02d.", hours, minutes);

                    InfoAdminFormat(playerid, "zszedl ze sluzby zarzadu.", CharacterCache[playerid][pGlobalNick]);
                    
	            	PlayerTextDrawSetString(playerid, AdminDuty[playerid], "~r~~h~~h~~h~ADM ~>~ ~w~T/~r~N");
	            	PlayerTextDrawShow(playerid, AdminDuty[playerid]);
	            	
	            	PlayerTextDrawHide(playerid, AdminInfo[playerid]);

	                if(IsPlayerPremium(playerid)) CharacterCache[playerid][pNickColor] = 0xFCDF1E99;
					else CharacterCache[playerid][pNickColor] = 0xFFFFFF99;
		
	                UpdatePlayer3DTextNick(playerid);
	            }
	            else
	            {
	                CharacterCache[playerid][pAdminDuty] = true;
	                SendClientMessageFormat(playerid, COLOR_ADMIN_GA, " » Wszed³eœ na s³u¿bê Zarz¹du, godzina rozpoczêcia %02d:%02d.", hours, minutes);

                    InfoAdminFormat(playerid, "wszedl na sluzbe zarzadu.", CharacterCache[playerid][pGlobalNick]);
                    
	                PlayerTextDrawSetString(playerid, AdminDuty[playerid], "~r~~h~~h~~h~ADM ~>~ ~g~T~w~/N");
	            	PlayerTextDrawShow(playerid, AdminDuty[playerid]);
	            	
	            	PlayerTextDrawShow(playerid, AdminInfo[playerid]);

	                CharacterCache[playerid][pNickColor] = 0xFFFFFF99;
	                UpdatePlayer3DTextNick(playerid);
	            }
	        }
	        else
	        {
	            if(CharacterCache[playerid][pAdminDuty])
	            {
	                CharacterCache[playerid][pAdminDuty] = false;
	                SendClientMessageFormat(playerid, COLOR_ADMIN_ADMIN, " » Zszed³eœ ze s³u¿by Administratora, godzina zakoñczenia %02d:%02d.", hours, minutes);

                    InfoAdminFormat(playerid, "zszedl ze sluzby administratora.", CharacterCache[playerid][pGlobalNick]);
                    
	            	PlayerTextDrawSetString(playerid, AdminDuty[playerid], "~g~~h~~h~~h~ADM ~>~ ~w~T/~r~N");
	            	PlayerTextDrawShow(playerid, AdminDuty[playerid]);
	            	
	            	PlayerTextDrawHide(playerid, AdminInfo[playerid]);

	                if(IsPlayerPremium(playerid)) CharacterCache[playerid][pNickColor] = 0xFCDF1E99;
					else CharacterCache[playerid][pNickColor] = 0xFFFFFF99;
		
	                UpdatePlayer3DTextNick(playerid);
	            }
	            else
	            {
	                CharacterCache[playerid][pAdminDuty] = true;
	                SendClientMessageFormat(playerid, COLOR_ADMIN_ADMIN, " » Wszed³eœ na s³u¿bê Administratora, godzina rozpoczêcia %02d:%02d.", hours, minutes);

                    InfoAdminFormat(playerid, "wszedl na sluzbe administratora.", CharacterCache[playerid][pGlobalNick]);
                    
	                PlayerTextDrawSetString(playerid, AdminDuty[playerid], "~g~~h~~h~~h~ADM ~>~ ~g~T~w~/N");
	            	PlayerTextDrawShow(playerid, AdminDuty[playerid]);
	            	
	            	PlayerTextDrawShow(playerid, AdminInfo[playerid]);

	                CharacterCache[playerid][pNickColor] = 0xFFFFFF99;
	                UpdatePlayer3DTextNick(playerid);
	            }
	        }
        }
    }
    else if(!strcmp(comm1, "support", true) || !strcmp(comm1, "supp", true))
    {
        if(DutyGroup[playerid])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Aby wejœæ na s³u¿bê administratora musisz zejœæ ze s³u¿by w grupie.", "Zamknij", "");
            return 1;
        }

        if(CharacterCache[playerid][pAdmin] > 0 && CharacterCache[playerid][pAdmin] < 6)
        {
            new nick[MAX_PLAYER_NAME];
            
            if(CharacterCache[playerid][pAdminDuty])
            {
                CharacterCache[playerid][pAdminDuty] = false;
                SendClientMessageFormat(playerid, COLOR_ADMIN_ASS, " » Zszed³eœ ze s³u¿by Supportera %s, godzina zakoñczenia %02d:%02d.", AssCode(playerid), hours, minutes);

                InfoAdminFormat(playerid, "zszedl ze sluzby supportu.", CharacterCache[playerid][pGlobalNick]);
                
                PlayerTextDrawSetString(playerid, AdminDuty[playerid], "~b~~h~~h~~h~SUPP ~>~ ~w~T/~r~N");
            	PlayerTextDrawShow(playerid, AdminDuty[playerid]);
            	
            	PlayerTextDrawHide(playerid, AdminInfo[playerid]);
            	
            	SetPlayerName(playerid, CharacterCache[playerid][pNick]);
            	
                if(IsPlayerPremium(playerid)) CharacterCache[playerid][pNickColor] = 0xFCDF1E99;
				else CharacterCache[playerid][pNickColor] = 0xFFFFFF99;
					
                UpdatePlayer3DTextNick(playerid);
            }
            else
            {
                CharacterCache[playerid][pAdminDuty] = true;
                SendClientMessageFormat(playerid, COLOR_ADMIN_ASS, " » Wszed³eœ na s³u¿bê Supportera %s, godzina rozpoczêcia %02d:%02d.", AssCode(playerid), hours, minutes);

                InfoAdminFormat(playerid, "wszedl na sluzbe supportu.", CharacterCache[playerid][pGlobalNick]);
                
                PlayerTextDrawSetString(playerid, AdminDuty[playerid], "~b~~h~~h~~h~SUPP ~>~ ~g~T~w~/N");
            	PlayerTextDrawShow(playerid, AdminDuty[playerid]);
            	
            	PlayerTextDrawShow(playerid, AdminInfo[playerid]);
            	
            	format(nick, sizeof(nick), "Support_%s", AssCode(playerid));
            	SetPlayerName(playerid, nick);
            	
                CharacterCache[playerid][pNickColor] = 0x53866899;
                UpdatePlayer3DTextNick(playerid);
            }
        }
    }
    else if(!strcmp(comm1, "praca", true) || !strcmp(comm1, "p", true))
    {
    	if(!CharacterCache[playerid][pJob])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz ¿adnej pracy dorywczej.\nUdaj siê na poblisk¹ stacjê i porozmawiaj z mechanikiem Allanem.", "Zamknij", "");
            return 1;
        }
        if(!IsPlayerInArea(playerid, AREA_STATION))
        {
        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê na stacji paliw.\nUdaj siê na poblisk¹ stacjê i porozmawiaj z mechanikiem.", "Zamknij", "");
            return 1;
        }
        if(CharacterCache[playerid][pDutyJob])
        {
            new time_hours, time_minutes, time_second, cash = 0, title[128], string[256];
            GetPlayedTimeSecZ(CharacterCache[playerid][pDutyJobTime], time_hours, time_minutes, time_second);
            
            CharacterCache[playerid][pDutyJob] = false;
            CharacterCache[playerid][pDutyJobTime] = 0;
            
            cash += PlayerActions[playerid] * 2;
            cash += time_hours * 60;
            cash += time_minutes * 1;
            
            format(title, sizeof(title), "{FFFFFF}Pomocnik stacji [{8CD147}%dh, %dmin{FFFFFF}]", time_hours, time_minutes);
            format(string, sizeof(string), "Przepracowany czas:\t\t{8CD147}%dh, %dmin\nZarobiona gotówka:\t\t$%d\n-----\nGotówka przydzielana jest co 30 minut, od czasu s³u¿by.\nW momencie AFK czas s³u¿by nie nalicza siê.", time_hours, time_minutes, cash);
            
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, title, string, "Zamknij", "");
        }
        else
        {
        	CharacterCache[playerid][pDutyJob] = true;
        
            PlayerActions[playerid] = 0;
        	SendClientMessage(playerid, 0x206FB0FF, "Wszed³eœ na s³u¿bê pomocnika stacji. Nie oddalaj siê teraz od stacji.");
        }
    }
    return 1;
}

CMD:bw(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] == 0) return 1;
    new type[32], varchar[32], string[128];
    if(sscanf(params, "s[32]S()[32]", type, varchar))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /bw [na³ó¿ | zdejmij | lista]", "Zamknij", "");
        return 1;
    }
    else
    {
	    if(!strcmp(type, "na³ó¿", true) || !strcmp(type, "naloz", true))
	    {
	        new giveplayer_id, time;
	        if(sscanf(varchar, "ud", giveplayer_id, time))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /bw na³ó¿ [ID gracza] [czas (minuty)]", "Zamknij", "");
	            return 1;
	        }
	        if(!Logged[giveplayer_id])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
	            return 1;
	        }
	        if(CharacterCache[giveplayer_id][pBW])
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Ten gracz ma ju¿ BW.\nU¿yj /bw zdejmij, aby zdj¹æ BW.", "Zamknij", "");
	            return 1;
	        }

	        CharacterCache[giveplayer_id][pBW] = time * 60;
	        GetPlayerPos(giveplayer_id, CharacterCache[giveplayer_id][pPos][0], CharacterCache[giveplayer_id][pPos][1], CharacterCache[giveplayer_id][pPos][2]);

	        CharacterCache[giveplayer_id][pInt] = GetPlayerInterior(playerid);
	        CharacterCache[giveplayer_id][pVW] = GetPlayerVirtualWorld(playerid);

	        SetPlayerCameraPos(giveplayer_id, CharacterCache[giveplayer_id][pPos][0] + 3, CharacterCache[giveplayer_id][pPos][1] + 4, CharacterCache[giveplayer_id][pPos][2] + 7);
	        SetPlayerCameraLookAt(giveplayer_id, CharacterCache[giveplayer_id][pPos][0], CharacterCache[giveplayer_id][pPos][1], CharacterCache[giveplayer_id][pPos][2]);

	        TogglePlayerControllable(giveplayer_id, 0);

	        SavePlayerStats(giveplayer_id, SAVE_PLAYER_POS);

	        format(string, sizeof(string), "Administrator %s na³o¿y³ Ci BW. Czas: %d min", PlayerName2(playerid), time);
	        ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");

	        format(string, sizeof(string), "Pomyœlnie na³o¿ono BW graczowi %s (ID: %d, UID: %d). Czas: %d min.", PlayerName2(giveplayer_id), giveplayer_id, CharacterCache[giveplayer_id][pUID], time);
	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");
	    }
	    else if(!strcmp(type, "zdejmij", true))
	    {
	        new giveplayer_id;
	        if(sscanf(varchar, "i", giveplayer_id))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /bw zdejmij [ID gracza]", "Zamknij", "");
	            return 1;
	        }
	        else
	        {
		        if(!Logged[giveplayer_id])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
		            return 1;
		        }
		        if(!CharacterCache[giveplayer_id][pBW])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Ten gracz nie ma BW.", "Zamknij", "");
		            return 1;
		        }

		        CharacterCache[giveplayer_id][pBW] = 0;

		        ApplyAnimation(giveplayer_id, "Attractors", "Stepsit_out", 4.0, 0, 0, 0, 0, 0, 1);
		        TogglePlayerControllable(giveplayer_id, 1);

		        SetCameraBehindPlayer(giveplayer_id);
		        SetPlayerHealth(giveplayer_id, 20);

		        format(string, sizeof(string), "Administrator %s zdj¹³ Ci BW", PlayerName2(playerid));
		        ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");

		        format(string, sizeof(string), "Pomyœlnie zdjêto BW graczowi %s (ID: %d, UID: %d).", PlayerName2(giveplayer_id), giveplayer_id, CharacterCache[giveplayer_id][pUID]);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");
	        }
	    }
	    else if(!strcmp(type, "lista", true))
	    {
	        new list_players[256];
	        ForeachEx(i, MAX_PLAYERS)
	        {
	            if(Logged[i])
	            {
	                if(CharacterCache[i][pBW])
	                {
	                    format(list_players, sizeof(list_players), "%s\n%d\t%d min\t%s", list_players, i, CharacterCache[i][pBW] / 60, PlayerName2(i));
	                }
	            }
	        }

	        if(!strlen(list_players))
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Nie znaleziono ¿adnych graczy maj¹cych BW.", "Zamknij", "");
	        }

	        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, "Znaleziono graczy maj¹cych BW:", list_players, "Zamknij", "");
	    }
    }
    return 1;
}

CMD:glob(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] != 9) return 1;
	new text[128];
	if(sscanf(params, "s[128]", text))
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /global [tekst]", "Zamknij", "");
        return 1;
	}
	else
	{
		SendClientMessageToAllFormat(COLOR_LIGHTPINK, "(( %s: %s ))", CharacterCache[playerid][pGlobalNick], text);
	}
	return 1;
}

CMD:restart(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] != 9) return 1;
    
    Restart = 11;
    return 1;
}

CMD:slap(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] <= 0) return 1;
	new playerid2;
	if(sscanf(params, "i", playerid2))
	{
	    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /slap [id gracza]", "Zamknij", "");
		return 1;
	}
	else
	{
		new Float: x, Float: y, Float: z;
		GetPlayerPos(playerid2, x, y, z);
		
		SetPlayerPos(playerid2, x, y, z + 5);
		
		PlayerPlaySound(playerid, 1190, 0.0, 0.0, 0.0);
		PlayerPlaySound(playerid2, 1190, 0.0, 0.0, 0.0);
	}
    return 1;
}

CMD:warn(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] <= 0) return 1;
    new giveplayer_id, reason[128];
    if(sscanf(params, "us[128]", giveplayer_id, reason))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /warn [ID gracza] [powód]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }

        SendClientMessageFormat(giveplayer_id, 0xBA2818FF, "(INFO) Otrzyma³eœ ostrze¿enie od %s, powód: %s", CharacterCache[playerid][pGlobalNick], reason);
        GivePenalty(giveplayer_id, playerid, -1, PENALTY_WARN, 0, reason);
    }
    return 1;
}

CMD:kick(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] <= 0) return 1;
    new giveplayer_id, reason[128];
    if(sscanf(params, "us[128]", giveplayer_id, reason))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /kick [ID gracza] [powód]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }

        GivePenalty(giveplayer_id, playerid, -1, PENALTY_KICK, 0, reason);
        KickWithWait(giveplayer_id);
    }
    return 1;
}

CMD:aj(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] <= 0) return 1;
    new giveplayer_id, time, reason[128];
    if(sscanf(params, "uds[128]", giveplayer_id, time, reason))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /aj [ID gracza] [czas (min)] [powód]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }
        if(CharacterCache[giveplayer_id][pBW])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Ten gracz ma BW.", "Zamknij", "");
            return 1;
        }
        if(CharacterCache[giveplayer_id][pAJ])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Ten gracz jest ju¿ uwiêziony w AdminJail.", "Zamknij", "");
            return 1;
        }
        if(CharacterCache[playerid][pAdmin] == 1 && time > 60)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wiêkszej iloœci czasu kary (max. 60 minut).", "Zamknij", "");
            return 1;
        }
        if(CharacterCache[playerid][pAdmin] == 2 && time > 120)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wiêkszej iloœci czasu kary (max. 120 minut).", "Zamknij", "");
            return 1;
        }
        if(CharacterCache[playerid][pAdmin] == 3 && time > 240)
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do wiêkszej iloœci czasu kary (max. 240 minut).", "Zamknij", "");
            return 1;
        }

        if(GetPlayerState(giveplayer_id) == PLAYER_STATE_DRIVER)
        {
            new vehid = GetPlayerVehicleID(giveplayer_id);
            SetVehicleToRespawn(vehid);

            VehicleInfo[vehid][vEngineTogged] = false;
            VehicleInfo[vehid][vLocked] = true;

            ChangeVehicleEngineStatus(vehid, VehicleInfo[vehid][vEngineTogged]);
            SetVehicleLock(vehid, VehicleInfo[vehid][vLocked]);

            SaveVehicle(vehid, SAVE_VEH_COUNT);
        }

        CharacterCache[giveplayer_id][pAJ] = time * 60;

        SetPlayerPos(giveplayer_id, -207.9819, 1062.1416, 19.7422);
        SetPlayerInterior(giveplayer_id, 0);
        SetPlayerVirtualWorld(giveplayer_id, playerid + 1000);

        SendClientMessageFormat(giveplayer_id, 0xBA2818FF, "(INFO) Ostrzyma³eœ karê Admin Jail (%d minut) od %s, powód: %s", time, CharacterCache[playerid][pGlobalNick], reason);
        GivePenalty(giveplayer_id, playerid, (gettime() + (time * 60)), PENALTY_AJ, time, reason);
    }
    return 1;
}

CMD:unaj(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] < 4) return 1;
    new giveplayer_id, reason[128], string[128];
    if(sscanf(params, "us[128]", giveplayer_id, reason))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /unaj [ID gracza] [powód]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }
        if(!CharacterCache[giveplayer_id][pAJ])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Ten gracz nie jest uwiêziony w AdminJail.", "Zamknij", "");
            return 1;
        }

        CharacterCache[giveplayer_id][pAJ] = 0;
        SavePlayerStats(giveplayer_id, SAVE_PLAYER_BASIC);

        OnPlayerSpawn(giveplayer_id);

        SendClientMessageFormat(giveplayer_id, 0x74BD26FF, "(INFO) Kara Admin Jail zosta³a Tobie zdjêta przez %s, powód: %s", CharacterCache[playerid][pGlobalNick], reason);

        format(string, sizeof(string), "Gracz %s zosta³ zwolniony z kary AdminJail'a.", PlayerName2(giveplayer_id));
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");
    }
    return 1;
}

CMD:block(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] < 4) return 1;
    new giveplayer_id, reason[128];
    if(sscanf(params, "us[128]", giveplayer_id, reason))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /block [ID gracza] [powód]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }

        CharacterCache[giveplayer_id][pBlock] += BLOCK_CHAR;
		CharacterCache[playerid][pBlockPlayer] = giveplayer_id;
		
		format(CharacterCache[playerid][pBlockReason], 128, "%s", reason);

		ShowPlayerDialog(playerid, D_BLOCK_CHAR, DIALOG_STYLE_MSGBOX, " Zabójstwo gracza", "Czy chcesz aby postaæ zosta³a zablokowana z powodu zabójstwa?\nW takim wypadku po blokadzie pojawi¹ siê zw³oki gracza.", "Tak", "Nie");
    }
    return 1;
}

CMD:ban(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_BAN)) return 1;
    new giveplayer_id, reason[128];
    if(sscanf(params, "us[128]", giveplayer_id, reason))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ban [ID gracza] [powód]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }

        CharacterCache[giveplayer_id][pBlock] += BLOCK_BAN;
        AddBan(giveplayer_id);
        
        PenaltyBan ++;

        SendClientMessageFormat(giveplayer_id, 0xBA2818FF, "(INFO) Twoje konto zosta³o zbanowane przez %s, powód: %s", CharacterCache[playerid][pGlobalNick], reason);
        GivePenalty(giveplayer_id, playerid, -1, PENALTY_BAN, 0, reason);
        
        KickWithWait(giveplayer_id);
    }
    return 1;
}

CMD:gamescore(playerid, params[])
{
    if(!(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_GAMESCORE)) return 1;
    new giveplayer_id, score, reason[128];
    if(sscanf(params, "uds[128]", giveplayer_id, score, reason))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /gamescore [ID gracza] [iloœæ] [powód]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }

        CharacterCache[giveplayer_id][pGlobalScore] += score;
        SetPlayerScore(giveplayer_id, CharacterCache[giveplayer_id][pGlobalScore]);

        SendClientMessageFormat(giveplayer_id, 0x74BD26FF, "(INFO) Gratulacje! Otrzyma³eœ %d GameScore, dziêki %s, powód: %s", score, CharacterCache[playerid][pGlobalNick], reason);
        GivePenalty(giveplayer_id, playerid, -1, PENALTY_SCORE, score, reason);
    }
    return 1;
}

CMD:to(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] < 2) return 1;
    new giveplayer_id;
    if(sscanf(params, "i", giveplayer_id))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /to [ID gracza]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }

        new Float:Pos[3];
        GetPlayerPos(giveplayer_id, Pos[0], Pos[1], Pos[2]);

        SetPlayerPos(playerid, Pos[0], Pos[1] + 2.0, Pos[2]);
        SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(giveplayer_id));
        SetPlayerInterior(playerid, GetPlayerInterior(giveplayer_id));
    }
    return 1;
}

CMD:tm(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] < 2) return 1;
    new giveplayer_id;
    if(sscanf(params, "i", giveplayer_id))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /tm [ID gracza]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }

        new Float:Pos[3];
        GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

        SetPlayerPos(giveplayer_id, Pos[0], Pos[1] + 2.0, Pos[2]);
        SetPlayerVirtualWorld(giveplayer_id, GetPlayerVirtualWorld(playerid));
        SetPlayerInterior(giveplayer_id, GetPlayerInterior(playerid));
    }
    return 1;
}

CMD:ptp(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] < 2) return 1;
    new giveplayer_id, to_player;
    if(sscanf(params, "uu", giveplayer_id, to_player))
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zastosowanie komendy", "U¿yj: /ptp [ID gracza] [Do gracza]", "Zamknij", "");
        return 1;
    }
    else
    {
        if(!Logged[giveplayer_id])
        {
            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Wyst¹pi³ b³¹d", "Gracz o podanym ID nie jest zalogowany.", "Zamknij", "");
            return 1;
        }

        new Float:Pos[3];
        GetPlayerPos(to_player, Pos[0], Pos[1], Pos[2]);

        SetPlayerPos(giveplayer_id, Pos[0], Pos[1] + 2.0, Pos[2]);
        SetPlayerVirtualWorld(giveplayer_id, GetPlayerVirtualWorld(to_player));
        SetPlayerInterior(giveplayer_id, GetPlayerInterior(to_player));

        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Gracz zosta³ przeteleportowany pomyœlnie.", "Zamknij", "");
    }
    return 1;
}

CMD:rc(playerid, params[])
{
    if(CharacterCache[playerid][pAdmin] < 2) return 1;
    new playerid2;
    if(sscanf(params, "i", playerid2))
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
        {
            CharacterCache[playerid][pSpec] = true;

            TogglePlayerSpectating(playerid, 0);
            SetPlayerVirtualWorld(playerid, CharacterCache[playerid][pSpecVW]);
            SetPlayerInterior(playerid, CharacterCache[playerid][pSpecInt]);
            SetPlayerPos(playerid, CharacterCache[playerid][pSpecPos][0], CharacterCache[playerid][pSpecPos][1], CharacterCache[playerid][pSpecPos][2]);
            SetCameraBehindPlayer(playerid);
        }
    }
    else
    {
        GetPlayerPos(playerid, CharacterCache[playerid][pSpecPos][0], CharacterCache[playerid][pSpecPos][1], CharacterCache[playerid][pSpecPos][2]);
        CharacterCache[playerid][pSpecVW] = GetPlayerVirtualWorld(playerid);
        CharacterCache[playerid][pSpecInt] = GetPlayerInterior(playerid);

        CharacterCache[playerid][pSpec] = true;

        SetPlayerInterior(playerid, GetPlayerInterior(playerid2));
        SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(playerid2));

        if(GetPlayerState(playerid2) == PLAYER_STATE_DRIVER)
        {
            TogglePlayerSpectating(playerid, 1);
            PlayerSpectateVehicle(playerid, GetPlayerVehicleID(playerid2));
        }
        else
        {
            TogglePlayerSpectating(playerid, 1);
            PlayerSpectatePlayer(playerid, playerid2);
        }
    }
    return 1;
}
CMD:spec(playerid, params[]) return cmd_rc(playerid, params);

