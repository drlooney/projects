forward DeleteObject(uid);
forward SaveObject(uid);
forward AddObject(model, ownertype, owner, World, InteriorEx, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);

stock GetObjectIndex( objectid )
{
	new uid = 0;
	ForeachEx(i, MAX_OBJECTS)
	{
		if(ObjectInfo[i][oObject] == objectid)
		{
			uid = i;
		}
	}
	
	return uid;
}

stock GetObjectID(uid)
{
	new list = 0;

	ForeachEx(i, MAX_OBJECTS)
	{
		if(ObjectInfo[i][oUID] == uid)
		{
			list = i;
		}
	}

	return list;
}

public AddObject(model, ownertype, owner, World, InteriorEx, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new query[300];
	format(query, sizeof(query), "INSERT INTO `fc_objects` (`model`, `x`, `y`, `z`, `rx`, `ry`, `rz`, `vw`, `int`, `ownertype`, `owner`) VALUES ('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d')",
	model, x, y, z, rx, ry, rz, World, InteriorEx, ownertype, owner);

	mysql_check();
	mysql_query(query);

	new uid = mysql_insert_id();

	ObjectInfo[uid][oUID] = uid;
	ObjectInfo[uid][oModel] = model;

	ObjectInfo[uid][oX] = x;
	ObjectInfo[uid][oY] = y;
	ObjectInfo[uid][oZ] = z;

	ObjectInfo[uid][oRX] = rx;
	ObjectInfo[uid][oRY] = ry;
	ObjectInfo[uid][oRZ] = rz;

	ObjectInfo[uid][oInt] = InteriorEx;
	ObjectInfo[uid][oVW] = World;

	ObjectInfo[uid][oOwnerType] = ownertype;
	ObjectInfo[uid][oOwner] = owner;

	ObjectInfo[uid][oGateX] = 0.0;
	ObjectInfo[uid][oGateY] = 0.0;
	ObjectInfo[uid][oGateZ] = 0.0;

	ObjectInfo[uid][oGateRX] = 0.0;
	ObjectInfo[uid][oGateRY] = 0.0;
	ObjectInfo[uid][oGateRZ] = 0.0;

	ObjectInfo[uid][oGate] = 0;

	ObjectInfo[uid][oObject] = CreateDynamicObject(ObjectInfo[uid][oModel], ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ], ObjectInfo[uid][oVW], ObjectInfo[uid][oInt], -1, 500.0);

	return uid;
}

public SaveObject(uid)
{
	new query[564];
	format(query, sizeof(query), "UPDATE `fc_objects` SET `model` = '%d', `x` = '%f', `y` = '%f', `z` = '%f', `rx` = '%f', `ry` = '%f', `rz` = '%f', `int` = '%d', `vw` = '%d', `ownertype` = '%d', `owner` = '%d', `mmat` = '%d' WHERE `uid` = '%d'",
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
	ObjectInfo[uid][oMMAT],
	uid);
	mysql_check();
	mysql_query(query);
	mysql_free_result();
	return 1;
}

forward SaveObjectGate(uid);
public SaveObjectGate(uid)
{
	new query[564];
	format(query, sizeof(query), "UPDATE `fc_objects` SET `gate_x` = '%f', `gate_y` = '%f', `gate_z` = '%f', `gate_rx` = '%f', `gate_ry` = '%f', `gate_rz` = '%f', `gate` = '%d' WHERE `uid` = '%d'",
	ObjectInfo[uid][oGateX],
	ObjectInfo[uid][oGateY],
	ObjectInfo[uid][oGateZ],
	ObjectInfo[uid][oGateRX],
	ObjectInfo[uid][oGateRY],
	ObjectInfo[uid][oGateRZ],
	ObjectInfo[uid][oGate],
	uid);
	mysql_check();
	mysql_query(query);

	mysql_free_result();
	return 1;
}

public DeleteObject(uid)
{
	mysql_check();
	mysql_query_format("DELETE FROM `fc_objects` WHERE `uid` = '%d'", uid);

	mysql_query_format("DELETE FROM `fc_mmat_text` WHERE `object` = '%d'", uid);
    mysql_query_format("DELETE FROM `fc_mmat_texture` WHERE `object` = '%d'", uid);

	ObjectInfo[uid][oUID] = 0;
	ObjectInfo[uid][oModel] = 0;
	ObjectInfo[uid][oX] = 0;
	ObjectInfo[uid][oY] = 0;
	ObjectInfo[uid][oZ] = 0;
	ObjectInfo[uid][oRX] = 0;
	ObjectInfo[uid][oRY] = 0;
	ObjectInfo[uid][oRZ] = 0;
	ObjectInfo[uid][oInt] = 0;
	ObjectInfo[uid][oVW] = 0;
	ObjectInfo[uid][oOwnerType] = 0;
	ObjectInfo[uid][oOwner] = 0;

	ObjectInfo[uid][oGateX] = 0.0;
	ObjectInfo[uid][oGateY] = 0.0;
	ObjectInfo[uid][oGateZ] = 0.0;

	ObjectInfo[uid][oGateRX] = 0.0;
	ObjectInfo[uid][oGateRY] = 0.0;
	ObjectInfo[uid][oGateRZ] = 0.0;

	ObjectInfo[uid][oGate] = 0;
	
	DestroyDynamicObject(ObjectInfo[uid][oObject]);

	mysql_free_result();
	return 1;
}