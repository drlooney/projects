forward GetPlayerArea(playerid);
forward IsOwnerArea(playerid, areaid);
forward IsPlayerInArea(playerid, areaid);
forward IsPositionInArea(areaid, Float:x, Float:y);
forward AddArea(Float:x, Float:y, Float:x2, Float:y2);
forward DeleteArea(uid);
forward SaveArea(uid);

public SaveArea(uid)
{
	new query[256];
	format(query, sizeof(query), "UPDATE `fc_areas` SET `pos_x_1` = '%f', `pos_x_2` = '%f', `pos_y_1` = '%f', `pos_y_2` = '%f', `owner` = '%d', `ownertype` = '%d', `limit` = '%d' WHERE `uid` = '%d'",
	AreaInfo[uid][aPos_x][0], AreaInfo[uid][aPos_x][1], AreaInfo[uid][aPos_y][0], AreaInfo[uid][aPos_y][1], AreaInfo[uid][aOwner], AreaInfo[uid][aOwnerType], AreaInfo[uid][aLimitObject], AreaInfo[uid][aUID]);
	mysql_query(query);

	return 1;
}

public DeleteArea(uid)
{
	new query[100];
	format(query, sizeof(query), "DELETE FROM `fc_areas` WHERE `uid` = '%d'", AreaInfo[uid][aUID]);

	mysql_check();
	mysql_query(query);

	AreaInfo[uid][aUID] = 0;
	AreaInfo[uid][aOwner] = 0;
	AreaInfo[uid][aOwnerType] = 0;
	AreaInfo[uid][aPos_x][0] = 0;
	AreaInfo[uid][aPos_x][1] = 0;
	AreaInfo[uid][aPos_y][0] = 0;
	AreaInfo[uid][aPos_y][1] = 0;
	AreaInfo[uid][aLimitObject] = 0;

	mysql_free_result();
	return 1;
}

public AddArea(Float:x, Float:y, Float:x2, Float:y2)
{
	new query[256];
	format(query, sizeof(query), "INSERT INTO `fc_areas` VALUES (NULL, '%f', '%f', '%f', '%f', '%d', '%d', 50)",
	x, x2, y, y2, 0, 0);
	
	mysql_query(query);

    new uid = mysql_insert_id();

   	AreaInfo[uid][aUID] 		= uid;
	AreaInfo[uid][aOwnerType] 	= OWNER_NONE;
	AreaInfo[uid][aOwner] 		= 0;
	AreaInfo[uid][aPos_x][0] 	= x;
	AreaInfo[uid][aPos_y][0] 	= y;
	AreaInfo[uid][aPos_x][1] 	= x2;
	AreaInfo[uid][aPos_y][1] 	= y2;
	AreaInfo[uid][aLimitObject] = 50;

    mysql_free_result();

	return uid;
}

public IsPositionInArea(areaid, Float:x, Float:y)
{
	new highestx, highesty, lowestx, lowesty;
	new retarn = 0;
	if(AreaInfo[areaid][aPos_x][0] > AreaInfo[areaid][aPos_x][1])
	{
		highestx = 0;
		lowestx = 1;
	}
	else if(AreaInfo[areaid][aPos_x][0] < AreaInfo[areaid][aPos_x][1])
	{
		highestx = 1;
		lowestx = 0;
	}
	if(AreaInfo[areaid][aPos_y][0] > AreaInfo[areaid][aPos_y][1])
	{
		highesty = 0;
		lowesty = 1;
	}
	else if(AreaInfo[areaid][aPos_y][0] < AreaInfo[areaid][aPos_y][1])
	{
		highesty = 1;
		lowesty = 0;
	}
	if(AreaInfo[areaid][aPos_x][highestx] > x && AreaInfo[areaid][aPos_x][lowestx] < x)
	{
		if(AreaInfo[areaid][aPos_y][highesty] > y && AreaInfo[areaid][aPos_y][lowesty] < y)
		{
			retarn = 1;
		}
	}
	return retarn;
}

public IsPlayerInArea(playerid, areaid)
{
	new highestx, highesty, lowestx, lowesty;
	new retarn = 0;
	if(AreaInfo[areaid][aPos_x][0] > AreaInfo[areaid][aPos_x][1])
	{
		highestx = 0;
		lowestx = 1;
	}
	else if(AreaInfo[areaid][aPos_x][0] < AreaInfo[areaid][aPos_x][1])
	{
		highestx = 1;
		lowestx = 0;
	}
	if(AreaInfo[areaid][aPos_y][0] > AreaInfo[areaid][aPos_y][1])
	{
		highesty = 0;
		lowesty = 1;
	}
	else if(AreaInfo[areaid][aPos_y][0] < AreaInfo[areaid][aPos_y][1])
	{
		highesty = 1;
		lowesty = 0;
	}
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	if(AreaInfo[areaid][aPos_x][highestx] > x && AreaInfo[areaid][aPos_x][lowestx] < x)
	{
		if(AreaInfo[areaid][aPos_y][highesty] > y && AreaInfo[areaid][aPos_y][lowesty] < y)
		{
			retarn = 1;
		}
	}
	return retarn;
}

public GetPlayerArea(playerid)
{
	new retarn = 0;
	ForeachEx(i, MAX_AREAS)
	{
		new highestx, highesty, lowestx, lowesty;
		if(AreaInfo[i][aPos_x][0] > AreaInfo[i][aPos_x][1])
		{
			highestx = 0;
			lowestx = 1;
		}
		else if(AreaInfo[i][aPos_x][0] < AreaInfo[i][aPos_x][1])
		{
			highestx = 1;
			lowestx = 0;
		}
		if(AreaInfo[i][aPos_y][0] > AreaInfo[i][aPos_y][1])
		{
			highesty = 0;
			lowesty = 1;
		}
		else if(AreaInfo[i][aPos_y][0] < AreaInfo[i][aPos_y][1])
		{
			highesty = 1;
			lowesty = 0;
		}
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		if(AreaInfo[i][aPos_x][highestx] > x && AreaInfo[i][aPos_x][lowestx] < x)
		{
			if(AreaInfo[i][aPos_y][highesty] > y && AreaInfo[i][aPos_y][lowesty] < y)
			{
				retarn = i;
			}
		}
	}
	return retarn;
}

public IsOwnerArea(playerid, areaid)
{
    if(AreaInfo[areaid][aOwnerType] == OWNER_GROUP && MemberGroup[playerid][1][GroupID] == AreaInfo[areaid][aOwner] && IsPlayerPermInGroup(playerid, MemberGroup[playerid][1][GroupID], PANEL_OBJECT) ||
       AreaInfo[areaid][aOwnerType] == OWNER_GROUP && MemberGroup[playerid][2][GroupID] == AreaInfo[areaid][aOwner] && IsPlayerPermInGroup(playerid, MemberGroup[playerid][2][GroupID], PANEL_OBJECT) ||
       AreaInfo[areaid][aOwnerType] == OWNER_GROUP && MemberGroup[playerid][3][GroupID] == AreaInfo[areaid][aOwner] && IsPlayerPermInGroup(playerid, MemberGroup[playerid][3][GroupID], PANEL_OBJECT) ||
       CharacterCache[playerid][pAdminPermission] & ADMIN_PERM_AREA)
    {
        return true;
    }
    else return false;
}

