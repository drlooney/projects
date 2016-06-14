forward ReloadGroupIcons();
forward SendMessageToGroup(groupid, color, text[]);
forward AddMember(playerid, uid, bool:leader, bool:head);
forward CountMembersCrimeInDoor(groupid, doorid);
forward SaveGroup(uid);
forward DeleteGroup(uid);
forward AddGroup(desc[32], kind, tag[12], admin);
forward CountMembersGroup(group_type);
forward CountMemberGroupOnDuty(group_uid);
forward IsPlayerInSubGroup(playerid, gameid);
forward IsPlayerInGroup(playerid, gameid);
forward HaveFreeSlotGroup(playerid);
forward GetGroupKind(group_kind);
forward IsPlayerOfficalGroup(playerid);
forward IsPlayerKindGroup(playerid, kind);
forward IsGroupHaveFlag(groupid, flag);
forward IsPermGroupFlag(playerid, flag);
forward IsPlayerPermGroupType(playerid, group_kind, perm);
forward IsPlayerPerm(playerid, perm);
forward IsPlayerPermInGroup(playerid, groupid, perm);
forward IsPermGroupTypeOnType(playerid, kind);
forward IsPlayerPermOnDuty(playerid, perm);

public IsPlayerPermOnDuty(playerid, perm)
{
	if(!DutyGroup[playerid]) return 1;
	new groupid = DutyGroup[playerid];
	
	ForeachEx(slot, MAX_PLAYER_GROUPS)
	{
		if(MemberGroup[playerid][slot][GroupID] == groupid)
		{
			if(MemberGroup[playerid][slot][GroupPerm] & perm)
			{
				return true;
			}
		}
	}
	
	return false;
}

public IsPermGroupTypeOnType(playerid, kind)
{
	new groupid = DutyGroup[playerid];
	new return_value = 0;

	if(GroupData[groupid][Kind] == kind)
	{
		return_value = GroupData[groupid][UID];
	}
	else return_value = 0;

	return return_value;
}

public IsPlayerPermInGroup(playerid, groupid, perm)
{
	ForeachEx(slot, MAX_PLAYER_GROUPS)
	{
		if(MemberGroup[playerid][slot][GroupID] == groupid)
		{
			if(MemberGroup[playerid][slot][GroupPerm] & perm)
			{
				return true;
			}
		}
	}
	
	return false;
}

public IsPlayerPerm(playerid, perm)
{
	ForeachEx(slot, MAX_PLAYER_GROUPS)
	{
		if(MemberGroup[playerid][slot][GroupPerm] & perm)
		{
			return true;
		}
	}
	
	return false;
}

public IsPlayerPermGroupType(playerid, group_kind, perm)
{
	ForeachEx(slot, MAX_PLAYER_GROUPS)
	{
		if(GroupData[MemberGroup[playerid][slot][GroupID]][Kind] == group_kind)
		{
			if(MemberGroup[playerid][slot][GroupPerm] & perm)
			{
				return true;
			}
		}
		else return false;
	}
	
	return false;
}

public IsPermGroupFlag(playerid, flag)
{
	if(GroupData[MemberGroup[playerid][1][GroupID]][Flags] & flag) return MemberGroup[playerid][1][GroupID];
	else if(GroupData[MemberGroup[playerid][2][GroupID]][Flags] & flag) return MemberGroup[playerid][2][GroupID];
	else if(GroupData[MemberGroup[playerid][3][GroupID]][Flags] & flag) return MemberGroup[playerid][3][GroupID];
	else return false;
}

public IsGroupHaveFlag(groupid, flag)
{
	if(GroupData[groupid][UID])
	{
		if(GroupData[groupid][Flags] & flag)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

public IsPlayerKindGroup(playerid, kind)
{
	for(new slot = 1; slot < 4; slot++)
	{
		if(GroupData[MemberGroup[playerid][slot][GroupID]][Kind] == kind)
		{
			return MemberGroup[playerid][slot][GroupID];
		}
	}
	
	return 1;
}

stock getPlayerOfficalGroup(playerid)
{
	new tag[12],
		group_id = DutyGroup[playerid];
		
	if(IsPlayerOfficalGroup(playerid))
	{
		format(tag, sizeof(tag), "[%s]", GroupData[group_id][Tag]);
	}
	
	return tag;
}

public IsPlayerOfficalGroup(playerid)
{
	new group_id = DutyGroup[playerid];
		
	if(GroupData[group_id][Kind] == GROUP_PD || GroupData[group_id][Kind] == GROUP_FBI || GroupData[group_id][Kind] == GROUP_SS || GroupData[group_id][Kind] == GROUP_GOV || GroupData[group_id][Kind] == GROUP_MC || GroupData[group_id][Kind] == GROUP_FD || GroupData[group_id][Kind] == GROUP_RADIO || GroupData[group_id][Kind] == GROUP_BORDER)
	{
		return true;
	}
	else return false;
}

public GetGroupKind(group_kind)
{
	new group_id = 0;

	ForeachEx(i, MAX_GROUPS)
	{
		if(GroupData[i][Kind] == group_kind)
		{
			group_id = i;
		}
	}

	return group_id;
}

public HaveFreeSlotGroup(playerid)
{
	if(!MemberGroup[playerid][1][GroupID]) return true;
	else if(!MemberGroup[playerid][2][GroupID]) return true;
	else if(!MemberGroup[playerid][3][GroupID]) return true;
	else return false;
}

public IsPlayerInGroup(playerid, gameid)
{
	if(MemberGroup[playerid][1][GroupID] == gameid) return true;
	else if(MemberGroup[playerid][2][GroupID] == gameid) return true;
	else if(MemberGroup[playerid][3][GroupID] == gameid) return true;
	else return false;
}

public IsPlayerInSubGroup(playerid, gameid)
{
	if(MemberGroup[playerid][1][GroupSubGroup] == gameid) return true;
	else if(MemberGroup[playerid][2][GroupSubGroup] == gameid) return true;
	else if(MemberGroup[playerid][3][GroupSubGroup] == gameid) return true;
	else return false;
}

public CountMemberGroupOnDuty(group_uid)
{
	new count = 0;
	
	ForeachEx(i, MAX_PLAYERS)
	{
		if(DutyGroup[i] == group_uid)
		{
			count ++;
		}
	}
	
	return count;
}

public CountMembersGroup(group_type)
{
	new count = 0;
	
	ForeachEx(i, MAX_PLAYERS)
	{
		if(IsPermGroupTypeOnType(i, group_type))
		{
			count ++;
		}
	}
	
	return count;
}

public AddGroup(desc[32], kind, tag[12], admin)
{
	new desc1[32], tag1[12];
	mysql_real_escape_string(desc, desc1);
	mysql_real_escape_string(tag, tag1);

	mysql_query_format("INSERT INTO `fc_groups` (`desc`, `kind`, `tag`, `admin`, `chat`, `license`) VALUES ('%s', '%d', '%s', '%d', '255,255,255', '%d')", desc1, kind, tag1, admin, gettime());
	new uid = mysql_insert_id();
	
	mysql_query_format("INSERT INTO `fc_ranks` VALUES (NULL, '%d', '%s', '%d', '%d', '%d')", uid, "Lider", PANEL_PANEL, 0, 0);
	new rank = mysql_insert_id();
	
	GroupData[uid][UID] = uid;
	format(GroupData[uid][Desc], sizeof(desc), "%s", desc);
	format(GroupData[uid][Tag], 12, "%s", tag);
	GroupData[uid][Kind] = kind;
	GroupData[uid][Cash] = 0;
	GroupData[uid][LimitVehicles] = 10;
	GroupData[uid][Flags] = 0;
	GroupData[uid][Chat][0] = 255;
	GroupData[uid][Chat][1] = 255;
	GroupData[uid][Chat][2] = 255;
	GroupData[uid][License] = gettime() + ((7 * 60) * 60);
	GroupData[uid][Leader] = 0;
	GroupData[uid][Admin] = admin;
	GroupData[uid][Points] = 0;
	GroupData[uid][Rank] = rank;
	
	SaveGroup(uid);
	
	return uid;
}

public DeleteGroup(uid)
{
	mysql_query_format("DELETE FROM `fc_groups` WHERE `uid` = '%d'", uid);
	mysql_query_format("DELETE FROM `fc_ranks` WHERE `group_uid` = '%d'", uid);
	
	GroupData[uid][UID] = 0;
	GroupData[uid][Desc] = 0;
	GroupData[uid][Tag] = 0;
	GroupData[uid][Kind] = 0;
	GroupData[uid][Cash] = 0;
	GroupData[uid][LimitVehicles] = 0;
	GroupData[uid][Flags] = 0;
	GroupData[uid][Chat][0] = 0;
	GroupData[uid][Chat][1] = 0;
	GroupData[uid][Chat][2] = 0;
	GroupData[uid][License] = 0;
	GroupData[uid][Leader] = 0;
	GroupData[uid][Admin] = 0;
	GroupData[uid][Points] = 0;
	GroupData[uid][Rank] = 0;
	
	return true;
}

public SaveGroup(uid)
{
	mysql_query_format("UPDATE `fc_groups` SET `desc` = '%s', `tag` = '%s', `kind` = '%d', `cash` = '%d', `limit_vehicles` = '%d', `flags` = '%d', `chat` = '%d,%d,%d', `license` = '%d', `leader` = '%d', admin = '%d', `points` = '%d', `head_rank` = '%d' WHERE `uid` = '%d'",
	GroupData[uid][Desc],
	GroupData[uid][Tag],
	GroupData[uid][Kind],
	GroupData[uid][Cash],
	GroupData[uid][LimitVehicles],
	GroupData[uid][Flags],
	GroupData[uid][Chat][0],
	GroupData[uid][Chat][1],
	GroupData[uid][Chat][2],
	GroupData[uid][License],
	GroupData[uid][Leader],
	GroupData[uid][Admin],
	GroupData[uid][Points],
	GroupData[uid][Rank],
	GroupData[uid][UID]);
}

public AddMember(playerid, uid, bool:leader, bool:head)
{
	mysql_check();
	
	if(leader) 
	{
		if(head)
		{
			mysql_query_format("INSERT INTO `fc_member_groups` VALUES ('%d', '%d', 0, 0, '%d')", CharacterCache[playerid][pUID], uid, GroupData[uid][Rank]);
			
			mysql_query_format("UPDATE `fc_groups` SET `leader` = '%d' WHERE `uid` = '%d'", CharacterCache[playerid][pUID], uid);
		}
		else
		{
			mysql_query_format("INSERT INTO `fc_member_groups` VALUES ('%d', '%d', 0, 0, '%d')", CharacterCache[playerid][pUID], uid, GroupData[uid][Rank]);
			
			mysql_query_format("UPDATE `fc_groups` SET `leader` = '%d' WHERE `uid` = '%d'", CharacterCache[playerid][pUID], uid);
		}
	}
	else mysql_query_format("INSERT INTO `fc_member_groups` VALUES ('%d', '%d', 0, 0, 0)", CharacterCache[playerid][pUID], uid);
	
	LoadPlayerGroup(playerid);
	return 1;
}

public CountMembersCrimeInDoor(groupid, doorid)
{
	new count = 0;
	
	ForeachEx(i, MAX_PLAYERS)
	{
		if(IsPlayerInGroup(i, groupid))
		{
			if(PlayerDoor[i] == doorid)
			{
				if((CharacterCache[i][pWeaponID] > 21 && CharacterCache[i][pWeaponID] < 33) || CharacterCache[i][pWeaponID] == 5)
				{
					count++;
				}
			}
		}
	}
	
	return count ++;
}

public ReloadGroupIcons()
{
	new string[128];
	
	if(CountMembersGroup(GROUP_GOV)) format(string, sizeof(string), "%s ~w~RZAD", string);
	if(CountMembersGroup(GROUP_PD)) format(string, sizeof(string), "%s ~b~~h~LSPD", string);
	if(CountMembersGroup(GROUP_BORDER)) format(string, sizeof(string), "%s ~g~BP", string);
	if(CountMembersGroup(GROUP_MC)) format(string, sizeof(string), "%s ~r~~h~LSMC", string);
	if(CountMembersGroup(GROUP_FD)) format(string, sizeof(string), "%s ~r~LSFD", string);
	if(CountMembersGroup(GROUP_RADIO)) format(string, sizeof(string), "%s ~p~~h~LSFM", string);
	
	TextDrawSetString(Icons, string);
}

public SendMessageToGroup(groupid, color, text[])
{
	ForeachEx(i, MAX_PLAYERS)
	{
	    if(IsPlayerInGroup(i, groupid))
	    {
	        SendClientMessage(i, color, text);
	    }
	}

	return 1;
}

