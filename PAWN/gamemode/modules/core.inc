enum sItemObject
{
	objItemUID,
	objID
}
new ItemObject[MAX_ITEMS][sItemObject];

new VehicleName[212][32] = {
"Landstalker","Bravura","Buffalo","Linerunner","Pereniel","Sentinel","Dumper","Firetruck","Trashmaster","Stretch","Manana",
"Infernus","Voodoo","Pony","Mule","Cheetah","Ambulance","Leviathan","Moonbeam","Esperanto","Taxi","Washington","Bobcat",
"Mr Whoopee","BF Injection","Hunter","Premier","Enforcer","Securicar","Banshee","Predator","Bus","Rhino","Barracks",
"Hotknife","Trailer","Previon","Coach","Cabbie","Stallion","Rumpo","RC Bandit","Romero","Packer","Monster","Admiral",
"Squalo","Seasparrow","Pizzaboy","Tram","Trailer","Turismo","Speeder","Reefer","Tropic","Flatbed","Yankee","Caddy",
"Solair","Berkley's RC Van","Skimmer","PCJ-600","Faggio","Freeway","RC Baron","RC Raider","Glendale","Oceanic",
"Sanchez","Sparrow","Patriot","Quad","Coastguard","Dinghy","Hermes","Sabre","Rustler","ZR-350","Walton","Regina",
"Comet","BMX","Burrito","Camper","Marquis","Baggage","Dozer","Maverick","News Chopper","Rancher","FBI Rancher",
"Virgo","Greenwood","Jetmax","Hotring","Sandking","Blista Compact","Police Maverick","Boxville","Benson","Mesa",
"RC Goblin","Hotring Racer","Hotring Racer","Bloodring Banger","Rancher","Super GT","Elegant","Journey","Bike",
"Mountain Bike","Beagle","Cropdust","Stunt","Tanker","RoadTrain","Nebula","Majestic","Buccaneer","Shamal","Hydra",
"FCR-900","NRG-500","HPV1000","Cement Truck","Tow Truck","Fortune","Cadrona","FBI Truck","Willard","Forklift","Tractor",
"Combine","Feltzer","Remington","Slamvan","Blade","Freight","Streak","Vortex","Vincent","Bullet","Clover","Sadler",
"Firetruck","Hustler","Intruder","Primo","Cargobob","Tampa","Sunrise","Merit","Utility","Nevada","Yosemite","Windsor",
"Monster","Monster","Uranus","Jester","Sultan","Stratum","Elegy","Raindance","RC Tiger","Flash","Tahoma","Savanna",
"Bandito","Freight","Trailer","Kart","Mower","Duneride","Sweeper","Broadway","Tornado","AT-400","DFT-30","Huntley",
"Stafford","BF-400","Newsvan","Tug","Trailer","Emperor","Wayfarer","Euros","Hotdog","Club","Trailer","Trailer",
"Andromeda","Dodo","RC Cam","Launch","Police Car","Police Car","Police Car","Police Ranger","Picador","S.W.A.T. Van",
"Alpha","Phoenix","Glendale","Sadler","Luggage Trailer","Luggage Trailer","Stair Trailer","Boxville","Farm Plow","Utility Trailer"};

enum characterInfo
{
	loginGID,
	pGID, 
	pUID,
	pNick[32],
	pAge,
	pSex,
	pCash,
	pHours,
	pMinutes,
	pSkin,
	pBW,
	pAJ,
	Float:pHealth,
	pJob,
	pBankCash,
	pBankNumber,
	pBlock,
	pCredit,
	pInsurance,
	pDocument,
	pPhone,
	pLastSkin,
	pFood,

	pParalizeTime,
	
	pPermit,

	pStr,
	pGun,
	pVehicle,
	pFish,
	
	Float:pPos[3],
	pVW,
	pInt,

	bool:pDutyJob,
	pDutyJobTime,

	pVehicleThief,
	pVehicleThiefID,

	pDrugs,
	pDrugsTime,

	pReport,
	pReportPD,

	bool:pShowBlood,
	bool:pMask,

	pBusStatus,
	pBusTarget,
	pBusTime,
	Float:pBusPos[3],

	bool:pDetect,
	pDetectNumber,
	pDetectPlayerID,
	pDetectProgress,

	pReanimation,
	pReanimationID,

	pRepair,
	pRepairVehicle,
	
	pRobbery,
	pRobberyID,

	pKey[32],
 	pPrivTo,
	pPrivMess[128],
	
	pIP[16],
	pPermission,

	pVehicleWarring,
	
	pTaxiVeh,
	pTaxiPay,
	pTaxiPrice,
	pTaxiPassenger,
	pTaxiGroup,

	pAdmin,
	pAdminPermission,
	
	pPremium,

	pUseDesc,

	Text3D:Nick,
	pNickColor,
	
	Float:pSpecPos[3],
	pSpecInt,
	pSpecVW,
	bool:pSpec,

	pCuffed,
	pCarSpawned,

	pPenaltyPoints,
	
	pMove3DText,
	pMove3DTextPhase,

	pGroupFlag,
	pLastW,
	
	pOption,
	pTog,
	pEditor,

	bool:pPackage,
	pPackageID,
	pPackageDoor,
	pPackageTime,

	pTakeDamage,

	pSellDrug,

	pJailTime,
	pJailID,

	pDeathReason,
	pDeathWeapon,

	pBlockPlayer,
	pBlockReason[128],

	bool:pShowInfoOffer,

	pWater,
	pBait,

	pStatus,
	pAFK,

	pAFKTime,

	pArea,

	bool:pWorek,
	bool:pKnebel,
	
	pShowGroups,
	pShowDoors,

	pSensor,
	
	Float:pAreaPos1,
	Float:pAreaPos2,

	Text3D:pDescTag,
	
	pGlobalNick[32],
	pGlobalScore,
	
	bool:pSelectCharacter,
	pSelectCharacterID,
	pMaxCharacters,
	
	pShowInfoText,
	
	bool:pAdminDuty,

	pFished,
	bool:pFishTaking,
	pFishingRodUID,
	
	pWeaponUID,
	pWeaponID,
	pWeaponAmmo,
	bool:pGetWeapon
}
new CharacterCache[MAX_PLAYERS][characterInfo];

enum areaInfo {
	aUID,
	aOwner,
	aOwnerType,
	Float:aPos_x[2],
	Float:aPos_y[2],
	aLimitObject,

	aGangID
};
new AreaInfo[MAX_AREAS][areaInfo];

enum vehicleInfoENUM
{
	vUID,
	vModel,

	Float:vHP,

	Float:vPosX,
	Float:vPosY,
	Float:vPosZ,
	Float:vPosA,

	vInteriorID,
	vWorldID,

	vOwner,
	vOwnerType,

	Float:vFuel,
	vRegister[12],

	vColor1,
	vColor2,

	vVisual[4],

	bool:vLocked,
	bool:vEngineTogged,

	vSpawned,
	Float:vDistance,

	vAccess,
	vBlock,
	vSlot,

	bool:vUseGPS,
	vPolice,

	vSensor,

	vComponent[14],
	bool: vCompLoaded,
	vPaintJob,

	vGameID
}
new VehicleInfo[MAX_VEHICLES][vehicleInfoENUM];

enum groupInfo
{
	UID,
	Desc[32],
	Tag[12],
	Kind,
	Cash,
	LimitVehicles,
	Flags,
	Chat[3],
	License,
	Leader,
	Admin,
	Points,
	Rank
}
new GroupData[MAX_GROUPS][groupInfo];

enum subgroup 
{
	sUID,
	sGroup,
	sDesc[32],
	sTag[12],
	sChat[3]
}
new SubData[MAX_SUBGROUPS][subgroup];

enum memberInfo
{
	GroupID,
	GroupCash,
	GroupRank[32],
	GroupPerm,
	GroupSkin,
	GroupTime,
	GroupSubGroup
}
new MemberGroup[MAX_PLAYERS][4][memberInfo];

enum memberInfoGame
{
	homeDoorID,
	homePerm,
	homeRank[32],
	homePrice,
	homeCharID
}
new MemberHome[MAX_PLAYERS][MAX_DOORS][memberInfoGame];

enum doorInfo
{
	dUID,

	dOwnerType,
	dOwner,

	Float:dEnterX,
	Float:dEnterY,
	Float:dEnterZ,
	Float:dEnterAng,

	dEnterInt,
	dEnterVw,
	dEnterCash,

	Float:dExitX,
	Float:dExitY,
	Float:dExitZ,
	Float:dExitAng,

	dExitInt,
	dExitVw,

	dLock,

	dPickupID,
	dName[31],

	dGarage,
	dPickup,

	dEnVw,
	dExVw,

	dDoor,
	Pickup,

	dValue,
	dAudioURL[128],

	dObject,
	dBlock,
	
	dFireUse,
	dFireValue,
	dFireObject[6],

	bool:dAlarm
}
new DoorInfo[MAX_DOORS][doorInfo];

enum sItemData
{
	iUID,
	iName[32],
	
	iValue1,
	iValue2,
	iType,
	
	iPlace,
	iOwner,
	
	iValues,

	iUsed,
	iFlags
}
new ItemInfo[MAX_ITEMS][sItemData];

enum oinfo
{
	oUID,
	oModel,

	Float:oX,
	Float:oY,
	Float:oZ,

	Float:oRX,
	Float:oRY,
	Float:oRZ,

	oInt,
	oVW,

	oObject,

	oOwnerType,
	oOwner,
	oDoor,

	Float:oGateX,
	Float:oGateY,
	Float:oGateZ,

	Float:oGateRX,
	Float:oGateRY,
	Float:oGateRZ,

	oGate,
	bool:oGateOpen,

	oMMAT
}
new ObjectInfo[MAX_OBJECTS][oinfo];

enum ofertaInfo
{
	oCustomer,
	oPrice,
	oType,
	oValue1,
	oSeller
}
new OfertaInfo[MAX_PLAYERS][ofertaInfo];

enum settingInfos 
{
	sStatus,
	sPassword,
	sDocID,
	sDocDriver,
	sDocFish,
	sDocRegister,
	sDocLicense,
	sDocPolice,
	sDocMedical,
	sDocPassport,
	sBenefit,
	sFuel,
	sFishSweet,
	sFishSalt,
	sProcent,
	Float:sMagazineX,
	Float:sMagazineY,
	Float:sMagazineZ
}
new SettingInfo[settingInfos];

enum busInfo
{
	bUID,
	bName[32],
	Text3D:bLabel,
	bObject,
	Float:bPos[3],
	Float:bRot[3]
}
new BusStop[MAX_BUSSTOP][busInfo];

enum corpseInfoGame
{
	cUID,
	cChar,
	cReason,
	cStatus,
	cDate,
	cFingers,
	Float:cPos[3],
	cVw,
	cWeaponUID,

	Text3D:cLabel,
	cObject
}
new CorpseInfo[MAX_CORPS][corpseInfoGame];

enum reportInfoGame
{
	reportID,
	reportChar,
	reportGroup,
	reportText[512],
	reportStatus,
	reportCharName[32],
	Float:reportPos[3]
}
new ReportInfo[MAX_REPORTS][reportInfoGame];

enum gangInfoGame
{
	gangID,
	gangSkin,
	gangName[32],

	Float:gangPosX,
	Float:gangPosY,
	Float:gangPosZ,

	Float:gangMarkerX,
	Float:gangMarkerY,
	Float:gangMarkerZ,

	gangStatus,
	gangToPlayer,

	gangMarker,
	gangNPC
}
new GangInfo[MAX_GANGS][gangInfoGame];

enum descriptionInfoGame
{
	descID,
	descTitle[32],
	descChar,
	descText[128]
}
new DescInfo[MAX_DESC][descriptionInfoGame];


enum labelInfoGame
{
	labelID,

	labelText[256],
	Float:labelRange,

	Float:labelPos[3],

	labelOwner,
	labelOwnerType,

	labelVw,
	labelInt,

	Text3D:label3D
}
new LabelInfo[MAX_LABELS][labelInfoGame];

enum attahInfo
{
	aUID,
	aModel,
	aitemID,
	Float:afOffsetX,
	Float:afOffsetY,
	Float:afOffsetZ,
	Float:afRotX,
	Float:afRotY,
	Float:afRotZ,
	Float:afScaleX,
	Float:afScaleY,
	Float:afScaleZ
}
new AttachInfo[MAX_ATTACH][attahInfo];

enum sensorInfoGame
{
	sensorID,
	sensorName[32],
	Float:sensorPos[3],

	Text3D:sensorText
}
new SensorInfo[MAX_SENSORS][sensorInfoGame];

enum plantInfoGame
{
	plantUID,
	Float:plantX,
	Float:plantY,
	Float:plantZ,
	plantVw,
	plantInt,
	plantDoor,
	plantChar,
	plantType,
	plantProgress,

	Text3D:plantText,
	plantObject
}
new PlantInfo[MAX_PLANTS][plantInfoGame];

enum burgerInfoGame
{
	burgerID,
	Float:burgerPos[3],

	burgerMarker
}
new BurgerInfo[MAX_BURGERS][burgerInfoGame];

enum raceInfoGame
{
	raceID,
	raceName[32],
	raceCreated
}
new RaceInfo[MAX_RACES][raceInfoGame];

enum groupInfoBox
{
    gName[32],
    gColor,
    bool:gAccess,
    gPrice
}
new GroupInfo[COUNT_GROUP + 1][groupInfoBox] =
{
    {"Nieokreœlona", 					0xFFFFFFFF,		false,		0},
    {"Police Department", 				0xFFFFFFFF, 	false,		0},
    {"Federal Bureau of Investigation", 0xFFFFFFFF, 	false,		0},
    {"Secret Service", 					0xFFFFFFFF, 	false,		0},
    {"Government", 						0xFFFFFFFF, 	false,		0},
    {"Medical Center", 					0xFFFFFFFF, 	false,		0},
    {"Fire Department", 				0xFFFFFFFF, 	false,		0},
    {"San News", 						0xFFFFFFFF, 	false,		0},
    {"Border Patrol",					0xFFFFFFFF, 	false,		0},
    {"Mafia", 							0xFFFFFFFF, 	false,		0},
    {"Gang uliczny", 					0xFFFFFFFF, 	false,		0},
    {"Œciganci", 						0xFFFFFFFF, 	false,		0},
    {"Syndykat", 						0xFFFFFFFF, 	false,		0},
    {"Sklep 24/7", 						0xFFFFFFFF, 	true,		0},
    {"Warsztat", 						0xFFFFFFFF, 	true,		0},
    {"Restauracja",						0xFFFFFFFF, 	true,		0},
    {"Salon samochodowy", 				0xFFFFFFFF, 	true,		0},
    {"Ochrona", 						0xFFFFFFFF, 	true,		0},
    {"Bank", 							0xFFFFFFFF, 	true,		0},
    {"Firma taksówkarska",				0xFFFFFFFF, 	true,		0}
};

enum pFishSweet
{
	fName[32],

	fValue1,
	fValue2
}
new FishSweet[5][pFishSweet] =
{
	{"Karas", 		1, 0},
	{"Okon", 		2, 0},
	{"Lin", 		3, 0},
	{"Szczupak", 	4, 0},
	{"Sum", 		5, 0}
};

enum pFishSalt
{
	fName[32],

	fValue1,
	fValue2
}
new FishSalt[5][pFishSalt] =
{
	{"Losos", 		6, 0},
	{"Dorsz", 		7, 0},
	{"Tunczyk", 	8, 0},
	{"Sledz", 	    9, 0},
	{"Makrela",		10, 0}
};

enum pickupInfo
{
    Name[64]
}
new PickupInfo[MAX_DOORS][pickupInfo];

enum sItemTypeInfo
{
    iTypeName[32],
    Float:iTypeWeight,

    iTypeObjModel,

    Float:iTypeObjRotX,
    Float:iTypeObjRotY
}
new ItemTypeInfo[TYPE_COUNT + 1][sItemTypeInfo] =
{
    {"Nieokreœlony",    0.0,    328,    90.0,   95.0},
    {"Broñ",            0.0,    328,    90.0,   95.0},
    {"Paralizator",     0.0,    328,    90.0,   95.0},
    {"Lakier",          0.0,    328,    90.0,   95.0},
    {"Syrena",          0.0,    18646,  90.0,   95.0},
    {"Metamfetamina",   0.0,    328,    90.0,   95.0},
    {"Kokaina",         0.0,    328,    90.0,   95.0},
    {"Marihuana",      	0.0,    328,    90.0,   95.0},
    {"Podpa³ka",        0.0,    328,    90.0,   95.0},
    {"Krótkofalówka",	0.0,	2966,	90.0,	95.0},
    {"Megafon", 		0.0,	328,	90.0,	95.0},
    {"Wytrych", 		0.0, 	328, 	90.0, 	95.0},
    {"Wêdka",  			0.0,	328,	90.0,	95.0},
    {"Przynêta",  		0.0,	328,	90.0,	95.0},
    {"Ryba",  			0.0,	328,	90.0,	95.0},
    {"Telefon", 		0.0,	18871, 	90.0,	95.0},
    {"Karta kredytowa",	0.0,	328,	90.0,	95.0},
    {"Maska",			0.0,	328,	90.0,	95.0},
    {"Przyczepialny",	0.0,	328,	90.0,	95.0},
    {"Tuning",			0.0,	328,	90.0,	95.0},
    {"Nasiona", 		0.0,	328,	90.0,	95.0},
	{"Jedzenie",        0.0,    328,    90.0,   95.0},
	{"Alkohol",         0.0,    328,    90.0,   95.0},
	{"Papierosy",		0.0,	328, 	90.0,	95.0},
	{"Zegarek",			0.0,	328, 	90.0, 	95.0},
	{"Koœæ do gry",		0.0,	328,	90.0,	95.0},
	{"Paczka pieniêdzy",0.0,	328,	90.0,	95.0},
	{"Tablice pojazdu", 0.0,	328,	90.0,	95.0}
};

enum Coords
{
    SPU,
    VehicleID,
    Float:sX,
    Float:sY,
    Float:sZ,
}
new SyrenaPos[39][Coords] = {
    {1, 572, 0.398071289, 0.75390625, 0.43879509},
    {2, 572, -0.35644531250, 0.0388183593, 0.863788605},
    {3, 415, 0.409729004, 0.526367188, 0.206963539},
    {4, 415, -0.290039062, -0.284179688, 0.631957054},
    {5, 421, 0.421691895, 0.804931641, 0.256482124},
    {6, 421, -0.323303223, 0.0207519532, 0.731482506},
    {7, 426, 0.575378418, 0.786132812, 0.361483574},
    {8, 426, -0.455505371, -0.143066406, 0.861475945},
    {9, 579, 0.454345703, 0.575683594, 0.645122528},
    {10, 579, -0.442626953, -0.269042969, 1.27014542},
    {11, 402, 0.53515625, 0.562988281, 0.278743744},
    {12, 402, -0.412841797, -0.474365234, 0.778804779},
    {13, 596, 0.53515625, 0.771728516, 0.373809814},
    {14, 596, -0.0048828125, -0.860107422, 0.848770142},
    {15, 597, 0.53515625, 0.771728516, 0.373809814},
    {16, 597, -0.0048828125, -0.860107422, 0.848770142},
    {17, 598, 0.406738281, 0.696777344, 0.398208618},
    {18, 598, -0.0048828125, -0.860107422, 0.848770142},
    {19, 544, 0.522338867, 2.5925293, 1.46867275},
    {20, 528, 0.563842773, 0.754882812, 0.487258911},
    {21, 525, -0.0089111328, 0.273193359, 1.4037838},
    {22, 409, 0.420776367, 1.80236816, 0.368680954},
    {23, 409, -0.439941406, 0.824829102, 0.842817307},
    {24, 461, 0.00000000, -0.932861328, 0.494509697},
    {25, 521, 0.00000000, -0.928955078, 0.558652878},
    {26, 586, 0.00000000, -1.20178223, 0.671886444},
    {27, 506, 0.541137695, 0.282714844, 0.272130013},
    {28, 482, 0.493530273, 1.39465332, 0.442443848},
    {29, 482, -0.392211914, 0.565551758, 0.941601753},
    {30, 424, -0.624511719, 0.139648438, 0.918135643},
    {31, 470, -0.617797851, 0.056640625, 1.10928631},
    {32, 433, -0.577392578, 1.23217773, 1.70311642},
    {33, 432, -1.21105957, -3.84765625, 1.17495251},
    {34, 560, 0.398071289, 0.75390625, 0.43879509},
    {35, 482, 0.4, 1.3, 0.5},
    {36, 490, 0.4, 1.2, 0.6},
    {37, 561, 0.4, 1.0, 0.3},
    {38, 405, 0.4, 0.6, 0.3},
    {34, 445, 0.398071289, 0.75390625, 0.43879509}
};

enum INTERIOR_INFO
{
    INTERIOR_ID,
    Float:INTERIOR_X,
    Float:INTERIOR_Y,
    Float:INTERIOR_Z,
    Float:INTERIOR_A,
    INTERIOR_NAME[32]
}
new Interior[][INTERIOR_INFO] = {
        { 11, 2003.1178, 1015.1948, 33.008, 351.5789, "Four Dragons' Managerial" },
        { 5, 770.8033, -0.7033, 1000.7267, 22.8599, "Ganton Gym" },
        { 3, 974.0177, -9.5937, 1001.1484, 22.6045, "Brothel" },
        { 3, 961.9308, -51.9071, 1001.1172, 95.5381, "Brothel2" },
        { 3, 830.6016, 5.9404, 1004.1797, 125.8149, "Inside Track Betting" },
        { 3, 1037.8276, 0.397, 1001.2845, 353.9335, "Blastin' Fools Records" },
        { 3, 1212.1489, -28.5388, 1000.9531, 170.5692, "The Big Spread Ranch" },
        { 18, 1290.4106, 1.9512, 1001.0201, 179.9419, "Warehouse 1" },
        { 1, 1412.1472, -2.2836, 1000.9241, 114.661, "Warehouse 2" },
        { 3, 1527.0468, -12.0236, 1002.0971, 350.0013, "B Dup's Apartment" },
        { 2, 1523.5098, -47.8211, 1002.2699, 262.7038, "B Dup's Crack Palace" },
        { 3, 612.2191, -123.9028, 997.9922, 266.5704, "Wheel Arch Angels" },
        { 3, 512.9291, -11.6929, 1001.5653, 198.7669, "OG Loc's House" },
        { 3, 418.4666, -80.4595, 1001.8047, 343.2358, "Barber Shop" },
        { 3, 386.5259, 173.6381, 1008.3828, 63.7399, "Planning Department" },
        { 3, 288.4723, 170.0647, 1007.1794, 22.0477, "Las Venturas Police Department" },
        { 3, 206.4627, -137.7076, 1003.0938, 10.9347, "Pro-Laps" },
        { 3, -100.2674, -22.9376, 1000.7188, 17.285, "Sex Shop" },
        { 3, -201.2236, -43.2465, 1002.2734, 45.8613, "Las Venturas Tattoo parlor" },
        { 17, -202.9381, -6.7006, 1002.2734, 204.2693, "Lost San Fierro Tattoo parlor" },
        { 17, -25.7220, -187.8216, 1003.5469, 5.0760, "24/7 (version 1)" },
        { 5, 454.9853, -107.2548, 999.4376, 309.0195, "Diner 1" },
        { 5, 372.5565, -131.3607, 1001.4922, 354.2285, "Pizza Stack" },
        { 17, 378.026, -190.5155, 1000.6328, 141.0245, "Rusty Brown's Donuts" },
        { 7, 315.244, -140.8858, 999.6016, 7.4226, "Ammu-nation" },
        { 5, 225.0306, -9.1838, 1002.218, 85.5322, "Victim" },
        { 2, 611.3536, -77.5574, 997.9995, 320.9263, "Loco Low Co" },
        { 10, 246.0688, 108.9703, 1003.2188, 0.2922, "San Fierro Police Department" },
        { 10, 6.0856, -28.8966, 1003.5494, 5.0365, "24/7 (version 2 - large)" },
        { 7, 773.7318, -74.6957, 1000.6542, 5.2304, "Below The Belt Gymr" },
        { 1, 621.4528, -23.7289, 1000.9219, 15.6789, "Transfenders" },
        { 1, 445.6003, -6.9823, 1000.7344, 172.2105, "World of Coq" },
        { 1, 285.8361, -39.0166, 1001.5156, 0.7529, "Ammu-nation (version 2)" },
        { 1, 204.1174, -46.8047, 1001.8047, 357.5777, "SubUrban" },
        { 1, 245.2307, 304.7632, 999.1484, 273.4364, "Denise's Bedroom" },
        { 3, 290.623, 309.0622, 999.1484, 89.9164, "Helena's Barn" },
        { 5, 322.5014, 303.6906, 999.1484, 8.1747, "Barbara's Love nest" },
        { 1, -2041.2334, 178.3969, 28.8465, 156.2153, "San Fierro Garage" },
        { 1, -1402.6613, 106.3897, 1032.2734, 105.1356, "Oval Stadium" },
        { 7, -1403.0116, -250.4526, 1043.5341, 355.8576, "8-Track Stadium" },
        { 2, 1204.6689, -13.5429, 1000.9219, 350.0204, "The Pig Pen (strip club 2)" },
        { 10, 2016.1156, 1017.1541, 996.875, 88.0055, "Four Dragons" },
        { 1, -741.8495, 493.0036, 1371.9766, 71.7782, "Liberty City" },
        { 2, 2447.8704, -1704.4509, 1013.5078, 314.5253, "Ryder's house" },
        { 1, 2527.0176, -1679.2076, 1015.4986, 260.9709, "Sweet's House" },
        { 10, -1129.8909, 1057.5424, 1346.4141, 274.5268, "RC Battlefield" },
        { 3, 2496.0549, -1695.1749, 1014.7422, 179.2174, "The Johnson House" },
        { 10, 366.0248, -73.3478, 1001.5078, 292.0084, "Burger shot" },
        { 1, 2233.9363, 1711.8038, 1011.6312, 184.3891, "Caligula's Casino" },
        { 2, 269.6405, 305.9512, 999.1484, 215.6625, "Katie's Lovenest" },
        { 2, 414.2987, -18.8044, 1001.8047, 41.4265, "Barber Shop 2 (Reece's)" },
        { 2, 1.1853, -3.2387, 999.4284, 87.5718, "Angel \"Pine Trailer\"" },
        { 18, -30.9875, -89.6806, 1003.5469, 359.8401, "24/7 (version 3)" },
        { 18, 161.4048, -94.2416, 1001.8047, 0.7938, "Zip" },
        { 3, -2638.8232, 1407.3395, 906.4609, 94.6794, "The Pleasure Domes" },
        { 5, 1267.8407, -776.9587, 1091.9063, 231.3418, "Madd Dogg's Mansion" },
        { 2, 2536.5322, -1294.8425, 1044.125, 254.9548, "Big Smoke's Crack Palace" },
        { 5, 2350.1597, -1181.0658, 1027.9766, 99.1864, "Burning Desire Building" },
        { 1, -2158.6731, 642.09, 1052.375, 86.5402, "Wu-Zi Mu's" },
        { 10, 419.8936, 2537.1155, 10.0, 67.6537, "Abandoned AC tower" },
        { 14, 256.9047, -41.6537, 1002.0234, 85.8774, "Wardrobe/Changing room" },
        { 14, 204.1658, -165.7678, 1000.5234, 181.7583, "Didier Sachs" },
        { 12, 1133.35, -7.8462, 1000.6797, 165.8482, "Casino (Redsands West)" },
        { 14, -1420.4277, 1616.9221, 1052.5313, 159.1255, "Kickstart Stadium" },
        { 17, 493.1443, -24.2607, 1000.6797, 356.9864, "Club" },
        { 18, 1727.2853, -1642.9451, 20.2254, 172.4193, "Atrium" },
        { 16, -202.842, -24.0325, 1002.2734, 252.8154, "Los Santos Tattoo Parlor" },
        { 5, 2233.6919, -1112.8107, 1050.8828, 8.6483, "Safe House group 1" },
        { 6, 1211.2484, 1049.0234, 359.941, 170.9341, "Safe House group 2" },
        { 9, 2319.1272, -1023.9562, 1050.2109, 167.3959, "Safe House group 3" },
        { 10, 2261.0977, -1137.8833, 1050.6328, 266.88, "Safe House group 4" },
        { 17, -944.2402, 1886.1536, 5.0051, 179.8548, "Sherman Dam" },
        { 16, -26.1856, -140.9164, 1003.5469, 2.9087, "24/7 (version 4)" },
        { 15, 2217.281, -1150.5349, 1025.7969, 273.7328, "Jefferson Motel" },
        { 1, 1.5491, 23.3183, 1199.5938, 359.9054, "Jet Interior" },
        { 1, 681.6216, -451.8933, -25.6172, 166.166, "The Welcome Pump" },
        { 3, 234.6087, 1187.8195, 1080.2578, 349.4844, "Burglary House X1" },
        { 2, 225.5707, 1240.0643, 1082.1406, 96.2852, "Burglary House X2" },
        { 1, 224.288, 1289.1907, 1082.1406, 359.868, "Burglary House X3" },
        { 5, 239.2819, 1114.1991, 1080.9922, 270.2654, "Burglary House X4" },
        { 15, 207.5219, -109.7448, 1005.1328, 358.62, "Binco" },
        { 15, 295.1391, 1473.3719, 1080.2578, 352.9526, "4 Burglary houses" },
        { 15, -1417.8927, 932.4482, 1041.5313, 0.7013, "Blood Bowl Stadium" },
        { 12, 446.3247, 509.9662, 1001.4195, 330.5671, "Budget Inn Motel Room" },
        { 0, 2306.3826, -15.2365, 26.7496, 274.49, "Palamino Bank" },
        { 0, 2331.8984, 6.7816, 26.5032, 100.2357, "Palamino Diner" },
        { 0, 663.0588, -573.6274, 16.3359, 264.9829, "Dillimore Gas Station" },
        { 18, -227.5703, 1401.5544, 27.7656, 269.2978, "Lil' Probe Inn" },
        { 0, -688.1496, 942.0826, 13.6328, 177.6574, "Torreno's Ranch" },
        { 0, -1916.1268, 714.8617, 46.5625, 152.2839, "Zombotech - lobby area" },
        { 0, 818.7714, -1102.8689, 25.794, 91.1439, "Crypt in LS cemetery (temple)" },
        { 0, 255.2083, -59.6753, 1.5703, 1.4645, "Blueberry Liquor Store" },
        { 2, 446.626, 1397.738, 1084.3047, 343.9647, "Pair of Burglary Houses" },
        { 5, 227.3922, 1114.6572, 1080.9985, 267.459, "Crack Den" },
        { 5, 227.7559, 1114.3844, 1080.9922, 266.2624, "Burglary House X11" },
        { 4, 261.1165, 1287.2197, 1080.2578, 178.9149, "Burglary House X12" },
        { 4, 291.7626, -80.1306, 1001.5156, 290.2195, "Ammu-nation (version 3)" },
        { 4, 449.0172, -88.9894, 999.5547, 89.6608, "Jay's Diner" },
        { 4, -27.844, -26.6737, 1003.5573, 184.3118, "24/7 (version 5)" },
        { 0, 2135.2004, -2276.2815, 20.6719, 318.59, "Warehouse 3" },
        { 4, 306.1966, 307.819, 1003.3047, 203.1354, "Michelle's Love Nest*" },
        { 10, 24.3769, 1341.1829, 1084.375, 8.3305, "Burglary House X14" },
        { 1, 963.0586, 2159.7563, 1011.0303, 175.313, "Sindacco Abatoir" },
        { 0, 2548.4807, 2823.7429, 10.8203, 270.6003, "K.A.C.C. Military Fuels Depot" },
        { 0, 215.1515, 1874.0579, 13.1406, 177.5538, "Area 69" },
        { 4, 221.6766, 1142.4962, 1082.6094, 184.9618, "Burglary House X13" },
        { 12, 2323.7063, -1147.6509, 1050.7101, 206.5352, "Unused Safe House" },
        { 6, 344.9984, 307.1824, 999.1557, 193.643, "Millie's Bedroom" },
        { 12, 411.9707, -51.9217, 1001.8984, 173.3449, "Barber Shop" },
        { 4, -1421.5618, -663.8262, 1059.5569, 170.9341, "Dirtbike Stadium" },
        { 6, 773.8887, -47.7698, 1000.5859, 10.7161, "Cobra Gym" },
        { 6, 246.6695, 65.8039, 1003.6406, 7.9562, "Los Santos Police Department" },
        { 14, -1864.9434, 55.7325, 1055.5276, 85.8541, "Los Santos Airport" },
        { 4, -262.1759, 1456.6158, 1084.3672, 82.459, "Burglary House X15" },
        { 5, 22.861, 1404.9165, 1084.4297, 349.6158, "Burglary House X16" },
        { 5, 140.3679, 1367.8837, 1083.8621, 349.2372, "Burglary House X17" },
        { 3, 1494.8589, 1306.48, 1093.2953, 196.065, "Bike School" },
        { 14, -1813.213, -58.012, 1058.9641, 335.3199, "Francis International Airport" },
        { 16, -1401.067, 1265.3706, 1039.8672, 178.6483, "Vice Stadium" },
        { 6, 234.2826, 1065.229, 1084.2101, 4.3864, "Burglary House X18" },
        { 6, -68.5145, 1353.8485, 1080.2109, 3.5742, "Burglary House X19" },
        { 6, -2240.1028, 136.973, 1035.4141, 269.0954, "Zero's RC Shop" },
        { 6, 297.144, -109.8702, 1001.5156, 20.2254, "Ammu-nation (version 4)" },
        { 6, 316.5025, -167.6272, 999.5938, 10.3031, "Ammu-nation (version 5)" },
        { 15, -285.2511, 1471.197, 1084.375, 85.6547, "Burglary House X20" },
        { 6, -26.8339, -55.5846, 1003.5469, 3.9528, "24/7 (version 6)" },
        { 6, 442.1295, -52.4782, 999.7167, 177.9394, "Secret Valley Diner" },
        { 2, 2182.2017, 1628.5848, 1043.8723, 224.8601, "Rosenberg's Office in Caligulas" },
        { 6, 748.4623, 1438.2378, 1102.9531, 0.6069, "Fanny Batter's Whore House" },
        { 8, 2807.3604, -1171.7048, 1025.5703, 193.7117, "Colonel Furhberger's" },
        { 9, 366.0002, -9.4338, 1001.8516, 160.528, "Cluckin' Bell" },
        { 1, 2216.1282, -1076.3052, 1050.4844, 86.428, "The Camel's Toe Safehouse" },
        { 1, 2268.5156, 1647.7682, 1084.2344, 99.7331, "Caligula's Roof" },
        { 2, 2236.6997, -1078.9478, 1049.0234, 2.5706, "Old Venturas Strip Casino" },
        { 3, -2031.1196, -115.8287, 1035.1719, 190.1877, "Driving School" },
        { 8, 2365.1089, -1133.0795, 1050.875, 177.3947, "Verdant Bluffs Safehouse" },
        { 0, 1168.512, 1360.1145, 10.9293, 196.5933, "Bike School" },
        { 9, 315.4544, 976.5972, 1960.8511, 359.6368, "Andromada" },
        { 10, 1893.0731, 1017.8958, 31.8828, 86.1044, "Four Dragons' Janitor's Office" },
        { 11, 501.9578, -70.5648, 998.7578, 171.5706, "Bar" },
        { 8, -42.5267, 1408.23, 1084.4297, 172.068, "Burglary House X21" },
        { 11, 2283.3118, 1139.307, 1050.8984, 19.7032, "Willowfield Safehouse" },
        { 9, 84.9244, 1324.2983, 1083.8594, 159.5582, "Burglary House X22" },
        { 9, 260.7421, 1238.2261, 1084.2578, 84.3084, "Burglary House X23" },
        { 0, -1658.1656, 1215.0002, 7.25, 103.9074, "Otto's Autos" },
        { 0, -1961.6281, 295.2378, 35.4688, 264.4891, "Wang Cars" }
};