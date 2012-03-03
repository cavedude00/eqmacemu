// ***************************************************************
//  EQCException   ·  date: 21/12/2007
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// Guidelines for Structures
// ***************************************************************
// As these strcutures are the core of how the server and client communicate, 
// some guidelines have been implimented to sure minimual defects and easy reading
// ***************************************************************
// 1. If you have confirmed a variable inside a strcuture, add the following lineto the comment:
//	  // Comment: Confirmed - Username - Date
//
// 2. When you discover the variables purpose give it a coorsponding name i.e haircolor, STA, DEX, then see Guidline 1
//
// 3. A structure MUST have a description about what it SHOULD contine, and what uses it. ideally also linked to an opcode!
//
// - Dark-Prince - 29/01/2008
// ***************************************************************
#ifndef EQ_PACKET_STRUCTS_H
#define EQ_PACKET_STRUCTS_H 

#include "types.h"
#include "config.h"
#include "GuildNetwork.h"
#include "PlayerProfile.h"

using namespace EQC::Common::Network;

/*
** Compiler override to ensure
** byte aligned structures
*/
#pragma pack(1)

// Valus of weapon types
enum SKILLTYPE : uint8
{
	SKILLTYPE_1HSLASHING = 0x00,
	SKILLTYPE_2HSLASHING = 0x01,
	SKILLTYPE_PIERCING = 0x02,
	SKILLTYPE_1HBLUNT = 0x03,
	SKILLTYPE_2HBLUNT = 0x04,
	SKILLTYPE_2HPIERCING = 0x23
};

enum TSpawnAppearanceType : int16 {		// Cofruben: Better this way..
	SAT_SendToBind			= 0,	// Comment: 0=send to bind, >0 = kill them
	SAT_LevelChange			= 1,	// Comment: the level that shows up on /who
	SAT_Invis				= 3,	// Comment: 0=visable, 1=invisable
	SAT_PvP					= 4,	// Comment:	0=disable, 1=enable
	SAT_Light				= 5,	// Comment:	
	SAT_Position_Update		= 14,	// Comment: 100=standing, 102=lose control (fear, mez, charm), 110=sitting, 111=ducking, 115=feigned, 105=looting
	SAT_Sneaking			= 15,	// Comment:
	SAT_Camp				= 16,	// Comment:
	SAT_HP_Regen			= 17,	// Comment: Client->Server, my HP has changed (like regen tic)
	SAT_LD					= 18,	// Comment:
	SAT_Levitate			= 19,	// Comment: 0=off, 1=flymode, 2=levitate
	SAT_GM_Tag				= 20,
	SAT_NameColor			= 21,	// Comment:	AT_PVP[0=green,1=dark red,2=light red] or !AT_PVP[0=green,1=blue,2=purple]
	SAT_Guild_ID			= 22,	// Comment: Joins player to the specified guild id param.
	SAT_Guild_Rank			= 23,	// Comment: 0=member, 1=officer, 2=leader
	SAT_AFK					= 24,	// Comment: 0=off, 1=on
	SAT_Autosplit			= 28,
	SAT_Size				= 29,	// Comment: spawn's size (0=smallest)
	SAT_NPC_Name			= 30	// Comment: change PC's name's color to NPC color (unreversable)
};

enum TBodyType : int16 {	// Cofruben: 16/08/08.
	BT_Humanoid			= 1,
	BT_Lycanthrope		= 2,
	BT_Undead			= 3,
	BT_Giant			= 4,
	BT_Construct		= 5,
	BT_Extraplanar		= 6,
	BT_Magical			= 7,	//this name might be a bit off, 
	BT_SummonedUndead	= 8,
	BT_NoTarget			= 11,	// can't target this bodytype
	BT_Vampire			= 12,
	BT_Atenha_Ra		= 13,
	BT_Greater_Akheva	= 14,
	BT_Khati_Sha		= 15,
	BT_Zek				= 19,
	BT_Luggald			= 20,
	BT_Animal			= 21,
	BT_Insect			= 22,
	BT_Monster			= 23,
	BT_Summoned			= 24,	//Elemental?
	BT_Plant			= 25,
	BT_Dragon			= 26,
	BT_Summoned2		= 27,
	BT_Summoned3		= 28,
	BT_VeliousDragon	= 30,	//might not be a tight set
	BT_Dragon3			= 32,
	BT_Boxes			= 33,
	BT_Muramite			= 34,	//tribal dudes
	BT_NoTarget2		= 60,
	BT_SwarmPet			= 63,	//is this valid, or made up?
	BT_Trigger			= 65,   //Yeahlight: Body type to completely hide the spawn
	BT_InvisMan			= 66,	//seen on 'InvisMan'
	BT_Special			= 67
};

enum TSpawnAppearancePositionParameter : int32 {
	SAPP_Sitting_To_Standing	= 100,
	SAPP_Lose_Control			= 102,
	SAPP_Looting				= 105,
	SAPP_Standing_To_Sitting	= 110,
	SAPP_Ducking				= 111,
	SAPP_Unconscious			= 115
};

/************************************************************** 
CharacterSelect_Struct - neorab 9/28/2007 

This structure is sent from the world in world/client.cpp in 
the Client::SendCharInfo() method.  Although there are only
eight character slots, all ten must be sent to correctly pack
the struct.

The equip portion of the character's data is represented by:
equip[x][0]=helm 
equip[x][1]=chest 
equip[x][2]=arm
equip[x][3]=bracer
equip[x][4]=hand
equip[x][5]=leg
equip[x][6]=boot
equip[x][7]=melee1
equip[x][8]=melee2

1-6 all follow the format of 0=none, 1=leather, 2=chain, 3=plate
and 4=monk straps (sexy humans)

7 and 8 need not be sent.  They must be there for padding but
the actuall data is requested by the client when they select the
char on screen.

I am not sure what, if any, purpose the unknown serves here 
other than padding.  Removing it does break the character select 
screen.

03/09/08 - Wizzel
Verified that the color was reading grabbing red values from blue,
green from alpha, and blue from red. Shifted the color portion
over two bytes and fixed the problem. No luck with weapons yet.

***************************************************************/
struct CharacterSelect_Struct
{
/*0000*/	char	name[10][64];		// Characters Names
/*0640*/	int8	level[10];			// Characters Levels
/*0650*/	int8	class_[10];			// Characters Classes
/*0660*/	int16	race[10];			// Characters Race
/*0680*/	int32	zone[10];			// Characters Current Zone
/*0720*/	int8	gender[10];			// Characters Gender
/*0730*/	int8	face[10];			// Characters Face Type
/*0740*/	int32	equip[10][9];		// 0=helm, 1=chest, 2=arm, 3=bracer, 4=hand, 5=leg, 6=boot, 7=melee1, 8=melee2
/*1100*/	int32	cs_colors[10][9];	// Characters Equipment Colors (RR GG BB 00)
/*1460*/	int8	cs_unknown[160];	// ***Placeholder
};

//Tazadar : This is used to show weapons on char select screen
struct CharWeapon_Struct
{
	int16 righthand[10];
	int16 lefthand[10];
};

struct ServerZoneEntry_Struct {
/*0000*/	int8	checksum[4];		// Checksum
/*0004*/	int8	unknown0004;		// ***Placeholder
/*0005*/	char	name[64];			// Name
/*0069*/	int8	sze_unknown0069;	// ***Placeholder
/*0070*/	int16	unknown0070;		// ***Placeholder
/*0072*/	int32	zone;				// Current Zone
#ifndef INVERSEXY
/*0076*/	float	x;					// X Position (Not Inversed)
/*0080*/	float	y;					// Y Position (Not Inversed)
#else
/*0076*/	float	y;					// Y Position (Inversed)
/*0080*/	float	x;					// X Position (Inversed)
#endif
/*0084*/	float	z;					// Z Position
/*0088*/	float	heading;			// Heading
/*0092*/	int32	unknown0092[18];	// ***Placeholder
/*0164*/	int16	guildeqid;			// Guild ID Number
/*0166*/	int8	unknown0166[7];		// ***Placeholder
/*0173*/	int8	class_;				// Class
/*0174*/	int16	race;				// Race
/*0176*/	int8	gender;				// Gender
/*0177*/	int8	level;				// Level
/*0178*/	int16	unknown0178;		// ***Placeholder	
/*0180*/	int8	pvp;				// PVP Flag
/*0181*/	int16	unknown0181;		// ***Placeholder
/*0183*/	int8	face;				// Face Type
/*0184*/	int16	helmet;				// Helmet Visual
/*0186*/	int16	chest;				// Chest Visual
/*0188*/	int16	arms;				// Arms Visual
/*0190*/	int16	bracers;			// Bracers Visual
/*0192*/	int16	hands;				// Hands Visual
/*0194*/	int16	legs;				// Legs Visual
/*0196*/	int16	feet;				// Feet Visual
/*0198*/	int16	melee1;				// Weapon 1 Visual
/*0200*/	int16	melee2;				// Weapon 2 Visual
/*0202*/	int16	unknown;			// ***Placeholder
/*0204*/	int32	helmet_color;		// Helmet Visual Color
/*0208*/	int32	chest_color;		// Chest Visual Color
/*0212*/	int32	arms_color;			// Arms Visual Color
/*0216*/	int32	bracers_color;		// Bracers Visual Color
/*0220*/	int32	hands_color;		// Hands Visual Color
/*0224*/	int32	legs_color;			// Legs Visual Color
/*0228*/	int32	feet_color;			// Feet Visual Color
/*0232*/	int32	melee1_color;		// Weapon 1 Visual Color
/*0236*/	int32	melee2_color;		// Weapon 2 Visual Color
/*0240*/	int8	npc_armor_graphic;	// Texture (0xFF=Player - See list of textures for more)
/*0241*/	int8	unknown0241[19];	// ***Placeholder
/*0260*/	float	walkspeed;			// Speed when you walk
/*0264*/	float	runspeed;			// Speed when you run
/*0268*/	int32	unknown0268[3];		// ***Placeholder (At least one flag in here disables a zone point or all)
/*0280*/	int8	anon;				// Anon. Flag
/*0281*/	int8	unknown0281[23];	// ***Placeholder (At least one flag in here disables a zone point or all)
/*0304*/	char	Surname[34];		// Lastname (This has to be wrong.. but 70 is to big =/..)
/*0338*/	int16	deity;				// Diety (Who you worship for those less literate)
/*0340*/	int8	unknown0340;		// ***Placeholder
/*0341*/	int8	haircolor;			// Hair Color
/*0342*/	int8	beardcolor;			// Beard Color
/*0343*/	int8	eyecolor1;			// Left Eye Color
/*0344*/	int8	eyecolor2;			// Right Eye Color
/*0345*/	int8	hairstyle;			// Hair Style
/*0346*/	int8	title;				// AA Title
/*0347*/	int8	luclinface;			// Face Type
/*0348*/	int8	skyradius;			// Skyradius (Lyenu: Not sure myself what this is)
/*0349*/	int8	unknown321[7];		// ***Placeholder
};

// 372 bytes

/*
** New Zone Struct
** OPCODE: 5b20
** Length: 372 Bytes
*/
// Wizzel: Loads information about the zone to be entered by the client.
// I have figured out nearly all relevant stuff. The unknowns are
// still handled correctly. This is a very fragile struct. If you have
// any questions, ask me about it.

struct NewZone_Struct 
{
/*0000*/	char	char_name[64];			// Character Name
/*0064*/	char	zone_short_name[32];	// Zone Short Name
/*0096*/	char	zone_long_name[278];	// Zone Long Name
/*0374*/	int8	zonetype;
/*0375*/	int8	fog_red[4];				// Red Fog 0-255 repeated over 4 bytes (confirmed: Wizzel)
/*0379*/	int8	fog_green[4];			// Green Fog 0-255 repeated over 4 bytes (confirmed: Wizzel)
/*0383*/	int8	fog_blue[4];			// Blue Fog 0-255 repeated over 4 bytes (confirmed: Wizzel)
/*0387*/	uint8	unknown387;
/*0388*/	float	fog_minclip[4];			// Where the fog begins (lowest clip setting). Repeated over 4 floats. (confirmed: Wizzel)
/*0404*/	float	fog_maxclip[4];			// Where the fog ends (highest clip setting). Repeated over 4 floats. (confirmed: Wizzel)	
/*0420*/	float	walkspeed;				// CD CC CC 3E Can't move if incorrect
/*0424*/	int8	time_type;
/*0425*/	uint8	unknown425[49];
/*0474*/	uint8	sky;
/*0475*/	uint8	zone_exp_multiplier;
/*0492*/	float	safe_y;
/*0496*/	float	safe_x;
/*0500*/	float	safe_z;
/*0504*/	float	maz_z;
/*0508*/	float	underworld;
/*0512*/	float	minclip;				// Minimum View Distance
/*0516*/	float	maxclip;				// Maximum View DIstance
/*0520*/	int8	unknown_end[52];		// ***Placeholder
};


struct MemorizeSpell_Struct 
{ 
	int32 slot;			// Comment:  Spot in the spell book/memorized slot 
	int32 spell_id;		// Comment:  Spell id (200 or c8 is minor healing, etc) 
	int32 scribing;		// Comment:  1 if memorizing a spell, set to 0 if scribing to book 
}; 

struct CastOn_Struct 
{
/*00*/	int32	target_id;			// Comment: Spell Targets ID 
/*02*/	int32	source_id;			// Comment: Spell Caster ID
/*04*/	int8	source_level;		// Comment: Spell Casters Level
/*05*/	int8	unknown1[4];		// Comment: Unknown -> needs confirming 
/*09*/	int8	unknown_zero1[7];	// Comment: Unknown -> needs confirming -> (orginal comment: lol) <- lol 
/*16*/	float	heading;			// Comment: Heading of Who? Caster or Target? Needs confirming
/*20*/	int8	unknown_zero2[4];	// Comment: Unknown -> needs confirming
/*24*/	int32	action;				// Comment: Unknown -> needs confirming -> Which action target or caster does maybe?
/*28*/	int16	spell_id;			// Comment: Spell ID of the Spell being casted? Needs Confirming
/*30*/	int8	unknown2[2];		// Comment: Unknown -> needs confirming
};

struct InterruptCast_Struct
{
	int16	spawnid;		// Comment: ID of Spell Caster
	int16	unknown1;		// Comment: Unknown -> needs confirming -> placeholder?
	char	message[0];		// Comment: Unknown -> needs confirming -> Message of what? the spell cast text?
};

struct ManaChange_Struct
{
	uint16 new_mana;	// Comment:  New Mana AMount
	uint16 spell_id;	// Comment:  Last Spell Cast
};

struct SwapSpell_Struct 
{ 
	int32 from_slot;	// Comment: Moving Spells around?
	int32 to_slot;		// Comment: Moving Spells Around?
}; 

struct BeginCast_Struct
{
/*000*/	int32	caster_id;		// Comment: Unknown -> needs confirming -> ID of Spell Caster? 
/*004*/	int32	spell_id;		// Comment: Unknown -> needs confirming -> ID of Spell being Cast?
/*008*/	int32	cast_time;		// Comment: Unknown -> needs confirming -> in miliseconds?
};

struct Buff_Struct
{
	uint32	target_id;		// Comment: Unknown -> needs confirming -> Target of the Buff
	uint32	b_unknown1;		// Comment: Unknown -> needs confirming
	uint16	spell_id;		// Comment: Unknown -> needs confirming -> Spell ID?
	uint32	b_unknown2;		// Comment: Unknown -> needs confirming
	uint16	b_unknown3;		// Comment: Unknown -> needs confirming
	uint32	buff_slot;		// Comment: Unknown -> needs confirming -> Which buff slot on the target maybe?
};

#define SLOT_ITEMSPELL		10		// Cofruben: we right clicked into a clickable item which allow us casting some spell.
struct CastSpell_Struct
{
	int16	slot;
	int16	spell_id;
	int16	inventoryslot;  // slot for clicky item, 0xFFFF = normal cast
	int16	target_id;
	int32	cs_unknown2;
};


//Yeahlight
//NOTEABLE TYPES (In decimal):
//  + 21: This type will remove you from your own client list and
//        possibly the list of others (GM spying).
struct SpawnAppearance_Struct
{
// len = 8
/*0000*/ uint16 spawn_id;          // ID of the spawn
/*0002*/ uint16 type;              // Values associated with the type
/*0004*/ uint32 parameter;         // Type of data sent
};

// Length: 24
struct SpellBuffFade_Struct {
/*000*/ uint32  playerid;       // Comment: Id of the player
/*004*/	int8	unknown000[4];	// Comment: 
/*008*/	int16	spellid;		// Comment: 
/*010*/	int8	unknown010[6];	// Comment: 
/*016*/	int8	slotid;			// Comment:  Buff slot # on the client
/*017*/	int8	unknown017[3];	// Comment: 
/*020*/	int8	fade;			// Comment: 01 = true
/*021*/	int8	unknown[3];		// Comment: 
};

/*
** client changes target struct
** Length: 2 Bytes
** OpCode: 6221
*/
struct ClientTarget_Struct {
/*000*/	int16	new_target;			// Target ID
};

/*
** Yeahlight
** Client hits taunt
** Length: 12 Bytes
** OpCode: 3b21
*/
struct ClientTaunt_Struct
{
	int16  tauntTarget;		// Comment: ID of target
	int16  buffer;          // Comment: ***Placeholder
	int16  tauntUser;		// Comment: ID of taunter
	int8   buffer2[6];		// Comment: ***Placeholder
};

struct Spawn_Struct
{
/*0000*/	int8	animation;
/*0001*/	int8	heading;			// Current Heading
/*0002*/	int8	deltaHeading;		// Delta Heading
#ifndef INVERSEXY
/*0003*/	sint16	x_pos;				// X Position
/*0005*/	sint16	y_pos;				// Y Position
#else
/*0003*/	sint16	y_pos;				// Y Position
/*0005*/	sint16	x_pos;				// X Position
#endif
/*0007*/	sint16	z_pos;				// Z Position
/*0009*/	sint32	deltaY:10,			// Velocity Y
					spacer1:1,			// Placeholder
					deltaZ:10,			// Velocity Z
					spacer2:1,			// ***Placeholder
					deltaX:10;			// Velocity X
/*0013*/	int8	unknown0051;
/*0014*/	int16	pet_owner_id;		// Id of pet owner (0 if not a pet)
/*0016*/	int8	s_unknown1a[8];		// Placeholder
/*0024*/	float	size;
/*0028*/	float	walkspeed;
/*0032*/	float	runspeed;
/*0036*/	int32	equipcolors[7];
/*0064*/	int8	unknown0064[8];
/*0072*/	uint16	spawn_id;			// Id of new spawn
/*0074*/	int8	traptype;			// 65 is disarmable trap, 66 and 67 are invis triggers/traps
/*0075*/	int8	unknown0075;
/*0076*/	sint16	cur_hp;				// Current hp's of Spawn
/*0078*/	int16	GuildID;			// GuildID - previously Current hp's of Spawn
/*0080*/	int16	race;				// Race
/*0082*/	int8	NPC;				// NPC type: 0=Player, 1=NPC, 2=Player Corpse, 3=Monster Corpse, 4=???, 5=Unknown Spawn,10=Self
/*0083*/	int8	class_;				// Class
/*0084*/	int8	gender;				// Gender Flag, 0 = Male, 1 = Female, 2 = Other
/*0085*/	int8	level;				// Level of spawn (might be one sint8)
/*0086*/	int8	invis;				// 0=visable, 1=invisable
/*0087*/	int8	unknown0087;
/*0088*/	int8	pvp;
/*0089*/	int8	anim_type;
/*0090*/	int8	light;				// Light emitting
/*0091*/	int8	anon;				// 0=normal, 1=anon, 2=RP
/*0092*/	int8	AFK;				// 0=off, 1=on
/*0093*/	int8	unknown078;
/*0094*/	int8	LD;					// 0=NotLD, 1=LD
/*0095*/	int8	GM;					// 0=NotGM, 1=GM
/*0096*/	int8	s_unknown5_5;		// used to be s_unknown5[5]
/*0097*/	int8	npc_armor_graphic;	// 0xFF=Player, 0=none, 1=leather, 2=chain, 3=steelplate
/*0098*/	int8	npc_helm_graphic;	// 0xFF=Player, 0=none, 1=leather, 2=chain, 3=steelplate
/*0099*/	int8	s_unknown0099;		// used to be s_unknown5[2]
/*0100*/	int16	equipment[9];		// Equipment worn: 0=helm, 1=chest, 2=arm, 3=bracer, 4=hand, 5=leg, 6=boot, 7=melee1, 8=melee2
/*0118*/	sint8	guildrank;			// ***Placeholder
/*0119*/	int8	unknown0207;
/*0120*/	int16	deity;				// Deity.
/*0122*/	int8	unknown122;			// ***Placeholder
/*0123*/	char	name[64];			// Name of spawn (len is 30 or less)
/*0187*/	char	Surname[20];		// Last Name of player
/*0207*/	int8	haircolor;
/*0208*/	int8	beardcolor;
/*0209*/	int8	eyecolor1;			// the eyecolors always seem to be the same, maybe left and right eye?
/*0210*/	int8	eyecolor2;
/*0211*/	int8	hairstyle;
/*0212*/	int8	title;				//Face Overlay? (barbarian only)
/*0213*/	int8	luclinface;			// and beard
			int8	unknownpop[6];
};

/*
** New Spawn
** Length: 176 Bytes
** OpCode: 4921
*/
struct NewSpawn_Struct
{
	int32  ns_unknown1;            // Comment: ***Placeholder
	struct Spawn_Struct spawn;     // Comment: Spawn Information
};

/*
** Delete Spawn
** Length: 2 Bytes
** OpCode: 2b20
*/
struct DeleteSpawn_Struct
{
/*00*/ int16 spawn_id;				// Comment: Spawn ID to delete
	   int32 ds_unknown1;			// Comment: 
};

/*
** Channel Message received or sent
** Length: 71 Bytes + Variable Length + 4 Bytes
** OpCode: 0721
*/
//Yeahlight: Old ChannelMessage_Struct struct (DO NOT DELETE)
//struct ChannelMessage_Struct
//{
//	char  targetname[32];		// Comment:  Tell recipient
//	char  sender[23];           // Comment:  The senders name (len might be wrong)
//	int8  cm_unknown2[9];       // Comment:  ***Placeholder
//	int16  language;            // Comment:  Language
//	int16  chan_num;            // Comment:  Channel
//	int8  cm_unknown4[5-1];     // Comment:  ***Placeholder
//	char  message[0];           // Comment:  Variable length message
//};

//Yeahlight: New ChannelMessage_Struct struct
struct ChannelMessage_Struct
{
/*000*/	char	targetname[64];		// Tell recipient
/*064*/	char	sender[64];			// The senders name (len might be wrong)
/*128*/	int16	language;			// Language
/*130*/	int16	chan_num;			// Channel
/*132*/	int8	cm_unknown4[2];		// ***Placeholder
/*134*/	int16	skill_in_language;	// The players skill in this language? might be wrong
/*136*/	char	message[0];			// Variable length message
};

//Kibanu: New EmoteMessage_Struct
struct EmoteMessage_Struct
{
	char to[32];		// Comment: Recipient
	int32 guilddbid;	// Comment: 
	int32 type;			// Comment: 
	char message[0];	// Comment: variable-length message
};

/*
** When somebody changes what they're wearing
**      or give a pet a weapon (model changes)
** Length: 16 Bytes
** Opcode: 9220
** This is not correct, but close.
*/

struct WearChange_Struct
{
/*000*/ int16 spawn_id;
/*002*/ int16 wear_slot_id;
/*004*/ int16 slot_graphic;
/*006*/ int8 color;
/*007*/ int8 unknown3;
/*009*/ int8 blue;
/*010*/ int8 green;
/*011*/ int8 red;
/*012*/ int8 unknown4;
};

/*
** Type:   Bind Wound Structure		//////////////////////////////////////////
** Length: 8 Bytes					//		BindWound_Struct				//
** OpCode: 9320						//		Moraj 08.20.09					//
*/									//////////////////////////////////////////
struct BindWound_Struct				// to = TargetID						//
{									// type = Return Action Type			//
/*000*/	int16	to;					// Bind Wound Return Action Types:		//
/*002*/	int16	unknown2;			// 0/1 = Complete						//
/*004*/	int16	type;				// 2 = Unlock Movement					//
/*006*/	int16	unknown6;			// 3 = Unlock Interface					//
};									// 4 = Fail: Target Died				//
									// 5 = Fail: Target Left Zone			//
									// 6 = Fail: Target Moved Away			//
									// 7 = Fail: You Moved					//
									//////////////////////////////////////////

//Used inside the object struct for items with effects.
//Size: 10 bytes
struct Object_Data_Struct{
	int8	max_charges;	//Max stack or charges. (Confirmed Sp0tter).
	int8	stack_size;		//Current stack size or current charges.
	int8	has_effect;		// 1 for has effect?  (not sure)
	int16	click_effect;	//ID of click effect.	(Confirmed Sp0tter).
	int8	unknown[5];
};

struct Object_Struct {
		int8	unknown001[8];
		int32	itemid;	//maybe
		int32	dropid;	//this id will be used, if someone clicks on this object
		uint8	unknown014[128];		// ***Placeholder
		float	ypos;
		float	xpos;
		float	zpos;					// Z Position
		char	idFile[16];				// ACTOR ID
		int16	heading;
		char	objectname[16];
		int16	itemsinbag[10]; //if you drop a bag, thats where the items are
		int8	unknowneos[14];
};
struct ClickObject_Struct {
	int32	objectID;
	int16	PlayerID;
	int16	unknown;
};
struct ClickObjectAck_Struct {
/*00*/	uint32	player_id;		// Comment: Entity Id of player who clicked object
/*04*/	int8	unknown[4];		// Comment: Unknown 
/*08*/	int8	open;			// Comment: 0=close 1=open
/*09*/	int8	unknown6;		// Comment: Unknown 
/*10*/	int8	type;			// Comment: number that determines the type of the item (i.e forge) 
/*11*/	int8	unknown8;		// Comment: Unknown 
/*12*/	int8	slot;			// Comment: number of slots of the container
/*13*/  int8	unknown10[3];	// Comment: Unknown 
/*14*/	int16	icon_nr;		// Comment: Icon of the item
/*16*/	int8	unknown16[4];	// Comment: Unknown
};

/*
** Drop Coins
** Length: 112 Bytes
** OpCode: 0720
*/
struct DropCoins_Struct
{
/*0000*/ int8	unknown0002[8];		    // Comment: Always 00's
/*0008*/ int32  platinumPieces;         // Comment: Number of PP dropped (confirmed: Yeahlight)
/*0012*/ int32  goldPieces;				// Comment: Number of GP dropped (confirmed: Yeahlight)
/*0016*/ int32  silverPieces;			// Comment: Number of SP dropped (confirmed: Yeahlight)
/*0020*/ int32  copperPieces;			// Comment: Number of CP dropped (confirmed: Yeahlight)
/*0024*/ int8	unknown0024[4];         // Comment: ***Placeholder
/*0028*/ int32	always34;				// Comment: Always 0x34
/*0032*/ int8	unknown0028[16];		// Comment: ***Placeholder
/*0048*/ int32	amount;					// Comment: Total Dropped (confirmed: Yeahlight)
/*0052*/ int16  test1;                  // Comment: ***Placeholder
/*0054*/ int16	test2;					// Comment: ***Placeholder
/*0056*/ float	yPos;					// Comment: Y Position (confirmed: Yeahlight)
/*0060*/ float	xPos;					// Comment: X Position (confirmed: Yeahlight)
/*0064*/ float	zPos;					// Comment: Z Position (confirmed: Yeahlight)
/*0068*/ uint8	unknown0070[12];		// Comment: ***Placeholder
/*0080*/ char	coinName[16];			// Comment: Texture file name; ie, PLAT_ACTORDEF (confirmed: Yeahlight)
/*0096*/ uint8	unknown0097[16];		// Comment: ***Placeholder
};

/************************************************************** 
Beg_Struct - neorab 5/24/2008 [Opcode: 0x2521  Size: 18]

This is the structure of the beg request and the return to the
client.  Using success >= 5 is the same as using success = 0.
I suspect the unknown is completely padding and nothing else,
the client certainly isn't using it for anything that I can see.
***************************************************************/
struct Beg_Struct
{
	int16	target;		// The player's target at time of beg.
	int16	begger;		// The player making the coin request.
	int8	skill;		// The player's begging skill level.
	int8	success;	// -1 = request | 0 = failure | 1 = plat | 2 = gold | 3 = silver | 4 = copper
	int16	unknown1;		// This is the time since player logged in.
	int32	unknown2;		// The number of coins.  Whatever success is set to.
	int8	unknown3[6];	// Not sure.  Maybe we'll find out one day.
};

/*
** Type:   Zone Change Request (before hand)
** Length: 70 Bytes-2 = 68 bytes 
** OpCode: a320
*/

#define ZONE_ERROR_NOMSG 0
#define ZONE_ERROR_NOTREADY -1
#define ZONE_ERROR_VALIDPC -2
#define ZONE_ERROR_STORYZONE -3
#define ZONE_ERROR_NOEXPANSION -6
#define ZONE_ERROR_NOEXPERIENCE -7

struct ZoneChange_Struct {
/*000*/	char	char_name[64];     // Character Name
/*064*/	int32	zoneID;
/*068*/ int8	unknown1[4];
/*072*/	sint8	success;		// =0 client->server, =1 server->client, -X=specific error
/*073*/	int8	unknown0073[3]; // =0 ok, =ffffff error
};

struct Attack_Struct
{
/*00*/ int32   spawn_id;		// Comment: Spawn ID
/*04*/ int8    type;			// Comment: 
/*05*/ int8    a_unknown2[7];	// Comment: ***Placeholder};
};
/*
** Battle Code
** Length: 24 Bytes
** OpCode: 5820
*/
struct Action_Struct
{
/*000*/	int32	target;			// Comment: 
/*004*/	int32	source;			// Comment: 
/*008*/	int8	type;			// Comment: 
/*009*/	int8	unknown005;		// Comment: 
/*010*/	int16	spell;			// Comment: 
/*012*/	sint32	damage;			// Comment: 
/*016*/	int8	unknown4[12];	// Comment: 
};

/************************************************************** 
Consider_Struct - neorab 9/23/2007 

OPCODE - 0x3721 

Used by the client to request consider information from server 
and by server to return consider information to client.  The 
unworthy code was never used live as far as I know.  Set it to 
anything but 0 and when the con is "green" the message is that 
the mob "would not make a worthy opponent."  When the con is 
"yellow" the little message is removed completely.  The two 
before it are padding that I think is used for sending data to 
the server, but we don't need it and we don't use it going out. 

At some point, unknown_c was level, cur_hp and max_hp.  After 
testing this many many times, I found that those three values 
make no difference.  The level for the consider is taken from 
the data in update structs and spawn_struct.  I verified that 
the HP items make no difference as well.  The two unknown_a(b) 
are padding around the player and target id.  It has been 
verified that they are not used as part of the IDs as I thought 
they were originally. 

***************************************************************/ 

struct Consider_Struct{
/*000*/ int16	playerid;               // PlayerID
/*002*/ int16	targetid;               // TargetID
/*004*/ int32	faction;                // Faction
/*008*/ int32	level;                  // Level
/*012*/ sint32	cur_hp;                  // Current Hitpoints
/*016*/ sint32	max_hp;                  // Maximum Hitpoints
/*020*/ int8	unknown3[4];
};

struct ConsentRequest_Struct
{
	char name[1];				//Comment: Name of player who consent is being given to.
};

struct ConsentResponse_Struct
{
/*0000*/ char consentee[32];        // Name of player who was consented
/*0064*/ char consenter[32];        // Name of player who consented
/*0128*/ uint8   allow;             // 00 = deny, 01 = allow
/*0129*/ char corpseZoneName[32];   // Zone where the corpse is
/*0193*/
};

//Tazadar: New working packet for NPC_Death (12/08/08)
  struct Death_Struct
{
/*000*/	int32	spawn_id;		// Comment: 
/*004*/	int32	killer_id;		// Comment: 
/*008*/	int32	corpseid;		// Comment: corpseid used for looting PC corpses ! (Tazadar)
/*012*/	int16	unknown12;		// Comment: 
/*014*/	int8	attack_skill;	// Comment: Attack skill (Confirmed by Tazadar)
/*015*/	int8	unknown15;		// Comment: 
/*016*/	int16	damage;			// Comment: Damage taken, (Confirmed by Tazadar)
/*018*/ int16	unknown18;		// Comment: 
};

/*
** Generic Spawn Update
** Length: 15 Bytes
** Used in:
**
*/
struct SpawnPositionUpdate_Struct
{
/*0000*/ int16  spawn_id;               // Id of spawn to update
/*0002*/ int8   anim_type; // ??
/*0003*/ int8	heading;                // Heading
/*0004*/ sint8  delta_heading;          // Heading Change
/*0005*/ sint16 x_pos;                  // New X position of spawn
/*0007*/ sint16 y_pos;                  // New Y position of spawn
/*0009*/ sint16 z_pos;                  // New Z position of spawn
/*0011*/ int32  delta_y:10,             // Y Velocity
                spacer1:1,              // ***Placeholder
                delta_z:10,             // Z Velocity
                spacer2:1,              // ***Placeholder
                delta_x:10;             // Z Velocity
};

/*
** Spawn Position Update
** Length: 6 Bytes + Number of Updates * 15 Bytes
** OpCode: a120
*/
struct SpawnPositionUpdates_Struct
{
/*0000*/ int32  num_updates;               // Number of SpawnUpdates
/*0004*/ struct SpawnPositionUpdate_Struct // Spawn Position Update
                     spawn_update[0];
};

/*
** Spawn HP Update
** Length: 14 Bytes
** OpCode: b220
*/
struct SpawnHPUpdate_Struct
{
/*00*/ int32  spawn_id;		// Comment: Id of spawn to update
/*04*/ sint32 cur_hp;		// Comment:  Current hp of spawn
/*08*/ sint32 max_hp;		// Comment: Maximum hp of spawn
};

/*
** Stamina
** Length: 8 Bytes
** OpCode: 5721
*/
struct Stamina_Struct 
{
/*00*/ int16 food;		// Comment: low more hungry 6000-0
/*02*/ int16 water;		// Comment: low more thirsty 6000-0
/*04*/ int16 fatigue;	// Comment: high more fatigued 0-100
};

/*
** Tazadar/Yeahlight : Resurrection struct (Corrected)
** Length: 160
** OpCode: 0x2a21
*/
struct Resurrect_Struct	
{            
	/* 000 */	int32	corpseEntityID; // Tazadar : Client do not use any bytes till 52
	/* 004 */	char	zoneName[ZONE_SHORTNAME_LENGTH]; 
	/* 020 */	char	unknown20[16]; 
	/* 036 */	float	y; 
	/* 040 */	float	x; 
	/* 044 */	float	z; 
	/* 050 */	int32	fullGMRez;
	/* 052 */	char	targetName[28]; // Tazadar : Client uses this !!! If its wrong you wont see any window
	/* 082 */   char	unknown82[8];
	/* 088 */	char	casterName[28]; // Tazadar : Caster name (Confirmed)
	/* 118 */   int32	unknown118;
	/* 120 */	int16	spellID; // Tazadar : ID of the spell (Confirmed)
	/* 122 */	char	corpseName[28];
	/* 150 */	char	unknown[6];
	/* 156 */	int32	action; // Tazadar : Action => player clicked yes = 1 or no = 0 (Confirmed)
};

/*
** Tazadar : Sacrifice struct 
** Length: 12
** OpCode: 0xea21
*/
struct Sacrifice_Struct{
	/* 000 */	int32 casterID;	// Tazadar : Caster who sends the request (Confirmed)
	/* 004 */	int32 targetID; // Tazadar : Player who recieves the request (Confirmed)
	/* 008 */	int32 action; // Tazadar : Action => player clicked yes = 1 or no = 0 (Confirmed)
};

/*
** Special Message
** Length: 6 Bytes + Variable Text Length
** OpCode: 8021
*/
struct SpecialMesg_Struct
{
/*0000*/ int32 msg_type;		// Comment: Type of message
/*0004*/ char  message[0];		// Comment: Message, followed by four bytes?
};

/*************************************************************
LevelUpdate_Struct - neorab, SpOtter 9/29/2008

This structure is sent to the client when a character levels.
The exp portion of the struct must not be read by out version
of the client because not byte in the first 200 could be found
to make any difference.

This may be different one we start on ExpUpdate_Struct.  We
can't know for sure that somewhere the client is just being
updated over and over that the exp is some bizarre number.

TODO: Look into this issue later.

The second byte is a flag.  If not equal to zero, the client
allows the character to de-level.  If it is equal to zero, the
client does not change the level of the played char.  Weird,
but maybe they just have a check in there for hackers.

There does not appear to be a problem at this point with just
using two bytes.  When this get re-evaluated, be sure to check
and see if you can send exp and if we need to increase the
length of this struct.
--------------------------------------------------------------
00 - level
01 - can_delevel
*************************************************************/
struct LevelUpdate_Struct
{
/*00*/	int8	level;			// Comment: Target Level of character
/*01*/	int8	can_delevel;	// Comment: If zero, don't delevel (clientside)
};

/*
** Experience Update
** Length: 14 Bytes
** OpCode: 9921
*/
struct ExpUpdate_Struct
{
/*0000*/ uint32 exp;			// Comment: Current experience value
};

/*
** Generic Item structure
** Length: 244 bytes
** Used in:
**    itemShopStruct(0c20), itemReceivedPlayerStruct(5220),
**    itemPlayerStruct(6421), bookPlayerStruct(6521),
**    containerPlayerStruct(6621), summonedItemStruct(7821),
**    tradeItemStruct(df20),
*/
#define ITEM_STRUCT_SIZE 360
#define SHORT_BOOK_ITEM_STRUCT_SIZE	264
#define SHORT_CONTAINER_ITEM_STRUCT_SIZE 276
struct Item_Struct
{
/*0000*/ char      name[64];        // Name of item
/*0064*/ char      lore[80];        // Lore text
/*0144*/ char      idfile[6];       // Not sure what this is used for
/*0150*/ sint16    flag;
/*0152*/ uint8	   unknown0150[22]; // Placeholder
/*0174*/ uint8	   weight;          // Weight of item
/*0175*/ sint8     norent;          // Nosave flag 1=normal, 0=nosave, -1=spell?
/*0176*/ sint8     nodrop;          // Nodrop flag 1=normal, 0=nodrop, -1=??
/*0177*/ uint8     size;            // Size of item
/*0178*/ int8      type;
/*0179*/ uint8     unknown0178;     // ***Placeholder
/*0180*/ uint16    item_nr;         // Unique Item number
/*0182*/ uint16    icon_nr;         // Icon Number
/*0184*/ sint16    equipSlot;       // Current Equip slot
/*0186*/ uint8     unknwn0186[2];   // Equip slot cont.?
/*0188*/ uint32    equipableSlots;  // Slots where this item goes
/*0192*/ sint32    cost;            // Item cost in copper
/*0196*/ uint8     unknown0196[32]; // ***Placeholder
union
{
	struct
	{
	// 0228- have different meanings depending on flags
	/*0228*/ sint8    STR;              // Strength
	/*0229*/ sint8    STA;              // Stamina
	/*0230*/ sint8    CHA;              // Charisma
	/*0231*/ sint8    DEX;              // Dexterity
	/*0232*/ sint8    INT;              // Intelligence
	/*0233*/ sint8    AGI;              // Agility
	/*0234*/ sint8    WIS;              // Wisdom
	/*0235*/ sint8    MR;               // Magic Resistance
	/*0236*/ sint8    FR;               // Fire Resistance
	/*0237*/ sint8    CR;               // Cold Resistance
	/*0238*/ sint8    DR;               // Disease Resistance
	/*0239*/ sint8    PR;               // Poison Resistance
	/*0240*/ uint16   HP;               // Hitpoints
	/*0242*/ uint16   MANA;             // Mana
	/*0244*/ uint16   AC;               // Armor Class
	/*0246*/ uint8    MaxCharges;       // Maximum number of charges, for rechargable? (Sept 25, 2002)
	/*0247*/ sint8    GMFlag;           // GM flag 0  - normal item, -1 - gm item (Sept 25, 2002)
	/*0248*/ uint8    light;            // Light effect of this item
	/*0249*/ uint8    delay;            // Weapon Delay
	/*0250*/ uint8    damage;           // Weapon Damage
	/*0251*/ sint8    clicktype;      // 0=combat, 1=click anywhere w/o class check, 2=latent/worn, 3=click anywhere EXPENDABLE, 4=click worn, 5=click anywhere w/ class check, -1=no effect
	/*0252*/ uint8    range;            // Range of weapon
	/*0253*/ uint8    itemType;            // Skill of this weapon, refer to weaponskill chart
	/*0254*/ sint8    magic;            // Magic flag
                        //   00  (0000)  =   ???
                        //   01  (0001)  =  magic
                        //   12  (1100)  =   ???
                        //   14  (1110)  =   ???
                        //   15  (1111)  =   ???
	/*0255*/ sint8    clicklevel2;           // Casting level
	/*0256*/ uint8    material;         // Material?
	/*0257*/ uint8    unknown0258[3];   // ***Placeholder
	/*0260*/ uint32   color;            // Amounts of RGB in original color
	/*0264*/ uint8    unknown0264[2];   // ***Placeholder (Asiel: Has to do with Diety, will unwrap later)
	/*0266*/ uint16   spell_effect_id;         // SpellID of special effect
	/*0268*/ uint16   classes;          // Classes that can use this item
	/*0270*/ uint8    unknown0270[2];   // ***Placeholder
	union
	{
		struct
		{
		/*0272*/ uint16   races;            // Races that can use this item
		/*0274*/ sint8    unknown0274[2];   // ***Placeholder
		/*0276*/ sint8    stackable;        //  1= stackable, 3 = normal, 0 = ? (not stackable)
		} normal;
	};
	/*0277*/ uint8    level;            // Casting level
	union // 0278 has different meanings depending on an stackable
	{
    /*0278*/ sint8    number;          // Number of items in stack
    /*0278*/ sint8    charges;         // Number of charges (-1 = unlimited)
	};
	/*0279*/ sint8    effecttype;      // 0=combat, 1=click anywhere w/o class check, 2=latent/worn, 3=click anywhere EXPENDABLE, 4=click worn, 5=click anywhere w/ class check, -1=no effect
	/*0280*/ uint16   click_effect_id;         // spellId of special effect
	/*0282*/ uint8    unknown0282[10]; // ***Placeholder 0288
	/*0292*/ uint32   casttime;        // Cast time of clicky item in miliseconds
	/*0296*/ uint8    unknown0296[16]; // ***Placeholder
	/*0312*/ uint16   skillModPercent; // Skill mod value in % (Sept 25, 2002)
	/*0314*/ sint16   skillModId;      // Skill mod index (Sept 25, 2002)
	/*0316*/ uint8    unknown0315[44]; // Bane and Elemental dmg struct (writing it now, hopefully will be up soon)
	} common;
	struct // Book Structure (flag == 0x7669)
	{
    /*0228*/ sint8    unknown0172[6];      // ***Placeholder
    /*0234*/ char     file[15];            // Filename of book text on server
    /*0249*/ sint8    unknown0190[15];    // ***Placeholder
	} book;
	struct // containers flag == 0x5400 or 0x5450
	{
		/*0228*/ sint8    unknown0212[41];     // ***Placeholder
		/*0269*/ uint8    BagSlots;        // number of slots in container
		/*0270*/ sint8    unknown0214;     // ***Placeholder
		/*0271*/ sint8    BagSize;    // Maximum size item container can hold
		/*0272*/ uint8    weightReduction; // % weight reduction of container
		/*0273*/ uint8    unknown0273[3];     // ***Placeholder
		} container;
};
};

struct BulkedItem_Struct {
/*000*/	int16		opcode;
/*002*/	Item_Struct	item;
};

/*
** Summoned Item - Player Made Item?
** Length: 244 Bytes
** OpCode: 7821
*/
struct SummonedItem_Struct
{
/*0000*/ struct Item_Struct item;        // Comment: Refer to itemStruct for members
};

/*
** Summoned Item waiting.
** Length: 3 Bytes
** 
*/
struct SummonedItemWaiting_Struct
{
/*0000*/ int16 itemID;
/*0002*/ int8  charge;
};

enum CONSUMETYPE : int8
{
	CONSUMEFOOD = 0x01,						// Comment: Food
	CONSUMEDRINK = 0x02						// Comment: Drink
};

enum HOWCONSUMEDTYPE: int32
{
	AUTO = 0xffffffff,				// Comment: Auto Consumed by the client as food/drink is needed
	RIGHTCLICKED = 222				// Comment: User has right clicked on food/drink to force eating/drinking
};

struct Consume_Struct
{
/*0000*/ int32 slot;						// Comment: slot the food/drink is being consumed from
/*0004*/ HOWCONSUMEDTYPE auto_consumed;		// Comment: 
/*0008*/ int8  c_unknown1[4];				// Comment: 
/*0012*/ CONSUMETYPE  Type;				// Comment: 
/*0013*/ int8  unknown13[3];				// Comment: 
};

struct MoveItem_Struct
{
/*0000*/ uint32 from_slot;				// Comment: 
/*0004*/ uint32 to_slot;				// Comment: 
/*0008*/ uint32 number_in_stack;		// Comment: 
};

struct MoveCoin_Struct
{
/*0000*/ uint32 from_slot;			// Comment: 
/*0004*/ uint32 to_slot;			// Comment: 
/*0008*/ uint32 cointype1;			// Comment: 
/*0012*/ uint32 cointype2;			// Comment: 
/*0016*/ uint32 amount;				// Comment: 
};

struct Split_Struct
{
	uint32	platinum;
	uint32	gold;
	uint32	silver;
	uint32	copper;
};

/* Sp0tter - fixed the surname struct.
There are some more letters received in the unknown
range that still need to be identified, but as is
players can set thier surname and it saves it to the
database. Currently, it still sends a message to client
saying the name was not valid, but the client does recognize
the name.*/
struct Surname_Struct
{
	char name[16];				// Comment: Player's first name
	int8 s_unknown1[20];		// Comment: Tazadar put 1 in this in order to accept the surname  ^^
	char Surname[PC_SURNAME_MAX_LENGTH];			// Comment: Player's Surname (max size 20 limited by client)
};

/*
** Money Loot
** Length: 22 Bytes
** OpCode: 5020
*/
struct MoneyOnCorpse_Struct
{
/*0000*/ uint8	response;		// Comment: 0 = someone else is, 1 = OK, 2 = not at this time
/*0001*/ uint8	unknown1;		// Comment: = 0x5a
/*0002*/ uint8	unknown2;		// Comment: = 0x40
/*0003*/ uint8	unknown3;		// Comment: = 0
/*0004*/ uint32	platinum;		// Comment: Platinum Pieces
/*0008*/ uint32	gold;			// Comment: Gold Pieces
/*0012*/ uint32	silver;			// Comment: Silver Pieces
/*0016*/ uint32	copper;			// Comment: Copper Pieces
};

// size 292
struct ItemOnCorpse_Struct 
{
  Item_Struct item;				// Comment: 
};

struct LootingItem_Struct 
{
/*000*/	int32	lootee;			// Comment: 
/*002*/	int32	looter;			// Comment: 
/*004*/	int16	slot_id;		// Comment: 
/*006*/	int8	unknown3[2];	// Comment: 
/*008*/	int32	type;			// Comment: 
};


// Size = 84 bytes
struct GMZoneRequest_Struct {
	char	charname[64];
	int32	zoneID;
	int8	unknown1[16];
	int8	success; // 0 if command failed, 1 if succeeded?
	int8	unknown2[3]; // 0x00
};

struct GMSummon_Struct {
/*  0*/	char    charname[64];
/* 30*/	char    gmname[64];
/* 60*/ int32	success;
/* 61*/	int32	zoneID;
#ifndef INVERSEXY
/*92*/	sint32  x;
/*96*/	sint32  y;
#else
	sint32 y;
	sint32 x;
#endif
/*100*/ sint32  z;
/*104*/	int8 unknown2[4]; // E0 E0 56 00
};

struct GMGoto_Struct { // x,y is swapped as compared to summon and makes sense as own packet
/*  0*/	char    charname[64];
/* 30*/	char    gmname[64];
/* 60*/ int32	success;
/* 61*/	int32	zoneID;

/*92*/	sint32  x;
/*96*/	sint32  y;
/*100*/ sint32  z;
/*104*/	int32 unknown2; // E0 E0 56 00
};

/*struct GMGoto_Struct 
{
	char	gotoname[30];		// Comment: 
	char	myname[30];			// Comment: 
	int8	unknown[48];		// Comment: 
};*/

struct GMSurname_Struct 
{
	char name[PC_MAX_NAME_LENGTH];			// Comment: 
	char gmname[PC_MAX_NAME_LENGTH];		// Comment: 
	char Surname[32];		// Comment: 
	int8 unknown[2];		// Comment: 0x00, 0x00, 0x01, 0x00 = Update the clients
};

//Dueling
struct Duel_Struct
{
int32 duel_initiator;
int32 duel_target;
};

struct DuelResponse_Struct
{
int32 target_id;
int32 entity_id;
int8 response[2];
};

//Combat Abilities
struct CombatAbility_Struct
{
	int32 m_id;			// Comment: 
	int32 m_atk;		// Comment: 
	int32 m_type;		// Comment: 
};

//Instill Doubt
struct Instill_Doubt_Struct 
{
	int8 i_id;			// Comment: 
	int8 ia_unknown;	// Comment: 
	int8 ib_unknown;	// Comment: 
	int8 ic_unknown;	// Comment: 
	int8 i_atk;			// Comment: 
	int8 id_unknown;	// Comment: 
	int8 ie_unknown;	// Comment: 
	int8 if_unknown;	// Comment: 
	int8 i_type;		// Comment: 
	int8 ig_unknown;	// Comment: 
	int8 ih_unknown;	// Comment: 
	int8 ii_unknown;	// Comment: 
};

//Pick Pockets struct verified by Wizzel
struct PickPockets_Struct {
// Size 18
    uint16 to;
    uint16 from;
    uint8 myskill;
    uint8 unknown0;
    uint8 type; // -1 you are being picked, 0 failed , 1 = plat, 2 = gold, 3 = silver, 4 = copper, 5 = item
    uint8 unknown1; // 0 for response, unknown for input
    uint32 coin;
    uint8 lastsix[6];
};

// This is only being used for fishing right now,
// but i think it gets used for more abilities (Sp0tter). That would make sense (Dark-Prince)
struct UseAbility_Struct 
{
	int16 player_id;	// Comment: Entity ID
	int8  unkown[10];	// Comment: Only two of these bytesever have values.  Guessing lore and skill.
};



struct GiveItem_Struct 
{
	uint16 to_entity;		// Comment: 
	sint16 to_equipSlot;	// Comment: 
	uint16 from_entity;		// Comment: 
	sint16 from_equipSlot;	// Comment: 
};


struct CancelTrade_Struct { 
	int16 fromid;
	int16 action;
	int8 unknown1337[4];
};


struct Random_Struct 
{
	int32 low;		// Comment: 
	int32 high;		// Comment: 
};

//Yeahlight: Old LFG_Struct (DO NOT DELETE)
//struct LFG_Struct 
//{
//	char	name[PC_MAX_NAME_LENGTH];	// Comment: 
//	int32	value;		// Comment: 
//};

//Yeahligth: New LFG_Struct
struct LFG_Struct 
{
	char	name[PC_MAX_NAME_LENGTH + 2];	// Comment: 
	int32	value;		// Comment: 
};

// EverQuest Time Information:
// 72 minutes per EQ Day
// 3 minutes per EQ Hour
// 6 seconds per EQ Tick (2 minutes EQ Time)
// 3 seconds per EQ Minute
struct TimeOfDay_Struct 
{
	int8	hour;			// Comment: 
	int8	minute;			// Comment: 
	int8	day;			// Comment: 
	int8	month;			// Comment: 
	int16	year;			// Comment: Kibanu - Changed from long to int16 on 7/30/2009
};

struct Merchant_Click_Struct {
/*000*/ int16	entityid;			// Merchant NPC's entity id
/*002*/ int16	playerid;
/*004*/ int8	unknown[8]; /*
0 is e7 from 01 to // MAYBE SLOT IN PURCHASE
1 is 03
2 is 00
3 is 00
4 is ??
5 is ??
6 is 00 from a0 to
7 is 00 from 3f to */
/*
0 is F6 to 01
1 is CE CE
4A 4A
00 00
00 E0
00 CB
00 90
00 3F
*/
};			
struct Merchant_Purchase_Struct {
/*000*/	int16	npcid;			// Merchant NPC's entity id
/*002*/	int16	playerid;		// Player's entity id
/*004*/	int16	itemslot;
/*006*/	int8	IsSold;		// Already sold
/*007*/	int8	unknown001;	// always 0x0b, 0x7c, 0x00 ??
//		int8	unknown002;  On live, it looks like it is only 16 bytes now and quanity is put at byte 9 (Hogie on 12/29/2002)
/*008*/	int8	quantity;		// Qty - when used in Merchant_Purchase_Struct
/*009*/	int8	unknown003;
/*010*/	int8	unknown004;
/*011*/	int8	unknown005;
/*012*/	sint32  itemcost;
};

struct Item_Shop_Struct {
	uint16 merchantid;
	int8 itemtype;
	Item_Struct item;
	int8 iss_unknown001[6];
};

struct Merchant_DelItem_Struct{
/*000*/	int32	npcid;			// Merchant NPC's entity id
/*004*/	int32	playerid;		// Player's entity id
/*008*/	int8	itemslot;       // Slot of the item you want to remove
/*009*/	int8	unknown[3];
};

 struct ItemToTrade_Struct { 
/*000*/	uint32 playerid;
/*004*/	int16 to_slot;
/*006*/	int8 unknown_1;
/*007*/	Item_Struct item;
	    int8  unknown02[3];
};

// 4-20-08 (Wizzel)
// Received when a client uses an illusion related action.
// Size: 72 Bytes
// OpCode: 9120
// Notes: Fucking finally... ;p
struct Illusion_Struct 
{ 
/*0000*/ char   name[16];
/*0016*/ int8	unknown1[4]; // usually 00 00 00 00
/*0020*/ int8	unknown2[4]; // dictated by packet, maybe zone but got 00 00 00 00 in grobb
/*0024*/ int8	unknown3[4];
/*0028*/ int8	unknown4[2];
/*0030*/ char	target[16];
/*0046*/ int8	unknown5[2];
/*0048*/ int16	jackbauer; //always 24
/*0050*/ int16	unknown7;
/*0052*/ int16  unknown8;
/*0054*/ int16	unknown9; //00 00
/*0056*/ int8	unknown10[4];
/*0060*/ int8	unknown11[2];
/*0062*/ int16	race; // 01 = human 02 = barbarian, etc
/*0064*/ int16	gender; // 00 = male 01 = female 02 = neuter, 02 is default if nothing is entered.
/*0066*/ int16	texture; // 00 = cloth 01 = leather FF = default
/*0068*/ int16	helm; // 00 = cloth 01 = leather FF = default
/*0070*/ int16	face; // 00 = cloth 01 = leather FF = default
};

struct CPlayerItems_packet_Struct 
{
/*000*/	int16		opcode;		// Comment: OP_ItemTradeIn
/*002*/	Item_Struct	item;		// Comment: 
};

struct CPlayerItems_Struct 
{
/*000*/	int16		count;							// Comment: 
/*002*/	CPlayerItems_packet_Struct	packets[0];		// Comment: 
};

//By Scruffy... Thanks ShowEQ and sins!
struct SkillUpdate_Struct 
{
	uint8 skillId;			// Comment: 
	int8 unknown1[3];		// Comment: 
	uint8 value;			// Comment: 
	int8 unknown2[3];		// Comment: 
};

struct ZoneUnavail_Struct 
{
	//This actually varies, but...
	char zonename[ZONE_SHORTNAME_LENGTH];		// Comment: 
	short int unknown[4];	// Comment: 
};

struct GroupInvite_Struct 
{
	char invited[PC_MAX_NAME_LENGTH];		// Comment: 
	char inviter[PC_MAX_NAME_LENGTH];		// Comment: 
	char unknown[31];		// Comment: 
};


/* Do not touch this please.  Used to add and 
 * remove group members from a group. Maybe more.*/
struct GroupUpdate_Struct
{
	char	receiverName[32];	//Member who needs new info;
	char	senderName[32];		//Member with new info;
	char	senderName2[32];	//? testing, but not working yet
	int8	unknown01[128];		
	int8	action;				//0: Player joins the group;		
								//1: ??
								//2: ??
								//3: Player leaves the group;	
								//4: You leave the group;		
};

struct GroupFollow_Struct
{
	char leader[PC_MAX_NAME_LENGTH];		// Comment: 
	char invited[PC_MAX_NAME_LENGTH];		// Comment: 
};

/* Sent when player clicks disband after receiving an invite 
 * or if a player is already grouped and gets an invite it 
 * is sent automaticaly. */
struct GroupInviteDecline_Struct{
	char leader[PC_MAX_NAME_LENGTH];		//Player1 who invited another Player2;
	char leaver[PC_MAX_NAME_LENGTH];		//Player2 who is declining/unable to accept invite from Player1;
	int8 action;			//Type of decline:
							//	1: 'leaver' is considering another group invite;
							//	2: 'leaver' already grouped;
							//	3: 'leaver' rejects your offer to join the group;
};

struct GroupDisband_Struct 
{
	char member[15];		// Comment: 
	char unknown1[41];		// Comment: 
	int8 framecounter;		// A frame counter that increments by 32 each time same client sends this code;
 	char unknown2[3];
};

struct ChangeLooks_Struct 
{
/*000*/	int8	haircolor;	// Comment: 
/*001*/	int8	beardcolor;	// Comment: 
/*002*/	int8	eyecolor1;	// Comment: the eyecolors always seem to be the same, maybe left and right eye?
/*003*/	int8	eyecolor2;	// Comment: 
/*004*/	int8	hairstyle;	// Comment: 
/*005*/	int8	wode;		// Comment: Face Overlay? (barbarian only)
/*006*/	int8	face;		// Comment: and beard
};

struct Trade_Window_Struct 
{
	int32 fromid;			// Comment: 
	int32 toid;				// Comment: 
};

struct TradeMoneyUpdate_Struct{
	int32	trader;			// Comment: 
	int32	type;		 // Comment: 
	int32	amount;			// Comment: 
};

struct TradeCoin_Struct{
	int32	trader;		// Comment: 
	int8	slot;		// Comment: 
	int16	unknown5;		// Comment: 
	int8	unknown7;		// Comment: 
	int32	amount;			// Comment: 
	int8	unknown8[10];	// Comment:
};

struct Give_Struct 
{
	int16 unknown[2];		// Comment: 
};

struct PetitionClientUpdate_Struct 
{
	int32 petnumber;		// Comment: Petition Number
	int32 color;			// Comment: 0x00 = green, 0x01 = yellow, 0x02 = red
	int32 senttime;			// Comment: 
	int8 unknown[4];		// Comment: 4 has to be 0x1F
	char accountid[32];		// Comment: 
	char gmsenttoo[32];		// Comment: 
	int32 something;		// Comment: 
	char charname[PC_MAX_NAME_LENGTH];		// Comment: 
};

struct Petition_Struct 
{
	int32 petnumber;			// Comment: 
	int32 urgency;				// Comment: 
	char accountid[32];			// Comment: 
	char lastgm[32];			// Comment: 
	char zone[32];				// Comment: 
	char charname[PC_MAX_NAME_LENGTH];			// Comment: 
	int32 charlevel;			// Comment: 
	int32 charclass;			// Comment: 
	int32 charrace;				// Comment: 
	time_t senttime;			// Comment: Time?
	int32 checkouts;			// Comment: 
	int32 unavail;				// Comment: 
	int8 unknown5[4];			// Comment: 
	char petitiontext[1024];	// Comment: 
};

/* 
	Bug_Report tested by Sp0tter.  It is currently linked to the database 'bug_report'
	table.  I've added the table to the /create fold in the database dir
	so just source that and any bug reporting will go straight to the database.
	It still needs sql injection handling.
*/
struct Bug_Report_Struct
{
	char playername[72];		// Comment: Players name
	uint8 blankspot1;			// Comment: not used
	uint8 cannotuplicate;		// Comment: 1 for cannot duplicate, 0 for can duplicate
	uint8 noncrashbug;			// Comment: 1 for does NOT crash, 0 for does cause crash
	char bugdescription[1024];	// Comment: The bug description
};

// Comment: 76 length in total
struct Who_All_Struct 
{
	char whom[32];		// Comment: 
	int16 wrace;		// Comment: FF FF = no race
	int16 wclass;		// Comment: FF FF = no class
	int16 firstlvl;		// Comment: FF FF = no numbers
	int16 secondlvl;	// Comment: FF FF = no numbers
	int16 gmlookup;		// Comment: FF FF = not doing /who all gm
	int8 unknown[34];	// Comment: 

};

// Comment: 4 bytes in total
struct Stun_Struct 
{
	int32 duration;		// Comment: Duration of stun
};

// Size: 32 Bytes
struct Combine_Struct 
{ 
	int8 worldobjecttype;	// Comment: Harakiri if its a world object like forge, id will be here
	int8 unknown001;		// Comment: 
	int8 unknown002;		// Comment: 
	int8 unknown003;
	int16 containerslot;	// Comment: the position of the container, or 1000 if its a world container	
	int16 iteminslot[10];	// Comment: IDs of items in container
	int16 unknown005;		// Comment: 
	int16 unknown006;		// Comment: 
	int16 containerID;		// Comment: ID of container item
};

struct Emote_Text
{
	int16 unknown1;			// Comment: 
	char message[1024];		// Comment: 
};


struct Social_Action_Struct 
{
	int8 unknown1[4];	// Comment: 
	int8 action;		// Comment: 
	int8 unknown2[7];	// Comment: 
};

//Size: 8  (Request)
struct InspectRequest_Struct 
{ 
	int32 TargetID;		// Comment: 
	int32 PlayerID;		// Comment: 
}; 

//Size: 1044 (Answer)
struct InspectAnswer_Struct 
{ 
	int32 TargetID;			// Comment: ? 
	int32 PlayerID;			// Comment: ?
	int8  unknown[1036];	// Comment: ?
}; 


struct SetDataRate_Struct 
{
	float newdatarate;	// Comment: 
};


struct SetServerFilter_Struct 
{
	int8 unknown[60];	// Comment: 
};

struct SetServerFilterAck_Struct 
{
	int8 blank[8];		// Comment: 
};

struct GMName_Struct 
{
	char oldname[PC_MAX_NAME_LENGTH];	// Comment: 
	char gmname[PC_MAX_NAME_LENGTH];	// Comment: 
	char newname[PC_MAX_NAME_LENGTH];	// Comment: 
	int8 badname;		// Comment: 
	int8 unknown[3];	// Comment: 
};

struct GMDelCorpse_Struct 
{
	char corpsename[PC_MAX_NAME_LENGTH];	// Comment: 
	char gmname[PC_MAX_NAME_LENGTH];		// Comment: 
	int8 unknown;			// Comment: 
};

struct GMKick_Struct 
{
	char name[PC_MAX_NAME_LENGTH];		// Comment: 
	char gmname[PC_MAX_NAME_LENGTH];	// Comment: 
	int8 unknown;		// Comment: 
};

struct GMKill_Struct 
{
	char name[PC_MAX_NAME_LENGTH];		// Comment: 
	char gmname[PC_MAX_NAME_LENGTH];	// Comment: 
	int8 unknown;		// Comment: 
};

struct GMEmoteZone_Struct 
{
	char text[512];		// Comment: 
};

// This is where the Text is sent to the client.
// Use ` as a newline character in the text.
// Variable length.
struct BookText_Struct 
{
	char* booktext;		// Comment: Variable Length
};

// This is the request to read a book.
// This is just a "text file" on the server
// or in our case, the 'name' column in our books table.
struct BookRequest_Struct 
{
	char txtfile[14]; // Comment: 
};

// 6-01-08 - Wizzel
// Recieved when player right clicks on guildmaster of his/her own guild
// Size: 148 Bytes
// OpCode: 9c20

struct ClassTrain_Struct{
	/*000*/ int32 npcid;
	/*002*/ int32 playerid;
	/*004*/ int8  highesttrain[73];
	        int8	unknown[32];
			int8	highesttrainLang[24];
	/*004*/ int8 unknown2[107];
};

struct ClassSkillChange_Struct {
/*000*/	int32	npcid;
/*004*/ int32	skill_type;	// 0=regular skills, 1=languages (Harakiri)
/*008*/ int32	skill_id;		// Skill trained
};



// Harakiri Struct for Clients Request to Show specific message board
struct MBRetrieveMessages_Struct{
	int8 entityID;
	int8 unknown[3];
	int8 category; // category is the type of board selected by the client
	/* 00 - OFFICIAL */
	/* 01 - FOR SALE */
	/* 02 - GENERAL */
	/* 03 - HELP WANTED */
	/* 04 - PERSONALS */
	/* 05 - GUILDS */
	int8 unknown2[3];
};

// Harakiri struct for deleting a specific message
struct MBEraseMessage_Struct{
/*0000*/ int32 entityID;	
/*0004*/ uint32 id; /* id of the message	
/*0008*/ int8 category;
/*0009*/ int8 unknown3[3];
}; 

// Harakiri struct for retrieving a specific message
struct MBRetrieveMessage_Struct{
/*0000*/ int32 entityID;	
/*0004*/ uint32 id; /* id of the message	
/*0008*/ int8 category;
/*0009*/ int8 unknown3[3];
}; 


// Harakiri Struct for of a message
struct MBMessage_Struct{		
/*0000*/ uint32 id; 
/*0004*/ char date[10]; /* char year[2]; char month[2]; char day[2];
/*0014*/ int8 unknown2[6];
/*0020*/ char author[PC_MAX_NAME_LENGTH];
/*0050*/ int8 unknown3[2];
/*0052*/ int8 language;
/*0053*/ int8 unknown4;
/*0054*/ char subject[29];
/*0083*/ int8 unknown5[3];
/*0086*/ int8 category;
/*0087*/ int8 unknown6;
/*0088*/ char message[2048]; // see eqgame function at .text:0047D4E5
}; 


// Harakiri Filter Types for Message Board
enum MESSAGEBOARD_CATEGORY
{
	OFFICIAL, 
	FOR_SALE, 
	GENERAL, 
	HELP_WANTED,
	PERSONALS, 
	GUILDS 
};


//Yeahlight: TODO: This struct will obviously not work when we get into sending bulk door spawns
struct Door_Struct{
/*0000*/ char    name[16];      // Filename of Door
/*0016*/ float   yPos;          // y loc
/*0020*/ float   xPos;          // x loc
/*0024*/ float   zPos;          // z loc
/*0028*/ float	 heading;		// y rotation (verified by Sp0tter).
/*0032*/ float	 incline;		// x rotation (verified by Sp0tter).
/*0036*/ float	 padding;
/*0038*/ uint8   doorid;
/*0039*/ uint8	 opentype;      //Opentype (verified by Wizzel)
/*0040*/ uint8	 doorIsOpen;    //Yeahlight: Door is open
/*0041*/ uint8	 inverted;	    //Yeahlight: Door starts at inverted state. This flags needs to be ON for traps to animate and has other odd effects on other types of doors.
/*0042*/ int16	 parameter;     //Yeahlight: Specific distance door (most likely a lift/button) will travel
/*0044*/ int8	 unknown0044;
/*0045*/ int8    auto_return;
/*0046*/ int8	 unknown0046;
/*????*/ //Yeahlight: I could not find the correct locations in the struct for the below variables, which probably means they are safe here:
/*0047*/ uint8	 triggerID;     //Yeahlight: ID of door this "door" triggers (0 means no doors triggered)
		 uint8	 lockpick;		//Yeahlight: Skill required to pick this lock (0 means no lock on door or door is unpickable if a key exists [below])
		 int16	 keyRequired;	//Yeahlight: Key required to open the lock, item ID #
		 char	 zoneName[16];  //Yeahlight: Destination zone name for clickies ("NONE" is default)
		 float	 destX;			//Yeahlight: Destination coordinates (x,y,z,heading)
		 float	 destY;
		 float	 destZ;
		 float   destHeading;
		 int32	 pLastClick;
		 uint8	 triggerType;

/******Useful Open Types*******/
//53: Spell Particle Effect
//55: Bulletin Board
/******************************/

/****Yeahlight: OpenType '53' accompanied by the 'inverted' flag results in a static spell effect, which are listed below:
1:   Healing orb (blue sphere)
2:   Buff aura (lots of color moving towards the center)
3:   Rain of fire (Orange flames)
4:   Summon item (green cone)
5:   Vision buff (White small effects)
6:   Healing cone (blue cone)
7:   Misc buff (blue particles spreading from center)
8:   Misc buff (large orange explosions)
9:   Invis/Gate (blue/white balls)
10:  Poison debuff (Large green balls and small green balls)
11:  ?? (Fast moving gold balls and a gold ball aura)
12:  Dispell (Slow moving blue balls and blue sphere)
13:  ?? (Fast moving orange balls on 2 planes, moving from center)
14:  Bind (Very slow moving blue balls and blue sphere)
15:  Stun (Very fast moving red effects on two planes)
16:  Root (Green circles moving outward from center)
17:  ?? (Three different blue effects in static positions from center)
18:  Rain of fire (Small orange flames)
19:  Cannabalize (Blue clouds moving to center)
20:  Lifetap Cast (Green balls moving to center)
21:  ?? (Lots going on here: Sphere of blue crystals, small blue balls moving outward, big blue balls moving outward slowly)
22:  ?? (Medium size white balls moving slowly outward, almost makes a sphere)
23:  ?? (Blue crystals)
24:  Lifetap or Poison (Green balls spewing everywhere)
25:  Stun (Red sphere and red balls moving outward
26:  ?? (Small blue balls rising strait up and small blue balls moving away from center)
27:  ?? (Green balls raining down from center on a plane, small blue balls rising from center on a plane and yellow balls forming a sphere from center)
28:  ?? (Green circle raining green balls towards center)
29:  ?? (Small orange balls forming a ring in center with orange puffs moving to center)
30:  Healing cone (Blue healing cone flipped on axis)
31:  Fire (Fire with orange balls)
32:  ?? (Blue crystals with blue balls moving upwards from center with blue smoke moving upwards)
33:  ?? (Small teal balls raining from center with static blue buffs forming a sphere)
34:  Poison debuff (Small green balls raining down fast from center)
35:  Harvest (Many blue balls moving away in two directions from center forming large walls)
40:  ?? (Very few blue blues flashing and a blue ring)
41:  ?? (Small orange flames flickering in a sphere with a ring of orange buffs in center)
42:  ?? (Gold star forming a sphere and random gold dots moving updwards from center)
43:  ?? (Small white balls raining from center with very very small blue dots appearing randomly)
44:  ?? (A sun type effect with orange dots raining from it)
45:  ?? (A sphere a blue dots raining downwards)
46:  ?? (A sphere of green dots raining outwards)
47:  ?? (A sphere of whote dots raining outwards with small blue dots mixed in)
48:  ?? (Orange dots on a flat plane running outwards from center (disc like))
49:  Jboots (Red effects moving towards center quickly)
50:  ?? (Blue dots forming a sphere and flickering)
51:  Manastone (Green skulls forming a sphere
66:  ?? (A small pale-green sprinkler)
67:  ?? (same as above)
68:  ?? (same as above)
69:  ?? (same as above)
105: Smoke stack
110: Flame (single orange flame)
111: Flames (8ish orange flames)
112: Flames (15ish orange flames)
113: ?? (Sphere of orange flames)
114: ?? (Large sphere of orange flames)
115: Smoke stack (GIGANTIC smoke stack, can be seen for miles)
116: ?? (Pale blue sprinkler)
117: ?? (same as 116)
118: ?? (Pale blue sprinkler, little different from 116)
120: ?? (Sphere of red sparkles)
121: ?? (Sphere of orange sparkles)
122: ?? (Sphere of few blue dots)
123: ?? (Sphere of blue sparkles)
124: Sprinkler (blue sparkles rushing out of a single hole)
125: Sprinkler (orange sparkles rushing out of a single hole)
126: Sprinkler (smaller blue sparkles rushing out of a single hole)
127: Sprinkler (pale red sparkles rushing out of a single hole)
128: Water fall (Blob of steam)
129: Water fall (Steam rushing from a single hole)
130: Fire ("Realistic" fire effect)
131: Pulsing HUGE white star
132: Sprinkler (large steam puffs)
133: Water fall (same as 128)
134: Water fall (same as 129)
143: Water fall (same as 128)
144: Water fall (same as 128)
145: ?? (Blue sparkles raining down randomly)
146: ?? (Same as 145 but smaller)*/
};

struct DoorSpawns_Struct	//SEQ
{
	uint16 count;            
	struct Door_Struct doors[0];
};

struct ClickDoor_Struct {
	int8	doorid;
	int8	unknown[3];
	int16	keyinhand;
	int16	playerid;
};

struct DoorOpen_Struct {
	int8	doorid;
	int8	action;
};

struct LSAuth_Struct {
	int32	lsaccount_id;
	char	name[19];
	char	key[16];
	bool	stale;
	bool	inuse;
	bool	firstconnect;
};

// Dark-Prince 22/12/2007
// Added this struct for eqemu and started eimplimentation ProcessOP_SendLoginInfo
//TODO: confirm everything in this struct
struct LoginInfo_Struct {
/*000*/	char	AccountName[127];	// Length confirmed - Dark-Prince 22/12/2007
/*064*/	uint8	Password[24];		// Length confirmed - Dark-Prince 22/12/2007
/*189*/	uint8	unknown189[19];		//TODO: Find out wtf is this one and confirm size
/*196*/
};

// Dark-Prince 22/12/2007
// Added this struct for eqemu and started eimplimentation ProcessOP_SendLoginInfo
//TODO: confirm everything in this struct
// this packet is a variable length...cuz its based on name
struct EnterWorld_Struct {
/*000*/	char	charname[PC_MAX_NAME_LENGTH];	//TODO: Confirm length - Set to 30 for char name which is the same size as the name in playerprofile struct
};

// Dark-Prince 22/12/2007
//TODO: work on this
struct NameApproval_Struct
{
	char charname[64];
	int32 race;
	int32 class_;
	int32 deity;
};


// Harakiri
// This can be sent on multiple occasions
// i.e. player vodka or is removed when using arrows
// or we sent OP_InitiateConsume - it can even be an item in a bag
//OpCode: 4621 Size: 12 bytes
struct ConsumeItem_Struct
{
	int16 slot;			//The slot id of the item consumed
	int8 other[2];		//These are all 0x00.
	int32 filler[2];	//These are both always 0xFFFFFFFF.
};

// Dark-Prince 22/12/2007 - Added this as it appears to be different to the 
//							other Server_Motd_struct (notice case) in servertalk.
struct ServerMOTD_Struct
{
	char motd[SERVER_MOTD_LENGTH];
};

// Dark-Prince 29/01/2008 - In dev
struct ChangeWeather_Struct
{
/*000*/	uint32 type;
/*004*/	uint32 intensity;
};

// 4-20-08 (Yeahlight)
// Received when a client executes the /target command
// Size: 4 Bytes
// OpCode: fe21
struct BackSlashTarget_Struct
{
	int16  bst_target;              // Target ID
	int16  bst_unknown1;             // ***Placeholder
};

// 4-23-08 (Yeahlight)
// Received when a client executes the /assist command
// Size: 4 Bytes
// OpCode: 0022
struct BackSlashAssist_Struct
{
	int16 bsa_target;
	int16 bsa_unknown1;
};

struct Make_Pet_Struct { //Simple struct for getting pet info Tazadar 01/06/08
	int8 level;
	int8 class_;
	int16 race;
	int8 texture;
	int8 pettype;
	float size;
	int8 type;
	int32 min_dmg;
	int32 max_dmg;
    sint32  max_hp;
};


struct GuildInviteAccept_Struct {
	char inviter[30];
	char newmember[30];
	int32 rank;
	int32 guildeqid;
};

// 6-22-08 - Wizzel
// Recieved when player steps onto a boat
// Size: 30 Bytes
// OpCode: bb21
struct Boat_Struct{
	char boatname[NPC_MAX_NAME_LENGTH]; //Tazadar: Changed the lenght of the name
};

// 6-24-08 - Wizzel
// Recieved when player right clicks a pilotable boat
// Size: 8 Bytes
// OpCode: bb21
struct CommandBoat_Struct{
	int8 unknown[8];
};

//Yeahlight: Struct for pulling zoneline data from DB
struct zoneLine_Struct
{
	int16 id;
	char zone[16];
	float x;
	float y;
	float z;
	char target_zone[16];
	float target_x;
	float target_y;
	float target_z;
	int16 range;
	int8 heading;
	int16 maxZDiff;
	int8 keepX;
	int8 keepY;
	int8 keepZ;
};

// Harakiri this is the generic teleport struct
// used to teleport a player
struct TeleportPC_Struct
{
/*0000*/ char zone[16];
/*0016*/ int8 unknown2[16];			
/*0032*/ float   yPos;          // Harakiri y loc
/*0036*/ float   xPos;          // Harakiri x loc			
/*0040*/ float   zPos;          // Harakiri z loc
/*0044*/ float	 heading;		// Harakiri will be divided by 2 by the client
};

// Harakiri
// This is sent to the client for translocate requests
// This is sent back from the client to the server if the request was either confirmed or denied
struct Translocate_Struct
{
/*0000*/ char zone[16];
/*0016*/ int8 unknown[16];
/*0032*/ int16 spellID; // Harakiri: ID of the translocate spell being cast, Client will popup "..translocated to your bind point?" if it is translocate 1422 or group translocate 1334
/*0034*/ int8 unknown1[6];
/*0040*/ char caster[16];
/*0056*/ int8 unknown2[16];
/*0072*/ float y;		// Harakiri translocate to this Y pos - the client will set this in the local playerProfile to have up2date values for save client request i think
/*0076*/ float x;		// Harakiri translocate to this X pos - the client will set this in the local playerProfile to have up2date values for save client request i think
/*0080*/ float z;		// Harakiri translocate to this Z pos - the client will set this in the local playerProfile to have up2date values for save client request i think			
/*0084*/ uint32 confirmed; // Harakiri Step 1 the server sents the initial request to the client, should be 0 = Confirmation box to player
						   // Harakiri Step 2 the client will response with this struct, if confirmed it will be 1 
						   // Harakiri Step 3 the server will response with the actual translocate this time confirmed is again 1
};

//Yeahlight: 0x8c21, 8
struct BecomeNPC_Struct 
{
/*0000*/ int32 entityID;
/*0004*/ int8 attackLevel;
/*0005*/ int8 unknown[3];
};

//Yeahlight: Struct for NPC roam boxes
struct RoamBox_Struct
{
	int16 id;
	float max_x;
	float min_x;
	float max_y;
	float min_y;
};
//Tazadar : Boat Commands
enum BOATCOMMANDS
{
	CHECK_FAMILY, // Check others boats before departing
	SPAWN, // Spawn the boat
	TELEPORT_PLAYERS, // Teleport player to the other zone
	GOTO, // Move boat to node number numnode
	WAIT, // Wait at zone/dock for timeneeded
	ROTATE, // Rotate the boat
};
//Tazadar : Struct for Boats routes
struct WorldBoatCommand_Struct
{
	BOATCOMMANDS cmd;
	string zonename;
	union {
		struct 
		{
			float x;
			float y;
			float z;
			float heading;
		}position;
		struct
		{
			int32 from_node; // -1 means that we keep the old one
			int32 to_node;
			int32 timeneeded;
		}go_to;
	};

};

//Tazadar : Struct for Boats routes
struct ZoneBoatCommand_Struct
{
	BOATCOMMANDS cmd;
	float x;
	float y;
	union {
		struct 
		{
			float speed;
		}go_to;
		struct
		{
			float heading;
		}rotate;
	};

};

//Yeahlight: Struct for the zone to communicate its status with World
struct ZoneStatus_Struct
{
	int16 zoneID;
};

//Yeahlight: No idea what this is used for, but it creates a
//           perminent object that no client may interact with.
//			 It also accepts spell sprites (i.e., GENC00), but 
//			 they do not currently display. I guess we could use 
//			 this for GM events?
//
//Opcode: 0xF620
struct ObjectDisplayOnly_Struct
{
/*0000*/ char test1[32];
/*0032*/ char modelName[16];	//Yeahlight: Confirmed (Note: The filename suffix is ASSUMED. Only use the filename prefix like 'PLAT' or 'IT10')
/*0048*/ char test2[12];
/*0060*/ float size;			//Yeahlight: Confirmed
/*0064*/ float y;				//Yeahlight: Confirmed
/*0068*/ float x;				//Yeahlight: Confirmed
/*0072*/ float z;				//Yeahlight: Confirmed
/*0076*/ float heading;			//Yeahlight: Confirmed
/*0080*/ float tilt;			//Yeahlight: Confirmed
/*0084*/ char test4[40];
};

//Yeahlight: Size: 116 (0x74u)
//           OpCode: 0x4520
struct SpawnProjectile_Struct
{
/*0000*/ int32 always1;				// Comment: Yeahlight: ASM claims that this member should always be a value of 1
/*0004*/ int32 always0;				// Comment: Yeahlight: ASM claims that this member should always be a value of 0
/*0008*/ int32 test1;				// Comment: Yeahlight: Unknown (ASM claims that this member is defined by the client and size int32)
/*0012*/ float y;					// Comment: Yeahlight: Object's y coordinate (Verified to be float)
/*0016*/ float x;					// Comment: Yeahlight: Object's x coordinate (Verified to be float)
/*0020*/ float z;					// Comment: Yeahlight: Object's z coordinate (Verified to be float)
/*0024*/ float heading;				// Comment: Yeahlight: Object's heading (Verified to be float)
/*0028*/ float tilt;				// Comment: Yeahlight: Object's tilt (Verified to be float)
/*0032*/ float velocity;			// Comment: Yeahlight: Object's velocity (Verified to be float)
/*0036*/ float burstVelocity;		// Comment: Yeahlight: Incremental velocity on the object during its first second of travel (Verified to be float)
/*0040*/ float burstHorizontal;		// Comment: Yeahlight: Shoves the object along the horizontal plane during its first second of travel (Verified to be float)
/*0044*/ float burstVertical;		// Comment: Yeahlight: Shoves the object along the vertical plane during its first second of travel (Verified to be float)
/*0048*/ float yaw;					// Comment: Yeahlight: Rotation around the z-axis (Verified to be float)
/*0052*/ float pitch;				// Comment: Yeahlight: Rotation around the x-axis (Verified to be float)
/*0056*/ float arc;					// Comment: Yeahlight: Applies a gravitational arc on the object (Verified to be float)
/*0060*/ int8 test5[4];				// Comment: Yeahlight: Unknown (ASM claims that this member is defined by the client)
/*0064*/ int32 sourceID;			// Comment: Yeahlight: Entity ID of the projectile's inflictor (Verified to be int32)
/*0068*/ int32 targetID;			// Comment: Yeahlight: Entity ID of the projectile's inflictee (Verified to be int32)
/*0072*/ int16 test6;				// Comment: Yeahlight: Unknown (ASM claims that this member is defined by the client and size int16)
/*0074*/ int16 test7;				// Comment: Yeahlight: Unknown (ASM claims that this member is defined by the client and size int16)
/*0076*/ int32 spellID;				// Comment: Yeahlight: Spell ID of the projectile (ASM claims int32)
/*0080*/ int8 lightSource;			// Comment: Yeahlight: Light source on the object (ASM claims int8)
/*0081*/ int8 test9;				// Comment: Yeahlight: Unknown (ASM claims int8)
/*0082*/ int8 spawnBehavior;		// Comment: Yeahlight: Boolean flag to enable the attack animation and spawn of the arrow projectile (See 0x11/0x1B below)
									//                     OR used to grant extended life to a spell projectile (See 0x09 below) (ASM claims int8)
/*0083*/ int8 projectileType;		// Comment: Yeahlight: 0x09 - Spell bolt, 0x11 - Arrow, 0x1B - Arrow, 0x1C - Under water attack? (Verified to be int8)
/*0084*/ int8 sourceAnimation;		// Comment: Yeahlight: Attack animation of the inflictor (Verified to be int8)
/*0085*/ char texture[16];			// Comment: Yeahlight: Object's texture filename (Must be set to "GENC00" or the like when using spell bolt projectiles)
/*0101*/ char spacer[15];			// Comment: Yeahlight: ASM makes no reference to any bytes after the 85th, so these must be padding
};


// Harakiri struct sent by client when using /discp
struct UseDiscipline_Struct {
/*0001*/ int8 discipline;			   // Comment: The discipline executed
/*0001*/ int8 unknown[3];			   // Comment: Seems to be always 0 
};

// Harakiri struct to sent to the client after completing a quest with money
// to get the fanfare sound, alternativly, just sent with all 0 to get sound
struct QuestCompletedMoney_Struct{
	/*0000*/	int32	npcID; 	 // Comment: Harakiri The ID of the NPC which gave money for the finished quest
	/*0004*/	int8	unknown[16];
	/*0020*/	uint32	copper;	// Comment: Harakiri amount of copper
	/*0024*/	uint32	silver; // Comment: Harakiri amount of silver
	/*0028*/	uint32	gold; 	// Comment: Harakiri amount of gold
	/*0032*/	uint32	platinum; // Comment: Harakiri amount of platinum			
	};

struct GlobalID_Struct
{
int16 entity_id;
};

// Restore structure packing to default
#pragma pack()

#endif

