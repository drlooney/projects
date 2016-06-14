new ReportNum = 0;
new bool:Logged[MAX_PLAYERS];

new Checkpoint[MAX_PLAYERS];
new PlayerDoor[MAX_PLAYERS];

new DutyGroup[MAX_PLAYERS];
new DutyGroupSlot[MAX_PLAYERS];
new DutyGroupTime[MAX_PLAYERS];

new DeletePenalty = -1;

new PenaltyAll = 0;
new PenaltyBan = 0;
new Restart = 0;

new AdvertiseTime = 0;
new bool:UsingRadio = false;

new bool:PlayerEditGate[MAX_PLAYERS];

new bool:SendOffer[MAX_PLAYERS];
new PlayerEditObject[MAX_PLAYERS];
new PlayerAFK[MAX_PLAYERS];
new PlayerActions[MAX_PLAYERS];
new PhoneNumber[MAX_PLAYERS];
new EditBusStop[MAX_PLAYERS];

new PlayerItemIndex[MAX_PLAYERS];

new Tick[MAX_VEHICLES];
new Float:VehiclePos[MAX_VEHICLES][3];

new CardUse[MAX_PLAYERS];

new CallNow[MAX_PLAYERS];
new CallTo[MAX_PLAYERS];
new CallTime[MAX_PLAYERS];

new CharacterOnline[MAX_PLAYERS];

new PlayerBar:DrugsBar[MAX_PLAYERS];
new PlayerBar:FoodBar[MAX_PLAYERS];

new EditGroup[MAX_PLAYERS];

new PlayerText:Textdraw0[MAX_PLAYERS];
new PlayerText:Textdraw1[MAX_PLAYERS];
new PlayerText:Textdraw2[MAX_PLAYERS];
new PlayerText:Textdraw3[MAX_PLAYERS];
new PlayerText:Textdraw4[MAX_PLAYERS];
new PlayerText:Textdraw5[MAX_PLAYERS];
new PlayerText:Textdraw6[MAX_PLAYERS];
new PlayerText:Textdraw7[MAX_PLAYERS];
new PlayerText:Textdraw8[MAX_PLAYERS];
new PlayerText:Textdraw9[MAX_PLAYERS];
new PlayerText:Textdraw10[MAX_PLAYERS];
new PlayerText:Textdraw11[MAX_PLAYERS];
new PlayerText:Textdraw12[MAX_PLAYERS];
new PlayerText:Textdraw13[MAX_PLAYERS];
new PlayerText:Textdraw14[MAX_PLAYERS];
new PlayerText:Textdraw15[MAX_PLAYERS];
new PlayerText:Textdraw16[MAX_PLAYERS];
new PlayerText:Textdraw17[MAX_PLAYERS];
new PlayerText:Textdraw18[MAX_PLAYERS];
new PlayerText:Textdraw19[MAX_PLAYERS];
new PlayerText:Textdraw20[MAX_PLAYERS];
new PlayerText:Textdraw21[MAX_PLAYERS];
new PlayerText:Textdraw22[MAX_PLAYERS];
new PlayerText:Textdraw23[MAX_PLAYERS];
new PlayerText:Textdraw24[MAX_PLAYERS];
new PlayerText:Textdraw25[MAX_PLAYERS];
new PlayerText:Textdraw26[MAX_PLAYERS];
new PlayerText:Textdraw27[MAX_PLAYERS];
new PlayerText:Textdraw28[MAX_PLAYERS];
new PlayerText:Textdraw29[MAX_PLAYERS];
new PlayerText:Textdraw30[MAX_PLAYERS];

new PlayerText:Offer[MAX_PLAYERS];
new PlayerText:AcceptOffer[MAX_PLAYERS];
new PlayerText:CrossOffer[MAX_PLAYERS];
new PlayerText:InfoOffer[MAX_PLAYERS];
new PlayerText:InfoBoxOffer[MAX_PLAYERS];
new PlayerText:ModelOffer[MAX_PLAYERS];

new PlayerText:TextPenaltyType[MAX_PLAYERS];
new PlayerText:TextPenalty[MAX_PLAYERS];

new PlayerText:IRPName[MAX_PLAYERS];

new PlayerText:TextDrawAudioError[MAX_PLAYERS];

new PlayerText:Panorama1[MAX_PLAYERS];
new PlayerText:Panorama2[MAX_PLAYERS];

new PlayerText:InfoDoor[MAX_PLAYERS];
new PlayerText:BlackScreen[MAX_PLAYERS];

new PlayerText:RadioFM[MAX_PLAYERS];
new PlayerText:AdminDuty[MAX_PLAYERS];

new PlayerText:BoxDoor[MAX_PLAYERS];
new PlayerText:BoxDoorIcon[MAX_PLAYERS];

new PlayerText:IconDoorRed[MAX_PLAYERS];
new PlayerText:IconDoorPurple[MAX_PLAYERS];
new PlayerText:IconDoorGreen[MAX_PLAYERS];

new PlayerText:TextDrawMainInfo[MAX_PLAYERS];

new PlayerText:AdminInfo[MAX_PLAYERS];

new Text:Icons;

new Text3D:NameTags[MAX_PLAYERS];

new Text3D:StatusTag[MAX_PLAYERS];
new Text3D:VehicleTag[MAX_VEHICLES];

new WeaponModel[47] = {0, 331, 333, 334, 335, 336, 337, 338, 339, 341, 321, 322, 323, 324, 325, 326, 342, 343, 344, 0, 0, 0, 346, 347, 348, 349, 350, 351, 352, 353, 355, 356, 372, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 371};
new PickupIDs[24] = {1318, 1318, 1240, 1242, 1239, 1272, 1273, 1212, 1241, 1247, 1248, 1252, 1253, 1254, 1274, 1275, 1277, 1313, 1314, 1276, 1310, 1279, 19300, 0};



#define chrtoupper(%1) \
        (((%1) > 0x60 && (%1) <= 0x7A) ? ((%1) ^ 0x20) : (%1))

#define chrtolower(%1) \
        (((%1) > 0x40 && (%1) <= 0x5A) ? ((%1) | 0x20) : (%1))
        
#define Speed(%0,%1,%2,%3,%4) \
		floatround(floatsqroot((%4)?(%0*%0+%1*%1+%2*%2):(%0*%0+%1*%1))*%3*1.6)

#define SendClientMessageFormat(%0,%1,%2,%3) \
do \
{ \
    if(strlen(%2) > 0) \
    { \
        new stringtest[256]; \
        format(stringtest, sizeof(stringtest), %2, %3); \
        SendClientMessage(%0, %1, stringtest); \
    } \
} \
while(FALSE)

#define SendClientMessageToAllFormat(%0,%1,%2) \
do \
{ \
    if(strlen(%1) > 0) \
    { \
        new strings[128]; \
        format(strings, sizeof(strings), %1, %2); \
        SendClientMessageToAll(%0, strings); \
        printf(strings); \
    } \
} \
while(FALSE)

#define InfoAdminFormat(%0,%1,%2) \
do \
{ \
     new stringtest[256]; \
     format(stringtest, sizeof(stringtest), %1, %2); \
     InfoAdmin(%0, stringtest); \
} \
while(FALSE)

#define SendAdminMessageFormat(%0,%1,%2) \
do \
{ \
    if(strlen(%1) > 0) \
    { \
        new stringtest[256]; \
        format(stringtest, sizeof(stringtest), %1, %2); \
        SendAdminMessage(%0, stringtest); \
    } \
} \
while(FALSE)