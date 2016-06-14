forward RestartGMX();
forward AddBan(playerid);

stock IsAdminPermission(playerid, perm)
{
	if(CharacterCache[playerid][pAdminPermission] & perm)
	{
		return true;
	}
	else return false;
}

stock InfoAdmin(playerid, text[])
{
	new string[256];

	if(CharacterCache[playerid][pAdmin] == 9)
	{
		format(string, sizeof(string), "~r~~h~(GA) ~y~~h~~h~%s ~w~~h~%s", CharacterCache[playerid][pGlobalNick], text);
	}
	else if(CharacterCache[playerid][pAdmin] > 4 && CharacterCache[playerid][pAdmin] < 9)
	{
	    format(string, sizeof(string), "~g~~h~~h~(ADMIN) ~y~~h~~h~%s ~w~~h~%s", CharacterCache[playerid][pGlobalNick], text);
	}
	else if(CharacterCache[playerid][pAdmin] > 0 && CharacterCache[playerid][pAdmin] < 5)
	{
	    format(string, sizeof(string), "~b~~h~~h~(ASS) ~y~~h~~h~%s ~w~~h~%s", CharacterCache[playerid][pGlobalNick], text);
	}
	
	ForeachEx(i, MAX_PLAYERS)
	{
	    if(CharacterCache[i][pAdmin] && CharacterCache[i][pAdminDuty])
	    {
			PlayerTextDrawSetString(i, AdminInfo[i], string);
		}
	}
	return 1;
}

stock SendAdminMessage(color, const string[])
{
	ForeachEx(i, MAX_PLAYERS)
	{
	    if(CharacterCache[i][pAdmin] > 0 && CharacterCache[i][pAdminDuty])
  		{
	        SendClientMessage(i, color, string);
	    }
	}

	return 1;
}

public RestartGMX()
{
	SendRconCommand("gmx");
}

public AddBan(playerid)
{
	new query[256];
	
	format(query, sizeof(query), "INSERT INTO `fc_bans` VALUES (NULL, '%s', '%d')", GetAccountIP(playerid), CharacterCache[playerid][pGID]);
	
	mysql_check();
	mysql_query(query);
	
	return 1;
}