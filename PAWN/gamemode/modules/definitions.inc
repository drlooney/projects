#define COLOR_WHITE			0xFFFFFFFF
#define COLOR_WHITE2		0xFFFFFF00
#define COLOR_BLACK         0x000000FF
#define COLOR_BLACK2        0x00000000
#define COLOR_BROWN 		0x8F4747FF
#define COLOR_KREM 			0xFF8080FF
#define COLOR_SAY 			0x2986CEFF
#define COLOR_GREY 			0xAFAFAFAA
#define COLOR_GREY2 		0xAFAFAF00
#define COLOR_SYSGREY 		0xC6BEBDFF
#define COLOR_GREEN 		0x33AA33AA
#define COLOR_RED 			0xAA3333AA
#define COLOR_LIGHTRED      0xFF6347AA
#define COLOR_YELLOW 		0xFFFF00AA
#define COLOR_LIGHTBLUE 	0x33CCFFFF
#define COLOR_ORANGE 		0xFF9900AA
#define COLOR_DARKRED 		0xAA993333
#define COLOR_RED 			0xAA3333AA
#define COLOR_YELLOW 		0xFFFF00AA
#define COLOR_PINK 			0xFF66FFAA
#define COLOR_BLUE 			0x0000BBAA
#define COLOR_ORANGE 		0xFF9900AA
#define COLOR_VIOLET 		0x8000FFFF
#define COLOR_BROWN 		0x8F4747FF
#define COLOR_DARKGREY 		0x808080FF
#define COLOR_BLACK 		0x000000FF
#define COLOR_DARKGREEN 	0x0D731FFF
#define COLOR_DARKBLUE 		0x2010E0FF
#define COLOR_DARKBROWN 	0x530000FF
#define COLOR_DARKVIOLET 	0x400040FF
#define COLOR_DARKYELLOW 	0x808000FF
#define COLOR_DARKPINK 		0x400040FF
#define COLOR_KREM 			0xFF8080FF
#define COLOR_LIGHTGREEN 	0x00FF00FF
#define COLOR_LIGHTPINK 	0xFF80FFFF
#define COLOR_PURPLE     	0xC2A2DAFF
#define COLOR_PURPLE2	    0xE0EA64FF
#define COLOR_ADMIN         0x408080FF
#define COLOR_DO       		0x9A9CCDFF

#define SZARY				0xC0C0C0CC
#define CZERWONY 			0x990000FF
#define DEFAULT				0xE1F0C299
#define FIOLETOWY			0xC2A2DAFF 
#define KOLOR_DO			0x9A9CCDFF
#define CZARNY 				0x000000FF
#define GM					0xD4C598FF
#define ZOLTY  				0xf6f42fFF
#define ZIELONY				0x008000BB
#define ZLOTY  				0xEBC79EFF
#define FIOLETOWA   		0xC2A2DAFF
#define BIALY   			0xFFFFFFFF
#define ADM					0xB2F24BBB

#define COLOR_SEND_PW   	0xFFC973FF
#define COLOR_GOT_PW  		0xFDAE33FF

#define COLOR_ADMIN_GA		0xCC2929FF
#define COLOR_ADMIN_ADMIN	0x25b000FF
#define COLOR_ADMIN_ASS		0x538668FF

#define COLOR_FADE1   		0xE6E6E6E6
#define COLOR_FADE2   		0xC8C8C8C8
#define COLOR_FADE3   		0xAAAAAAAA
#define COLOR_FADE4   		0x8C8C8C8C
#define COLOR_FADE5   		0x6E6E6E6E

#define COLOR_GRAD1   		0xB4B5B7FF
#define COLOR_GRAD2   		0xBFC0C2FF
#define COLOR_GRAD3   		0xCBCCCEFF
#define COLOR_GRAD4   		0xD8D8D8FF
#define COLOR_GRAD5   		0xE3E3E3FF
#define COLOR_GRAD6   		0xF0F0F0FF

#define WEAPON_TYPE_NONE    			0
#define WEAPON_TYPE_HEAVY   			1
#define WEAPON_TYPE_LIGHT   			2
#define WEAPON_TYPE_MELEE   			3

#define SAVE_PLAYER_BASIC				1
#define SAVE_PLAYER_SETTING				2
#define SAVE_PLAYER_POS					3
#define SAVE_PLAYER_GLOBAL				4

#define SAVE_VEH_POS    				1
#define SAVE_VEH_ACCESS  				2
#define SAVE_VEH_COUNT  				4
#define SAVE_VEH_THINGS 				8
#define SAVE_VEH_LOCK   				16

#define LIMIT_AREA						40
#define LIMIT_DOOR						200

#define BUS_NONE						0 // Brak
#define BUS_SEARCH						1 // Wyszukiwanie przystanku
#define BUS_TARGET						2 // Wybrany przystanek
#define BUS_GOTO						3 // Transport na przystanek

#define OWNER_NONE						0
#define OWNER_PLAYER					1
#define OWNER_GROUP						2
#define OWNER_AREA						3
#define OWNER_JAIL						4
#define OWNER_DOOR						5
#define OWNER_BANK						6
#define OWNER_VEHICLE					7
#define OWNER_SUBGROUP					8
#define OWNER_ADMIN						9
#define OWNER_HOUSE						10

#define GROUP_PD						1
#define GROUP_FBI 						2
#define GROUP_SS						3
#define GROUP_GOV						4
#define GROUP_MC						5
#define GROUP_FD						6
#define GROUP_RADIO						7
#define GROUP_BORDER					8
#define GROUP_MAFIA						9
#define GROUP_GANG						10
#define GROUP_DRIVERS					11
#define GROUP_SYNDYCATE					12
#define GROUP_SHOP						13
#define GROUP_WORKSHOP					14
#define GROUP_FOOD						15
#define GROUP_CARDEALER					16
#define GROUP_SECURITY					17
#define GROUP_BANK						18
#define GROUP_TAXI 						19

#define COUNT_GROUP						19

#define AREA_STATION					1

#define ATTACH_NONE         			0
#define ATTACH_GLASSES      			1
#define ATTACH_CAP          			2
#define ATTACH_CASE         			3
#define ATTACH_HELMET       			4
#define ATTACH_PHONE					5 
#define ATTACH_TIME						6

#define SLOT_CASE						0
#define SLOT_WEAPON						1
#define SLOT_HAT            			2
#define SLOT_GLASSES        			3
#define SLOT_PHONE          			4
#define SLOT_TIME						5 

#define BAIT_WORMS						1
#define BAIT_MUSH						2

#define DRUG_META						1 // Metamfetamina
#define DRUG_COCAINE					2 // Kokaina
#define DRUG_MAR						3 // Marihuana

//== DEFINICJA ==        		 		== NUMER ==         == NAZWA ==             == WARTOŒÆ 1 ==     == WARTOŒÆ 2 ==           
#define TYPE_WEAPON						1 // 				Broñ					id broni			ammo
#define TYPE_INHIBITOR					2 // 				Paralizator				model broni			amunicja
#define TYPE_PAINT						3 // 				Spray					41					iloœæ ammo
#define TYPE_POLICE						4 //				Syrena					0					0
#define TYPE_META						5 // 				Metamfetamina			czas trwania (min)	1
#define TYPE_COCAINE					6 //				Kokaina					czas trwania (min)	1
#define TYPE_MAR						7 // 				Marihuana				czas trwania (min)	1
#define TYPE_FIRE						8 //				Podpa³ka				1					1
#define TYPE_RADIO						9 // 				Krótkofalówka			1                   1
#define TYPE_MEGAPHONE					10 // 				Megafon					1 					1
#define TYPE_PICKLOCK					11 //				Wytrych					1 					1
#define TYPE_ROD 						12 // 				Wêdka					1  					1
#define TYPE_BAIT						13 // 				Przynêta				typ przynêty		1
#define TYPE_FISH						14 // 				Ryba 					1 					1
#define TYPE_PHONE 						15 //				Telefon					numer telefonu		1
#define TYPE_CARD						16 // 				Karta kredytowa			ID karty			ID gracza
#define TYPE_MASK						17 // 				Maska					iloœæ u¿yæ			1
#define TYPE_ATTACH						18 // 				Przyczepialny 			model obiektu 		slot u¿ycia
#define TYPE_TUNING						19 // 				Tuning 					ID tuningu 			1
#define TYPE_PLANT						20 // 				Nasiono					ID narkotyku		1
#define TYPE_FOOD						21 // 				Jedzenie				iloœæ g³odu (+)		1
#define TYPE_BEER						22 // 				Piwo 					1 					1
#define TYPE_CIGGY						23 // 				Papierosy				1 					1
#define TYPE_TIME						24 // 				Zegarek					1 					1
#define TYPE_BONE						25 // 				Koœæ do gry 			1 					1
#define TYPE_MONEY						26 // 				Paczka z gotówk¹		kwota				1
#define TYPE_REGISTER					27 // 				Tablice rejestracyjne	1 					1

#define TYPE_COUNT						27

#define	FLAG_DEPARTMENT					1 // Czat departamentowy
#define FLAG_MEGAPHONE					2 // Megafon
#define FLAG_NICK						4 // Kolorowy nick-name
#define FLAG_OUT						8 // Opuszczanie grupy
#define FLAG_CASH						16 // Wyp³acanie gotówki z konta grupy
#define FLAG_DB							32 // Drive By
#define FLAG_BLOCK						64 // Stawianie blokad
#define FLAG_DETENTION					128 // Przetrzymywanie
#define FLAG_ITEM						256	// Zabieranie przedmiotów
#define FLAG_CALL_911					512 // Telefon alarmowy
#define FLAG_REPORTS					1024 // Zg³oszenia grupowe
#define FLAG_GPS						2048 // GPS w pojazdach
#define FLAG_ALARM						4096 // Uruchamianie alarmu w pojazdach

#define ITEM_FLAG_PARALIZE				1 // Paralizator
#define ITEM_FLAG_NODMG					2 // Brak obra¿eñ

#define PANEL_PANEL						1 // Zarz¹dzanie pracownikami
#define PANEL_MAGAZYN					2 // Zarz¹dzanie magazynem
#define PANEL_PRODUCT					4 // Zarz¹dzanie produktami
#define PANEL_OPTION_VEH				8 // Zarz¹dzanie pojazdami
#define PANEL_DOOR						16 // Zarz¹dzanie drzwiami
#define PANEL_OBJECT					32 // Zarz¹dzanie obiektami
#define PANEL_SUBGROUP					64 // Zarz¹dzanie subgrup¹
#define PANEL_VEH						128 // Dostêp do pojazdów
#define PANEL_SPECIAL_VEH				256 // Dostêp do pojazdów specjalnych
#define PANEL_OOC						512 // Dostêp do chatu OOC
#define PANEL_OFFER						1024 // Dostêp do ofert

#define PERM_HOUSE_MEMBER				0 // Mieszkaniec
#define PERM_HOUSE_LEADER				1 // W³aœciciel budynku

#define ADMIN_PERM_THINGS				1 // Zarz¹dzanie przedmiotami
#define ADMIN_PERM_VEHICLES				2 // Zarz¹dzanie pojazdami
#define ADMIN_PERM_GROUPS				4 // Zarz¹dzanie grupami
#define ADMIN_PERM_AREA					8 // Zarz¹dzanie strefami
#define ADMIN_PERM_BAN					16 // Banowanie
#define ADMIN_PERM_PLAYER				32 // Zarz¹dzanie graczami (/set)
#define ADMIN_PERM_CASH					64 // Operacje na gotówce (/set [cash | bank])
#define ADMIN_PERM_OBJECT				128 // Zarz¹dzanie obiektami
#define ADMIN_PERM_DOORS				256 // Zarz¹dzanie drzwiami
#define ADMIN_PERM_GAMESCORE			512 // Nadawanie gamescore
#define ADMIN_PERM_SETTINGS				1024 // Zarz¹dzanie ustawieniami serwera
#define ADMIN_PERM_PRODUCTS				2048 // Zarz¹dzanie produktami
#define ADMIN_PERM_PLANTS				4096 // Zarz¹dzanie roœlinami
#define ADMIN_PERM_SENSORS				8192 // Zarz¹dzanie czujnikami
#define ADMIN_PERM_BUS					16384 // Zarz¹dzanie przystankami
#define ADMIN_PERM_BURGER				32768 // Zarz¹dzanie jedzeniem

#define BLOCK_CHAR						1 // Blokada postaci
#define BLOCK_BAN						2 // Banicja

#define PHASE_NONE          			0
#define PHASE_UDRL        				1
#define PHASE_FB            			2
#define PHASE_ROT           			3

#define BULLET_HIT_TYPE_NONE            0
#define BULLET_HIT_TYPE_PLAYER          1
#define BULLET_HIT_TYPE_VEHICLE         2
#define BULLET_HIT_TYPE_OBJECT          3

#define PENALTY_WARN					1
#define PENALTY_KICK					2
#define PENALTY_BAN						3
#define PENALTY_BLOCK					4
#define PENALTY_SCORE					5
#define PENALTY_AJ						6

#define DAMAGE_TORSO					1
#define DAMAGE_GROIN					2
#define DAMAGE_LEFT_ARM					4
#define DAMAGE_RIGHT_ARM				8
#define DAMAGE_LEFT_LEG					16
#define DAMAGE_RIGHT_LEG				32
#define DAMAGE_HEAD						64

#define TOG_PW							1
#define TOG_AUDIO						2
#define TOG_NAME						4
#define TOG_OOC							8
#define TOG_FM							16

#define OPTION_EDITOR_KEY				1
#define OPTION_EDITOR_MACHINE			0

#define	OPTION_FREEZE					1
#define OPTION_SAY						2
#define	OPTION_KRZYK					4
#define OPTION_PANORAMIC				8
#define OPTION_TOKEN					16

#define STATUS_AFK						1
#define STATUS_DUTY						2
#define STATUS_UNCON					4
#define STATUS_WOREK					8
#define STATUS_KNEBEL					16
#define STATUS_HEALTH					32
#define STATUS_CUFFED					64

#define OFFER_ITEM 						1
#define OFFER_VEHICLE 					2
#define OFFER_FUEL						3
#define OFFER_REPAIR_JOB				4
#define OFFER_ID						5
#define OFFER_DRIVER					6
#define OFFER_FISH						7
#define OFFER_PASSPORT					8
#define OFFER_POLICE					9
#define OFFER_MEDICAL					10
#define OFFER_REGISTER					11
#define OFFER_LICENSE					12
#define OFFER_INSURANCE					13
#define OFFER_ALARM						14
#define OFFER_GATE						15
#define OFFER_VCARD						16
#define OFFER_MANDAT					17
#define OFFER_PASSAGE					18
#define OFFER_PERMIT					19

#define ACCEPT							1
#define REJECT							2

#define JOB_STATION						1

#define WATER_SALT						1
#define WATER_SWEET						2

#define DOC_ID							1
#define DOC_DRIVER						2
#define DOC_FISH						4
#define DOC_PASSPORT					8
#define DOC_LICENSE						16
#define DOC_POLICE						32
#define DOC_MEDICAL						64
#define DOC_INSURANCE					128

#define DOOR_ALARM						1
#define DOOR_GATE						2

#define KEY_1 							64231     
#define KEY_2 							12373
#define KEY_3 							97864 
#define KEY_4 							21675
#define KEY_5 							58786

#define NPC_FREE						0
#define NPC_CLOSE						1
#define NPC_RUN_TO						2
#define NPC_RUN_OUT						3
 
#define MAX_STRING_TO_CODE 				8

#define D_INFO							0
#define D_LOGIN_GLOBAL					1
#define D_MANAGE_VEH					2
#define D_LIST_PLAYER_CARS				3
#define D_LIST_SPAWNED_CARS				4
#define D_CREATE_GROUP_NAME				5
#define D_CREATE_GROUP_TAG				6
#define D_CREATE_GROUP_KIND				7
#define D_DELETE_GROUP					8
#define D_CHECK_LEADER					9
#define D_VEHICLE_GROUP_OPTIONS			10
#define D_VEHICLE_GROUP_OPTIONS_SELECT	11
#define D_SELECT_GLOBAL					12
#define D_ITEM							13
#define D_ITEM_OPTION					14
#define D_RAISE_ITEM					15
#define D_CHANGE_VEHICLE				16
#define D_SLOT_VEHICLE					17
#define	D_FLAG_GROUP					18
#define D_ITEM_NAME						19
#define D_ITEM_TYPE						20
#define D_ITEM_VALUE1					21
#define D_ITEM_VALUE2					22
#define D_TOG							23
#define D_AREA_1						24
#define D_DOOR_OPTIONS					25
#define D_DOOR_ITEMS					26
#define D_MAGAZINE						27
#define D_OFFER_ITEMS					28
#define D_OFFER_VEHICLES				29
#define D_OFFER_ITEMS_PLAYERS			30
#define D_OFFER_VEHICLES_PLAYERS		31
#define D_DOOR_NAME						32
#define D_DOOR_PRICE					33
#define D_PHONE							34
#define D_PHONE_CALL					35
#define D_PHONE_SMS						36
#define D_PHONE_SMS_SEND				37
#define D_BLOCK_CHAR					38
#define D_CONTACTS						39
#define D_CONTACT_OPTIONS				40
#define D_CHANGE_CONTACT_NAME			41
#define D_BANK							42
#define D_CREATE_CARD					43
#define D_CREATED_CARD					44
#define D_CARD_INFO						45
#define D_CARD_OPTIONS					46
#define D_BLOCK_CARD					47
#define D_CHANGE_CARD_PIN				48
#define D_CHANGE_CARD_NAME				49
#define D_CASH_OUT						50
#define D_CASH_IN						51
#define D_EDIT_GROUP					52
#define D_CHECK_GROUP					53
#define D_GROUP_NAME 					54
#define D_GROUP_TAG 					55
#define D_GROUP_KIND 					56
#define D_GROUP_LIMIT					57
#define D_GROUP_TAX 					58
#define D_GROUP_LEADER 					59
#define D_GROUP_CHECK_LEADER 			60
#define D_GROUP_MEMBERS 				61
#define D_CALL_911						62
#define D_CALL_911_REASON				63
#define D_REPORTS 						64
#define D_REPORT_OPTIONS				65
#define D_OUT_ITEM						66
#define D_TAXI							67
#define D_RADIO							68
#define D_GROUP_MAGAZINE				69
#define D_ORDER_CATEGORY				70
#define D_ORDER_VALUE					71
#define D_ORDER_ID						72
#define D_ORDER_MAGAZINE				73
#define D_DESCRIPTIONS					74
#define D_USE_DESC						75
#define D_CREATE_DESC					76
#define D_DELETE_DESC					77
#define D_DELETE_ALL_DESC				78
#define D_TEXT_DESC						79
#define D_USE_SUBGROUP					80
#define D_DRUG_OUT						81
#define D_DRUG_OUT_2					82
#define D_ATTACH_USE					83
#define D_PRODUCT_TYPE 					84
#define D_PRODUCT_KIND 					85
#define D_PRODUCT_VALUE1 				86
#define D_PRODUCT_VALUE2 				87
#define D_PRODUCT_NAME 					88
#define D_PRODUCT_GROUP 				89
#define D_PRODUCT_CASH					90
#define D_REWRITE_DOOR					91
#define D_PRIV_MSG						92
#define D_CHANGE_DOOR_AUDIO				93
#define D_BURGER_BUY					94
#define D_CHOOSE_BURGER					95
#define D_HELP							96

#undef 	MAX_PLAYERS
#undef 	MAX_VEHICLES
#undef 	MAX_OBJECTS
#define MAX_PLAYERS						100
#define MAX_VEHICLES    				800
#define MAX_GROUPS						500
#define MAX_PLAYER_GROUPS				4
#define MAX_SLOT_GROUPS					3
#define MAX_LIST_ITEMS      			10
#define MAX_ITEMS						3200
#define MAX_SUBGROUPS					500
#define MAX_AREAS						4001
#define MAX_DOORS						200
#define MAX_BUSSTOP						50
#define MAX_CORPS						100
#define MAX_REPORTS						500
#define MAX_GANGS						11
#define MAX_DESC						500
#define MAX_LABELS						500
#define MAX_ATTACH						1000
#define MAX_SENSORS						10
#define MAX_OBJECTS						10000
#define MAX_PLANTS						200
#define MAX_BURGERS						20
#define MAX_AREA 						3601
#define MAX_RACES						500

#define DEF_NAME						"Innovation RolePlay"

#define PlayerToPoint(%0,%1,%2,%3,%4) IsPlayerInRangeOfPoint(%1,%0,%2,%3,%4)
#define ForeachEx(%2,%1) for(new %2 = 0; %2 < %1; %2++)
#define GetDistanceBetweenPoints(%0,%1,%2,%3,%4,%5) (((%0 - %3) * (%0 - %3)) + ((%1 - %4) * (%1 - %4)) + ((%2 - %5) * (%2 - %5)))