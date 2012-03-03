// ***************************************************************
//  EQCException   ·  date: 31/08/2009
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// -Cofruben: initial release on 31/08/09.
// ***************************************************************
#include "database.h"
#include "EQCException.hpp"
#include "SharedMemory.hpp"

bool SharedMemory::LoadDoors(){
	char errbuf[MYSQL_ERRMSG_SIZE];
	char *query = 0;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int id;
	query = new char[256];
	strcpy(query, "SELECT MAX(id) FROM doors");

	EQC::Common::PrintF(CP_SHAREDMEMORY, "Loading doors... ");
	if (Database::Instance()->RunQuery(query, strlen(query), errbuf, &result)) {
		safe_delete(query);
		row = mysql_fetch_row(result);
		if (row != 0 && row[0] > 0)
		{ 
			getPtr()->max_door = atoi(row[0]);
			if (getPtr()->max_door >= MAXDOORID) {
				EQC::Common::PrintF(CP_SHAREDMEMORY, "bool SharedMemory::LoadDoors(): More items than MAXDOORID. Change constant in SharedMemory.hpp");
				return false;
			}
			memset(&getPtr()->door_array, 0, sizeof(getPtr()->door_array));
			mysql_free_result(result);

			MakeAnyLenString(&query, "SELECT name,pos_x,pos_y,pos_z,heading,opentype,doorid,triggerdoor,triggertype,door_param,incline,doorisopen,invert_state,lockpick,keyitem,dest_zone,dest_x,dest_y,dest_z,dest_heading,id FROM doors");

			if (Database::Instance()->RunQuery(query, strlen(query), errbuf, &result))
			{
				safe_delete_array(query);//delete[] query;
				while(row = mysql_fetch_row(result))
				{
					
					id = atoi(row[20]);
					memset(&getPtr()->door_array[id], 0, sizeof(Door_Struct));
					strcpy(getPtr()->door_array[id].name, row[0]);
					getPtr()->door_array[id].xPos = (float)atof(row[1]);
					getPtr()->door_array[id].yPos = (float)atof(row[2]);
					getPtr()->door_array[id].zPos = (float)atof(row[3]);
					getPtr()->door_array[id].heading = (float)atof(row[4]);
					getPtr()->door_array[id].opentype = atoi(row[5]);
					getPtr()->door_array[id].doorid = (uint8)atoi(row[6]);
					getPtr()->door_array[id].triggerID = atoi(row[7]);
					getPtr()->door_array[id].triggerType = atoi(row[8]);
					getPtr()->door_array[id].parameter = atoi(row[9]);
					getPtr()->door_array[id].incline = (float)atof(row[10]);
					getPtr()->door_array[id].doorIsOpen = atoi(row[11]);
					getPtr()->door_array[id].inverted = atoi(row[12]);
					getPtr()->door_array[id].lockpick = atoi(row[13]);
					getPtr()->door_array[id].keyRequired = atoi(row[14]);
					strcpy(getPtr()->door_array[id].zoneName, row[15]);
					getPtr()->door_array[id].destX = (float)atof(row[16]);
					getPtr()->door_array[id].destY = (float)atof(row[17]);
					getPtr()->door_array[id].destZ = (float)atof(row[18]);
					getPtr()->door_array[id].destHeading = (float)atof(row[19]);

					Sleep(0);
				}
				mysql_free_result(result);
			}
			else {
				cerr << "Error in PopulateZoneLists query '" << query << "' " << errbuf << endl;
				safe_delete_array(query);//delete[] query;
				return false;
			}
		}
		else {
			mysql_free_result(result);
		}
	}
	else {
		cerr << "Error in PopulateZoneLists query '" << query << "' " << errbuf << endl;
		safe_delete_array(query);//delete[] query;
		return false;
	}
	EQC::Common::PrintF(CP_SHAREDMEMORY, "Door loading finished.");
	return true;
}

void SharedMemory::UnloadDoors() {
}

Door_Struct* SharedMemory::getDoor(uint32 id) {
	if (isLoaded() && id < SharedMemory::getMaxDoor())
		return &getPtr()->door_array[id];
	else
		return NULL;
}

int SharedMemory::getMaxDoor(){
	uint32 maxdr = getPtr()->max_door;
	return (maxdr> 0) ? maxdr : MAXDOORID;
}
