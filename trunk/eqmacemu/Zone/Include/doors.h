#include "entity.h"
#include "mob.h"
#include "zonedump.h"

class Doors : public Entity
{
public:
	Doors(const Door* door);
	~Doors();

	virtual bool	IsDoor() { return true; }
	virtual bool	Process();
	void	HandleClick(Client* sender, int16 key);

	int8	GetDoorID() { return doorid; }
	int32	GetDoorDBID() { return db_id; }
	int8	GetOpenType() { return opentype; }
	char*	GetDoorName() { return name; }
	char*	GetZone() { return zoneName; }
	bool	IsDoorOpen() { return doorIsOpen; }
	void	SetOpenState(bool st) { doorIsOpen = st; }
	int32	GetLastClick() { return pLastClick; }

	float	GetX() { return xPos; }
	float	GetY() { return yPos; }
	float	GetZ() { return zPos; }
	float	GetHeading() { return heading; }

	int8	GetTriggerDoorID() { return triggerID; }
	int8	GetTriggerType() { return triggerType; }
	bool	triggered;
	uint8	GetInvertedState() { return inverted; }
	int16	GetParameter() { return parameter; }
	int16	GetSize() { return size; }
	float	GetIncline() { return incline; }

	int16	GetKeyItem() { return keyRequired; }
	int16	GetLockpick() { return lockpick; }

	int32	GetEntityID() { return entity_id; }
	void	SetEntityID(int32 entity) { entity_id = entity; }
	
	void DumpDoor();
	float	GetDestX() { return destX; }
	float	GetDestY() { return destY; }
	float	GetDestZ() { return destZ; }
	float	GetDestHeading() { return destHeading; }
	char*	GetDestZone() { return dest_zone; }
	
	
private:
int32	db_id;
int8	doorid;
char	zoneName[16];
char	name[16];
float	xPos;
float	yPos;
float	zPos;
float	heading;
int8	opentype;
int16	lockpick;
int16	keyRequired;
int8	triggerID;
int8	triggerType;
int32	entity_id;
bool	doorIsOpen;
int32	pLastClick;
uint8	inverted;
int16	parameter;
int16	size;
float	incline;
Timer	close_timer;
Timer*	PickLock_timer;

char    dest_zone[16];
float   destX;
float   destY;
float   destZ;
float   destHeading;


};