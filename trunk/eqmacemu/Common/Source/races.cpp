// ***************************************************************
//  races   ·  date: 21/12/2007
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "eq_packet_structs.h"
#include "races.h"

namespace EQC
{
	namespace Common
	{
		// Converts the int8 race to a text value
		char* GetRaceName(int8 in_race) 
		{
			char* result = "";
			
			switch(in_race) 
			{
				case HUMAN:
					  result = "Human";
					  break;
				case BARBARIAN:
					  result = "Barbarian";
					  break;
				case ERUDITE:
				  result = "Erudite";
				  break;
				case WOOD_ELF:
				  result = "Wood Elf";
				  break;
				case HIGH_ELF:
				  result = "High Elf";
				  break;
				case DARK_ELF:
				  result = "Dark Elf";
				  break;
				case HALF_ELF:
				  result = "Half Elf";
				  break;
				case DWARF:
				  result = "Dwarf";
				  break;
				case TROLL:
				  result = "Troll";
				  break;
				case OGRE:
				  result = "Ogre";
				  break;
				case HALFLING:
				  result = "Halfling";
				  break;
				case GNOME:
				  result = "Gnome";
				  break;
				case AVIAK:
				  result = "Aviak";
				  break;
				case HIGHPASS_CITIZEN:
				  result = "Highpass Citizen";
				  break;
				case BROWNIE:
				  result = "Brownie";
				  break;
				case CENTAUR:
				  result = "Centaur";
				  break;
				case GOLEM:
				  result = "Golem";
				  break;
				case GIANT:
				  result = "Giant / Cyclops";
				  break;
				case TRAKANON:
				  result = "Trakanon"; // Harakiri misspelled as Trakenon in eqgame
				  break;
				case VENRIL_SATHIR:
				  result = "Venril Sathir"; // Harakiri misspelled as "Venril Sathor in eqgame
				  break;
				case EVIL_EYE:
				  result = "Evil Eye";
				  break;
				case BEETLE:
				  result = "Beetle";
				  break;
				case KERRA:
				  result = "Kerra";
				  break;
				case FISH:
				  result = "Fish";
				  break;
				case FAIRY:
				  result = "Fairy";
				  break;
				case OLD_FROGLOK:
				  result = "Froglok";
				  break;
				case FROGLOK_GHOUL:
				  result = "Froglok Ghoul";
				  break;
				case FUNGUSMAN:
				  result = "Fungusman";
				  break;
				case GARGOYLE:
				  result = "Gargoyle";
				  break;
				case GASBAG:
				  result = "Gasbag";
				  break;
				case GELATINOUS_CUBE:
				  result = "Gelatinous Cube";
				  break;
				case GHOST:
				  result = "Ghost";
				  break;
				case GHOUL:
				  result = "Ghoul";
				  break;
				case GIANT_BAT:
				  result = "Giant Bat";
				  break;
				case GIANT_EEL:
				  result = "Giant Eel";
				  break;
				case GIANT_RAT:
				  result = "Giant Rat";
				  break;
				case GIANT_SNAKE:
				  result = "Giant Snake";
				  break;
				case GIANT_SPIDER:
				  result = "Giant Spider";
				  break;
				case GNOLL:
				  result = "Gnoll";
				  break;
				case GOBLIN:
				  result = "Goblin";
				  break;
				case GORILLA:
				  result = "Gorilla";
				  break;
				case WOLF:
				  result = "Wolf";
				  break;
				case BEAR:
				  result = "Bear";
				  break;
				case FREEPORT_GUARDS:
				  result = "Freeport Guards";
				  break;
				case DEMI_LICH:
				  result = "Demi Lich";
				  break;
				case IMP:
				  result = "Imp";
				  break;
				case GRIFFIN:
				  result = "Griffin";
				  break;
				case KOBOLD:
				  result = "Kobold";
				  break;
				case LAVA_DRAGON:
				  result = "Lava Dragon";
				  break;
				case LION:
				  result = "Lion";
				  break;
				case LIZARD_MAN:
				  result = "Lizard Man";
				  break;
				case MIMIC:
				  result = "Mimic";
				  break;
				case MINOTAUR:
				  result = "Minotaur";
				  break;
				case ORC:
				  result = "Orc";
				  break;
				case HUMAN_BEGGAR:
				  result = "Human Beggar";
				  break;
				case PIXIE:
				  result = "Pixie";
				  break;
				case DRACNID:
				  result = "Dracnid";
				  break;
				case SOLUSEK_RO:
				  result = "Solusek Ro";
				  break;
				case BLOODGILLS:
				  result = "Bloodgills";
				  break;
				case SKELETON:
				  result = "Skeleton";
				  break;
				case SHARK:
				  result = "Shark";
				  break;
				case TUNARE:
				  result = "Tunare";
				  break;
				case TIGER:
				  result = "Tiger";
				  break;
				case TREANT:
				  result = "Treant";
				  break;
				case VAMPIRE:
				  result = "Vampire";
				  break;
				case RALLOS_ZEK:
				  result = "Rallos Zek";
				  break;
				case WEREWOLF:
				  result = "Were Wolf";
				  break;
				case TENTACLE:
				  result = "Tentacle";
				  break;
				case WILL_O_WISP:
				  result = "Will 'O Wisp";
				  break;
				case ZOMBIE:
				  result = "Zombie";
				  break;
				case QEYNOS_CITIZEN:
				  result = "Qeynos Citizen";
				  break;
				case SHIP:
				  result = "Ship";
				  break;
				case LAUNCH:
				  result = "Launch";
				  break;
				case PIRANHA:
				  result = "Piranha";
				  break;
				case ELEMENTAL:
				  result = "Elemental";
				  break;
				case BOAT:
				  result = "Boat";
				  break;
				case PUMA:
				  result = "Puma";
				  break;
				case NERIAK_CITIZEN:
				  result = "Neriak Citizen";
				  break;
				case ERUDIN_CITIZEN:
				  result = "Erudite Citizen";
				  break;
				case BIXIE:
				  result = "Bixie";
				  break;
				case REANIMATED_HAND:
				  result = "Reanimated Hand";
				  break;
				case RIVERVALE_CITIZEN:
				  result = "Rivervale Citizen";
				  break;
				case SCARECROW:
				  result = "Scarecrow";
				  break;
				case SKUNK:
				  result = "Skunk";
				  break;
				case SNAKE_ELEMENTAL:
				  result = "Snake Elemental";
				  break;
				case SPECTRE:
				  result = "Spectre";
				  break;
				case SPHINX:
				  result = "Sphinx";
				  break;
				case ARMADILLO:
				  result = "Armadillo";
				  break;
				case CLOCKWORK_GNOME:
				  result = "Clockwork Gnome";
				  break;
				case DRAKE:
				  result = "Drake";
				  break;
				case HALAS_CITIZEN:
				  result = "Halas Citizen";
				  break;
				case ALLIGATOR:
				  result = "Alligator";
				  break;
				case GROBB_CITIZEN:
				  result = "Grobb Citizen";
				  break;
				case OGGOK_CITIZEN:
				  result = "Oggok Citizen";
				  break;
				case KALADIM_CITIZEN:
				  result = "Kaladim Citizen";
				  break;
				case CAZIC_THULE:
				  result = "Cazic Thule";
				  break;
				case COCKATRICE:
				  result = "Cockatrice";
				  break;
				case DAISY_MAN:
				  result = "Daisy Man";
				  break;
				case ELF_VAMPIRE:
				  result = "Elf Vampire";
				  break;
				case DENIZEN:
				  result = "Denizen";
				  break;
				case DERVISH:
				  result = "Dervish";
				  break;
				case EFREETI:
				  result = "Efreeti";
				  break;
				case FROGLOK_TADPOLE:
				  result = "Froglok Tadpole";
				  break;
				case KEDGE:
				  result = "Kedge";
				  break;
				case LEECH:
				  result = "Leech";
				  break;
				case SWORDFISH:
				  result = "Swordfish";
				  break;
				case FELGUARD:
				  result = "Felguard";
				  break;
				case MAMMOTH:
				  result = "Mammoth";
				  break;
				case EYE_OF_ZOMM:
				  result = "Eye of Zomm";
				  break;
				case WASP:
				  result = "Wasp";
				  break;
				case MERMAID:
				  result = "Mermaid";
				  break;
				case HARPIE:
				  result = "Harpie";
				  break;
				case FAYGUARD:
				  result = "Fayguard";
				  break;
				case DRIXIE:
				  result = "Drixie";
				  break;
				case GHOST_SHIP:
				  result = "Ghost Ship";
				  break;
				case CLAM:
				  result = "Clam";
				  break;
				case SEA_HORSE:
				  result = "Sea Horse";
				  break;
				case GHOST_DWARF:
				  result = "Ghost Dwarf";
				  break;
				case ERUDITE_GHOST:
				  result = "Erudite Ghost";
				  break;
				case SABERTOOTH_CAT:
				  result = "Sabertooth Cat";
				  break;
				case WOLF_ELEMENTAL:
				  result = "Wolf Elemental";
				  break;
				case GORGON:
				  result = "Gorgon";
				  break;
				case DRAGON_SKELETON:
				  result = "Dragon Skeleton";
				  break;
				case INNORUK:
				  result = "Innoruuk";
				  break;
				case UNICORN:
				  result = "Unicorn";
				  break;
				case PEGASUS:
				  result = "Pegasus";
				  break;
				case DJINN:
				  result = "Djinn";
				  break;
				case INVISIBLE_MAN:
				  result = "Invisible Man";
				  break;
				case IKSAR:
				  result = "Iksar";
				  break;
				case SCORPION:
				  result = "Scorpion";
				  break;
				case SARNAK:
				  result = "Sarnak";
				  break;
				case DRAGLOCK:
				  result = "Draglock";
				  break;
				case LYCANTHROPE:
				  result = "Lycanthrope";
				  break;
				case MOSQUITO:
				  result = "Mosquito";
				  break;
				case RHINO:
				  result = "Rhino";
				  break;
				case XALGOZ:
				  result = "Xalgoz";
				  break;
				case KUNARK_GOBLIN:
				  result = "Kunark Goblin";
				  break;
				case YETI:
				  result = "Yeti";
				  break;
				case IKSAR_CITIZEN:
				  result = "Iksar Citizen";
				  break;
				case FOREST_GIANT:
				  result = "Forest Giant";
				  break;
				case BURYNAI:
				  result = "Burynai";
				  break;
				case GOO:
				  result = "Goo";
				  break;
				case SPECTRAL_SARNAK:
				  result = "Spectral Sarnak";
				  break;
				case SPECTRAL_IKSAR:
				  result = "Spectral Iksar";
				  break;
				case KUNARK_FISH:
				  result = "Kunark Fish";
				  break;
				case IKSAR_SCORPION:
				  result = "Iksar Scorpion";
				  break;
				case EROLLISI:
				  result = "Erollisi";
				  break;
				case TRIBUNAL:
				  result = "Tribunal";
				  break;
				case BERTOXXULOUS:
				  result = "Bertoxxulous";
				  break;
				case BRISTLEBANE:
				  result = "Bristlebane";
				  break;
				case FAY_DRAKE:
				  result = "Fay Drake";
				  break;
				case SARNAK_SKELETON:
				  result = "Sarnak Skeleton";
				  break;
				case RATMAN:
				  result = "Ratman";
				  break;
				case WYVERN:
				  result = "Wyvern";
				  break;
				case WURM:
				  result = "Wurm";
				  break;
				case DEVOURER:
				  result = "Devourer";
				  break;
				case IKSAR_GOLEM:
				  result = "Iksar Golem";
				  break;
				case IKSAR_SKELETON:
				  result = "Iksar Skeleton";
				  break;
				case MAN_EATING_PLANT:
				  result = "Man Eating Plant";
				  break;
				case RAPTOR:
				  result = "Raptor";
				  break;
				case SARNAK_GOLEM:
				  result = "Sarnak Golem";
				  break;
				case WATER_DRAGON:
				  result = "Water Dragon";
				  break;
				case IKSAR_HAND:
				  result = "Iksar Hand";
				  break;
				case SUCCULENT:
				  result = "Succulent";
				  break;
				case FLYING_MONKEY:
				  result = "Flying Monkey";
				  break;
				case BRONTOTHERIUM:
				  result = "Brontotherium";
				  break;
				case SNOW_DERVISH:
				  result = "Snow Dervish";
				  break;
				case DIRE_WOLF:
				  result = "Dire Wolf";
				  break;
				case MANTICORE:
				  result = "Manticore";
				  break;
				case TOTEM:
				  result = "Totem";
				  break;
				case COLD_SPECTRE:
				  result = "Cold Spectre";
				  break;
				case ENCHANTED_ARMOR:
				  result = "Enchanted Armor";
				  break;
				case SNOW_BUNNY:
				  result = "Snow Bunny";
				  break;
				case WALRUS:
				  result = "Walrus";
				  break;
				case ROCK_GEM_MEN:
				  result = "Rock-gem Men";
				  break;
				case YAK_MAN:
				  result = "Yak Man";
				  break;
				case FAUN:
				  result = "Faun";
				  break;
				case COLDAIN:
				  result = "Coldain";
				  break;
				case VELIOUS_DRAGONS:
				  result = "Velious Dragons";
				  break;
				case UNKNOWN_185:
				  result = "UNKNOWN_185";
				  break;
				case HIPPOGRIFF:
				  result = "Hippogriff";
				  break;
				case SIREN:
				  result = "Siren";
				  break;
				case FROST_GIANT:
				  result = "Frost Giant";
				  break;
				case STORM_GIANT:
				  result = "Storm Giant";
				  break;
				case OTTERMEN:
				  result = "Ottermen";
				  break;
				case WALRUS_MAN:
				  result = "Walrus Man";
				  break;
				case CLOCKWORK_DRAGON:
				  result = "Clockwork Dragon";
				  break;
				case ABHORENT:
				  result = "Abhorent";
				  break;
				case SEA_TURTLE:
				  result = "Sea Turtle";
				  break;
				case BLACK_AND_WHITE_DRAGONS:
				  result = "Black and White Dragons";
				  break;
				case GHOST_DRAGON:
				  result = "Ghost Dragon";
				  break;
				case RONNIE_TEST:
				  result = "Ronnie Test";
				  break;
				case PRISMATIC_DRAGON:
				  result = "Prismatic Dragon";
				  break;
				case SHIKNAR:
				  result = "ShikNar";
				  break;
				case ROCKHOPPER:
				  result = "Rockhopper";
				  break;
				case UNDERBULK:
				  result = "Underbulk";
				  break;
				case GRIMLING:
				  result = "Grimling";
				  break;
				case VAHSHIR:
				  result = "Vah Shir";
				  break;
				case VACUUM_WORM:
				  result = "Vacuum Worm";
				  break;
				case EVAN_TEST:
				  result = "Evan Test";
				  break;
				case KAHLI_SHAH:
				  result = "Kahli Shah";
				  break;
				case OWLBEAR:
				  result = "Owlbear";
				  break;
				case RHINO_BEETLE:
				  result = "Rhino Beetle";
				  break;
				case VAMPYRE:
				  result = "Vampyre";
				  break;
				case EARTH_ELEMENTAL:
				  result = "Earth Elemental";
				  break;
				case AIR_ELEMENTAL:
				  result = "Air Elemental";
				  break;
				case WATER_ELEMENTAL:
				  result = "Water Elemental";
				  break;
				case FIRE_ELEMENTAL:
				  result = "Fire Elemental";
				  break;
				case WETFANG_MINNOW:
				  result = "Wetfang Minnow";
				  break;
				case THOUGHT_HORROR:
				  result = "Thought Horror";
				  break;
				case TEGI:
				  result = "Tegi";
				  break;
				case HORSE:
				  result = "Horse";
				  break;
				case SHISSAR:
				  result = "Shissar";
				  break;
				case FUNGAL_FIEND:
				  result = "Fungal Fiend";
				  break;
				case VAMPIRE_VOLATALIS:
				  result = "Vampire Volatalis";
				  break;
				case STONEGRABBER:
				  result = "Stonegrabber";
				  break;
				case SCARLET_CHEETAH:
				  result = "Scarlet Cheetah";
				  break;
				case ZELNIAK:
				  result = "Zelniak";
				  break;
				case LIGHTCRAWLER:
				  result = "Lightcrawler";
				  break;
				case SHADE:
				  result = "Shade";
				  break;
				case SUNFLOWER:
				  result = "Sunflower";
				  break;
				case SUN_REVENANT:
				  result = "Sun Revenant";
				  break;
				case SHRIEKER:
				  result = "Shrieker";
				  break;
				case GALORIAN:
				  result = "Galorian";
				  break;
				case NETHERBIAN:
				  result = "Netherbian";
				  break;
				case AKHEVA:
				  result = "Akheva";
				  break;
				case SPIRE_SPIRIT:
				  result = "Spire Spirit";
				  break;
				case SONIC_WOLF:
				  result = "Sonic Wolf";
				  break;
				case GROUND_SHAKER:
				  result = "Ground Shaker";
				  break;
				case VAH_SHIR_SKELETON:
				  result = "Vah Shir Skeleton";
				  break;
				case MUTANT_HUMANOID:
				  result = "Mutant Humanoid";
				  break;
				case SERU:
				  result = "Seru";
				  break;
				case RECUSO:
				  result = "Recuso";
				  break;
				case VAH_SHIR_KING:
				  result = "Vah Shir King";
				  break;
				case VAH_SHIR_GUARD:
				  result = "Vah Shir Guard";
				  break;
				case TELEPORT_MAN:
				  result = "Teleport Man";
				  break;
				case LUJEIN:
				  result = "Lujein";
				  break;
				case NAIAD:
				  result = "Naiad";
				  break;
				case NYMPH:
				  result = "Nymph";
				  break;
				case ENT:
				  result = "Ent";
				  break;
				case FLY_MAN:
				  result = "Fly Man";
				  break;
				case TAREW_MARR:
				  result = "Tarew Marr";
				  break;
				case SOL_RO:
				  result = "Sol Ro";
				  break;
				case CLOCKWORK_GOLEM:
				  result = "Clockwork Golem";
				  break;
				case CLOCKWORK_BRAIN:
				  result = "Clockwork Brain";
				  break;
				case SPECTRAL_BANSHEE:
				  result = "Spectral Banshee";
				  break;
				case GUARD_OF_JUSTICE:
				  result = "Guard of Justice";
				  break;
				case UNKNOWN_252:
				  result = "Unknown 252";
				  break;
				case DISEASE_BOSS:
				  result = "Disease Boss";
				  break;
				case SOL_RO_GUARD:
				  result = "Sol Ro Guard";
				  break;
				case NEW_BERTOX:
				  result = "New Bertox";
				  break;
				case NEW_TRIBUNAL:
				  result = "New Tribunal";
				  break;
				case TERRIS_THULE:
				  result = "Terris Thule";
				  break;
				case VEGEROG:
				  result = "Vegerog";
				  break;
				case CROCODILE:
				  result = "Crocodile";
				  break;
				case BAT:
				  result = "Bat";
				  break;
				case SLARGHILUG:
				  result = "Slarghilug";
				  break;
				case TRANQUILION:
				  result = "Tranquilion";
				  break;
				case TIN_SOLDIER:
				  result = "Tin Soldier";
				  break;
				case NIGHTMARE_WRAITH:
				  result = "Nightmare Wraith";
				  break;
				case MALARIAN:
				  result = "Malarian";
				  break;
				case KNIGHT_OF_PESTILENCE:
				  result = "Knight of Pestilence";
				  break;
				case LEPERTOLOTH:
				  result = "Lepertoloth";
				  break;
				case BUBONIAN_BOSS:
				  result = "Bubonian Boss";
				  break;
				case BUBONIAN_UNDERLING:
				  result = "Bubonian Underling";
				  break;
				case PUSLING:
				  result = "Pusling";
				  break;
				case WATER_MEPHIT:
				  result = "Water Mephit";
				  break;
				case STORMRIDER:
				  result = "Stormrider";
				  break;
				case JUNK_BEAST:
				  result = "Junk Beast";
				  break;
				case BROKEN_CLOCKWORK:
				  result = "Broken Clockwork";
				  break;
				case GIANT_CLOCKWORK:
				  result = "Giant Clockwork";
				  break;
				case CLOCKWORK_BEETLE:
				  result = "Clockwork Beetle";
				  break;
				case NIGHTMARE_GOBLIN:
				  result = "Nightmare Goblin";
				  break;
				case KARANA:
				  result = "Karana";
				  break;
				case BLOOD_RAVEN:
				  result = "Blood Raven";
				  break;
				case NIGHTMARE_GARGOYLE:
				  result = "Nightmare Gargoyle";
				  break;
				case MOUTHS_OF_INSANITY:
				  result = "Mouths of Insanity";
				  break;
				case SKELETAL_HORSE:
				  result = "Skeletal Horse";
				  break;
				case SARYN:
				  result = "Saryn";
				  break;
				case FENNIN_RO:
				  result = "Fennin Ro";
				  break;
				case TORMENTOR:
				  result = "Tormentor";
				  break;
				case NECRO_PRIEST:
				  result = "Necro Priest";
				  break;
				case NIGHTMARE:
				  result = "Nightmare";
				  break;
				case NEW_RALLOS_ZEK:
				  result = "New Rallos Zek";
				  break;
				case VALLON_ZEK:
				  result = "Vallon Zek";
				  break;
				case TALLON_ZEK:
				  result = "Tallon Zek";
				  break;
				case AIR_MEPHIT:
				  result = "Air Mephit";
				  break;
				case EARTH_MEPHIT:
				  result = "Earth Mephit";
				  break;
				case FIRE_MEPHIT:
				  result = "Fire Mephit";
				  break;
				case NIGHTMARE_MEPHIT:
				  result = "Nightmare Mephit";
				  break;
				case ZEBUXORUK:
				  result = "Zebuxoruk";
				  break;
				case MITHANIEL_MARR:
				  result = "Mithaniel Marr";
				  break;
				case UNDEAD_KNIGHT:
				  result = "Undead Knight";
				  break;
				case THE_RATHE:
				  result = "The Rathe";
				  break;
				case XEGONY:
				  result = "Xegony";
				  break;
				case FIEND:
				  result = "Fiend";
				  break;
				case TEST_OBJECT:
				  result = "Test Object";
				  break;
				case CRAB:
				  result = "Crab";
				  break;
				case PHOENIX:
				  result = "Phoenix";
				  break;
				case POP_DRAGON:
				  result = "PoP Dragon";
				  break;
				case POP_BEAR:
				  result = "PoP Bear";
				  break;
				case STORM_TAARID:
				  result = "Storm Taarid";
				  break;
				case STORM_SATUUR:
				  result = "Storm Satuur";
				  break;
				case STORM_KURAALN:
				  result = "Storm Kuraaln";
				  break;
				case STORM_VOLAAS:
				  result = "Storm Volaas";
				  break;
				case STORM_MANA:
				  result = "Storm Mana";
				  break;
				case STORM_FIRE:
				  result = "Storm Fire";
				  break;
				case STORM_CELESTIAL:
				  result = "Storm Celestial";
				  break;
				case WAR_WRAITH:
				  result = "War Wraith";
				  break;
				case WRULON:
				  result = "Wrulon";
				  break;
				case KRAKEN:
				  result = "Kraken";
				  break;
				case POISON_FROG:
				  result = "Poison Frog";
				  break;
				case QUEZTOCOATAL:
				  result = "Queztocoatal";
				  break;
				case VALORIAN:
				  result = "Valorian";
				  break;
				case WAR_BOAR:
				  result = "War Boar";
				  break;
				case POP_EFREETI:
				  result = "PoP Efreeti";
				  break;
				case WAR_BOAR_UNARMORED:
				  result = "War Boar Unarmored";
				  break;
				case BLACK_KNIGHT:
				  result = "Black Knight";
				  break;
				case ANIMATED_ARMOR:
				  result = "Animated Armor";
				  break;
				case UNDEAD_FOOTMAN:
				  result = "Undead Footman";
				  break;
				case RALLOS_ZEK_MINION:
				  result = "Rallos Zek Minion";
				  break;
				case ARACHNID:
				  result = "Arachnid";
				  break;
				case CRYSTAL_SPIDER:
				  result = "Crystal Spider";
				  break;
				case ZEB_CAGE:
				  result = "Zeb Cage";
				  break;
				case BOT_PORTAL:
				  result = "Bot Portal";
				  break;
				case FROGLOK:
				  result = "Froglok";
				  break;
				case TROLL_BUCCANEER:
				  result = "Troll Buccaneer";
				  break;
				case TROLL_FREEBOOTER:
				  result = "Troll Freebooter";
				  break;
				case TROLL_SEA_ROVER:
				  result = "Troll Sea Rover";
				  break;
				case SPECTRE_PIRATE_BOSS:
				  result = "Spectre Pirate Boss";
				  break;
				case PIRATE_BOSS:
				  result = "Pirate Boss";
				  break;
				case PIRATE_DARK_SHAMAN:
				  result = "Pirate Dark Shaman";
				  break;
				case PIRATE_OFFICER:
				  result = "Pirate Officer";
				  break;
				case GNOME_PIRATE:
				  result = "Gnome Pirate";
				  break;
				case DARK_ELF_PIRATE:
				  result = "Dark Elf Pirate";
				  break;
				case OGRE_PIRATE:
				  result = "Ogre Pirate";
				  break;
				case HUMAN_PIRATE:
				  result = "Human Pirate";
				  break;
				case ERUDITE_PIRATE:
				  result = "Erudite Pirate";
				  break;
				case POISON_DART_FROG:
				  result = "Poison Dart Frog";
				  break;
				case TROLL_ZOMBIE:
				  result = "Troll Zombie";
				  break;
				case LUGGALD_LAND:
				  result = "Luggald Land";
				  break;
				case LUGGALD_ARMORED:
				  result = "Luggald Armored";
				  break;
				case LUGGALD_ROBED:
				  result = "Luggald Robed";
				  break;
				case LUGGALD_MOUNT:
				  result = "Luggald Mount";
				  break;
				case FROGLOK_SKELETON:
				  result = "Froglok Skeleton";
				  break;
				case UNDEAD_FROGLOK:
				  result = "Undead Froglok";
				  break;
				case CHOSEN_WARRIOR:
				  result = "Chosen Warrior";
				  break;
				case CHOSEN_WIZARD:
				  result = "Chosen Wizard";
				  break;
				case VEKSAR:
				  result = "Veksar";
				  break;
				case GREATER_VEKSAR:
				  result = "Greater Veksar";
				  break;
				case VEKSAR_BOSS:
				  result = "Veksar Boss";
				  break;
				case CHOKADAI:
				  result = "Chokadai";
				  break;
				case UNDEAD_CHOKADAI:
				  result = "Undead Chokadai";
				  break;
				case UNDEAD_VEKSAR:
				  result = "Undead Veksar";
				  break;
				default:
				  result = "UNKNOWN RACE";
				  break;
						}

			return result;
		}
	}
}