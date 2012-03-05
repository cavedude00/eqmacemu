/*  EQEMu:  Everquest Server Emulator
    Copyright (C) 4001-4002  EQEMu Development Team (http://eqemu.org)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY except by those people which sell it, which
	are required to give you total support for your newly bought product;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR
	A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  04111-1307  USA
*/
#ifndef EQ_OPCODES_H
#define EQ_OPCODES_H

#define OP_SERVERMOTD		0xdd41		// Comment: froglok23 : Server MOTD opcode.

#define OP_PetitionClientUpdate		0x0f40	// Comment:
/*============ Merchants ============*/
#define OP_ShopRequest		0x0b40		// Comment: right-click on merchant
#define OP_ShopItem			0x0c40		// Comment:
#define OP_ShopPlayerBuy	0x3540		// Comment: Cofruben: correct opcode.
#define OP_ShopPlayerSell	0x2740		// Comment: Cofruben: correct opcode.
#define OP_ShopDelItem		0x3840		// Comment: Tazadar: correct opcode.
#define OP_ShopEnd			0x3740		// Comment:
#define OP_ShopEndConfirm	0x4541		// Comment:

/*============== Items ==============*/
#define OP_ItemTradeIn		0x3140		// Comment:
#define OP_LootComplete		0x4541		// Comment:
#define OP_EndLootRequest	0x4F40		// Comment:
#define OP_MoneyOnCorpse	0x5040		// Comment:
#define OP_SplitMoney		0x3141      // Comment:
#define OP_ItemOnCorpse		0x5240		// Comment:
#define OP_LootItem			0xA040		// Comment:
#define OP_LootRequest		0x4e40		// Comment:
#define OP_DropCoin			0x0740		// Comment: Player attempts to drop coin on ground.  (Size: 112)
#define OP_PickupCoin		0x0840		// Comment: Yeahlight: Not testing, but this may be correct
#define OP_DropItem			0x3540		// Comment: Player attempts to drop item on ground.
#define OP_PickupItem		0x3640		// Comment: Player clicks to attempt to pick up an object on ground.

/*============== Doors ==============*/
#define	OP_SpawnDoor		0xf741		// Comment: //9450
#define OP_CSpawnDoor		0x9520
#define	OP_UpdateDoor		0x9840		// Comment:
#define	OP_ClickDoor		0x8d40		// Comment:
#define	OP_OpenDoor			0x8e40		// Comment:
#define OP_DespawnDoor		0x9b40		// Comment: Yeahlight: Despawns a door

/*============== Message Board ==============*/
#define OP_MBRetrieveMessages			0x0841		// Comment: Player clicks on a Message Board or on a category GENERAL/Sales etc (Harakiri)
#define OP_MBRetrieveMessage			0x0941		// Comment: Player right clicks on a specific message (Harakiri)
#define OP_MBSendMessageToClient		0x0a41		// Comment: Send 1 Message each time to Client for Message Board Message List (Harakiri)
#define OP_MBMessageDetail				0x0b41		// Comment: Server signals that message detail was sent, now open detail popup (Harakiri)
#define OP_MBPostMessage				0x0c41		// Comment: Client sents a post request for a messsage (Harakiri)
#define OP_MBEraseMessage				0x0d41		// Comment: Client sents a delete request for a messsage (Harakiri)
#define OP_MBDataSent_OpenMessageBoard	0x0e41		// Comment: Signal the client that all available messages have been sent or a erase/post request was successful, show now the message board


/*============= Trading =============*/
#define OP_Click_Give		0xda40		// Comment:
#define OP_CloseTrade		0xdc40		// Comment:
#define OP_CancelTrade		0xdb40		// Comment:
#define OP_TradeAccepted    0xE640
#define OP_ItemToTrade		0xdf40      // Comment:	Send items on the other client windows while trading
#define OP_TradeCoins		0xe440      // Comment: Client update the amount of money in trade window (Confirmed By Tazadar)

/*============= Groups ============= */
#define OP_GroupExp			    0x9a40  // Comment: Tazadar :This is the group message exp opcode (empty packet it seems), Confirmed: Harakiri
#define OP_GroupInvite			0x3e20
#define OP_GroupInvite2			0x4040	//
#define OP_GroupFollow			0x3d20
#define OP_GroupFollow2			0x4240	// Sent after someone clicks 'Follow' after receiving group invite;
#define OP_GroupDeclineInvite	0x4120	// Sent when member declines group invite by clicking disband;
#define OP_GroupQuit			0x4440	// Sent when member chooses to disband OR member is kicked from leader;
#define OP_GroupUpdate			0x2620	// Used to notify group members of group events;
#define OP_GroupDelete			0x9721	// When leader clicks disband on himself;

/*========== Guild Commands =========*/
#define OP_GuildInviteAccept	0x1841  // Comment:
#define OP_GuildLeader			0x9541	// Comment: /guildleader command
#define OP_GuildPeace			0x9141	// Comment: /guildpeace command
#define OP_GuildWar				0x6f41	// Comment: /guildwar command
#define OP_GuildInvite			0x1741	// Comment: /guildinvite command
#define OP_GuildRemove			0x1941	// Comment: /guildremove command
#define OP_GuildMOTD			0x0342	// Comment: /guildmotd command
#define OP_GuildUpdate			0x7b41	// Comment:
#define OP_GuildsList			0x9241	// Comment:

/*========== General Skills =========*/
#define OP_Beg			    0x2541		// Comment: Player attempts to start begging.
#define OP_Forage			0x9440		// Comment:
#define OP_Fishing			0x8f41		// Comment:
#define OP_BindWound		0x9340		// Comment: Sent when a player attempts to bind wound.

/*=========== Class Skills ==========*/
#define OP_Sneak			0x8541		// Comment:
#define OP_Hide				0x8641		// Comment:
#define OP_SenseTraps		0x8841		// Comment:
#define OP_Mend				0x9d41		// Comment:
#define OP_HarmTouch		0x7E41		// Comment:
#define OP_Taunt			0x3b41		// Comment:
#define OP_FeignDeath		0xac40		// Comment: Harakiri: If you sent this to the client with 1, it will print Phineas_Taylor00 has been slain by Phineas_Taylor00! if Phineas is entity id 1 in your zone
#define OP_InstillDoubt		0x9c41		// Comment:
#define OP_PickPockets		0xad40		// Comment: Player click pickpocket on a PC.
#define OP_DisarmTraps		0xf341		// Comment: Player clicks disarm traps in the abilities tab.
#define OP_SafeFallSuccess	0xab41		// Comment: Player falls and absorbs some damage.
#define OP_Track			0x8441		// Comment: Player clicks track in the abilities tab.
#define OP_ApplyPoison		0xba41		// Comment: Harakiri client sents this when you right click on a poison

/*============== Boats ==============*/
#define	OP_GetOnBoat		0xbb41		// Comment: Player gets on a boat.
#define OP_GetOffBoat		0xbc41		// Comment: Player leaves a boat.
#define OP_CommandBoat		0x2641		// Comment: Player on a small boat clicks on the boat to control it. Yeahlight: This may also be used to control an NPC

/*============= General =============*/
#define	OP_ReadBook			0xce40		// Comment:
#define OP_MultiLineMsg		0x1440		// Comment:
#define OP_CPlayerItems		0xf641		// Comment:
#define OP_CPlayerItem		0x6441		// Comment:
#define OP_Illusion			0x9140		// Comment:
#define OP_LFG				0xf041		// Comment:
#define OP_Translocate		0x0642		// Comment:
#define OP_Jump				0x2040		// Comment:
#define OP_MovementUpdate	0x1F40		// Comment:
#define OP_SenseHeading		0x8741		// Comment:
#define OP_SafePoint		0x2440		// Comment:
#define OP_Surname			0xc441		// Comment:
#define OP_YellForHelp		0xda41		// Comment:
#define OP_ZoneServerInfo	0x0480		// Comment:
#define OP_ChannelMessage	0x0741		// Comment:
#define OP_Camp				0x0742		// Comment:
#define OP_ZoneEntry		0x2840		// Comment:
#define OP_DeleteSpawn		0x2940		// Comment:
#define OP_MoveItem			0x2c41		// Comment:
#define OP_MoveCoin			0x2d41		// Comment:
#define OP_TradeMoneyUpdate	0x3d41      // Comment: Update the amount of money of the client after a trade :)
#define OP_PlayerProfile	0x3640		// Comment:
#define OP_Save				0x2e40		// Comment:
#define OP_Consider			0x3741
#define OP_ConsiderCorpse   0x3442
#define OP_SendCharInfo		0x4740
#define OP_NewSpawn			0x6b42
#define OP_ZoneSpawns		0x5f41
#define OP_Death			0x4a40		// Comment:
#define OP_AutoAttack		0x5141		// Comment:
#define OP_InitiateConsume  0x9041		// Comment: Harakiri - can be sent to the client to initiate an auto consume of a specific itemID in a specific Slot
#define OP_NAMEAPPROVAL		0x8B40		// Comment:
#define OP_ENTERWORLD		0x0180		// Comment:
#define OP_ENVDAMAGE2		0x1e40		// Comment:
#define OP_Stamina			0x5741		// Comment:
#define OP_AutoAttack2		0x6141		// Comment:
#define OP_SendLoginInfo	0x5818		// Comment:
#define OP_Action			0x5840		// Comment:
#define OP_DeleteCharacter	0x5a40		// Comment:
#define OP_NewZone			0x5b40		// Comment:
#define OP_ClientTarget		0x6241		// Comment:
#define OP_TargetGroupBuff	0x2042
#define OP_Target			0xfe41		// /client /target and /rtarget
#define OP_Target2			0xe401		// LoY Opcode?
#define OP_SummonedItem		0x7841		// Comment:
#define OP_SpecialMesg		0x8041		// Comment:
#define OP_WearChange		0x9240		// Comment:
#define SUB_ChangeChar		32767		// Comment:
//#define SUB_RequestSlot		24397		// Comment:
#define OP_LevelUpdate		0x9841		// Comment:
#define OP_SplitResponse	0x9a41      // Comment: Tazadar : send the money to player after autosplit (noise + message included)
#define OP_CleanStation		0x0542      // Comment: Tazadar : remove items from station !! (i found you muhaha!!!!)
#define OP_ExpUpdate		0x9941		// Comment:
#define OP_SkillUpdate		0x8941		// Comment:
#define OP_Attack			0xa140
#define OP_MobUpdate		0x9f40
#define OP_ZoneChange		0xa340		// Comment:
#define	OP_CraftingStation	0xd740		// Comment:
#define OP_HPUpdate			0xb240		// Comment:
#define OP_TimeOfDay		0xf240		// Comment:
#define OP_ClientUpdate		0xf340		// Comment:
#define OP_WhoAll			0xf440		// Comment:
#define OP_SpawnAppearance	0xf540		// Comment:
#define OP_BeginCast		0xa940		// Comment:
#define OP_CastSpell		0x7e41		// Comment:
#define OP_Buff				0x3241		// Comment:
#define OP_CastOn			0x4640		// Comment:
#define OP_InterruptCast	0x3542		// Comment:
#define OP_ManaChange		0x7f41		// Comment:
#define OP_MemorizeSpell	0x8241 		// Comment:
#define OP_DeleteSpell		0x4a42
#define OP_SwapSpell		0xce41 		// Comment:
#define OP_CombatAbility	0x6041		// Comment: 0x5f41
//#define OP_UseAbility		0x9f40		// Comment:
#define OP_GiveItem			0xd140		// Comment:
#define OP_StationItem		0xfb40		// Comment:
#define OP_ExpansionInfo	0xd841		// Comment:
#define OP_Random			0xe741		// Comment:
#define OP_Weather			0x3641		// Comment:
#define OP_Stun				0x5b41		// Comment:
#define OP_WebUpdate		0x3c42		// Comment:
#define OP_CharacterCreate	0x4940		// Comment:
#define OP_ZoneUnavail		0x0580		// Comment:
#define OP_InspectRequest	0xb540		// Comment:
#define OP_InspectAnswer	0xb640		// Comment:
#define OP_ConsumeItem		0x5641		// Comment: Received when client right clicks alcohol in inv. or when arrows etc are consumed
#define OP_ConsumeFoodDrink	0x4641		// Comment: Used when food or drink is consumed (auto and right clicked)
#define OP_ConsentRequest	0xb740		// Comment: Received when client types /consent
#define OP_ConsentResponse	0xb741		// Comment:
#define	OP_RequestDuel		0xcf40		// Comment:
#define OP_DuelResponse		0xd040		// Comment:
#define OP_DuelResponse2	0x5d41		// Comment:
#define OP_RezzRequest		0x2a41		// Comment: Player casts a rez spell on a corpse.
#define	OP_Sacrifice		0xea41		// Comment: Sent to a player to accept a sacrifice (Confirmed by Tazadar)
#define OP_RezzAnswer		0x9b41		// Comment:
#define OP_RezzComplete		0xec41		// Comment: Harakiri, with all 1 this will print blue text, "Resurrect failed, unable to find corpse."
#define OP_Medding			0x5841		// Comment: Player opens or closes a spell book.
#define OP_SenseHeading		0x8741		// Comment: Player clicks on sense heading in the abilities tab.
#define OP_BackSlashTarget	0xfe41		// Comment: Player issues /target command.
#define OP_AssistTarget		0x0042		// Comment: Player issues /assist command.
#define OP_QuestCompletedMoney 0x8040	// Comment: Yeahlight: Music played when a quest is completed; Harakiri: Its actually the quest completed opcode, if you fill the struct with 1 you get money from NPC with ID 1
#define OP_SpawnProjectile	0x4540		// Comment: Yeahlight: Spawns a projectile
#define OP_ZoneUnavailable	0xa240		// Comment: Harakiri red message "That zone is currently down, moving you to safe point within your current zone."
#define OP_NPCIsBusy		0xd640		// Comment: Harakiri prints message Phineas_Taylor00 tells you, 'I'm busy right now.' if Phin is entity ID 1 in your zone
#define OP_SenseTrap		0xf441		// Comment: Harakiri player will turn in the direction where a trap is located
#define OP_CorpseDragPermission		0x1441  // Comment: Harakiri yellow message X has permission to drag corpse
#define OP_PartyChannelMessage		0x1740	// Comment: Harakiri Needs Entity ID from sender at one of the first 20 locations, will issue "X tells the party"
#define OP_GuildChannelMessage		0x3341	// Comment: Harakiri green message told the guild <garbled> - probably needs entity ID and string msg
#define OP_DoorSays					0x1641	// Comment: Harakiri #yellow message The door says, "...
#define OP_Ressurection_Failed		0x2240	// Comment: Harakiri  blue message "You were unable to restore the corpse to life, but you may have success with a later attempt." rez failed?
#define OP_Sell_Message				0x27F3	// Comment: Harakiri red message "Error.  Tried to sell possessions that were NULL."  cavedude: maybe wrong
#define OP_GuildCreateResponse		0x2b41	// Comment: Harakiri with 1 message "The new player guild was created." , with 0 message "Failed to create new player guild."
#define OP_ItemMissing				0x2F41  // Comment: Harakiri blue message You are missing, sent by the client when he casts a spell and doesnt have the components "You are missing some required spell components."
#define OP_MoneyTrade				0x3F40  // Comment: Harakiri green message "You receive <randomvalue> Platinum from ." player gets the money in inventory
#define OP_MessageUnstuned			0x5bd1	// Comment: Harakiri message You are unstunned. needs value of 1   cavedude: maybe wrong
#define OP_CorpseInZone				0xa741  // Comment: Harakiri Yellow Text Corpse:  in zone: , response to /corpse?
#define OP_UseDiscipline			0xe641  // Maybe 0x6042 Comment: Harakiri client will sent this after issuing /discpline - in pp the bit discplineAvailable needs to be set to 1
#define OP_ClientError				0x4741	// Comment: Harakiri client sents this when an error client side happend i.e. a stackable item without charges sent to the client, or an invalid item (got a bogus item) etc
#define OP_TeleportPC				0x4D41  // Comment: Harakiri THIS is the generic opcode to teleport a PC, just sent TeleportPC_Struct,
											// the client will automatically decide if the player needs to be zoned to another zone or just moved to the coord if the player is already in the zone he should be teleported to
#define OP_PlayerDeath				0x2941  // Comment: Harakiri sent by the client when the player is death right before sending zone change struct at offset 0048048E, afterwards clears all the vars in the playerProfile like memorized spells and money
#define OP_PlayerSave				0x5441  // Comment: Harakiri sent before zoning there is a flag either this or OP_PlayerSave2 is sent
#define OP_PlayerSave2				0x5541  // Comment: Harakiri sent before zoning there is a flag either this or OP_PlayerSave2 is sent
#define OP_ItemView					0x6442
#define OP_ViewPetition				0x6142
#define OP_DeletePetition			0x6422
#define OP_CommonMessage			0x3642
#define OP_SendZonepoints			0xb440
//#define OP_AAPoints				0x1522 //ShowEQ 4.3.4
#define OP_UpdateAA					0x1442
#define OP_RespondAA				0x1542
#define OP_SendAAStats				0x2342
#define OP_BazaarWindow				0x1142
#define OP_TraderWindow				0x1422
#define OP_Charm					0x4442
#define OP_PetCommands				0x4542
#define PET_BACKOFF			1
#define PET_GETLOST			2
#define PET_HEALTHREPORT	4
#define PET_GUARDHERE		5
#define PET_GUARDME			6
#define PET_ATTACK			7
#define PET_FOLLOWME		8
#define PET_SITDOWN			9
#define PET_STANDUP			10
#define PET_TAUNT			11
#define PET_LEADER			16

/*======== TESTING / Unconfirmed =======*/
#define	OP_CreateObject		0x2c40
#define	OP_ClickObject		0x2b40
#define OP_TradeRequest		0xd140
#define OP_Summon			0x3d40		// Comment: Tazadar :Need more work on it , but it says 's hands are full !
#define OP_PKAcknowledge	0x8c41		// Comment: Tazadar :It sends a message :You are now a PK !!
#define OP_GMQuestResponse	0xc041      // Comment: Tazadar :It sends a message :GM quest succesful!
#define	OP_SkillChangeResp	0xbe41		// Comment: Tazadar :It sends a message :Skill change OK!
#define OP_AbilChangeResp	0xbf41		// Comment: Tazadar :It sends a message :Ability change OK!
#define OP_XPGiveResponse	0xc141	    // Comment: Tazadar :It sends a message :XP give OK!
#define OP_XPSetResponse	0xc241	    // Comment: Tazadar :It sends a message :XP set OK!
#define OP_ForceLogOut		0xd940		// Comment: Tazadar :It seems to forces the logout Confirmed: Harakiri
#define OP_LoseControl		0xb040      // Comment: Tazadar :It tells you that you have the control of yourself again
#define OP_ConsentPlayer	0xd540		// Comment: Tazadar :It tells the other client he has permission to drag soandso's corpse
#define OP_PlayerKiller		0xcf41		// Comment: Tazadar :It asks you if you are sure to become a pk or not :)
#define OP_PoisonComplete   0xba41      // Comment: Tazadar :It tells you if you succefully applied the poison Confirmed: Harakiri
#define OP_DisarmComplete   0xaa40      // Comment: Tazadar :It tells you if you succefully disarmed Confirmed: Harakiri 1 or 0 if success or not
#define OP_GMFindPlayer     0x6940      // Comment: Tazadar :It says (player is in zone ... at loc x=.. y=..
#define OP_EnvDamage		0x5840
#define SummonedItem	    0x7841
#define SummonedContainer   0x7941
#define OP_ClassTraining	0x9c40		// Comment:	AKA (GMTraining) - Renamed to avoid confusion
#define OP_ClassEndTraining	0x9d40		// Comment:	AKA (GMEndTraining) - Renamed to avoid confusion
#define OP_ClassTrainSkill	0x4041		// Comment: AKA (GMTrainSkill) - Renamed to avoid confusion
#define OP_TimeOfDaySound	0xf240		// Comment: Yeahlight: I hear cricket noises with this opcode
#define OP_SummonUnknownItem 0x3440  // Comment: Harakiri default perlnecklace will be summoned at cursor
#define OP_SpawnUnkownItem	0xf640	// Comment: Harakiri bag spawns at 0 0 0 int8[20] all 1, other values may crash client with 100 array

/*========== Support Opcodes ===========*/
#define OP_GMNameApprovalWindow	0x8c40  // Comment: Harakiri GM Name Approval Window appears
#define OP_GMPetitionWindow		0xd041  // Comment: Harakiri GM Petition Window appears
#define OP_PetitionCheckout		0x8e41	// Comment:
#define OP_PetitionDelete		0xa041	// Comment:
#define OP_PetitionCheckIn		0x9e41	// Comment:
#define OP_PetitionRefresh		0x1140	// Comment:
#define OP_BugReport			0xb340	// Comment:
#define OP_Petition				0x0e40	// Comment:
#define OP_Social_Text			0x1540	// Comment:
#define OP_Social_Action		0xa140	// Comment:
#define OP_SetDataRate			0xe841	// Comment:
#define OP_SetServerFilter		0xff41	// Comment:
#define OP_SetServerFilterAck	0xc341	// Comment:
#define OP_TradeSkillCombine	0x0541	// Comment:
#define OP_Report				0xbd41

/*=========== GM Commands ==============*/
#define OP_GMGetSkillInfo		0xe041	// Comment: Harakiri - prints all the skills and their value of a target?
#define OP_GMZoneRequest		0x4f41 	// Comment: Quagmire - client sends this when you use /zone
#define OP_GMZoneRequest2		0x0842	// Comment:
#define OP_GMGoto				0x6e40	// Comment: /goto command
#define OP_GMSummon				0xc540	// Comment:
#define OP_GMNameChange			0xcb40	// Comment: /name command
#define OP_GMKill				0x6c40	// Comment: /kill command
#define OP_GMSurname			0x6e41	// Comment: /Surname command
#define OP_GMToggle				0xde41	// Comment: /toggle command
#define OP_GMDelCorpse			0xe941	// Comment:
#define	OP_GMKick				0x6d40	// Comment:
#define OP_GMServers			0xa840	// Comment:
#define OP_GMHideMe				0xd441	// Comment:
#define OP_GMEmoteZone			0xe341	// Comment:
#define OP_GMBecomeNPC			0x8c41	// Comment: Yeahlight: /becomeNPC
/*======================================*/

/************ ENUMERATED PACKET OPCODES ************/
#define ALL_FINISH                  0x0500	// Comment:

// Login Server?
#define LS_REQUEST_VERSION          0x5900	// Comment:
#define LS_SEND_VERSION             0x5900	// Comment:
#define LS_SEND_LOGIN_INFO          0x0100	// Comment:
#define LS_SEND_SESSION_ID          0x0400	// Comment:
#define LS_REQUEST_UPDATE           0x5200	// Comment:
#define LS_SEND_UPDATE              0x5200	// Comment:
#define LS_REQUEST_SERVERLIST       0x4600	// Comment:
#define LS_SEND_SERVERLIST          0x4600	// Comment:
#define LS_REQUEST_SERVERSTATUS     0x4800	// Comment:
#define LS_SEND_SERVERSTATUS        0x4A00	// Comment:
#define LS_GET_WORLDID              0x4700	// Comment:
#define LS_SEND_WORLDID             0x4700	// Comment:

// World Server?
#define WS_SEND_LOGIN_INFO          0x5818	// Comment:
#define WS_SEND_LOGIN_APPROVED      0x0710	// Comment:
#define WS_SEND_LOGIN_APPROVED2     0x0180	// Comment:
#define WS_SEND_CHAR_INFO           0x4720	// Comment:

#endif
