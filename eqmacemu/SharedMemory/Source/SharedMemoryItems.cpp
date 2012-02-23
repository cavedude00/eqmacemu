// ***************************************************************
//  EQCException   ·  date: 31/08/2009
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// -Cofruben: initial release on 31/08/09.
// ***************************************************************
#include "database.h"
#include "EQCException.hpp"
#include "itemtypes.h"
#include "SharedMemory.hpp"


bool SharedMemory::LoadItems(){
	char errbuf[MYSQL_ERRMSG_SIZE];
	char *query = 0;
	MYSQL_RES *result;
	MYSQL_ROW row;
	int id;
	query = new char[256];
	strcpy(query, "SELECT MAX(id) FROM items");

	EQC::Common::PrintF(CP_SHAREDMEMORY, "Loading items... ");
	if (Database::Instance()->RunQuery(query, strlen(query), errbuf, &result)) {
		safe_delete(query);
		row = mysql_fetch_row(result);
		if (row != 0 && row[0] > 0)
		{ 
			getPtr()->max_item = atoi(row[0]);
			if (getPtr()->max_item >= MAXITEMID) {
				EQC::Common::PrintF(CP_SHAREDMEMORY, "bool SharedMemory::LoadItems(): More items than MAXITEMID. Change constant in SharedMemory.hpp");
				return false;
			}
			memset(&getPtr()->item_array, 0, sizeof(getPtr()->item_array));
			mysql_free_result(result);

			MakeAnyLenString(&query, "SELECT id,raw_data FROM items");

			if (Database::Instance()->RunQuery(query, strlen(query), errbuf, &result))
			{
				safe_delete_array(query);//delete[] query;
				while(row = mysql_fetch_row(result))
				{
					unsigned long* lengths;
					lengths = mysql_fetch_lengths(result);
					if (lengths[1] == sizeof(Item_Struct))
					{
						id = atoi(row[0]);
						memcpy(&getPtr()->item_array[id], row[1], sizeof(Item_Struct));
						//Yeahlight: Client container exceptions
						if(getPtr()->item_array[id].type == 1)
						{
							//Tazadar : We clean this or the client crashes or bag are full of shit
							memset(&getPtr()->item_array[id].common.level,0x00,69*sizeof(int8));
						//	memset(&getPtr()->item_array[id].unknown0144[0],0x00,68*sizeof(int8));
						}
						//Yeahlight: Client book exceptions
						else if(getPtr()->item_array[id].type == 2)
						{

						}
					}
					else
					{
						cout << "Invalid items in database..." << endl;
					}
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
	EQC::Common::PrintF(CP_SHAREDMEMORY, "Item loading finished.");
	return true;
}

void SharedMemory::UnloadItems() {
}

Item_Struct* SharedMemory::getItem(uint32 id) {
	if (isLoaded() && id < SharedMemory::getMaxItem())
		return &getPtr()->item_array[id];
	else
		return NULL;
}

int SharedMemory::getMaxItem(){
	uint32 maxitm = getPtr()->max_item;
	return (maxitm > 0) ? maxitm : MAXITEMID;
}