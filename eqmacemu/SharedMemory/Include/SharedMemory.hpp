// ***************************************************************
//  EQCException   ·  date: 31/08/2009
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
// -Cofruben: initial release on 31/08/09.
// ***************************************************************
#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H
#include <windows.h>
#include "EQCUtils.hpp"
#include "eq_packet_structs.h"
#include "types.h"
#include "../../zone/include/zonedump.h"

using namespace std;

const uint32	MAXITEMID = 33000;
const uint32	MAXDOORID = 40000;

class __declspec(dllexport) SharedMemory 
{
public:
	SharedMemory();
	~SharedMemory();

	struct ShMemData_Struct {
		Item_Struct item_array[MAXITEMID];
		Door		door_array[MAXDOORID];
		uint32		max_item;
		uint32		max_door;
	};

	static bool	isLoaded();
	static bool	Load();
	static void	Unload();
	
	static Item_Struct*	getItem(uint32 id);
	static Door*		getDoor(uint32 id);
	static int			getMaxItem();
	static int			getMaxDoor();

	static void setDLL(HINSTANCE aDll) {hSharedDLL = aDll; }
	static void setMemPtr(LPVOID alpvMem) {lpvSharedMem = alpvMem; }
	static void setMapObject(HANDLE ahMapObject) {hSharedMapObject = ahMapObject; }

private:
	static bool					LoadItems();
	static void					UnloadItems();
	static bool					LoadDoors();
	static void					UnloadDoors();
	static ShMemData_Struct*	getPtr();
	static uint32				CalcSMSize();
	static HINSTANCE			hSharedDLL;
	static HANDLE				hSharedMapObject;  // handle to file mapping
	static LPVOID				lpvSharedMem;      // pointer to shared memory
};


#endif