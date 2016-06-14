forward LoadCorps();
forward LoadPlants();
forward LoadItems();
forward LoadDoors();
forward LoadMaterialText();
forward LoadTexture();
forward LoadBurgers();
forward LoadBusStop();
forward LoadVehicles();
forward LoadAreas();
forward LoadSubGroup(uid);
forward LoadGroup(groupid);
forward LoadGroups();
forward LoadObjects();
forward LoadObjectInDoor(doorid);
forward LoadSettings();
forward LoadAttachedItems();
forward LoadSensors();

public LoadSensors()
{
	new result[64], i = 0;

	mysql_check();
	mysql_query("SELECT * FROM `fc_sensors`");

	mysql_store_result();

	if(mysql_num_rows() > MAX_SENSORS) printf("[ERROR][SENSORS] Limit czujnikow w gamemode jest zbyt maly.");

	if(mysql_num_rows() > 0)
	{
		while(mysql_fetch_row_format(result, "|") == 1)
		{
			new uid, name_sensor[64];
			sscanf(result,  "p<|>d", uid);
			sscanf(result,  "p<|>ds[32]fff", 	SensorInfo[uid][sensorID],
												SensorInfo[uid][sensorName],
												SensorInfo[uid][sensorPos][0],
												SensorInfo[uid][sensorPos][1],
												SensorInfo[uid][sensorPos][2]);

			format(name_sensor, sizeof(name_sensor), "Czujnik podczerwieni\n%s (%d)", SensorInfo[uid][sensorName], SensorInfo[uid][sensorID]);
			SensorInfo[uid][sensorText] = Create3DTextLabel(name_sensor, 0xFFFFFFBB, SensorInfo[uid][sensorPos][0], SensorInfo[uid][sensorPos][1], SensorInfo[uid][sensorPos][2] - 0.2, 10.0, 0);

			i ++;
		}
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d czujnikow z bazy danych.", i);
	return 1;
}

public LoadAttachedItems()
{
	new result[128], i = 0;

	mysql_check();
	mysql_query("SELECT * FROM `fc_attached_object`");

	mysql_store_result();

	if(mysql_num_rows() > MAX_ATTACH) printf("[ERROR][ATTACHS] Limit przyczepialnych w gamemode jest zbyt maly.");

	if(mysql_num_rows() > 0)
	{
		while(mysql_fetch_row_format(result, "|") == 1)
		{
			new uid;
			sscanf(result,  "p<|>d", uid);
			sscanf(result,  "p<|>dddfffffffff", 		AttachInfo[uid][aUID],
														AttachInfo[uid][aModel],
														AttachInfo[uid][aitemID],
														AttachInfo[uid][afOffsetX],
														AttachInfo[uid][afOffsetY],
														AttachInfo[uid][afOffsetZ],
														AttachInfo[uid][afRotX],
														AttachInfo[uid][afRotY],
														AttachInfo[uid][afRotZ],
														AttachInfo[uid][afScaleX],
														AttachInfo[uid][afScaleY],
														AttachInfo[uid][afScaleZ]);

			i ++;
		}
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d przyczepialnych z bazy danych.", i);
	return 1;
}

public LoadSettings()
{
	new result[128], i = 0;
    mysql_check();
	mysql_query("SELECT * FROM `fc_setting`");
    mysql_store_result();
    while(mysql_fetch_row_format(result, "|") == 1)
	{
		sscanf(result,  "p<|>dddddddddddddddfff",	SettingInfo[sStatus],
													SettingInfo[sPassword],
													SettingInfo[sDocID],
													SettingInfo[sDocDriver],
													SettingInfo[sDocFish],
													SettingInfo[sDocRegister],
													SettingInfo[sDocLicense],
													SettingInfo[sDocPolice],
													SettingInfo[sDocMedical],
													SettingInfo[sDocPassport],
													SettingInfo[sBenefit],
													SettingInfo[sFuel],
													SettingInfo[sFishSweet],
													SettingInfo[sFishSalt],
													SettingInfo[sProcent],
													SettingInfo[sMagazineX],
													SettingInfo[sMagazineY],
													SettingInfo[sMagazineZ]);

		i++;
	}
	mysql_free_result();
	printf("[LOAD] Wczytano %d ustawieñ z bazy danych.", i);
	return 1;
}

public LoadObjectInDoor(doorid)
{
	ForeachEx(i, MAX_OBJECTS)
	{
		if(ObjectInfo[i][oVW] == doorid || ObjectInfo[i][oDoor] == doorid)
		{
			ObjectInfo[i][oUID] = 0;
			ObjectInfo[i][oModel] = 0;

			ObjectInfo[i][oX] = 0;
			ObjectInfo[i][oY] = 0;
			ObjectInfo[i][oZ] = 0;

			ObjectInfo[i][oRX] = 0;
			ObjectInfo[i][oRY] = 0;
			ObjectInfo[i][oRZ] = 0;

			ObjectInfo[i][oInt] = 0;
			ObjectInfo[i][oVW] = 0;

			ObjectInfo[i][oOwnerType] = 0;
			ObjectInfo[i][oOwner] = 0;

			ObjectInfo[i][oGateX] = 0.0;
			ObjectInfo[i][oGateY] = 0.0;
			ObjectInfo[i][oGateZ] = 0.0;

			ObjectInfo[i][oGateRX] = 0.0;
			ObjectInfo[i][oGateRY] = 0.0;
			ObjectInfo[i][oGateRZ] = 0.0;

			ObjectInfo[i][oGate] = 0;

			ObjectInfo[i][oGateOpen] = false;

			ObjectInfo[i][oDoor] = 0;
			ObjectInfo[i][oMMAT] = 0;
			
			DestroyDynamicObject(ObjectInfo[i][oObject]);
		}
	}

	new result[512];

    mysql_check();
	mysql_query_format("SELECT * FROM `fc_objects` WHERE `doorid` = '%d' OR `vw` = '%d'", doorid, doorid);
    mysql_store_result();

    if(mysql_num_rows() > MAX_OBJECTS) printf("[ERROR][OBJECTS] Limit obiektow w gamemode jest zbyt maly.");

    while(mysql_fetch_row_format(result, "|") == 1)
	{
	    new uid;
		sscanf(result, 	"p<|>d", uid);
		sscanf(result,  "p<|>ddffffffdddddffffffdd",	ObjectInfo[uid][oUID],
														ObjectInfo[uid][oModel],
														ObjectInfo[uid][oX],
														ObjectInfo[uid][oY],
														ObjectInfo[uid][oZ],
														ObjectInfo[uid][oRX],
														ObjectInfo[uid][oRY],
														ObjectInfo[uid][oRZ],
														ObjectInfo[uid][oInt],
														ObjectInfo[uid][oVW],
														ObjectInfo[uid][oOwnerType],
														ObjectInfo[uid][oOwner],
														ObjectInfo[uid][oDoor],
														ObjectInfo[uid][oGateX],
														ObjectInfo[uid][oGateY],
														ObjectInfo[uid][oGateZ],
														ObjectInfo[uid][oGateRX],
														ObjectInfo[uid][oGateRY],
														ObjectInfo[uid][oGateRZ],
														ObjectInfo[uid][oGate],
														ObjectInfo[uid][oMMAT]);

		ObjectInfo[uid][oObject] = CreateDynamicObject(ObjectInfo[uid][oModel], ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ], ObjectInfo[uid][oVW], ObjectInfo[uid][oInt], -1, 500.0);
		ObjectInfo[uid][oGateOpen] = false;

	}

	mysql_free_result();

	printf("[LOAD] Wczytano obiekty dla drzwi %d.", doorid);
	return 1;
}

public LoadObjects()
{
	new result[512], i = 0;
    mysql_check();
	mysql_query("SELECT * FROM `fc_objects`");
    mysql_store_result();

    if(mysql_num_rows() > MAX_OBJECTS) printf("[ERROR][OBJECTS] Limit obiektow w gamemode jest zbyt maly.");

    while(mysql_fetch_row_format(result, "|") == 1)
	{
	    new uid;
		sscanf(result, 	"p<|>d", uid);
		sscanf(result,  "p<|>ddffffffdddddffffffdd",	ObjectInfo[uid][oUID],
														ObjectInfo[uid][oModel],
														ObjectInfo[uid][oX],
														ObjectInfo[uid][oY],
														ObjectInfo[uid][oZ],
														ObjectInfo[uid][oRX],
														ObjectInfo[uid][oRY],
														ObjectInfo[uid][oRZ],
														ObjectInfo[uid][oInt],
														ObjectInfo[uid][oVW],
														ObjectInfo[uid][oOwnerType],
														ObjectInfo[uid][oOwner],
														ObjectInfo[uid][oDoor],
														ObjectInfo[uid][oGateX],
														ObjectInfo[uid][oGateY],
														ObjectInfo[uid][oGateZ],
														ObjectInfo[uid][oGateRX],
														ObjectInfo[uid][oGateRY],
														ObjectInfo[uid][oGateRZ],
														ObjectInfo[uid][oGate],
														ObjectInfo[uid][oMMAT]);

		ObjectInfo[uid][oObject] = CreateDynamicObject(ObjectInfo[uid][oModel], ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ], ObjectInfo[uid][oVW], ObjectInfo[uid][oInt], -1, 500.0);
		ObjectInfo[uid][oGateOpen] = false;

		i++;
	}
	mysql_free_result();
	printf("[LOAD] Wczytano %d obiektów z bazy danych.", i);
	return 1;
}

public LoadGroups()
{
    new uid, data[256], color[12];
	mysql_query("SELECT * FROM `fc_groups`");
	
	mysql_store_result();

	if(mysql_num_rows() > MAX_GROUPS) printf("[ERROR][GROUPS] Limit grup w gamemode jest zbyt maly.");

	while(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>d", uid);
		sscanf(data, "p<|>ds[32]s[12]dddds[11]ddddd",
		GroupData[uid][UID],
		GroupData[uid][Desc],
		GroupData[uid][Tag],
		GroupData[uid][Kind],
		GroupData[uid][Cash],
		GroupData[uid][LimitVehicles],
		GroupData[uid][Flags],
		color,
		GroupData[uid][License],
		GroupData[uid][Leader],
		GroupData[uid][Admin],
		GroupData[uid][Points],
		GroupData[uid][Rank]);
		
		sscanf(color, "p<,>ddd", GroupData[uid][Chat][0], GroupData[uid][Chat][1], GroupData[uid][Chat][2]);
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d grup z bazy danych.", uid);
	return 1;
}

public LoadGroup(groupid)
{
    new uid, data[256], color[12], query[128];
	format(query, sizeof(query), "SELECT * FROM `fc_groups` WHERE `uid` = '%d'", groupid);
	mysql_query(query);
	
	mysql_store_result();
	while(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>d", uid);
		sscanf(data, "p<|>ds[32]s[12]dddds[11]ddddd",
		GroupData[uid][UID],
		GroupData[uid][Desc],
		GroupData[uid][Tag],
		GroupData[uid][Kind],
		GroupData[uid][Cash],
		GroupData[uid][LimitVehicles],
		GroupData[uid][Flags],
		color,
		GroupData[uid][License],
		GroupData[uid][Leader],
		GroupData[uid][Admin],
		GroupData[uid][Points],
		GroupData[uid][Rank]);
		
		sscanf(color, "p<,>ddd", GroupData[uid][Chat][0], GroupData[uid][Chat][1], GroupData[uid][Chat][2]);
	}
	mysql_free_result();

	printf("[LOAD] Wczytano grupe z bazy danych.", uid);
	return 1;
}

public LoadSubGroup(uid)
{
    new gameid, data[128], color[11], query[128];
	format(query, sizeof(query), "SELECT * FROM `fc_subgroups` WHERE `uid` = '%d'", uid);
	mysql_query(query);
	
	mysql_store_result();
	while(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>d", gameid);
		sscanf(data, "p<|>dds[32]s[6]s[11]",
		
		SubData[gameid][sUID],
		SubData[gameid][sGroup],
		SubData[gameid][sDesc],
		SubData[gameid][sTag],
		color);
		
		sscanf(color, "p<,>ddd", SubData[gameid][sChat][0], SubData[gameid][sChat][1], SubData[gameid][sChat][2]);
	}
	mysql_free_result();

	printf("[LOAD] Wczytano subgrupe z bazy danych.", uid);
	return 1;
}

public LoadAreas()
{
	new result[256], i = 0;
	
    mysql_check();
    mysql_query("SELECT * FROM `fc_areas`");
    mysql_store_result();
	
	if(mysql_num_rows() > MAX_AREAS) printf("[ERROR][AREAS] Limit stref w gamemode jest zbyt maly.");

	if(mysql_num_rows() > 0)
	{
		while(mysql_fetch_row_format(result, "|") == 1)
		{
			new uid;
			sscanf(result, "p<|>d", uid);
			sscanf(result, "p<|>dffffddd", 	AreaInfo[uid][aUID],
											AreaInfo[uid][aPos_x][0],
											AreaInfo[uid][aPos_x][1],
											AreaInfo[uid][aPos_y][0],
											AreaInfo[uid][aPos_y][1],
											AreaInfo[uid][aOwnerType],
											AreaInfo[uid][aOwner],
											AreaInfo[uid][aLimitObject]);

			if(AreaInfo[uid][aOwnerType] == OWNER_GROUP)
			{
				AreaInfo[uid][aGangID] = GangZoneCreate(AreaInfo[uid][aPos_x][1], AreaInfo[uid][aPos_y][1], AreaInfo[uid][aPos_x][0], AreaInfo[uid][aPos_y][0]);
			}

			i++;
		}
	}
	mysql_free_result();
	
	printf("[LOAD] Wczytano %d stref z bazy danych.", i);
	return 1;
}

public LoadVehicles()
{
	new result[256], i = 0, visual[32];
    mysql_check();
	mysql_query("SELECT * FROM `fc_vehicles` WHERE `ownertype` = 2");
    mysql_store_result();

    if(mysql_num_rows() > MAX_VEHICLES) printf("[ERROR][VEHICLES] Limit pojazdow w gamemode jest zbyt maly.");

    while(mysql_fetch_row_format(result, "|") == 1)
	{
	    new uid;
		sscanf(result, 	"p<|>d", uid);
		sscanf(result, "p<|>ddfffffddddfs[12]dds[32]fdddd",
															VehicleInfo[uid][vUID],
															VehicleInfo[uid][vModel],
															VehicleInfo[uid][vHP],
															VehicleInfo[uid][vPosX],
															VehicleInfo[uid][vPosY],
															VehicleInfo[uid][vPosZ],
															VehicleInfo[uid][vPosA],
															VehicleInfo[uid][vInteriorID],
															VehicleInfo[uid][vWorldID],
															VehicleInfo[uid][vOwner],
															VehicleInfo[uid][vOwnerType],
															VehicleInfo[uid][vFuel],
															VehicleInfo[uid][vRegister],
															VehicleInfo[uid][vColor1],
															VehicleInfo[uid][vColor2],
															visual,
															VehicleInfo[uid][vDistance],
															VehicleInfo[uid][vAccess],
															VehicleInfo[uid][vBlock],
															VehicleInfo[uid][vSlot],
															VehicleInfo[uid][vPaintJob]);
			
		sscanf(visual, "p<,>dddd", VehicleInfo[uid][vVisual][0], VehicleInfo[uid][vVisual][1], VehicleInfo[uid][vVisual][2], VehicleInfo[uid][vVisual][3]);

		VehicleInfo[uid][vGameID] = CreateVehicle(VehicleInfo[uid][vModel], VehicleInfo[uid][vPosX], VehicleInfo[uid][vPosY], VehicleInfo[uid][vPosZ], VehicleInfo[uid][vPosA], VehicleInfo[uid][vColor1], VehicleInfo[uid][vColor2], 7200);
		
		VehicleInfo[uid][vEngineTogged] = false;
		VehicleInfo[uid][vSpawned] = true;

		if(!VehicleInfo[uid][vPaintJob]) VehicleInfo[uid][vPaintJob] = 3;
			
		SetVehicleNumberPlate(VehicleInfo[uid][vGameID], VehicleInfo[uid][vRegister]);
			
		if(VehicleInfo[uid][vHP] < 350) VehicleInfo[uid][vHP] = 350.0;

		SetVehicleHealth(VehicleInfo[uid][vGameID], VehicleInfo[uid][vHP]);
		UpdateVehicleDamageStatus(VehicleInfo[uid][vGameID], VehicleInfo[uid][vVisual][0], VehicleInfo[uid][vVisual][1], VehicleInfo[uid][vVisual][2], VehicleInfo[uid][vVisual][3]);

		SetVehicleVirtualWorld(VehicleInfo[uid][vGameID], VehicleInfo[uid][vWorldID]);
		LinkVehicleToInterior(VehicleInfo[uid][vGameID], VehicleInfo[uid][vInteriorID]);
		
		DestroyObject(VehicleInfo[uid][vPolice]);
		VehicleInfo[uid][vPolice] = 0;
			
		if(VehicleInfo[uid][vModel] == 509 || VehicleInfo[uid][vModel] == 510 || VehicleInfo[uid][vModel] == 481)
		{
			VehicleInfo[uid][vLocked] = false;
			VehicleInfo[uid][vEngineTogged] = true;
		}
		else
		{
			VehicleInfo[uid][vLocked] = true;
			VehicleInfo[uid][vEngineTogged] = false;
		}

		SetVehicleLock(VehicleInfo[uid][vGameID], VehicleInfo[uid][vLocked]);
		ChangeVehicleEngineStatus(VehicleInfo[uid][vGameID], VehicleInfo[uid][vEngineTogged]);

		i ++;
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d pojazdy/ów z bazy danych.", i);
	return 1;
}

public LoadBusStop()
{
    new uid, data[64], name_bus[128];
	mysql_query("SELECT * FROM `fc_bus`");

	mysql_store_result();
	
	if(mysql_num_rows() > MAX_BUSSTOP) printf("[ERROR][BUSSTOP] Limit przystankow w gamemode jest zbyt maly.");
	
	while(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>d", uid);
		sscanf(data, "p<|>ds[32]ffffff",
		BusStop[uid][bUID],
		BusStop[uid][bName],
		BusStop[uid][bPos][0],
		BusStop[uid][bPos][1],
		BusStop[uid][bPos][2],
		BusStop[uid][bRot][0],
		BusStop[uid][bRot][1],
		BusStop[uid][bRot][2]);

		format(name_bus, sizeof(name_bus), "{FFFFFF}Przystanek: {88CC54}%s\n{FFFFFF}Wpisz /bus by zaczekaæ na autobus.", BusStop[uid][bName]);

		BusStop[uid][bObject] = CreateDynamicObject(1257, BusStop[uid][bPos][0], BusStop[uid][bPos][1], BusStop[uid][bPos][2], BusStop[uid][bRot][0], BusStop[uid][bRot][1], BusStop[uid][bRot][2], 0);
		BusStop[uid][bLabel] = CreateDynamic3DTextLabel(name_bus, -1, BusStop[uid][bPos][0], BusStop[uid][bPos][1], BusStop[uid][bPos][2], 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d przystanków z bazy danych.", uid);
	return 1;
}

public LoadBurgers()
{
    new uid, data[128], i = 0;
	mysql_query("SELECT * FROM `fc_burgers`");

	mysql_store_result();

	if(mysql_num_rows() > MAX_BURGERS) printf("[ERROR][BURGERS] Limit burger shotow w gamemode jest zbyt maly.");

	while(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>d", uid);
		sscanf(data, "p<|>dfff",
											BurgerInfo[uid][burgerID],
											BurgerInfo[uid][burgerPos][0],
											BurgerInfo[uid][burgerPos][1],
											BurgerInfo[uid][burgerPos][2]);

		BurgerInfo[uid][burgerMarker] = CreateDynamicCP(BurgerInfo[uid][burgerPos][0], BurgerInfo[uid][burgerPos][1], BurgerInfo[uid][burgerPos][2], 1.0);
		i ++;
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d burger shotow z bazy danych.", i);
	return 1;
}

public LoadTexture()
{
	new result[128], i = 0;

    mysql_check();
	mysql_query("SELECT * FROM `fc_mmat_texture`");
    mysql_store_result();
    
    while(mysql_fetch_row_format(result, "|") == 1)
	{
	    new object, index, materialcolor, modelid, txdname[32], texturename[32];

		sscanf(result,  "p<|>ddxds[32]s[32]",	object,
		                                        index,
												materialcolor,
												modelid,
												txdname,
												texturename);

        new uid = GetObjectID(object);

        if(ObjectInfo[uid][oUID] && ObjectInfo[uid][oMMAT] == 0)
        {
			SetDynamicObjectMaterial(ObjectInfo[uid][oObject], index, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));
		}

		i++;
	}

	mysql_free_result();

	printf("[LOAD] Wczytano %d tekstur z bazy danych.", i);
	return 1;
}

public LoadMaterialText()
{
	new result[256], i = 0;

    mysql_check();
	mysql_query("SELECT * FROM `fc_mmat_text`");
    mysql_store_result();

    while(mysql_fetch_row_format(result, "|") == 1)
	{
	    new object, index, matsize, fontsize, bold, fontcolor, backcolor, align, fontface[32], text[64];

		sscanf(result,  "p<|>dddddxxds[32]s[64]",	object,
													index,
													matsize,
													fontsize,
													bold,
													fontcolor,
													backcolor,
													align,
													fontface,
													text);

        new uid = GetObjectID(object);

        if(ObjectInfo[uid][oUID] && ObjectInfo[uid][oMMAT] == 1)
        {
            new color_font = ShiftRGBAToABGR(fontcolor);
			new color_back = ShiftRGBAToABGR(backcolor);
			    
            SetDynamicObjectMaterialText(ObjectInfo[object][oObject], index, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
		}

		i++;
	}

	mysql_free_result();

	printf("[LOAD] Wczytano %d tekstur z bazy danych.", i);
	return 1;
}

public LoadDoors()
{
    new result[512], i = 0;

    mysql_check();
    mysql_query("SELECT * FROM `fc_doors`");
    mysql_store_result();

    if(mysql_num_rows() > MAX_DOORS) printf("[ERROR][DOORS] Limit drzwi w gamemode jest zbyt maly.");
    
    if(mysql_num_rows() > 0)
    {
        while(mysql_fetch_row_format(result, "|") == 1)
        {
            new uid;
            sscanf(result, "p<|>d", uid);
            sscanf(result,  "p<|>dddffffddffffdddds[31]ddds[128]dd",        DoorInfo[uid][dUID],
                                                                            DoorInfo[uid][dOwner],
                                                                            DoorInfo[uid][dOwnerType],
                                                                            DoorInfo[uid][dEnterX],
                                                                            DoorInfo[uid][dEnterY],
                                                                            DoorInfo[uid][dEnterZ],
                                                                            DoorInfo[uid][dEnterAng],
                                                                            DoorInfo[uid][dEnterInt],
                                                                            DoorInfo[uid][dEnterVw],
                                                                            DoorInfo[uid][dExitX],
                                                                            DoorInfo[uid][dExitY],
                                                                            DoorInfo[uid][dExitZ],
                                                                            DoorInfo[uid][dExitAng],
                                                                            DoorInfo[uid][dExitInt],
                                                                            DoorInfo[uid][dExitVw],
                                                                            DoorInfo[uid][dLock],
                                                                            DoorInfo[uid][dPickupID],
                                                                            DoorInfo[uid][dName],
                                                                            DoorInfo[uid][dGarage],
                                                                            DoorInfo[uid][dValue],
                                                                            DoorInfo[uid][dEnterCash],
                                                                            DoorInfo[uid][dAudioURL],
                                                                            DoorInfo[uid][dObject],
                                                                            DoorInfo[uid][dBlock]);

            if(DoorInfo[uid][dOwnerType] == OWNER_GROUP || DoorInfo[uid][dOwnerType] == OWNER_BANK)
            {
                DoorInfo[uid][dLock] = 1;
            }
            
			DoorInfo[uid][dAlarm] = false;

            DoorInfo[uid][Pickup] = CreateDynamicPickup(DoorInfo[uid][dPickupID], 1, DoorInfo[uid][dEnterX], DoorInfo[uid][dEnterY], DoorInfo[uid][dEnterZ], DoorInfo[uid][dEnterVw], DoorInfo[uid][dEnterInt]);
            PickupInfo[DoorInfo[uid][Pickup]][Name] = DoorInfo[uid][dName];
            i++;
        }
    }
    mysql_free_result();
    printf("[LOAD] Wczytano %d drzwi z bazy danych.", i);
    return 1;
}

public LoadItems()
{
    new uid, world, Float:pos_x, Float:pos_y, Float:pos_z, list = 0, data[64];
    mysql_query("SELECT `uid`, `world`, `pos_x`, `pos_y`, `pos_z` FROM `fc_items` WHERE `ownertype` = 0");

    mysql_store_result();
    
    if(mysql_num_rows() > MAX_ITEMS) printf("[ERROR][ITEMS] Limit przedmiotow w gamemode jest zbyt maly.");
    
    while(mysql_fetch_row_format(data, "|"))
    {
        list ++;
        sscanf(data, "p<|>ddfff",
        uid,
        world,
        pos_x,
        pos_y,
        pos_z);

        new object_id = GetFreeItemObjectID();
        ItemObject[object_id][objItemUID] = ItemInfo[uid][iUID];

        if(ItemInfo[uid][iType] == TYPE_WEAPON || ItemInfo[uid][iType] == TYPE_INHIBITOR || ItemInfo[uid][iType] == TYPE_PAINT)
        {
            ItemObject[object_id][objID] = CreateDynamicObject(WeaponModel[ItemInfo[uid][iValue1]], pos_x, pos_y, pos_z - 1.0, 80.0, 0.0, 0, world, -1, -1, 80.0);
        }
        else if(ItemInfo[uid][iType] == TYPE_ATTACH)
		{
		    ItemObject[object_id][objID] = CreateDynamicObject(ItemInfo[uid][iValue1], pos_x, pos_y, pos_z - 1.0, 80.0, 0.0, 0, world, -1, -1, 80.0);
		}
        else
        {
            ItemObject[object_id][objID] = CreateDynamicObject(ItemTypeInfo[ItemInfo[uid][iType]][iTypeObjModel], pos_x, pos_y, pos_z - 1.0, ItemTypeInfo[ItemInfo[uid][iType]][iTypeObjRotX], ItemTypeInfo[ItemInfo[uid][iType]][iTypeObjRotY], 0, world, -1, -1, 80.0);
        }
    }
    mysql_free_result();

    printf("[LOAD] Wczytano %d przedmiot/ów z bazy danych.", list);
}

public LoadPlants()
{
    new uid, data[64], name_plant[64], i = 0;
	mysql_query("SELECT * FROM `fc_plants`");

	mysql_store_result();

	if(mysql_num_rows() > MAX_PLANTS) printf("[ERROR][PLANTS] Limit roslin w gamemode jest zbyt maly.");

	while(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>d", uid);
		sscanf(data, "p<|>dfffdddddd",
		PlantInfo[uid][plantUID],
		PlantInfo[uid][plantX],
		PlantInfo[uid][plantY],
		PlantInfo[uid][plantZ],
		PlantInfo[uid][plantVw],
		PlantInfo[uid][plantInt],
		PlantInfo[uid][plantDoor],
		PlantInfo[uid][plantChar],
		PlantInfo[uid][plantType],
		PlantInfo[uid][plantProgress]);

		format(name_plant, sizeof(name_plant), "%s (%d)\n%d procent\nAby zebraæ u¿yj komendy /zbierz", NamePlant(PlantInfo[uid][plantType]), PlantInfo[uid][plantUID], PlantInfo[uid][plantProgress]);

		PlantInfo[uid][plantText] = Create3DTextLabel(name_plant, 0xFFFFFFBB, PlantInfo[uid][plantX], PlantInfo[uid][plantY], PlantInfo[uid][plantZ] - 0.2, 10.0, PlantInfo[uid][plantVw]);
		PlantInfo[uid][plantObject] = CreateDynamicObject(678, PlantInfo[uid][plantX], PlantInfo[uid][plantY], PlantInfo[uid][plantZ] - 1.0, 0, 0, 0, PlantInfo[uid][plantVw], PlantInfo[uid][plantInt]);

		i ++;
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d roslin z bazy danych.", i);
	return 1;
}

public LoadCorps()
{
    new uid, data[64], name_corp[24], i = 0;
	mysql_query("SELECT * FROM `fc_corps`");

	mysql_store_result();
	
	if(mysql_num_rows() > MAX_CORPS) printf("[ERROR][CORPS] Limit zwlok w gamemode jest zbyt maly.");
	
	while(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>d", uid);
		sscanf(data, "p<|>ddddddfffdd",
		CorpseInfo[uid][cUID],
		CorpseInfo[uid][cChar],
		CorpseInfo[uid][cReason],
		CorpseInfo[uid][cStatus],
		CorpseInfo[uid][cDate],
		CorpseInfo[uid][cFingers],
		CorpseInfo[uid][cPos][0],
		CorpseInfo[uid][cPos][1],
		CorpseInfo[uid][cPos][2],
		CorpseInfo[uid][cVw],
		CorpseInfo[uid][cWeaponUID]);

		format(name_corp, sizeof(name_corp), "Zw³oki (%d)", CorpseInfo[uid][cUID]);

		CorpseInfo[uid][cLabel] = Create3DTextLabel(name_corp, 0xFFFFFFBB, CorpseInfo[uid][cPos][0], CorpseInfo[uid][cPos][1], CorpseInfo[uid][cPos][2] - 0.2, 10.0, CorpseInfo[uid][cVw]);
		CorpseInfo[uid][cObject] = CreateDynamicObject(2060, CorpseInfo[uid][cPos][0], CorpseInfo[uid][cPos][1], CorpseInfo[uid][cPos][2] - 1.0, 0, 0, 0, CorpseInfo[uid][cVw]);

		i ++;
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d zwlok z bazy danych.", i);
	return 1;
}