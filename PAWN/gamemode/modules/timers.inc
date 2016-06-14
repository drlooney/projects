forward TimerSecond();
forward TimerMinute();
forward TimerHour();

public TimerSecond()
{
	if(Restart)
	{
	    Restart --;
	    
	    SendClientMessageToAllFormat(0x90D424FF, "[RESTART] Serwer zostanie zrestartowany za %d sekund.", Restart);
	    
	    if(!Restart)
	    {
	        ForeachEx(i, MAX_PLAYERS)
	        {
	            if(!CharacterCache[i][pAdmin])
	            {
	            	KickWithWait(i);
	            }
	        }
	        
	        SendClientMessageToAllFormat(CZERWONY, "[RESTART] Gracze opuœcili serwer. Rozpoczynam restart.", Restart);
         	SetTimer("RestartGMX", 1000, false);
	    }
	}
	
    if(DeletePenalty != -1)
    {
        DeletePenalty--;
        if(DeletePenalty < 1)
        {
            ForeachEx(playerid, MAX_PLAYERS)
            {
	            PlayerTextDrawHide(playerid, TextPenaltyType[playerid]);
	            PlayerTextDrawHide(playerid, TextPenalty[playerid]);
            }
            
            DeletePenalty = -1;
        }
    }
    
    ForeachEx(i, MAX_VEHICLES)
    {
        if(VehicleInfo[i][vSensor])
        {
            VehicleInfo[i][vSensor] --;
            
            if(!VehicleInfo[i][vSensor])
            {
                 VehicleInfo[i][vSensor] = 0;
            }
		}
    }
    
    ForeachEx(i, MAX_PLAYERS)
    {
        if(Logged[i])
        {
            // Naliczanie godzin
            CharacterOnline[i] ++;
            
            // GPS w publicznych
            if(IsPermGroupFlag(i, FLAG_GPS))
            {
                new iconid = 6, Float:Pos[3];
                
                ForeachEx(vehid, MAX_VEHICLES)
                {
                    if(VehicleInfo[vehid][vGameID] && VehicleInfo[vehid][vUseGPS])
                    {
                        GetVehiclePos(VehicleInfo[vehid][vGameID], Pos[0], Pos[1], Pos[2]);

                        SetPlayerMapIcon(i, iconid, Pos[0], Pos[1], Pos[2], 30, 0, MAPICON_GLOBAL);
                        iconid ++;
                    }
                }
            }

            // Zaktualizuj status
            UpdatePlayerStatus(i);

            // Update nicku
            UpdatePlayer3DTextNick(i);

            // Naliczanie s³u¿by
            if(DutyGroup[i])
            {
                DutyGroupTime[i] ++;
            }

			// Naliczenia czasu AFK dziœ
    		if(CharacterCache[i][pStatus] & STATUS_AFK)
    		{
    		    PlayerAFK[i] ++;
    		}
    		
    		// Czujniki
    		if(CharacterCache[i][pSensor])
    		{
    		    CharacterCache[i][pSensor] --;
    		    
    		    if(!CharacterCache[i][pSensor])
    		    {
    		        CharacterCache[i][pSensor] = 0;
    		    }
    		}
    
            // Animacja BW
            if(CharacterCache[i][pBW])
            {
                ApplyAnimation(i, "CRACK", "crckdeth3", 4.1, 0, 0, 0, 1, 0, 1);
            }
            
            // Aktualizuj nick czerwony
    		if(CharacterCache[i][pTakeDamage])
    		{
    		    CharacterCache[i][pTakeDamage] --;
    		    
    		    if(CharacterCache[i][pTakeDamage] == 0)
    		    {
    		        CharacterCache[i][pTakeDamage] = 0;
    		        
                    if(IsPlayerPremium(i)) CharacterCache[i][pNickColor] = 0xFCDF1E99;
					else CharacterCache[i][pNickColor] = 0xFFFFFF99;
    		    }
    		}
    		
    		// Krêcenie ekranu - g³ód
    		if(CharacterCache[i][pFood] <= 45)
            {
                SetPlayerDrunkLevel(i, 15000);
            }
		
		    // Namierzanie
		    if(CharacterCache[i][pDetectProgress])
		    {
		        new playerid2 = CharacterCache[i][pDetectPlayerID];
				new Float:Pos[3];
				new string[64];
				
				GetPlayerPos(playerid2, Pos[0], Pos[1], Pos[2]);
				
				SetPlayerCameraPos(i, Pos[0] + random(40), (Pos[1] + random(40)) - 2, Pos[2] + (CharacterCache[i][pDetectProgress] + 30));
				SetPlayerCameraLookAt(i, Pos[0], Pos[1], Pos[2]);
				
				CharacterCache[i][pDetectProgress] --;
				
				format(string, sizeof(string), "~n~~n~~n~~n~~n~~n~Namierzanie: ~g~%d", CharacterCache[i][pDetectProgress] - 10);
				GameTextForPlayer(i, string, 3000, 4);
			
				if(!CharacterCache[i][pDetectProgress])
				{
				    CharacterCache[i][pDetect] = true;
				    CharacterCache[i][pDetectNumber] = 0;
				    CharacterCache[i][pDetectPlayerID] = INVALID_PLAYER_ID;
				    CharacterCache[i][pDetectProgress] --;
				    
				    SetPlayerCameraPos(i, Pos[0], Pos[1] - 2, Pos[2] + 50);
					SetPlayerCameraLookAt(i, Pos[0], Pos[1] - 2, Pos[2]);
				    
				    SendClientMessage(i, 0xCACACAFF, "Aby zakoñczyæ namierzanie u¿yj komendy /namierz.");
			    
			    	GameTextForPlayer(i, "~n~~n~~n~~n~~n~~n~Namierzanie: ~g~ukonczone", 3000, 4);
			    }
		    }
		    
			// Kajdanki
			if(CharacterCache[i][pCuffed] != INVALID_PLAYER_ID)
			{
			    new cuffed_to = CharacterCache[i][pCuffed];

			    new Float:x, Float:y, Float:z,
			        interior = GetPlayerInterior(cuffed_to), virtual_world = GetPlayerVirtualWorld(cuffed_to);

			    GetPlayerPos(cuffed_to, x, y, z);

			    if(!IsPlayerInRangeOfPoint(i, 3.0, x, y, z))
			    {
			        if(IsPlayerInAnyVehicle(i))
			        {
			            RemovePlayerFromVehicle(i);
			            TogglePlayerControllable(i, 1);
			        }
			        SetPlayerPos(i, x + 1, y, z);

			        SetPlayerInterior(i, interior);
			        SetPlayerVirtualWorld(i, virtual_world);
			    }
			    else if(GetPlayerState(cuffed_to) == PLAYER_STATE_DRIVER)
			    {
			        new vehid = GetPlayerVehicleID(cuffed_to);
					if(IsSeatFree(vehid, 2))
					{
					    PutPlayerInVehicle(i, vehid, 2);
					    TogglePlayerControllable(i, 0);
					}
					else if(IsSeatFree(vehid, 3))
					{
					    PutPlayerInVehicle(i, vehid, 3);
                        TogglePlayerControllable(i, 0);
					}
					else
					{
						GameTextForPlayer(cuffed_to, "~r~Brak wolnego miejsca w pojezdzie.", 4000, 3);
					}
			    }
			}
			
			// Pojazdy
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
			{
			    new vehid = GetVehicleUID(GetPlayerVehicleID(i));
				new speed = GetPlayerSpeed(i, true);

			    if(VehicleInfo[vehid][vEngineTogged])
			    {
					// Odejmij paliwo
					if(VehicleInfo[vehid][vFuel] > 0)
					{
			    		if(speed < 1)
				    	{
		   					VehicleInfo[vehid][vFuel] -= 0.002;
				    	}
				    	else if(speed >= 1 && speed <= 40)
				    	{
		    				VehicleInfo[vehid][vFuel] -= 0.0025;
				    	}
				    	else if(speed >= 41 && speed <= 80)
				    	{
		    				VehicleInfo[vehid][vFuel] -= 0.005;
				    	}
				    	else if(speed >= 81 && speed <= 120)
					   	{
		    				VehicleInfo[vehid][vFuel] -= 0.0075;
				    	}
				    	else if(speed >= 121 && speed <= 150)
				    	{
		    				VehicleInfo[vehid][vFuel] -= 0.01;
				    	}
				    	else
				    	{
		    				VehicleInfo[vehid][vFuel] -= 0.0125;
				    	}
					}

			    	new Float:x, Float:y, Float:z;
					GetVehiclePos(VehicleInfo[vehid][vGameID], x, y, z);

					new Float:distance = floatsqroot(floatpower(floatabs(floatsub(x, VehiclePos[vehid][0])), 2) + floatpower(floatabs(floatsub(y, VehiclePos[vehid][1])),2) + floatpower(floatabs(floatsub(z, VehiclePos[vehid][2])), 2));
	    			Tick[VehicleInfo[vehid][vGameID]] += floatround(distance);

					new Float: health;
					GetVehicleHealth(VehicleInfo[vehid][vGameID], health);
					if(health > VehicleInfo[vehid][vHP])
					{
					    CharacterCache[i][pVehicleWarring] ++;
					    
					    if(CharacterCache[i][pVehicleWarring] >= 3)
					    {
	 						SetVehicleHealth(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vHP]);
	 						
	 						CharacterCache[i][pVehicleWarring] = 0;
	 					}
					}
					if(health < VehicleInfo[vehid][vHP])
					{
	 					GetVehicleHealth(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vHP]);
				 	}

	                new panels, doors, lights, tires;
					GetVehicleDamageStatus(VehicleInfo[vehid][vGameID], panels, doors, lights, tires);
					if(panels < VehicleInfo[vehid][vVisual][0] || doors < VehicleInfo[vehid][vVisual][1] || tires < VehicleInfo[vehid][vVisual][3])
					{
					    CharacterCache[i][pVehicleWarring] ++;
					    
					    if(CharacterCache[i][pVehicleWarring] >= 3)
					    {
							UpdateVehicleDamageStatus(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vVisual][0], VehicleInfo[vehid][vVisual][1], VehicleInfo[vehid][vVisual][2], VehicleInfo[vehid][vVisual][3]);
							
							CharacterCache[i][pVehicleWarring] = 0;
						}
					}
					GetVehicleDamageStatus(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vVisual][0], VehicleInfo[vehid][vVisual][1], VehicleInfo[vehid][vVisual][2], VehicleInfo[vehid][vVisual][3]);

					if(Tick[VehicleInfo[vehid][vGameID]] >= 110)
					{
			    		if(CharacterCache[i][pTaxiPassenger] != INVALID_PLAYER_ID)
					    {
					        new passenger_id = CharacterCache[i][pTaxiPassenger];
					        new string[64];

     						if(CharacterCache[passenger_id][pCash] > CharacterCache[passenger_id][pTaxiPay])
     						{
     						    CharacterCache[passenger_id][pTaxiPay] += CharacterCache[passenger_id][pTaxiPrice];

								format(string, sizeof(string), "~w~Koszt: ~g~$%d", CharacterCache[passenger_id][pTaxiPay]);

								GameTextForPlayer(i, string, 5000, 6);
				    			GameTextForPlayer(passenger_id, string, 5000, 6);
							}
							else
							{
							    GameTextForPlayer(i, "~r~Pasazer nie posiada tyle gotowki", 5000, 6);
							    GameTextForPlayer(passenger_id, "~r~Nie posiadasz tyle gotowki", 5000, 6);
							}
					    }
					    
	 					Tick[VehicleInfo[vehid][vGameID]] = false;
	 					VehicleInfo[vehid][vDistance] += 0.1;
					}

					VehiclePos[vehid][0] = x;
					VehiclePos[vehid][1] = y;
					VehiclePos[vehid][2] = z;


					if(VehicleInfo[vehid][vHP] <= 360 || VehicleInfo[vehid][vHP] < 700 && random(150) == 25 && VehicleInfo[vehid][vModel] != 509 && VehicleInfo[vehid][vModel] != 510 && VehicleInfo[vehid][vModel] != 481)
					{
  						VehicleInfo[vehid][vEngineTogged] = false;
						ChangeVehicleEngineStatus(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vEngineTogged]);

						new string[128];
						format(string, sizeof(string), "** Silnik w pojeŸdzie %s zaprzesta³ pracowaæ.", GetVehicleModelName(VehicleInfo[vehid][vModel]));
						
						ProxDetector(10.0, i, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO);

						GameTextForPlayer(i, "~r~Silnik w pojezdzie zgasl ze wzgledu na uszkodzenia techniczne.", 5000, 3);
					}

    				if(VehicleInfo[vehid][vFuel] <= 0 && VehicleInfo[vehid][vModel] != 509 && VehicleInfo[vehid][vModel] != 510 && VehicleInfo[vehid][vModel] != 481)
			    	{
	    				VehicleInfo[vehid][vEngineTogged] = false;
                        ChangeVehicleEngineStatus(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vEngineTogged]);

                        new string[128];
						format(string, sizeof(string), "** Silnik w pojeŸdzie %s zaprzesta³ pracowaæ.", GetVehicleModelName(VehicleInfo[vehid][vModel]));
						
						ProxDetector(10.0, i, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO);

						GameTextForPlayer(i, "~r~Silnik w pojezdzie zgasl ze wzgledu na brak paliwa.", 5000, 3);
			    	}
			    	
		    		ForeachEx(j, 14)
			   		{
        				new componentid = GetVehicleComponentInSlot(VehicleInfo[vehid][vGameID], j);
		      			if (componentid != 0 && componentid != (VehicleInfo[vehid][vComponent][j] + 999))
			        	{
							SetVehicleToRespawn(vehid);
				            continue;
				        }
				    }
				}
			}
			
			// Jest z parali¿owany
			if(CharacterCache[i][pParalizeTime])
			{
			    CharacterCache[i][pParalizeTime] --;

			    if(GetPlayerAnimationIndex(i) != 402)
			    {
			        ApplyAnimation(i, "CRACK", "crckdeth2", 4.0, 0, 0, 0, 1, 0, 1);
			    }

			    if(CharacterCache[i][pParalizeTime] <= 0)
			    {
			        ApplyAnimation(i, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0);
			        CharacterCache[i][pParalizeTime] = 0;
			    }
			}
			
			// BUS - transport
			if(CharacterCache[i][pBusTime])
			{
			    CharacterCache[i][pBusTime] --;
			    
			    if(!CharacterCache[i][pBusTime])
			    {
			        new busid = CharacterCache[i][pBusTarget];
			        
			        CharacterCache[i][pBusTarget] = 0;
			        CharacterCache[i][pBusTime] = 0;
			        CharacterCache[i][pBusStatus] = BUS_NONE;
			        
			        SetPlayerPos(i, BusStop[busid][bPos][0], BusStop[busid][bPos][1], BusStop[busid][bPos][2]);
			        SetCameraBehindPlayer(i);
			        TogglePlayerControllable(i, 1);
			    }
			}
			
			// Lowi rybki
			if(CharacterCache[i][pFished])
			{
			    if(IsPlayerFishing(i))
			    {
					if(GetPlayerAnimationIndex(i) != 257)
					{
					    ApplyAnimation(i, "CAMERA", "camstnd_lkabt", 4.1, 0, 0, 0, 1, 0, 1);
					}

					if(!CharacterCache[i][pFishTaking])
					{
				        if(!CharacterCache[i][pBait])
				    	{
				    	    new item = CharacterCache[i][pFishingRodUID],
				    	    	query[128];

							ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", " Nie za³o¿y³eœ przynêty na wêdkê. Zrób to, a nastêpnie rozpocznij po³ów.", "Zamknij", "");

							CharacterCache[i][pFishTaking] = false;
					        CharacterCache[i][pFishingRodUID] = 0;
			   				CharacterCache[i][pFished] = false;

			   				ItemInfo[item][iUsed] = 0;

			   				format(query, sizeof(query), "UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", ItemInfo[item][iUID]);
				            mysql_check(); mysql_query(query);

				   			RemovePlayerAttachedObject(i, SLOT_CASE);
							ApplyAnimation(i, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0);
					    }
					    
					    new rand = random(100);
						if(rand == 23 || rand == 86)
						{
						    CharacterCache[i][pFishTaking] = true;
						}
					}
					else
					{
						if(random(20) == 5)
						{
						    GameTextForPlayer(i, "~w~Ryba ~r~uciekla", 5000, 3);
						    CharacterCache[i][pFishTaking] = false;
						    CharacterCache[i][pBait] = 0;
						}

					    Infobox(i, 5, "~g~~h~Splawik ~w~~h~sie poruszyl, masz branie.~n~~w~~h~Wciskaj ~g~~k~~PED_FIREWEAPON~~w~~h~, aby starac sie ~g~~h~zlowic ~w~zdobycz.");
					}
			    }
			    else
			    {
					new itemid = CharacterCache[i][pFishingRodUID],
						mysql[128];
					
			        ItemInfo[itemid][iUsed] = 0;

		            format(mysql, sizeof(mysql), "UPDATE `fc_items` SET `used` = 0 WHERE `uid` = '%d'", ItemInfo[itemid][iUID]);
		            mysql_check(); mysql_query(mysql);
			        
				    CharacterCache[i][pFishingRodUID] = 0;
				    CharacterCache[i][pFished] = false;

		   			RemovePlayerAttachedObject(i, SLOT_CASE);
					ApplyAnimation(i, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0);
	    		}
			}
			
			// Nabijanie czasu duty - praca
			if(CharacterCache[i][pDutyJob])
			{
			    if(!(CharacterCache[i][pStatus] & STATUS_AFK))
			    {
			    	CharacterCache[i][pDutyJobTime] ++;
			    }
			    if(!IsPlayerInArea(i, AREA_STATION))
		        {
		        	new hours, minutes, second, cash = 0, title[128], string[256];
		            GetPlayedTimeSecZ(CharacterCache[i][pDutyJobTime], hours, minutes, second);

		            CharacterCache[i][pDutyJob] = false;
		            CharacterCache[i][pDutyJobTime] = 0;

		            cash += PlayerActions[i] * 2;
		            cash += hours * 60;
		            cash += minutes * 1;

		            format(title, sizeof(title), "{FFFFFF}Pomocnik stacji [{8CD147}%dh, %dmin{FFFFFF}]", hours, minutes);
		            format(string, sizeof(string), "Przepracowany czas:\t\t{8CD147}%dh, %dmin\nZarobiona gotówka:\t\t$%d\n-----\nGotówka przydzielana jest co 30 minut, od czasu s³u¿by.\nW momencie AFK czas s³u¿by nie nalicza siê.", hours, minutes, cash);

		            ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_LIST, title, string, "Zamknij", "");
		        }
			}

			// Sprawdzanie gotówki gracza
			if(CharacterCache[i][pCash] != GetPlayerMoney(i))
			{
			    ResetPlayerMoney(i);
			    GivePlayerMoney(i, CharacterCache[i][pCash]);
			}
			
			// Sprawdzenie reanimacji
			if(CharacterCache[i][pReanimation])
			{
			    CharacterCache[i][pReanimation] --;
			    
			    GameTextForPlayer(i, "~n~~n~~n~~n~~g~~h~Trwa reanimacja...", 1000, 5);
				GameTextForPlayer(CharacterCache[i][pReanimationID], "~n~~n~~n~~n~~g~~h~Trwa reanimacja...", 1000, 5);
			    
				if(!CharacterCache[i][pReanimation])
				{
				    new playerid2 = CharacterCache[i][pReanimationID];
				    new string[256];
				    
				    CharacterCache[i][pReanimationID] = INVALID_PLAYER_ID;
				    CharacterCache[i][pReanimation] = 0;
				    
					CharacterCache[playerid2][pBW] = 0;
				    SetPlayerHP(playerid2, 10.0);

				    ApplyAnimation(playerid2, "Attractors", "Stepsit_out", 4.0, 0, 0, 0, 0, 0, 1);
					TogglePlayerControllable(playerid2, 1);

					SetCameraBehindPlayer(playerid2);

				    format(string, sizeof(string), "Zosta³eœ uleczony przez medyka %s.\nTwój stan zdrowia jest dobry, lecz wymaga hospitalizacji.", PlayerName2(i));
				    ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");

				    format(string, sizeof(string), "Pomyœlnie uleczy³eœ gracza %s.", PlayerName2(playerid2));
				    ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", string, "Zamknij", "");
				}
			}
			
			// Odliczanie czasu naprawy
			if(CharacterCache[i][pRepair])
			{
			    new playerid2 = GetPVarInt(i, "RepairPlayerID");
			    new price = GetPVarInt(i, "RepairPrice");
			    new vehid = CharacterCache[i][pRepairVehicle];
				new string[64];
			    
			    CharacterCache[i][pRepair] --;
			    
		     	format(string, sizeof(string), "(( Naprawa pojazdu %s - %d procent ))", GetVehicleModelName(VehicleInfo[vehid][vModel]), (100 - CharacterCache[i][pRepair]));
	    		UpdateDynamic3DTextLabelText(VehicleTag[VehicleInfo[vehid][vGameID]], 0xFFFFFFCC, string);
			    
			    if(!CharacterCache[i][pRepair])
			    {
			    	CharacterCache[i][pRepair] = 0;
			        CharacterCache[i][pRepairVehicle] = 0;
			        
			        GivePlayerCash(playerid2, -(floatround(price * 3)));
	    			GivePlayerCash(i, price);
	    			
	    			VehicleInfo[vehid][vHP] = 1000.0;
			        SetVehicleHealth(VehicleInfo[vehid][vGameID], 1000.0);

			        RepairVehicle(VehicleInfo[vehid][vGameID]);
			        SaveVehicle(vehid, SAVE_VEH_COUNT);
        
        			UpdateDynamic3DTextLabelText(VehicleTag[VehicleInfo[vehid][vGameID]], 0xFFFFFFCC, "");
        
                    PlayerPlaySound(i, 1133, 0, 0, 0);
			        PlayerPlaySound(playerid2, 1133, 0, 0, 0);
			        
	    			GameTextForPlayer(i, "~g~~h~Pojazd naprawiony!", 2000, 1);
	    			GameTextForPlayer(playerid2, "~g~~h~Pojazd naprawiony!", 2000, 1);
			    }
			    if(!Logged[playerid2] || CharacterCache[playerid2][pCash] < price)
			    {
			        CharacterCache[i][pRepair] = 0;
			        CharacterCache[i][pRepairVehicle] = 0;
			        
			        UpdateDynamic3DTextLabelText(VehicleTag[VehicleInfo[vehid][vGameID]], 0xFFFFFFCC, "");
			        
			        ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Petent nie posiada odpowiedniej iloœci gotówki, lub wyszed³ z gry.\nAkcja zosta³a przerwana.", "Zamknij", "");
			        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", " Praca zosta³a przerwana gdy¿ nie posiadasz odpowiedniej iloœci gotówki na koncie.", "Zamknij", "");
			    }
			    if(!PlayerToPlayer(5.0, i, playerid2) || !IsPlayerInAnyVehicle(playerid2))
			    {
			    	CharacterCache[i][pRepair] = 0;
			        CharacterCache[i][pRepairVehicle] = 0;
			        
			        UpdateDynamic3DTextLabelText(VehicleTag[VehicleInfo[vehid][vGameID]], 0xFFFFFFCC, "");

			        ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Petent nie znajduje siê w pojeŸdzie lub jest zbyt daleko od niego.\nAkcja zosta³a przerwana.", "Zamknij", "");
			        ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", " Praca zosta³a przerwana gdy¿ mechanik znajdowa³ siê zbyt daleko od pojazdu.", "Zamknij", "");
			    }
			    if(!IsPlayerInArea(i, AREA_STATION))
		        {
		            CharacterCache[i][pRepair] = 0;
			        CharacterCache[i][pRepairVehicle] = 0;
			        
			        UpdateDynamic3DTextLabelText(VehicleTag[VehicleInfo[vehid][vGameID]], 0xFFFFFFCC, "");
			        
		        	ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Nie znajdujesz siê na stacji paliw.\nAkcja zosta³a przerwana.", "Zamknij", "");
		        	ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, " Wyst¹pi³ b³¹d", "Pomocnik nie znajdowa³ siê na stacji.\nAkcja zosta³a przerwana.", "Zamknij", "");
		        }
			}
			
            // Odliczanie czasu textdrawu
            if(CharacterCache[i][pShowInfoText])
            {
                CharacterCache[i][pShowInfoText]--;
                if(CharacterCache[i][pShowInfoText] == 0)
                {
                    CharacterCache[i][pShowInfoText] = 0;
                    PlayerTextDrawHide(i, TextDrawMainInfo[i]);
                }
            }

            // Napady na sklep
            if(CharacterCache[i][pRobbery])
            {
                CharacterCache[i][pRobbery] --;

                new string[128],
                    groupid = CharacterCache[i][pRobberyID];

                format(string, sizeof(string), "~w~Koniec napadu: ~g~%d ~w~sekund.", CharacterCache[i][pRobbery]);

                ForeachEx(player, MAX_PLAYERS)
                {
                    if(IsPlayerInGroup(player, groupid) && PlayerDoor[player] == PlayerDoor[i])
                    {
                        GameTextForPlayer(player, string, 1000, 1);
                    }
                }

                if(CharacterCache[i][pRobbery] == 0)
                {
                    CharacterCache[i][pRobbery] = 0;
                    CharacterCache[i][pRobberyID] = 0;

                    new rand = random(2),
                        cash;

                    switch(rand)
                    {
                        case 0: cash = 400;
                        case 1: cash = 500;
                        case 2: cash = 600;
                    }

                    format(string, sizeof(string), "~n~~n~~g~Napad na sklep dobiegl konca!~n~Zarobiles : $%d", cash);

                    ForeachEx(player, MAX_PLAYERS)
                    {
                        if(IsPlayerInGroup(player, groupid) && PlayerDoor[player] == PlayerDoor[i])
                        {
                            GameTextForPlayer(player, string, 1000, 4);
                        }
                    }

                    GivePlayerCash(i, cash);

                    GroupData[groupid][LimitVehicles] = 1;
                    SaveGroup(groupid);
                }
                else
                {
                    if(CharacterCache[i][pRobberyID] != DutyGroup[i])
                    {
                        CharacterCache[i][pRobbery] = 0;
                        CharacterCache[i][pRobberyID] = 0;

                        ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Zszed³eœ ze s³u¿by w grupie przestêpczej dlatego napad zosta³ przerwany.", "Zamknij", "");
                    }
                }
            }

			// Kradzie¿ pojazdu
			if(CharacterCache[i][pVehicleThief])
			{
			    new vehid = CharacterCache[i][pVehicleThiefID];
			    new Float:Pos[3];
			    new string[32];
			    GetVehiclePos(VehicleInfo[vehid][vGameID], Pos[0], Pos[1], Pos[2]);
			    
			    CharacterCache[i][pVehicleThief] --;
			    
			    format(string, sizeof(string), "~w~Koniec kradziezy: ~g~%d ~w~sekund.", CharacterCache[i][pVehicleThief]);
			    GameTextForPlayer(i, string, 1000, 1);
			    
			    if(!CharacterCache[i][pVehicleThief])
			    {
			        CharacterCache[i][pVehicleThief] = 0;
			        CharacterCache[i][pVehicleThiefID] = 0;
			        
			        VehicleInfo[vehid][vOwnerType] = OWNER_PLAYER;
			        VehicleInfo[vehid][vOwner] = CharacterCache[i][pUID];
			        
			        SaveVehicle(vehid, SAVE_VEH_THINGS);
			        
			        UpdateDynamic3DTextLabelText(StatusTag[i], 0xFFFFFFCC, "");
			        
			        ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Pojazd zosta³ pomyœlnie skradziony.\nPojawi siê on na Twoim koncie gry.", "Zamknij", "");
			    }
			    
			    if(!PlayerToPoint(5.0, i, Pos[0], Pos[1], Pos[2]))
			    {
			        CharacterCache[i][pVehicleThief] = 0;
			        CharacterCache[i][pVehicleThiefID] = 0;
			        
			        UpdateDynamic3DTextLabelText(StatusTag[i], 0xFFFFFFCC, "");
			        
                    ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Akcja kradzie¿y pojazdu zosta³a przerwana.\nOddali³eœ siê zbyt daleko pojazdu.", "Zamknij", "");
			    }
			}
			
            // Wyœwietlanie drzwi
            if(CharacterCache[i][pShowDoors])
            {
                CharacterCache[i][pShowDoors] --;

                if(!CharacterCache[i][pShowDoors])
                {
                    PlayerTextDrawHide(i, InfoDoor[i]);
                    PlayerTextDrawHide(i, BoxDoor[i]);
                    PlayerTextDrawHide(i, BoxDoorIcon[i]);
                    PlayerTextDrawHide(i, IconDoorRed[i]);
                    PlayerTextDrawHide(i, IconDoorPurple[i]);
                    PlayerTextDrawHide(i, IconDoorGreen[i]);
                }
            }

            // Usuwanie AFK
            CharacterCache[i][pAFK] --;

            // Podpalenie
            new doorid = GetClosestDoor(i);

            if(DoorInfo[doorid][dFireUse])
            {
                if(IsPlayerKindGroup(i, GROUP_FD))
                {
                    new keysa, uda, lra;
                    GetPlayerKeys(i, keysa, uda, lra);
                    if(keysa & KEY_FIRE && GetPlayerWeapon(i) == 42 && !IsPlayerInAnyVehicle(i))
                    {
                        GameTextForPlayer(i, "~n~~n~~n~~n~~n~~r~~h~Trwa gaszenie...", 1000, 5);
                        if(DoorInfo[doorid][dFireUse] == 1) DoorInfo[doorid][dFireValue] = 500;
                        DoorInfo[doorid][dFireUse] = 2;
                        DoorInfo[doorid][dFireValue]--;

                        if(DoorInfo[doorid][dFireValue] == 0)
                        {
                            DestroyObject(DoorInfo[doorid][dFireObject][0]);
                            DestroyObject(DoorInfo[doorid][dFireObject][1]);
                            DestroyObject(DoorInfo[doorid][dFireObject][2]);
                            DestroyObject(DoorInfo[doorid][dFireObject][3]);
                            DestroyObject(DoorInfo[doorid][dFireObject][4]);
                            DestroyObject(DoorInfo[doorid][dFireObject][5]);

                            DoorInfo[doorid][dFireUse] = 0;
                            DoorInfo[doorid][dFireValue] = 0;
                        }
                    }
                }
                else
                {
                    AddPlayerHP(i, -2);
                    GameTextForPlayer(i, "~n~~n~~n~~n~~n~~r~~h~Palisz sie!", 2000, 5);
                }
            }

            //Admin Jail
            if(CharacterCache[i][pAJ])
            {
                new string[128];
                if(!IsPlayerInRangeOfPoint(i, 5.0, 154.1221, -1951.9156, 47.8750))
                {
                    SetPlayerPos(i, 154.1221, -1951.9156, 47.8750);
                    SetPlayerInterior(i, 0);
                    SetPlayerVirtualWorld(i, i + 1000);
                }

                CharacterCache[i][pAJ] --;
                if(CharacterCache[i][pAJ] > 1*60)
                {
                    format(string, sizeof(string), "~w~Koniec ~r~AJ~w~: ~g~%d ~w~min.", CharacterCache[i][pAJ]/60);
                    GameTextForPlayer(i, string, 1000, 1);
                }
                else
                {
                    format(string, sizeof(string), "~w~Koniec ~r~AJ~w~: ~g~%d ~w~sek.", CharacterCache[i][pAJ]);
                    GameTextForPlayer(i, string, 1000, 1);
                }
                if(CharacterCache[i][pAJ] <= 0)
                {
                    CharacterCache[i][pAJ] = 0;
                    OnPlayerSpawn(i);
                }
            }
        }
    }
}

public TimerMinute()
{
    ForeachEx(i, MAX_PLAYERS)
    {
        CharacterCache[i][pMinutes] ++;
        if(CharacterCache[i][pMinutes] > 59)
        {
            CharacterCache[i][pMinutes] = 0;
            CharacterCache[i][pHours] ++;

            if(IsPlayerPremium(i)) CharacterCache[i][pGlobalScore] += 10;
            else CharacterCache[i][pGlobalScore] += 5;
            
            SetPlayerScore(i, CharacterCache[i][pGlobalScore]);

            SavePlayerStats(i, SAVE_PLAYER_GLOBAL);
        }

		// Aktywowanie TD
		TextDrawShowForAll(Icons);
		
		if(CharacterCache[i][pDrugsTime])
		{
		    CharacterCache[i][pDrugsTime] -= 5;

		    SetPlayerProgressBarValue(i, DrugsBar[i], CharacterCache[i][pDrugsTime]);
	    	UpdatePlayerProgressBar(i, DrugsBar[i]);

		    OnPlayerUseDrug(i);
		}

		if(CharacterCache[i][pJailTime])
		{
			CharacterCache[i][pJailTime] --;

		    if(!CharacterCache[i][pJailTime])
		    {
		        CharacterCache[i][pJailTime] = 0;
		        CharacterCache[i][pJailID] = 0;

		        TeleportPlayerToSpawn(i);
		    }
		    if(CharacterCache[i][pJailTime] == 1)
		    {
				GameTextForPlayer(i, "~w~Pozostala: ~r~minuta.", 10000, 1);
		    }
		    else
		    {
		        new time[64];
		    	format(time, sizeof(time), "~w~Pozostalo: ~r~%d min.", CharacterCache[i][pJailTime]);

				GameTextForPlayer(i, time, 10000, 1);
			}
		}
			
        if(CharacterCache[i][pBW])
        {
            new string[128];
            CharacterCache[i][pBW] -= 60;

            if(CharacterCache[i][pBW] > 60)
            {
                format(string, sizeof(string), "~w~Koniec ~r~BW~w~: ~g~%d ~w~min.", CharacterCache[i][pBW]/60);
                GameTextForPlayer(i, string, 1000, 1);
            }
            else
            {
                format(string, sizeof(string), "~w~Koniec ~r~BW~w~: ~g~%d ~w~sek.", CharacterCache[i][pBW]);
                GameTextForPlayer(i, string, 1000, 1);
            }
            
            if(CharacterCache[i][pBW] <= 0)
            {
                CharacterCache[i][pBW] = 0;

                ApplyAnimation(i, "Attractors", "Stepsit_out", 4.0, 0, 0, 0, 0, 0, 1);
                TogglePlayerControllable(i, 1);

                SetCameraBehindPlayer(i);
                SetPlayerHealth(i, 20);

                ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "Ockn¹³eœ siê, jednak nie jesteœ wystarczaj¹co na si³ach.\nTwój stan zdrowia nie jest idealny - mo¿e udaj siê do szpitala?", "Zamknij", "");

                SetPlayerDrunkLevel(i, 15000);
            }
        }
    }
    
	new hours, minutes, seconds;
	gettime(hours, minutes, seconds);
	
	if(minutes == 0)
	{
	    TimerHour();
	}
	
	if(AdvertiseTime)
	{
	    AdvertiseTime --;

	    if(AdvertiseTime <= 0)
	    {
	        ForeachEx(i, MAX_PLAYERS)
	        {
	        	PlayerTextDrawSetString(i, RadioFM[i], "~y~~h~        ~>~ ~w~Aktualnie nadawany jest standardowy blok reklamowy!");
	        }

			UsingRadio = false;
			AdvertiseTime = 0;
		}
	}
	
    ForeachEx(i, MAX_DOORS)
    {
        if(DoorInfo[i][dFireUse] == 1)
        {
            DoorInfo[i][dFireValue] += 5;

            new rand = random(3);
            if(rand == 2 && DoorInfo[i][dFireValue] >= 10) CreateExplosion(DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ], 10, 10.0);

            DestroyObject(DoorInfo[i][dFireObject][0]);
            DestroyObject(DoorInfo[i][dFireObject][1]);
            DestroyObject(DoorInfo[i][dFireObject][2]);
            DestroyObject(DoorInfo[i][dFireObject][3]);
            DestroyObject(DoorInfo[i][dFireObject][4]);
            DestroyObject(DoorInfo[i][dFireObject][5]);

            if(DoorInfo[i][dFireValue] == 5)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18735, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18735, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18735, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18735, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18735, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18735, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 10)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18726, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18726, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18726, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18726, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18726, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18726, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 15)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18688, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18688, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18688, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18688, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18688, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18688, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 20)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18692, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18692, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18692, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18692, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18692, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18692, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 25)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 30)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 35)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 40)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 45)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 50)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 55)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 60)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 65)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 70)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 75)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 80)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 85)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 90)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 95)
            {
                DoorInfo[i][dFireObject][0] = CreateObject(18691, DoorInfo[i][dEnterX], DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][1] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][2] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] - 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][3] = CreateObject(18691, DoorInfo[i][dEnterX] + 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 0, 0, 0);
                DoorInfo[i][dFireObject][4] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY], DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
                DoorInfo[i][dFireObject][5] = CreateObject(18694, DoorInfo[i][dEnterX] - 2.5, DoorInfo[i][dEnterY] + 2.5, DoorInfo[i][dEnterZ] - 2.6, 90.0, 0, 0);
            }
            if(DoorInfo[i][dFireValue] == 100)
            {
                DestroyObject(DoorInfo[i][dFireObject][0]);
                DestroyObject(DoorInfo[i][dFireObject][1]);
                DestroyObject(DoorInfo[i][dFireObject][2]);
                DestroyObject(DoorInfo[i][dFireObject][3]);
                DestroyObject(DoorInfo[i][dFireObject][4]);
                DestroyObject(DoorInfo[i][dFireObject][5]);

                DoorInfo[i][dBlock] = 1;
                DoorInfo[i][dFireValue] = 0;
                DoorInfo[i][dFireUse] = false;

                SaveDoors(i);
            }
        }
    }
}

public TimerHour()
{
    new godzina, minuta;
    gettime(godzina, minuta);
    SetWorldTime(godzina + 1);
    new string[64];
    
    format(string, sizeof(string), "** Dzwony w ratuszu bij¹ %d razy. **", godzina);
    SendClientMessageToAll(KOLOR_DO, string);
    
    LoadSettings();
    
    ForeachEx(i, MAX_PLANTS)
    {
	    if(PlantInfo[i][plantProgress] >= 0 && PlantInfo[i][plantProgress] < 100)
		{
            PlantInfo[i][plantProgress] += 5;
            
            new name_plant[64];
            Delete3DTextLabel(PlantInfo[i][plantText]);
            
            format(name_plant, sizeof(name_plant), "%s (%d)\n%d procent\nAby zebraæ u¿yj komendy /zbierz", NamePlant(PlantInfo[i][plantType]), PlantInfo[i][plantUID], PlantInfo[i][plantProgress]);
			PlantInfo[i][plantText] = Create3DTextLabel(name_plant, 0xFFFFFFBB, PlantInfo[i][plantX], PlantInfo[i][plantY], PlantInfo[i][plantZ] - 0.2, 10.0, PlantInfo[i][plantVw]);
		
            SavePlant(i);
	    }
    }
    
    ForeachEx(i, MAX_CORPS)
	{
	    if(CorpseInfo[i][cStatus] > 0)
	    {
	        CorpseInfo[i][cStatus] --;
	        SaveCorpse(i);

	        if(!CorpseInfo[i][cStatus])
	        {
	            DeleteCorpse(i);
	        }
	    }
	}
	
	ForeachEx(i, MAX_PLAYERS)
	{
	    if(Logged[i] && IsPlayerConnected(i))
		{
		    // Zapis graczy
		    SavePlayerStats(i, SAVE_PLAYER_BASIC);
	        SavePlayerStats(i, SAVE_PLAYER_SETTING);
	        SavePlayerStats(i, SAVE_PLAYER_POS);
	        SavePlayerStats(i, SAVE_PLAYER_GLOBAL);
        
	        // Zmniejszanie poziomu g³odu
    		if(CharacterCache[i][pFood] >= 5)
    		{
    		    CharacterCache[i][pFood] -= 5;

    		    SetPlayerProgressBarValue(i, FoodBar[i], CharacterCache[i][pFood]);
				UpdatePlayerProgressBar(i, FoodBar[i]);
    		}
	    }
	}
}