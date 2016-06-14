forward ProxDetector(Float:radi, playerid, string[],col1,col2,col3,col4,col5);
forward GetPhoneID(number);
forward KickWithWait(i);
forward KickPlayer(i);
forward SaveBusStop(uid);
forward AddBusStop(playerid, name[32]);
forward DeleteBusStop(uid);
forward DeleteBurger(uid);
forward AddBurger(playerid);
forward DeleteSensor(uid);
forward AddSensor(playerid, name[32]);
forward AddCorpse(playerid, reason, weapon);
forward SaveCorpse(uid);
forward DeleteCorpse(uid);
forward AddPlant(playerid, type);
forward SavePlant(uid);
forward DeletePlant(uid);
forward DeleteReport(uid);
forward AddReport(playerid, groupid, text[512]);
forward DeleteAttach(uid);
forward SaveAttach(uid);
forward AddAttach(modelid, itemid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ);
forward AddLabel(playerid, ownertype, owner, Float:range, text[256], vw, int);
forward SaveLabel(uid);
forward DeleteLabel(uid);

public DeleteLabel(uid)
{
	LabelInfo[uid][labelID] = 0;

	LabelInfo[uid][labelRange] = 0;
	LabelInfo[uid][labelText] = 0;

	LabelInfo[uid][labelPos][0] = 0.0;
	LabelInfo[uid][labelPos][1] = 0.0;
	LabelInfo[uid][labelPos][2] = 0.0;

	LabelInfo[uid][labelOwner] = 0;
	LabelInfo[uid][labelOwnerType] = 0;

	LabelInfo[uid][labelVw] = 0;
	LabelInfo[uid][labelInt] = 0;

	DestroyDynamic3DTextLabel(LabelInfo[uid][label3D]);
	return 1;
}

public SaveLabel(uid)
{
	mysql_query_format("UPDATE `fc_3dtext` SET `label_range` = '%f', `label_x` = '%f', `label_y` = '%f', `label_z` = '%f', `label_owner` = '%d', `label_ownertype` = '%d', `label_vw` = '%d', `label_int` = '%d' WHERE `label_uid` = '%d'",
	LabelInfo[uid][labelRange],
	LabelInfo[uid][labelPos][0],
	LabelInfo[uid][labelPos][1],
	LabelInfo[uid][labelPos][2],
	LabelInfo[uid][labelOwner],
	LabelInfo[uid][labelOwnerType],
	LabelInfo[uid][labelVw],
	LabelInfo[uid][labelInt],
	LabelInfo[uid][labelID]);
	return 1;
}

public AddLabel(playerid, ownertype, owner, Float:range, text[256], vw, int)
{
	new Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

	mysql_check();
	mysql_query_format("INSERT INTO `fc_3dtext` VALUES (NULL, '%s', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d')", text, range, Pos[0], Pos[1], Pos[2], owner, ownertype, vw, int);

	new uid = mysql_insert_id();

	LabelInfo[uid][labelID] = uid;
	LabelInfo[uid][labelRange] = range;

	format(LabelInfo[uid][labelText], 256, "%s", text);

	LabelInfo[uid][labelPos][0] = Pos[0];
	LabelInfo[uid][labelPos][1] = Pos[1];
	LabelInfo[uid][labelPos][2] = Pos[2];

	LabelInfo[uid][labelOwner] = owner;
	LabelInfo[uid][labelOwnerType] = ownertype;

	LabelInfo[uid][labelVw] = vw;
	LabelInfo[uid][labelInt] = int;

	EscapeLabel(text);

	LabelInfo[uid][label3D] = CreateDynamic3DTextLabel(WordWrap(text, 7), 0xFFFFFFFF, Pos[0], Pos[1], Pos[2], range, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, vw, int, -1, 80.0);

	return uid;
}

public AddAttach(modelid, itemid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	mysql_check();
	mysql_query_format("INSERT INTO `fc_attached_object` (`model`, `itemid`, `fOffsetX`, `fOffsetY`, `fOffsetZ`, `fRotX`, `fRotY`, `fRotZ`, `fScaleX`, `fScaleY`, `fScaleZ`) VALUES ('%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f')", modelid, itemid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);

	new uid = mysql_insert_id();

	AttachInfo[uid][aUID] = uid;
	AttachInfo[uid][aModel] = modelid;
	AttachInfo[uid][aitemID] = itemid;
	
	AttachInfo[uid][afOffsetX] = fOffsetX;
	AttachInfo[uid][afOffsetY] = fOffsetY;
	AttachInfo[uid][afOffsetZ] = fOffsetZ;
	
	AttachInfo[uid][afRotX] = fRotX;
	AttachInfo[uid][afRotY] = fRotY;
	AttachInfo[uid][afRotZ] = fRotZ;
	
	AttachInfo[uid][afScaleX] = fScaleX;
	AttachInfo[uid][afScaleY] = fScaleY;
	AttachInfo[uid][afScaleZ] = fScaleZ;

	return uid;
}

public SaveAttach(uid)
{
	mysql_check();
	mysql_query_format("UPDATE `fc_attached_object` SET `model` = '%d', `itemid` = '%d', `fOffsetX` = '%f', `fOffsetY` = '%f', `fOffsetZ` = '%f', `fRotX` = '%f', `fRotY` = '%f', `fRotZ` = '%f', `fScaleX` = '%f', `fScaleY` = '%f', `fScaleZ` = '%f' WHERE `uid` = '%d'",
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
	AttachInfo[uid][afScaleZ],
	AttachInfo[uid][aUID]);

	return 1;
}

public DeleteAttach(uid)
{
	mysql_check();
	mysql_query_format("DELETE FROM `fc_attached_object` WHERE `uid` = '%d'", uid);

	AttachInfo[uid][aUID] = 0;
	AttachInfo[uid][aModel] = 0;
	AttachInfo[uid][aitemID] = 0;
	
	AttachInfo[uid][afOffsetX] = 0;
	AttachInfo[uid][afOffsetY] = 0;
	AttachInfo[uid][afOffsetZ] = 0;
	
	AttachInfo[uid][afRotX] = 0;
	AttachInfo[uid][afRotY] = 0;
	AttachInfo[uid][afRotZ] = 0;
	
	AttachInfo[uid][afScaleX] = 0;
	AttachInfo[uid][afScaleY] = 0;
	AttachInfo[uid][afScaleZ] = 0;

	return 1;
}

stock ComparisonString(text1[], text2[])
{
    new cmpTest1 = strlen(text1);
    new cmpTest2 = strlen(text2);
    if(cmpTest1 == cmpTest2)
    {
        new BAD = 0;
        for(new c = 0; c < cmpTest1; c++)
        {
            if(text1[c] == text2[c]) continue;
            else
            {
                BAD = 1;
                break;
            }
        }
        if(BAD == 1) return false;
        else return true;
    }
    return false;
}

stock GetPlayedTimeSecZ(zmienna, &hours, &minutes, &second)
{
	hours 	= zmienna / 3600;
	minutes = (zmienna - hours * 3600) / 60;
	second 	= ((zmienna - (hours * 3600)) - (minutes * 60));
	return 1;
}

stock EscapeLabel(name[])
{
    for(new i = 0; name[i] != 0; i++)
    {
        if(name[i] == '|') name[i] = '\n';
        else if(name[i] == '(') name[i] = '{';
        else if(name[i] == ')') name[i] = '}';
    }
}

stock dechex(number)
{
	new hexadecimal_string[15];
	format(hexadecimal_string, 15, "%x", number);
	return hexadecimal_string;
}

stock NamePlant(type)
{
	new name[32];
	
	switch(type)
	{
	    case DRUG_META: format(name, sizeof(name), "Metamfetamina");
	    case DRUG_COCAINE: format(name, sizeof(name), "Kokaina");
	    case DRUG_MAR: format(name, sizeof(name), "Marihuana");
	}
	
	return name;
}

public AddReport(playerid, groupid, text[512])
{
	if(GroupData[groupid][UID])
	{
		new uid = ReportNum + 1;

		ReportInfo[uid][reportID] = uid;
		ReportInfo[uid][reportChar] = CharacterCache[playerid][pUID];
		ReportInfo[uid][reportGroup] = GroupData[groupid][UID];

		GetPlayerPos(playerid, ReportInfo[uid][reportPos][0], ReportInfo[uid][reportPos][1], ReportInfo[uid][reportPos][2]);

        format(ReportInfo[uid][reportCharName], 32, "%s", PlayerName2(playerid));
		format(ReportInfo[uid][reportText], 512, "%s", text);
	}

	return 1;
}

public DeleteReport(uid)
{
	ReportInfo[uid][reportID] = 0;
	ReportInfo[uid][reportChar] = 0;
	ReportInfo[uid][reportGroup] = 0;

	ReportInfo[uid][reportPos][0] = 0.0;
	ReportInfo[uid][reportPos][1] = 0.0;
	ReportInfo[uid][reportPos][2] = 0.0;

	ReportInfo[uid][reportText] = 0;

	return 1;
}

public DeletePlant(uid)
{
	mysql_check();
	mysql_query_format("DELETE FROM `fc_plants` WHERE `uid` = '%d'", PlantInfo[uid][plantUID]);

	PlantInfo[uid][plantUID] = 0;
	
	PlantInfo[uid][plantX] = 0.0;
	PlantInfo[uid][plantY] = 0.0;
	PlantInfo[uid][plantZ] = 0.0;
	
	PlantInfo[uid][plantVw] = 0;
	PlantInfo[uid][plantInt] = 0;
	
	PlantInfo[uid][plantDoor] = 0;
	PlantInfo[uid][plantChar] = 0;
	
	PlantInfo[uid][plantType] = 0;
	PlantInfo[uid][plantProgress] = 0;

	Delete3DTextLabel(PlantInfo[uid][plantText]);
	DestroyDynamicObject(PlantInfo[uid][plantObject]);
	return 1;
}

public SavePlant(uid)
{
	mysql_check();
	mysql_query_format("UPDATE `fc_plants` SET `x` = '%f', `y` = '%f', `z` = '%f', `vw` = '%d', `int` = '%d', `doorid` = '%d', `char_id` = '%d', `type` = '%d', `progress` = '%d' WHERE `uid` = '%d'",
	PlantInfo[uid][plantX],
	PlantInfo[uid][plantY],
	PlantInfo[uid][plantZ],
	PlantInfo[uid][plantVw],
	PlantInfo[uid][plantInt],
	PlantInfo[uid][plantDoor],
	PlantInfo[uid][plantChar],
	PlantInfo[uid][plantType],
	PlantInfo[uid][plantProgress],
	PlantInfo[uid][plantUID]);
	
	return 1;
}

public AddPlant(playerid, type)
{
    new Float:Pos[3], name_plant[64];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

	mysql_check();
	mysql_query_format("INSERT INTO `fc_plants` VALUES (NULL, '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%d', '%d')", Pos[0], Pos[1], Pos[2], GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), PlayerDoor[playerid], CharacterCache[playerid][pUID], type, 0);

	new uid = mysql_insert_id();

	PlantInfo[uid][plantUID] = uid;
	
	PlantInfo[uid][plantX] = Pos[0];
	PlantInfo[uid][plantY] = Pos[1];
	PlantInfo[uid][plantZ] = Pos[2];
	
	PlantInfo[uid][plantVw] = GetPlayerVirtualWorld(playerid);
	PlantInfo[uid][plantInt] = GetPlayerInterior(playerid);
	
	PlantInfo[uid][plantDoor] = PlayerDoor[playerid];
	PlantInfo[uid][plantChar] = CharacterCache[playerid][pUID];
	
	PlantInfo[uid][plantType] = type;
	PlantInfo[uid][plantProgress] = 0;

	format(name_plant, sizeof(name_plant), "%s (%d)\n%d procent\nAby zebraÊ uøyj komendy /zbierz", NamePlant(PlantInfo[uid][plantType]), PlantInfo[uid][plantUID], PlantInfo[uid][plantProgress]);

	PlantInfo[uid][plantText] = Create3DTextLabel(name_plant, 0xFFFFFFBB, PlantInfo[uid][plantX], PlantInfo[uid][plantY], PlantInfo[uid][plantZ] - 0.2, 10.0, PlantInfo[uid][plantVw]);
	PlantInfo[uid][plantObject] = CreateDynamicObject(678, PlantInfo[uid][plantX], PlantInfo[uid][plantY], PlantInfo[uid][plantZ] - 1.0, 0, 0, 0, PlantInfo[uid][plantVw], PlantInfo[uid][plantInt]);

	return uid;
}

public DeleteCorpse(uid)
{
	new query[100];
	format(query, sizeof(query), "DELETE FROM `fc_corps` WHERE `corp_uid` = '%d'", CorpseInfo[uid][cUID]);

	mysql_check();
	mysql_query(query);

	CorpseInfo[uid][cUID] 		= 0;
	CorpseInfo[uid][cChar] 		= 0;
	CorpseInfo[uid][cReason] 	= 0;
	CorpseInfo[uid][cStatus] 	= 0;
	CorpseInfo[uid][cDate] 		= 0;
	CorpseInfo[uid][cFingers] 	= 0;
	CorpseInfo[uid][cPos][0] 	= 0;
	CorpseInfo[uid][cPos][1] 	= 0;
	CorpseInfo[uid][cPos][2] 	= 0;
	CorpseInfo[uid][cVw]		= 0;
	CorpseInfo[uid][cWeaponUID] = 0;

	Delete3DTextLabel(CorpseInfo[uid][cLabel]);
	DestroyDynamicObject(CorpseInfo[uid][cObject]);
	return 1;
}

public SaveCorpse(uid)
{
	new query[512];

	format(query, sizeof(query), "UPDATE `fc_corps` SET `corp_char` = '%d', `corp_reason` = '%d', `corp_status` = '%d', `corp_date` = '%d', `corp_fingers` = '%d', `corp_pos_x` = '%f', `corp_pos_y` = '%f', `corp_pos_z` = '%f', `corp_vw` = '%d', `corp_weapon` = '%d' WHERE `corp_uid` = '%d'",
	CorpseInfo[uid][cChar],
	CorpseInfo[uid][cReason],
	CorpseInfo[uid][cStatus],
	CorpseInfo[uid][cDate],
	CorpseInfo[uid][cFingers],
	CorpseInfo[uid][cPos][0],
	CorpseInfo[uid][cPos][1],
	CorpseInfo[uid][cPos][2],
	CorpseInfo[uid][cVw],
	CorpseInfo[uid][cWeaponUID],
	CorpseInfo[uid][cUID]);

	mysql_query(query);
	return 1;
}

public AddCorpse(playerid, reason, weapon)
{
	new Float:Pos[3], name_corp[24];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

	mysql_check();
	mysql_query_format("INSERT INTO `fc_corps` VALUES (NULL, '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%d', '%d')",
	CharacterCache[playerid][pUID], reason, 100, gettime(), 1, Pos[0], Pos[1], Pos[2] - 2.0, GetPlayerVirtualWorld(playerid), weapon);

    new uid = mysql_insert_id();

   	CorpseInfo[uid][cUID] = uid;
	CorpseInfo[uid][cChar] = CharacterCache[playerid][pUID];
	
	CorpseInfo[uid][cReason] = reason;
	CorpseInfo[uid][cStatus] = 100;
	
	CorpseInfo[uid][cDate] = gettime();
	CorpseInfo[uid][cFingers] = 1;
	
	CorpseInfo[uid][cPos][0] = Pos[0];
	CorpseInfo[uid][cPos][1] = Pos[1];
	CorpseInfo[uid][cPos][2] = Pos[2];
	
	CorpseInfo[uid][cVw] = GetPlayerVirtualWorld(playerid);
	CorpseInfo[uid][cWeaponUID] = weapon;

	format(name_corp, sizeof(name_corp), "Zw≥oki (%d)", CorpseInfo[uid][cUID]);

	CorpseInfo[uid][cLabel] = Create3DTextLabel(name_corp, 0xFFFFFFBB, CorpseInfo[uid][cPos][0], CorpseInfo[uid][cPos][1], CorpseInfo[uid][cPos][2] - 0.2, 10.0, CorpseInfo[uid][cVw]);
	CorpseInfo[uid][cObject] = CreateDynamicObject(2060, CorpseInfo[uid][cPos][0], CorpseInfo[uid][cPos][1], CorpseInfo[uid][cPos][2] - 1.0, 0, 0, 0, 0);

    mysql_free_result();

	return uid;
}

public AddSensor(playerid, name[32])
{
    new Float:Pos[3], name_sensor[64];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	
	mysql_check();
	mysql_query_format("INSERT INTO `fc_sensors` VALUES (NULL, '%s', '%f', '%f', '%f')", name, Pos[0], Pos[1], Pos[2]);
	
	new uid = mysql_insert_id();
	
	SensorInfo[uid][sensorID] = uid;
	format(SensorInfo[uid][sensorName], 32, "%s", name);
	
	SensorInfo[uid][sensorPos][0] = Pos[0];
	SensorInfo[uid][sensorPos][1] = Pos[1];
	SensorInfo[uid][sensorPos][2] = Pos[2];
	
	format(name_sensor, sizeof(name_sensor), "Czujnik podczerwieni\n%s (%d)", SensorInfo[uid][sensorName], SensorInfo[uid][sensorID]);
	SensorInfo[uid][sensorText] = Create3DTextLabel(name_sensor, 0xFFFFFFBB, SensorInfo[uid][sensorPos][0], SensorInfo[uid][sensorPos][1], SensorInfo[uid][sensorPos][2] - 0.2, 10.0, 0);
	
	return uid;
}

public DeleteSensor(uid)
{
	mysql_check();
	mysql_query_format("DELETE FROM `fc_sensors` WHERE `uid` = '%d'", uid);
	
	SensorInfo[uid][sensorID] = 0;
	SensorInfo[uid][sensorName]= 0;

	SensorInfo[uid][sensorPos][0] = 0.0;
	SensorInfo[uid][sensorPos][1] = 0.0;
	SensorInfo[uid][sensorPos][2] = 0.0;
	
	return 1;
}

public AddBurger(playerid)
{
	new Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	
    mysql_check();
	mysql_query_format("INSERT INTO `fc_burgers` VALUES (NULL, '%f', '%f', '%f')", Pos[0], Pos[1], Pos[2]);
	
	new uid = mysql_insert_id();
	
	BurgerInfo[uid][burgerID] = uid;
	
	BurgerInfo[uid][burgerPos][0] = Pos[0];
	BurgerInfo[uid][burgerPos][1] = Pos[1];
	BurgerInfo[uid][burgerPos][2] = Pos[2];
	
	BurgerInfo[uid][burgerMarker] = CreateDynamicCP(BurgerInfo[uid][burgerPos][0], BurgerInfo[uid][burgerPos][1], BurgerInfo[uid][burgerPos][2], 1.0);
	return 1;
}

public DeleteBurger(uid)
{
    mysql_check();
	mysql_query_format("DELETE FROM `fc_burgers` WHERE `uid` = '%d'", uid);
	
	BurgerInfo[uid][burgerID] = 0;

	BurgerInfo[uid][burgerPos][0] = 0;
	BurgerInfo[uid][burgerPos][1] = 0;
	BurgerInfo[uid][burgerPos][2] = 0;
	
	DestroyDynamicCP(BurgerInfo[uid][burgerMarker]);
	
	return 1;
}

public DeleteBusStop(uid)
{
	new query[100];
	format(query, sizeof(query), "DELETE FROM `fc_bus` WHERE `uid` = '%d'", BusStop[uid][bUID]);

	mysql_check();
	mysql_query(query);

	BusStop[uid][bUID] 		= 0;

	BusStop[uid][bPos][0] 	= 0;
	BusStop[uid][bPos][0] 	= 0;
	BusStop[uid][bPos][0] 	= 0;

	BusStop[uid][bRot][0] 	= 0;
	BusStop[uid][bRot][1] 	= 0;
	BusStop[uid][bRot][2] 	= 0;

	BusStop[uid][bName] 	= 0;

	DestroyDynamic3DTextLabel(BusStop[uid][bLabel]);
	DestroyDynamicObject(BusStop[uid][bObject]);

	mysql_free_result();
	return 1;
}

public AddBusStop(playerid, name[32])
{
	new Float:Pos[3], name_bus[128];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

	new query[256];
	format(query, sizeof(query), "INSERT INTO `fc_bus` VALUES (NULL, '%s', '%f', '%f', '%f', '%f', '%f', '%f')",
	name, Pos[0], Pos[1] + 2.0, Pos[2], 0.0, 0.0, 0.0);

	mysql_query(query);

    new uid = mysql_insert_id();

   	BusStop[uid][bUID] 		= uid;

	BusStop[uid][bPos][0] 	= Pos[0];
	BusStop[uid][bPos][1] 	= Pos[1] + 2.0;
	BusStop[uid][bPos][2] 	= Pos[2];

	BusStop[uid][bRot][0] 	= 0.0;
	BusStop[uid][bRot][1] 	= 0.0;
	BusStop[uid][bRot][2] 	= 0.0;

	format(BusStop[uid][bName], 32, "%s", name);

	format(name_bus, sizeof(name_bus), "{FFFFFF}Przystanek: {88CC54}%s\n{FFFFFF}Wpisz /bus by zaczekaÊ na autobus.", BusStop[uid][bName]);

	BusStop[uid][bObject] = CreateDynamicObject(1257, Pos[0], Pos[1] + 2.0, Pos[2], BusStop[uid][bRot][0], BusStop[uid][bRot][1], BusStop[uid][bRot][2], 0);
	BusStop[uid][bLabel] = CreateDynamic3DTextLabel(name_bus, -1, Pos[0], Pos[1] + 2.0, Pos[2], 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);

    mysql_free_result();

	return uid;
}

public SaveBusStop(uid)
{
	new query[256];

	format(query, sizeof(query), "UPDATE `fc_bus` SET `pos_x` = '%f', `pos_y` = '%f', `pos_z` = '%f', `rot_x` = '%f', `rot_y` = '%f', `rot_z` = '%f', `name` = '%s' WHERE `uid` = '%d'",
	BusStop[uid][bPos][0],
	BusStop[uid][bPos][1],
	BusStop[uid][bPos][2],
	BusStop[uid][bRot][0],
	BusStop[uid][bRot][1],
	BusStop[uid][bRot][2],
	BusStop[uid][bName],
	BusStop[uid][bUID]);

	mysql_query(query);

	new name_bus[128];
	format(name_bus, sizeof(name_bus), "{FFFFFF}Przystanek: {88CC54}%s\n{FFFFFF}Wpisz /bus by zaczekaÊ na autobus.", BusStop[uid][bName]);

	DestroyDynamic3DTextLabel(BusStop[uid][bLabel]);
	BusStop[uid][bLabel] = CreateDynamic3DTextLabel(name_bus, -1, BusStop[uid][bPos][0], BusStop[uid][bPos][1], BusStop[uid][bPos][2], 20.0);
}

stock CheckItemAttach(itemid)
{
	new a = 0;
	
	ForeachEx(i, MAX_ATTACH)
	{
	    if(AttachInfo[i][aitemID] == itemid)
	    {
	        a = i;
	    }
	}

	return a;
}

stock WordWrap(givenString[], spaces)
{
	new editingString[128], spaceCounter = 0;
	memcpy(editingString, givenString, 0, 128 * 4);

	for (new i = 0; editingString[i] != 0; i++)
	{
	    if(editingString[i] == ',' || editingString[i] == '.')
	    {
			if(editingString[i+1] != ' ') strins(editingString, " ", i + 1);
		}

	    if(editingString[i] == ' ' && editingString[i+1] != ' ') spaceCounter++;

	    if(spaceCounter >= spaces)
		{
			editingString[i] = '\n';
			spaceCounter = 0;
		}
	}
	return editingString;
}

stock IsHexValue(hstring[])
{
	if(strlen(hstring) < 10) return 0;
	if(hstring[0] == 48 && hstring[1] == 120)
	{
		for(new i = 2; i < 10; i++)
		{
			if(hstring[i] == 48 || hstring[i] == 49 || hstring[i] == 50 || hstring[i] == 51 || hstring[i] == 52 ||
				hstring[i] == 53 || hstring[i] == 54 || hstring[i] == 55 || hstring[i] == 56 || hstring[i] == 57 ||
				hstring[i] == 65 || hstring[i] == 66 || hstring[i] == 67 || hstring[i] == 68 || hstring[i] == 69 ||
				hstring[i] == 70) continue;
			else return 0;
		}
	}
	else return 0;
	return 1;
}

stock HexToInt(string[])
{
    if (string[0] == 0)
    {
        return 0;
    }
    new i;
    new cur = 1;
    new res = 0;
    for (i = strlen(string); i > 0; i--)
    {
        if (string[i-1] < 58)
        {
            res = res + cur * (string[i - 1] - 48);
        }
        else
        {
            res = res + cur * (string[i-1] - 65 + 10);
            cur = cur * 16;
        }
    }
    return res;
}

stock Convert_RGBToHex(r, g, b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b & 0xFF) << 0));
}

stock Convert_HexToDecimal(color)
{
	return color >>> 8;
}

stock MakeColorDarker(r1, g1, b1, percent)
{
	new
		r,
		g,
		b,
		Float:percentage = (100 - percent) + 0.1;
    
	r = floatround(r1 * percentage / 100);
	g = floatround(g1 * percentage / 100);
	b = floatround(b1 * percentage / 100);

	new color = r << 24 | g << 16 | b << 8 | 0xFF;
	
	return color;
}

stock MakeColorLighter(r1, g1, b1, percent)
{
	new
		r,
		g,
		b,
		Float:percentage = (100 - percent) + 0.1;
    
	r = floatround(r1 * percentage / 100) + floatround(255 - percentage / 100 * 255);
	g = floatround(g1 * percentage / 100) + floatround(255 - percentage / 100 * 255);
	b = floatround(b1 * percentage / 100) + floatround(255 - percentage / 100 * 255);

	new color = r << 24 | g << 16 | b << 8 | 0xFF;
	
	return color;
}

stock GetWeaponType(weaponid)
{
	new type = WEAPON_TYPE_NONE;

	switch(weaponid)
	{
		case 22, 23, 24, 26, 28, 32:
			type = WEAPON_TYPE_LIGHT;

		case 3, 4, 16, 17, 18, 39, 10, 11, 12, 13, 14, 40, 41:
			type = WEAPON_TYPE_MELEE;

		case 2, 5, 6, 7, 8, 9, 25, 27, 29, 30, 31, 33, 34, 35, 36, 37, 38:
			type = WEAPON_TYPE_HEAVY;
	}

	return type;
}

stock GetPlayerSQLName(sqlid)
{
    new nick[32];
    
	if(sqlid == 0)
	{
		format(nick, sizeof(nick), "Brak");
	}
	else
	{
		new query[128];
		format(query, sizeof(query), "SELECT `name` FROM `fc_characters` WHERE `player_uid` = '%d' LIMIT 1", sqlid);

		mysql_check();
		mysql_query(query);

		mysql_store_result();
		mysql_fetch_row_format(nick, "");

		UnderscoreToSpace(nick);
		mysql_free_result();
	}
	
	return nick;
}

stock timestamp_to_date(unix_timestamp = 0, &year = 1970, &mies = 1, &day = 1, &hour = 0, &minute = 0, &second = 0)
{
	year = unix_timestamp / 31557600;
	unix_timestamp -= year * 31557600;
	year += 1970;

	if ( year % 4 == 0 ) unix_timestamp -= 21600;

	day = unix_timestamp / 86400;

	switch ( day )
	{
		case    0..30 : { second = day;       mies =  1; }
		case   31..58 : { second = day -  31; mies =  2; }
		case   59..89 : { second = day -  59; mies =  3; }
		case  90..119 : { second = day -  90; mies =  4; }
		case 120..150 : { second = day - 120; mies =  5; }
		case 151..180 : { second = day - 151; mies =  6; }
		case 181..211 : { second = day - 181; mies =  7; }
		case 212..242 : { second = day - 212; mies =  8; }
		case 243..272 : { second = day - 243; mies =  9; }
		case 273..303 : { second = day - 273; mies = 10; }
		case 304..333 : { second = day - 304; mies = 11; }
		case 334..366 : { second = day - 334; mies = 12; }
	}

	unix_timestamp -= day * 86400;
	hour = unix_timestamp / 3600;

	unix_timestamp -= hour * 3600;
	minute = unix_timestamp / 60;

	unix_timestamp -= minute * 60;
	day = second + 1;
	second = unix_timestamp;
}

public KickPlayer(i)
{
	Kick(i);
	return 1;
}

public KickWithWait(i)
{
	SetTimerEx("KickPlayer", 350, false, "i", i);
}

stock UniqueCode(string[MAX_STRING_TO_CODE],key1,key2,key3,key4,key5)
{
	new length = strlen(string),string2[MAX_STRING_TO_CODE];
    for(new i = 0; i < length; i++)
    {
   		string2[i] = (string[i]-key1)+key2-key3+key4+key5;
    }
    
    return string2;
}

stock AssCode(playerid)
{
	new text[32];
	new string1[32];
	new char1[5], char2[5], char3[5], char4[4];
	new charcode2[5];
	
	format(text, sizeof(text), "%d", CharacterCache[playerid][pUID]);
	
	strmid(charcode2, MD5_Hash(text), 0, strlen(MD5_Hash(text)), 255);
	strmid(char1, charcode2[0], 0, 1, 255);
	strmid(char2, charcode2[1], 0, 1, 255);
	strmid(char3, charcode2[2], 0, 1, 255);
	strmid(char4, charcode2[3], 0, 1, 255);
	
	format(string1, sizeof(string1), "%s%s%s%s", char1, char2, char3, char4);
	strtoupper(string1);
	
	return string1;
}

stock CharCode(playerid)
{
	new text[32];
	new string1[32];
	new char1[5], char2[5], char3[5], char4[4];
	new charcode2[5];
	
	format(text, sizeof(text), "%d", CharacterCache[playerid][pUID]);
	
	strmid(charcode2, MD5_Hash(text), 0, strlen(MD5_Hash(text)), 255);
	strmid(char1, charcode2[0], 0, 1, 255);
	strmid(char2, charcode2[1], 0, 1, 255);
	strmid(char3, charcode2[2], 0, 1, 255);
	strmid(char4, charcode2[3], 0, 1, 255);
	
	format(string1, sizeof(string1), "%s%s%s%s", char1, char2, char3, char4);
	strtoupper(string1);
	
	return string1;
}

stock strtoupper(string[])
{
        for(new l, i = strlen(string); l < i; l++)
        string[l] = toupper(string[l]);
}

stock ShiftRGBAToABGR(&color)
{
    new r, g, b, a;
    r = (color >>> 24);
    g = (color >>> 16 & 0xFF);
    b = (color >>> 8 & 0xFF);
    a = (color  & 0xFF);
    color = (a & 0xFF) | ((b & 0xFF) << 8) | ((g & 0xFF) << 16) | (r << 24);
    return color;
}

stock GetFCNPCID(uid)
{
	new id = 0;
	
	ForeachEx(i, MAX_GANGS)
	{
	    if(uid == GangInfo[i][gangNPC])
	    {
	        id = i;
	    }
	}
	
	return id;
}

public GetPhoneID(number)
{
	new data[12], owner, ownertype;
	
	mysql_check();
	mysql_query_format("SELECT `ownertype`, `owner` FROM `fc_items` WHERE `kind` = '%d' AND `value1` = '%d' AND `ownertype` = '%d'", TYPE_PHONE, number, OWNER_PLAYER);
	
  	mysql_store_result();
  	
  	if(mysql_num_rows() > 0)
  	{
	    mysql_fetch_row_format(data, "|");

	    sscanf(data, "p<|>dd", ownertype, owner);
		mysql_free_result();
		
		return GetPlayerID(owner);
	}
	else
	{
	    return INVALID_PLAYER_ID;
	}
}

stock Sirene(uid)
{
    ForeachEx(i, sizeof(SyrenaPos))
    {
        if(SyrenaPos[i][VehicleID] == VehicleInfo[uid][vModel]) return SyrenaPos[i][SPU]-1;
    }
    return false;
}

stock EscapeTildes(givenString[])
{
	new pos, editingString[64];
    memcpy(editingString, givenString, 0, 64 * 4);

	pos = strfind(editingString, "~", true);
    while(pos != -1)
    {
        strdel(editingString, pos, pos + 1);
        pos = strfind(editingString, "~", true, pos + 1);
    }
	return editingString;
}

stock EscapePL(name[])
{
    for(new i = 0; name[i] != 0; i++)
    {
        if(name[i] == 'ú') name[i] = 's';
        else if(name[i] == 'Í') name[i] = 'e';
        else if(name[i] == 'Û') name[i] = 'o';
        else if(name[i] == 'π') name[i] = 'a';
        else if(name[i] == '≥') name[i] = 'l';
        else if(name[i] == 'ø') name[i] = 'z';
        else if(name[i] == 'ü') name[i] = 'z';
        else if(name[i] == 'Ê') name[i] = 'c';
        else if(name[i] == 'Ò') name[i] = 'n';
        else if(name[i] == 'å') name[i] = 'S';
        else if(name[i] == ' ') name[i] = 'E';
        else if(name[i] == '”') name[i] = 'O';
        else if(name[i] == '•') name[i] = 'A';
        else if(name[i] == '£') name[i] = 'L';
        else if(name[i] == 'Ø') name[i] = 'Z';
        else if(name[i] == 'è') name[i] = 'Z';
        else if(name[i] == '∆') name[i] = 'C';
        else if(name[i] == '—') name[i] = 'N';
    }
}

stock EscapeMMAT(name[])
{
    for(new i = 0; name[i] != 0; i++)
    {
        if(name[i] == '|') name[i] = '\n';

    }
}

public ProxDetector(Float:radi, playerid, string[],col1,col2,col3,col4,col5)
{
    if(IsPlayerConnected(playerid)){
        new Float:posx, Float:posy, Float:posz;
        new Float:oldposx, Float:oldposy, Float:oldposz;
        new Float:tempposx, Float:tempposy, Float:tempposz;
        GetPlayerPos(playerid, oldposx, oldposy, oldposz);
        new vir=GetPlayerVirtualWorld(playerid);
        ForeachEx(i, MAX_PLAYERS){
            if(IsPlayerConnected(i)&&GetPlayerVirtualWorld(i)==vir){
                    GetPlayerPos(i, posx, posy, posz);
                    tempposx = (oldposx -posx);
                    tempposy = (oldposy -posy);
                    tempposz = (oldposz -posz);
                    if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16))){
                        SendClientMessage(i, col1, string);
                    }
                    else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8))){
                        SendClientMessage(i, col2, string);
                    }
                    else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4))){
                        SendClientMessage(i, col3, string);
                    }
                    else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2))){
                        SendClientMessage(i, col4, string);
                    }
                    else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))){
                        SendClientMessage(i, col5, string);
                    }
            }
        }
    }
    return 1;
}