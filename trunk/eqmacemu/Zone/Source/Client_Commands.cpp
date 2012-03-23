//TODO: sep.IsNumber(split chr)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "config.h"
#include "client.h"
#include "net.h"
#include "database.h"
#include "mob.h"
#include "packet_functions.h"
#include "worldserver.h"
#include "zone.h"
#include "seperator.h"
#include "spdat.h"
#include "PlayerCorpse.h"
#include "SpellsHandler.hpp"
#include "projectile.h"
#include "SharedMemory.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "Client_Commands.h"

#ifdef EMBPERL
	#include "embparser.h"
#endif

extern Database			database;
extern Zone*			zone;
extern SpellsHandler	spells_handler;
extern WorldServer		worldserver;

float fdistance(float x1, float y1, float x2, float y2);

float square(float number);

//struct cl_struct *commandlist;	// the actual linked list of commands
int commandcount;								// how many commands we have

// this is the pointer to the dispatch function, updated once
// init has been performed to point at the real function
int (*command_dispatch)(Client *,char *)=command_notavail;


void command_bestz(Client *c, const Seperator *message);
void command_pf(Client *c, const Seperator *message);

map<string, CommandRecord *> commandlist;

//All allocated CommandRecords get put in here so they get deleted on shutdown
LinkedList<CommandRecord *> cleanup_commandlist;

// Harakiri for command mapping to perl
#ifdef EMBPERL_COMMANDS
XS(XS_command_add); /* prototype to pass -Wmissing-prototypes */
XS(XS_command_add)
{
    dXSARGS;
    if (items != 3)
        Perl_croak(aTHX_ "Usage: commands::command_add(name, desc, access)");

	char *name = SvPV_nolen(ST(0));
	char *desc = SvPV_nolen(ST(1));
	int	access = (int)SvIV(ST(2));

	command_add_perl(name, desc, access);

    XSRETURN_EMPTY;
}
#endif

/*
 * command_notavail
 * This is the default dispatch function when commands aren't loaded.
 *
 * Parameters:
 *	 not used
 *
 */
int command_notavail(Client *c, char *message)
{
	c->Message(RED, "Commands not available.");
	return -1;
}

/*****************************************************************************/
/*  the rest below here could be in a dynamically loaded module eventually   */
/*****************************************************************************/

/*

Access Levels:

0		Normal
10	* Steward *
20	* Apprentice Guide *
50	* Guide *
80	* QuestTroupe *
81	* Senior Guide *
85	* GM-Tester *
90	* EQ Support *
95	* GM-Staff *
100	* GM-Admin *
150	* GM-Lead Admin *
160	* QuestMaster *
170	* GM-Areas *
180	* GM-Coder *
200	* GM-Mgmt *
250	* GM-Impossible *

*/

/*
 * command_init
 * initializes the command list, call at startup
 *
 * Parameters:
 *	 none
 *
 * When adding a command, if it's the first time that function pointer is
 * used it is a new command.  If that function pointer is used for another
 * command, the command is added as an alias; description and access level
 * are not used and can be NULL.
 *
 */
int command_init(void) {

	int GM_MASTER_ACESSS = 250;
	int GM_MANAGEMENT_ACESSS = 200;
	int GM_ADMIN = 0;
	int NORMAL_ACESS = 0;
	if
	(	command_add("goto","[x] [y] [z] - Teleport to the provided coordinates or to your target",GM_MASTER_ACESSS,command_goto) ||
		command_add("level","[level] - Set your or your target's level",GM_MASTER_ACESSS,command_level) ||
		command_add("damage","[x] - Inflicts damage upon target.",EQC_Alpha_Tester,command_damage) ||
		command_add("heal","[x] - (PC only) Completely heals your target.",EQC_Alpha_Tester,command_heal) ||
		command_add("kill","Kills your target.",EQC_Alpha_Tester,command_kill) ||
		command_add("mana","(PC only) Replenishes your target\'s mana.",EQC_Alpha_Tester,command_mana) ||
		command_add("timeofday","Sets the date to Monday, Janurary 1st, 1 at the specified time temporary.",GM_MASTER_ACESSS,command_timeofday) ||

		// summonitem related
		command_add("summonitem","[itemid] [charges] - Summon an item onto your cursor.  Charges are optional.",EQC_Alpha_Tester,command_summonitem) ||
		command_add("si",NULL,EQC_Alpha_Tester,command_summonitem) ||

		command_add("summonitemnonblob","[itemid] [charges] - Summon an item onto your cursor.  Charges are optional.",EQC_Alpha_Tester,command_summonitemnonblob) ||
		command_add("si2",NULL,EQC_Alpha_Tester,command_summonitemnonblob) ||
		command_add("summonitem2",NULL,EQC_Alpha_Tester,command_summonitemnonblob) ||


		command_add("setexp","[value] - Set your experience",GM_ADMIN,command_setexp) ||
		command_add("addexp","[value] - Adds to your experience",GM_ADMIN,command_addexp) ||

		// itemsearch related
		command_add("itemsearch","[search criteria] - Search for an item",EQC_Alpha_Tester,command_itemsearch) ||
		command_add("search",NULL,EQC_Alpha_Tester,command_itemsearch) ||
		command_add("finditem",NULL,EQC_Alpha_Tester,command_itemsearch) ||
		command_add("fi",NULL,EQC_Alpha_Tester,command_itemsearch) ||

		command_add("zone","[zonename] - Zones to safepoint in the specified zone. This command only accepts proper zone names, i.e. \'freporte\' and \'cabeast\'.",EQC_Alpha_Tester,command_zone) ||

		command_add("loc","Shows you your current location.",EQC_Alpha_Tester,command_loc) ||
		command_add("npcstats","- Show stats about target NPC",GM_MANAGEMENT_ACESSS,command_npcstats) ||

		command_add("findspell","[searchstring] - Search for a spell",EQC_Alpha_Tester,command_findspell) ||
		command_add("spfind",NULL,EQC_Alpha_Tester,command_findspell) ||

		command_add("findrecipe","[searchstring] - Search for a receipe",EQC_Alpha_Tester,command_findreceipe) ||
		command_add("fr",NULL,EQC_Alpha_Tester,command_findreceipe) ||

		command_add("receipesummon","[receipeid] - Summon all components of a recipe",EQC_Alpha_Tester,command_receipesummon) ||
		command_add("rs",NULL,EQC_Alpha_Tester,command_receipesummon) ||

		command_add("clearcursor","clears clients cursor server side",EQC_Alpha_Tester,command_clearcursor) ||
		command_add("cc",NULL,EQC_Alpha_Tester,command_clearcursor) ||

		command_add("reloadperl","Reload Perl/Quests",EQC_Alpha_Tester,command_reloadperl) ||
		command_add("reloadquests",NULL,EQC_Alpha_Tester,command_reloadperl) ||

		command_add("diffitem","[itemid] compares blob item with nonblob item",EQC_Alpha_Tester,command_diffitem) ||
		command_add("di",NULL,EQC_Alpha_Tester,command_diffitem) ||

		command_add("translocate","[zone] ([x] [y] [z]) translocates you to the specific parameters",EQC_Alpha_Tester,command_translocate) ||

		command_add("givemoney","[copper] [silver] [gold] [plat] - Gives specified amount of money to the target player.",GM_MANAGEMENT_ACESSS,command_givemoney) ||
		command_add("money",NULL,GM_MANAGEMENT_ACESSS,command_givemoney) ||

		command_add("castspell","[id] Cast spell on target",GM_MANAGEMENT_ACESSS,command_castspell) ||
		command_add("cast",NULL,GM_MANAGEMENT_ACESSS,command_castspell) ||

		command_add("invulnerable","Make target invulnerable",GM_MANAGEMENT_ACESSS,command_invulnerable) ||
		command_add("invul",NULL,GM_MANAGEMENT_ACESSS,command_invulnerable) ||

		command_add("listlang","List all languages and their ids",GM_MANAGEMENT_ACESSS,command_listlang) ||

		command_add("setlang","[id] Sets the languages skill value",GM_MANAGEMENT_ACESSS,command_setlang) ||

		command_add("setskill","[id] Sets the skill value",GM_MANAGEMENT_ACESSS,command_setskill) ||

		command_add("setskillall","Sets all skills to value",GM_MANAGEMENT_ACESSS,command_setskillall) ||

		command_add("checkskillall","Checks all skills of the target",GM_MANAGEMENT_ACESSS,command_checkskillall) ||

		command_add("save","Manually save target",GM_MANAGEMENT_ACESSS,command_save) ||

		command_add("scribespells","[1-60] - Scribes all spells for your class to desired level.",GM_MANAGEMENT_ACESSS,command_scribespells) ||

		command_add("flymode","[0|1] target can fly",GM_MANAGEMENT_ACESSS,command_flymode) ||

		command_add("depopzone","Removes all NPCS in this zone",GM_MANAGEMENT_ACESSS,command_depopzone) ||

		command_add("repopzone","Respawns all NPCS in this zone",GM_MANAGEMENT_ACESSS,command_repopzone) ||

		command_add("sky","Changes the sky",GM_MANAGEMENT_ACESSS,command_sky) ||

		command_add("fogcolor","<red> <green> <blue>",GM_MANAGEMENT_ACESSS,command_fogcolor) ||

		command_add("zoneappearance","Lists the intended zone appearance variables",GM_MANAGEMENT_ACESSS,command_zoneappearance) ||

		command_add("zoneclip","<minclip> <maxclip>",GM_MANAGEMENT_ACESSS,command_zoneclip) ||

		command_add("debug","[1|0] - Enable additional output",GM_MANAGEMENT_ACESSS,command_debug) ||

		command_add("help","[search term] - List available commands and their description, specify partial command as argument to search",NORMAL_ACESS,command_help)

		)
	{
		command_deinit();
		return -1;
	}

	map<string, CommandRecord *>::iterator cur,end;
	cur = commandlist.begin();
	end = commandlist.end();
	/*map<string,uint8> command_settings;
	map<string,uint8>::iterator itr;
	database.GetCommandSettings(command_settings);
	for(; cur != end; cur++) {
		if ((itr=command_settings.find(cur->first))!=command_settings.end())
		{
			cur->second->access = itr->second;
#if EQDEBUG >=5
			EQC::Common::Log(EQCLog::Debug,CP_CLIENT, "command_init(): - Command '%s' set to access level %d." , cur->first.c_str(), itr->second);
#endif
		}
		else
		{
#ifdef COMMANDS_WARNINGS
			if(cur->second->access == 0)
				EQC::Common::Log(EQCLog::Debug,CP_CLIENT, "command_init(): Warning: Command '%s' defaulting to access level 0!" , cur->first.c_str());
#endif
		}
	}*/

	command_dispatch = command_realdispatch;

	return commandcount;
}

/*
 * command_deinit
 * clears the command list, freeing resources
 *
 * Parameters:
 *	 none
 *
 */
void command_deinit(void)
{

	commandlist.clear();

	command_dispatch = command_notavail;
	commandcount = 0;
}

/*
 * command_add
 * adds a command to the command list; used by command_init
 *
 * Parameters:
 *	 command_string	- the command ex: "spawn"
 *	 desc		- text description of command for #help
 *	 access		- default access level required to use command
 *	 function		- pointer to function that handles command
 *
 */
int command_add(const char *command_string, const char *desc, int access, CmdFuncPtr function)
{
	if(function == NULL)
		return(-1);

	string cstr(command_string);

	if(commandlist.count(cstr) != 0) {
		EQC::Common::Log(EQCLog::Error,CP_CLIENT, "command_add() - Command '%s' is a duplicate - check Client_Commands.cpp." , command_string);
		return(-1);
	}

	//look for aliases...
	map<string, CommandRecord *>::iterator cur,end,del;
	cur = commandlist.begin();
	end = commandlist.end();
	for(; cur != end; cur++) {
		if(cur->second->function == function) {
			int r;
			for(r = 1; r < CMDALIASES; r++) {
				if(cur->second->command[r] == NULL) {
					cur->second->command[r] = command_string;
					break;
				}
			}
			commandlist[cstr] = cur->second;
			return(0);
		}
	}

	CommandRecord *c = new CommandRecord;
	cleanup_commandlist.Append(c);
	c->desc = desc;
	c->access = access;
	c->function = function;
	memset(c->command, 0, sizeof(c->command));
	c->command[0] = command_string;

	commandlist[cstr] = c;

	commandcount++;
	return 0;
}

/*
 *
 * command_realdispatch
 * Calls the correct function to process the client's command string.
 * Called if message starts with command character (#).
 *
 * Parameters:
 *	 c			- pointer to the calling client object
 *	 message		- what the client typed
 *
 */
int command_realdispatch(Client *c, char *message)
{
    Seperator sep(message, ' ', 10, 100, true); //changed by Eglin: "three word argument" should be considered 1 arg

	command_logcommand(c, message);

	string cstr(sep.arg[0]+1);

	if(commandlist.count(cstr) != 1) {
		c->Message(RED, "Command '%s' not recognized.", sep.arg[0]+1);
		return(-1);
	}

	CommandRecord *cur = commandlist[cstr];
	if(c->Admin() < cur->access){
		c->Message(RED,"Your access level is not high enough to use this command.");
		return(-1);
	}

#ifdef COMMANDS_LOGGING
	if(cur->access >= COMMANDS_LOGGING_MIN_STATUS) {
		EQC::Common::Log(EQCLog::Debug,CP_CLIENT, "%s (%s) used command: %s (target=%s)", c->GetName(), c->AccountName(), message, c->GetTarget()?c->GetTarget()->GetName():"NONE");
	}
#endif

	if(cur->function == NULL) {
#ifdef EMBPERL_COMMANDS
		//dispatch perl command
		perlParser->ExecCommand(c, &sep);
#else
		EQC::Common::Log(EQCLog::Error,CP_CLIENT, "Command '%s' has a null function, but perl commands are diabled!\n", cstr.c_str());
		return(-1);
#endif
	} else {
		//dispatch C++ command
		cur->function(c, &sep);	// dispatch command
	}
	return 0;

}


void command_logcommand(Client *c, char *message)
{
	/*
	int admin=c->Admin();

	bool continueevents=false;
	switch (zone->loglevelvar){ //catch failsafe
		case 9: { // log only LeadGM
			if ((admin>= 150) && (admin <200))
				continueevents=true;
			break;
		}
		case 8: { // log only GM
			if ((admin>= 100) && (admin <150))
				continueevents=true;
			break;
		}
		case 1: {
			if ((admin>= 200))
				continueevents=true;
			break;
		}
		case 2: {
			if ((admin>= 150))
				continueevents=true;
			break;
		}
		case 3: {
			if ((admin>= 100))
				continueevents=true;
			break;
		}
		case 4: {
			if ((admin>= 80))
				continueevents=true;
			break;
		}
		case 5: {
			if ((admin>= 20))
				continueevents=true;
			break;
		}
		case 6: {
			if ((admin>= 10))
				continueevents=true;
			break;
		}
		case 7: {
				continueevents=true;
				break;
		}
	}

	if (continueevents)
		database.logevents(
			c->AccountName(),
			c->AccountID(),
			admin,c->GetName(),
			c->GetTarget()?c->GetTarget()->GetName():"None",
			"Command",
			message,
			1
		);*/
}

#ifdef EMBPERL_COMMANDS
/*
 * command_add_perl
 * adds a command to the command list, as a perl function
 *
 * Parameters:
 *	 command_string	- the command ex: "spawn"
 *	 desc		- text description of command for #help
 *	 access		- default access level required to use command
 *
 */
int command_add_perl(const char *command_string, const char *desc, int access) {
	string cstr(command_string);

	if(commandlist.count(cstr) != 0) {
#ifdef COMMANDS_PERL_OVERRIDE
		//print a warning so people dont get too confused when this happens
		EQC::Common::Log(EQCLog::Warn, CP_PERL, "command_add_perl() - Perl Command '%s' is overriding the compiled command." , command_string);
		CommandRecord *tmp = commandlist[cstr];
		safe_delete(tmp);
#else
		EQC::Common::Log(EQCLog::Error, CP_PERL, "command_add_perl() - Command '%s' is a duplicate - check commands.pl." , command_string);
		return(-1);
#endif
	}

	CommandRecord *c = new CommandRecord;
	c->desc = desc;
	c->access = access;
	c->function = NULL;

	commandlist[cstr] = c;

	commandcount++;
	return 0;

}

//clear out any perl commands.
//should restore any overridden C++ commands, but thats a lot of work.
void command_clear_perl() {
	map<string, CommandRecord *>::iterator cur,end,del;
	cur = commandlist.begin();
	end = commandlist.end();
	for(; cur != end;) {
		del = cur;
		cur++;
		if(del->second->function == NULL) {
			safe_delete(del->second);
			commandlist.erase(del);
		}
	}
}

#endif //EMBPERL_COMMANDS

void command_help(Client *c, const Seperator *sep)
{
	int commands_shown=0;

	c->Message(BLACK, "Available EQC commands for access level %d :",c->Admin());

	map<string, CommandRecord *>::iterator cur,end;
	cur = commandlist.begin();
	end = commandlist.end();

	for(; cur != end; cur++) {
		if(sep->arg[1][0]) {
			if(cur->first.find(sep->arg[1]) == string::npos) {
				continue;
			}
		}

		if(c->Admin() < cur->second->access)
			continue;
  		commands_shown++;
		c->Message(BLACK, "%c%s %s", COMMAND_CHAR, cur->first.c_str(), cur->second->desc == NULL?"":cur->second->desc);
	}
	c->Message(BLACK, "%d command%s listed.", commands_shown, commands_shown!=1?"s":"");

}

void command_goto(Client *c, const Seperator *sep)
{
		int32 zoneid = 0;
		if (sep->arg[1][0] == 0 && c->GetTarget() != 0) {
			c->MovePC(zoneid, c->GetTarget()->GetX(), c->GetTarget()->GetY(), c->GetTarget()->GetZ(), false, false);
		}
		else if (!(sep->IsNumber(1) && sep->IsNumber(2) && sep->IsNumber(3))) {
			c->Message(BLACK, "Usage: #goto [x y z].");
		}
		else {
			c->MovePC(zoneid, atof(sep->arg[2]), atof(sep->arg[1]), atof(sep->arg[3]), false, false);
		}
}

void command_level(Client *c, const Seperator *sep)
{
		if (c->GetTarget() == 0)
		{
			c->Message(BLACK, "Error: #Level: No target.");
		}
		else if (sep->arg[1][0] == 0)
		{
			c->Message(BLACK, "Usage: #level x (between 1 and %i).", MAX_PLAYERLEVEL);
		}
		else
		{
			int16 level = atoi(sep->arg[1]);


			if((c->GetTarget()->IsClient()) &&  ( (level <= 0) || (level > MAX_PLAYERLEVEL) ) )
			{
				c->Message(BLACK, "Usage: #level x (between 1 and %i).", MAX_PLAYERLEVEL);
				return;
			}

			if( (c->GetTarget()->IsNPC()) && ( (level <= 0) ||(level > MAX_NPCLEVEL) ) )
			{
				c->Message(BLACK, "Usage: #level x (NPC level is between 1 and %i).", MAX_NPCLEVEL);
				return;
			}
			if (c->GetTarget()->IsClient()) {
				int32 supposed_exp = c->GetTarget()->CastToClient()->GetEXPForLevel(level);
				c->GetTarget()->CastToClient()->SetEXP(supposed_exp + 1);
			}
			else {
				c->GetTarget()->SetLevel(level);
				c->GetTarget()->Save();
			}
		}

}
void command_damage(Client *c, const Seperator *sep)
{
		if (c->GetTarget()==0)
		{
			c->Message(BLACK, "Error: #damage: No Target.");
		}
		else if (!sep->IsNumber(1))
		{
			c->Message(BLACK, "Usage: #damage x.");
		}
		else
		{
			sint32 nkdmg = atoi(sep->arg[1]);

			if (nkdmg > MAX_DAMAGE || nkdmg < MIN_DAMAGE)
			{
				c->Message(BLACK, "You must enter a number greater than 0 and less than 32,000.");
			}
			else
			{
				c->GetTarget()->Damage(c, nkdmg, 0xffff);
			}
		}
}
void command_heal(Client *c, const Seperator *sep)
{
		if (c->GetTarget()==0)
		{
			c->Message(BLACK, "Error: #Heal: No Target.");
		}
		else
		{
			c->GetTarget()->Heal();
		}
}

void command_mana(Client *c, const Seperator *sep)
{
	if (c->GetTarget() == 0)
		{
			// TODO: Seems although items are in the mana calculation, it doesn't
			// factor them in.
			c->SetMana(c->CalcMaxMana());
		}
		else
		{
			c->GetTarget()->SetMana(c->GetTarget()->GetMaxMana());
		}
}

void command_kill(Client *c, const Seperator *sep)
{
		if (c->GetTarget()==0)
		{
			c->Message(BLACK, "Error: #kill: No target.");
		}
		else
		{
			if ((!c->GetTarget()->IsClient()) || c->GetTarget()->CastToClient()->Admin() < c->Admin())
			{
				c->GetTarget()->Kill();
			}
		}
}
void command_timeofday(Client *c, const Seperator *sep)
{
		if (!sep->IsNumber(1) || atoi(sep->arg[1]) <= 0 || atoi(sep->arg[1]) >= 25)
		{
			c->Message(BLACK, "Usage: #timeofday <hour>");
		}
		else
		{
			APPLAYER* timepacket = c->CreateTimeOfDayPacket(atoi(sep->arg[1]),0,1,1,1);
			entity_list.QueueClients(c, timepacket);
			safe_delete(timepacket);//delete timepacket;
		}
}

void command_setexp(Client *c, const Seperator *sep)

{
		if (sep->IsNumber(1)) {
			if (atoi(sep->arg[1]) > MAX_PC_EXPERIANCE)
				c->Message(BLACK, "Error: SetEXP: Value too high.");
			else
				c->SetEXP (atoi(sep->arg[1]));
		}
		else
			c->Message(BLACK, "Usage: #setexp number");
}

void command_addexp(Client *c, const Seperator *sep)
{
		if (sep->IsNumber(1)) {

			if (atoi(sep->arg[1]) > MAX_PC_EXPERIANCE)
				c->Message(BLACK, "Error: AddEXP: Value too high.");
			else
				c->AddEXP (atoi(sep->arg[1]));
		}
		else
			c->Message(BLACK, "Usage: #addexp number");
}

void command_summonitem(Client *c, const Seperator *sep)
{
	if (!sep->IsNumber(1)) {
			c->Message(BLACK, "Usage: #summonitem x , x is an item number");
	}
	else {
			int16 itemid = atoi(sep->arg[1]);
			if (c->Admin() < 100 && ((itemid >= 32768) || (itemid >= 19900 && itemid <= 19943) || (itemid >= 31814 && itemid <= 31815) || (itemid >= 19917 && itemid <= 19928) || (itemid >= 11500 && itemid <= 11535) || (itemid >=32740 && itemid <=32758))) { 					c->Death(c, 0);
			}
			else
				c->SummonItem(itemid,1);
	}
}

void command_itemsearch(Client *c, const Seperator *sep)
{
		if (sep->arg[1][0] == 0)
			c->Message(BLACK, "Usage: #itemsearch [search string]");
		else
		{
			const char *search_criteria=sep->argplus[1];

			const Item_Struct* item = 0;
			if (Seperator::IsNumber(search_criteria)) {
				item = Database::Instance()->GetItem(atoi(search_criteria));
				if (item)
					c->Message(BLACK, "  %i: %s", (int) item->item_nr, item->name);
				else
					c->Message(BLACK, "Item #%s not found", search_criteria);
				return;
			}
	//#ifdef SHAREMEM
			int count=0;
			//int iSearchLen = strlen(search_criteria)+1;
			char sName[64];
			char sCriteria[255];
			strncpy(sCriteria, search_criteria, sizeof(sCriteria));
			_strupr(sCriteria);
			char* pdest;
			// -Cofruben: changing to shared memory method.
#ifndef EQC_SHAREDMEMORY
			for (int i=0; i < Database::Instance()->max_item; i++)
			{
				if (Database::Instance()->item_array[i] != 0)
				{
					item = (Item_Struct*)Database::Instance()->item_array[i];
#else
			for (int i=0; i < SharedMemory::getMaxItem(); i++) {
				{
					item = SharedMemory::getItem(i);
#endif
					strncpy(sName, item->name, sizeof(sName));
					_strupr(sName);
					pdest = strstr(sName, sCriteria);
					if (pdest != NULL) {
						c->Message(BLACK, "  %i: %s", (int) item->item_nr, item->name);
						count++;
					}
					if (count == 20)
						break;
				}
			}
			if (count == 20)
				c->Message(BLACK, "20 items shown...too many results.");
			else
				c->Message(BLACK, "%i items found", count);
	//#endif
		}
	}

void command_zone(Client *c, const Seperator *sep)
{
	uint16 zoneid = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	if (sep->IsNumber(1))
	{
		zoneid = atoi(sep->arg[1]);
		char* shortname = Database::Instance()->GetZoneName(zoneid);
		if(shortname = 0)
		{
			c->Message(RED, "Invalid Zone ID: %i.", zoneid);
			return;
		}
	}
	if (!sep->IsNumber(1))
	{
		zoneid = Database::Instance()->LoadZoneID(sep->arg[1]);
		if(zoneid == 0)
		{
			c->Message(RED, "Invalid Zone Name.");
			return;
		}
	}
	if (sep->IsNumber(2) && sep->IsNumber(3) && sep->IsNumber(4))
	{
			x = atof(sep->arg[3]);
			y = atof(sep->arg[2]);
			z = atof(sep->arg[4]);
			c->SetZoningX(x);
			c->SetZoningY(y);
			c->SetZoningZ(z);
			cerr << "Got a zone request for ID: " << zoneid << " x: " << x  << " y: " << y << " z: " << z << endl;
	}
	else if (sep->arg[1][0] == 0)
	{
		c->Message(BLACK, "Usage: #zone [zonename]");
		c->Message(BLACK, "Optional Usage: #zone [zonename] y x z (heading)");
		return;
	}
	else
	{
		if(Database::Instance()->GetSafePointsByID(zoneid, &x, &y, &z, 0, 0))
		{
		c->SetZoningX((sint32)x);
		c->SetZoningY((sint32)y);
		c->SetZoningZ((sint32)z);
		cerr << "Got a zone request using safe points for ID: " << zoneid << " x: " << x  << " y: " << y << " z: " << z << endl;
		}
		else
		{
			c->Message(RED, "That zone is not currently available. ID: ", zoneid);
			return;
		}
	}
	c->SetUsingSoftCodedZoneLine(false);
	c->SetIsZoning(true);
	c->SetHeading(0.0f);
	c->Message(BLACK, "Got a zone request for %i", zoneid);
	c->MovePC(zoneid, x, y, z, true, false);
}


void command_loc(Client *c, const Seperator *sep)
{
		if (c->GetTarget() != 0)
		{
			//Changed back. Screwed things up more -Wizzel
			c->Message(BLACK, "%s's Location: %1.1f, %1.1f, %1.1f, h=%1.1f", c->GetTarget()->GetName(), c->GetTarget()->GetY(), c->GetTarget()->GetX(), c->GetTarget()->GetZ(), c->GetTarget()->GetHeading());
		}
		else
		{
			c->Message(BLACK, "Current Location: %1.1f, %1.1f, %1.1f, h=%1.1f", c->GetY(), c->GetX(), c->GetZ(), c->GetHeading());
		}
}

void command_npcstats(Client *c, const Seperator *sep)
{
		if (c->GetTarget() == 0)
			c->Message(BLACK, "ERROR: No target!");
		else if (!c->GetTarget()->IsNPC())
			c->Message(BLACK, "ERROR: Target is not a NPC!");
		else {
			c->Message(BLACK, "NPC Stats:");
			c->Message(BLACK, "  Name: %s",c->GetTarget()->GetName());
			//Message(BLACK, "  Last Name: %s",sep.arg[2]);
			c->Message(BLACK, "  Race: %i",c->GetTarget()->GetRace());
			c->Message(BLACK, "  Level: %i",c->GetTarget()->GetLevel());
			c->Message(BLACK, "  Material: %i",c->GetTarget()->GetTexture());
			c->Message(BLACK, "  Class: %i",c->GetTarget()->GetClass());
			c->Message(BLACK, "  Current HP: %i", c->GetTarget()->GetHP());
			c->Message(BLACK, "  Max HP: %i", c->GetTarget()->GetMaxHP());
			//Message(BLACK, "Weapon Item Number: %s",target->GetWeapNo());
			c->Message(BLACK, "  Gender: %i",c->GetTarget()->GetGender());
			c->GetTarget()->CastToNPC()->QueryLoot(c);
		}
}

void command_findspell(Client *c, const Seperator *sep)
{
		if (sep->arg[1][0] == 0)
			c->Message(BLACK, "Usage: #FindSpell [spellname]");
		else if (!spells_handler.SpellsLoaded())
			c->Message(BLACK, "Spells not loaded");
		else if (Seperator::IsNumber(sep->argplus[1])) {
			int spellid = atoi(sep->argplus[1]);
			if (spellid <= 0 || spellid >= SPDAT_RECORDS) {
				c->Message(BLACK, "Error: Number out of range");
			}
			else {
				c->Message(BLACK, "  %i: %s", spellid, spells_handler.GetSpellPtr(spellid)->GetSpellName());
			}
		}
		else {
			int count=0;
			int iSearchLen = strlen(sep->argplus[1])+1;
			char sName[64];
			char sCriteria[65];
			strncpy(sCriteria, sep->argplus[1], 64);
			_strupr(sCriteria);
			for (int i = 0; i < SPDAT_RECORDS; i++)
			{
				const char* name = spells_handler.GetSpellPtr(i)->GetSpellName();
				if (name[0] != 0) {
					strcpy(sName, name);

					_strupr(sName);
					char* pdest = strstr(sName, sCriteria);
					if ((pdest != NULL) && (count <=20)) {
						c->Message(BLACK, "  %i: %s", i, name);
						count++;
					}
					else if (count > 20)
						break;
				}
			}
			if (count > 20)
				c->Message(BLACK, "20 spells found... max reached.");
			else
				c->Message(BLACK, "%i spells found.", count);
		}

}

void command_findreceipe(Client *c, const Seperator *sep)
{
		if (sep->arg[1][0] == 0)
			c->Message(BLACK, "Usage: #findreceipe [search string]");
		else
		{
			const char *search_criteria=sep->argplus[1];

			 vector<DBTradeskillRecipe_Struct*> specList;

			bool result = Database::Instance()->SearchTradeRecipe(search_criteria,0,&specList);

			if(!result) {
					c->Message(BLACK, "No recipes found");
				return;
			}

			c->Message(BLACK, "Found %i Recipes", specList.size());

				 for (int i=0; i<specList.size();i++) {

					 c->Message(BLACK, "Recipe %i: %s tradeskill: %i trivial: %i", specList[i]->recipeID, specList[i]->name,specList[i]->tradeskill, specList[i]->trivial);

					std::stringstream stringstream;

					vector< pair<uint32,uint8> >::iterator	itr =  specList[i]->oncombine.begin();

					while(itr !=  specList[i]->oncombine.end()) {

						const Item_Struct* item = 0;

						item = Database::Instance()->GetItem(itr->first);

						int second = itr->second;

						if(second!=0) {
							stringstream << second << " x ";
						}
						if(item!=0) {
							stringstream << item->name << " (" << itr->first << ")";
						} else {
							stringstream << " UNKNOWN (" << itr->first << ")";
						}

						stringstream << "\n";
						itr++;
					}

					c->Message(BLACK, "%s", stringstream.str().c_str());

					if(i == 19) {
						c->Message(BLACK, "Search result has been limit to 20 entries");
					}
				}

		}
}

void command_receipesummon(Client *c, const Seperator *sep)
{
		if (sep->arg[1][0] == 0)
			c->Message(BLACK, "Usage: #receipesummon <recipeid>");
		else
		{
			int recipeID=atoi(sep->argplus[1]);

			 vector<DBTradeskillRecipe_Struct*> specList;

			bool result = Database::Instance()->SearchTradeRecipe(0,recipeID,&specList);

			if(!result) {
				c->Message(BLACK, "No items found");
				return;
			}

			c->Message(BLACK, "Summoning Recipe Items");

				 for (int i=0; i<1;i++) {

			 		vector< pair<uint32,uint8> >::iterator	itr =  specList[i]->oncombine.begin();

					while(itr !=  specList[i]->oncombine.end()) {

						c->SummonItem(itr->first, itr->second);
						itr++;
					}
				}

		}
}


void command_clearcursor(Client *c, const Seperator *sep)
{

		c->Message(BLACK, "Clearing player cursor items server side...");

		if (c->GetTarget() != 0 && c->GetTarget()->IsClient()) {
				c->GetTarget()->CastToClient()->GetPlayerProfilePtr()->inventory[0] = 0xFFFF;
		} else {
			c->GetPlayerProfilePtr()->inventory[0] = 0xFFFF;
		}
}

void command_reloadperl(Client *c, const Seperator *sep)
{
		c->Message(BLACK, "Reloading Perl/Quests...");

		#ifdef EMBPERL
			perlParser->ReloadQuests();
		#endif
}

void command_summonitemnonblob(Client *c, const Seperator *sep)
{
		if (!sep->IsNumber(1)) {
			c->Message(BLACK, "Usage: #summonitem2 x , x is an item number");
		}
		else {
			int16 itemid = atoi(sep->arg[1]);
			c->SummonItemNonBlob(itemid);
		}
}

void command_diffitem(Client *c, const Seperator *sep)
{
		if (!sep->IsNumber(1)) {
			c->Message(BLACK, "Usage: #diffitem x , x is an item number");
		}
		else {
			int16 itemid = atoi(sep->arg[1]);
			Item_Struct* itemBlob = Database::Instance()->GetItem(itemid);
			Item_Struct* item = Database::Instance()->GetItemNonBlob(itemid);

			if (itemBlob == 0) {
				c->Message(BLACK, "No such item: %i", itemid);
			}

			APPLAYER* outapp = new APPLAYER(OP_SummonedItem, sizeof(SummonedItem_Struct));
			memcpy(outapp->pBuffer, item, sizeof(Item_Struct));

			APPLAYER* outappBlob = new APPLAYER(OP_SummonedItem, sizeof(SummonedItem_Struct));
			memcpy(outappBlob->pBuffer, itemBlob, sizeof(Item_Struct));

			for(int i=0; i < sizeof(Item_Struct);i++) {

				// dont show diff for name, price , class, races
				if(outappBlob->pBuffer[i] == outapp->pBuffer[i] || i < 100 || i == 140 || i == 141 || i == 142 || i == 143 || i == 208 || i == 209 || i == 212 || i == 213) {
				} else {
					char *unknownData = 0;

					MakeAnyLenString(&unknownData,"");

					//unknown0144
					if(i>=144 && i<172) {
						MakeAnyLenString(&unknownData,"(unknown0144)");
					}
					if(i==196) {
						MakeAnyLenString(&unknownData,"(clicklevel2)");
					}

					if(i>=222 && i<232) {
						MakeAnyLenString(&unknownData,"(unknown0222)");
					}

					c->Message(BLACK, "diff pos %i blob %02X nonblob %02X %s", i, (unsigned char)outappBlob->pBuffer[i],(unsigned char)outapp->pBuffer[i],unknownData);
					EQC::Common::Log(EQCLog::Debug,CP_CLIENT,"diff pos %i blob %02X nonblob %02X %s", i, (unsigned char)outappBlob->pBuffer[i],(unsigned char)outapp->pBuffer[i],unknownData);
				}

			}
		}
	}

void command_translocate(Client *c, const Seperator *sep)
{

		if (sep->arg[1][0] == 0)
		{
			c->Message(BLACK, "Usage: #translocate [zonename] ([x] [y] [z])");
		}
		else  {

			float x = 0;
			float y = 0;
			float z = 0;

			if (sep->IsNumber(2) && sep->IsNumber(3) && sep->IsNumber(3)) {
				x = atof(sep->arg[2]);
				y = atof(sep->arg[3]);
				z = atof(sep->arg[4]);
			}

			c->Message(BLACK, "Translocating you to zone name = %s, x = %f, y = %f, z = %f", sep->arg[1], x, y, z);

			c->TranslocatePC(sep->arg[1], x, y, z);
		}

}

void command_givemoney(Client *c, const Seperator *sep)
{

	if(sep->arg[1][0]==0 && sep->arg[2][0]==0 && sep->arg[3][0]==0 && sep->arg[4][0]==0) {
		c->Message(BLACK,"FORMAT: #money <copper> <silver> <gold> <plat>");
	}
	else {
		int16 plat = atoi(sep->arg[4]);
		int16 gold = atoi(sep->arg[3]);
		int16 silver = atoi(sep->arg[2]);
		int16 copper = atoi(sep->arg[1]);
		if( c->GetTarget() != 0 && c->GetTarget()->IsClient()){
			 c->GetTarget()->CastToClient()->AddMoneyToPP(copper, silver, gold, plat,false);
			c->GetTarget()->Message(BLACK, "Your coin purse feels heavier..., please zone");
		}else{
			c->AddMoneyToPP(copper, silver, gold, plat,false);
			c->Message(BLACK, "Your coin purse feels heavier..., please zone");
		}
	}
}

void command_castspell(Client *c, const Seperator *sep)
{
		Spell* spell = NULL;
		int16 spellid = 0;
		if (!sep->IsNumber(1)) {
			if (strlen(sep->argplus[1]) < 4 || strlen(sep->argplus[1]) > 62) {
				c->Message(BLACK, "Error: #CastSpell: Spell name incorrect.");
			}
			char sName[64]; memset(sName, 0, sizeof(sName));
			strcpy(sName, sep->argplus[1]);
			spell = spells_handler.GetSpellByName(sName);
		}
		else {
			spellid = atoi(sep->arg[1]);
			spell = spells_handler.GetSpellPtr(spellid);
			if (spellid >= (SPDAT_RECORDS + NUMBER_OF_CUSTOM_SPELLS) || !spell)
				c->Message(BLACK, "Error: #CastSpell: Arguement out of range.");
		}
		if (spell) {
			spellid = spell->GetSpellID();
			if ((spellid == 982 || spellid == 905) && c->Admin() < 100)
				c->SetTarget(c);
			c->SetCastingSpellLocationX(c->GetX());
			c->SetCastingSpellLocationY(c->GetY());
			c->SpellFinished(spell, ((c->GetTarget() == 0) ? 0 : c->GetTarget()->GetID()) );
		}
		else
			c->Message(BLACK, "Error: #CastSpell: Spell not found.");
}

void command_invulnerable(Client *c, const Seperator *sep)
{
		Client* client = c;
		if (c->GetTarget()) {
			if (c->GetTarget()->IsClient())
				client = c->GetTarget()->CastToClient();
		}
		if (sep->arg[1][0] == '1') {
			client->Message(BLACK, "You are now invulnerable from attack and spells.");
			client->SetInvulnerable(true);
			client->SetSpellImmunity(true);
		}
		else if (sep->arg[1][0] == '0') {
			client->Message(BLACK, "You are no longer invulnerable from attack and spells.");
			client->SetInvulnerable(false);
			client->SetSpellImmunity(false);
		}
		else
			client->Message(BLACK, "Usage: #invulnerable [1/0]");
	}


void command_listlang(Client *c, const Seperator *sep)
{
		for(int i=LANGUAGE_COMMON_TONGUE; i <= LANGUAGE_DARK_SPEECH;i++) {
			c->Message(BLACK, "%i %s",i,GetLanguageName(i));
		}
}

void command_setlang(Client *c, const Seperator *sep)
{
		if (c->GetTarget() == 0 || !c->GetTarget()->IsClient()) {
			c->Message(BLACK, "Error: #setlang: No valid target.");
		}
		else if (!sep->IsNumber(1) || atoi(sep->arg[1]) < 0 || atoi(sep->arg[1]) > 23) {
			c->Message(BLACK, "Usage: #setlang language x ");
			c->Message(BLACK, "       language = 0 to 23 use #listlang for possible values");
			c->Message(BLACK, "       x = 0 to 100");
			c->Message(BLACK, "NOTE: skill values greater than 250 may cause the skill to become unusable on the client.");
		}
		else if (!sep->IsNumber(2) || atoi(sep->arg[2]) < 0 || atoi(sep->arg[2]) > 100) {
			c->Message(BLACK, "Usage: #setlang language x ");
			c->Message(BLACK, "       language = 0 to 23 use #listlang for possible values");
			c->Message(BLACK, "       x = 0 to 100");
		}
		else {
			cout << "Setting " << c->GetTarget()->GetName() << " language " << sep->arg[1] << " to " << sep->arg[2] << endl;
			int languageID = atoi(sep->arg[1]);
			int8 skillVal = (int8)atoi(sep->arg[2]);
			c->GetTarget()->CastToClient()->SetLanguageSkill(languageID,skillVal);
			c->GetTarget()->CastToClient()->Save();
			c->Message(BLACK, "Please zone/logout to update the clients language skill!");
		}
	}

void command_setskill(Client *c, const Seperator *sep)
{

		if (c->GetTarget() == 0) {
			c->Message(BLACK, "Error: #setskill: No target.");
		}
		else if (!sep->IsNumber(1) || atoi(sep->arg[1]) < 0 || atoi(sep->arg[1]) > 73) {
			c->Message(BLACK, "Usage: #setskill skill x ");
			c->Message(BLACK, "       skill = 0 to 73");
			c->Message(BLACK, "       x = 0 to 255");
			c->Message(BLACK, "NOTE: skill values greater than 250 may cause the skill to become unusable on the client.");
		}
		else if (!sep->IsNumber(2) || atoi(sep->arg[2]) < 0 || atoi(sep->arg[2]) > 255) {
			c->Message(BLACK, "Usage: #setskill skill x ");
			c->Message(BLACK, "       skill = 0 to 73");
			c->Message(BLACK, "       x = 0 to 255");
		}
		else {
			//pp.skills[atoi(sep.arg[1])] = (int8)atoi(sep.arg[2]);
			cout << "Setting " << c->GetTarget()->GetName() << " skill " << sep->arg[1] << " to " << sep->arg[2] << endl;
			int skill_num = atoi(sep->arg[1]);
			int8 skill_id = (int8)atoi(sep->arg[2]);
			c->GetTarget()->SetSkill(skill_num, skill_id);
		}
	}

void command_setskillall(Client *c, const Seperator *sep)
{
		if (c->GetTarget() == 0 || !c->GetTarget()->IsClient()) {
			c->Message(BLACK, "Error: #setskillall: No client targeted.");
		}
		else if (!sep->IsNumber(1) || atoi(sep->arg[1]) < 0 || atoi(sep->arg[1]) > 252) {
			c->Message(BLACK, "Usage: #setskillall value ");
			c->Message(BLACK, "       value = 0 to 252");
		}
		else {
			//pp.skills[atoi(sep.arg[1])] = (int8)atoi(sep.arg[2]);
			cout << "Setting ALL of " << c->GetTarget()->GetName() << "'s skills to " << sep->arg[1] << endl;
			int8 setNumber = atoi(sep->arg[1]);
			int16 maxSkill = 0;
			for(int skill_num = 0; skill_num <= 74; skill_num++)
			{
				//Yeahlight: Check for the max skill before we put the supplied number into the skill
				maxSkill = c->GetTarget()->CheckMaxSkill(skill_num, c->GetTarget()->GetRace(), c->GetTarget()->GetClass(), c->GetTarget()->GetLevel());
				//Yeahlight: The skill's maximum for this target's class and level is lower than the supplied value
				if(maxSkill <= setNumber && maxSkill != 0)
					c->GetTarget()->CastToClient()->SetSkill(skill_num, maxSkill);
				else if(maxSkill != 0)
					c->GetTarget()->CastToClient()->SetSkill(skill_num, setNumber);
			}
			//Yeahlight: Refresh target's mitigation and avoidance
			c->GetTarget()->CalculateACBonuses();
		}
	}

void command_checkskillall(Client *c, const Seperator *sep)
{

		if (c->GetTarget() == 0)
		{
			c->Message(BLACK, "Error: #setallskill: No client targeted.");
		}
		if(c->GetTarget()->IsNPC())
		{
			for(int i = 0; i <= 74; i++)
				c->Message(WHITE, "Debug: %s's skill %i: %i", c->GetTarget()->CastToNPC()->GetProperName(), i, c->GetTarget()->GetSkill(i));
		}
		else if(c->GetTarget()->IsClient())
		{
			for(int i = 0; i <= 74; i++)
				c->Message(WHITE, "Debug: %s's skill %i: %i", c->GetTarget()->GetName(), i, c->GetTarget()->CastToClient()->GetSkill(i));
		}
}

void command_save(Client *c, const Seperator *sep)
{
		if (c->GetTarget() == 0)
			c->Message(BLACK, "Error: no target");
		else if (!c->GetTarget()->IsClient())
			c->Message(BLACK, "Error: target not a client");
		else if	(c->GetTarget()->CastToClient()->Save())
			c->Message(BLACK, "%s successfully saved.", c->GetTarget()->GetName());
		else
			c->Message(BLACK, "Manual save for %s failed.", c->GetTarget()->GetName());
}

void command_scribespells(Client *c, const Seperator *sep)
{
		if(sep->arg[1][0]==0) {
			c->Message(BLACK,"FORMAT: #scribespells <level>");
		} else if((atoi(sep->arg[1]) < 1) || (atoi(sep->arg[1]) > 60)) {
			c->Message(BLACK,"ERROR: Enter a level between 1 and 60 inclusive.");
		} else if (c->GetTarget() == 0 || !c->GetTarget()->IsClient()) {
			c->Message(BLACK,"ERROR: This command requires a valid target.");
		} else {

			int level = atoi(sep->arg[1]);

			// iterate over all spells
			int slotId = 0;

			// im to lazy, iterate over the spdat N times for each level to
			// make it scribe by Spell Level
			for(int spellLevel=0; spellLevel<=level; spellLevel++) {

				for (int spellid = 0; spellid < SPDAT_RECORDS; spellid++) {

					Spell* spell = spells_handler.GetSpellPtr(spellid);

					int Canuse = spell->CanUseSpell(c->GetTarget()->GetClass(), spellLevel);

					if (Canuse != 0) {

						if(spell->GetSpellClass(c->GetTarget()->GetClass()-1) == spellLevel) {
							c->Message(DARK_BLUE, "Scribing level %i spell %s", spellLevel, spell->GetSpellName());
							c->GetTarget()->CastToClient()->GetPlayerProfilePtr()->spell_book[slotId] = spellid;
							slotId++;
						}
					}
				}
			}

			c->Message(BLACK, "Scribing spells to spellbook done (zone to take effect)");

		}
}

void command_flymode(Client *c, const Seperator *sep)
{
		if (strlen(sep->arg[1]) == 1 && !(sep->arg[1][0] == '0' || sep->arg[1][0] == '1' || sep->arg[1][0] == '2')) {
			c->Message(BLACK, "#flymode [0/1/2]");
		}
		else
		{
			int16 Spawn_ID = -1;

			if (c->GetTarget() == 0 || !c->GetTarget()->IsClient() || c->Admin() < 100)
			{
				Spawn_ID = c->GetID();

				if (sep->arg[1][0] == '1')
				{
					c->Message(BLACK, "Turning Flymode ON");
				}
				else if (sep->arg[1][0] == '2')
				{
					c->Message(BLACK, "Turning Flymode LEV");
				}
				else
				{
					c->Message(BLACK, "Turning Flymode OFF");
				}
			}
			else
			{
				Spawn_ID = c->GetTarget()->GetID();

				if (sep->arg[1][0] == '1')
				{
					c->Message(BLACK, "Turning %s's Flymode ON", c->GetTarget()->GetName());
				}
				else if (sep->arg[1][0] == '2')
				{
					c->Message(BLACK, "Turning %s's Flymode LEV", c->GetTarget()->GetName());
				}
				else
				{
					c->Message(BLACK, "Turning %s's Flymode OFF", c->GetTarget()->GetName());
				}
			}
			c->SendAppearancePacket(Spawn_ID, SAT_Levitate, atoi(sep->arg[1]), true);
		}
}

void command_depopzone(Client *c, const Seperator *sep)
{
		zone->Depop();
		c->Message(BLACK, "Zone depoped.");
}

void command_repopzone(Client *c, const Seperator *sep)
{
		if (sep->IsNumber(1)) {
			zone->Repop(atoi(sep->arg[1])*1000);
			c->Message(BLACK, "Zone depoped. Repop in %i seconds", atoi(sep->arg[1]));
		}
		else {
			zone->Repop();
			c->Message(BLACK, "Zone depoped. Repoping now.");
		}
}
void command_sky(Client *c, const Seperator *sep)
{
	//Change the sky type of the current zone. Useful in newzone_struct testing. Maybe for GM events too. -Wizzel
	if(sep->arg[1][0]==0)
		c->Message(BLACK, "FORMAT: zsky <sky type>");
	else if(atoi(sep->arg[1])<0||atoi(sep->arg[1])>255)
		c->Message(BLACK, "ERROR: Sky type can not be less than 0 or greater than 255.");
	else {
		zone->newzone_data.sky = atoi(sep->arg[1]);

		APPLAYER* outapp = new APPLAYER(OP_NewZone, sizeof(NewZone_Struct));
		memcpy(outapp->pBuffer, &zone->newzone_data, outapp->size);
		entity_list.QueueClients(c, outapp);
		safe_delete(outapp);
	}
}
void command_fogcolor(Client *c, const Seperator *sep)
{
	//Change the fog color of the current zone. Useful in newzone_struct testing. Maybe for GM events too. -Wizzel
	if(sep->arg[3][0]==0)
	c->Message(BLACK, "FORMAT: #fogcolor <r/g/b>");
	else if(atoi(sep->arg[1])<0||atoi(sep->arg[1])>255)
		c->Message(BLACK, "ERROR: Red can not be less than 0 or greater than 255!");
	else if(atoi(sep->arg[2])<0||atoi(sep->arg[2])>255)
		c->Message(BLACK, "ERROR: Green can not be less than 0 or greater than 255!");
	else if(atoi(sep->arg[3])<0||atoi(sep->arg[3])>255)
		c->Message(BLACK, "ERROR: Blue can not be less than 0 or greater than 255!");
	else {
//		zone->newzone_data.fog_red[0] = atoi(sep->arg[1]);
//		zone->newzone_data.fog_green[0] = atoi(sep->arg[2]);
//		zone->newzone_data.fog_blue[0] = atoi(sep->arg[3]);
	}

	APPLAYER* outapp = new APPLAYER(OP_NewZone, sizeof(NewZone_Struct));
	memcpy(outapp->pBuffer, &zone->newzone_data, outapp->size);
	entity_list.QueueClients(c, outapp);
	safe_delete(outapp);
}
void command_zoneappearance(Client *c, const Seperator *sep)
{
	int8 sky;
	int8 fog_red;
	int8 fog_green;
	int8 fog_blue;
	float fog_minclip;
	float fog_maxclip;
	float minclip;
	float maxclip;
	int8 ztype;
	float safe_x;
	float safe_y;
	float safe_z;
	float underworld;
	char* zlong_name;
	//float walkspeed;

	//Grab the zone ID
	int16 zoneID = Database::Instance()->LoadZoneID(zone->GetShortName());

	Database::Instance()->GetZoneCFG(zoneID, &sky, &fog_red, &fog_green, &fog_blue, &fog_minclip, &fog_maxclip, &minclip, &maxclip, &ztype, &safe_x, &safe_y, &safe_z, &underworld, &zlong_name);

	c->Message(BLACK, "Zone Appearance:");
	c->Message(BLACK, "  Zone: %s",zlong_name);
	c->Message(BLACK, "  Zone ID: %i",zoneID);
	c->Message(BLACK, "  Sky: %i",sky);
	c->Message(BLACK, "  Fog-Red: %i",fog_red);
	c->Message(BLACK, "  Fog-Green: %i",fog_green);
	c->Message(BLACK, "  Fog-Blue: %i",fog_blue);
	c->Message(BLACK, "  Fog Minclip: %f",fog_minclip);
	c->Message(BLACK, "  Fog Maxclip: %f",fog_maxclip);
	c->Message(BLACK, "  Minclip: %f",minclip);
	c->Message(BLACK, "  Maxclip: %f",maxclip);
	c->Message(BLACK, "  Zone Type: %i",ztype);
	c->Message(BLACK, "  Safe X: %f",safe_x);
	c->Message(BLACK, "  Safe Y: %f",safe_y);
	c->Message(BLACK, "  Safe Z: %f",safe_z);
	c->Message(BLACK, "  Underworld: %f",underworld);
	//c->Message(BLACK, "  Walkspeed: %f",walkspeed);
}
void command_zoneclip(Client *c, const Seperator *sep)
{
	//Change the clip plane of the current zone. Useful in newzone_struct testing. -Wizzel
	if(sep->arg[2][0]==0)
			c->Message(BLACK, "Usage: #zclip <min clip> <max clip>");
		else if(atoi(sep->arg[1])<=0)
			c->Message(BLACK, "ERROR: Min clip can not be zero or less!");
		else if(atoi(sep->arg[2])<=0)
			c->Message(BLACK, "ERROR: Max clip can not be zero or less!");
		else if(atoi(sep->arg[1])>atoi(sep->arg[2]))
			c->Message(BLACK, "ERROR: Min clip is greater than max clip!");
		else {
			zone->newzone_data.minclip = atof(sep->arg[1]);
			zone->newzone_data.maxclip = atof(sep->arg[2]);

			APPLAYER* outapp = new APPLAYER(OP_NewZone, sizeof(NewZone_Struct));
			memcpy(outapp->pBuffer, &zone->newzone_data, outapp->size);
			entity_list.QueueClients(c, outapp);
			safe_delete(outapp);//delete outapp;
		}
}
void command_debug(Client *c, const Seperator *sep)
{
	if(atoi(sep->arg[1]) == 0)
	{
		c->SetDebugMe(false);
		c->Message(WHITE, "Debug: Turning debug mode OFF");
	}
	else
	{
		c->SetDebugMe(true);
		c->Message(WHITE, "Debug: Turning debug mode ON");
	}
}

void Client::ProcessCommand(char* message)
{

	command_realdispatch(this,message);

}

float fdistance(float x1, float y1, float x2, float y2){
	return sqrt(square(x2-x1)+square(y2-y1));
}

float square(float number){
	return number * number;
}