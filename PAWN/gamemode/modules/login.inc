forward CheckAccount(playerid);
forward OnPlayerLogin(playerid, charid);
forward ClearCache(playerid);

public CheckAccount(playerid)
{
    new name[32];
    GetPlayerName(playerid, name, sizeof(name));

    new query[256];
    format(query, sizeof(query), "SELECT `global_uid` FROM `fc_characters` WHERE `name` = '%s'", name);
    mysql_check(); mysql_query(query);

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

public OnPlayerLogin(playerid, charid)
{
    PlayerTextDrawHide(playerid, Panorama1[playerid]);
    PlayerTextDrawHide(playerid, Panorama2[playerid]);

    new query[512],
        last_online,
        logged,
        in_game,
        hide,
        data[64];

    format(query, sizeof(query), "SELECT * FROM `fc_characters` WHERE `player_uid` = '%d' LIMIT 1", charid);
    mysql_check(); mysql_query(query);

    mysql_store_result();
    if(mysql_num_rows())
    {
        mysql_fetch_row_format(query);
        sscanf(query,  "p<|>dds[24]ddddddddfdddddddddfffddddddddddddddddddd",  		CharacterCache[playerid][pUID],
							                                                        CharacterCache[playerid][pGID],
							                                                        CharacterCache[playerid][pNick],
							                                                        CharacterCache[playerid][pAge],
							                                                        CharacterCache[playerid][pSex],
							                                                        CharacterCache[playerid][pCash],
							                                                        CharacterCache[playerid][pHours],
							                                                        CharacterCache[playerid][pMinutes],
							                                                        CharacterCache[playerid][pSkin],
							                                                        CharacterCache[playerid][pBW],				// 10
							                                                        CharacterCache[playerid][pAJ],
							                                                        CharacterCache[playerid][pHealth],
							                                                        CharacterCache[playerid][pJob],
							                                                        CharacterCache[playerid][pBlock],
							                                                        last_online,
							                                                        logged,
							                                                        in_game,
							                                                        hide,
							                                                        CharacterCache[playerid][pTog],
							                                                        CharacterCache[playerid][pOption],			// 20
							                                                        CharacterCache[playerid][pEditor],
							                                                        CharacterCache[playerid][pPos][0],
							                                                        CharacterCache[playerid][pPos][1],
							                                                        CharacterCache[playerid][pPos][2],
							                                                        CharacterCache[playerid][pVW],
							                                                        CharacterCache[playerid][pInt],
																					CharacterCache[playerid][pCredit],
																					CharacterCache[playerid][pInsurance],
																					CharacterCache[playerid][pStr],
																					CharacterCache[playerid][pGun],				// 30
																					CharacterCache[playerid][pVehicle],
																					CharacterCache[playerid][pFish],
																					CharacterCache[playerid][pDocument],
																					CharacterCache[playerid][pPhone],
																					CharacterCache[playerid][pLastSkin], //
																					CharacterCache[playerid][pDrugs],
																					CharacterCache[playerid][pDrugsTime],
																					CharacterCache[playerid][pSellDrug],
																					CharacterCache[playerid][pJailTime],
																					CharacterCache[playerid][pJailID],			// 30
																					CharacterCache[playerid][pPenaltyPoints],
																					CharacterCache[playerid][pPermit],
																					CharacterCache[playerid][pFood]);
        mysql_free_result();

		if(CharacterCache[playerid][pBlock] & BLOCK_CHAR || CharacterCache[playerid][pBlock] & BLOCK_BAN)
		{
			// Sprawdzanie poprawnoœci konta
	        if(CharacterCache[playerid][pBlock] & BLOCK_CHAR)
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Twoje konto zosta³o permanentnie zablokowane lub uœmiercone.\nJe¿eli uwa¿asz, ¿e jest to b³¹d - skontaktuj siê z administratorem.", "Zamknij", "");
	            KickWithWait(playerid);
	        }

	        if(CharacterCache[playerid][pBlock] & BLOCK_BAN)
	        {
	            ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Twoje konto zosta³o permanentnie zbanowane.\nJe¿eli uwa¿asz, ¿e jest to b³¹d - skontaktuj siê z administratorem.", "Zamknij", "");
	            KickWithWait(playerid);
	        }
		}
		else
		{
			// Aktualizowanie danych logowania
	        mysql_check();
			mysql_query_format("UPDATE `fc_characters` SET `logged` = '1', `in_game` = '%d' WHERE `player_uid` = '%d'", gettime(), CharacterCache[playerid][pUID]);

			// Wczytywanie informacji OOC
			mysql_check();
			mysql_query_format("SELECT `members_display_name`, `score`, `admin`, `permission`, `premium` FROM `ipb_members` WHERE `member_id` = '%d'", CharacterCache[playerid][pGID]);

			mysql_store_result();

			while(mysql_fetch_row_format(data, "|") == 1)
			{
				sscanf(data,  "p<|>s[32]dddd", CharacterCache[playerid][pGlobalNick], CharacterCache[playerid][pGlobalScore], CharacterCache[playerid][pAdmin], CharacterCache[playerid][pAdminPermission], CharacterCache[playerid][pPremium]);
			}

			mysql_free_result();

			// Ustawianie specyfikacji logowania / spawnu
	        SetSpawnInfo(playerid, 0, CharacterCache[playerid][pLastSkin], 1225.4353, 362.1379, 19.5547, 245.9456, -1, -1, -1, -1, -1, -1);
	        TogglePlayerSpectating(playerid, false);

			// Sprawdzanie opcji gracza
	        if(!(CharacterCache[playerid][pTog] & TOG_NAME))
	        {
	            PlayerTextDrawShow(playerid, IRPName[playerid]);
	        }

	        if(!(CharacterCache[playerid][pTog] & TOG_FM))
	        {
	            PlayerTextDrawShow(playerid, RadioFM[playerid]);
	        }

	        if(CharacterCache[playerid][pOption] & OPTION_PANORAMIC)
	        {
	            PlayerTextDrawShow(playerid, Panorama1[playerid]);
	    		PlayerTextDrawShow(playerid, Panorama2[playerid]);
	        }

	        // Generacja tekstu dla administratora
	        if(CharacterCache[playerid][pAdmin] == 9)
	        {
	            PlayerTextDrawSetString(playerid, AdminDuty[playerid], "~r~~h~~h~~h~ADM ~>~ ~w~T/~r~N");
	            PlayerTextDrawShow(playerid, AdminDuty[playerid]);
	        }
	        else if(CharacterCache[playerid][pAdmin] > 5 && CharacterCache[playerid][pAdmin] < 9)
	        {
	            PlayerTextDrawSetString(playerid, AdminDuty[playerid], "~g~~h~~h~~h~ADM ~>~ ~w~T/~r~N");
	            PlayerTextDrawShow(playerid, AdminDuty[playerid]);
	        }
	        else if(CharacterCache[playerid][pAdmin] < 6 && CharacterCache[playerid][pAdmin] > 0)
	        {
	            PlayerTextDrawSetString(playerid, AdminDuty[playerid], "~b~~h~~h~~h~SUPP ~>~ ~w~T/~r~N");
	            PlayerTextDrawShow(playerid, AdminDuty[playerid]);
	        }
	        else
	        {
	            PlayerTextDrawHide(playerid, AdminDuty[playerid]);
	        }

	        // Aktualizacja narkotyków
	        DrugsBar[playerid] = CreatePlayerProgressBar(playerid, 548.0, 42.0, 59.0, 5.0, 0x1F51ADFF, 100.0);

	        if(CharacterCache[playerid][pDrugsTime] > 0)
			{
				ShowPlayerProgressBar(playerid, DrugsBar[playerid]);

	            SetPlayerProgressBarValue(playerid, DrugsBar[playerid], CharacterCache[playerid][pDrugsTime]);
		    	UpdatePlayerProgressBar(playerid, DrugsBar[playerid]);

				OnPlayerUseDrug(playerid);
			}
	        else HidePlayerProgressBar(playerid, DrugsBar[playerid]);

            // Aktualizacja g³odu
	        FoodBar[playerid] = CreatePlayerProgressBar(playerid, 548.0, 55.0, 59.0, 5.0, 0xE0D3B6FF, 100.0);
	        ShowPlayerProgressBar(playerid, FoodBar[playerid]);

	        SetPlayerProgressBarValue(playerid, FoodBar[playerid], CharacterCache[playerid][pFood]);
			UpdatePlayerProgressBar(playerid, FoodBar[playerid]);

			// Ustawianie HP i score
	        SetPlayerScore(playerid, CharacterCache[playerid][pGlobalScore]);
	        SetPlayerHealth(playerid, CharacterCache[playerid][pHealth]);

	        // Ustawianie czasu
	        new godzina, minuta;
		    gettime(godzina, minuta);

		    SetPlayerTime(playerid, godzina + 1, 0);
		    SetPlayerWeather(playerid, 1);

			// Generowanie premium
			if(IsPlayerPremium(playerid))
			{
			    new name[32];
			    format(name, sizeof(name), "%s*", PlayerName(playerid));

			    SetPlayerName(playerid, name);

			    CharacterCache[playerid][pNickColor] = 0xFCDF1E99;
			    SetPlayerColor(playerid, 0xA0CC47FF);
			}
			else
			{
			    SetPlayerColor(playerid, 0x7FAB27FF);
				CharacterCache[playerid][pNickColor] = 0xFFFFFF99;
	  		}

	        format(CharacterCache[playerid][pIP], 16, "%s", GetAccountIP(playerid));

			// Nicki 3D
	  		Attach3DTextLabelToPlayer(NameTags[playerid], playerid, 0.0, 0.0, 0.2);
	  		Attach3DTextLabelToPlayer(CharacterCache[playerid][pDescTag], playerid, 0.0, 0.0, -0.6);

	        UpdatePlayer3DTextNick(playerid);
	        RemovePlayerBuild(playerid);
	        ReloadAnims(playerid);

	        // £adowanie specyfikacji
	        LoadPlayerGroup(playerid);
	        LoadPlayerItems(playerid);
	        LoadPlayerVehicles(playerid);
	        LoadPlayerDescs(playerid);
	        LoadPlayerHouse(playerid);

			// Aktualizacja gotówki
	        ResetPlayerMoney(playerid);
	        GivePlayerMoney(playerid, CharacterCache[playerid][pCash]);
	        CancelSelectTextDraw(playerid);

			// Chowanie TD
			PlayerTextDrawHide(playerid, AdminInfo[playerid]);

			// Pokazywanie TD
			TextDrawShowForAll(Icons);

			// Od³aduj aktywne
			mysql_query_format("UPDATE `fc_items` SET `used` = 0 WHERE `ownertype` = '%d' AND `owner` = '%d'", OWNER_PLAYER, CharacterCache[playerid][pUID]);

			// £adowanie przedmiotów gracza
			if(CharacterCache[playerid][pPhone])
			{
			    mysql_query_format("UPDATE `fc_items` SET `used` = 1 WHERE `uid` = '%d' AND `ownertype` = '%d' AND `owner` = '%d'", CharacterCache[playerid][pPhone], OWNER_PLAYER, CharacterCache[playerid][pUID]);
			}

			// Informacje startowe
	        new first_string[256];
	        format(first_string, sizeof(first_string), "Witaj, {88CC54}%s (GID: %d){FFFFFF}. Zosta³eœ zalogowany na postaæ {88CC54}%s (UID: %d){FFFFFF}. ¯yczymy mi³ej gry!", CharacterCache[playerid][pGlobalNick], CharacterCache[playerid][pGID], PlayerName2(playerid), CharacterCache[playerid][pUID]);
	        SendClientMessage(playerid, -1, first_string);

	        // Informacja o premium
	        if(IsPlayerPremium(playerid)) SendClientMessage(playerid, 0xFCDF1EFF, "Posiadasz aktywne konto premium. Dziêkujemy za wsparcie dla projektu.");

	        // Informorwanie admnistracji
	        if(CharacterCache[playerid][pAdmin])
			{
	   			SendAdminMessageFormat(0xD96A6AFF, "[AI] %s (ID: %d) zalogowa³ siê do gry.", PlayerName2(playerid), playerid);
			}

			// Informorwanie admnistracji
	        if(CharacterCache[playerid][pAdmin] == 9)
			{
	   			SendClientMessage(playerid, COLOR_GREEN, "(Licencja) Licencja oprogramowania wygasa: 30/04/2014 13:00.");
			}

			// Ikony ³owienia
	        SetPlayerMapIcon(playerid, 0, 1426.8884, 499.9664, 1.0215, 9, 0, MAPICON_LOCAL);
	        SetPlayerMapIcon(playerid, 1, -420.8112, 1163.5447, 1.8502, 9, 0, MAPICON_LOCAL);
	        SetPlayerMapIcon(playerid, 2, 2103.7791, -103.5335, 2.2457, 9, 0, MAPICON_LOCAL);

	        // Ikona magazynu
			SetPlayerMapIcon(playerid, 3, SettingInfo[sMagazineX], SettingInfo[sMagazineY], SettingInfo[sMagazineZ], 51, 0, MAPICON_GLOBAL);

			// Przestêpcza
			if(IsPlayerKindGroup(playerid, GROUP_SYNDYCATE))
			{
			    // Ikona magazynu przestêpczego
				SetPlayerMapIcon(playerid, 4, 259.8107, -302.6047, 1.9184, 56, 0, MAPICON_GLOBAL);
			}

		   // £adowanie stref dla gracza

   			ForeachEx(i, MAX_AREAS)
			{
				if(AreaInfo[i][aOwnerType] == OWNER_GROUP)
			    {
			        new groupid = AreaInfo[i][aOwner];
			        new color = GroupData[groupid][Chat][0] << 24 | GroupData[groupid][Chat][1] << 16 | GroupData[groupid][Chat][2] << 8 | 0x66;

                    GangZoneShowForAll(AreaInfo[i][aGangID], color);
			    }
			}

			// Informacje z dnia
	  		new string[1024];

	        format(string, sizeof(string), "{C0C0C0}Je¿eli potrzebujesz pomocy u¿yj komendy /pomoc.");
	        format(string, sizeof(string), "%s\n{C0C0C0}Znajdziesz tam informacje, które pomog¹ Ci w dalszej grze.", string);

	  		format(string, sizeof(string), "%s\n{C0C0C0}-----", string);

	    	format(string, sizeof(string), "%s\nStan portfela:\t\t$%d", string, CharacterCache[playerid][pCash]);
	    	format(string, sizeof(string), "%s\nStan konta:\t\t$%d", string, CharacterCache[playerid][pBankCash]);

	    	format(string, sizeof(string), "%s\n{C0C0C0}-----", string);

	    	format(string, sizeof(string), "%s\nKurs paliwa:\t\t{FFC675}$%d za litr", string, SettingInfo[sFuel]);
	    	format(string, sizeof(string), "%s\nRyby s³odkowodne:\t$%d", string, SettingInfo[sFishSweet]);
	    	format(string, sizeof(string), "%s\nRyby s³onowodne:\t$%d", string, SettingInfo[sFishSalt]);

	    	format(string, sizeof(string), "%s\n{C0C0C0}-----", string);

	    	format(string, sizeof(string), "%s\nDowód osobisty:\t$%d", string, SettingInfo[sDocID]);
	    	format(string, sizeof(string), "%s\nPrawo jazdy:\t\t$%d", string, SettingInfo[sDocDriver]);
	    	format(string, sizeof(string), "%s\nKarta rybacka:\t\t$%d", string, SettingInfo[sDocFish]);
	    	format(string, sizeof(string), "%s\nPaszport:\t\t$%d", string, SettingInfo[sDocPassport]);
	    	format(string, sizeof(string), "%s\nRejestracja pojazdu:\t$%d", string, SettingInfo[sDocRegister]);
	    	format(string, sizeof(string), "%s\nLicencja na broñ:\t$%d", string, SettingInfo[sDocLicense]);
	    	format(string, sizeof(string), "%s\nNiekaralnoœæ:\t\t$%d", string, SettingInfo[sDocPolice]);
	    	format(string, sizeof(string), "%s\nMetryczka zdrowia:\t$%d", string, SettingInfo[sDocMedical]);
	    	format(string, sizeof(string), "%s\nZasi³ek:\t\t\t$%d", string, SettingInfo[sBenefit]);

	    	format(string, sizeof(string), "%s\n{C0C0C0}-----", string);

	    	format(string, sizeof(string), "%s\nNadanych dziœ kar:\t%d {ff8282}(w tym %d banów)", string, PenaltyAll, PenaltyBan);

	    	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, "Informacje z dnia [www.in-rp.net]", string, "Zamknij", "");
    	}
    }
    return 1;
}

public ClearCache(playerid)
{
    CharacterCache[playerid][loginGID] = 0;
    CharacterCache[playerid][pGID] = 0;
    CharacterCache[playerid][pUID] = 0;
    CharacterCache[playerid][pNick] = 0;
    CharacterCache[playerid][pAge] = 0;
    CharacterCache[playerid][pSex] = 0;
    CharacterCache[playerid][pCash] = 0;
    CharacterCache[playerid][pHours] = 0;
    CharacterCache[playerid][pMinutes] = 0;
    CharacterCache[playerid][pSkin] = 0;
    CharacterCache[playerid][pBW] = 0;
    CharacterCache[playerid][pAJ] = 0;
    CharacterCache[playerid][pHealth] = 0;
    CharacterCache[playerid][pJob] = 0;
    CharacterCache[playerid][pBankCash] = 0;
    CharacterCache[playerid][pBankNumber] = 0;
    CharacterCache[playerid][pBlock] = 0;
    CharacterCache[playerid][pCredit] = 0;
    CharacterCache[playerid][pInsurance] = 0;
    CharacterCache[playerid][pLastSkin] = 0;
    CharacterCache[playerid][pFood] = 0;
    
    CharacterCache[playerid][pMask] = false;
    CharacterCache[playerid][pPhone] = 0;
    
    CharacterCache[playerid][pPermit] = 0;
    
    CharacterCache[playerid][pStr] = 0;
	CharacterCache[playerid][pGun] = 0;
	CharacterCache[playerid][pVehicle] = 0;
	CharacterCache[playerid][pFish] = 0;
	
	CharacterCache[playerid][pKey] = 0;
 	CharacterCache[playerid][pPrivTo] = INVALID_PLAYER_ID;
	CharacterCache[playerid][pPrivMess] = 0;

	CharacterCache[playerid][pTaxiVeh] = INVALID_VEHICLE_ID;
	CharacterCache[playerid][pTaxiPay] = 0;
	CharacterCache[playerid][pTaxiPrice] = 0;
	CharacterCache[playerid][pTaxiPassenger] = INVALID_PLAYER_ID;
    CharacterCache[playerid][pTaxiGroup] = 0;

    CharacterCache[playerid][pAdminPermission] = 0;
    CharacterCache[playerid][pAdmin] = 0;
    
    CharacterCache[playerid][pVehicleWarring] = 0;
    
	CharacterCache[playerid][pJailTime] = 0;
	CharacterCache[playerid][pJailID] = 0;
		
	CharacterCache[playerid][pBusStatus] = BUS_NONE;
	CharacterCache[playerid][pBusTarget] = 0;
	CharacterCache[playerid][pBusTime] = 0;
	
	CharacterCache[playerid][pSensor] = 0;
	CharacterCache[playerid][pArea] = 0;
	
	CharacterCache[playerid][pPenaltyPoints] = 0;
	
	CharacterCache[playerid][pBusPos][0] = 0;
	CharacterCache[playerid][pBusPos][1] = 0;
	CharacterCache[playerid][pBusPos][2] = 0;
	
 	CharacterCache[playerid][pDetect] = false;
    CharacterCache[playerid][pDetectNumber] = 0;
	CharacterCache[playerid][pDetectPlayerID] = INVALID_PLAYER_ID;
	CharacterCache[playerid][pDetectProgress] = 0;
	
    CharacterCache[playerid][pWorek] = false;
    CharacterCache[playerid][pKnebel] = false;
    
    CharacterCache[playerid][pCuffed] = INVALID_PLAYER_ID;
	CharacterCache[playerid][pCarSpawned] = 0;
	
	CharacterCache[playerid][pWater] = 0;
	CharacterCache[playerid][pBait] = 0;
	
	CharacterCache[playerid][pFished] = 0;
	CharacterCache[playerid][pFishTaking] = false;
	CharacterCache[playerid][pFishingRodUID] = 0;
    
    CharacterCache[playerid][pAFKTime] = 0;
    
    CharacterCache[playerid][pMove3DText] = 0;
	CharacterCache[playerid][pMove3DTextPhase] = PHASE_NONE;
    
    CharacterCache[playerid][pRepair] = 0;
	CharacterCache[playerid][pRepairVehicle] = 0;
	
	CharacterCache[playerid][pUseDesc] = 0;
	CharacterCache[playerid][pSellDrug] = 0;
	
	CharacterCache[playerid][pDrugs] = 0;
	CharacterCache[playerid][pDrugsTime] = 0;

	CharacterCache[playerid][pParalizeTime] = 0;
	
    CharacterCache[playerid][pSpecPos][0] = 0;
    CharacterCache[playerid][pSpecPos][1] = 0;
    CharacterCache[playerid][pSpecPos][2] = 0;
    CharacterCache[playerid][pSpecVW] = 0;
    CharacterCache[playerid][pSpecInt] = 0;

    CharacterCache[playerid][pLastW] = INVALID_PLAYER_ID;
    CharacterCache[playerid][pOption] = 0;
    CharacterCache[playerid][pTog] = 0;
    CharacterCache[playerid][pEditor] =0;
    
    CharacterCache[playerid][pShowInfoOffer] = false;
    
    CharacterCache[playerid][pDutyJob] = false;
    CharacterCache[playerid][pDutyJobTime] = 0;

    CharacterCache[playerid][pGroupFlag] = 0;
    CharacterCache[playerid][pStatus] = 0;
    CharacterCache[playerid][pAFK] = 5;
    
    CharacterCache[playerid][pVehicleThief] = 0;
    CharacterCache[playerid][pVehicleThiefID] = 0;

    CharacterCache[playerid][pReport] = 0;
    
    CharacterCache[playerid][pBlockPlayer] = INVALID_PLAYER_ID;
    CharacterCache[playerid][pTakeDamage] = 0;

    CharacterCache[playerid][pAreaPos1] = 0;
    CharacterCache[playerid][pAreaPos2] = 0;

    CharacterCache[playerid][pShowGroups] = 0;
    CharacterCache[playerid][pShowDoors] = 0;

    CharacterCache[playerid][pNickColor] = 0xFFFFFF99;
    CharacterCache[playerid][pAdminDuty] = false;

    CharacterCache[playerid][pGlobalNick] = 0;
    CharacterCache[playerid][pGlobalScore] = 0;

    CharacterCache[playerid][pShowInfoText] = 0;
    CharacterCache[playerid][pGroupFlag] = 0;

    CharacterCache[playerid][pRobbery] = 0;
    CharacterCache[playerid][pRobberyID] = 0;

    CharacterCache[playerid][pWeaponUID] = 0;
    CharacterCache[playerid][pWeaponID] = 0;
    CharacterCache[playerid][pWeaponAmmo] = 0;
    CharacterCache[playerid][pGetWeapon] = false;

    CharacterCache[playerid][pDeathReason] = 0;
    CharacterCache[playerid][pDeathWeapon] = 0;

    CharacterCache[playerid][pBlockReason] = 0;
    
    CharacterCache[playerid][pShowBlood] = false;
    
    CharacterCache[playerid][pPackage] = false;
    CharacterCache[playerid][pPackageID] = 0;
    CharacterCache[playerid][pPackageDoor] = 0;
	CharacterCache[playerid][pPackageTime] = 0;

    Logged[playerid] = false;
    SendOffer[playerid] = false;
    
   	CallNow[playerid] = false;
	CallTo[playerid] = INVALID_PLAYER_ID;
	CallTime[playerid] = -1;

    DutyGroup[playerid] = 0;
    DutyGroupSlot[playerid] = 0;
    DutyGroupTime[playerid] = 0;
    
    PlayerDoor[playerid] = 0;
    PhoneNumber[playerid] = 0;
    
    PlayerEditObject[playerid] = 0;
    EditBusStop[playerid] = 0;
    
    CharacterOnline[playerid] = 0;
    PlayerItemIndex[playerid] = 0;
    
    OfertaInfo[playerid][oType] = 0;
    OfertaInfo[playerid][oCustomer] = -1;
    OfertaInfo[playerid][oPrice] = 0;
    OfertaInfo[playerid][oValue1] = 0;
    OfertaInfo[playerid][oSeller] = -1;

    MemberGroup[playerid][1][GroupID] = 0;
    MemberGroup[playerid][1][GroupCash] = 0;
    MemberGroup[playerid][1][GroupRank] = 0;
    MemberGroup[playerid][1][GroupPerm] = 0;
    MemberGroup[playerid][1][GroupSkin] = 0;
    MemberGroup[playerid][1][GroupTime] = 0;
    MemberGroup[playerid][1][GroupSubGroup] = 0;

    MemberGroup[playerid][2][GroupID] = 0;
    MemberGroup[playerid][2][GroupCash] = 0;
    MemberGroup[playerid][2][GroupRank] = 0;
    MemberGroup[playerid][2][GroupPerm] = 0;
    MemberGroup[playerid][2][GroupSkin] = 0;
    MemberGroup[playerid][2][GroupTime] = 0;
    MemberGroup[playerid][2][GroupSubGroup] = 0;

    MemberGroup[playerid][3][GroupID] = 0;
    MemberGroup[playerid][3][GroupCash] = 0;
    MemberGroup[playerid][3][GroupRank] = 0;
    MemberGroup[playerid][3][GroupPerm] = 0;
    MemberGroup[playerid][3][GroupSkin] = 0;
    MemberGroup[playerid][3][GroupTime] = 0;
    MemberGroup[playerid][3][GroupSubGroup] = 0;

    ReloadAnims(playerid);
    
    SetPlayerDrunkLevel(playerid, 0);
    
    DestroyPlayerProgressBar(playerid, DrugsBar[playerid]);
    DestroyPlayerProgressBar(playerid, FoodBar[playerid]);
    
    RemovePlayerAttachedObject(playerid, SLOT_CASE);
	RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
	RemovePlayerAttachedObject(playerid, SLOT_HAT);
	RemovePlayerAttachedObject(playerid, SLOT_GLASSES);
	RemovePlayerAttachedObject(playerid, SLOT_PHONE);
	RemovePlayerAttachedObject(playerid, SLOT_TIME);
    
    PlayerTextDrawDestroy(playerid, AdminInfo[playerid]);
    
    PlayerTextDrawDestroy(playerid, TextPenaltyType[playerid]);
    PlayerTextDrawDestroy(playerid, TextPenalty[playerid]);

    PlayerTextDrawDestroy(playerid, TextDrawAudioError[playerid]);
    PlayerTextDrawDestroy(playerid, IRPName[playerid]);
    
    PlayerTextDrawDestroy(playerid, Panorama1[playerid]);
    PlayerTextDrawDestroy(playerid, Panorama2[playerid]);

    PlayerTextDrawDestroy(playerid, InfoDoor[playerid]);
    PlayerTextDrawDestroy(playerid, BoxDoor[playerid]);
    PlayerTextDrawDestroy(playerid, BoxDoorIcon[playerid]);
    PlayerTextDrawDestroy(playerid, IconDoorRed[playerid]);
    PlayerTextDrawDestroy(playerid, IconDoorPurple[playerid]);
    PlayerTextDrawDestroy(playerid, IconDoorGreen[playerid]);
    
    PlayerTextDrawDestroy(playerid, RadioFM[playerid]);
	PlayerTextDrawDestroy(playerid, AdminDuty[playerid]);

    PlayerTextDrawDestroy(playerid, TextDrawMainInfo[playerid]);

    PlayerTextDrawDestroy(playerid, Textdraw0[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw1[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw2[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw3[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw4[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw5[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw6[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw7[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw8[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw9[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw10[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw11[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw12[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw13[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw14[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw15[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw16[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw17[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw18[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw19[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw20[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw21[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw22[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw23[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw24[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw25[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw26[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw27[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw28[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw29[playerid]);
    PlayerTextDrawDestroy(playerid, Textdraw30[playerid]);
}