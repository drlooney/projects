forward UnspawnVehicle(gameid);
forward OnVehicleEngineStarted(vehicleid);
forward ShowPlayerVehicleInfo(playerid, gameid);
forward VehicleHaveItemType(vehicleid, type);
forward IsOwnerVehicle(playerid, vehid);
forward SaveVehicle(gameid, what);
forward DeleteVehicle(gameid);
forward CreateCar(modelid, Float:PosX, Float:PosY, Float:PosZ, Float:PosA, color1, color2, vw);
forward LoadVehicle(gameid);

public UnspawnVehicle(gameid)
{
	new vehid = GetVehicleID(gameid);
		
	ForeachEx(i, 14)
	{
	    if(VehicleInfo[vehid][vComponent][i] != 0)
	    {
	        irp_RemoveVehicleComponent(vehid, VehicleInfo[vehid][vComponent][i] + 999);
	    }
	}

	GetVehicleDamageStatus(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vVisual][0], VehicleInfo[vehid][vVisual][1], VehicleInfo[vehid][vVisual][2], VehicleInfo[vehid][vVisual][3]);
	GetVehicleHealth(VehicleInfo[vehid][vGameID], VehicleInfo[vehid][vHP]);

	SaveVehicle(vehid, SAVE_VEH_COUNT);
	DestroyVehicle(VehicleInfo[vehid][vGameID]);
	
	VehicleInfo[vehid][vUID] 			= 0;
	VehicleInfo[vehid][vModel] 			= 0;

	VehicleInfo[vehid][vPosX] 			= 0.0;
	VehicleInfo[vehid][vPosY] 			= 0.0;
	VehicleInfo[vehid][vPosZ] 			= 0.0;
	VehicleInfo[vehid][vPosA] 			= 0.0;

	VehicleInfo[vehid][vColor1] 		= 0;
	VehicleInfo[vehid][vColor2] 		= 0;

	VehicleInfo[vehid][vOwner] 			= 0;
	VehicleInfo[vehid][vOwnerType] 		= 0;

	VehicleInfo[vehid][vHP] 			= 0.0;
	VehicleInfo[vehid][vAccess] 		= 0;

	VehicleInfo[vehid][vVisual][0] 		= 0;
	VehicleInfo[vehid][vVisual][1] 		= 0;
	VehicleInfo[vehid][vVisual][2] 		= 0;
	VehicleInfo[vehid][vVisual][3] 		= 0;

	VehicleInfo[vehid][vFuel] 			= 0.0;
	VehicleInfo[vehid][vDistance] 		= 0.0;

	VehicleInfo[vehid][vEngineTogged] 	= false;

	VehicleInfo[vehid][vLocked] 		= false;
	VehicleInfo[vehid][vSpawned] 		= false;
		
	VehicleInfo[vehid][vBlock]			= 0;
	VehicleInfo[vehid][vSlot] 			= 0;

	VehicleInfo[vehid][vCompLoaded]		= false;
	VehicleInfo[vehid][vPaintJob] 		= 0;

	VehicleInfo[vehid][vGameID] 		= 0;
	
	DestroyObject(VehicleInfo[vehid][vPolice]);
	VehicleInfo[vehid][vPolice] = 0;
}

public LoadVehicle(gameid)
{		
	new visual[32], query[128], data[256], uid;
	
	format(query, sizeof(query), "SELECT * FROM `fc_vehicles` WHERE uid = '%d'", gameid);
	mysql_query(query);

	mysql_store_result();
	if(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>d", uid);
		sscanf(data, "p<|>ddfffffddddfs[12]dds[32]fdddd",
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
			
		sscanf(visual, "p<,>dddd", VehicleInfo[uid][vVisual][0],
								   VehicleInfo[uid][vVisual][1],
								   VehicleInfo[uid][vVisual][2], 
								   VehicleInfo[uid][vVisual][3]);

		VehicleInfo[uid][vGameID] = CreateVehicle(VehicleInfo[uid][vModel], VehicleInfo[uid][vPosX], VehicleInfo[uid][vPosY], VehicleInfo[uid][vPosZ], VehicleInfo[uid][vPosA], VehicleInfo[uid][vColor1], VehicleInfo[uid][vColor2], 7200);
		
		VehicleInfo[uid][vEngineTogged] = false;
		VehicleInfo[uid][vSpawned] = true;

		if(!VehicleInfo[uid][vPaintJob]) VehicleInfo[uid][vPaintJob] = 3;

		VehicleInfo[uid][vCompLoaded] = false;
			
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
	}
	
	mysql_free_result();
}

public CreateCar(modelid, Float:PosX, Float:PosY, Float:PosZ, Float:PosA, color1, color2, vw)
{
	new uid, query[256];
	format(query, sizeof(query), "INSERT INTO `fc_vehicles` (model, pos_x, pos_y, pos_z, pos_a, color_1, color_2, fuel, vw, hp, register) VALUES ('%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%f', '%s')", modelid, PosX, PosY, PosZ, PosA, color1, color2, GetVehicleMaxFuel(modelid), vw, 1000.0, "_");
	mysql_query(query);
	
	uid = mysql_insert_id();
	LoadVehicle(uid);
	
	mysql_free_result();
	return uid;
}

public DeleteVehicle(gameid)
{
	new query[256];
	format(query, sizeof(query), "DELETE FROM `fc_vehicles` WHERE `uid` = '%d'", VehicleInfo[gameid][vUID]);
	mysql_query(query);
	
	if(VehicleInfo[gameid][vOwnerType] == OWNER_PLAYER)
	{
	    new giveplayer_id = GetPlayerID(VehicleInfo[gameid][vOwner]);
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

	VehicleInfo[gameid][vUID] = 0;
	VehicleInfo[gameid][vModel] = 0;

	VehicleInfo[gameid][vPosX] = 0.0;
	VehicleInfo[gameid][vPosY] = 0.0;
	VehicleInfo[gameid][vPosZ] = 0.0;
	VehicleInfo[gameid][vPosA] = 0.0;
	
	VehicleInfo[gameid][vInteriorID] = 0;
	VehicleInfo[gameid][vWorldID] = 0;

	VehicleInfo[gameid][vColor1] = 0;
	VehicleInfo[gameid][vColor2] = 0;

	VehicleInfo[gameid][vOwner] = 0;
	VehicleInfo[gameid][vOwnerType] = 0;

	VehicleInfo[gameid][vHP] = 0.0;
	VehicleInfo[gameid][vAccess] = 0;
	
	VehicleInfo[gameid][vVisual][0] = 0;
	VehicleInfo[gameid][vVisual][1] = 0;
	VehicleInfo[gameid][vVisual][2] = 0;
	VehicleInfo[gameid][vVisual][3] = 0;

	VehicleInfo[gameid][vFuel] = 0.0;
	VehicleInfo[gameid][vDistance] = 0.0;

	VehicleInfo[gameid][vEngineTogged] = false;

	VehicleInfo[gameid][vBlock] = 0;
	VehicleInfo[gameid][vSlot] = 0;
	VehicleInfo[gameid][vLocked] = false;
	VehicleInfo[gameid][vSpawned] = false;

	VehicleInfo[gameid][vCompLoaded] = false;
	VehicleInfo[gameid][vPaintJob] = 0;
	
	DestroyObject(VehicleInfo[gameid][vPolice]);
	VehicleInfo[gameid][vPolice] = 0;
	
	DestroyVehicle(VehicleInfo[gameid][vGameID]);
	return 1;
}

public SaveVehicle(gameid, what)
{
	new main_query[512], query[256];
	format(main_query, sizeof(main_query), "UPDATE `fc_vehicles` SET");
	if(what & SAVE_VEH_POS)
	{
	    // Pozycja pojazdu
		format(query, sizeof(query), " `pos_x` = '%f', `pos_y` = '%f', `pos_z` = '%f', `pos_a` = '%f', `interior` = '%d', `vw` = '%d'",
		VehicleInfo[gameid][vPosX],
		VehicleInfo[gameid][vPosY],
		VehicleInfo[gameid][vPosZ],
		VehicleInfo[gameid][vPosA],
		VehicleInfo[gameid][vInteriorID],
		VehicleInfo[gameid][vWorldID]);

		if(strlen(main_query) > 32)
		{
		    strcat(main_query, ",", sizeof(main_query));
		}
  		strcat(main_query, query, sizeof(main_query));
	}
	if(what & SAVE_VEH_ACCESS)
	{
	    // Akcesoria pojazdu (kolory, rodzaj paliwa, paintjob, blokada na ko³o, akcesoria)
	    format(query, sizeof(query), " `color_1` = '%d', `color_2` = '%d', `access` = '%d', `paint_job` = '%d'",
	    VehicleInfo[gameid][vColor1],
	    VehicleInfo[gameid][vColor2],
		VehicleInfo[gameid][vAccess],
		VehicleInfo[gameid][vPaintJob]);
		
		if(strlen(main_query) > 32)
		{
		    strcat(main_query, ",", sizeof(main_query));
		}
  		strcat(main_query, query, sizeof(main_query));
	}
	if(what & SAVE_VEH_COUNT)
	{
	    // Liczniki (paliwo, przebieg, uszkodzenie techniczne, uszkodzenie wizualne, akumulator)
	    format(query, sizeof(query), " `hp` = '%f', `fuel` = '%f', `distance` = '%f', `visual` = '%d,%d,%d,%d'",
	    VehicleInfo[gameid][vHP],
	    VehicleInfo[gameid][vFuel],
		VehicleInfo[gameid][vDistance],
    	VehicleInfo[gameid][vVisual][0],
		VehicleInfo[gameid][vVisual][1],
		VehicleInfo[gameid][vVisual][2],
		VehicleInfo[gameid][vVisual][3]);
		
		if(strlen(main_query) > 32)
		{
		    strcat(main_query, ",", sizeof(main_query));
		}
  		strcat(main_query, query, sizeof(main_query));
	}
	if(what & SAVE_VEH_THINGS)
	{
	    // Pozosta³e (w³aœciciel, model, nazwa)
	    format(query, sizeof(query), " `owner` = '%d', `ownertype` = '%d', `model` = '%d', `register` = '%s', `block` = '%d', `slot` = '%d'",
	    VehicleInfo[gameid][vOwner],
	    VehicleInfo[gameid][vOwnerType],
	    VehicleInfo[gameid][vModel],
		VehicleInfo[gameid][vRegister],
		VehicleInfo[gameid][vBlock],
		VehicleInfo[gameid][vSlot]);
	    
		if(strlen(main_query) > 32)
		{
		    strcat(main_query, ",", sizeof(main_query));
		}
  		strcat(main_query, query, sizeof(main_query));
	}
	format(query, sizeof(query), " WHERE `uid` = '%d' LIMIT 1", VehicleInfo[gameid][vUID]);
	strcat(main_query, query, sizeof(main_query));
	
	mysql_query(main_query);
	return 1;
}

stock GetVehicleDriver(vehicleid)
{
	ForeachEx(i, MAX_PLAYERS)
	{
		if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
		{
		    if(GetPlayerVehicleID(i) == vehicleid)
		    {
		        return i;
		    }
		}
	}
	return INVALID_PLAYER_ID;
}

stock GetVehicleModelName(modelid)
{
	new tmp = modelid - 400;
	return VehicleName[tmp];
}

stock ChangeVehicleEngineStatus(vehicleid, bool: toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, toggle, lights, alarm, doors, bonnet, boot, objective);
	return toggle;
}

stock GetVehicleEngineStatus(vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return engine;
}

stock SetVehicleLock(vehicleid, bool: toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, engine, lights, alarm, toggle, bonnet, boot, objective);
	return toggle;
}

stock ChangeVehicleLightsStatus(vehicleid, bool: toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, engine, toggle, alarm, doors, bonnet, boot, objective);
	return toggle;
}

stock GetVehicleLightsStatus(vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return lights;
}

stock ChangeVehicleBonnetStatus(vehicleid, bool: toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, toggle, boot, objective);
	return toggle;
}

stock GetVehicleBonnetStatus(vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return bonnet;
}

stock ChangeVehicleBootStatus(vehicleid, bool: toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, toggle, objective);
	return toggle;
}

stock GetVehicleBootStatus(vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return boot;
}

stock GetVehicleUID(gameid)
{
	new list = 0;
	
	ForeachEx(i, MAX_VEHICLES)
	{
		if(VehicleInfo[i][vGameID] == gameid)
		{
			list = i;
		}
	}
	
	return list;
}

stock GetVehicleRotation(vehicleid, &Float: heading,  &Float: attitude,  &Float: bank)
{
    new
		Float: quat_w,
		Float: quat_x,
		Float: quat_y,
		Float: quat_z;

    GetVehicleRotationQuat(vehicleid, quat_w, quat_x, quat_y, quat_z);
    ConvertNonNormaQuatToEuler(quat_w, quat_x, quat_z, quat_y,  heading,  attitude,  bank);

	bank = -1 * bank;
    return 1;
}

stock GetVehicleMaxFuel(model)
{
	if(model == 400) return 70;
	else if(model == 401) return 52;
	else if(model == 402) return 60;
	else if(model == 403) return 400;
	else if(model == 404) return 50;
	else if(model == 405) return 52;
	else if(model == 406) return 150;
	else if(model == 407) return 250;
	else if(model == 408) return 150;
	else if(model == 409) return 110;
	else if(model == 410) return 66;
	else if(model == 411) return 66;
	else if(model == 412) return 52;
	else if(model == 413) return 80;
	else if(model == 414) return 120;
	else if(model == 415) return 76;
	else if(model == 416) return 120;
	else if(model == 417) return 408;
	else if(model == 418) return 80;
	else if(model == 419) return 72;
	else if(model == 420) return 80;
	else if(model == 421) return 82;
	else if(model == 422) return 80;
	else if(model == 423) return 90;
	else if(model == 424) return 30;
	else if(model == 425) return 500;
	else if(model == 426) return 70;
	else if(model == 427) return 120;
	else if(model == 428) return 120;
	else if(model == 429) return 68;
	else if(model == 430) return 220;
	else if(model == 431) return 315;
	else if(model == 432) return 1020;
	else if(model == 433) return 430;
	else if(model == 434) return 30;
	else if(model == 435) return 0;
	else if(model == 436) return 60;
	else if(model == 437) return 310;
	else if(model == 438) return 80;
	else if(model == 439) return 72;
	else if(model == 440) return 80;
	else if(model == 441) return 0;
	else if(model == 442) return 61;
	else if(model == 443) return 180;
	else if(model == 444) return 162;
	else if(model == 445) return 56;
	else if(model == 446) return 101;
	else if(model == 447) return 140;
	else if(model == 448) return 7;
	else if(model == 449) return 100;
	else if(model == 450) return 0;
	else if(model == 451) return 78;
	else if(model == 452) return 111;
	else if(model == 453) return 201;
	else if(model == 454) return 221;
	else if(model == 455) return 198;
	else if(model == 456) return 101;
	else if(model == 457) return 15;
	else if(model == 458) return 70;
	else if(model == 459) return 84;
	else if(model == 460) return 30;
	else if(model == 461) return 25;
	else if(model == 462) return 7;
	else if(model == 463) return 30;
	else if(model == 464) return 0;
	else if(model == 465) return 0;
	else if(model == 466) return 71;
	else if(model == 467) return 61;
	else if(model == 468) return 27;
	else if(model == 469) return 50;
	else if(model == 470) return 110;
	else if(model == 471) return 35;
	else if(model == 472) return 110;
	else if(model == 473) return 69;
	else if(model == 474) return 70;
	else if(model == 475) return 71 ;
	else if(model == 476) return 68;
	else if(model == 477) return 69;
	else if(model == 478) return 45;
	else if(model == 479) return 61;
	else if(model == 480) return 67;
	else if(model == 481) return 0;
	else if(model == 482) return 96;
	else if(model == 483) return 75;
	else if(model == 484) return 87;
	else if(model == 485) return 40;
	else if(model == 486) return 141;
	else if(model == 487) return 123;
	else if(model == 488) return 121;
	else if(model == 489) return 91;
	else if(model == 490) return 101;
	else if(model == 491) return 81;
	else if(model == 492) return 62;
	else if(model == 493) return 130;
	else if(model == 494) return 99;
	else if(model == 495) return 81;
	else if(model == 496) return 61;
	else if(model == 497) return 140;
	else if(model == 498) return 121;
	else if(model == 499) return 104;
	else if(model == 500) return 71;
	else if(model == 501) return 0;
	else if(model == 502) return 96;
	else if(model == 503) return 97;
	else if(model == 504) return 91;
	else if(model == 505) return 84;
	else if(model == 506) return 67;
	else if(model == 507) return 81;
	else if(model == 508) return 133;
	else if(model == 509) return 0;
	else if(model == 510) return 0;
	else if(model == 511) return 210;
	else if(model == 512) return 130;
	else if(model == 513) return 54;
	else if(model == 514) return 300;
	else if(model == 515) return 300;
	else if(model == 516) return 63;
	else if(model == 517) return 64;
	else if(model == 518) return 67;
	else if(model == 519) return 300;
	else if(model == 520) return 290;
	else if(model == 521) return 35;
	else if(model == 522) return 35;
	else if(model == 523) return 121;
	else if(model == 524) return 91;
	else if(model == 525) return 65;
	else if(model == 526) return 63;
	else if(model == 527) return 71;
	else if(model == 528) return 71;
	else if(model == 529) return 67;
	else if(model == 530) return 12;
	else if(model == 531) return 21;
	else if(model == 532) return 36;
	else if(model == 533) return 61;
	else if(model == 534) return 71;
	else if(model == 535) return 85;
	else if(model == 536) return 69;
	else if(model == 537) return 100;
	else if(model == 538) return 100;
	else if(model == 539) return 33;
	else if(model == 540) return 60;
	else if(model == 541) return 71;
	else if(model == 542) return 69;
	else if(model == 543) return 60;
	else if(model == 544) return 120;
	else if(model == 545) return 74;
	else if(model == 546) return 64;
	else if(model == 547) return 67;
	else if(model == 548) return 210;
	else if(model == 549) return 71;
	else if(model == 550) return 64;
	else if(model == 551) return 64;
	else if(model == 552) return 68;
	else if(model == 553) return 330;
	else if(model == 554) return 81;
	else if(model == 555) return 61;
	else if(model == 556) return 123;
	else if(model == 557) return 124;
	else if(model == 558) return 61;
	else if(model == 559) return 63;
	else if(model == 560) return 71;
	else if(model == 561) return 74;
	else if(model == 562) return 66;
	else if(model == 563) return 210;
	else if(model == 564) return 0;
	else if(model == 565) return 57;
	else if(model == 566) return 65;
	else if(model == 567) return 66;
	else if(model == 568) return 45;
	else if(model == 569) return 0;
	else if(model == 570) return 0;
	else if(model == 571) return 10;
	else if(model == 572) return 10;
	else if(model == 573) return 121;
	else if(model == 574) return 21;
	else if(model == 575) return 71;
	else if(model == 576) return 75;
	else if(model == 577) return 900;
	else if(model == 578) return 210;
	else if(model == 579) return 85;
	else if(model == 580) return 80;
	else if(model == 581) return 31;
	else if(model == 582) return 81;
	else if(model == 583) return 20;
	else if(model == 584) return 0;
	else if(model == 585) return 64;
	else if(model == 586) return 30;
	else if(model == 587) return 66;
	else if(model == 588) return 79;
	else if(model == 589) return 59;
	else if(model == 590) return 0;
	else if(model == 591) return 0;
	else if(model == 592) return 0;
	else if(model == 593) return 110;
	else if(model == 594) return 0;
	else if(model == 595) return 151;
	else if(model == 596) return 89;
	else if(model == 597) return 89;
	else if(model == 598) return 89;
	else if(model == 599) return 94;
	else if(model == 600) return 61;
	else if(model == 601) return 120;
	else if(model == 602) return 61;
	else if(model == 603) return 59;
	else if(model == 604) return 91;
	else if(model == 605) return 64;
	else if(model == 606) return 0;
	else if(model == 607) return 0;
	else if(model == 608) return 0;
	else if(model == 609) return 99;
	else if(model == 610) return 0;
	else if(model == 611) return 0;
	else return 0;
}

stock GetVehicleID(vehuid)
{
	new vehid = INVALID_VEHICLE_ID;
	ForeachEx(i, MAX_VEHICLES)
	{
		if(VehicleInfo[i][vUID] == vehuid)
		{
			vehid = i;
		}
	}
	
	return vehid;
}

stock GetDistanceToVehicle(playerid,carid)
{
	new Float:x1, Float:y1, Float:z1,
		Float:x2, Float:y2, Float:z2, Float:dis;
		
	GetPlayerPos(playerid, x1, y1, z1);
	GetVehiclePos(carid, x2, y2, z2);

	dis = floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
	return floatround(dis);
}

stock IsParkingPlaceFree(vehid)
{
	new Float:posx, Float:posy, Float:posz, world, free = 1, query[512];
 	GetVehiclePos(vehid, posx, posy, posz);
 	
 	world = GetVehicleVirtualWorld(VehicleInfo[vehid][vGameID]);

  	format(query, sizeof(query), "SELECT uid FROM `fc_vehicles` WHERE pos_x < %f + 2 AND pos_x > %f - 2 AND pos_y < %f + 2 AND pos_y > %f - 2 AND pos_z < %f + 2 AND pos_z > %f - 2 AND vw = '%d' LIMIT 1", posx, posx, posy, posy, posz, posz, world);
   	mysql_query(query);
	
    mysql_store_result();
    if(mysql_num_rows())
    {
    	free = 0;
    }
    mysql_free_result();
    
	return free;
}

public IsOwnerVehicle(playerid, vehid)
{
	new bool:value;

	if(CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_VEHICLES)
	{
		value = true;		
	}
	else if(VehicleInfo[vehid][vOwnerType] == OWNER_PLAYER)
	{
		if(VehicleInfo[vehid][vOwner] == CharacterCache[playerid][pUID])
		{
			value = true;
		}
		else
		{
			value = false;
		}
	}
	else if(VehicleInfo[vehid][vOwnerType] == OWNER_GROUP)
	{
		ForeachEx(slot, MAX_PLAYER_GROUPS)
	 	{
		    if(VehicleInfo[vehid][vOwner] == MemberGroup[playerid][slot][GroupID])
		    {
		    	if(VehicleInfo[vehid][vSlot] == 0)
				{
					if(IsPlayerPermInGroup(playerid, MemberGroup[playerid][slot][GroupID], PANEL_VEH))
					{
						value = true;
					}
					else
					{
						value = false;
					}
				}
				else if(VehicleInfo[vehid][vSlot] == 1)
				{
					if(IsPlayerPermInGroup(playerid, MemberGroup[playerid][slot][GroupID], PANEL_SPECIAL_VEH))
					{
						value = true;
					}
					else
					{
						value = false;
					}
				}
				else
				{
					value = false;
				}
		    }
		    else
		    {
		    	value = false;
		    }
		}
	}
	else if(VehicleInfo[vehid][vOwnerType] == OWNER_SUBGROUP)
	{
		ForeachEx(slot, MAX_PLAYER_GROUPS)
	 	{
		    if(VehicleInfo[vehid][vOwner] == MemberGroup[playerid][slot][GroupSubGroup])
		    {
		    	if(VehicleInfo[vehid][vSlot] == 0)
				{
					if(IsPlayerPermInGroup(playerid, MemberGroup[playerid][slot][GroupID], PANEL_VEH))
					{
						value = true;
					}
					else
					{
						value = false;
					}
				}
				else if(VehicleInfo[vehid][vSlot] == 1)
				{
					if(IsPlayerPermInGroup(playerid, MemberGroup[playerid][slot][GroupID], PANEL_SPECIAL_VEH))
					{
						value = true;
					}
					else
					{
						value = false;
					}
				}
				else
				{
					value = false;
				}
		    }
		    else
		    {
		    	value = false;
		    }
		}
	}
	else
	{
		value = false;
	}

	return value;
}

stock IsAircraft(model)
{
	if(model == 417 || model == 425 || model == 447 || model == 460 || model == 469 || model == 476 || model == 487 || model == 488 || model == 497 || model == 511 || model == 512 || model == 513 || model == 519 || model == 520 || model == 548 || model == 553 || model == 563 || model == 577 || model == 592 || model == 593)
	{
	    return true;
	}
	else
	{
	    return false;
	}
}

stock IsSeatFree(vehid, seatid)
{
	ForeachEx(i, MAX_PLAYERS)
	{
	    if(Logged[i])
	    {
	        if(GetPlayerVehicleID(i) == vehid)
	        {
	            if(GetPlayerVehicleSeat(i) == seatid)
	            {
	                return false;
	            }
	        }
	    }
	}
	return true;
}

public VehicleHaveItemType(vehicleid, type)
{
    new query[256];
    format(query, sizeof(query), "SELECT * FROM `fc_items` WHERE `kind` = '%d' AND `owner` = '%d' AND `ownertype` = '%d'", type, VehicleInfo[vehicleid][vUID], OWNER_VEHICLE);
    mysql_query(query);
    mysql_store_result();
    if(mysql_num_rows())
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

public ShowPlayerVehicleInfo(playerid, gameid)
{
    new list_stats[512], string[128];

    format(list_stats, sizeof(list_stats), "Model:\t\t\t%s (%d)", GetVehicleModelName(VehicleInfo[gameid][vModel]), VehicleInfo[gameid][vModel]);
    format(list_stats, sizeof(list_stats), "%s\nKolory:\t\t\t%d/%d\n", list_stats, VehicleInfo[gameid][vColor1], VehicleInfo[gameid][vColor2]);
    if(VehicleInfo[gameid][vOwnerType] == OWNER_NONE)
    {
        format(list_stats, sizeof(list_stats), "%s\nTyp w³aœciciela:\t\tBrak\n", list_stats);
    }
    if(VehicleInfo[gameid][vOwnerType] == OWNER_PLAYER)
    {
        format(list_stats, sizeof(list_stats), "%s\nTyp w³aœciciela:\t\tGracz\n", list_stats);
        format(list_stats, sizeof(list_stats), "%s\nUID gracza:\t\t%d\n", list_stats, VehicleInfo[gameid][vOwner]);
    }
    if(VehicleInfo[gameid][vOwnerType] == OWNER_GROUP)
    {
        format(list_stats, sizeof(list_stats), "%s\nTyp w³aœciciela:\t\tGrupa\n", list_stats);
        format(list_stats, sizeof(list_stats), "%s\nNazwa grupy:\t\t%s\n", list_stats, GroupData[VehicleInfo[gameid][vOwner]][Desc]);
    }
    if(VehicleInfo[gameid][vOwnerType] == OWNER_SUBGROUP)
    {
        format(list_stats, sizeof(list_stats), "%s\nTyp w³aœciciela:\t\tPodgrupa\n", list_stats);
        format(list_stats, sizeof(list_stats), "%s\nNazwa podgrupy:\t\t%s\n", list_stats, SubData[VehicleInfo[gameid][vOwner]][sDesc]);
    }
    if(VehicleInfo[gameid][vHP] <= 650)
    {
        format(list_stats, sizeof(list_stats), "%s\n\nStan techniczny:\t{FFC675}%.1f{FFFFFF} HP\n", list_stats, VehicleInfo[gameid][vHP]);
    }
    else
    {
        format(list_stats, sizeof(list_stats), "%s\n\nStan techniczny:\t{8CD147}%.1f HP\n", list_stats, VehicleInfo[gameid][vHP]);
    }
    format(list_stats, sizeof(list_stats), "%s\n\nPaliwo:\t\t\t%d/%d L\n", list_stats, floatround(VehicleInfo[gameid][vFuel]), GetVehicleMaxFuel(VehicleInfo[gameid][vModel]));
    format(list_stats, sizeof(list_stats), "%s\nPrzebieg:\t\t%0.1f KM\n", list_stats, VehicleInfo[gameid][vDistance]);

    format(string, sizeof(string), "%s (sampID: %d, UID: %d) » Informacje", GetVehicleModelName(VehicleInfo[gameid][vModel]), gameid, VehicleInfo[gameid][vUID]);
    ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, string, list_stats, "Zamknij", "");
    return 1;
}

public OnVehicleEngineStarted(vehicleid)
{
    new playerid = GetVehicleDriver(VehicleInfo[vehicleid][vGameID]);
    if(playerid == INVALID_PLAYER_ID)
    {
        return 1;
    }
    if(VehicleInfo[vehicleid][vFuel] <= 0)
    {
        ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, "Informacja", "W tym pojeŸdzie nie ma paliwa.\nZatankuj pojazd, aby móc odpaliæ silnik.", "Zamknij", "");
        return 1;
    }

    VehicleInfo[vehicleid][vEngineTogged] = true;
    ChangeVehicleEngineStatus(VehicleInfo[vehicleid][vGameID], VehicleInfo[vehicleid][vEngineTogged]);

    GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~w~Aby zgasic pojazd uzyj ~r~/silnik", 3000, 3);
    return 1;
}

stock irp_AddVehicleComponent(vehicleid, componentid)
{
	new slot = GetVehicleComponentType(componentid);
	if(slot != -1)
	{
	    AddVehicleComponent(VehicleInfo[vehicleid][vGameID], componentid);
	    VehicleInfo[vehicleid][vComponent][slot] = componentid - 999;
	}
	return 1;
}

stock irp_RemoveVehicleComponent(vehicleid, componentid)
{
	new slot = GetVehicleComponentType(componentid);
	if(slot != 1)
	{
	    RemoveVehicleComponent(VehicleInfo[vehicleid][vGameID], componentid);
	    VehicleInfo[vehicleid][vComponent][slot] = 0;
	}
	return 1;
}