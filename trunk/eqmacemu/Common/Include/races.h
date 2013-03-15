// ***************************************************************
//  EQCException   ·  date: 21/12/2007
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#ifndef RACES_H
#define RACES_H

//o--------------------------------------------------------------
//| Name: Race List - 06/22/08 - Wizzel
//o--------------------------------------------------------------
//| Notes: These are the list of all races in our client    
//o--------------------------------------------------------------

//---------------1-15---------------//
#define HUMAN				1		// Comment: Human
#define BARBARIAN			2		// Comment: Barbarian
#define ERUDITE				3		// Comment: Erudite
#define WOOD_ELF			4		// Comment: Wood Elf
#define HIGH_ELF			5		// Comment: High Elf
#define DARK_ELF			6		// Comment: Dark Elf
#define HALF_ELF			7		// Comment: Half Elf
#define DWARF				8		// Comment: Dwarf
#define TROLL				9		// Comment: Troll
#define OGRE				10		// Comment: Ogre
#define HALFLING			11		// Comment: Halfing
#define GNOME				12		// Comment: Gnome
#define PLAYER_RACE_COUNT	13		// The count of all player races
#define AVIAK				13		// Comment: Aviak				Texture 0: Black, 1: White, 2: Parrot
#define WEREWOLF			14		// Comment: Werewolf			Texture 0: Normal
#define BROWNIE				15		// Comment: Brownie				Texture 0: Normal
//---------------16-30--------------//
#define CENTAUR				16		// Comment: Centaur							
#define GOLEM				17		// Comment: Golem				
#define GIANT				18		// Comment: Giant				
#define TRAKANON			19		// Comment: Trakanon					
#define VENRIL_SATHIR		20		// Comment: Venril Sathir		
#define EVIL_EYE			21		// Comment: Evil Eye			Texture 0: Normal
#define BEETLE				22		// Comment: Beetle				
#define KERRA				23		// Comment: Kerra
#define FISH				24		// Comment: Fish				Texture 0: Blue, 1: Red, 2: Green
#define FAIRY				25		// Comment: Fairy				Texture 0: Normal
#define OLD_FROGLOK			26		// Comment: Froglok Guard		Texture 0: Normal
#define FROGLOK_GHOUL		27		// Comment: Froglok				Texture 0: Normal, 1:Undead
#define FUNGUSMAN			28		// Comment: Fungus Man		Texture 0: Normal(Red/White), 1:Diseased (Purple), 2:Green Striped
#define GARGOYLE			29		// Comment: Gargoyle	
#define GASBAG				30		// Comment: Gasbag
//---------------31-45--------------//
#define GELATINOUS_CUBE		31		// Comment: Gelatinous Cube
#define GHOST				32		// Comment: Ghost
#define GHOUL				33		// Comment: Ghoul	
#define GIANT_BAT			34		// Comment: Bat
#define GIANT_EEL			35		// Comment: Eel
#define GIANT_RAT			36		// Comment: Rat
#define GIANT_SNAKE			37		// Comment: Snake
#define GIANT_SPIDER		38		// Comment: Spider
#define GNOLL				39		// Comment: Gnoll
#define GOBLIN				40		// Comment: Goblin
#define GORILLA				41		// Comment: Gorilla
#define WOLF				42		// Comment: Wolf
#define BEAR				43		// Comment: Bear				Texture 0: Brown, 1: Black, 2: White
#define FREEPORT_GUARDS		44		// Comment: Freeport Guard
#define DEMI_LICH			45		// Comment: Demi Lich
//---------------46-60--------------//
#define IMP					46		// Comment: Imp
#define GRIFFIN				47		// Comment: Griffin
#define KOBOLD				48		// Comment: Kobold
#define LAVA_DRAGON			49		// Comment: Dragon				Texure 0: Naggy, 1: Gorenaire/Vox, 2: ??, 3: ??, 4: ??, 5: ??, 6: Phara Dar, 7: ??
#define LION				50		// Comment: Lion
#define LIZARD_MAN			51		// Comment: Lizard Man
#define MIMIC				52		// Comment: Mimic		
#define MINOTAUR			53		// Comment: Minotaur
#define ORC					54		// Comment: Orc
#define HUMAN_BEGGAR		55		// Comment: Human Beggar
#define	PIXIE				56		// Comment: Pixie
#define DRACNID				57		// Comment: Dracnic
#define SOLUSEK_RO			58		// Comment: Solusek Ro
#define BLOODGILLS			59		// Comment: Bloodgills
#define SKELETON			60		// Comment: Human Skeleton		Texture 0: White, 1: Brown
//---------------61-75--------------//
#define SHARK				61		// Comment: Shark
#define TUNARE				62		// Comment: Tunare
#define TIGER				63		// Comment: Tiger
#define TREANT				64		// Comment: Treant
#define VAMPIRE				65		// Comment: Vampire
#define RALLOS_ZEK			66		// Comment: Rallos Zek
#define HIGHPASS_CITIZEN	67		// Comment: Highpass Citizen
#define TENTACLE			68		// Comment: Tentacle
#define WILL_O_WISP			69		// Comment: Will O Wisp
#define ZOMBIE				70		// Comment: Zombie
#define QEYNOS_CITIZEN		71		// Comment: Qeynos Citizen
#define SHIP				72		// Comment:	Ship
#define LAUNCH				73		// Comment: Launch
#define PIRANHA				74		// Comment: Piranha
#define ELEMENTAL			75		// Comment: Elemental			Texture 0: Earth, 1: Fire, 2: Water, 3: Air
//---------------76-90--------------//
#define PUMA				76		// Comment: Puma
#define NERIAK_CITIZEN		77		// Comment: Neriak Citizen
#define ERUDIN_CITIZEN		78		// Comment: Erudin Citizen
#define BIXIE				79		// Comment: Bixie
#define REANIMATED_HAND		80		// Comment: Reanimated Hand
#define RIVERVALE_CITIZEN	81		// Comment: Rivervale Citizen
#define SCARECROW			82		// Comment: Scarecrow
#define SKUNK				83		// Comment: Skunk
#define SNAKE_ELEMENTAL		84		// Comment: Snake Elemental
#define SPECTRE				85		// Comment: Spectre
#define SPHINX				86		// Comment: Sphinx
#define ARMADILLO			87		// Comment: Armadillo
#define CLOCKWORK_GNOME		88		// Comment: Clockwork Gnome
#define DRAKE				89		// Comment: Drake
#define HALAS_CITIZEN		90		// Comment: Halas Citizen
//--------------91-105--------------//
#define ALLIGATOR			91		// Comment: Alligator
#define GROBB_CITIZEN		92		// Comment: Grobb Citizen
#define OGGOK_CITIZEN		93		// Comment: Oggok Citizen
#define KALADIM_CITIZEN		94		// Comment: Kaladim Citizen
#define CAZIC_THULE			95		// Comment: Cazic Thule
#define COCKATRICE			96		// Comment: Cockatrice
#define DAISY_MAN			97		// Comment: Daisy Man
#define ELF_VAMPIRE			98		// Comment: Elf Vampire
#define DENIZEN				99		// Comment: Denizen
#define DERVISH				100		// Comment: Dervish
#define EFREETI				101		// Comment: Efreeti
#define FROGLOK_TADPOLE		102		// Comment: Froglok Tadpole
#define KEDGE				103		// Comment: Kedge
#define LEECH				104		// Comment: Leech	
#define SWORDFISH			105		// Comment: Swordfish
//--------------106-120-------------//
#define FELGUARD			106		// Comment: Felguard
#define MAMMOTH				107		// Comment: Mammoth
#define EYE_OF_ZOMM			108		// Comment: Eye of Zomm
#define WASP				109		// Comment: Wasp
#define MERMAID				110		// Comment: Mermaid
#define HARPIE				111		// Comment: Harpie
#define FAYGUARD			112		// Comment: Fayguard
#define DRIXIE				113		// Comment: Drixie
#define GHOST_SHIP			114		// Comment: Ghost Ship
#define CLAM				115		// Comment: Clam
#define SEA_HORSE			116		// Comment: Sea Horse
#define GHOST_DWARF			117		// Comment: Dwarf Ghost
#define ERUDITE_GHOST		118		// Comment: Erudite Ghost
#define	SABERTOOTH_CAT		119		// Comment: Sabertooth Cat
#define WOLF_ELEMENTAL		120		// Comment: Wolf Elemental - Texture 0: Normal, 1: Ghost
//--------------121-135-------------//
#define GORGON				121		// Comment: Gorgon
#define DRAGON_SKELETON		122		// Comment: Bone Dragon
#define	INNORUK				123		// Comment: Innoruk
#define UNICORN				124		// Comment: Unicorn - Texture 0: White, 1: Black, 2: White w/ white eyes
#define PEGASUS				125
#define DJINN				126
#define INVISIBLE_MAN		127		// Comment: Invisible Man
#define IKSAR				128		// Comment: Iksar
#define SCORPION			129
#define VAHSHIR				130		// Comment: Vah Shir
#define SARNAK				131
#define DRAGLOCK			132
#define LYCANTHROPE			133
#define MOSQUITO			134
#define	RHINO				135
//--------------136-150-------------//
#define XALGOZ				136
#define KUNARK_GOBLIN		137
#define YETI				138
#define IKSAR_CITIZEN		139
#define FOREST_GIANT		140
#define BOAT				141
#define NEAREST_DOODAD		142
#define NEAREST_TREE		143
#define BURYNAI				144
#define GOO					145
#define SPECTRAL_SARNAK		146
#define SPECTRAL_IKSAR		147
#define KUNARK_FISH			148
#define IKSAR_SCORPION		149
#define	EROLLISI			150
//--------------151-165-------------//
#define TRIBUNAL			151		// Comment: Some god dressed up as an executioner
#define BERTOXXULOUS		152
#define BRISTLEBANE			153		// Comment: Bristlebane
#define FAY_DRAKE			154
#define SARNAK_SKELETON		155
#define RATMAN				156
#define WYVERN				157
#define WURM				158
#define DEVOURER			159
#define IKSAR_GOLEM			160
#define IKSAR_SKELETON		161		// Comment: Iksar Skeleton
#define MAN_EATING_PLANT	162
#define RAPTOR				163
#define SARNAK_GOLEM		164
#define WATER_DRAGON		165		// Comment: The boss mob from cobalt scar, don't know his name
//--------------166-180-------------//

//o--------------------------------------------------------------
//|  Harakiri 08/11/09
//o--------------------------------------------------------------
//|found in the eqgame.exe sub_4C9105 (004C9105)   
//o--------------------------------------------------------------

#define IKSAR_HAND			166
#define SUCCULENT			167
#define FLYING_MONKEY		168
#define BRONTOTHERIUM		169
#define SNOW_DERVISH		170
#define	DIRE_WOLF			171
#define MANTICORE			172
#define TOTEM				173
#define COLD_SPECTRE		174
#define ENCHANTED_ARMOR		175
#define SNOW_BUNNY			176
#define WALRUS				177
#define ROCK_GEM_MEN		178
#define YAK_MAN				181
#define FAUN				182
#define COLDAIN				183
#define VELIOUS_DRAGONS		184
#define UNKNOWN_185			185
#define HIPPOGRIFF			186
#define SIREN				187
#define FROST_GIANT			188
#define STORM_GIANT			189
#define OTTERMEN			190
#define WALRUS_MAN			191
#define CLOCKWORK_DRAGON	192
#define ABHORENT			193
#define SEA_TURTLE			194
#define BLACK_AND_WHITE_DRAGONS 195
#define GHOST_DRAGON		196
#define RONNIE_TEST			197	// Harakiri this is the actual value from the client, some dev made some tests =)
#define SLEEPER				198		// Comment: Sleeper from ST / Harakiri: no idea if this is right
#define PRISMATIC_DRAGON	198
#define SHIKNAR				199
#define ROCKHOPPER			200
#define UNDERBULK			201
#define GRIMLING			202
#define VACUUM_WORM			203
#define EVAN_TEST			204 // Harakiri this is the actual value from the client, some dev made some tests =)
#define KAHLI_SHAH			205
#define OWLBEAR				206
#define RHINO_BEETLE		207
#define VAMPYRE				208
#define EARTH_ELEMENTAL		209
#define AIR_ELEMENTAL		210
#define WATER_ELEMENTAL		211
#define FIRE_ELEMENTAL		212
#define WETFANG_MINNOW		213
#define THOUGHT_HORROR		214
#define TEGI				215
#define HORSE				216		// Comment: A model displaying no name
#define SHISSAR				217
#define FUNGAL_FIEND		218
#define VAMPIRE_VOLATALIS	219
#define STONEGRABBER		220
#define SCARLET_CHEETAH		221
#define ZELNIAK				222
#define LIGHTCRAWLER		223
#define SHADE				224
#define SUNFLOWER			225
#define SUN_REVENANT		226
#define SHRIEKER			227
#define GALORIAN			228
#define NETHERBIAN			229
#define AKHEVA				230
#define SPIRE_SPIRIT		231
#define SONIC_WOLF			232
#define GROUND_SHAKER		233
#define VAH_SHIR_SKELETON	234
#define MUTANT_HUMANOID		235
#define SERU				236
#define RECUSO				237
#define VAH_SHIR_KING		238
#define VAH_SHIR_GUARD		239
#define TELEPORT_MAN		240
#define LUJEIN				241
#define NAIAD				242
#define NYMPH				243
#define ENT					244
#define FLY_MAN				245
#define TAREW_MARR			246
#define SOL_RO				247
#define CLOCKWORK_GOLEM		248
#define CLOCKWORK_BRAIN		249
#define SPECTRAL_BANSHEE	250
#define GUARD_OF_JUSTICE	251
#define UNKNOWN_252			252
#define DISEASE_BOSS		253
#define SOL_RO_GUARD		254
#define NEW_BERTOX			255
#define NEW_TRIBUNAL		256
#define TERRIS_THULE		257
#define VEGEROG				258
#define CROCODILE			259
#define BAT					260
#define SLARGHILUG			261
#define TRANQUILION			262
#define TIN_SOLDIER			263
#define NIGHTMARE_WRAITH	264
#define MALARIAN			265
#define KNIGHT_OF_PESTILENCE 266
#define LEPERTOLOTH			267
#define BUBONIAN_BOSS		268
#define BUBONIAN_UNDERLING	269
#define PUSLING				270
#define WATER_MEPHIT		271
#define STORMRIDER			272
#define JUNK_BEAST			273
#define BROKEN_CLOCKWORK	274
#define GIANT_CLOCKWORK		275
#define CLOCKWORK_BEETLE	276
#define NIGHTMARE_GOBLIN	277
#define KARANA				278
#define BLOOD_RAVEN			279
#define NIGHTMARE_GARGOYLE	280
#define MOUTHS_OF_INSANITY	281
#define SKELETAL_HORSE		282
#define SARYN				283
#define FENNIN_RO			284
#define TORMENTOR			285
#define NECRO_PRIEST		286
#define NIGHTMARE			287
#define NEW_RALLOS_ZEK		288
#define VALLON_ZEK			289
#define TALLON_ZEK			290
#define AIR_MEPHIT			291
#define EARTH_MEPHIT		292
#define FIRE_MEPHIT			293
#define NIGHTMARE_MEPHIT	294
#define ZEBUXORUK			295
#define MITHANIEL_MARR		296
#define UNDEAD_KNIGHT		297
#define THE_RATHE			298
#define XEGONY				299
#define FIEND				300
#define TEST_OBJECT			301
#define CRAB				302
#define PHOENIX				303
#define POP_DRAGON			304
#define POP_BEAR			305
#define STORM_TAARID		306
#define STORM_SATUUR		307
#define STORM_KURAALN		308
#define STORM_VOLAAS		309
#define STORM_MANA			310
#define STORM_FIRE			311
#define STORM_CELESTIAL		312
#define WAR_WRAITH			313
#define WRULON				314
#define KRAKEN				315
#define POISON_FROG			316
#define QUEZTOCOATAL		317
#define VALORIAN			318
#define WAR_BOAR			319
#define POP_EFREETI			320
#define WAR_BOAR_UNARMORED	321
#define BLACK_KNIGHT		322
#define ANIMATED_ARMOR		323
#define UNDEAD_FOOTMAN		324
#define RALLOS_ZEK_MINION	325
#define ARACHNID			326
#define CRYSTAL_SPIDER		327
#define ZEB_CAGE			328
#define BOT_PORTAL			329
#define FROGLOK				330
#define TROLL_BUCCANEER		331
#define TROLL_FREEBOOTER	332
#define TROLL_SEA_ROVER		333
#define SPECTRE_PIRATE_BOSS	334
#define PIRATE_BOSS			335
#define PIRATE_DARK_SHAMAN	336
#define PIRATE_OFFICER		337
#define GNOME_PIRATE		338
#define DARK_ELF_PIRATE		339
#define OGRE_PIRATE			340
#define HUMAN_PIRATE		341
#define ERUDITE_PIRATE		342
#define POISON_DART_FROG	343
#define TROLL_ZOMBIE		344
#define LUGGALD_LAND		345
#define LUGGALD_ARMORED		346
#define LUGGALD_ROBED		347
#define LUGGALD_MOUNT		348
#define FROGLOK_SKELETON	349
#define UNDEAD_FROGLOK		350
#define CHOSEN_WARRIOR		351
#define CHOSEN_WIZARD		352
#define VEKSAR				353
#define GREATER_VEKSAR		354
#define VEKSAR_BOSS			355
#define CHOKADAI			356
#define UNDEAD_CHOKADAI		357
#define UNDEAD_VEKSAR		358

namespace EQC
{
	namespace Common
	{
		char* GetRaceName(int8 race);
	}
}

#endif