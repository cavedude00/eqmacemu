// ***************************************************************
//  Player Profile   ·  date: 7/06/2008
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef PLAYERPROFILE_H
#define PLAYERPROFILE_H

#include "types.h"
#include "config.h"
#include "GuildNetwork.h"
#include "../../Zone/Include/spdat.h"

using namespace EQC::Common::Network;

// Compiler override to ensure byte aligned structures
#pragma pack(1)

/*
** Buffs
** Length: 10 Bytes
** Used in:
**    playerProfileStruct(2d20)
*/
struct SpellBuff_Struct
{
	/*000*/int8  visable;		// Comment: Cofruben: 0 = Buff not visible, 1 = Visible and permanent buff(Confirmed by Tazadar) , 2 = Visible and timer on(Confirmed by Tazadar) 
	/*001*/int8  level;			// Comment: Level of person who casted buff
	/*002*/int8  bard_modifier;	// Comment: Harakiri: this seems to be the bard modifier, it is normally 0x0A because we set in in the CastOn_Struct when its not a bard, else its the instrument mod
	/*003*/int8  b_unknown3;	// Comment: ***Placeholder
	/*004*/int16 spellid;		// Comment: Unknown -> needs confirming -> ID of spell?
	/*006*/int32 duration;		// Comment: Unknown -> needs confirming -> Duration in ticks
};

// Length: 10
struct ItemProperties_Struct {

int8	unknown01[2];
sint8	charges;				// Comment: Harakiri signed int because unlimited charges are -1
int8	unknown02[7];
};

/*
** Player Profile
** Length: 8104 Bytes
*/
struct PlayerProfile_Struct
{
#define pp_inventory_size 30
#define pp_containerinv_size 80
#define pp_cursorbaginventory_size 10
#define pp_bank_inv_size 8
#define pp_bank_cont_inv_size 80
/* ***************** */

/*0000*/	int8	checksum[4];		// Checksum
/*0004*/	int8	unknown0004[2];		// ***Placeholder
/*0006*/	char	name[64];			// Player First Name
/*0070*/	char	Surname[70];		// Player Last Name
/*0140*/	int8	gender;				// Player Gender
/*0141*/	int8	unknown0141;		// ***Placeholder
/*0142*/	int16	race;				// Player Race (Lyenu: Changed to an int16, since races can be over 255)
/*0144*/	int16	class_;				// Player Class
/*0146*/	int8	unknown0146;		// ***Placeholder
/*0147*/	int8	unknown0147;		// ***Placeholder
/*0148*/	int8	level;				// Player Level
/*0149*/	int8	unknown0149;		// ***Placeholder
/*0150*/	int8	unknown0150[2];		// ***Placeholder
/*0152*/	int32	exp;				// Current Experience
/*0156*/	int16	trainingpoints;				// Players Points
/*0158*/	int16	mana;				// Player Mana
/*0160*/	int16	cur_hp;				// Player Health
/*0162*/	int16	face;				// Players Face
/*0164*/	int16	STR;				// Player Strength
/*0166*/	int16	STA;				// Player Stamina
/*0168*/	int16	CHA;				// Player Charisma
/*0170*/	int16	DEX;				// Player Dexterity
/*0172*/	int16	INT;				// Player Intelligence
/*0174*/	int16	AGI;				// Player Agility
/*0176*/	int16	WIS;				// Player Wisdom
/*0178*/	int8	face_;               //
/*0179*/    int8    EquipType[9];       // i think its the visible parts of the body armor
/*0188*/    int32   EquipColor[9];      //
/*0224*/	int16	inventory[30];		// Player Inventory Item Numbers
/*0284*/	int8	languages[26];		// Player Languages
/*0310*/	int8	unknown0310[6];		// ***Placeholder
/*0316*/	struct	ItemProperties_Struct	invItemProprieties[30];
										// These correlate with inventory[30]
/*0616*/	struct	SpellBuff_Struct	buffs[15];
										// Player Buffs Currently On
/*0766*/	int16	containerinv[pp_containerinv_size];	// Player Items In "Bags"
										// If a bag is in slot 0, this is where the bag's items are
/*0926*/	int16   cursorbaginventory[10];
/*0946*/	struct	ItemProperties_Struct	bagItemProprieties[pp_containerinv_size];
										// Just like InvItemProperties
/*1746*/    struct  ItemProperties_Struct	cursorItemProprieties[10];
                                          //just like invitemprops[]
/*1846*/	sint16	spell_book[256];	// Player spells scribed in their book
/*2358*/	int8	unknown2374[512];	// ***Placeholder
/*2870*/	sint16	spell_memory[8];	// Player spells memorized
/*2886*/	int8	unknown2886[14];			// ***Placeholder [16]
/*2900*/	int16	unknown2900;
/*2902*/	float	x;					// Player X
/*2906*/	float	y;					// Player Y
/*2910*/	float	z;					// Player Z
/*2914*/	float	heading;			// Player Heading
/*2918*/	int8	unknown2920[6];		// ***Placeholder
/*2924*/	int32	platinum;			// Player Platinum (Character)
/*2928*/	int32	gold;				// Player Gold (Character)
/*2932*/	int32	silver;				// Player Silver (Character)
/*2936*/	int32	copper;				// Player Copper (Character)
/*2940*/	int32	platinum_bank;		// Player Platinum (Bank)
/*2944*/	int32	gold_bank;			// Player Gold (Bank)
/*2948*/	int32	silver_bank;		// Player Silver (Bank)
/*2952*/	int32	copper_bank;		// Player Copper (Bank)
/*2956*/	int32	platinum_cursor;
/*2960*/	int32	gold_cursor;
/*2964*/	int32	silver_cursor;
/*2968*/	int32	copper_cursor;
/*2972*/	int8	unknown2972[16];	// ***Placeholder
/*2988*/	int16	skills[75];			// Player Skills
/*3138*/	int32	hungerlevel;		// Probably wrong, previously was in the spot where skills should be.
/*3142*/	int32	thirstlevel;		// Probably wrong, previously was in the spot where skills should be.
/*3146*/	int8	unknown3144[202];
/*3348*/	int8	autosplit;
/*3349*/	int8	unknown3449[95];
/*3444*/	int32	current_zone;		// 
/*3448*/	int8	unknown3448[336];	// ***Placeholder
/*3784*/	int32	bind_point_zone;	// Lyenu: Bind zone is saved as a int32 now
/*3788*/	int32	start_point_zone[4];
										// Lyenu: Start Point Zones are saved as int32s now
/*3804*/	float	bind_location[3][5];
										// Player Bind Location (5 different X,Y,Z - Multiple bind points?)
/*3864*/	int8	unknown3656[20];	// ***Placeholder
/*3884*/	ItemProperties_Struct	bankinvitemproperties[8];
/*3964*/	ItemProperties_Struct	bankbagitemproperties[80];
/*4764*/	int8	unknown4556[4];
/*4768*/	int16	bank_inv[8];		// Player Bank Inventory Item Numbers
/*4784*/	int16	bank_cont_inv[80];	// Player Bank Inventory Item Numbers (Bags)
/*4944*/	int16	deity;		// ***Placeholder
/*4946*/	int16	guildid;			// Player Guild ID Number
/*4948*/	int32   BirthdayTime;
/*4952*/	int32   Unknown_4952;
/*4956*/	int32   TimePlayedMin;
/*4960*/	int8    Unknown_4960[2];
/*4962*/	int8    fatigue;
/*4963*/	int8	pvp;				// Player PVP Flag
/*4964*/	int8	unknown4756;		// ***Placeholder
/*4965*/	int8	anon;				// Player Anon. Flag
/*4966*/	int8	gm;					// Player GM Flag
/*4967*/	sint8	guildrank;			// Player Guild Rank (0=member, 1=officer, 2=leader)
/*4968*/	int8	unknown4760[44];
/*5012*/	char	GroupMembers[6][64];	// Group Members
/*5396*/	int8	unknown5124[29];	// ***Placeholder 
/*5425*/	int8	AAPercent;			// Player AA Percent
/*5426*/	int8	haircolor;			// Player Hair Color
/*5427*/	int8	beardcolor;			// Player Beard Color
/*5428*/	int8	eyecolor1;			// Player Left Eye Color
/*5429*/	int8	eyecolor2;			// Player Right Eye Color
/*5430*/	int8	hairstyle;			// Player Hair Style
/*5431*/	int8	beard_t;			// T7g: Beard Type, formerly title - I have no clue why, Title moved a few lines below this one
/*5432*/	int8	luclinface;			// Player Face Type (Is that right?)
/*5433*/	int8	unknown5225[195];	// ***Placeholder
/*5628*/	int32	expAA;				// AA Exp
/*5632*/	int8	title;				// AA Title
/*5633*/	int8	perAA;				// AA Percentage
/*5634*/	int32	aapoints;			// AA Points
/*5638*/	int8	unknown5426[2822];	// Unknown
//			int32	raid_id;			// Raid ID?
//			int32	unknown5450;		// Unknown (Added 09 Oct 2002)
};
// Restore structure packing to default
#pragma pack()

#endif