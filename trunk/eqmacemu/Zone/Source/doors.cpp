#include "doors.h"
#include "client.h"
#include "zone.h"
#include "skills.h"

extern Database database;
extern EntityList entity_list;
extern Zone* zone;

Doors::Doors(const Door* door)
:    close_timer(5000)
{
	db_id = door->db_id;
	doorid = door->doorid;
	strn0cpy(zoneName,door->zoneName,16);
	strn0cpy(name,door->name,16);
	xPos = door->xPos;
	yPos = door->yPos;
	zPos = door->zPos;
	heading = door->heading;
	incline = door->incline;
	opentype = door->opentype;
	lockpick = door->lockpick;
	keyRequired = door->keyRequired;
	triggerID = door->triggerID;
	triggerType = door->triggerType;
	triggered=false;
	parameter = door->parameter;
	inverted = door->inverted;
	SetOpenState(false);

	close_timer.Disable();

	strn0cpy(dest_zone,door->dest_zone,16);
	destX = door->destX;
	destY = door->destY;
	destZ = door->destZ;
	destHeading = door->destHeading;
}

Doors::~Doors()
{
}

bool Doors::Process()
{
    if(close_timer.Enabled() && close_timer.Check() && IsDoorOpen())
    {
	triggered=false;
        close_timer.Disable();
        SetOpenState(false);
    }
	return true;
}

void Doors::HandleClick(Client* sender, int16 key)
{
	bool debugFlag = true;
			//Yeahlight: If the door has not been touched in twelve seconds, then return it to the closed state
			if(time(0) - pLastClick >= 12)
				doorIsOpen = false;
			//Yeahlight: Record the time this door was touched
			pLastClick = time(0);
			if(debugFlag && sender->GetDebugMe())
				sender->Message(WHITE,"Debug: You clicked a door: #%i, parameter: %i. Door was last clicked at %i", doorid, parameter, pLastClick);
			APPLAYER* outapp = new APPLAYER(OP_OpenDoor, sizeof(DoorOpen_Struct));
			APPLAYER* outapp2 = new APPLAYER(OP_OpenDoor, sizeof(DoorOpen_Struct));
			DoorOpen_Struct* od = (DoorOpen_Struct*)outapp->pBuffer;
			//Yeahlight: Door is a trigger for another door.
			//Yeahlight: TODO: Are any triggers "locked"?
			if(triggerID > 0)
			{
				DoorOpen_Struct* od2 = (DoorOpen_Struct*)outapp2->pBuffer;
				od2->doorid = triggerID;
				od2->action = 0x02;
				entity_list.QueueClients(sender, outapp2, false);
			}
			//Yeahlight: Door is locked
			if(keyRequired > 0 || lockpick > 0)
			{
				//Yeahlight: Compare required key to item on cursor
				if(key == keyRequired)
				{
					//Yeahlight: Door is a teleporter
					if(strcmp(dest_zone, "NONE") != 0)
					{
						if(debugFlag && sender->GetDebugMe())
							sender->Message(LIGHTEN_BLUE, "Debug: You touched a locked TP object: %s", dest_zone);
						if(strcmp(zone->GetShortName(), dest_zone) != 0)
						{
							//Yeahlight: Locked door TPs player to different zone
							sender->MovePC(dest_zone, destX, destY, destZ);
						}
						else
						{
							//Yeahlight: Locked door TPs player to different location in same zone
							sender->MovePC(0, destX, destY, destZ);
						}
					}
					//Yeahlight Door is a legit "door" and needs to be opened for players
					else
					{
						if(!doorIsOpen == 1)
						{
							sender->Message(DARK_BLUE,"The door swings open!");
							od->doorid = doorid;
							od->action = 0x02;
							doorIsOpen = 1;
						}
						else
						{
							od->doorid = doorid;
							od->action = 0x03;
							doorIsOpen = 0;
						}
						entity_list.QueueClients(sender, outapp, false);
					}
				//Yeahlight: Lockpick attempt
				}
				else if(lockpick > 0 && key == 13010){
					if(PickLock_timer->Check())
					{
						//Yeahlight: 10 seconds is the lockout on the "Pick Lock" skill button
						PickLock_timer->Start(10000);
						if(sender->GetSkill(PICK_LOCK) >= lockpick)
						{
							if(!doorIsOpen == 1){
								sender->Message(DARK_BLUE,"The door swings open!");
								od->doorid = doorid;
								od->action = 0x02;
								doorIsOpen = 1;
							}
							else
							{
								od->doorid = doorid;
								od->action = 0x03;
								doorIsOpen = 0;
							}
							entity_list.QueueClients(sender, outapp, false);
							//Yeahlight: TODO: Research the range for which skilling up is possible. Set at door trivial + 15 for now
							if((sender->GetSkill(PICK_LOCK) - lockpick) <= 15)
							sender->CheckAddSkillPickLock(10);
						}
						else
						{
							sender->Message(DARK_BLUE,"You were unable to pick this lock");
						}
					}
				}
				else
				{
					sender->Message(RED, "You do not have the required key in hand to open this door");
					if(debugFlag && sender->GetDebugMe())
					{
						sender->Message(LIGHTEN_BLUE, "Debug: Key Required: (%i)",keyRequired);
						if(lockpick > 0)
							sender->Message(LIGHTEN_BLUE, "Debug: This door may be picked (%i)",lockpick);
					}
				}
			}
			//Yeahlight: Door is a teleporter
			else if(strcmp(dest_zone, "NONE") != 0)
			{
				if(debugFlag && sender->GetDebugMe())
					sender->Message(LIGHTEN_BLUE, "Debug: You touched a TP object: %s", dest_zone);
				if(strcmp(zone->GetShortName(), dest_zone) != 0)
				{
					//Yeahlight: Door TPs player to different zone
					sender->MovePC(dest_zone, destX, destY, destZ);
				}
				else
				{
					//Yeahlight: Door TPs player to different location in same zone
					sender->MovePC(0, destX, destY, destZ);
				}
			}
			//Yeahlight: Normal door, open for all other players
			else
			{
				if(!doorIsOpen == 1)
				{
					od->doorid = doorid;
					od->action = 0x02;
					doorIsOpen = 1;
					sender->Message(LIGHTEN_BLUE, "Regular Door: IsOpen");
				}
				else
				{
					od->doorid = doorid;
					od->action = 0x03;
					doorIsOpen = 0;
					sender->Message(LIGHTEN_BLUE, "Regular Door: Is Not Open");
				}
				entity_list.QueueClients(sender, outapp, false);
			}
			safe_delete(outapp);//delete outapp;
			safe_delete(outapp2);//delete outapp2;
			return;

			//Yeahlight: Zone freeze debug
		if(ZONE_FREEZE_DEBUG && rand()%ZONE_FREEZE_DEBUG == 1)
			EQC_FREEZE_DEBUG(__LINE__, __FILE__);
		}
		