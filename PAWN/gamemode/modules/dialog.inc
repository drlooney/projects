public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_INFO:
        {
            return 1;
        }
        case D_LOGIN_GLOBAL:
        {
            if(response)
            {
                new str[256];

                mysql_real_escape_string(inputtext, inputtext);
                format(str, sizeof(str), "SELECT c.player_uid FROM `ipb_members` m, `fc_characters` c WHERE m.`members_pass_hash` = MD5(CONCAT(MD5(m.members_pass_salt),'', MD5('%s'))) AND m.`member_id` = c.`global_uid` AND c.`name` = '%s' LIMIT 1", inputtext, PlayerName(playerid));
                mysql_check(); mysql_query(str);
                mysql_store_result();

                if(mysql_num_rows())
                {
                    OnPlayerLogin(playerid, mysql_fetch_int());
                    
                    mysql_free_result();
                }
                else
                {
                    new string[256];
                    format(string, sizeof(string), "{FFFFFF}Witamy na polskim serwerze roleplay {88CC54}"DEF_NAME"{FFFFFF}.\n{FFFFFF}Zalogowaæ siê mo¿esz przy u¿yciu nazwy swojej postaci.");
    				format(string, sizeof(string), "%s\n\n{FFFFFF}Wpisz has³o, aby do³¹czyæ do najbardziej oczekiwanego projektu RolePlay.", string);

                    ShowPlayerDialog(playerid, D_LOGIN_GLOBAL, DIALOG_STYLE_PASSWORD, " Logowanie do platformy", string, "Zaloguj", "Zamknij");
                    
                    mysql_free_result();
                }
            }
            else
            {
                KickWithWait(playerid);
                return 1;
            }
        }
        case D_MANAGE_VEH:
        {
            if(response)
            {
                new vehid = GetPlayerVehicleID(playerid);
                switch(listitem)
                {
                    case 0:
                    {
                        if(GetVehicleBonnetStatus(vehid) == 1)
                        {
                            ChangeVehicleBonnetStatus(vehid, false);
                            GameTextForPlayer(playerid, "~w~Maska ~r~zamknieta", 5000, 3);
                        }
                        else
                        {
                            ChangeVehicleBonnetStatus(vehid, true);
                            GameTextForPlayer(playerid, "~w~Maska ~g~otwarta", 5000, 3);
                        }
                    }
                    case 1:
                    {
                        if(GetVehicleBootStatus(vehid) == 1)
                        {
                            ChangeVehicleBootStatus(vehid, false);
                            GameTextForPlayer(playerid, "~w~Bagaznik ~r~zamkniety", 5000, 3);
                        }
                        else
                        {
                            ChangeVehicleBootStatus(vehid, true);
                            GameTextForPlayer(playerid, "~w~Bagaznik ~g~otwarty", 5000, 3);
                        }
                    }
                    case 2:
                    {
                        if(GetVehicleLightsStatus(vehid) == 1)
                        {
                            ChangeVehicleLightsStatus(vehid, false);
                            GameTextForPlayer(playerid, "~w~Swiatla ~r~zgaszone", 5000, 3);
                        }
                        else
                        {
                            ChangeVehicleLightsStatus(vehid, true);
                            GameTextForPlayer(playerid, "~w~Swiatla ~g~zapalone", 5000, 3);
                        }
                    }
                    case 3:
                    {
                        return cmd_pojazd(playerid, " ");
                    }
                    case 4:
                    {
                        return cmd_pojazd(playerid, "info");
                    }
                    case 5:
                    {
                        return cmd_przedmiot(playerid, "szukaj");
                    }
                    case 6:
                    {
                        return cmd_pojazd(playerid, "przepisz");
                    }
                    case 7:
                    {
                        return cmd_pojazd(playerid, "tuning");
                    }
                }
            }
            else
            {
                return 1;
            }
        }
        case D_LIST_PLAYER_CARS:
        {
            if(response)
            {
                new string[256], uid = strval(inputtext);

                if(!VehicleInfo[uid][vGameID])
                {
                    if(IsPlayerPremium(playerid))
                    {
	                    if(CharacterCache[playerid][pCarSpawned] >= 5)
						{
						    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie mo¿esz zespawnowaa wiêcej pojazdów ni¿ 5.\nOdspawnuj jeden z pojazdów, aby móc zespawnowaæ inny.", "Zamknij", "");
						    return 1;
						}
                    }
                    else
                    {
	                    if(CharacterCache[playerid][pCarSpawned] >= 3)
						{
						    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie mo¿esz zespawnowaa wiêcej pojazdów ni¿ 3.\nOdspawnuj jeden z pojazdów, aby móc zespawnowaæ inny.", "Zamknij", "");
						    return 1;
						}
					}

                    LoadVehicle(uid);
                    CharacterCache[playerid][pCarSpawned] ++;

                    format(string, sizeof(string), "Pojazd %s (UID: %d) zosta³ zespawnowany pomyœlnie.", GetVehicleModelName(VehicleInfo[uid][vModel]), VehicleInfo[uid][vUID]);
                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
                }
                else
                {
                    UnspawnVehicle(uid);
                    CharacterCache[playerid][pCarSpawned] --;

                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pojazd zosta³ odspawnowany pomyœlnie.", "Zamknij", "");
                }
            }
            else
            {
                return 1;
            }
        }
        case D_CREATE_GROUP_NAME:
        {
            if(response)
            {
                SetPVarString(playerid, "CreateGroupName", inputtext);

                ShowPlayerDialog(playerid, D_CREATE_GROUP_TAG, DIALOG_STYLE_INPUT, " Tworzenie nowej grupy", "WprowadŸ nazwê tagu dla nowo tworzonej grupy:", "Dalej", "Zamknij");
            }
            else
            {
                return 1;
            }
        }
        case D_CREATE_GROUP_TAG:
        {
            if(response)
            {
                SetPVarString(playerid, "CreateGroupTag", inputtext);
                new string[1024];

                ForeachEx(i, COUNT_GROUP + 1)
                {
                    format(string, sizeof(string), "%s\n%d\t%s", string, i, GroupInfo[i][gName]);
                }

                ShowPlayerDialog(playerid, D_CREATE_GROUP_KIND, DIALOG_STYLE_LIST, " Tworzenie nowej grupy", string, "Dalej", "Zamknij");
            }
            else
            {
                return 1;
            }
        }
        case D_CREATE_GROUP_KIND:
        {
            if(response)
            {
                new string[256];
                new kind = strval(inputtext);

                new name[32];
                GetPVarString(playerid, "CreateGroupName", name, sizeof(name));

                new tag[12];
                GetPVarString(playerid, "CreateGroupTag", tag, sizeof(tag));

                new uid = AddGroup(name, kind, tag, CharacterCache[playerid][pUID]);
                
                InfoAdminFormat(playerid, "stworzyl nowa grupe ~y~~h~~h~%s (UID:%d)~w~~h~.", GroupData[uid][Desc], GroupData[uid][UID]);

                format(string, sizeof(string), "Gratulacje, grupa (UID: %d) zosta³a pomyœlnie stworzona!", uid);
                format(string, sizeof(string), "%s\n\nNazwa grupy:\t\t\t%s", string, name);
                format(string, sizeof(string), "%s\nTag grupy:\t\t\t%s", string, tag);
                format(string, sizeof(string), "%s\nTyp grupy:\t\t\t%s", string, GroupInfo[kind][gName]);
                format(string, sizeof(string), "%s\n\nAby nadaæ lidera graczowi u¿yj komendy '/agrupa lider [id grupy] [id gracza]'.", string);

                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
            }
            else
            {
                return 1;
            }
        }
        case D_DELETE_GROUP:
        {
            if(response)
            {
                new groupid = GetPVarInt(playerid, "DeleteGroup");

                new string[128];
                format(string, sizeof(string), "Grupa %s (UID: %d) zosta³a pomyœlnie usuniêta.", GroupData[groupid][UID], GroupData[groupid][Desc]);

                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
                
                InfoAdminFormat(playerid, "usunal grupe ~y~~h~~h~%s (UID:%d)~w~~h~.", GroupData[groupid][Desc], GroupData[groupid][UID]);

                new query[128], sql[128];
                format(query, sizeof(query), "DELETE FROM `fc_member_groups` WHERE `group_id` = '%d'", GroupData[groupid][UID]);
                mysql_check(); mysql_query(query);

                format(sql, sizeof(sql), "DELETE FROM `fc_member_groups` WHERE `group_id` = '%d'", GroupData[groupid][UID]);
                mysql_check(); mysql_query(sql);

                SetPVarInt(playerid, "DeleteGroup", 0);
                DeleteGroup(groupid);
            }
            else
            {
                return 1;
            }
        }
        case D_CHECK_LEADER:
        {
            if(response)
            {
                new groupid = GetPVarInt(playerid, "CheckLeaderGroupID"),
                    giveplayer_id = GetPVarInt(playerid, "CheckLeaderPlayerID");

                AddMember(giveplayer_id, groupid, true, true);

                new string[256];
                format(string, sizeof(string), "Gratulacje, nada³eœ nowego g³ównego lidera graczowi.");
                format(string, sizeof(string), "%s\n\nIdentyfikator grupy:\t\t%d", string, groupid);
                format(string, sizeof(string), "%s\nNazwa grupy:\t\t\t%s", string, GroupData[groupid][Desc]);
                format(string, sizeof(string), "%s\nNazwa postaci:\t\t\t%s", string, PlayerName2(giveplayer_id));
                format(string, sizeof(string), "%s\nG³ówny lider:\t\t\tTak", string);
                format(string, sizeof(string), "%s\n\nUprawnienia zosta³y odpowiednio przypisane.", string);

                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

                SendClientMessageFormat(giveplayer_id, SZARY, "(INFO) %s nada³ Tobie g³ównego lidera grupy %s (UID: %d). Mi³ej gry!", CharacterCache[playerid][pGlobalNick], GroupData[groupid][Desc], groupid);
            }
            else
            {
                new groupid = GetPVarInt(playerid, "CheckLeaderGroupID"),
                    giveplayer_id = GetPVarInt(playerid, "CheckLeaderPlayerID");

                AddMember(giveplayer_id, groupid, true, false);

                new string[256];
                format(string, sizeof(string), "Gratulacje, nada³eœ nowego lidera graczowi.");
                format(string, sizeof(string), "%s\n\nIdentyfikator grupy:\t\t%d", string, groupid);
                format(string, sizeof(string), "%s\nNazwa grupy:\t\t\t%s", string, GroupData[groupid][Desc]);
                format(string, sizeof(string), "%s\nNazwa postaci:\t\t\t%s", string, PlayerName2(giveplayer_id));
                format(string, sizeof(string), "%s\nG³ówny lider:\t\t\tNie", string);
                format(string, sizeof(string), "%s\n\nUprawnienia zosta³y odpowiednio przypisane.", string);

                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

                SendClientMessageFormat(giveplayer_id, SZARY, "(INFO) %s nada³ Tobie lidera grupy %s (UID: %d). Mi³ej gry!", CharacterCache[playerid][pGlobalNick], GroupData[groupid][Desc], groupid);
            }
        }
        case D_LIST_SPAWNED_CARS:
        {
            if(response)
            {
                if(CharacterCache[playerid][pPackage])
				{
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Podczas dostarczania paczki nie mo¿esz namierzyæ pojazdu.", "Zamknij", "");
					return 1;
				}

                new vehid = strval(inputtext), Float:x, Float:y, Float:z, string[128];
                GetVehiclePos(VehicleInfo[vehid][vGameID], x, y, z);

                SetPlayerCheckpoint(playerid, x, y, z, 5.0);
                Checkpoint[playerid] = 1;

                format(string, sizeof(string), "Namierzony zosta³ pojazd %s.\nAby anulowaæ namierzanie, wpisz komendê /v namierz.", GetVehicleModelName(VehicleInfo[vehid][vModel]));
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
            }
            else
            {
                return 1;
            }
        }
        case D_VEHICLE_GROUP_OPTIONS:
        {
            if(response)
            {
                new veh = strval(inputtext);
                SetPVarInt(playerid, "VehicleID", veh);

                ShowPlayerDialog(playerid, D_VEHICLE_GROUP_OPTIONS_SELECT, DIALOG_STYLE_LIST, " Informacja", "1. Namierz pojazd\n2. (Un)spawn pojazdu", "Wybierz", "Zamknij");
            }
            else
            {
                return 1;
            }
        }
        case D_VEHICLE_GROUP_OPTIONS_SELECT:
        {
            if(response)
            {
                new vehid = GetPVarInt(playerid, "VehicleID");
                if(listitem == 0)
                {
                    if(Checkpoint[playerid])
                    {
                        DisablePlayerCheckpoint(playerid);
                        Checkpoint[playerid] = 0;

                        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Namierzanie zosta³o wy³¹czone.", "Zamknij", "");
                    }
                    else
                    {
                        if(CharacterCache[playerid][pPackage])
						{
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Podczas dostarczania paczki nie mo¿esz namierzyæ pojazdu.", "Zamknij", "");
							return 1;
						}

                        new Float:x, Float:y, Float:z;
                        GetVehiclePos(VehicleInfo[vehid][vGameID], x, y, z);

                        SetPlayerCheckpoint(playerid, x, y, z, 5.0);
                        Checkpoint[playerid] = 1;
                    }
                }
                else if(listitem == 1)
                {
                    new string[256];
                    if(!VehicleInfo[vehid][vGameID])
                    {
                        LoadVehicle(vehid);

                        format(string, sizeof(string), "Pojazd %s (UID: %d) zosta³ zespawnowany pomyœlnie.", GetVehicleModelName(VehicleInfo[vehid][vModel]), vehid);
                        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
                    }
                    else
                    {
                        UnspawnVehicle(vehid);

                        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pojazd zosta³ odspawnowany pomyœlnie.", "Zamknij", "");
                    }
                }
            }
            else
            {
                return 1;
            }
        }
        case D_ITEM:
        {
            if(response)
            {
                new item = strval(inputtext);
                new itemid = GetItemID(item);
                
                if(!item)
                {
                    return 0;
                }
                if(!ItemInfo[itemid][iUID])
                {
                    LoadItem(item);
                }
                
                OnPlayerUseItem(playerid, itemid);
            }
            else
            {
                new item = strval(inputtext);
                new itemid = GetItemID(item);
                new title[128];
                
                if(!item)
                {
                    return 0;
                }
                if(!ItemInfo[itemid][iUID])
                {
                    LoadItem(item);
                }

                SetPVarInt(playerid, "ItemDialog", itemid);

                format(title, sizeof(title), "Przedmiot - %s (UID: %d)", ItemInfo[itemid][iName], ItemInfo[itemid][iUID]);
                ShowPlayerDialog(playerid, D_ITEM_OPTION, DIALOG_STYLE_LIST, title, "1. Od³ó¿ w pobli¿u\n2. Informacje ogólne\n3. Schowaj do schowka", "Wybierz", "Zamknij");
            }
        }
        case D_ITEM_OPTION:
        {
            if(response)
            {
                new itemid = GetPVarInt(playerid, "ItemDialog");
                if(listitem == 0)
                {
                    OnPlayerDropItem(playerid, itemid);
                }
                else if(listitem == 1)
                {
                    if(!IsOwnerItem(playerid, itemid)) cmd_przedmiot(playerid, " ");

                    new string[1024], title[64];
                    format(title, sizeof(title), " Przedmiot %s (UID:%d)", ItemInfo[itemid][iName], ItemInfo[itemid][iUID]);

                    format(string, sizeof(string), "%s\nIdentyfikator:\t\t%d", string, ItemInfo[itemid][iUID]);
                    format(string, sizeof(string), "%s\nTyp:\t\t\t%s", string, ItemTypeInfo[ItemInfo[itemid][iType]][iTypeName]);
                    format(string, sizeof(string), "%s\nNazwa:\t\t\t%s", string, ItemInfo[itemid][iName]);

                    format(string, sizeof(string), "%s\n\nWartoœæ 1:\t\t%d", string, ItemInfo[itemid][iValue1]);
                    format(string, sizeof(string), "%s\nWartoœæ 2:\t\t%d", string, ItemInfo[itemid][iValue2]);

                    format(string, sizeof(string), "%s\n\nTyp w³aœciciela:\t\tGracz", string);
                    
                    format(string, sizeof(string), "%s\nFlagi:", string);
                    
                    if(ItemInfo[itemid][iFlags] & ITEM_FLAG_PARALIZE) format(string, sizeof(string), "%s\n\t- Paralizator", string);
                    if(ItemInfo[itemid][iFlags] & ITEM_FLAG_NODMG) format(string, sizeof(string), "%s\n\t- Brak obra¿eñ", string);

                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, title, string, "Zamknij", "");
                }
                else if(listitem == 2)
                {
                    // Chowanie do schowka (DRZWI)
                    return 1;
                }
            }
            else
            {
                return 1;
            }
        }
        case D_RAISE_ITEM:
        {
            if(response)
            {
                new itemuid = strval(inputtext);
                OnPlayerRaiseItem(playerid, itemuid);
            }
            else
            {
                return 1;
            }
        }
        case D_CHANGE_VEHICLE:
        {
            if(response)
            {
                new string[256],
                    vehicleid = GetPVarInt(playerid, "VehicleChangeID"),
                    group_id = strval(inputtext);

                if(!GroupData[group_id][UID])
                {
                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrana grupa jest nieprawid³owa.", "Zamknij", "");
                    return 1;
                }

                VehicleInfo[vehicleid][vOwnerType]  = OWNER_GROUP;
                VehicleInfo[vehicleid][vOwner]      = GroupData[group_id][UID];

                SaveVehicle(vehicleid, SAVE_VEH_THINGS);

                format(string, sizeof(string), "Pojazd %s (UID: %d) zosta³ przepisany na grupê %s (UID: %d).", GetVehicleModelName(VehicleInfo[vehicleid][vModel]), VehicleInfo[vehicleid][vUID], GroupData[group_id][Desc], GroupData[group_id][UID]);
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
            }
            else
            {
                return 1;
            }
        }
        case D_SLOT_VEHICLE:
        {
            if(response)
            {
                if(listitem == 2)
                {
                    new list_subgroup[512],
                        vehicleid = GetPVarInt(playerid, "VehicleChangeID");
                    
                    ForeachEx(i, MAX_SUBGROUPS)
	 				{
                        if(SubData[i][sGroup] == VehicleInfo[vehicleid][vOwner])
                        {
                            format(list_subgroup, sizeof(list_subgroup), "%s\n%d\t%s", list_subgroup, SubData[i][sUID], SubData[i][sDesc]);
                        }
                    }
                    
                    if(strlen(list_subgroup) != 0) ShowPlayerDialog(playerid, D_USE_SUBGROUP, DIALOG_STYLE_LIST, " Informacja", list_subgroup, "Przepisz", "Zamknij");
                    else Infobox(playerid, 5, "W grupie nie znajduje sie zadna subgrupa.");
                }
                else
                {
	                new string[256],
	                    vehicleid = GetPVarInt(playerid, "VehicleChangeID");

	                VehicleInfo[vehicleid][vSlot] = listitem;

	                SaveVehicle(vehicleid, SAVE_VEH_THINGS);

	                format(string, sizeof(string), "Pojazd %s (UID: %d) zmieni³ swój status.", GetVehicleModelName(VehicleInfo[vehicleid][vModel]), VehicleInfo[vehicleid][vUID]);
	                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
                }
            }
            else
            {
                return 1;
            }
        }
        case D_FLAG_GROUP:
        {
            if(response)
            {
                new text[256], flag_id, group_id = CharacterCache[playerid][pGroupFlag];
                format(text, sizeof(text), "%s", inputtext);

                if(listitem == 0) flag_id = FLAG_DEPARTMENT;
                else if(listitem == 1) flag_id = FLAG_MEGAPHONE;
                else if(listitem == 2) flag_id = FLAG_NICK;
                else if(listitem == 3) flag_id = FLAG_OUT;
                else if(listitem == 4) flag_id = FLAG_CASH;
                else if(listitem == 5) flag_id = FLAG_DB;
                else if(listitem == 6) flag_id = FLAG_BLOCK;
                else if(listitem == 7) flag_id = FLAG_DETENTION;
                else if(listitem == 8) flag_id = FLAG_ITEM;
                else if(listitem == 9) flag_id = FLAG_CALL_911;
                else if(listitem == 10) flag_id = FLAG_REPORTS;
                else if(listitem == 11) flag_id = FLAG_GPS;
                else if(listitem == 12) flag_id = FLAG_ALARM;
                else flag_id = 0;

                if(!(GroupData[group_id][Flags] & flag_id)) GroupData[group_id][Flags] += flag_id;
                else GroupData[group_id][Flags] -= flag_id;

                SaveGroup(group_id);

                new cmd_string[12];
                format(cmd_string, sizeof(cmd_string), "flagi %d", CharacterCache[playerid][pGroupFlag]);
                cmd_ag(playerid, cmd_string);
            }
            else
            {
	        	return 1;
          	}
		}
        case D_ITEM_NAME:
        {
            if(response)
            {
                new name[32],
                    string[1024];
                    
				if(strlen(inputtext) == 0)
				{
					ShowPlayerDialog(playerid, D_ITEM_NAME, DIALOG_STYLE_INPUT, " Informacja", "Podaj nazwê nowo tworzonego przedmiotu:", "Wybierz", "Zamknij");
					return 1;
				}
				
                format(name, sizeof(name), "%s", inputtext);
                
                EscapePL(name);
                SetPVarString(playerid, "ItemCreateName", name);

                ForeachEx(i, (TYPE_COUNT + 1))
                {
                    format(string, sizeof(string), "%s\n%s", string, ItemTypeInfo[i][iTypeName]);
                }

                ShowPlayerDialog(playerid, D_ITEM_TYPE, DIALOG_STYLE_LIST, " Wybierz typ przedmiotu", string, "Wybierz", "Zamknij");
            }
            else
            {
                return 1;
            }
        }
        case D_ITEM_TYPE:
        {
            if(response)
            {
                SetPVarInt(playerid, "ItemCreateKind", listitem);

                ShowPlayerDialog(playerid, D_ITEM_VALUE1, DIALOG_STYLE_INPUT, " Informacja", "WprowadŸ wartoœæ (1) przedmiotu", "Dalej", "Zamknij");
            }
            else
            {
                return 1;
            }
        }
        case D_ITEM_VALUE1:
        {
            if(response)
            {
                new value1 = strval(inputtext);
                SetPVarInt(playerid, "ItemCreateValue1", value1);

                ShowPlayerDialog(playerid, D_ITEM_VALUE2, DIALOG_STYLE_INPUT, " Informacja", "WprowadŸ wartoœæ (2) przedmiotu", "Dalej", "Zamknij");
            }
            else
            {
                return 1;
            }
        }
        case D_ITEM_VALUE2:
        {
            if(response)
            {
                new value2  = strval(inputtext);
                new value1  = GetPVarInt(playerid, "ItemCreateValue1");
                new kind    = GetPVarInt(playerid, "ItemCreateKind");
                new name[32];
                new string[256];

                GetPVarString(playerid, "ItemCreateName", name, 32);

                new item_uid = CreatePlayerItem(playerid, name, kind, value1, value2, 1);

                format(string, sizeof(string), "Przedmiot %s (UID: %d) zosta³ stworzony pomyœlnie.\n\nTyp przedmiotu:\t%s\nWartoœæ 1:\t\t\t%d\nWartoœæ 2:\t\t\t%d\n\nPrzedmiot znajdziesz w swoim ekwipunku.", name, item_uid, ItemTypeInfo[kind][iTypeName], value1, value2);
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", string, "Zamknij", "");
            }
            else
            {
                return 1;
            }
        }
        case D_TOG:
        {
            if(response)
            {
                switch(listitem)
                {
                    case 1: // Wy³¹czone wiadomoœci PW
                    {
                        if(CharacterCache[playerid][pTog] & TOG_PW) CharacterCache[playerid][pTog] -= TOG_PW;
                        else CharacterCache[playerid][pTog] += TOG_PW;
                    }
                    case 2: // Ukryty textdraw audio
                    {
                        if(CharacterCache[playerid][pTog] & TOG_AUDIO) CharacterCache[playerid][pTog] -= TOG_AUDIO;
                        else
                        {
                            CharacterCache[playerid][pTog] += TOG_AUDIO;
                            PlayerTextDrawHide(playerid, TextDrawAudioError[playerid]);
                        }
                    }
                    case 3: // Ukryty textdraw nazwy serwera
                    {
                        if(CharacterCache[playerid][pTog] & TOG_NAME)
                        {
                            CharacterCache[playerid][pTog] -= TOG_NAME;
                            PlayerTextDrawShow(playerid, IRPName[playerid]);
                        }
                        else
                        {
                            CharacterCache[playerid][pTog] += TOG_NAME;
                            PlayerTextDrawHide(playerid, IRPName[playerid]);
                        }
                    }
                    case 4:
                    {
                        if(CharacterCache[playerid][pTog] & TOG_FM)
                        {
                            CharacterCache[playerid][pTog] -= TOG_FM;
                            PlayerTextDrawShow(playerid, RadioFM[playerid]);
                        }
                        else
                        {
                            CharacterCache[playerid][pTog] += TOG_FM;
                            PlayerTextDrawHide(playerid, RadioFM[playerid]);
                        }
                    }
                    case 5: // Blokada czatów OOC
                    {
                        if(CharacterCache[playerid][pTog] & TOG_OOC) CharacterCache[playerid][pTog] -= TOG_OOC;
                        else CharacterCache[playerid][pTog] += TOG_OOC;
                    }
                    case 7: // Edytor klawiszowy
                    {
                        if(CharacterCache[playerid][pEditor] == OPTION_EDITOR_KEY) CharacterCache[playerid][pEditor] = OPTION_EDITOR_MACHINE;
                        else CharacterCache[playerid][pEditor] = OPTION_EDITOR_KEY;
                    }
                    case 8: // Freeze w drzwiach
                    {
                        if(CharacterCache[playerid][pOption] & OPTION_FREEZE) CharacterCache[playerid][pOption] -= OPTION_FREEZE;
                        else CharacterCache[playerid][pOption] += OPTION_FREEZE;
                    }
                    case 9: // Animacja mówienia
                    {
                        if(CharacterCache[playerid][pOption] & OPTION_SAY) CharacterCache[playerid][pOption] -= OPTION_SAY;
                        else CharacterCache[playerid][pOption] += OPTION_SAY;
                    }
                    case 10: // Animacja krzyku
                    {
                        if(CharacterCache[playerid][pOption] & OPTION_KRZYK) CharacterCache[playerid][pOption] -= OPTION_KRZYK;
                        else CharacterCache[playerid][pOption] += OPTION_KRZYK;
                    }
                    case 11: // Panoramiczny ekran
                    {
                        if(CharacterCache[playerid][pOption] & OPTION_PANORAMIC)
						{
							CharacterCache[playerid][pOption] -= OPTION_PANORAMIC;
							
							PlayerTextDrawHide(playerid, Panorama1[playerid]);
	    					PlayerTextDrawHide(playerid, Panorama2[playerid]);
						}
                        else
						{
							CharacterCache[playerid][pOption] += OPTION_PANORAMIC;
							
	                        PlayerTextDrawShow(playerid, Panorama1[playerid]);
	    					PlayerTextDrawShow(playerid, Panorama2[playerid]);
						}
                    }
                    case 12: // Token administracyjny
                    {
                        if(CharacterCache[playerid][pOption] & OPTION_TOKEN)
                        {
                            CharacterCache[playerid][pOption] -= OPTION_TOKEN;
                        }
                        else
                        {
                            CharacterCache[playerid][pOption] += OPTION_TOKEN;
                        }
                    }
                }

                SavePlayerStats(playerid, SAVE_PLAYER_SETTING);
                cmd_tog(playerid, " ");
            }
            else
            {
                return 1;
            }
        }
        case D_AREA_1:
        {
            if(response)
            {
                new Float:Pos[3];
                GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

                CharacterCache[playerid][pAreaPos1] = Pos[0];
                CharacterCache[playerid][pAreaPos2] = Pos[1];

                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pierwsze pozycje strefy zosta³y pomyœlnie pobrane.\nUstaw siê na drugiej pozycji i u¿yj komendy '/as stwórz'.", "Zamknij", "");
            }
            else
            {
                return 1;
            }
        }
		case D_MAGAZINE:
		{
		    if(response)
		    {
		        new itemid = strval(inputtext);
		        if(!itemid)
		        {
		        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Formularz pobrany podczas pobierania danych zosta³ Ÿle pobrany.\nSkontaktuj siê z administratorem serwisu.", "Zamknij", "");
		            return 1;
		        }
		        
          		new data[32], query[256], string[128], uid, name[32], value1, value2, value, kind, cash;

			    format(query, sizeof(query), "SELECT * FROM `fc_magazine` WHERE uid = '%d' LIMIT 1", itemid);
			    mysql_check(); mysql_query(query);

			    mysql_store_result();
			    if(mysql_fetch_row_format(data, "|"))
			    {
			        sscanf(data, "p<|>ds[32]ddddd",
			        uid,
					name,
					value1,
					value2,
					value,
					kind,
					cash);
			    }

			    mysql_free_result();
			    
			    if(value < 1)
			    {
			    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "W magazynie nie znajduje siê odpowiednia iloœæ broni.", "Zamknij", "");
		            return 1;
			    }
			    if(CharacterCache[playerid][pCash] != 0 && CharacterCache[playerid][pCash] < cash)
			    {
			    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz odpowiedniej kwoty gotówki aby zakupiæ dan¹ broñ.", "Zamknij", "");
		            return 1;
			    }
			    
			    GivePlayerCash(playerid, -cash);
			    CreatePlayerItem(playerid, name, kind, value1, value2, 1);
			    
			    format(query, sizeof(query), "UPDATE `fc_magazine` SET `value` = `value` - 1 WHERE uid = '%d' LIMIT 1", itemid);
			    mysql_check(); mysql_query(query);
			    
			    format(string, sizeof(string), "Pomyœlnie zakupi³eœ broñ %s (ID: %d) w magazynie za cenê $%d dolarów.", name, uid, cash);
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		    }
		    else
			{
		        return 1;
		    }
		}
		case D_OFFER_ITEMS:
		{
		    if(response)
		    {
		        new item_uid = strval(inputtext);
		        new found = 0, string[512];
		        
				SetPVarInt(playerid, "OfferItemUID", item_uid);
				ForeachEx(i, MAX_PLAYERS)
				{
				    if(PlayerToPlayer(15.0, playerid, i) && i != playerid)
				    {
						format(string, sizeof(string), "%s\n%d\t%s", string, i, PlayerName2(i));
						found++;
					}
				}
				
				if(strlen(string) != 0) ShowPlayerDialog(playerid, D_OFFER_ITEMS_PLAYERS, DIALOG_STYLE_LIST, "Oferta przedmiotu", string, "Oferuj", "Anuluj");
				else Infobox(playerid, 5, "Nikt nie znajduje sie kolo Ciebie.");
			}
			else
			{
			    return 1;
			}
		}
		case D_OFFER_ITEMS_PLAYERS:
		{
		    if(response)
		    {
		        new customer = strval(inputtext);
		        new cash = GetPVarInt(playerid, "OfferItemCash");
		        new item_uid = GetPVarInt(playerid, "OfferItemUID");
		        
		        if(Logged[customer])
		        {
		            Oferta(playerid, customer, OFFER_ITEM, cash, item_uid);
		        }
		        else return Infobox(playerid, 5, "Wybrany gracz nie jest zalogowany.");
			}
			else
			{
			    return 1;
			}
		}
		case D_OFFER_VEHICLES:
		{
		    if(response)
		    {
		        new veh_uid = strval(inputtext);
		        new found = 0, string[512];
		        
				SetPVarInt(playerid, "OfferVehicleUID", veh_uid);
				ForeachEx(i, MAX_PLAYERS)
				{
				    if(PlayerToPlayer(15.0, playerid, i) && i != playerid)
				    {
						format(string, sizeof(string), "%s\n%d\t%s", string, i, PlayerName2(i));
						found++;
					}
				}
				
				if(strlen(string) != 0) ShowPlayerDialog(playerid, D_OFFER_VEHICLES_PLAYERS, DIALOG_STYLE_LIST, "Oferta pojazdu", string, "Oferuj", "Zamknij");
				else Infobox(playerid, 5, "Nikt nie znajduje sie kolo Ciebie.");
			}
			else
			{
				return 1;
			}
		}
		case D_OFFER_VEHICLES_PLAYERS:
		{
		    if(response)
		    {
		        new customer = strval(inputtext);
		        new cena = GetPVarInt(playerid, "OfferVehicleCash");
		        new veh_uid = GetPVarInt(playerid, "OfferVehicleUID");
		        
		        if(Logged[customer])
		        {
		            Oferta(playerid, customer, OFFER_VEHICLE, cena, veh_uid);
		        }
		        else return Infobox(playerid, 5, "Wybrany gracz nie jest zalogowany.");
			}
			else
			{
			    return 1;
			}
		}
		case D_DOOR_OPTIONS:
		{
		    if(response)
		    {
				new doorid = PlayerDoor[playerid];
				
		        switch(listitem)
		        {
		            case 0: // Zmiana nazwy budynku
		            {
		                ShowPlayerDialog(playerid, D_DOOR_NAME, DIALOG_STYLE_INPUT, " Zmiana nazwy drzwi", "WprowadŸ w poni¿sze pole now¹ nazwê drzwi.\nPamiêtaj, ¿e nie mo¿esz u¿ywaæ funkcji formatowania tekstu.", "Zmieñ", "Zamknij");
		            }
					case 1:
					{
					    ShowPlayerDialog(playerid, D_DOOR_PRICE, DIALOG_STYLE_LIST, " Op³ata za wejœcie do lokalu", "0\t\tDarmowe\n5\t\tOp³ata wejœcia do lokalu - $5\n10\t\tOp³ata wejœcia do lokalu - $10\n25\t\tOp³ata wejœcia do lokalu - $25\n50\t\tOp³ata wejœcia do lokalu - $50", "Wybierz", "Zamknij");
					}
					case 2:
					{
					    LoadObjectInDoor(DoorInfo[doorid][dUID]);

						ForeachEx(i, MAX_PLAYERS)
						{
						    if(PlayerDoor[i] == doorid)
						    {
						        OnPlayerExitDoor(playerid, doorid, 0, DoorInfo[doorid][dEnVw]);
						        Infobox(i, 5, "Obiekty w interiorze zostaly ~g~~h~pomyslnie~w~~h~ przeladowane.");
						    }
						}
					}
					case 3:
					{
						if(!doorid)
				        {
				            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz sie w budynku.", "Zamknij", "");
				            return 1;
				        }
					    if(!strlen(DoorInfo[doorid][dAudioURL]))
					    {
					    	ShowPlayerDialog(playerid, D_CHANGE_DOOR_AUDIO, DIALOG_STYLE_INPUT, "Opcje drzwi » Muzyka spoza gry", "WprowadŸ link do muzyki lub radia, które us³ysz¹ wszyscy przebywaj¹cy w tym budynku.\nLink nie mo¿e przekroczyæ 128 znaków.\n\nUpewnij siê, ¿e link jest poprawny w innym wypadku muzyka mo¿e nie byæ s³yszalna.", "Graj", "Anuluj");
						}
						else
						{
					        ForeachEx(i, MAX_PLAYERS)
					        {
	            				if(PlayerDoor[i] == doorid)
	                			{
	                                StopAudioStreamForPlayer(playerid);
								}
							}

						    strmid(DoorInfo[doorid][dAudioURL], "", 0, 0);
						    SaveDoors(doorid);

						    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Muzyka spoza gry dla tego budynku zosta3a wy³¹czona.\nAby w³¹czyæ muzykê spoza gry, wybierz tê opcjê ponownie.", "Zamknij", "");
						}
					}
					case 4:
					{
						if(!DoorInfo[doorid][dGarage])
						{
						    DoorInfo[doorid][dGarage] = true;
						    SaveDoors(doorid);

							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Opcje drzwi » Mo¿liwoœæ przejazdu", "Mo¿liwoœæ przejazdu samochodem przez drzwi zosta³a w³¹czona.\n\nOd tej pory bedziesz móg³ wjechaæ dowolnym pojazdem do budynku.\nAby wjechaæ pojazdem do budynku skorzystaj z komendy /przejazd.", "Zamknij", "");
						}
						else
						{
		    				DoorInfo[doorid][dGarage] = false;
		    				SaveDoors(doorid);

							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Opcje drzwi » Mo¿liwoœæ przejazdu", "Mo¿liwoœæ przejazdu samochodem przez drzwi zosta³a wy³¹czona.", "Zamkij", "");
						}
					}
					case 5:
					{
						GetPlayerPos(playerid, DoorInfo[doorid][dExitX], DoorInfo[doorid][dExitY], DoorInfo[doorid][dExitZ]);
				  		GetPlayerFacingAngle(playerid, DoorInfo[doorid][dExitAng]);
				  		
				  		DoorInfo[doorid][dExitInt] = GetPlayerInterior(playerid);
				  		DoorInfo[doorid][dExitVw] = GetPlayerVirtualWorld(playerid);
				  		
				  		SaveDoors(doorid);

				  		new title[128];
				  		format(title, sizeof(title), "Pozycja wejœcia do drzwi %s (UID: %d) zosta³a pomyœlnie ustawiona.", DoorInfo[doorid][dName], DoorInfo[doorid][dUID]);
				  		
				  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Opcje » Wejœcie do drzwi", title, "Zamknij", "");
					}
					case 6:
					{
					    cmd_drzwi(playerid, "schowek");
					}
					case 7:
					{
					    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Opcja czasowo wy³¹czona.", "Zamknij", "");
					}
					case 8:
					{
						ForeachEx(i, MAX_OBJECTS)
					    {
					        if(ObjectInfo[i][oVW] == DoorInfo[doorid][dExitVw])
					        {
							    DeleteObject(i);
							}
					    }
					    
					    Streamer_Update(playerid);
					    Infobox(playerid, 5, "Wszystkie obiekty zostaly ~b~~h~pomyslnie~w~~h~ usuniete.");
					}
		        }
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_DOOR_NAME:
		{
		    if(response)
		    {
				if(strlen(inputtext) > 32 || strlen(inputtext) < 1)
				{
				    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona nazwa drzwi jest niepoprawna.\nSpróbuj ponownie za chwilê.", "Zamknij", "");
				    return 1;
				}
				
				format(DoorInfo[PlayerDoor[playerid]][dName], 32, "%s", inputtext);
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nazwa drzwi zosta³a pomyœlnie zmieniona.", "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_DOOR_PRICE:
		{
		    if(response)
		    {
				new price_id = strval(inputtext);
				
				if(!price_id)
				{
				    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona cena za wejœcie do lokalu jest nieprawid³owa.", "Zamknij", "");
				    return 1;
				}
				
				DoorInfo[PlayerDoor[playerid]][dEnterCash] = price_id;
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Cena wejœcia do lokalu zosta³a pomyœlnie zmieniona.", "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_PHONE:
		{
			if(response)
   			{
			    switch(listitem)
			    {
			        case 0: // Zadzwoñ do numeru
					{
						ShowPlayerDialog(playerid, D_PHONE_CALL, DIALOG_STYLE_INPUT, " Numer telefonu", "WprowadŸ numer telefonu pod który chcesz zadzwoniæ.", "Zadzwoñ", "Zamknij");
					}
					case 1: // Wyœlij wiadomoœæ SMS
					{
					    ShowPlayerDialog(playerid, D_PHONE_SMS, DIALOG_STYLE_INPUT, " Numer telefonu", "WprowadŸ numer telefonu pod który chcesz wys³aæ wiadomoœæ SMS.", "Dalej", "Zamknij");
					}
					case 2: // Lista kontaktów
					{
					    new itemid = GetItemID(CharacterCache[playerid][pPhone]);
					    new name[32], number;
						new list_vcards[1024], query[256], data[64];
						
						format(list_vcards, sizeof(list_vcards), "911\tTelefon alarmowy", list_vcards);
						format(list_vcards, sizeof(list_vcards), "%s\n777\tLas Venturas Transport Logistic", list_vcards);
						format(list_vcards, sizeof(list_vcards), "%s\n778\tLas Venturas Magazine", list_vcards);
						format(list_vcards, sizeof(list_vcards), "%s\n444\tLos Santos News", list_vcards);
						format(list_vcards, sizeof(list_vcards), "%s\n333\tKorporacje taksówkarskie", list_vcards);
						
						format(list_vcards, sizeof(list_vcards), "%s\n-----", list_vcards);
						
		    			format(query, sizeof(query), "SELECT * FROM `fc_vcards` WHERE `phone_number` = '%d'", ItemInfo[itemid][iValue1]);

						mysql_check();
						mysql_query(query);
					    mysql_store_result();

					    while(mysql_fetch_row_format(data, "|"))
					    {
					        sscanf(data, "p<|>s[32]d", name, number);
					        format(list_vcards, sizeof(list_vcards), "%s\n%d\t%s", list_vcards, number, name);
					    }
					    mysql_free_result();

						ShowPlayerDialog(playerid, D_CONTACTS, DIALOG_STYLE_LIST, " Lista kontaktów", list_vcards, "Wybierz", "Zamknij");
					}
					case 3: // Ustawienia
					{
					    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Opcja jest chwilowo niedostepna.", "Zamknij", "");
					    return 1;
					}
			    }
			}
			else
			{
			    return 1;
			}
		}
		case D_PHONE_CALL:
		{
		    if(response)
		    {
		        cmd_call(playerid, inputtext);
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_PHONE_SMS:
		{
		    if(response)
		    {
				new number = strval(inputtext);
				PhoneNumber[playerid] = number;
				
				if(!number) return 1;
				
				ShowPlayerDialog(playerid, D_PHONE_SMS_SEND, DIALOG_STYLE_INPUT, " Wiadomoœæ SMS", "WprowadŸ wiadomoœæ SMS, któr¹ chcesz wys³aæ pod dany numer:", "Wyœlij", "Zamknij");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_PHONE_SMS_SEND:
		{
			if(response)
		    {
		        new command[64];
				if(strlen(inputtext) < 1 || strlen(inputtext) > 32)
				{
				    ShowPlayerDialog(playerid, D_PHONE_SMS_SEND, DIALOG_STYLE_INPUT, " Wiadomoœæ SMS", "Wiadomoœæ jest zbyt d³uga, spróbuj ponownie.\n\nWprowadŸ wiadomoœæ SMS, któr¹ chcesz wys³aæ pod dany numer:", "Wyœlij", "Zamknij");
				}
				
				format(command, sizeof(command), "%d %s", PhoneNumber[playerid], inputtext);
				PhoneNumber[playerid] = 0;
				
				cmd_sms(playerid, command);
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_BLOCK_CHAR:
		{
			new giveplayer_id = CharacterCache[playerid][pBlockPlayer];
			new reason[128];
			
			format(reason, sizeof(reason), "%s", CharacterCache[playerid][pBlockReason]);
			
		    if(response)
		    {
		        if(CharacterCache[giveplayer_id][pBW])
		        {
		            AddCorpse(giveplayer_id, CharacterCache[playerid][pDeathReason], CharacterCache[playerid][pDeathWeapon]);
		        }
		        else
		        {
                	AddCorpse(giveplayer_id, 54, CharacterCache[playerid][pDeathWeapon]);
                }

	        	SendClientMessageFormat(giveplayer_id, 0xBA2818FF, "(INFO) Twoje konto zosta³o zablokowane przez %s.", CharacterCache[playerid][pGlobalNick], reason);
				SendClientMessage(giveplayer_id, 0xBA2818FF, "(INFO) Konto zosta³o zablokowane z powodu œmierci naturalnej.");
				
				KickWithWait(giveplayer_id);
		    }
		    else
		    {
	        	SendClientMessageFormat(giveplayer_id, 0xBA2818FF, "(INFO) Twoje konto zosta³o zablokowane przez %s.", CharacterCache[playerid][pGlobalNick], reason);
	        	GivePenalty(giveplayer_id, playerid, -1, PENALTY_BLOCK, 0, reason);
	        	
	        	KickWithWait(giveplayer_id);
		    }
		}
		case D_CONTACTS:
		{
			if(response)
			{
			    new number = strval(inputtext),
			        string[128];
			        
			    PhoneNumber[playerid] = number;
				if(!number) return 1;
				    
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
    			    format(string, sizeof(string), "%s (telefon): Las Venturas Transport Logistic.", PlayerName2(playerid));
   					ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
   					
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
				    ShowPlayerDialog(playerid, D_CONTACT_OPTIONS, DIALOG_STYLE_LIST, " Opcje kontaktu", "# Zadzwoñ do kontaktu\n# Napisz SMS do kontaktu\n# Zmieñ nazwê kontaktu", "Wybierz", "Zamknij");
			    }
			}
			else
			{
			    return 1;
			}
		}
		case D_ORDER_VALUE:
		{
		    if(response)
		    {
		        new value = strval(inputtext);
		        new product_id = GetPVarInt(playerid, "ProductID");
		        new door_id = GetPVarInt(playerid, "ProductDoor");
		        new doorid = PlayerDoor[playerid];
		        new string[512], data[64], product_value1, product_value2, product_cash, product_kind, product_name[32];
		        
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
		        if(value < 0 || value == 0)
		        {
		        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona iloœæ sztuk jest nieprawid³owa.", "Zamknij", "");
   			    	return 1;
		        }
		        
				mysql_query_format("SELECT `product_value1`, `product_value2`, `product_cash`, `product_kind`, `product_name` FROM `fc_orders_products` WHERE `product_uid` = '%d'", product_id);
				
				mysql_store_result();
				mysql_fetch_row_format(data, "|");
				
				sscanf(data, "p<|>ddddds[32]", product_value1, product_value2, product_cash, product_kind, product_name);
				mysql_free_result();
				
		        if(GroupData[DoorInfo[doorid][dOwner]][Cash] < ((product_cash * value) + (3 * value)))
		        {
		        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Na koncie grupowym nie znajduje siê odpowiednia kwota na zakup produktu.", "Zamknij", "");
   			    	return 1;
		        }
		        
		        GroupData[DoorInfo[doorid][dOwner]][Cash] -= ((product_cash * value) + (3 * value));
		        SaveGroup(DoorInfo[doorid][dOwner]);
		        
		        mysql_query_format("INSERT INTO `fc_orders` (`door_uid`, `value1`, `value2`, `name`, `value`, `drive`, `kind`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d')", DoorInfo[door_id][dUID], product_value1, product_value2, product_name, value, 0, product_kind);
		        
		        new uid = mysql_insert_id();
		        
				format(string, sizeof(string), "{008000}Produkt zamówiony!");
				format(string, sizeof(string), "%s\n\n{FFFFFF}Numer przesy³ki: %d", string, uid);
				format(string, sizeof(string), "%s\nNazwa: %s", string, product_name);
				format(string, sizeof(string), "%s\nIloœæ: %d", string, value);
				format(string, sizeof(string), "%s\nCena za szt.: $%d\n", string, product_cash);
				format(string, sizeof(string), "%s\nKurier: $%d\nL¹cznie: $%d\n\nPoczekaj na kuriera, aby sprawdziæ status paczki zadzwon pod 778.", string, 3 * value, ((product_cash * value) + (3 * value)));

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Produkt zamówiony!", string, "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_ORDER_ID:
		{
		    if(response)
		    {
		        new product_id = strval(inputtext);
		        
		        SetPVarInt(playerid, "ProductID", product_id);
		        
				ShowPlayerDialog(playerid, D_ORDER_VALUE, DIALOG_STYLE_INPUT, " Iloœæ sztuk", "WprowadŸ iloœæ sztuk do zamówienia przez kuriera.", "Zamów", "Zamknij");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_ORDER_CATEGORY:
		{
		    if(response)
		    {
		        new list_products[1024], data[64], product_uid, product_name[32], product_cash;
		        new cat_id = strval(inputtext);
		        
				mysql_query_format("SELECT `product_uid`, `product_name`, `product_cash` FROM `fc_orders_products` WHERE `product_cat` = '%d' AND `product_group` = '%d'", cat_id, DoorInfo[PlayerDoor[playerid]][dOwner]);

				mysql_store_result();

				while(mysql_fetch_row_format(data, "|"))
				{
				    sscanf(data, "p<|>ds[32]d", product_uid, product_name, product_cash);
				    
				    format(list_products, sizeof(list_products), "%s\n%d\t%s ($%d)", list_products, product_uid, product_name, product_cash);
				}
				
				mysql_free_result();

				ShowPlayerDialog(playerid, D_ORDER_ID, DIALOG_STYLE_LIST, " Produkty do zamówienia", list_products, "Wybierz", "Wróæ");
		    }
		    else
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
       			if(!IsPlayerPermInGroup(playerid, DoorInfo[doorid][dOwner], PANEL_PRODUCT))
       			{
       				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz uprawnieñ do zamawiania produktów.", "Zamknij", "");
      			    return 1;
       			}

				new list_type[1024], data[64], uid, name[32];
				mysql_query_format("SELECT * FROM `orders_type`");

				mysql_store_result();

				while(mysql_fetch_row_format(data, "|"))
				{
				    sscanf(data, "p<|>ds[32]", uid, name);
					    
				    format(list_type, sizeof(list_type), "%s\n%d\t%s", list_type, uid, name);
				}
					
				mysql_free_result();

				ShowPlayerDialog(playerid, D_ORDER_CATEGORY, DIALOG_STYLE_LIST, " Wybierz kategoriê produktów", list_type, "Wybierz", "Zamknij");
		    }
		}
		case D_TAXI:
		{
		    if(response)
		    {
				new groupid = strval(inputtext);
				new color = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0xFF;
				new string[128];
				new itemid = GetItemID(CharacterCache[playerid][pPhone]);
				
				if(!GroupData[groupid][UID]) return 1;
				
				AddReport(playerid, groupid, "Transport pasazera.");

				format(string, sizeof(string), "** Zawiadomienie od numeru %d (( %s )) **", ItemInfo[itemid][iValue1], PlayerName2(playerid));
				SendMessageToGroup(GroupData[groupid][UID], color, string);

				SendMessageToGroup(GroupData[groupid][UID], color, "** U¿yj /g {slot} zg³oszenia aby przyj¹æ zg³oszenie **");
				
				format(string, sizeof(string), "%s (telefon): %s.", PlayerName2(playerid), GroupData[groupid][Desc]);
				ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Taksówka zosta³a wezwana w miejsce, w którym siê znajdujesz.\nOtrzymasz informacjê gdy pracownik zaakceptuje kurs.", "Zamknij", "");
	    	}
		    else
		    {
		        return 1;
		    }
		}
		case D_RADIO:
		{
		    if(response)
		    {
		        new groupid = GetGroupKind(GROUP_RADIO);
		        new color = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0xFF;
		        new itemid = GetItemID(CharacterCache[playerid][pPhone]);
		        new string[128];
		        
		        format(string, sizeof(string), "** Zawiadomienie od numeru %d (( %s )) **", ItemInfo[itemid][iValue1], PlayerName2(playerid));
				SendMessageToGroup(GroupData[groupid][UID], color, string);

                format(string, sizeof(string), "** %s **", inputtext);
				SendMessageToGroup(GroupData[groupid][UID], color, string);
				
				format(string, sizeof(string), "%s (telefon): %s.", PlayerName2(playerid), inputtext);
				ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_CONTACT_OPTIONS:
		{
		    if(response)
		    {
				switch(listitem)
				{
				    case 0: // Zadzwoñ do kontaktu
				    {
				        new str[12];
				        format(str, sizeof(str), "%d", PhoneNumber[playerid]);
				        
        				cmd_call(playerid, str);
				    }
				    case 1: // SMS do kontaktu
				    {
				        ShowPlayerDialog(playerid, D_PHONE_SMS_SEND, DIALOG_STYLE_INPUT, " Wiadomoœæ SMS", "WprowadŸ wiadomoœæ SMS, któr¹ chcesz wys³aæ pod dany numer:", "Wyœlij", "Zamknij");
				    }
				    case 2:
				    {
				        ShowPlayerDialog(playerid, D_CHANGE_CONTACT_NAME, DIALOG_STYLE_INPUT, " Zmiana nazwy kontaktu", "WprowadŸ now¹ nazwê dla kontaktu", "Zmieñ", "Zamknij");
				    }
				}
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_CHANGE_CONTACT_NAME:
		{
		    if(response)
		    {
		        new itemid = GetItemID(CharacterCache[playerid][pPhone]),
		            query[256];

				if(!itemid)
				{
				    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz przy sobie przedmiotu aktywowanego telefonu.", "Zamknij", "");
				    return 1;
				}
		        if(!strlen(inputtext) || strlen(inputtext) > 32 || strlen(inputtext) < 3)
		        {
		            ShowPlayerDialog(playerid, D_CHANGE_CONTACT_NAME, DIALOG_STYLE_INPUT, " Zmiana nazwy kontaktu", "WprowadŸ now¹ nazwê dla kontaktu", "Zmieñ", "Zamknij");
		        }
		        
				format(query, sizeof(query), "UPDATE `fc_vcards` SET `name` = '%s' WHERE `number` = '%d' AND `phone_number` = '%d'", inputtext, PhoneNumber[playerid], ItemInfo[itemid][iValue1]);

				mysql_check();
				mysql_query(query);

				PhoneNumber[playerid] = 0;
                
                ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nazwa kontaktu zosta³a pomyœlnie zmieniona.", "Zamknij", "");
			}
		    else
		    {
		        return 1;
		    }
		}
		case D_BANK:
		{
		    if(response)
			{
		        switch(listitem)
		        {
		            case 0: // Stwórz now¹ kartê
					{
						ShowPlayerDialog(playerid, D_CREATE_CARD, DIALOG_STYLE_MSGBOX, " Tworzenie karty", "Tworzenie karty kredytowej\n\n\nAby stworzyæ kartê kredytow¹ musisz posiadaæ dowód osobisty oraz pewn¹ kwotê pieniêdzy.\nKarta zostanie stworzona i udostêpniona automatycznie.\n\nKoszt karty:\t\t$25\nTypy kart:\t\tZwyk³a / PayPass\n\nCzy chcesz utworzyæ swoj¹ kartê?", "Tak", "Nie");
					}
					case 1: // Lista posiadanych kart
					{
					    new data[128], list_cards[2048], card_uid, card_number, card_cash, card_block, card_name[32], query[256];
					    format(query, sizeof(query), "SELECT `card_uid`, `card_number`, `card_cash`, `card_block`, `card_name` FROM `fc_cards` WHERE `card_char` = '%d' AND `card_group` = '%d'", CharacterCache[playerid][pUID], GroupData[DoorInfo[PlayerDoor[playerid]][dOwner]][UID]);

						mysql_check();
						mysql_query(query);
					    mysql_store_result();

					    while(mysql_fetch_row_format(data, "|"))
					    {
					        sscanf(data, "p<|>dddds[32]", card_uid, card_number, card_cash, card_block, card_name);
					        
					        if(card_block) format(list_cards, sizeof(list_cards), "%s\n\t\t%s {BF291D}[Zablokowana]", list_cards, card_name);
					        else format(list_cards, sizeof(list_cards), "%s\n%d\t\t%s", list_cards, card_number, card_name);
					    }
					    mysql_free_result();

						if(strlen(list_cards) != 0) ShowPlayerDialog(playerid, D_CARD_INFO, DIALOG_STYLE_LIST, " Karty kredytowe", list_cards, "Wybierz", "Zamknij");
						else ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie posiadasz ¿adnych kart kredytowych.\nStwórz now¹ kartê kredytow¹.", "Zamknij", "");
					}
					case 2: // Kredyt bankowy
					{
					    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Kredyt bankowy\n\nOpcja wziêcia kredytu bankowego udostêpniona bêdzie ju¿ nied³ugo.\nPoinformujemy Ciê gdy udostêpnimy konta kredytowe.", "Zamknij", "");
					}
		        }
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_CREATE_CARD:
		{
		    if(response)
		    {
		        ShowPlayerDialog(playerid, D_CREATED_CARD, DIALOG_STYLE_PASSWORD, " Informacja", "WprowadŸ kod PIN do Twojej nowej karty.\nZapamiêtaj go gdy¿ nie zostanie Ci on przywrócony.", "WprowadŸ", "Zamknij");
		    }
			else
			{
			    return 1;
			}
		}
		case D_CREATED_CARD:
		{
		    if(response)
		    {
		        if(strlen(inputtext) != 4 || !isNumeric(inputtext))
		        {
		        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony kod PIN jest nieprawid³owy. Wymagana liczba znaków to 4.", "Zamknij", "");
				    return 1;
		        }
				if(CharacterCache[playerid][pCash] < 25)
				{
				    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz przy sobie 25 dolarów aby stworzyæ kartê.", "Zamknij", "");
				    return 1;
				}
				
				GivePlayerCash(playerid, -25);
				
				new query[256];
				new groupid = DoorInfo[PlayerDoor[playerid]][dOwner];
				new number = 444444 + random(111111);
				
				format(query, sizeof(query), "INSERT INTO `fc_cards` VALUES (NULL, '%d', '%d', '%d', '%s', '%d', '%s', '%d', '%d')", CharacterCache[playerid][pUID], number, 0, inputtext, 0, "Konto kredytowe", GroupData[groupid][UID], 0);
				
				mysql_check();
				mysql_query(query);
				
				new uid = mysql_insert_id();

				GroupData[groupid][Cash] += 25;
				SaveGroup(groupid);
				
				CreatePlayerItem(playerid, "Karta kredytowa", TYPE_CARD, uid, CharacterCache[playerid][pUID], 1);
				
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Gratulacje!\nPomyœlnie stworzy³eœ swoj¹ kartê kredytow¹.\nKarta jest o typie zwyk³ym lecz w ka¿dej chwili mo¿esz zmieniæ j¹ na PayPass.\n\nKwota 25 dolarów zosta³a pobrana z konta.", "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_CARD_INFO:
		{
		    if(response)
	  		{
				new list_options[1024];
				new card_id = strval(inputtext);
				new query[256], result[64];
				new card_number, card_name[32], card_group, card_type, card_cash;
				
				if(!card_id)
				{
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wyst¹pi³ b³¹d w kontakcie z bankiem.\nKarta nie zosta³a wykryta lub zosta³a zablokowana.", "Zamknij", "");
				    return 1;
				}
				
				CardUse[playerid] = card_id;
				
				format(query, sizeof(query), "SELECT `card_number`, `card_name`, `card_group`, `card_type`, `card_cash` FROM `fc_cards` WHERE `card_number` = '%d'", card_id);
				
				mysql_check();
				mysql_query(query);
				mysql_store_result();
				mysql_fetch_row_format(result, "|");
				
				sscanf(result, "p<|>ds[32]ddd", card_number, card_name, card_group, card_type, card_cash);
				
				mysql_free_result();
				
				format(list_options, sizeof(list_options), "Numer karty:\t\t%d", card_id);
				
				if(!card_type) format(list_options, sizeof(list_options), "%s\nTyp karty:\t\tZwyk³a", list_options);
				else format(list_options, sizeof(list_options), "%s\nTyp karty:\t\t{7AB045}PayPass", list_options);
				
				format(list_options, sizeof(list_options), "%s\nKod PIN:\t\t****", list_options);
				format(list_options, sizeof(list_options), "%s\nStan konta:\t\t%d", list_options, card_cash);
				format(list_options, sizeof(list_options), "%s\nNazwa karty:\t\t%s", list_options, card_name);
				format(list_options, sizeof(list_options), "%s\nNazwa banku:\t\t%s", list_options, GroupData[card_group][Desc]);
				format(list_options, sizeof(list_options), "%s\nBlokada karty:\t\tNie", list_options);
				
				format(list_options, sizeof(list_options), "%s\n-----", list_options);
				
				if(!card_type) format(list_options, sizeof(list_options), "%s\n{7AB045}# Zamieñ na kartê PayPass ($50)", list_options);
				else format(list_options, sizeof(list_options), "%s\n# Zamieñ na kartê kredytow¹ ($25)", list_options);
				
				format(list_options, sizeof(list_options), "%s\n# Wyp³ata œrodków z konta", list_options);
				format(list_options, sizeof(list_options), "%s\n# Wp³ata œrodków na konto", list_options);
				format(list_options, sizeof(list_options), "%s\n# Zmieñ nazwê karty", list_options);
				format(list_options, sizeof(list_options), "%s\n# Zmieñ kod PIN", list_options);
				format(list_options, sizeof(list_options), "%s\n{DE1826}# Zablokuj kartê", list_options);
				
				ShowPlayerDialog(playerid, D_CARD_OPTIONS, DIALOG_STYLE_LIST, " Informacje dotycz¹ce karty", list_options, "Wybierz", "Zamknij");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_CARD_OPTIONS:
		{
		    if(response)
		    {
		        switch(listitem)
		        {
		            case 8: // Zmiana na kartê PayPass
					{
					    new query[256], result[12], card_number, card_type;
			  			format(query, sizeof(query), "SELECT `card_number`, `card_type` FROM `fc_cards` WHERE `card_number` = '%d'", CardUse[playerid]);

						mysql_check();
						mysql_query(query);
						mysql_store_result();
						mysql_fetch_row_format(result, "|");

						sscanf(result, "p<|>dd", card_number, card_type);

						mysql_free_result();
						
						if(card_type)
						{
						    if(CharacterCache[playerid][pCash] < 25)
						    {
						        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz odpowiedniej kwoty pieniêdzy, aby zmieniæ kartê. ($50)", "Zamknij", "");
						        return 1;
						    }
						    
						    GivePlayerCash(playerid, -25);
						    
						    format(query, sizeof(query), "UPDATE `fc_cards` SET `card_type` = 0 WHERE `card_number` = '%d'", CardUse[playerid]);
						    
						    mysql_check();
						    mysql_query(query);
						    
						    CardUse[playerid] = 0;
						    
						    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Twoja karta zosta³a zmieniona na zwyk³¹.", "Zamknij", "");
						}
						else
						{
						    if(CharacterCache[playerid][pCash] < 50)
						    {
						        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz odpowiedniej kwoty pieniêdzy, aby zmieniæ kartê. ($25)", "Zamknij", "");
						        return 1;
						    }
						    
						    GivePlayerCash(playerid, -50);
						    
						    format(query, sizeof(query), "UPDATE `fc_cards` SET `card_type` = 1 WHERE `card_number` = '%d'", CardUse[playerid]);

						    mysql_check();
						    mysql_query(query);
						    
						    CardUse[playerid] = 0;
						    
						    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Twoja karta zosta³a zmieniona na PayPass.", "Zamknij", "");
						}
		            }
		            case 9: // Wyp³ata œrodków
		            {
		                ShowPlayerDialog(playerid, D_CASH_OUT, DIALOG_STYLE_INPUT, " Informacja", "Podaj kwotê wyp³aty œrodków z konta:", "Wyp³aæ", "Zamknij");
		            }
		            case 10: // Wp³ata œrodków
		            {
		            	ShowPlayerDialog(playerid, D_CASH_IN, DIALOG_STYLE_INPUT, " Informacja", "Podaj kwotê wp³aty na konto bankowe:", "Wp³aæ", "Zamknij");
		            }
		            case 11: // Zmiana nazwy karty
		            {
		                ShowPlayerDialog(playerid, D_CHANGE_CARD_NAME, DIALOG_STYLE_INPUT, " Zmiana nazwy karty", "WprowadŸ now¹ nazwê karty kredytowej.", "Zmieñ", "Zamknij");
		            }
					case 12: // Zmiana kodu PIN
					{
					    ShowPlayerDialog(playerid, D_CHANGE_CARD_PIN, DIALOG_STYLE_PASSWORD, " Zmiana kodu PIN", "WprowadŸ nowy kod PIN do karty kredytowej.", "Zmieñ", "Zamknij");
					}
					case 13: // Blokada karty
					{
					    ShowPlayerDialog(playerid, D_BLOCK_CARD, DIALOG_STYLE_MSGBOX, " Blokada karty", "Czy chcesz dokonaæ blokadê swojej karty?\nNie bêdzie ona zdatna do u¿ytku.", "Tak", "Nie");
					}
		        }
		    }
		    else
			{
		        return 1;
		    }
		}
		case D_CASH_OUT:
		{
		    new cash = strval(inputtext), string[128], query[256];
		    
			new result[12], card_number, card_cash;
			format(query, sizeof(query), "SELECT `card_number`, `card_cash` FROM `fc_cards` WHERE `card_number` = '%d'", CardUse[playerid]);

			mysql_check();
			mysql_query(query);
			mysql_store_result();
			mysql_fetch_row_format(result, "|");

			sscanf(result, "p<|>dd", card_number, card_cash);

			mysql_free_result();
			
			if(card_cash < cash)
			{
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Na Twoim koncie nie znajduje siê odpowiednia iloœæ gotówki.", "Zamknij", "");
			    return 1;
			}

			GivePlayerCash(playerid, cash);
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC);

			format(query, sizeof(query), "UDATE `fc_cards` SET `card_cash` = `card_cash` - '%d' WHERE `card_number` = '%d'", cash, CardUse[playerid]);
			mysql_query(query);
			
			CardUse[playerid] = 0;

			format(string, sizeof(string), "Pomyœlnie wyp³aci³eœ gotówkê ($%d) z karty bankowej.", cash);
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		}
		case D_CASH_IN:
		{
		    new cash = strval(inputtext), string[128], query[256];
			if(CharacterCache[playerid][pCash] > cash)
			{
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz przy sobie tyle gotówki.", "Zamknij", "");
			    return 1;
			}
			
			CharacterCache[playerid][pCash] -= cash;
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
			
			format(query, sizeof(query), "UDATE `fc_cards` SET `card_cash` = `card_cash` + '%d' WHERE `card_number` = '%d'", cash, CardUse[playerid]);
			mysql_query(query);
			
			CardUse[playerid] = 0;
			
			format(string, sizeof(string), "Pomyœlnie wp³aci³eœ gotówkê w wysokoœci %d dolarów na swoj¹ kartê.", cash);
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		}
		case D_CHANGE_CARD_NAME:
		{
		    if(response)
		    {
		        if(!CardUse[playerid])
				{
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie wybra³eœ ¿adnej karty. Spróbuj ponownie póŸniej.", "Zamknij", "");
				    return 1;
				}
				if(strlen(inputtext) < 6)
				{
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzona iloœæ znaków jest nieprawid³owa. Minimalna iloœc znaków to 6.", "Zamknij", "");
				    return 1;
				}
				
				new query[256];
                format(query, sizeof(query), "UPDATE `fc_cards` SET `card_name` = '%s' WHERE `card_number` = '%d'", inputtext, CardUse[playerid]);

				mysql_check();
    			mysql_query(query);
						    
                CardUse[playerid] = 0;
                
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nazwa karty zosta³a pomyœlnie zmieniona.", "Zamknij", "");
		    }
		    else
			{
		        return 1;
		    }
		}
		case D_CHANGE_CARD_PIN:
		{
		    if(response)
			{
		        if(strlen(inputtext) != 4 || !isNumeric(inputtext))
		        {
		        	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony kod PIN jest nieprawid³owy. Wymagana liczba znaków to 4.", "Zamknij", "");
				    return 1;
		        }
		        
				new query[256];
                format(query, sizeof(query), "UPDATE `fc_cards` SET `card_pin` = '%s' WHERE `card_number` = '%d'", inputtext, CardUse[playerid]);

				mysql_check();
    			mysql_query(query);

                CardUse[playerid] = 0;

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Kod PIN zosta³ pomyœlnie zmieniony.", "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_BLOCK_CARD:
		{
		    if(response)
		    {
		    	new query[256];
                format(query, sizeof(query), "UPDATE `fc_cards` SET `card_block` = 1 WHERE `card_number` = '%d'", CardUse[playerid]);

				mysql_check();
    			mysql_query(query);

                CardUse[playerid] = 0;

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Karta zosta³a pomyœlnie zablokowana.", "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_CHECK_GROUP:
		{
		    if(response)
		    {
		        new itemid = strval(inputtext);
				if(!itemid) return 1;
				
				if(!GroupData[itemid][UID])
				{
				    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Podana grupa nie zosta³a znaleziona.", "Zamknij", "");
				    return 1;
				}
				
				EditGroup[playerid] = itemid;
				cmd_agrupa(playerid, "edytuj");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_EDIT_GROUP:
		{
		    if(response)
		    {
		        switch(listitem)
		        {
		            case 0: // Nazwa grupy
		            {
		                new title[128];
		                format(title, sizeof(title), "%s (UID: %d) » Zmiana nazwy grupy", GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);
		                
		                ShowPlayerDialog(playerid, D_GROUP_NAME, DIALOG_STYLE_INPUT, title, "WprowadŸ now¹ nazwê dla grupy.", "Zmieñ", "Zamknij");
		            }
		            case 1: // Tag grupy
		            {
		                new title[128];
		                format(title, sizeof(title), "%s (UID: %d) » Zmiana tagu grupy", GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);
		                
		                ShowPlayerDialog(playerid, D_GROUP_TAG, DIALOG_STYLE_INPUT, title, "WprowadŸ nowy tag dla grupy.", "Zmieñ", "Zamknij");
		            }
		            case 2: // Flagi grupy
		            {
 						new string_group[12];
				        format(string_group, sizeof(string_group), "flagi %d", EditGroup[playerid]);

				        EditGroup[playerid] = 0;
				        cmd_agrupa(playerid, string_group);
		            }
		            case 3: // Limit pojazdów
		            {
		                new title[128];
		                format(title, sizeof(title), "%s (UID: %d) » Limit pojazdów", GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);
		                
						ShowPlayerDialog(playerid, D_GROUP_LIMIT, DIALOG_STYLE_INPUT, title, "WprowadŸ iloœæ pojazdów mo¿liwych do zespawnowania w grupie.", "WprowadŸ", "Zamknij");
		            }
		            case 4: // Podatek
		            {
		                new title[128];
		                format(title, sizeof(title), "%s (UID: %d) » Podatek grupowy", GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);
		                
						ShowPlayerDialog(playerid, D_GROUP_TAX, DIALOG_STYLE_LIST, title, "7\tOp³ata podatku na 7 dni\n14\tOp³ata podatku na 14 dni\n30\tOp³ata podatku na 30 dni", "Wybierz", "Zamknij");
		            }
		            case 5: // Typ grupy
		            {
						new string[1024];

		                ForeachEx(i, COUNT_GROUP + 1)
		                {
		                    format(string, sizeof(string), "%s\n%d\t%s", string, i, GroupInfo[i][gName]);
		                }

                        new title[128];
		                format(title, sizeof(title), "%s (UID: %d) » Zmiana typu grupy", GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);
		                
		                ShowPlayerDialog(playerid, D_GROUP_KIND, DIALOG_STYLE_LIST, title, string, "Zamieñ", "Zamknij");
		            }
		            case 6: // Lider
		            {
		                new title[128];
		                format(title, sizeof(title), "%s (UID: %d) » Nadawanie lidera", GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);
		                
						ShowPlayerDialog(playerid, D_GROUP_LEADER, DIALOG_STYLE_INPUT, title, "WprowadŸ ID osoby, która ma zostaæ nowym liderem grupy.", "Wybierz", "Zamknij");
		            }
		            case 7: // Usuñ pracowników
		            {
		                new title[128];
		                format(title, sizeof(title), "%s (UID: %d) » Usuwanie pracowników z grupy", GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);

						new string[256];
						format(string, sizeof(string), "Czy chcesz usun¹æ wszystkich pracowników z grupy %s (UID: %d)?\nOperacja nie bêdzie mog³a zostaæ cofniêta.", GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);

						ShowPlayerDialog(playerid, D_GROUP_MEMBERS, DIALOG_STYLE_MSGBOX, title, string, "Tak", "Nie");
		            }
		            case 8: // Usuñ grupê
		            {
						new string_group[12];
				        format(string_group, sizeof(string_group), "usuñ %d", EditGroup[playerid]);

				        EditGroup[playerid] = 0;
				        cmd_agrupa(playerid, string_group);
		            }
		        }
			}
		    else
		    {
		        EditGroup[playerid] = 0;
		        
		        return 1;
		    }
		}
		case D_GROUP_NAME:
		{
		    if(response)
		    {
		        if(strlen(inputtext) == 0) return 1;

		        new string_group[64];
		        format(string_group, sizeof(string_group), "nazwa %d %s", EditGroup[playerid], inputtext);

		        EditGroup[playerid] = 0;
		        cmd_agrupa(playerid, string_group);
 		    }
		    else
		    {
		        EditGroup[playerid] = 0;
		        
		        return 1;
			}
		}
		case D_GROUP_TAG:
		{
		    if(response)
		    {
		   		if(strlen(inputtext) == 0) return 1;

		        new string_group[32];
		        format(string_group, sizeof(string_group), "tag %d %s", EditGroup[playerid], inputtext);

		        EditGroup[playerid] = 0;
		        cmd_agrupa(playerid, string_group);
		    }
		    else
		    {
		        EditGroup[playerid] = 0;
		        
		        return 1;
		    }
		}
		case D_GROUP_KIND:
		{
		    if(response)
		    {
		    	if(!strval(inputtext)) return 1;

		        new string_group[12];
		        format(string_group, sizeof(string_group), "typ %d %d", EditGroup[playerid], strval(inputtext) );

		        EditGroup[playerid] = 0;
		        cmd_agrupa(playerid, string_group);
		    }
		    else
		    {
		        EditGroup[playerid] = 0;
		        
		        return 1;
		    }
		}
		case D_GROUP_LIMIT:
		{
			if(response)
			{
			    if(strval(inputtext) < 1) return 1;

			    new string_group[12];
		        format(string_group, sizeof(string_group), "limit %d %d", EditGroup[playerid], strval(inputtext));

		        EditGroup[playerid] = 0;
		        cmd_agrupa(playerid, string_group);
			}
			else
			{
			    EditGroup[playerid] = 0;
			    
			    return 1;
			}
		}
		case D_GROUP_TAX:
		{
		    if(response)
		    {
		        if(strval(inputtext) != 7 && strval(inputtext) != 14 && strval(inputtext) != 30) return 1;

		        new string_group[24];
		        format(string_group, sizeof(string_group), "podatek %d %d", EditGroup[playerid], strval(inputtext));

		        EditGroup[playerid] = 0;
		        cmd_agrupa(playerid, string_group);
		    }
		    else
		    {
		        EditGroup[playerid] = 0;
		        
		        return 1;
		    }
		}
		case D_GROUP_LEADER:
		{
		    if(response)
		    {
		        new playerid2 = strval(inputtext);

		        if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wybrany gracz nie jest zalogowany.", "Zamknij", "");
		            return 1;
		        }

		        SetPVarInt(playerid, "GroupPlayerID2", playerid2);

                new title[128];
			    format(title, sizeof(title), "%s (UID: %d) » Nadawanie lidera", GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);

				new string[256];
				format(string, sizeof(string), "Czy chcesz nadaæ graczowi %s (ID: %d) lidera grupy %s (UID: %d)?", PlayerName2(playerid2), playerid2, GroupData[EditGroup[playerid]][Desc], GroupData[EditGroup[playerid]][UID]);

				ShowPlayerDialog(playerid, D_GROUP_CHECK_LEADER, DIALOG_STYLE_MSGBOX, title, string, "Tak", "Nie");
			}
			else
			{
			    EditGroup[playerid] = 0;
			    
			    return 1;
			}
		}
		case D_GROUP_CHECK_LEADER:
		{
		    if(response)
		    {
				new playerid2 = GetPVarInt(playerid, "GroupPlayerID2");
    			new string_group[24];

		        format(string_group, sizeof(string_group), "lider %d %d", playerid2, EditGroup[playerid]);

		        EditGroup[playerid] = 0;
		        cmd_agrupa(playerid, string_group);
		    }
			else
			{
			    EditGroup[playerid] = 0;
			    
			    return 1;
			}
		}
		case D_GROUP_MEMBERS:
		{
		    if(response)
		    {
		        new groupid = EditGroup[playerid];
		        new query[256];

		        ForeachEx(i, MAX_PLAYERS)
		        {
		            if(IsPlayerInGroup(i, groupid))
		            {
		                SendClientMessageFormat(playerid, CZERWONY, " » Zosta³eœ usuniêty z grupy %s przez administratora %s (ID: %d).", GroupData[EditGroup[playerid]][Desc], PlayerName2(playerid), playerid);
		            }
		        }

				format(query, sizeof(query), "DELETE FROM `fc_member_groups` WHERE `group_id` = '%d'", EditGroup[playerid]);
		        mysql_query(query);
		        
		        EditGroup[playerid] = 0;

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pracownicy w grupie zostali usuniêci.", "Zamknij", "");
		    }
		    else
		    {
		        EditGroup[playerid] = 0;
		        
		        return 1;
		    }
		}
		case D_CALL_911:
		{
		    if(response)
		    {
		        new groupid = strval(inputtext);
				new title[128], string[128];
		        SetPVarInt(playerid, "CallGroup", groupid);
		        
				format(string, sizeof(string), "%s (telefon): %s,", PlayerName2(playerid), GroupData[groupid][Desc]);
				ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		        
		        format(title, sizeof(title), "%s » Telefon alarmowy", GroupData[groupid][Desc]);
		        ShowPlayerDialog(playerid, D_CALL_911_REASON, DIALOG_STYLE_INPUT, title, "Centrala 911:\n\tProszê opisaæ co siê dzieje. Miejsce zg³oszenia zostanie automatycznie namierzone.\n\tPamiêtaj o poprawnoœci swoich danych.", "Zg³oœ", "Zamknij");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_CALL_911_REASON:
		{
		    if(response)
		    {
				new groupid = GetPVarInt(playerid, "CallGroup");
				new text[512];
				new color = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0xFF;
				new string[128];
				new itemid = GetItemID(CharacterCache[playerid][pPhone]);
				
				format(text, 512, "%s", inputtext);
				AddReport(playerid, groupid, text);
				
				format(string, sizeof(string), "** Zawiadomienie od numeru %d (( %s )) **", ItemInfo[itemid][iValue1], PlayerName2(playerid));
				SendMessageToGroup(GroupData[groupid][UID], color, string);
				
				SendMessageToGroup(GroupData[groupid][UID], color, "** U¿yj /g {slot} zg³oszenia aby przyj¹æ zg³oszenie **");
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Zg³oszenie przyjête", "Zg³oszenie zosta³o przyjête przez pracownika 911 Emergency Center.\nW miejsce wezwania zosta³y wys³ane odpowiednie jednostki.\n\nOczekuj w spokoju na dojazd jednostek pomocy.", "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_REPORTS:
		{
		    if(response)
		    {
		        new reportid = strval(inputtext);
		        new playerid2 = GetPlayerID(ReportInfo[reportid][reportChar]);
		        
		        if(ReportInfo[reportid][reportStatus])
		        {
		            if(ReportInfo[reportid][reportStatus] != CharacterCache[playerid][pUID])
		            {
		                cmd_zadanie(playerid, " ");
		            }
		            else
		            {
			            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Zg³oszenie jest akutalnie rozpatrywane przez inn¹ jednostkê.", "Zamknij", "");
			            return 1;
		            }
		        }
		        else
		        {
		            if(CharacterCache[playerid][pPackage])
					{
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Podczas dostarczania paczki nie mo¿esz odebraæ zg³oszenia.", "Zamknij", "");
						return 1;
					}

			        SetPlayerCheckpoint(playerid, ReportInfo[reportid][reportPos][0], ReportInfo[reportid][reportPos][1], ReportInfo[reportid][reportPos][2], 3.0);

			        ReportInfo[reportid][reportStatus] = CharacterCache[playerid][pUID];
					CharacterCache[playerid][pReportPD] = reportid;

					SendClientMessageFormat(playerid2, 0xCACACAFF, "Pracownik %s (ID: %d) odebra³ Twoje zg³oszenie (ID: %d).", PlayerName2(playerid), playerid, reportid);

			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zg³oszenie zosta³o przez Ciebie przyjête.\nUdaj siê do miejsca zaznaczego na mapie.\n\nOperowaæ na zg³oszeniu mo¿esz za pomoc¹ komendy /zadanie .", "Zamknij", "");
				}
			}
		    else
		    {
		    	return 1;
		    }
		}
		case D_REPORT_OPTIONS:
		{
		    if(response)
		    {
		        switch(listitem)
		        {
		            case 0:
		            {
		                new reportid = CharacterCache[playerid][pReportPD];
                        CharacterCache[playerid][pReportPD] = 0;
                        
                        DisablePlayerCheckpoint(playerid);

						DeleteReport(reportid);
                        
                        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zg³oszenie zosta³o pomyœlnie zakoñczone i nie  bêdzie wyœwietlane.", "Zamknij", "");
		            }
		            case 1:
		            {
		                new reportid = CharacterCache[playerid][pReportPD];
		                new playerid2 = GetPlayerID(ReportInfo[reportid][reportChar]);
		                
                        CharacterCache[playerid][pReportPD] = 0;
						ReportInfo[reportid][reportStatus] = 0;
						
						SendClientMessageFormat(playerid2, 0xCACACAFF, "Pracownik %s (ID: %d) anulowa³ dojazd do Twojego zg³oszenia (ID: %d).", PlayerName2(playerid), playerid, reportid);
						SendClientMessage(playerid2, 0xCACACAFF, "Poczekaj a¿ inny pracownik przejmie zg³oszenie.");
						
						DisablePlayerCheckpoint(playerid);

                        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zg³oszenie zosta³o pomyœlnie anulowane.\nOczekuje na ponowne znalezienie pracownika.", "Zamknij", "");
		            }
		            case 2:
		            {
		                new reportid = CharacterCache[playerid][pReportPD];
		                new string[1024];
		                
		                format(string, sizeof(string), "{88CC54}Zg³aszaj¹cy:{FFFFFF}\t%s (ID: %d)\n{88CC54}Treœæ:{FFFFFF}\n%s", ReportInfo[reportid][reportCharName], GetPlayerID(ReportInfo[reportid][reportChar]), ReportInfo[reportid][reportText]);
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacje o zg³oszeniu", string, "Zamknij", "");
					}
		        }
		    }
		    else
		    {
		        return 1;
			}
		}
		case D_OUT_ITEM:
		{
		    if(response)
		    {
		        new itemid = strval(inputtext);
				new item_uid = GetItemID(itemid);
		        new playerid2 = GetPVarInt(playerid, "ItemPlayerID2");
		        new string[256];
		        
		        format(string, sizeof(string), "UPDATE `fc_items` SET `ownertype` = '%d', `owner` = '%d' WHERE `uid` = '%d'", OWNER_PLAYER, CharacterCache[playerid][pUID], itemid);
				mysql_check(); mysql_query(string);
				
				format(string, sizeof(string), "Zabra³eœ przedmiot %s (UID: %d) graczowi %s (ID: %d).", ItemInfo[item_uid][iName], ItemInfo[item_uid][iUID], PlayerName2(playerid2), playerid2);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
				
				format(string, sizeof(string), "%s (ID: %d) zabra³ Tobie przedmiot %s (UID: %d).", PlayerName2(playerid), playerid, ItemInfo[item_uid][iName], ItemInfo[item_uid][iUID]);
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_GROUP_MAGAZINE:
		{
		    if(response)
			{
			    new itemid = strval(inputtext);
			    new item_uid = GetItemID(itemid);
			    new query[256], string[128];
			    
			    if(!item_uid)
			    {
			        LoadItem(itemid);
			        item_uid = GetItemID(itemid);
			    }
			    if(ItemInfo[item_uid][iValues] <= 0)
			    {
			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Iloœæ sztuk w magazynie nie jest prawid³owa.\nW przypadku b³êdu - powiadom administracjê.", "Zamknij", "");
			        
			        DeleteItem(ItemInfo[item_uid][iUID]);
			        return 1;
			    }
			    
			    CreatePlayerItem(playerid, ItemInfo[item_uid][iName], ItemInfo[item_uid][iType], ItemInfo[item_uid][iValue1], ItemInfo[item_uid][iValue2], 1);
			    
			    ItemInfo[item_uid][iValues] --;
			   
			    if(ItemInfo[item_uid][iValues] > 0)
			    {
			    	format(query, sizeof(query), "UPDATE `fc_items` SET `value` = `value` - 1 WHERE `uid` = '%d'", ItemInfo[item_uid][iUID]);
			    	mysql_check(); mysql_query(query);
			    }
			    else
			    {
			        DeleteItem(ItemInfo[item_uid][iUID]);
			    }
			    
			    format(string, sizeof(string), "Pomyœlnie wyci¹gn¹³eœ z magazynu przedmiot %s (UID: %d).", ItemInfo[item_uid][iName], ItemInfo[item_uid][iUID]);
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}
			else
			{
			    return 1;
			}
		}
		case D_ORDER_MAGAZINE:
		{
			if(response)
			{
			    new pack_id = strval(inputtext);
			    new data[32], order_uid, status, drive, doorid;

			    mysql_query_format("SELECT `order_uid`, `status`, `drive`, `door_uid` FROM `fc_orders` WHERE `order_uid` = '%d'", pack_id);

			    mysql_store_result();
			    mysql_fetch_row_format(data, "|");

			    sscanf(data, "p<|>dddd", order_uid, status, drive, doorid);
			    mysql_free_result();

			    if(status != 0)
			    {
		    		new string[256];
					format(string, sizeof(string), "Paczka zosta³a ju¿ dostarczona przez kuriera.\n\nNumer paczki: %d\nKurier: %s", order_uid, GetPlayerSQLName(drive));

			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", string, "Zamknij", "");
			        return 1;
			    }
			    if(drive != 0)
			    {
					new string[256];
					format(string, sizeof(string), "Aktualnie paczka jest dostarczana przez kuriera.\n\n{FFFFFF}Numer paczki: %d\nKurier: %s", order_uid, GetPlayerSQLName(drive));

			        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", string, "Zamknij", "");
			        return 1;
			    }

			    mysql_query_format("UPDATE `fc_orders` SET `drive` = '%d' WHERE `order_uid` = '%d'", CharacterCache[playerid][pUID], order_uid);

			    DisablePlayerCheckpoint(playerid);
			    SetPlayerCheckpoint(playerid, DoorInfo[doorid][dEnterX], DoorInfo[doorid][dEnterY], DoorInfo[doorid][dEnterZ], 3.0);

			    CharacterCache[playerid][pPackage] = true;
				CharacterCache[playerid][pPackageID] = order_uid;
				CharacterCache[playerid][pPackageDoor] = doorid;
				CharacterCache[playerid][pPackageTime] = gettime() + 60;

			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Paczka zosta³a pobrana z magazynu Las Ventruas.\nNa mapie zosta³o oznaczone miejsce odbioru paczki.", "Zamknij", "");
			}
			else
			{
			    return 1;
			}
		}
		case D_DESCRIPTIONS:
		{
		    if(response)
		    {
		        switch(strval(inputtext))
		        {
		            case 1: // Lista opisów
		            {
						new list[512];
						
						ForeachEx(i, MAX_DESC)
						{
						    if(DescInfo[i][descChar] == CharacterCache[playerid][pUID])
							{
						        format(list, sizeof(list), "%s\n%d\t%s", list, DescInfo[i][descID], DescInfo[i][descTitle]);
						    }
						}
						
						if(strlen(list) != 0) ShowPlayerDialog(playerid, D_USE_DESC, DIALOG_STYLE_LIST, " Lista dostêpnych opisów", list, "U¿yj", "Zamknij");
						else Infobox(playerid, 5, "Brak dostepnych opisów w bazie.");
					}
		            case 2: // Tworzenie opisu
					{
					    new count = GetPlayerDesc(playerid);
					    new max_count;
					    
					    if(IsPlayerPremium(playerid)) max_count = 5;
					    else max_count = 3;
					    
					    if(count > max_count)
					    {
					        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Iloœæ zapisanych opisów jest zbyt du¿a.\nUsuñ jeden z nich, aby móæ stworzyæ nowy.", "Zamknij", "");
					        return 1;
					    }
					    
					    ShowPlayerDialog(playerid, D_CREATE_DESC, DIALOG_STYLE_INPUT, " Tworzenie nowego opisu", "WprowadŸ tytu³ dla nowego opisu.", "Dalej", "Zamknij");
					}
		            case 3: // Usuwanie opisu
		            {
		            	new list[512];

						ForeachEx(i, MAX_DESC)
						{
						    if(DescInfo[i][descChar] == CharacterCache[playerid][pUID])
							{
						        format(list, sizeof(list), "%s\n%d\t%s", list, DescInfo[i][descID], DescInfo[i][descTitle]);
						    }
						}

						if(strlen(list) != 0) ShowPlayerDialog(playerid, D_DELETE_DESC, DIALOG_STYLE_LIST, " Lista dostêpnych opisów", list, "Usuñ", "Zamknij");
						else Infobox(playerid, 5, "Brak dostepnych opisów w bazie.");
		            }
		            case 4: // Pokazanie aktualnego opisu
					{
					    if(CharacterCache[playerid][pUseDesc])
					    {
					        new string[256];
					        format(string, sizeof(string), "Twój aktualny opis to:\n\n{FFFFFF}%s", WordWrap(DescInfo[CharacterCache[playerid][pUseDesc]][descText], 5));
					        
					        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
					    }
					    else
					    {
					        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Nie posiadasz u¿ytego ¿adnego z opisów.", "Zamknij", "");
					        return 1;
					    }
					}
		            case 5: // Usuwanie wszystkich opisów
		            {
		                ShowPlayerDialog(playerid, D_DELETE_ALL_DESC, DIALOG_STYLE_MSGBOX, " Usuniêcie opisów", "Czy chcesz usun¹æ wszystkie opisy nale¿¹ce do postaci?\nNie bêdziesz w stanie ich przywróciæ.", "Tak", "Nie");
		            }
		            case 6: // Usuniêcie aktualnego opisu
		            {
   						CharacterCache[playerid][pUseDesc] = 0;

						Update3DTextLabelText(CharacterCache[playerid][pDescTag], 0x7290C4FF, " ");

		        		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Opis postaci zosta³ pomyœlnie wy³¹czony.", "Zamknij", "");
		            }
		        }
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_DELETE_DESC:
		{
		    if(response)
		    {
				new desc_id = strval(inputtext);
				
				if(CharacterCache[playerid][pUseDesc] == desc_id)
				{
				    Update3DTextLabelText(CharacterCache[playerid][pDescTag], 0x7290C4FF, " ");
				    
                    CharacterCache[playerid][pUseDesc] = 0;
				}
				
				mysql_query_format("DELETE FROM `fc_descriptions` WHERE `desc_uid` = '%d'", desc_id);
				
				DescInfo[desc_id][descID] = 0;
				DescInfo[desc_id][descTitle] = 0;
				DescInfo[desc_id][descChar] = 0;
				DescInfo[desc_id][descText] = 0;
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Opis postaci zosta³ pomyœlnie usuniêty.", "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_DELETE_ALL_DESC:
		{
		    if(response)
			{
			    CharacterCache[playerid][pUseDesc] = 0;
				Update3DTextLabelText(CharacterCache[playerid][pDescTag], 0x7290C4FF, " ");

				mysql_query_format("DELETE FROM `fc_descriptions` WHERE `desc_char` = '%d'", CharacterCache[playerid][pUID]);

				ForeachEx(i, MAX_DESC)
				{
				    if(DescInfo[i][descChar] == CharacterCache[playerid][pUID])
				    {
				        DescInfo[i][descID] = 0;
				        DescInfo[i][descTitle] = 0;
				        DescInfo[i][descChar] = 0;
				        DescInfo[i][descText] = 0;
				    }
				}

			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Wszystkie opisy zosta³y usuniête pomyœlnie.", "Zamknij", "");
			}
			else
			{
			    return 1;
			}
		}
		case D_CREATE_DESC:
		{
		    if(response)
		    {
				SetPVarString(playerid, "DescTitle", inputtext);
				
				ShowPlayerDialog(playerid, D_TEXT_DESC, DIALOG_STYLE_INPUT, " Treœæ opisu", "WprowadŸ treœæ opisu jaki ma zostaæ ustalony.", "Dalej", "Zamknij");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_TEXT_DESC:
		{
		    if(response)
		    {
		        new title[32];
		        new text[128];
		        new string[128];
		        
		        EscapePL(inputtext);
		        
				GetPVarString(playerid, "DescTitle", title, 32);
				format(text, sizeof(text), "%s", inputtext);

				mysql_query_format("INSERT INTO `fc_descriptions` VALUES (NULL, '%s', '%d', '%s')", title, CharacterCache[playerid][pUID], text);
				
				new uid = mysql_insert_id();
				
				DescInfo[uid][descID] = uid;
				DescInfo[uid][descChar] = CharacterCache[playerid][pUID];
				
				format(DescInfo[uid][descTitle], 32, "%s", title);
				format(DescInfo[uid][descText], 128, "%s", text);

				format(string, sizeof(string), "Opis (ID: %d) dla postaci zosta³ pomyœlnie stworzony.\n\nTytu³: %s", uid, title);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_USE_DESC:
		{
		    if(response)
	  		{
		        new desc_id = strval(inputtext);
		        
		        CharacterCache[playerid][pUseDesc] = desc_id;

				Update3DTextLabelText(CharacterCache[playerid][pDescTag], 0x7290C4FF, WordWrap(DescInfo[desc_id][descText], 5));
	
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Opis postaci zosta³ pomyœlnie w³¹czony.\nMo¿esz go wy³¹czyæ za pomoc¹ komendy /opis.", "Zamknij", "");
		    }
		    else
			{
		        return 1;
		    }
		}
		case D_USE_SUBGROUP:
		{
		    if(response)
		    {
		        new string[256],
					sub_id = strval(inputtext),
		            vehicleid = GetPVarInt(playerid, "VehicleChangeID");
		            
				VehicleInfo[vehicleid][vOwnerType] = OWNER_SUBGROUP;
				VehicleInfo[vehicleid][vOwner] = SubData[sub_id][sUID];
				
				format(string, sizeof(string), "Pomyœlnie przepisa³eœ pojazd na subgrupê %s (UID: %d).", SubData[sub_id][sDesc], SubData[sub_id][sUID]);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_DRUG_OUT:
		{
			if(response)
			{
			    new item_uid = strval(inputtext);
				new itemid = GetItemID(item_uid);
				new price = 0;
				new string[128];

			    if(!ItemInfo[itemid][iUID])
			    {
			        LoadItem(item_uid);
			    }

			    SetPVarInt(playerid, "SellDrug", itemid);

			    switch(ItemInfo[itemid][iType])
			    {
			        case TYPE_META:
			        {
			            price = 50;
			        }
			        case TYPE_MAR:
			        {
			            price = 90;
			        }
			        case TYPE_COCAINE:
			        {
			            price = 130;
			        }
			    }

			    SetPVarInt(playerid, "SellDrugPrice", price);

			    format(string, sizeof(string), "Czy chcesz sprzedaæ %s (UID: %d) dilerowi za cenê $%d ?", ItemInfo[itemid][iName], ItemInfo[itemid][iUID], price);
			    ShowPlayerDialog(playerid, D_DRUG_OUT_2, DIALOG_STYLE_MSGBOX, " Informacja", string, "Tak", "Nie");
			}
			else
			{
			    return 1;
			}
		}
		case D_DRUG_OUT_2:
		{
			if(response)
			{
				new itemid = GetPVarInt(playerid, "SellDrug");
				new price = GetPVarInt(playerid, "SellDrugPrice");

				DeleteItem(ItemInfo[itemid][iUID]);
				GivePlayerCash(playerid, price);
				
				CharacterCache[playerid][pSellDrug] ++;

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Narkotyk zosta³ pomyœlnie sprzedany.\nKwota trafi³a na Twoje konto.", "Zamknij", "");
			}
			else
			{
			    return 1;
			}
		}
		case D_ATTACH_USE:
		{
			new index = ItemInfo[PlayerItemIndex[playerid]][iUID];
			new data[64], value, value1, value2, use;

			mysql_query_format("SELECT `value`, `value1`, `value2`, `used` FROM `fc_items` WHERE `uid` = '%d'", index);
			
			mysql_store_result();
			mysql_fetch_row_format(data, "|");
			
		 	sscanf(data, "p<|>dddd", value, value1, value2, use);
		 	mysql_free_result();

			if(response)
			{
				new attach_type = value2, modelid = value1;
				switch(attach_type)
				{
				    case ATTACH_GLASSES:
				    {
		                if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_GLASSES) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie nosisz ju¿ jakieœ okulary, zdejmij je.", "Zamknij", "");
		                    return 1;
		                }
		                if(!use)
		                {
							if(CheckItemAttach(index))
							{
								new attach_id = CheckItemAttach(index);
								SetPlayerAttachedObject(playerid, SLOT_GLASSES, modelid, 2, AttachInfo[attach_id][afOffsetX], AttachInfo[attach_id][afOffsetY], AttachInfo[attach_id][afOffsetZ], AttachInfo[attach_id][afRotX], AttachInfo[attach_id][afRotY], AttachInfo[attach_id][afRotZ]);
							}
							else
							{
								SetPlayerAttachedObject(playerid, SLOT_GLASSES, modelid, 2);
							}

							mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
						}
						else
						{
						    PlayerItemIndex[playerid] = 0;
						    mysql_query_format("UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", index);
						    RemovePlayerAttachedObject(playerid, SLOT_GLASSES);
						}
					}
				    case ATTACH_CAP:
				    {
		      			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_HAT) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie nosisz ju¿ jak¹œ czapke (lub kask), zdejmij j¹.", "Zamknij", "");
		                    return 1;
		                }
		                if(!use)
		                {
		         			if(CheckItemAttach(index))
		                    {
		                        new attach_id = CheckItemAttach(index);
		                        SetPlayerAttachedObject(playerid, SLOT_HAT, modelid, 2, AttachInfo[attach_id][afOffsetX], AttachInfo[attach_id][afOffsetY], AttachInfo[attach_id][afOffsetZ], AttachInfo[attach_id][afRotX], AttachInfo[attach_id][afRotY], AttachInfo[attach_id][afRotZ]);
		                    }
		                    else
		                    {
			                    SetPlayerAttachedObject(playerid, SLOT_HAT, modelid, 2);
		                	}

		                    mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
						}
						else
						{
						    PlayerItemIndex[playerid] = 0;
						    mysql_query_format("UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", index);
						    RemovePlayerAttachedObject(playerid, SLOT_HAT);
						}
				    }
					case ATTACH_HELMET:
				    {
		      			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_HAT) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie nosisz ju¿ jak¹œ czapke (lub kask), zdejmij j¹.", "Zamknij", "");
		                    return 1;
		                }
		                if(!use)
		                {
		      				if(CheckItemAttach(index))
		                    {
		                        new attach_id = CheckItemAttach(index);
		                        SetPlayerAttachedObject(playerid, SLOT_HAT, modelid, 2, AttachInfo[attach_id][afOffsetX], AttachInfo[attach_id][afOffsetY], AttachInfo[attach_id][afOffsetZ], AttachInfo[attach_id][afRotX], AttachInfo[attach_id][afRotY], AttachInfo[attach_id][afRotZ]);
		                    }
		                    else
		                    {
			                    SetPlayerAttachedObject(playerid, SLOT_HAT, modelid, 2);
		                	}

		                    mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
						}
						else
						{
						    PlayerItemIndex[playerid] = 0;
						    mysql_query_format("UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", index);
						    RemovePlayerAttachedObject(playerid, SLOT_HAT);
						}
				    }
				    case ATTACH_CASE:
				    {
		   				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_CASE) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie trzymasz ju¿ walizke w rece.", "Zamknij", "");
		                    return 1;
		                }
		                if(!use)
		                {
		   					if(CheckItemAttach(index))
		                    {
		                        new attach_id = CheckItemAttach(index);
		                        SetPlayerAttachedObject(playerid, SLOT_CASE, modelid, 5, AttachInfo[attach_id][afOffsetX], AttachInfo[attach_id][afOffsetY], AttachInfo[attach_id][afOffsetZ], AttachInfo[attach_id][afRotX], AttachInfo[attach_id][afRotY], AttachInfo[attach_id][afRotZ]);
		                    }
		                    else
		                    {
			                    SetPlayerAttachedObject(playerid, SLOT_CASE, modelid, 5);
		                	}

		                    mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
						}
						else
						{
						    PlayerItemIndex[playerid] = 0;
						    mysql_query_format("UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", index);
						    RemovePlayerAttachedObject(playerid, SLOT_CASE);
						}
				    }
				    case ATTACH_PHONE:
				    {
		  				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_PHONE) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie trzymasz ju¿ walizke w rece.", "Zamknij", "");
		                    return 1;
		                }
		                if(!use)
		                {
		                	if(CheckItemAttach(index))
		                    {
		                        new attach_id = CheckItemAttach(index);
		                        SetPlayerAttachedObject(playerid, SLOT_PHONE, modelid, 6, AttachInfo[attach_id][afOffsetX], AttachInfo[attach_id][afOffsetY], AttachInfo[attach_id][afOffsetZ], AttachInfo[attach_id][afRotX], AttachInfo[attach_id][afRotY], AttachInfo[attach_id][afRotZ]);
		                    }
		                    else
		                    {
			                    SetPlayerAttachedObject(playerid, SLOT_PHONE, modelid, 6);
		                	}

		                    mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
						}
						else
						{
						    PlayerItemIndex[playerid] = 0;
						    mysql_query_format("UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", index);
						    RemovePlayerAttachedObject(playerid, SLOT_PHONE);
						}
				    }
				    case ATTACH_TIME:
				    {
		  				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_TIME) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie masz za³o¿ony zegarek, b¹dŸ bransolete.", "Zamknij", "");
		                    return 1;
		                }
		                if(!use)
		                {
		                	if(CheckItemAttach(index))
		                    {
		                        new attach_id = CheckItemAttach(index);
		                        SetPlayerAttachedObject(playerid, SLOT_TIME, modelid, 5, AttachInfo[attach_id][afOffsetX], AttachInfo[attach_id][afOffsetY], AttachInfo[attach_id][afOffsetZ], AttachInfo[attach_id][afRotX], AttachInfo[attach_id][afRotY], AttachInfo[attach_id][afRotZ]);
		                    }
		                    else
		                    {
			                    SetPlayerAttachedObject(playerid, SLOT_TIME, modelid, 5);
		                	}

		                    mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
						}
						else
						{
						    PlayerItemIndex[playerid] = 0;
						    mysql_query_format("UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", index);
						    RemovePlayerAttachedObject(playerid, SLOT_TIME);
						}
				    }
				}
			}
			else
			{
			    new attach_type = value2, modelid = value1;
				switch(attach_type)
				{
				    case ATTACH_GLASSES:
				    {
		                if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_GLASSES) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie nosisz ju¿ jakieœ okulary, zdejmij je.", "Zamknij", "");
		                    return 1;
		                }

		                SetPlayerAttachedObject(playerid, SLOT_GLASSES, modelid, 2);
						EditAttachedObject(playerid, SLOT_GLASSES);

						mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
					}
				    case ATTACH_CAP:
				    {
		      			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_HAT) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie nosisz ju¿ jak¹œ czapke (lub kask), zdejmij j¹.", "Zamknij", "");
		                    return 1;
		                }

			            SetPlayerAttachedObject(playerid, SLOT_HAT, modelid, 2);
			            EditAttachedObject(playerid, SLOT_HAT);

		                mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
				    }
					case ATTACH_HELMET:
				    {
		      			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_HAT) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie nosisz ju¿ jak¹œ czapke (lub kask), zdejmij j¹.", "Zamknij", "");
		                    return 1;
		                }

			            SetPlayerAttachedObject(playerid, SLOT_HAT, modelid, 2);
			            EditAttachedObject(playerid, SLOT_HAT);

		                mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
				    }
				    case ATTACH_CASE:
				    {
		   				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_CASE) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie trzymasz ju¿ walizke w rece.", "Zamknij", "");
		                    return 1;
		                }

			            SetPlayerAttachedObject(playerid, SLOT_CASE, modelid, 5);
			            EditAttachedObject(playerid, SLOT_CASE);

		                mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
				    }
				    case ATTACH_PHONE:
				    {
		  				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_PHONE) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie trzymasz ju¿ walizke w rece.", "Zamknij", "");
		                    return 1;
		                }

			            SetPlayerAttachedObject(playerid, SLOT_PHONE, modelid, 6);
			            EditAttachedObject(playerid, SLOT_PHONE);

		                mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
				    }
				    case ATTACH_TIME:
				    {
		  				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_TIME) && !use)
		                {
		                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Obecnie masz za³o¿ony zegarek, b¹dŸ bransolete.", "Zamknij", "");
		                    return 1;
		                }

			            SetPlayerAttachedObject(playerid, SLOT_TIME, modelid, 5);
			            EditAttachedObject(playerid, SLOT_TIME);

		                mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d'", index);
				    }
				}
			}
		}
		case D_PRODUCT_TYPE:
		{
			if(response)
			{
				new cat_id = strval(inputtext),
				    string[1024];

				SetPVarInt(playerid, "ProductCat", cat_id);

				ForeachEx(i, (TYPE_COUNT + 1))
		  		{
		        	format(string, sizeof(string), "%s\n%s", string, ItemTypeInfo[i][iTypeName]);
		   		}

				ShowPlayerDialog(playerid, D_PRODUCT_KIND, DIALOG_STYLE_LIST, " Informacja", string, "Wybierz", "Zamknij");
			}
			else
			{
				return 1;
			}
		}

		case D_PRODUCT_KIND:
		{
		    if(response)
			{
			    SetPVarInt(playerid, "ProductKind", listitem);

			    ShowPlayerDialog(playerid, D_PRODUCT_VALUE1, DIALOG_STYLE_INPUT, " Informacja", "WprowadŸ wartoœæ 1 dla tworzonego produktu.", "Wybierz", "Zamknij");
			}
			else
			{
			    return 1;
			}
		}

		case D_PRODUCT_VALUE1:
		{
		    if(response)
			{
			    new value1 = strval(inputtext);
			    SetPVarInt(playerid, "ProductValue1", value1);

			    ShowPlayerDialog(playerid, D_PRODUCT_VALUE2, DIALOG_STYLE_INPUT, " Informacja", "WprowadŸ wartoœæ 2 dla tworzonego produktu.", "Wybierz", "Zamknij");
			}
			else
			{
			    return 1;
			}
		}

		case D_PRODUCT_VALUE2:
		{
		    if(response)
			{
			    new value2 = strval(inputtext);
			    SetPVarInt(playerid, "ProductValue2", value2);

			    ShowPlayerDialog(playerid, D_PRODUCT_NAME, DIALOG_STYLE_INPUT, " Informacja", "WprowadŸ nazwê dla tworzonego produktu.", "Wybierz", "Zamknij");
			}
			else
			{
			    return 1;
			}
		}

		case D_PRODUCT_NAME:
		{
		    if(response)
			{
			    EscapePL(inputtext);
			    SetPVarString(playerid, "ProductName", inputtext);

			    ShowPlayerDialog(playerid, D_PRODUCT_GROUP, DIALOG_STYLE_INPUT, " Informacja", "WprowadŸ ID grupy dla tworzonego produktu.", "Wybierz", "Zamknij");
			}
			else
			{
			    return 1;
			}
		}

		case D_PRODUCT_GROUP:
		{
		    if(response)
			{
			    new groupid = strval(inputtext);
			    SetPVarInt(playerid, "ProductGroup", groupid);

			    if(!GroupData[groupid][UID])
			    {
			        ShowPlayerDialog(playerid, D_PRODUCT_GROUP, DIALOG_STYLE_INPUT, " Informacja", "Niepoprawne ID grupy!\n\nWprowadŸ ID grupy dla tworzonego produktu.", "Wybierz", "Zamknij");
			    }

			    ShowPlayerDialog(playerid, D_PRODUCT_CASH, DIALOG_STYLE_INPUT, " Informacja", "WprowadŸ cenê dla tworzonego produktu.", "Wybierz", "Zamknij");
			}
			else
			{
			    return 1;
			}
		}

		case D_PRODUCT_CASH:
		{
		    if(response)
			{
			    new cash = strval(inputtext),
			    	groupid = GetPVarInt(playerid, "ProductGroup"),
			    	catid = GetPVarInt(playerid, "ProductCat"),
			    	kind = GetPVarInt(playerid, "ProductKind"),
			    	value1 = GetPVarInt(playerid, "ProductValue1"),
					value2 = GetPVarInt(playerid, "ProductValue2"),
					name[32],
					string[1024];

				GetPVarString(playerid, "ProductName", name, 32);

			    if(cash < 0)
			    {
			        cash = 0;
			    }

				mysql_query_format("INSERT INTO `fc_orders_products` VALUES (NULL, '%d', '%d', '%d', '%d', '%d', '%s', '%d')", catid, kind, value1, value2, cash, name, GroupData[groupid][UID]);

				format(string, sizeof(string), "{008000}Produkt stworzony!\n\n{FFFFFF}Nazwa: %s\n{FFFFFF}Wartoœæ 1: %d\n{FFFFFF}Wartoœæ 2: %d\n{FFFFFF}Cena: %d\n{FFFFFF}Typ: %s\n\n{FFFFFF}Grupa: %s\n\n{FFFFFF}Pojawi siê on w magazynie, w ci¹gu 5 minut.", name, value1, value2, cash, ItemTypeInfo[kind][iTypeName], GroupData[groupid][Desc]);
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}
			else
			{
			    return 1;
			}
		}
		case D_REWRITE_DOOR:
		{
			if(response)
			{
				new doorid = strval(inputtext);
				new string[256];
				if(!doorid) return 1;

				DoorInfo[doorid][dOwnerType] = OWNER_HOUSE;
				DoorInfo[doorid][dOwner] = DoorInfo[doorid][dUID];
				
				SaveDoors(doorid);

				mysql_query_format("INSERT INTO `fc_member_door` VALUES ('%d', '%d', '%s', '%d', '%d')", DoorInfo[doorid][dUID], PERM_HOUSE_LEADER, "Wlasciciel", 0, CharacterCache[playerid][pUID]);

				LoadPlayerHouse(playerid);

				format(string, sizeof(string), "Drzwi %s (ID: %d) zosta³y uczynione mieszkaniem.", DoorInfo[doorid][dName], DoorInfo[doorid][dUID]);
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
			}
			else
			{
			    return 1;
			}
		}
		case D_PRIV_MSG:
		{
			if(response)
			{
			    if(ComparisonString(CharacterCache[playerid][pKey], inputtext))
			    {
			        new giveplayer_id = CharacterCache[playerid][pPrivTo];
			        new text[128];
					new string[256];
					
					format(text, 128, "%s", CharacterCache[playerid][pPrivMess]);

					if(CharacterCache[playerid][pAdmin] > 0 && CharacterCache[playerid][pAdmin] < 6 && CharacterCache[playerid][pAdminDuty])
					{
				    	format(string, sizeof(string), "(( « Assistance %s : %s ))", AssCode(playerid), text);
				    }
				    else
				    {
				    	format(string, sizeof(string), "(( « %s [%d]: %s ))", PlayerName2(playerid), playerid, text);
				    }

				    SendClientMessage(giveplayer_id, COLOR_GOT_PW, string);

					if(CharacterCache[giveplayer_id][pAdmin] > 0 && CharacterCache[giveplayer_id][pAdmin] < 6 && CharacterCache[giveplayer_id][pAdminDuty])
					{
						format(string, sizeof(string), "(( » Assistance %s : %s ))", AssCode(giveplayer_id), text);
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

				    CharacterCache[playerid][pKey] = 0;
				    CharacterCache[playerid][pPrivTo] = INVALID_PLAYER_ID;
				    CharacterCache[playerid][pPrivMess] = 0;
				}
				else
				{
				    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Wprowadzony token administracyjny jest niepoprawny.\nSpróbuj ponownie napisaæ wiadomoœæ.", "Zamknij", "");
				    return 1;
				}
			}
			else
			{
			    return 1;
			}
		}
		case D_BURGER_BUY:
		{
		    if(response)
		    {
		        new price, food, name[32], string[128];
		        
		        switch(listitem)
		        {
		            case 0:
					{
						price = 10;
						food = 20;
						format(name, sizeof(name), "Moo Kids Meal (J)");
					}
		            case 1:
					{
						price = 25;
						food = 50;
						format(name, sizeof(name), "Beef Tower (J)");
					}
		            case 2:
					{
						price = 50;
						food = 70;
						format(name, sizeof(name), "Meet Stack (J)");
					}
		            case 3:
					{
						price = 25;
						food = 50;
						format(name, sizeof(name), "Salad Meal (J)");
					}
		            case 4:
					{
						price = 10;
						food = 20;
						format(name, sizeof(name), "Cluckin Little Meal (J)");
					}
		            case 5:
					{
						price = 25;
						food = 50;
						format(name, sizeof(name), "Cluckin Big Meal (J)");
					}
		            case 6:
					{
						price = 50;
						food = 70;
						format(name, sizeof(name), "Cluckin Huge Meal (J)");
					}
		            case 7:
					{
						price = 50;
						food = 70;
						format(name, sizeof(name), "Big Salad Meal (J)");
					}
		        }
		        
		        if(CharacterCache[playerid][pCash] < price)
		        {
		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie posiadasz przy sobie tyle gotówki by zamówiæ produkt.", "Zamknij", "");
		            return 1;
		        }
		        
		        CreatePlayerItem(playerid, name, TYPE_FOOD, food, 0, 1);
		        
		        GivePlayerCash(playerid, -price);
		        
		        GroupData[GetGroupKind(GROUP_GOV)][Cash] += price;
		        SaveGroup(GetGroupKind(GROUP_GOV));
		        
		        format(string, sizeof(string), "Produkt zosta³ zakupiony!\nPomyœlnie kupi³eœ zestaw %s za cenê $%d.", name, price);
		        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
		    }
		    else
		    {
		        return 1;
		    }
		}
		case D_CHOOSE_BURGER:
		{
			if(response)
			{
			    AddBurger(playerid);
			    
			    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Miejsce z jedzeniem zosta³o stworzone.", "Zamknij", "");
			}
			else
			{
			    return 1;
			}
  		}
  		case D_HELP:
  		{
  		    switch(listitem)
  		    {
  		        case 1: // Administrator - Komendy
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Dostêp do komend administratorskich zosta³ wy³¹czony.", "Zamknij", "");
  		        }
  		        case 3: // Informacje - Administracja
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Administrator ma obowi¹zek niesienia pomocy graczowi w momencie s³u¿by.\nW przypadku gdy nie znajduje siê on na s³u¿bie nie posiada takiego obowi¹zku.\n\nW trakcie s³u¿by Assistance jest chroniony poprzez skrypt, aby zadbaæ o jego anonimowoœæ.\nAdministrator mo¿e odmówiæ pomocy osobie, która nie wyra¿a chêci wspó³pracy.\nKontakt z administratorem odbywa siê poprzez /report oraz /w.", "Zamknij", "");
  		        }
  		        case 5: // Grupy - Zarz¹dzanie
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zarz¹dzanie grupami odbywa siê za pomoc¹ komend /g {slot} [zaproœ, wyproœ, wyp³aæ, wp³aæ, magazyn].\nKomendy udostêpnione s¹ dla ka¿dego z liderów grupy.\n\nAktualizacje grupy dokonuj¹ siê zawsze podczas logowania pracownika na serwer.\nPodstaowe ustawienia serwerowe ³adowane s¹ o pe³nej godzinie.", "Zamknij", "");
  		        }
  		        case 6: // Grupy - Zastosowanie
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Grupy pozwalaj¹ na dostêp do dodatkowych systemów przypisanych pod typ grupowy.\nGrupy posiadaj¹ce odpowiednie flagi maj¹ przypisane dodatkowe uprawnienia.\n\nListê wszystkich flag mo¿na zauwa¿yæ w panelu grupowym, dostêpnym na stronie.", "Zamknij", "");
  		        }
  		        case 8: // Pojazdy - Zarz¹dzanie
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zarz¹dzanie pojazdami odbywa siê poprzez komendê /pojazd.\nGdy znajdujemy siê w pojeŸdzie jesteœmy w stanie operowaæ danymi dotycz¹cymi danego pojazdu.\n\nGdy znajdujemy siê poza nim mamy mo¿liwoœæ operowania swoj¹ list¹ pojazdów przypisanych do konta.", "Zamknij", "");
  		        }
  		        case 9: // Pojazdy - Kupno
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Kupno pojazdu mo¿liwe jest w salonach samochodowych, które prowadzone s¹ przez graczy.\nAby dokonaæ zakupu w grze musi byæ aktywny pracownik grupy.\n\nKontakt z pracownikiem mo¿e odbyæ siê za pomoc¹ telefonu (/call 555).\nOsoby posiadaj¹ce konto premium maj¹ mo¿liwoœæ wybrania koloru pojazdu w trakcie zakupu.", "Zamknij", "");
  		        }
  		        case 10: // Pojazdy - Mo¿liwoœci
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zak³adka zosta³a tymczasowo zablokowana.", "Zamknij", "");
  		        }
  		        case 11: // Pojazdy - Tuning
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Tuningowanie pojazdu mo¿liwe jest w warsztatach grupowych.\nZnajduj¹ siê tam czêsci, które s¹ powszechnie legalne.\n\nTuning nielegalny mo¿liwy jest do zdobycia u grup zmotoryzowanych.\nPosiadanie owego tuningu mo¿e wi¹zaæ siê z zarekwirowaniem pojazdu lub jego odebraniem.", "Zamknij", "");
  		        }
  		        case 12: // Pojazd - Zabezpieczenie
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zakupuj¹c pojazd ka¿da z osób jest w stanie nabyæ odpowiednie zabezpieczenie.\nZabezpieczenia dostêpne s¹ w warsztatach samochodowych.\nMo¿liwy jest zakup alarmów, lub immobilizerów.", "Zamknij", "");
  		        }
  		        case 14: // Przedmioty - Zarz¹dzanie
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zarz¹dzanie przedmiotami odbywa siê za pomoc¹ komendy /p(rzedmiot).\nUdostêpnione zosta³y opcje schowania przedmiotu do schowka drzwi, informacji o nim lub od³o¿eniu.\n\nNiektóre z przedmiotów nie posiadaj¹ mo¿liwoœci od³o¿enia lub nie mo¿na ich podnieœæ.\nPrzedmioty mog¹ posiadaæ tak¿e nadane flagi (typu: brak obra¿eñ), które dostêpne s¹ w informacjach.", "Zamknij", "");
  		        }
  		        case 16: // Strefy - Kupno
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Zak³adka zosta³a tymczasowo zablokowana.", "Zamknij", "");
  		        }
  		        case 17: // Strefy - Dzia³anie
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Strefy daj¹ mo¿liwoœæ graczowi budowania w³asnych obiektów w œwiecie g³ównym (tzw. VW 0).\nMo¿liwe jest ich odpisanie z konta, gdy aktualnie s¹ do niego przypisane.\n\nOdœwie¿enie stref nastêpuje o pe³nych godzinach.", "Zamknij", "");
  		        }
  		        case 18: // Strefy - Przejmowanie
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Przejmowanie stref grupowych odbywa siê podczas tworzenia drzwi.\nGdy drzwi znajduj¹ siê na strefie neutralnej zostaje ona przepisana na dan¹ osobê.\n\nOsoba ma mo¿liwoœæ odpisania strefy poprzez dostêpny panel na forum.", "Zamknij", "");
  		        }
  		        case 20: // Gracz - Oferty
  		        {
  		            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Listê aktywnych ofert ka¿dy z graczy otrzymuje po wpisaniu /o(feruj).\nW czasie wejœcia na s³u¿bê w danej grupie pojawiaj¹ siê nowe z opcji.\nKa¿da z tych opcji przypisana jest pod dany typ grupy.", "Zamknij", "");
  		        }
  		        case 21: // Gracz - Darowanie
				{
                    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Przekazywanie gotówki jest stale monitorowane przez system.\nW przypadku wykrycia nieprawid³owoœci konto mo¿e zostaæ zablokowane przez system.\n\nLogi konta dostêpne s¹ dla u¿ytkowników posiadaj¹cych konto premium.", "Zamknij", "");
				}
				case 22: // Gracz - Zg³aszanie
				{
				    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Wa¿ne zasady:\n\t1. Pamiêtaj o zachowaniu kultury wobec administratora.\n\t2. Inni gracze te¿ potrzebuj¹ pomocy - oczekuj w spokoju.\n\t3. Wysy³anie ci¹g³ych zg³oszeñ nie przyœpieszy czasu realizacji.", "Zamknij", "");
				}
  		    }
  		}
    }
    return 1;
}